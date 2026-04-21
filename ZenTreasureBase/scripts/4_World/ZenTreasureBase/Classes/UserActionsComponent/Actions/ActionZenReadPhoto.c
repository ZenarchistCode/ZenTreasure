class ActionZenReadPhotoCB : ActionContinuousBaseCB {}

class ActionZenReadPhoto : ActionContinuousBase
{
	void ActionZenReadPhoto()
	{
		m_CallbackClass = ActionZenReadPhotoCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_PRONE;
		m_Text = "#read";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return !player.IsPlacingLocal();
	}

	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		#ifdef ZenModPack
		if (!ZenModEnabled("ZenTreasure"))
			return;
		#endif

		ZenTreasure_PhotoBase photo = ZenTreasure_PhotoBase.Cast(action_data.m_MainItem);
		if (!photo || !action_data.m_Player)
			return;

		// Check we're on the right map First
		string mapName = photo.ConfigGetString("mapName");
		mapName.ToLower();

		if (mapName != "missing")
		{
			string thisMapName = g_Game.GetWorldName();
			thisMapName.ToLower();

			if (thisMapName != mapName)
			{
				string notifyText;
				g_Game.ConfigGetText("CfgVehicles ZenTreasure_" + mapName + " wrongMapText", notifyText);
				SendMessageToClient(action_data.m_Player, notifyText);
				return;
			}
		}

		// Only spawn the stash for this particular photo once.
		if (!photo.SpawnedStash())
		{
			photo.SpawnStash(action_data.m_Player);

			// First time player reads photo - SynchDirty() on SpawnStash() takes too long so send stash type along with InspectMenu open RPC
			GetRPCManager().SendRPC("ZenMod_RPC", "RPC_ReceiveZenTreasurePhotoReadClient", new Param2<ItemBase, int>(photo, photo.GetStashType()), true, action_data.m_Player.GetIdentity(), action_data.m_Player);
		}
		else
		{
			// Photo info is already known - request client open Inspect Menu on this photo
			GetRPCManager().SendRPC("ZenMod_RPC", "RPC_ReceiveZenTreasurePhotoReadClient", new Param2<ItemBase, int>(photo, -1), true, action_data.m_Player.GetIdentity(), action_data.m_Player);
		}
	}

	// For compatibility with @ZenCraftingSounds
	override string GetSoundCategory(ActionData action_data)
	{
		return "Zen_Paper";
	}
}