modded class MissionBase
{
	//! SHARED 
	void MissionBase()
	{
		#ifndef SERVER
		//! TREASURE 
		GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenTreasureTextClient", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenTreasurePhotoReadClient", this, SingeplayerExecutionType.Client);
        #endif

		//! TREASURE 
		// Load how many photos exist for RandomPhoto spawner
		for (int i = 0; i < GetGame().ConfigGetChildrenCount("CfgVehicles"); i++)
		{
			string cfg_name = "";
			GetGame().ConfigGetChildName("CfgVehicles", i, cfg_name);
			if (cfg_name.Contains("ZenTreasure_Photo") && !cfg_name.Contains("Base"))
				ZenTreasure_RandomPhoto.PHOTO_COUNT++;
		}

		Print("[ZenTreasure] Loaded " + ZenTreasure_RandomPhoto.PHOTO_COUNT + " random photo types.");
	}

	//! TREASURE 
	// Server -> inform player of treasure descriptions
	void RPC_ReceiveZenTreasureTextClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<array<string>> data;
        if (!ctx.Read(data))
        {
            Error("[ZenTreasure] Error sync'ing server-side data to client - RPC_ReceiveZenTreasureTextClient");
            return;
        }

		// Copy config over from received map
		for (int i = 0; i < data.param1.Count(); i++)
		{
			ZenTreasureConfig.TreasureDescriptions.Insert(data.param1.Get(i));
		}
    }

	// Server -> player reads photo for first time -> tells client to open inspect menu via RPC along with photo data before SynchDirty happens
	void RPC_ReceiveZenTreasurePhotoReadClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param2<ItemBase, int> data;
        if (!ctx.Read(data))
        {
            Error("[ZenTreasure] Error sync'ing server-side data to client - RPC_ReceiveZenTreasurePhotoReadClient");
            return;
        }

		ZenTreasure_PhotoBase photo = ZenTreasure_PhotoBase.Cast(data.param1);
		if (!photo)
			return;

		if (data.param2 != -1) // First time reading if this is -1
			photo.SetStashType(data.param2);
		
		ZenOpenPhotoInspect(photo);
    }

	// TODO: Find a way to move this code to item OnRPC instead of MissionBase?
	void ZenOpenPhotoInspect(notnull ZenTreasure_PhotoBase photo)
	{
		if (GetGame().GetUIManager().GetMenu() != NULL)
			return;

		MissionGameplay missionGP = MissionGameplay.Cast(GetGame().GetMission());
		if (!missionGP)
			return;

		missionGP.ShowInventory();

		InventoryMenu inventory_menu = InventoryMenu.Cast(GetGame().GetUIManager().FindMenu(MENU_INVENTORY));
		if (!inventory_menu)
			return;

		InspectMenuNew inspect_menu = InspectMenuNew.Cast(inventory_menu.EnterScriptedMenu(MENU_INSPECT));
		if (inspect_menu)
		{
			GetGame().GetMission().GetHud().ShowHudUI(false);
			GetGame().GetMission().GetHud().ShowQuickbarUI(false);
			inspect_menu.SetItem(photo);
		}
	}
}