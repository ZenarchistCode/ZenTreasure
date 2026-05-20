modded class PluginManager
{
	override void Init()
	{
		super.Init();

		RegisterPlugin("PluginZenTreasureTriggerManager", false, true);
	}
}
