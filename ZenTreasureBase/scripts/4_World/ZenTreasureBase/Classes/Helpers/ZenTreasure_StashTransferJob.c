// This is getting convoluted but I am having reports from so many different servers about issues with stashes not spawning properly
// So this class monitors the stash transfer - it attempts to move the crate into the stash immediately (works fine for my server but not for some)
// If that fails, it re-attempts every few seconds, using multiple inventory juncture methods, and if it fails it notifies the player and error logs.
// This mod is making me want to kill myself.
class ZenTreasure_StashTransferJob
{
	protected PlayerBase m_Player;
	protected EntityAI m_Container;
	protected UndergroundStash m_Stash;
	protected ref Timer m_Timer;
	protected int m_Attempts;
	protected int m_MaxAttempts;

	void ZenTreasure_StashTransferJob(notnull PlayerBase player, notnull EntityAI container, notnull UndergroundStash stash)
	{
		m_Player = player;
		m_Container = container;
		m_Stash = stash;
		m_Attempts = 0;
		m_MaxAttempts = 10;

		m_Timer = new Timer(CALL_CATEGORY_SYSTEM);

		// First re-attempt waits 1 second. This gives newly spawned entities time to register network/object state.
		m_Timer.Run(1.0, this, "TryMoveToStash", null, true);

		// Give it a try immediately
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TryMoveToStash);
	}

	void TryMoveToStash()
	{
		m_Attempts++;

		if (!m_Player)
		{
			ZMPrint("[ZenTreasure] Stash transfer cancelled: player is null.");
			Finish();
			return;
		}

		if (!m_Container)
		{
			ZMPrint("[ZenTreasure] Stash transfer cancelled: container is null.");
			Finish();
			return;
		}

		if (!m_Stash)
		{
			ZMPrint("[ZenTreasure] Stash transfer cancelled: stash is null.");
			Finish();
			return;
		}

		m_Container.Update();
		m_Stash.Update();

		bool movedToStash = false;
		string method = "";

		if (m_Stash && m_Stash.GetInventory() && m_Container)
		{
			movedToStash = m_Stash.GetInventory().TakeEntityToInventory(InventoryMode.SERVER, FindInventoryLocationType.CARGO, m_Container);
			method = " using stash.TakeEntityToInventory()";
		}

		if (!movedToStash && m_Player)
		{
			movedToStash = m_Player.ServerTakeEntityToTargetCargo(m_Stash, m_Container);
			method = " using player.ServerTakeEntityToTargetCargo()";
		}

		if (movedToStash)
		{
			ZMPrint("[ZenTreasure] Took container " + m_Container.GetType() + " to stash " + m_Stash.GetType() + method + " after attempts=" + m_Attempts);

			m_Stash.SetLifetimeMax(GetZenTreasureConfig().TreasureStashPersistenceSecs);
			m_Stash.SetLifetime(GetZenTreasureConfig().TreasureStashPersistenceSecs);

			m_Container.SetLifetimeMax(GetZenTreasureConfig().TreasureStashPersistenceSecs);
			m_Container.SetLifetime(GetZenTreasureConfig().TreasureStashPersistenceSecs);
			m_Container.IncreaseLifetimeUp();

			Finish();
			return;
		}

		if (m_Attempts >= m_MaxAttempts)
		{
			Error("[ZenTreasure] Failed to move " + m_Container + " into stash " + m_Stash + " after attempts=" + m_Attempts);

			if (m_Container)
			{
				m_Container.DeleteSafe();
			}

			if (m_Stash)
			{
				m_Stash.DeleteSafe();
			}

			if (m_Player)
			{
				ZenNotifications.Notify(m_Player, "#layout_notification_info_warning", "#STR_ZenTreasure_SpawnFailed", "", 30);
			}

			Finish();
			return;
		}

		ZMPrint("[ZenTreasure] Stash transfer retry " + m_Attempts + "/" + m_MaxAttempts);
	}

	protected void Finish()
	{
		if (m_Timer)
		{
			m_Timer.Stop();
		}

		PluginZenTreasureTriggerManager stashPlugin = PluginZenTreasureTriggerManager.Cast(GetPlugin(PluginZenTreasureTriggerManager));
		if (stashPlugin)
		{
			stashPlugin.RemoveTransferJob(this);
		}
	}
}