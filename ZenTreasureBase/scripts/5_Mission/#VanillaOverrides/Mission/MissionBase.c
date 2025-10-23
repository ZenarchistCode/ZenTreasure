modded class MissionBase
{
	//! SHARED 
	void MissionBase()
	{
		#ifndef SERVER
		//! TREASURE CLIENT
		GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenTreasureTextClient", this, SingeplayerExecutionType.Client);
		GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenTreasurePhotoReadClient", this, SingeplayerExecutionType.Client);
        #else
		//! TREASURE SERVER
		Print("[ZenTreasure] Loading random photo types:");

		string cfg_name;
		string map_name;
		int photoID = 0;

		// Load how many photos exist for RandomPhoto spawner
		for (int i = 0; i < GetGame().ConfigGetChildrenCount("CfgVehicles"); i++)
		{
			GetGame().ConfigGetChildName("CfgVehicles", i, cfg_name);
			if (cfg_name.Contains("ZenTreasure_Photo") && !cfg_name.Contains("Base"))
			{
				photoID++;
				//Print("[ZenTreasure] Valid photo detected: " + cfg_name + " / ID=" + photoID);

				if (GetGame().ConfigIsExisting("CfgVehicles " + cfg_name + " mapName"))
				{
					GetGame().ConfigGetText("CfgVehicles " + cfg_name + " mapName", map_name);
				}
				else 
				{
					map_name = "";
				}

				if (GetZenTreasureConfig().SkipSpawnableRandomPhotosID && GetZenTreasureConfig().SkipSpawnableRandomPhotosID.Find(photoID) != -1)
				{
					Print("[ZenTreasure] SKIPPING PHOTO ID: " + photoID);
					continue;
				}

				if (GetZenTreasureConfig().SkipSpawnableRandomPhotosMap && GetZenTreasureConfig().SkipSpawnableRandomPhotosMap.Find(map_name) != -1)
				{
					Print("[ZenTreasure] SKIPPING PHOTO ID: " + photoID + " (Map=" + map_name + ")");
					continue;
				}

				ZenTreasure_RandomPhoto.ALLOWED_PHOTO_IDS.Insert(photoID);
			}
		}

		Print("[ZenTreasure] Loaded " + ZenTreasure_RandomPhoto.ALLOWED_PHOTO_IDS.Count() + " random photo types.");
		#endif
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

		if (data.param2 != -1)
		{
			photo.SetZenCanRead(true);
			photo.SetStashType(data.param2);
		}

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