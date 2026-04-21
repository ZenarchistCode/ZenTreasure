modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		#ifdef ZenModPack
		if (!ZenModEnabled("ZenTreasure"))
			return;
		#endif

		GetZenTreasureConfig();
		GetZenTreasure_Triggers().SpawnStartupTriggers();

		// Add map markers for debugging map treasure positions
		if (GetZenTreasureConfig().DebugZenMapCompatibility)
		{
			#ifdef ZenMap
			PluginZenMapMarkers mapPlugin = PluginZenMapMarkers.Cast(GetPlugin(PluginZenMapMarkers));
			if (!mapPlugin)
			{
				Error("[ZenTreasure Debug] Map plugin doesn't exist!");
				return;
			}

			float x, z;
			vector buryPos = vector.Zero;
			string cfg_path;
			string cfg_name = "";
			string mapName;
			string thisMapName = g_Game.GetWorldName();
			thisMapName.ToLower();

			for (int i = 0; i < g_Game.ConfigGetChildrenCount("CfgVehicles"); i++)
			{
				g_Game.ConfigGetChildName("CfgVehicles", i, cfg_name);
				if (cfg_name.Contains("ZenTreasure_Photo") && !cfg_name.Contains("Base"))
				{
					cfg_path = "CfgVehicles " + cfg_name;

					g_Game.ConfigGetText(cfg_path + " mapName", mapName);
					mapName.ToLower();

					if (mapName != "missing")
					{
						if (mapName != thisMapName)
							continue;
					}
					
					ZenTreasureLocation loc;
					if (GetZenTreasureConfig().TreasureLocationOverrides.Find(cfg_name, loc))
					{
						x = loc.StashX;
						z = loc.StashZ;
					}
					else 
					{
						x = g_Game.ConfigGetFloat(cfg_path + " treasure_stash_x");
						z = g_Game.ConfigGetFloat(cfg_path + " treasure_stash_z");
					}
					
					buryPos[0] = x;
					buryPos[1] = 0;
					buryPos[2] = z;

					mapPlugin.AddMarker(new MapMarker(buryPos, cfg_name, -65536, GetZenMapConfig().FileToArrayIndex("ZenMap/data/icons/shovel.paa")));
				}
			}
			#endif
		}
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);

		#ifdef ZenModPack
		if (!ZenModEnabled("ZenTreasure"))
			return;
		#endif

		SendZenTreasureConfig(player, identity);
	}

	void SendZenTreasureConfig(PlayerBase player, PlayerIdentity identity)
	{
		array<string> m_treasureDescriptions = new array<string>;
		foreach(ZenTreasureStashType treasure : GetZenTreasureConfig().TreasureTypes)
		{
			m_treasureDescriptions.Insert(treasure.Description);
		}

		GetRPCManager().SendRPC("ZenMod_RPC", "RPC_ReceiveZenTreasureTextClient", new Param1<array<string>>(m_treasureDescriptions), true, player.GetIdentity());
	}
}