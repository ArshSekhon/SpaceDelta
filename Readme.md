# Technical Documentation

## Introduction
Space Delta: Guardians of Galaxy is a space-shooter style game based upon Allegro 4.4.2. The project was created using Visual Studio. 

In this game player has to fight against waves of alien invaders (Please refer to the game design document for more details on the story of the game). The goal of the game is to survive for as long as possible and kill as many enemies as possible. 

Key features of the Game include:
- Beatiful graphics and sprite animations
- Amazing sound effects and music
- Sound and Graphics related settings that are persistent
- User friendly user interfaces
- Game supports 3 different resolutions, full screen and windowed mode
- Addictive gameplay (I made my 11 year old brother play it for testing and he was so into it that he wouldn't let me work further on it. He kept playing for a really long time.)
- Game features different enemy types that have different level of difficulty
- Refined Collision detection

*Note: Some graphics settings like high resolution or full screen mode may misbehave on newer version of windows due to compatibility issue as Allegro 4.4.2 came out in early 2000s*


## Install Instructions
In order to run the game you would need to setup the allegro first:

1. Go to [https://www.allegro.cc/files/?v=4.4](https://www.allegro.cc/files/?v=4.4) and download windows binaries for MSVC 10
2. Unzip the binaries to C:/allegro
3. Now you should have the following folders C:/allegro/bin, C:/allegro/include and C:/allegro/lib.
4. On the Windows desktop, right-click My Computer and click properties.
5. In the System Properties window, go to the following Advanced tab > Environment Variables > System Variables.
6. Find the variable Path and click edit, if the last character is not a semi-colon(;) then add one ; to the end and after it paste C:/allegro/bin;
7. Click apply a bunch of times as required and you should be good to go.

Now open the SpaceDelta Project in Visual Studio and hit run!

## Technical Design

The entrypoint for the project is SpaceDelta.cpp. The file basically creates a [GameManager](@ref GameManager) object and calls the [gameManager.init()](@ref GameManager.init) function. This function does all the required setup and perform tasks like setting up allegro, creating struct to store gameState, acquiring mouse, setting up sound etc.


After this [gameManager.runGameLoop()](@ref GameManager.runGameLoop) is called and the control is completely passed to the game manager. The game loop basically checks the current state of the game and then hands over the control to object of correct Screen/Menu class. These Screen/Menu objects basically take care of things like drawing graphics on screen, playing sounds, handling event etc. 

For e.g. if the Game state indicates that player has settings menu open then game loop would basically call [settingsMenu.showSettingsMenu](@ref SettingsMenu.showSettingsMenu) This would draw the required graphics on the screen, would do the required event handling and actions by making use of other classes

This is a brief overview of how the game is designed.

Refer to GameManager.cpp for more details.


