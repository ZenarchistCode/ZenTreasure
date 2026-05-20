class PluginZenTreasureTriggerManager extends PluginBase
{
	protected ref array<ZenTreasure_StashTrigger> m_Triggers; 
	private ref array<ref ZenTreasure_StashTransferJob> m_TransferJobs;
	
    override void OnInit()
    {
		super.OnInit();
		
        ZMPrint("[ZenTreasureTriggerManager] :: OnInit");
		
		m_Triggers = new array<ZenTreasure_StashTrigger>;
		m_TransferJobs = new array<ref ZenTreasure_StashTransferJob>;
    }
	
	array<ZenTreasure_StashTrigger> GetTriggers()
	{
		return m_Triggers;
	}
	
	array<ref ZenTreasure_StashTransferJob> GetTransferJobs()
	{
		return m_TransferJobs;
	}
	
	void AddTransferJob(ZenTreasure_StashTransferJob job)
	{
		m_TransferJobs.Insert(job);
	}
	
	void RemoveTransferJob(ZenTreasure_StashTransferJob job)
	{
		m_TransferJobs.RemoveItem(job);
	}

	void SpawnStartupTriggers()
	{
		// Loop through config to spawn triggers on server startup
		foreach (ZenTreasureTriggerConfig cfg : GetZenTreasureDB().TreasureTriggers)
		{
			SpawnTrigger(cfg);
		}
	}

	void SpawnTrigger(ZenTreasureTriggerConfig cfg, PlayerBase player = null)
	{
		// Check if one already exists for this cfg first
		for (int i = m_Triggers.Count() - 1; i >= 0; i--)
		{
			ZenTreasure_StashTrigger existingTrigger = m_Triggers.Get(i);
			if (!existingTrigger)
			{
				Error("Strange error: ZenTreasure_StashTrigger does not exist for index: " + i);
				m_Triggers.Remove(i);
				continue;
			}

			if (!existingTrigger.GetConfig().Position)
			{
				Error("Strange error: vector Position does not exist for index: " + i);
				m_Triggers.Remove(i);
				continue;
			}

			if (vector.Distance(existingTrigger.GetConfig().Position, cfg.Position) < 1)
			{
				existingTrigger.SetConfig(cfg);
				
				if (player && vector.Distance(existingTrigger.GetPosition(), player.GetPosition()) <= GetZenTreasureConfig().TreasureStashSpawnTriggerDistance)
				{
					ZMPrint("[ZenTreasureTriggerManager] Player is too close to trigger - forcing manual spawn.");
					existingTrigger.ZenOnEnter(player);
				}
				
				Print("ZenTreasureTriggerManager::SpawnTrigger() - Updated trigger @ " + cfg.Position);
				return;
			}
		}

		ZenTreasure_StashTrigger trigger = ZenTreasure_StashTrigger.Cast(g_Game.CreateObject("ZenTreasure_StashTrigger", cfg.Position));
		
		if (!trigger)
		{
			Error("ZenTreasureTriggerManager::SpawnTrigger() - Failed to spawn trigger!");
			return;
		}

		trigger.SetPosition(cfg.Position); // Ensure no place on surface etc happens
		trigger.SetConfig(cfg);
		trigger.SetCollisionSphere(GetZenTreasureConfig().TreasureStashSpawnTriggerDistance);
		m_Triggers.Insert(trigger);
		ZMPrint("ZenTreasureTriggerManager::SpawnTrigger() - Successfully spawned trigger @ " + cfg.Position);

		if (player && vector.Distance(trigger.GetPosition(), player.GetPosition()) <= GetZenTreasureConfig().TreasureStashSpawnTriggerDistance)
		{
			ZMPrint("[ZenTreasureTriggerManager] Player is too close to trigger - forcing manual spawn.");
			trigger.ZenOnEnter(player);
		}
	}

	void RemoveTrigger(ZenTreasure_StashTrigger trigger)
	{
		// Don't delete the trigger if other players are still attached to it
		if (trigger.GetConfig().TreasureHunters.Count() > 0)
			return;

		for (int i = m_Triggers.Count() - 1; i >= 0; i--)
		{
			ZenTreasure_StashTrigger existingTrigger = m_Triggers.Get(i);
			if (existingTrigger == trigger)
			{
				existingTrigger.DeleteSafe();
				m_Triggers.Remove(i);
			}
		}
	}
}