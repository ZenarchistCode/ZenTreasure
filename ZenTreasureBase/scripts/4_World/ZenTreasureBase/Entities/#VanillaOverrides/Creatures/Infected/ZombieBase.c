modded class ZombieBase extends DayZInfected
{
	protected bool m_ZenTreasureHasInit = false;

	// Called when zombie is created
	override void DeferredInit()
	{
		super.DeferredInit();

		if (!g_Game.IsDedicatedServer())
		{
			return;
		}

		#ifdef ZenModPack
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
		ZenTreasure_PhotoBase photo = ZenTreasure_PhotoBase.Cast(GetInventory().CreateInInventory(photoType));
		if (!photo)
		{
			Error("[ZenTreasure] Failed to spawn photo '" + photoType + "' on zombie. Make sure classname exists. Check PhotoSpawnStartNumber & PhotoSpawnStopNumber range is valid.");
		}
	}
}