## OUTDATED, YOU CAN GET THE LATEST SRC BY [REQUEST AND APPROVAL]. SKYPE[balan.narcis1] E-MAIL[balan.narcis96@gmail.com].

# Tera_Emulator_v1xxx
This is a WIP[Work in progress].

      To compile it, you need:
      -boost code [http://www.boost.org/users/history/version_1_61_0.html]

      v1010
      v1020
      v1025
      v1030
      -Updated for NA 4605 OpCode version.
      -finished lobby
      -Basic world.
      v1035
      -New OpCode system update
      -more stabile
      v1036
      -autostart added [see config file]
      
       v1040=>
	confing file edited. added [playerStartContinentId = 5] 
	added world.config file in Config// folder, holds the areas to start [visitable areas]

		
	finished [items][skills][passivities][abnormalities] loaders
	
	made basic inventory system
		-!!! 1 bug [after opening Profile(in game) the inventory won't open]
	made basic world functions [players are visible to eachother depending on theyr currentContinent & 	current visitedSection & visibelRangeVar
	

	chat not ready.
		-> added chat admin commands
			-[./additem %itemId%]
			-[./addgold %ammount%]
			-[./sysmsg %msgId%]
			-[./exit] to disconnect from server
			-[./cleargold]
			-[./expandinventory] expands inventory by 8 slots
			-[./clearinventory] clears the inventory and profile items
	main server window
		->commands:
			-[./start] to start server
			-[./stop] to disconenct all clients and close all areas 
			-[./cls] clear console buffer
			-[./inf] server basic info ::connectedClientsCount, ::startedAreasCount
			-[./asc] ads continentId to [toStartAreasList] [only when server is stopped , not running]
			-[./close] close client by entityId

	v1050
		new chat commands:
			-[./drop %itemid%] drops item in world with not owner
			-[./cleardp] clear all drop from current arrea
			-[./setlevel] <-
			-[./savedb] saves all new changes to db
		unequip/equip items works [not tested for skins]
		resolved inventory-profile bug
		discarded items are now droped in world, not destroyed
		
	still a WIP, so... 
