/*
On my server, players were repeatedly farming the treasure locations once they learned of each spot.
This config ensures the treasure only spawns when a player who has read a treasure photo enters the area.
*/
ref ZenTreasureDB g_ZenTreasureDB;

static ZenTreasureDB GetZenTreasureDB()
{
	if (!g_ZenTreasureDB) GetZenConfigRegister().RegisterConfig(ZenTreasureDB);
	return g_ZenTreasureDB;
}

modded class ZenConfigRegister
{
	override void RegisterPreload()
	{
		super.RegisterPreload();
		RegisterType(ZenTreasureDB);
	}
}

class ZenTreasureDB: ZenConfigBase
{
	// -------------------------
	// CONFIG SETTINGS
	// -------------------------
	override void OnRegistered()
	{
		g_ZenTreasureDB = this;
	}
	
	override string 	GetRootFolder() 			{ return ZenConstants.GetDbFolder(); }
	override string    	GetCurrentVersion()   		{ return "1.29.1"; }
	override bool		ShouldLoadOnServer() 		{ return true; }
	override bool 		IsServerOnlyConfig()		{ return true; }
	
	override bool ReadJson(string path, out string err)
	{
		return JsonFileLoader<ZenTreasureDB>.LoadFile(path, this, err);
	}

	override bool WriteJson(string path, out string err)
	{
		return JsonFileLoader<ZenTreasureDB>.SaveFile(path, this, err);
	}

	// -------------------------
	// CONFIG VARS
	// -------------------------
	ref array<ref ZenTreasureTriggerConfig> TreasureTriggers = new array<ref ZenTreasureTriggerConfig>;

	ZenTreasureTriggerConfig AddTreasureTrigger(vector position, string playerID, int stashType)
	{
		for (int i = 0; i < TreasureTriggers.Count(); i++)
		{
			ZenTreasureTriggerConfig cfg = TreasureTriggers.Get(i);
			if (vector.Distance(position, cfg.Position) < 1)
			{
				for (int x = 0; x < cfg.TreasureHunters.Count(); x++)
				{
					ZenTreasureHunter hunter = cfg.TreasureHunters.Get(x);
					if (hunter.ZenPlayerID == playerID)
					{
						cfg.TreasureHunters.Get(x).ZenTimestamp = CF_Date.Now().GetTimestamp();
						cfg.TreasureHunters.Get(x).ZenStashID = stashType;
						Save();

						return cfg;
					}
				}

				cfg.TreasureHunters.Insert(new ZenTreasureHunter(stashType, playerID));
				Save();

				return cfg;
			}
		}

		// Trigger not found - create it
		ZenTreasureTriggerConfig newCfg = new ZenTreasureTriggerConfig(position, playerID, stashType);
		TreasureTriggers.Insert(newCfg);
		Save();

		return newCfg;
	}

	void ClearOutdatedTriggers()
	{
		int timestamp = CF_Date.Now().GetTimestamp();
		ZenTreasureTriggerConfig cfg;

		for (int i = 0; i < TreasureTriggers.Count(); i++)
		{
			cfg = TreasureTriggers.Get(i);
			for (int x = cfg.TreasureHunters.Count() - 1; x >= 0; x--)
			{
				ZenTreasureHunter hunter = cfg.TreasureHunters.Get(x);
				if (hunter.ZenTimestamp == 0 || (timestamp - hunter.ZenTimestamp > GetZenTreasureConfig().TreasureTriggerPersistenceSecs) || hunter.ZenPlayerID == "")
				{
					cfg.TreasureHunters.Remove(x);
				}
			}
		}

		Save();
	}
}

// Define a stash trigger (save stash position, type, player ID and timestamp)
class ZenTreasureTriggerConfig
{
	vector Position;
	ref array<ref ZenTreasureHunter> TreasureHunters = new array<ref ZenTreasureHunter>;

	void ZenTreasureTriggerConfig(vector p_stashPos, string p_id, int p_type)
	{
		Position = p_stashPos;
		AddTreasureHunter(p_id, p_type);
	}

	void AddTreasureHunter(string p_id, int p_type)
	{
		int timestamp = CF_Date.Now().GetTimestamp();

		for (int i = 0; i < TreasureHunters.Count(); i++)
		{
			ZenTreasureHunter hunter = TreasureHunters.Get(i);
			if (hunter.ZenPlayerID == p_id)
			{
				hunter.ZenStashID = p_type;
				hunter.ZenTimestamp = timestamp;
				return;
			}
		}

		TreasureHunters.Insert(new ZenTreasureHunter(p_type, p_id));
	}
}

class ZenTreasureHunter
{
	string ZenPlayerID;
	int ZenStashID;
	int ZenTimestamp;

	void ZenTreasureHunter(int p_type, string p_id)
	{
		ZenStashID = p_type;
		ZenPlayerID = p_id;
		ZenTimestamp = CF_Date.Now().GetTimestamp();
	}
}
