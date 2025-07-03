class CfgPatches
{
	class ZenTreasurePhotos
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
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

	// This is for optional compatibility with MapLink Hive mod. If player finds a photo on the wrong map, 
	// then they need to travel there to find the treasure and reading the photo will just produce this wrong 
	// map message.
	class ZenTreasure_Enoch
	{
		wrongMapText = "This photo looks like it was taken in Livonia... I should travel there before I look for this treasure.";
	};
	class ZenTreasure_ChernarusPlus
	{
		wrongMapText = "This photo looks like it was taken in Chernarus... I should travel there before I look for this treasure.";
	};
	class ZenTreasure_Sakhal
	{
		wrongMapText = "This photo looks like it was taken in Sakhal... I should travel there before I look for this treasure.";
	};

	//! LIVONIA PHOTO CONFIG:
	class ZenTreasure_Photo01 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "If you're reading this, then I'm dead. I buried some TREASURETYPE supplies under a pile of tires near the power plant east of Karlin. There's an old caravan right next to the pile of tires. Take care survivor. I hope you have better luck than I did.";
		treasure_stash_x = 11579; // Karlin power plant
		treasure_stash_z = 6940;
		mapName = "enoch";
	};
	class ZenTreasure_Photo02 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Sergio my friend, I hope you find this before someone else does. Last night we were ambushed near Sitnik. I managed to survive and kill our attacker, but I was wounded pretty badly. I couldn't carry everything the other survivor had on him, so I buried it. If you walk to the place where the train tracks split off to the Sitnik industrial area you'll find a stash of TREASURETYPE supplies buried nearby in the treeline of the hill. It's well worth the trek my friend.";
		treasure_stash_x = 10935; // Sitnik train cross intersection
		treasure_stash_z = 9490;
		mapName = "enoch";
	};
	class ZenTreasure_Photo03 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Michal, do you remember this girl in the picture? She could drive her Ada like a devil! Better than you drove anyway. I was with her when it all first broke out, we were 'social distancing' together if you know what I mean. We buried some TREASURETYPE supplies not far from her house in Wrzeszcz. When the situation calms down a little, we should go back and pick it up. It's just beyond that outhouse near some old ruins.";
		treasure_stash_x = 8891; // Wrzcczczc
		treasure_stash_z = 4464;
		mapName = "enoch";
	};
	class ZenTreasure_Photo04 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Before this all started I was on a pub crawl with some friends. We took this photo the night before the world turned to hell. I thought Shaun of the Living Dead was a parody film, not a documentary... If you find this photo it means me and my friends are probably dead, so we won't have any use for the TREASURETYPE supply stash we buried near the garbage bins at Lawenda Summer Camp. I hope you have better luck than we did.";
		treasure_stash_x = 782; // Lawenda Summer Camp
		treasure_stash_z = 8622;
		mapName = "enoch";
	};
	class ZenTreasure_Photo05 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "My dearest Aleksy, I didn't want to wake you as I know how hard it has been for you to sleep since you got sick. I'm going to search for more supplies, if I'm not back in a few days I buried a TREASURETYPE stash for you near two dead trees on my way out of Dolnik. The trees are next to an old trailer on the main road. I'm going to look for more supplies up north, and if I find anything worthwhile I'll come straight home. If I don't see you again, I'm so sorry. I love you more than you know ~ Your Natasha";
		treasure_stash_x = 11031; // Dolnik trees
		treasure_stash_z = 1588;
		mapName = "enoch";
	};
	class ZenTreasure_Photo06 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I've tried all I can to stay alive, but sickness is creeping into my very bones. I suspect I have sepsis, but I'm too weak to find medicine. If you find this photo, leaving this note on the back was the last thing I did before resting inside this cabin near Lukow. I buried some TREASURETYPE gear in between the wooden campfire benches there. Good luck to you, stranger.";
		treasure_stash_x = 4335; // Cabin Near Lukow
		treasure_stash_z = 12412;
		mapName = "enoch";
	};
	class ZenTreasure_Photo07 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I thought I was brave. I joined the United Nations as soon as I finished my basic training, ready to take on the infected. But I was wrong, I'm not brave. I'm fucking terrified. Shortly after this photo was taken I ran for the forest and I don't plan to ever return to civilization. I'm going to live out the rest of my days in the mountains, and pray that I never see another infected. I buried all of the UN TREASURETYPE supplies I had under a tree on the northern side of a small pond to the north-east of Lukow. Good luck whoever finds this, you're going to need it.";
		treasure_stash_x = 3673; // Lukow pond
		treasure_stash_z = 12560;
		mapName = "enoch";
	};
	class ZenTreasure_Photo08 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Well, it finally happened. I spent 20 years learning to live off the land in preparation for doomsday. Now I'm ready. The only problem is I forgot where I buried half of my TREASURETYPE supplies. I buried them in various places to keep them hidden from the government who would surely confiscate them. I found most of my stashes, but there's one I can't find. This photo was taken by a friend of mine when I was exploring the castle ruins near the Branzow military base. I remember burying something between a tree stump and some large rocks, next to some ruins. Maybe you can find it, fellow survivor. - Igor";
		treasure_stash_x = 1360; // Branzow ruins
		treasure_stash_z = 11311;
		mapName = "enoch";
	};
	class ZenTreasure_Photo09 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I hope you do better than I and my family did. We've been sheltered in Polana for weeks, but no help is coming. I've decided to commit suicide. I only have 3 bullets left - one for my wife, two for my children. Once they are dead I'll climb the evac tower on the hill and jump to my death. My wife took this photo of me fishing a few days before this hell began, at a lake north-east of our home in Polana. I buried all of my TREASURETYPE equipment there. You'll need to follow the dry creek bed that leads south-west into the mountains, I buried a stash under a tree there next to a dead log. Good luck. - David";
		treasure_stash_x = 4213; // Polana lake
		treasure_stash_z = 2915;
		mapName = "enoch";
	};
	class ZenTreasure_Photo10 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Wow, I was wasted last night. I went to a party in an apartment in Topolin and things got pretty crazy. Once the ecstasy wore off the next morning someone took this photo of me. I don't know where my shoes went, but I remember burying them somewhere. I also remember burying a crate full of TREASURETYPE supplies that I stole from a store in town. Apparently some sort of virus is spreading throughout Livonia so I'm not sure if I'll get a chance to go and check. But I think I buried the crate near a tree surrounded by rubbish behind the police station.";
		treasure_stash_x = 1471; // Topolin police station
		treasure_stash_z = 7361;
		mapName = "enoch";
	};
	class ZenTreasure_Photo11 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Peter, I must be quick. While we were fortifying the old castle ruins south-east of Swarog we were ambushed. I was the only one who managed to escape. You'll remember the castle from this photo. I buried as many supplies as I could carry, hopefully you can recover them before someone finds our TREASURETYPE stash. I buried it between two rocks in a small cluster of trees east of the castle, past the destroyed BMD. Good luck my friend, I hope to see you again soon but for now I must hide. - Alexei (Castle Coordinates: 6921.88 / 1146.87)";
		treasure_stash_x = 6980; // Southern castle
		treasure_stash_z = 1144;
		mapName = "enoch";
	};
	class ZenTreasure_Photo12 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I remember when I first heard the news about the infected breaking out of quarantine and attacking locals. I was leading my group of scouts on a hike through the castle ruins north of Grabin. The news rattled me and I didn't know what to do. I had to get the kids back to their families, but I also had a lot of excess TREASURETYPE supplies on me at the time. I decided to bury most of them in a memorable location. I buried a stash next to a large rock and a small group of trees on the hill near Sowa castle. If I don't find them, maybe you will.";
		treasure_stash_x = 11503; // Grabin castle
		treasure_stash_z = 11906;
		mapName = "enoch";
	};
	class ZenTreasure_Photo13 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Hello survivor. If you found this old photo, perhaps you can recover our doomsday stash too. When the virus outbreak began my family buried a stash of TREASURETYPE gear beneath a treehouse on a remote island in the north-east of Livonia situated in the middle of a large lake. We're unable to return to it and have made plans to leave Livonia. The stash is well worth your time to hunt down if you dare. Good luck, stranger.";
		treasure_stash_x = 12351; // NE lake treehouse
		treasure_stash_z = 10886;
		mapName = "enoch";
	};
	class ZenTreasure_Photo14 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The revolution never came. But the downfall did. We always knew these capitalist pigs would destroy the world someday, but we never imagined it would be due to a virus born out of their greed and abuse of scientific endeavour. My group are leaving Livonia for fresher pastures. We're leaving behind our TREASURETYPE stash, you'll find it buried between two giant spools in the factory perimiter north of Sitnik. Good luck, unknown comrade.";
		treasure_stash_x = 11766; // Factory north sitnik
		treasure_stash_z = 10768;
		mapName = "enoch";
	};
	class ZenTreasure_Photo15 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The taste of human flesh is unparalleled. Before the apocalypse I would have never dreamed of eating human meat. But things have changed. Only the strong survive now. And what is more powerful than consuming the flesh of the most apex of predators on earth? Nothing. They call us a cult, but that's because they don't understand divine genius. We have accumulated riches and power the likes of which the common man could never achieve. I've buried some of this treasure just for fun. In a cluster of bushes near the Stone Circle north-east of Dolnik you will find one such TREASURETYPE stash. I promise, it's not a trap. - Josef the Cannibal";
		treasure_stash_x = 12126; // Stone circle
		treasure_stash_z = 1729;
		mapName = "enoch";
	};
	class ZenTreasure_Photo16 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Blessed are the meek, for they shall inherit the earth. And blessed are the strong, for they shall eat the meek. Hahaha... we do love the taste of human flesh. And everybody knows the most tender meat is that which has not been... over-used. If you share our.. good taste, then you're welcome to our southern TREASURETYPE stash. Consider it a gift for the brave. It is buried between two trees where deer come to die, on the outskirts of the contaminated zone. Don't suffer for too long, stranger. It spoils the meat. (Approx Coordinates: 7661.52 / 2321.09)";
		treasure_stash_x = 7695; // Deer grave
		treasure_stash_z = 2285;
		mapName = "enoch";
	};
	class ZenTreasure_Photo17 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I'm leaving this place. I've lived in solitude for 15 years, but since this outbreak I've had to kill far too many trespassers looking for shelter in my home. Survival was exhausting before the outbreak - now it's intolerable. I'm setting out for Chernarus. I hear things are better there. Fewer survivors, which means fewer scavengers to worry about. In the meantime... if you find this photo, you're welcome to my TREASURETYPE stash. It's buried behind a deer feeder stand near my old house, far to the west of Livonia, in the woods just south of Zalesie.";
		treasure_stash_x = 675; // Western hermit house near Zalesie
		treasure_stash_z = 4397;
		mapName = "enoch";
	};
	class ZenTreasure_Photo18 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Once a frogman, always a frogman. BUDS might not have prepared us for zombies, but what kills living bad guys kills undead bad guys, too. We've been thriving down here in the south. Far fewer survivors means far more game to hunt. We've collected more gear than we'll ever need, so we buried a stash of TREASURETYPE gear beneath the radar tower at Dambog military outpost - if you find this photo, you're welcome to it. Good luck survivor. I'd say see you later, but you'll never see us!";
		treasure_stash_x = 542; // Dambog radar tower
		treasure_stash_z = 1119;
		mapName = "enoch";
	};
	class ZenTreasure_Photo19 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "SEALs never reveal their secrets. But we're not a greedy bunch, we only take what we need. So in this case I'll make an exception. There's a secret stash buried in the north, near Jantar Lake. It's a cache of TREASURETYPE supplies. You'll find it underneath the treehouse built on the huge dead tree there. Good luck, civilian. You'll need it out here.";
		treasure_stash_x = 3376; // Jantar lake with treehouse
		treasure_stash_z = 8913;
		mapName = "enoch";
	};
	class ZenTreasure_Photo20 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "More than half of the town is already infected. The healthy either fled to the woods or are barricaded in houses. It's getting worse, I don't think there will be any help. Looks like it's time for me to head out into the wild and try my luck out there. If I don't survive, the least I can try to do is leave something behind for those who do somehow survive this madness. I buried some spare TREASURETYPE supplies in the bushes near my old green house by the fire station in Topolin. If you find this photograph, well, good luck my friend. Maybe we'll meet someday. Maybe.";
		treasure_stash_x = 1628; // Topolin red house
		treasure_stash_z = 7388;
		mapName = "enoch";
	};
	class ZenTreasure_Photo21 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Before I left the army, my last exercise was just near the shooting range in Wrzeszcz. Even then, there were rumours about an unknown infection. That's why I stole some TREASURETYPE gear and a few other useful things from the supply cache, despite the threat of being court-martialed. I buried what I could fit in a stash towards the back of the shooting range. I hear it has since become an evacuation point so I imagine it's pretty hard to get to now. Good luck, whoever finds this message.";
		treasure_stash_x = 9948; // Shooting range
		treasure_stash_z = 3954;
		mapName = "enoch";
	};
	class ZenTreasure_Photo22 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Looks like the shit has finally hit the fan. They're shutting down the quarry and evacuating all of us out of Livonia. I don't know what's going to happen, but I'm not waiting around to find out. I've stolen as much gear as possible from the surrounding towns of Nadbor. Just in case our evacuation plans don't pan out like the big wigs say it will, I've buried a TREASURETYPE stash inside the Nadbor quarry near the water. If you find this message it means we got out of Livonia alive. Feel free to take the stash for yourself and good luck out there.";
		treasure_stash_x = 6996; // Quarry near nadbor
		treasure_stash_z = 4583;
		mapName = "enoch";
	};
	class ZenTreasure_Photo23 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "My friend, I can go on no longer. I'm afraid I've reached my wits' end. I'm 83 years old and I realize how difficult it has been to keep me alive, and I've been slowing down the group for too long. I'm tired. I'm in constant pain. The travel has worn me down. I've decided to end my life. I'm going to where we first met, by the abandoned quarry north of Dambog. It was beautiful there. You'll find a dead tree next to a large boulder - that is where you'll find my final belongings, a stash of TREASURETYPE supplies. Good luck my friend. Thanks for all you have done. - Jim";
		treasure_stash_x = 682; // North dambog quarry
		treasure_stash_z = 2401;
		mapName = "enoch";
	};
	class ZenTreasure_Photo24 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I'm getting the fuuuck outa here! I don't do zombies man. No sir. Thank god I finished my pilot training a month ago or I'd be shitting bricks right now. I'm taking this MH6 and a one-way ticket to Chernarus. I hear things are better there. They better be. I left a TREASURETYPE stash buried under the radar tower at the Lukow airfield. Whoever wants it can have it. I'm gone. Ciao motherfuckers, and good luck!!";
		treasure_stash_x = 4015; // Airfield
		treasure_stash_z = 10296;
		mapName = "enoch";
	};
	class ZenTreasure_Photo25 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Verily, my trusty blade proves futile against these foul undead fiends! Methinks my prowess in the art of live action roleplay avails me naught in this dire hour. 'Tis prudent that I depart this accursed place and seek refuge amidst those skilled in true combat. I shall conceal my TREASURETYPE belongings by the forsaken well near yonder castle in the Eastern realm of Livonia. Whosoever chances upon it, mayhaps they shall find strength to lay siege to this land with valor and fortitude.";
		treasure_stash_x = 11880; // Eastern castle
		treasure_stash_z = 6579;
		mapName = "enoch";
	};

	//! CHERNARUS PHOTO CONFIG:
	class ZenTreasure_Photo26 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Well, basic training is over just in time for the end of the world. Apparently there's some kind of zombie outbreak. Sounds ridiculous to me, I'll believe it when I see it. Before we left we had a big drink up at the local pub. A bunch of us buried some TREASURETYPE gear near some rocks on the hill as a time capsule just in case this zombie thing turns out to be the real deal. We'll come back for it in a few years, unless someone else finds it first!";
		treasure_stash_x = 4884.433594;  // Balota airfield trees
		treasure_stash_z = 2732.638916;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo27 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "He begged. Said he had a family. I told him so did I - turns out that was a lie. This photo? Took it right after I ended him. Buried his TREASURETYPE stash in the trees near where this photo was taken south of Green Mountain, under a mound of dirt still warm from his body heat when I left. If you want it, dig fast. Might not be alone. Hey, I'm beginning to enjoy this lifestyle. Wish the apocalypse had come sooner.";
		treasure_stash_x = 3539.516113;  // Green mountain field
		treasure_stash_z = 5428.537109;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo28 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "If you're reading this, then I didn't make it. I buried my last stash of TREASURETYPE things above the cliffs of Belaya Polana, near a lone yellow tree. I wish I had more time. Wish we all did. Take my gear. Stay alive at any cost. It's the best we can hope for these days.";
		treasure_stash_x = 14174.469727;  // Belaya polana camp area
		treasure_stash_z = 15256.251953;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo29 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "This is for Black Raven. Operation failed. Squad KIA. Only one survivor: me. There's a TREASURETYPE cache hidden near where you took this photo of me last year, under yellow tree. Marked with a broken branch. Retrieve if possible. I'm not coming back, don't want to compromise our shelter location. You're alone now. Good luck. Over and out.";
		treasure_stash_x = 4238.457031;  // Airfield tents
		treasure_stash_z = 11164.960938;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo30 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "They said the signal was just static. But I heard it. A voice, clear as day, calling from up high, east of the twin cities and their useless churches. I left my TREASURETYPE supplies there, buried beneath the humming steel. If the signal speaks to you too... you'll know where to dig.";
		treasure_stash_x = 8310.640625;  // Radio tower east of Sobor
		treasure_stash_z = 7540.496094;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo31 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Rule #1 of the apocalypse: never trust a guy named Greg. He stole my shoes and left me stranded with this photo. Joke's on him - I already buried all the TREASURETYPE loot we found together. It's near the bridge where I first met him, near where he took this photo of my damned shoes. It might be a while before I can make it back there though. Good luck, Greg. I hope your feet hurt.";
		treasure_stash_x = 563.244019;  // Bridge at Biatholon
		treasure_stash_z = 10993.575195;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo32 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "To my daughter: if you ever return home and find this, I'm gone. I was bitten and I'm leaving before things get too bad. I don't want you to find me like this. Know that I never stopped loving you, or believing you would return. I left a TREASURETYPE stash buried near our house, under the old tree we used to climb when you were a child. Be safe. I love you.";
		treasure_stash_x = 12525.000977;  // House near Berezino
		treasure_stash_z = 10425.946289;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo33 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "When the realm fell to chaos, I held fast within the castle upon yonder island. For three moons I reigned as Sir Thaddeus, Warden of Chernarus, Slayer of the Undead. But alas... foam swords are no match for real zombies. I buried my finest TREASURETYPE treasure by the stairs of the castle keep and fled. Mayhaps thou art braver than I. Or stupider.";
		treasure_stash_x = 13414.611328;  // Skalisty castle
		treasure_stash_z = 3284.592773;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo34 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The light hasn't worked in weeks. No one's coming. I kept hoping someone would answer the distress calls... but only silence ever replied. I've made peace with it now. Before I end things, I've buried my remaining TREASURETYPE supplies behind the shed of my lighthouse. If you find it - live better than I did.";
		treasure_stash_x = 2632.308350;  // Komarovo light house 
		treasure_stash_z = 2211.786133;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo35 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "We killed them all. Men, women, children. Elderly, young, sick, healthy... all dead. My commander said we couldn't risk it. The entire town had been exposed to contamination. Does that make us any better than the creatures we've been sent here to kill? I don't know anymore. We rounded up all of their belongings, some junk, but mostly TREASURETYPE items, and buried it by their bodies. Not much use for it anymore, but if you find this note, then maybe you'll have reason to dig it up.";
		treasure_stash_x = 14851.450195;  // Shkolnik summer camp
		treasure_stash_z = 14607.780273;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo36 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "We ran for days. No food. No sleep. Just screams behind us. I dropped everything I could to stay light. The last of my TREASURETYPE supplies is buried right beneath the spot where I took this final photo of the city I grew up in but can never return to. I thought I'd go back for it some day, but there's no chance now. If you find it, take it, and run. Don't look back.";
		treasure_stash_x = 11853.893555;  // Novod hill
		treasure_stash_z = 14726.685547;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo37 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "We watched three men go into this old castle. Only one came back. Didn't speak. Didn't blink. Just dropped this photo and walked into the woods. We heard there's TREASURETYPE gear stashed there, looks like it's buried behind a bin at some old tourist area. After seeing his eyes... I ain't going anywhere near that place. Up to you if it's worth it.";
		treasure_stash_x = 1541.490601;  // Korona castle
		treasure_stash_z = 9130.580078;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo38 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "She said this place was her favourite. So quiet. So peaceful. I come here sometimes just to remember. I left some TREASURETYPE behind the big tree near her cross - it felt wrong to carry it any further. If anyone finds this, it's yours if you want it.";
		treasure_stash_x = 2554.497070;  // North of Zelenogorsk, little lake
		treasure_stash_z = 5931.146973;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo39 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I worked at the radio station for my entire life. But this pandemic is getting out of control. We're evacuating the entire precinct. In the off chance we get to come back here, I buried a bunch of TREASURETYPE gear between three yellow trees near where I took this final photograph. If I don't make it back to it, maybe whoever finds this note will.";
		treasure_stash_x = 8238.098633;  // Altar
		treasure_stash_z = 9099.567383;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo40 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I came to the cliffs to be alone. Long before the dead rose, I was already done with people. But now they come crawling - the living and the other kind. I'm moving on. I buried my TREASURETYPE gear beneath a lone tree far in the northern mountains, where the wind howls and no footsteps echo. If you found this, maybe the world dragged you up here too. Take what you need. I have no use for it anymore.";
		treasure_stash_x = 6051.155273;  // Northern cliffs
		treasure_stash_z = 14745.204102;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo41 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "This was the last photo I ever took of my sister. We were on our way to the next town - just two backpacks and a little hope. Bandits ambushed us before we even made it past Pusta. I killed them all. Every single one. I buried her TREASURETYPE gear next to a big tree close to where this picture was taken. I couldn't carry the weight. If anyone finds this, you're welcome to it. Just be careful. No one else deserves the fate of my sister.";
		treasure_stash_x = 8829.941406;  // Cherno mountain
		treasure_stash_z = 2863.192871;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo42 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I know you're not proud of me dad, but I did what I had to do. When the outbreak hit, command told us to hold the line. But I saw what was coming - and I wasn't about to die for politicians who fled first. I went AWOL that night and buried the TREASURETYPE gear I couldn't take with me, behind the last row of targets at the old firing range, just in case we need it someday. I don't regret leaving. I only regret not doing it sooner. Think of me what you will - at least I'm alive. Everyone who stayed there is dead now.";
		treasure_stash_x = 1008.772400;  // Tisy shooting range
		treasure_stash_z = 14604.788086;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo43 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The soil stopped giving long before the dead came. I tried to hold on - to the farm, to the routine, to hope. But it all dried up in the end. I buried my TREASURETYPE supplies under a dead tree by the lake, not far from Novaya Petrovka near the old water tower. If you're reading this, take it. Just don't waste it.";
		treasure_stash_x = 4664.858398;  // Novaya Petrovka lake
		treasure_stash_z = 13339.625000;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo44 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I never needed much. Just a line, a hook, and the lake cradled by cliffs. The fish bit often. The silence bit harder. People have begun frequenting my area more often. I think it's time to move on. I buried the TREASURETYPE gear I can't take with me on the lake's peninsula, where I used to sit and watch the mist roll in. If you're the quiet sort, maybe you'll feel what I felt here. If not - take the gear and move on. I don't care anymore.";
		treasure_stash_x = 13326.987305;  // Chernoyeozero lake
		treasure_stash_z = 12054.108398;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo45 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "We found a dead man near some castle ruins in the north. Don't think it was the infected who killed him. Looks like something big got him, maybe a bear? His face was covered with bloody scratches, unrecognizable. We searched the area but couldn't find a sign of any other survivors. We buried his stuff, a bunch of TREASURETYPE gear, at the base of the dead tree in the distance of this photo. If you find this, and you know this man, you'll find his gear there. I hope you fare better than he did.";
		treasure_stash_x = 6876.056152;  // Devil's castle
		treasure_stash_z = 11424.153320;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo46 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I stayed in the old prison ruin for weeks. Thought it was the perfect shelter. But the sounds... whispers in the cells, footsteps when I was alone. I couldn't take it anymore. I ran in the night with just a torch. The TREASURETYPE gear I had with me was too heavy to swim far with, so I buried it on the furthest island near the prison and took this photo to remember where I put it. Don't think I'll be going back though. If you go back there... don't stay after dark.";
		treasure_stash_x = 3255.923828;  // Prison island
		treasure_stash_z = 1244.895996;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo47 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Mommy and Daddy didn't wake up after the bad people came and hurt them. I ran to the top of the hill and stayed there for a long time. I was so hungry. Then a man found me. He said he'd take care of me... he said I'd make a nice appetizer when we got to his camp. I don't know what that means but he gave me some food which made me happy. I buried Mommy and Daddy's TREASURETYPE stuff on the hill, by the big rock and the old wooden benches we used to make fires near. I hope someone nice finds it.";
		treasure_stash_x = 12313.744141;  // Tulga
		treasure_stash_z = 4546.652344;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo48 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "For years I tended to empty pews and the howls beyond the chapel walls. Faith was my shield, but even that has limits. I was bitten last week. The fever grows. I've chosen to walk into the wilderness and meet my maker on my feet, not on my knees. I buried my TREASURETYPE belongings behind the old chapel at my sleepy town in the valley. May it serve you better than it did me. Go with God.";
		treasure_stash_x = 9585.004883;  // Shakhovka
		treasure_stash_z = 6818.185059;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo49 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The graveyard served us well... for a time. But we ran out of graves to dig up, and fresh meat's getting scarce. We're heading south where there are more survivors lurking - greener pastures, fuller bellies. Before we left, we buried some TREASURETYPE things we couldn't carry beneath the dead tree in the churchyard. Take it, if you dare. Just don't stick around after dark. We may come back hungry...";
		treasure_stash_x = 7905.499023;  // Severograd church
		treasure_stash_z = 11964.219727;
		mapName = "chernarusplus";
	};
	class ZenTreasure_Photo50 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I've lived long enough. Too long without her. I buried my TREASURETYPE belongings beside her grave on the hill, near the old wooden benches we used to sit and rest on when we'd go on our hikes together before this all began. I'm heading west now - just me, the revolver, and one bullet. If you find this note and make your way to our precious hill far up on the north-eastern coast, take what you need. But please... don't disturb the grave.";
		treasure_stash_x = 11476.593750;  // Klen hill
		treasure_stash_z = 11320.959961;
		mapName = "chernarusplus";
	};

	//! SAKHAL PHOTO CONFIG:
	class ZenTreasure_Photo51 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The storm hit hard and fast. We ran aground on the northern islands of Sakhal, near an old defunct lighthouse. The sea took the ship. Most of the crew didn't make it. We salvaged what we could, but the snow was too deep and the packs too heavy. We buried the leftover TREASURETYPE gear at the base of the lighthouse to come back for someday. Maybe this gear will help someone else stay alive a little longer if we never make it back.";
		treasure_stash_x = 10922.257813;  // Uzhki lighthouse
		treasure_stash_z = 14555.028320;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo52 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I don't know how I ended up here. Fog rolled in, boat drifted, and now I'm stuck on this godforsaken island near in the far north. No landmarks. No shelter. Too cold to swim back to the mainland. I buried my TREASURETYPE gear at the base of the tree in this photo before the cold finishes what the sea started. If you found this, you're already luckier than me. If you have some means of getting here, take my things, and at least my fate won't be for nothing.";
		treasure_stash_x = 3762.903564;  // Tochka island
		treasure_stash_z = 14419.357422;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo53 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Been stationed on this island out west for six months. Last contact with command was over a month ago after rumours of some kind of pandemic outbreak. No updates. No evac. Just static. I took this photo from the bunker - same view I've stared at every day since it all went quiet. I'm done. Heading out alone. Buried my TREASURETYPE gear just outside the bunker. If anyone finds this... good luck, I guess.";
		treasure_stash_x = 955.388672;  // Cerepacha island
		treasure_stash_z = 10991.975586;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo54 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I kept that old lighthouse running for over a decade. Through storms, blackouts, and now... this. No one has visited my lonely island down here in the south-west for months. Supplies finally ran out. No more food, no more water. I have to move inland, but I can't carry everything. Buried my TREASURETYPE things at the base of my old lighthouse. If anyone finds it - keep moving, and keep the light alive, even if it's just in your heart.";
		treasure_stash_x = 1132.217896;  // Urup island
		treasure_stash_z = 590.405273;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo55 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I have walked among the dead and heard the voice of the divine in the silence. This ghost town was my temple - empty streets, broken homes, and an underground fountain that still flows. I have lived here over a year, awaiting the chosen. I am the messenger. The saviour. The last light. It is my time. I have been bitten. I buried my TREASURETYPE gear behind the fountain on my holy island deep down in the south-east of this frozen wasteland, where the stone weeps and the truth was revealed. Take it, pilgrim. My trial has ended, and your trial begins now.";
		treasure_stash_x = 12699.535156;  // Urup island
		treasure_stash_z = 2441.110840;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo56 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "Yeah, I dragged a chair up a volcano. Why? Because I wanted the best damn seat in the apocalypse. Sat up there like a king, sipping rainwater and eating cold beans. Eventually got bored and climbed back down. Honestly, bringing my TREASURETYPE gear with me was probably the dumbest part of the whole thing. I couldn't carry it any further, so I buried it up there near the chair. I left the chair there in case someone else wants to feel majestic for a while. Just don't fall asleep up there. It rumbles sometimes.";
		treasure_stash_x = 10024.045898;  // Volcano
		treasure_stash_z = 12092.102539;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo57 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I was up here working in the quarry when everything started falling apart. One day it was just radio chatter - the next, silence. Figured it was time to stop digging and start surviving. I'm making my way north, taking the first ship outta here. I buried the TREASURETYPE gear I'd collected over the months working on this god-forsaken island under the scoop in the quarry out east. Snow's covering it now. Better be quick if you find this.";
		treasure_stash_x = 12048.958984;  // Excavator Zvezdgny
		treasure_stash_z = 10626.849609;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo58 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "The springs out West boil with life... and death. We made the offering as the old texts demanded - flesh, bone, and steel. Buried our offering of TREASURETYPE materials in the center of the hot springs, nestled in the ribs of the beast we found there. The water hisses when it's near. That means it's accepted. If you take it... you'd better leave something behind.";
		treasure_stash_x = 7705.441895;  // Western hot springs
		treasure_stash_z = 11498.166992;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo59 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "I was the last one out of the airbase. The sound of screams were spreading, radios were dead, and the evac never came. I did what I could - but when the infected started pouring in, it was time to go. Couldn't carry everything. Buried my TREASURETYPE gear I couldn't carry behind the fire station at the Nogovo evac center, near the back corner of the garage. If you're reading this, stay low and keep moving. No one's coming back for us.";
		treasure_stash_x = 6942.657227;  // Nogovo airfield
		treasure_stash_z = 7603.251953;
		mapName = "sakhal";
	};
	class ZenTreasure_Photo60 : ZenTreasure_PhotoBase
	{
		scope = 2;
		descriptionShort = "We tried to hold the line. Screaming civilians, broken comms, and then... silence. I watched everyone get torn apart in the heart of Sakhal. No backup. No mercy. I ran. I didn't stop running until the only sound was my own breath. Buried my TREASURETYPE gear under the big crane at the evac zone before I left - it would only slow me down, and figured I might come back for it if things ever calmed down. But now... I'm not so sure they ever will.";
		treasure_stash_x = 8319.366211;  // Sakhalskaj evac
		treasure_stash_z = 10386.261719;
		mapName = "sakhal";
	};
};