class ZenTreasure_PhotoBase extends ItemBase
{
	static const int ZEN_TREASUREID_RPC_RESPONSE = -34827419;
	static const int ZEN_TREASUREID_RPC_REQUEST = -34827418;

	protected int m_ZenStashType = -1;
	protected vector m_StashPosition;
	protected string m_StashCreatorID;
	protected bool m_ZenCanReadPhoto;

	// Called when Central Economy engine spawns this item into the world as loot
	override void EEOnCECreate()
	{
		super.EEOnCECreate();

		// This makes it so you don't gotta set cfgspawnabletypes.xml to spawn photos Pristine.
		// The photos are impossible to see once damaged, so let's always spawn them Pristine.
		// If they get damaged by zombies/combat/etc later.. well, tough luck survivor.
		SetHealth(GetMaxHealth());
	}

	void ZenTreasure_PhotoBase()
	{
		RegisterNetSyncVariableInt("m_ZenStashType");

		m_ZenCanReadPhoto = false;
		SetStashCreatorID("");

		// Get photo number for texture purposes (remove 'ZenTreasure_Photo' to get number text only)
		string className = GetType();
		string substringNumber = className.Substring(17, className.Length() - 17);
		int photoNumber = substringNumber.ToInt();
		if (photoNumber < 10)
			substringNumber = "0" + photoNumber.ToString();
		else
			substringNumber = photoNumber.ToString();

		// Assign texture
		AsssignPhotoTexture(substringNumber);
	}

	void SetZenCanRead(bool b)
	{
		m_ZenCanReadPhoto = b;
	}

	override void DeferredInit()
	{
		super.DeferredInit();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ZenCheckReadableRPC, 1000, false);
	}

	void ZenCheckReadableRPC()
	{
		if (GetGame().IsClient())
		{
			// Request RPC to tell if this player found the stash 
			RPCSingleParam(ZEN_TREASUREID_RPC_REQUEST, new Param1<bool>(true), true, NULL);
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		// Server-side receiver
		if (rpc_type == ZEN_TREASUREID_RPC_REQUEST)
		{
			bool canRead = false;

			if (sender.GetPlainId() == m_StashCreatorID || m_StashCreatorID == "")
			{
				canRead = true;
			}

			RPCSingleParam(ZEN_TREASUREID_RPC_RESPONSE, new Param1<bool>(canRead), true, sender);
		}

		// Client-side receiver
		if (rpc_type == ZEN_TREASUREID_RPC_RESPONSE)
		{
			Param1<bool> params;

			if (!ctx.Read(params) || !params.param1)
				return;

			m_ZenCanReadPhoto = params.param1;
		}
	}

	void AsssignPhotoTexture(string photoNumber)
	{
		if (IsWinterPhoto())
		{
			if (GetHiddenSelectionsTextures().Count() > 0)
				SetObjectTexture(0, GetHiddenSelectionsTextures().Get(1));
			else 
				SetObjectTexture(0, "ZenTreasurePhotos/data/photos/photo" + photoNumber + "_winter.paa");
		}
		else 
		{
			if (GetHiddenSelectionsTextures().Count() > 0)
				SetObjectTexture(0, GetHiddenSelectionsTextures().Get(0));
			else 
				SetObjectTexture(0, "ZenTreasurePhotos/data/photos/photo" + photoNumber + ".paa");
		}
	}

	void AssignRandomStashType()
	{
		if (m_ZenStashType != -1)
			return;

		// Assign a random loot type to this photo
		if (GetZenTreasureConfig().DebugAlwaysSpawnStashID == -1)
			m_ZenStashType = Math.RandomIntInclusive(0, GetZenTreasureConfig().TreasureTypes.Count() - 1);
		else 
			m_ZenStashType = GetZenTreasureConfig().DebugAlwaysSpawnStashID;

		SetSynchDirty();
	}

	override void EEInit()
	{
		super.EEInit();

		m_StashPosition = GetBuryPosition();
	}

	static bool IsWinterPhoto()
	{
		return GetZenTreasureConfig().IsWinterMap;
	}

	override bool DescriptionOverride(out string output)
	{
		if (!m_ZenCanReadPhoto)
		{
			output = "#STR_ZenTreasure_CantRead";
		}
		else 
		{
			string cfgPath = "CfgVehicles ZenTreasure_PhotoBase";
			string treasureTypeText = "";

			if (SpawnedStash())
			{
				cfgPath = "CfgVehicles " + GetType();
				treasureTypeText = ZenTreasureConfig.TreasureDescriptions.Get(m_ZenStashType);
			}

			GetGame().ConfigGetText(cfgPath + " descriptionShort", output);
			output.Replace("TREASURETYPE", treasureTypeText);
		}
		
		return true;
	}

	// Get bury location from *.cpp file config
	vector GetBuryPosition()
	{
		string cfgPath = "CfgVehicles " + GetType();

		float x = GetGame().ConfigGetFloat(cfgPath + " treasure_stash_x");
		float y = GetGame().ConfigGetFloat(cfgPath + " treasure_stash_z");
		float z = GetGame().SurfaceY(x, y);

		vector buryPos = vector.Zero;
		buryPos[0] = x;
		buryPos[1] = z;
		buryPos[2] = y;

		return buryPos;
	}

	string GetStashCreatorID()
	{
		return m_StashCreatorID;
	}

	void SetStashCreatorID(string id)
	{
		m_StashCreatorID = id;
	}

	int GetStashType()
	{
		return m_ZenStashType;
	}

	void SetStashType(int type)
	{
		m_ZenStashType = type;
		SetSynchDirty();
	}

	bool SpawnedStash()
	{
		return m_ZenStashType != -1;
	}

	void SpawnStash(PlayerBase player)
	{
		AssignRandomStashType();

		// Spawn stash!
		SpawnTreasureTrigger(player);

		// Debug teleport?
		if (GetZenTreasureConfig().DebugTeleportToPhoto)
		{
			DeveloperTeleport.SetPlayerPosition(player, m_StashPosition);
		}
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenReadPhoto);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_ZenStashType))
			return false;

		if (!ctx.Read(m_StashCreatorID))
			return false;

		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_ZenStashType);
		ctx.Write(m_StashCreatorID);
	}

	void PhotoDebugPrint(string msg)
	{
		msg = "[ZenTreasure Debug] " + msg;
		Print(msg);
	}

	void SpawnTreasureTrigger(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
		{
			Error("[ZenTreasure] Treasure stashed was spawned with no valid Player responsible for it!");
			return;
		}

		ZenTreasureStashType treasureConfig = GetZenTreasureConfig().TreasureTypes.Get(m_ZenStashType);
		if (!treasureConfig)
		{
			Error("[ZenTreasure] Could not spawn treasure loot trigger - config not found for m_ZenStashType=" + m_ZenStashType);
			return;
		}

		GetZenTreasure_Triggers().SpawnTrigger(GetZenTreasureConfig_SpawnTriggers().AddTreasureTrigger(m_StashPosition, player.GetCachedID(), m_ZenStashType), player);
		Print("[ZenTreasure] " + player.GetCachedID() + " spawned treasure stash TRIGGER @ " + m_StashPosition + " with config " + treasureConfig.ConfigName);
	
		m_StashCreatorID = player.GetIdentity().GetPlainId();
		RPCSingleParam(ZEN_TREASUREID_RPC_RESPONSE, new Param1<bool>(true), true, player.GetIdentity());
	}

	#ifdef MAPLINK
	override void OnUApiSave(UApiEntityStore data)
	{
		super.OnUApiSave(data);

		data.Write("m_ZenStashType", GetStashType());
		data.Write("m_StashCreatorID", GetStashCreatorID());
		Print("[ZenTreasure_PhotoBase::MapLink] Saving photo - stash ID: " + GetStashType());
	}
	
	override void OnUApiLoad(UApiEntityStore data)
	{
		super.OnUApiLoad(data);
		
		SetStashType(data.GetInt("m_ZenStashType"));
		Print("[ZenTreasure_PhotoBase::MapLink] Loaded photo - stash ID: " + GetStashType());
	}
	#endif
}