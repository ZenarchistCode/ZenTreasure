class CfgPatches
{
	class ZenTreasurePhotos
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"ZenTreasureBase"
		};
	};
};

// Define photographs & textures
class CfgVehicles
{
	//! DEFINE PHOTO DESCRIPTIONS & LOCATIONS (textures are automatically applied in ZenTreasure_PhotoBase.c based on photo #)
	//! Always modify and re-pack this mod if you want to add new photos, and either edit my existing Livonia photo config 
	//! to suit your map, or add new photos after my custom photo config.
	class ZenTreasure_PhotoBase;

	//! LIVONIA PHOTO CONFIG:
	class ZenTreasure_Photo01 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "If you're reading this, then I'm dead. I buried some TREASURETYPE supplies under a pile of tires near the power plant east of Karlin. There's an old caravan right next to the pile of tires. Take care survivor. I hope you have better luck than I did.";
		treasure_stash_x = 11579; // Karlin power plant
		treasure_stash_z = 6940;
	};
	class ZenTreasure_Photo02 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Sergio my friend, I hope you find this before someone else does. Last night we were ambushed near Sitnik. I managed to survive and kill our attacker, but I was wounded pretty badly. I couldn't carry everything the other survivor had on him, so I buried it. If you walk to the place where the train tracks split off to the Sitnik industrial area you'll find a stash of TREASURETYPE supplies buried nearby in the treeline of the hill. It's well worth the trek my friend.";
		treasure_stash_x = 10935; // Sitnik train cross intersection
		treasure_stash_z = 9490;
	};
	class ZenTreasure_Photo03 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Michal, do you remember this girl in the picture? She could drive her Ada like a devil! Better than you drove anyway. I was with her when it all first broke out, we were 'social distancing' together if you know what I mean. We buried some TREASURETYPE supplies not far from her house in Wrzeszcz. When the situation calms down a little, we should go back and pick it up. It's just beyond that outhouse near some old ruins.";
		treasure_stash_x = 8891; // Wrzcczczc
		treasure_stash_z = 4464;
	};
	class ZenTreasure_Photo04 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Before this all started I was on a pub crawl with some friends. We took this photo the night before the world turned to hell. I thought Shaun of the Living Dead was a parody film, not a documentary... If you find this photo it means me and my friends are probably dead, so we won't have any use for the TREASURETYPE supply stash we buried near the garbage bins at Lawenda Summer Camp. I hope you have better luck than we did.";
		treasure_stash_x = 782; // Lawenda Summer Camp
		treasure_stash_z = 8622;
	};
	class ZenTreasure_Photo05 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "My dearest Aleksy, I didn't want to wake you as I know how hard it has been for you to sleep since you got sick. I'm going to search for more supplies, if I'm not back in a few days I buried a TREASURETYPE stash for you near two dead trees on my way out of Dolnik. The trees are next to an old trailer on the main road. I'm going to look for more supplies up north, and if I find anything worthwhile I'll come straight home. If I don't see you again, I'm so sorry. I love you more than you know ~ Your Natasha";
		treasure_stash_x = 11031; // Dolnik trees
		treasure_stash_z = 1588;
	};
	class ZenTreasure_Photo06 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I've tried all I can to stay alive, but sickness is creeping into my very bones. I suspect I have sepsis, but I'm too weak to find medicine. If you find this photo, leaving this note on the back was the last thing I did before resting inside this cabin near Lukow. I buried some TREASURETYPE gear in between the wooden campfire benches there. Good luck to you, stranger.";
		treasure_stash_x = 4335; // Cabin Near Lukow
		treasure_stash_z = 12412;
	};
	class ZenTreasure_Photo07 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I thought I was brave. I joined the United Nations as soon as I finished my basic training, ready to take on the infected. But I was wrong, I'm not brave. I'm fucking terrified. Shortly after this photo was taken I ran for the forest and I don't plan to ever return to civilization. I'm going to live out the rest of my days in the mountains, and pray that I never see another infected. I buried all of the UN TREASURETYPE supplies I had under a tree on the northern side of a small pond to the north-east of Lukow. Good luck whoever finds this, you're going to need it.";
		treasure_stash_x = 3673; // Lukow pond
		treasure_stash_z = 12560;
	};
	class ZenTreasure_Photo08 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Well, it finally happened. I spent 20 years learning to live off the land in preparation for doomsday. Now I'm ready. The only problem is I forgot where I buried half of my TREASURETYPE supplies. I buried them in various places to keep them hidden from the government who would surely confiscate them. I found most of my stashes, but there's one I can't find. This photo was taken by a friend of mine when I was exploring the castle ruins near the Branzow military base. I remember burying something between a tree stump and some large rocks, next to some ruins. Maybe you can find it, fellow survivor. - Igor";
		treasure_stash_x = 1360; // Branzow ruins
		treasure_stash_z = 11311;
	};
	class ZenTreasure_Photo09 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I hope you do better than I and my family did. We've been sheltered in Polana for weeks, but no help is coming. I've decided to commit suicide. I only have 3 bullets left - one for my wife, two for my children. Once they are dead I'll climb the evac tower on the hill and jump to my death. My wife took this photo of me fishing a few days before this hell began, at a lake north-east of our home in Polana. I buried all of my TREASURETYPE equipment there. You'll need to follow the dry creek bed that leads south-west into the mountains, I buried a stash under a tree there next to a dead log. Good luck. - David";
		treasure_stash_x = 4213; // Polana lake
		treasure_stash_z = 2915;
	};
	class ZenTreasure_Photo10 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Wow, I was wasted last night. I went to a party in an apartment in Topolin and things got pretty crazy. Once the ecstasy wore off the next morning someone took this photo of me. I don't know where my shoes went, but I remember burying them somewhere. I also remember burying a crate full of TREASURETYPE supplies that I stole from a store in town. Apparently some sort of virus is spreading throughout Livonia so I'm not sure if I'll get a chance to go and check. But I think I buried the crate near a tree surrounded by rubbish behind the police station.";
		treasure_stash_x = 1471; // Topolin police station
		treasure_stash_z = 7361;
	};
	class ZenTreasure_Photo11 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Peter, I must be quick. While we were fortifying the old castle ruins south-east of Swarog we were ambushed. I was the only one who managed to escape. You'll remember the castle from this photo. I buried as many supplies as I could carry, hopefully you can recover them before someone finds our TREASURETYPE stash. I buried it between two rocks in a small cluster of trees east of the castle, past the destroyed BMD. Good luck my friend, I hope to see you again soon but for now I must hide. - Alexei (Castle Coordinates: 6921.88 / 1146.87)";
		treasure_stash_x = 6980; // Southern castle
		treasure_stash_z = 1144;
	};
	class ZenTreasure_Photo12 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I remember when I first heard the news about the infected breaking out of quarantine and attacking locals. I was leading my group of scouts on a hike through the castle ruins north of Grabin. The news rattled me and I didn't know what to do. I had to get the kids back to their families, but I also had a lot of excess TREASURETYPE supplies on me at the time. I decided to bury most of them in a memorable location. I buried a stash next to a large rock and a small group of trees on the hill near Sowa castle. If I don't find them, maybe you will.";
		treasure_stash_x = 11503; // Grabin castle
		treasure_stash_z = 11906;
	};
	class ZenTreasure_Photo13 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Hello survivor. If you found this old photo, perhaps you can recover our doomsday stash too. When the virus outbreak began my family buried a stash of TREASURETYPE gear beneath a treehouse on a remote island in the north-east of Livonia situated in the middle of a large lake. We're unable to return to it and have made plans to leave Livonia. The stash is well worth your time to hunt down if you dare. Good luck, stranger.";
		treasure_stash_x = 12351; // NE lake treehouse
		treasure_stash_z = 10886;
	};
	class ZenTreasure_Photo14 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The revolution never came. But the downfall did. We always knew these capitalist pigs would destroy the world someday, but we never imagined it would be due to a virus born out of their greed and abuse of scientific endeavour. My group are leaving Livonia for fresher pastures. We're leaving behind our TREASURETYPE stash, you'll find it buried between two giant spools in the factory perimiter north of Sitnik. Good luck, unknown comrade.";
		treasure_stash_x = 11766; // Factory north sitnik
		treasure_stash_z = 10768;
	};
	class ZenTreasure_Photo15 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The taste of human flesh is unparalleled. Before the apocalypse I would have never dreamed of eating human meat. But things have changed. Only the strong survive now. And what is more powerful than consuming the flesh of the most apex of predators on earth? Nothing. They call us a cult, but that's because they don't understand divine genius. We have accumulated riches and power the likes of which the common man could never achieve. I've buried some of this treasure just for fun. In a cluster of bushes near the Stone Circle north-east of Dolnik you will find one such TREASURETYPE stash. I promise, it's not a trap. - Josef the Cannibal";
		treasure_stash_x = 12126; // Stone circle
		treasure_stash_z = 1729;
	};
	class ZenTreasure_Photo16 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Blessed are the meek, for they shall inherit the earth. And blessed are the strong, for they shall eat the meek. Hahaha... we do love the taste of human flesh. And everybody knows the most tender meat is that which has not been... over-used. If you share our.. good taste, then you're welcome to our southern TREASURETYPE stash. Consider it a gift for the brave. It is buried between two trees where deer come to die, on the outskirts of the contaminated zone. Don't suffer for too long, stranger. It spoils the meat. (Approx Coordinates: 7661.52 / 2321.09)";
		treasure_stash_x = 7695; // Deer grave
		treasure_stash_z = 2285;
	};
	class ZenTreasure_Photo17 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I'm leaving this place. I've lived in solitude for 15 years, but since this outbreak I've had to kill far too many trespassers looking for shelter in my home. Survival was exhausting before the outbreak - now it's intolerable. I'm setting out for Chernarus. I hear things are better there. Fewer survivors, which means fewer scavengers to worry about. In the meantime... if you find this photo, you're welcome to my TREASURETYPE stash. It's buried behind a deer feeder stand near my old house, far to the west of Livonia, in the woods just south of Zalesie.";
		treasure_stash_x = 675; // Western hermit house near Zalesie
		treasure_stash_z = 4397;
	};
	class ZenTreasure_Photo18 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Once a frogman, always a frogman. BUDS might not have prepared us for zombies, but what kills living bad guys kills undead bad guys, too. We've been thriving down here in the south. Far fewer survivors means far more game to hunt. We've collected more gear than we'll ever need, so we buried a stash of TREASURETYPE gear beneath the radar tower at Dambog military outpost - if you find this photo, you're welcome to it. Good luck survivor. I'd say see you later, but you'll never see us!";
		treasure_stash_x = 542; // Dambog radar tower
		treasure_stash_z = 1119;
	};
	class ZenTreasure_Photo19 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "SEALs never reveal their secrets. But we're not a greedy bunch, we only take what we need. So in this case I'll make an exception. There's a secret stash buried in the north, near Jantar Lake. It's a cache of TREASURETYPE supplies. You'll find it underneath the treehouse built on the huge dead tree there. Good luck, civilian. You'll need it out here.";
		treasure_stash_x = 3376; // Jantar lake with treehouse
		treasure_stash_z = 8913;
	};
	class ZenTreasure_Photo20 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "More than half of the town is already infected. The healthy either fled to the woods or are barricaded in houses. It's getting worse, I don't think there will be any help. Looks like it's time for me to head out into the wild and try my luck out there. If I don't survive, the least I can try to do is leave something behind for those who do somehow survive this madness. I buried some spare TREASURETYPE supplies in the bushes near my old green house by the fire station in Topolin. If you find this photograph, well, good luck my friend. Maybe we'll meet someday. Maybe.";
		treasure_stash_x = 1628; // Topolin red house
		treasure_stash_z = 7388;
	};
	class ZenTreasure_Photo21 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Before I left the army, my last exercise was just near the shooting range in Wrzeszcz. Even then, there were rumours about an unknown infection. That's why I stole some TREASURETYPE gear and a few other useful things from the supply cache, despite the threat of being court-martialed. I buried what I could fit in a stash towards the back of the shooting range. I hear it has since become an evacuation point so I imagine it's pretty hard to get to now. Good luck, whoever finds this message.";
		treasure_stash_x = 9948; // Shooting range
		treasure_stash_z = 3954;
	};
	class ZenTreasure_Photo22 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Looks like the shit has finally hit the fan. They're shutting down the quarry and evacuating all of us out of Livonia. I don't know what's going to happen, but I'm not waiting around to find out. I've stolen as much gear as possible from the surrounding towns of Nadbor. Just in case our evacuation plans don't pan out like the big wigs say it will, I've buried a TREASURETYPE stash inside the Nadbor quarry near the water. If you find this message it means we got out of Livonia alive. Feel free to take the stash for yourself and good luck out there.";
		treasure_stash_x = 6996; // Quarry near nadbor
		treasure_stash_z = 4583;
	};
	class ZenTreasure_Photo23 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "My friend, I can go on no longer. I'm afraid I've reached my wits' end. I'm 83 years old and I realize how difficult it has been to keep me alive, and I've been slowing down the group for too long. I'm tired. I'm in constant pain. The travel has worn me down. I've decided to end my life. I'm going to where we first met, by the abandoned quarry north of Dambog. It was beautiful there. You'll find a dead tree next to a large boulder - that is where you'll find my final belongings, a stash of TREASURETYPE supplies. Good luck my friend. Thanks for all you have done. - Jim";
		treasure_stash_x = 682; // North dambog quarry
		treasure_stash_z = 2401;
	};
	class ZenTreasure_Photo24 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I'm getting the fuuuck outa here! I don't do zombies man. No sir. Thank god I finished my pilot training a month ago or I'd be shitting bricks right now. I'm taking this MH6 and a one-way ticket to Chernarus. I hear things are better there. They better be. I left a TREASURETYPE stash buried under the radar tower at the Lukow airfield. Whoever wants it can have it. I'm gone. Ciao motherfuckers, and good luck!!";
		treasure_stash_x = 4015; // Airfield
		treasure_stash_z = 10296;
	};
	class ZenTreasure_Photo25 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Verily, my trusty blade proves futile against these foul undead fiends! Methinks my prowess in the art of live action roleplay avails me naught in this dire hour. 'Tis prudent that I depart this accursed place and seek refuge amidst those skilled in true combat. I shall conceal my TREASURETYPE belongings by the forsaken well near yonder castle in the Eastern realm of Livonia. Whosoever chances upon it, mayhaps they shall find strength to lay siege to this land with valor and fortitude.";
		treasure_stash_x = 11880; // Eastern castle
		treasure_stash_z = 6579;
	};
};