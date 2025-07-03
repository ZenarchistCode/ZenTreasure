class ZenRandomAmmoBox : Box_Base
{
	array<string> GetAmmoBoxes()
	{
		array<string> ammoBoxes = new array<string>;

		ammoBoxes.Insert("AmmoBox_00buck_10rnd");
		ammoBoxes.Insert("AmmoBox_12gaSlug_10Rnd");
		ammoBoxes.Insert("AmmoBox_22_50Rnd");
		ammoBoxes.Insert("AmmoBox_308Win_20Rnd");
		ammoBoxes.Insert("AmmoBox_308WinTracer_20Rnd");
		ammoBoxes.Insert("AmmoBox_357_20Rnd");
		ammoBoxes.Insert("AmmoBox_380_35rnd");
		ammoBoxes.Insert("AmmoBox_45ACP_25rnd");
		ammoBoxes.Insert("AmmoBox_545x39_20Rnd");
		ammoBoxes.Insert("AmmoBox_545x39Tracer_20Rnd");
		ammoBoxes.Insert("AmmoBox_556x45_20Rnd");
		ammoBoxes.Insert("AmmoBox_556x45Tracer_20Rnd");
		ammoBoxes.Insert("AmmoBox_762x39_20Rnd");
		ammoBoxes.Insert("AmmoBox_762x39Tracer_20Rnd");
		ammoBoxes.Insert("AmmoBox_762x54_20Rnd");
		ammoBoxes.Insert("AmmoBox_762x54Tracer_20Rnd");
		ammoBoxes.Insert("AmmoBox_9x19_25rnd");
		ammoBoxes.Insert("AmmoBox_9x39_20Rnd");
		ammoBoxes.Insert("AmmoBox_9x39AP_20Rnd");

		return ammoBoxes;
	}

	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);

		if (GetGame().IsDedicatedServer())
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ShapeshifterMorph, Math.RandomFloatInclusive(900, 1000), false);
	}

	private void ShapeshifterMorph()
	{
		GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, new ReplaceItemWithNewLambda(this, GetAmmoBoxes().GetRandomElement(), NULL));
	}
}

class ReplaceRandomAmmoLambda : ReplaceItemWithNewLambdaBase
{
	void ReplaceRandomAmmoLambda(EntityAI old_item, string new_item_type)
	{
		m_OldItem = old_item;
		m_NewItemType = new_item_type;
	}
}