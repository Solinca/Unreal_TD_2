# Unreal_TD_2

Controls:

Z Q S D    -> Player Movement

Space      -> Player Jump

R          -> Reload current gun ( pressed once, slowly gain 1 bullet with interval until full or shot triggered )

Left Click -> Shoot with current gun ( keep pressed for automatic shoot )

Escape     -> Trigger in game pause menu

& (1)      -> Switch to first weapon ( pistol )

é (2)      -> Switch to first weapon ( machine gun )

" (3)      -> Switch to first weapon ( shotgun )

Inputs are disabled on death and during pause


Bonus Types:

- Health                 -> Heal 5 health points
- Golden Statue          -> Gain 500$
- Shield                 -> Gain unlimited ammo for 10 seconds
- Player "Soul" ( pole ) -> Gain 5000$ - Only appears when the player has died at least once ( at the previous death position )


UI Types:

- Player      -> Display Health ( bottom left ), Munition and Unlimited ammo bonus ( bottom right ), Score ( top left ) and Money ( top right )
- Wave        -> Displayed current wave with ease in/out animation
- Death       -> Red fade in screen on death and return to main menu
- Pause       -> Can "Resume game" or "Quit to main menu"
- Main Menu   -> Can "Play" the game, check out "Leaderboard", "Delete" current save ( leaderboard and death position ) and "Quit" the game
- Leaderboard -> Display every saved score, not ordered


Customization:

BP_MyCharacter->PlayerWeaponComponent->WeaponData to modify Weapon Mesh, Damage, Range, Max Ammo, Score on kill, Time Between Shots and Reload Interval ( for one bullet )

BP_MyCharacter->PlayerHealthComponent to modify Player Health

BP_PlayerRemainingSoul to modify the amount of gold given

BP_ZombieAI to modify damage to player and "invicibility time" ( time between attack on contact with player )

BP_ZombieWaveManager to modify the delay between Zombie Spawn and the number of Zombie per wave

BP_Bonus to modify the duration of Unlimited Ammo

BP_Gold to modify the amount of gold given

BP_Heart to modify the amount of health restored
