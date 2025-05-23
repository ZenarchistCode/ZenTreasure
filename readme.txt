[h1]What Is This?[/h1]

This mod adds photo-based treasure hunting to the game.

It's inspired by Hunterz's https://steamcommunity.com/workshop/filedetails/?id=1982919196 Treasure mod, but I needed more functionality for my server so I created my own version from scratch and the features of my mod are a bit different.

Check out the https://www.youtube.com/watch?v=MaGxDq25pxA&ab_channel=Zenarchist YouTube video attached above to see how it works.

The main differences with my mod compared to the original treasure mod are:

- When a player "reads" a photo, it creates a trigger to spawn the stash when the player goes near it instead of instantly spawning the stash. This prevents people "farming" photo stash locations without having found the corresponding photo first
- The stash's loot configs are chosen at random each time (so finding the same photo twice will produce two entirely different loot contents)
- New photo textures are much easier to add (everything is hidden-selected, so adding a new photo texture is automatic and based on the photo number in the .cpp file)
- This mod includes a "random photo" item which automatically turns into a random photo from the list, making it easy to add random photos as airdrop loot etc (photo list is auto-generated from .cpp file)
- The containers which spawn the loot inside cannot be picked up or put into cargo

Adding loot config is easy to do, just modify the ZenTreasureConfig.json file in your server profiles folder (the mod comes with an example JSON config setup for Livonia).

Note: my mod currently only includes photos for Livonia. To set up photos for a different map this will need to be done manually - there is a video guide on how to do that here: https://youtu.be/MaGxDq25pxA

[h1]Installation Instructions:[/h1]

Install this mod like any other mod - copy it into your server folder and add it to your mods list. Make sure to copy the .bikey into your server keys if you're not using a server management tool like OmegaManager which does that automatically.

This server must be run on both the client and the server.

A JSON config file for adjusting this mod's settings will be automatically created in server_profiles/Zenarchist/ZenTreasureConfig.json

Here are some instructions for the config file and how to add new photos: https://github.com/ZenarchistCode/ZenModPack/wiki/Zen's-Treasure-Mod

[h1]Repack & Source Code:[/h1]

You can repack this mod if you like, and do anything else you want with it for that matter. The source code is on my GitHub at www.zenarchist.io

[h1]Buy Me A Coffee:[/h1]

All my mods are free and open source, but it takes an enormous amount of time to put some of these mods together. If I've helped you out, please consider helping me buy my next coffee! I don't expect it, but I very much appreciate it.

https://buymeacoffee.com/zenarchist

Enjoy!