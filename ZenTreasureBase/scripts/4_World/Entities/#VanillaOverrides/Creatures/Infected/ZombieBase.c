modded class ZombieBase extends DayZInfected
{
	protected bool m_ZenTreasureHasInit = false;

	// Called when zombie is created
	override void DeferredInit()
	{
		super.DeferredInit();

		if (!GetGame().IsDedicatedServer())
		{
			return;
		}

		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenTreasure"))
		{
			return;
		}
		#endif

		if (GetZenTreasureConfig().SpawnPhotosOnZombiesChance <= 0)
		{
			return;
		}

		if (m_ZenTreasureHasInit)
		{
			return;
		}

		m_ZenTreasureHasInit = true;

		if (Math.RandomFloat01() >= GetZenTreasureConfig().SpawnPhotosOnZombiesChance)
		{
			return;
		}

		string photoType = "ZenTreasure_RandomPhoto";

		if (GetZenTreasureConfig().PhotoSpawnStartNumber != 0 && GetZenTreasureConfig().PhotoSpawnStopNumber != 0)
		{
			string id = "";
			int photoID = Math.RandomIntInclusive(GetZenTreasureConfig().PhotoSpawnStartNumber, GetZenTreasureConfig().PhotoSpawnStopNumber);
			id = photoID.ToString();
			if (photoID <= 9)
				id = "0" + id;

			photoType = "ZenTreasure_Photo" + id;
		}

		ZenTreasure_PhotoBase photo = ZenTreasure_PhotoBase.Cast(GetInventory().CreateInInventory(photoType));
		if (!photo)
		{
			Error("[ZenTreasure] Failed to spawn photo '" + photoType + "' on zombie. Make sure classname exists. Check PhotoSpawnStartNumber & PhotoSpawnStopNumber range is valid.");
		}
	}
}