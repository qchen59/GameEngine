# HW5
Scripting and a second game
### Prerequisites

SFML 2.5.1
CPPZMQ
ZMQ Library
Microsoft Windows 10

### Getting started

##### Files and source code

In the zip file `HW5` , there are:

 `HW5/Release`  : Contains the  realease version of executable file.

`HW5/Debug`: Contains the  debug version of executable file.

 `HW5/CSC481_Client` : Contains the source code and build files for client project.
 
  `HW5/CSC481_Server` : Contains the source code and build files for server project.
  
   `HW5/CSC481_Client2` : Contains the source code and build files for second game client project.
 
  `HW5/CSC481_Server2` : Contains the source code and build files for second game server project.

`HW5/CSC481.sin`: The visual studio solution

##### Execution instruction

1. To Start execute the game, direct to `Release` folder, double click on `CSC481_Server.exe` or `CSC481_Server2.exe` for second game. 
2. Then double click on `CSC481_Client.exe` to excute the client or `CSC481_Client2.exe` for second game.There will be a window pop up which display the game figures. The game support at most 3 clients.
3. To end the game, click on the `X` on the right top.

### Controls of the game (Fisrt Game)

In the game, the red heart is the character that player can control. There will also be a moving UFO above the heart that the heart can jump on it.

`A`: Press the key `A` on keyboard, the heart will move left

`D`: Press the key `D` on keyboard, the heart will move right.

`Space` Press the key `Space` the heart will jump.

**Jumping and  landing** : The heart is able to jump on the movig UFO and land on it. Player can also jump off from the UFO.

`P`: Press the key `P` on keyboard, the time of the game will be paused.

`U`: Press the key `U` on keyboard, the time of the game will be unpaused.

**Pause and unpause** : The game can be paused and unpaused.

`Up`: Press the key `Up` on keyboard, change the time speed to 1 time.

`Left`: Press the key `Left` on keyboard, change the time speed to 0.5 time.

`Right`: Press the key `Right` on keyboard, change the time speed to 2 time.

**Speed up and down** : Player can speed up or slow down the game timeline.

`Death zone`: The upper border of the winodw is the death zone, when the character collides with the upper border, it will be sent to the spawn point.

`Spawn point`: The spawn point is in the bottom left corner. When a character hit the Death zone, it will be sent to the spawn point.

**Death zone and spawn point** : The game include a death zone and a spawn point.

`Side boundary`: The left and right border of the winow are the side boundaries. When the character collides with those side boundries the view of window will move left or rihght follow the character. So some object and scenes will disappear at some points or appear again when moving back.

**Side boundary** : The game has side boundaries.

### Controls of the game (Second Game)
This game is a simple Space Invaders, the character can shoot fire and the fire can destory the spaceship.

`A`: Press the key `A` on keyboard, the heart will move left

`D`: Press the key `D` on keyboard, the heart will move right.

`W`: Press the key `W` on keyboard, the heart will move forwad.

`S`: Press the key `S` on keyboard, the heart will move backward.

`Space`: Press the key `Space` the heart will shoot a fire.

**Destory the spaceship**

When the fire collide with the spaceship, the spaceship will be destoried.

### Graphics/Textures
The game graphics are  `heart.png`and`UFO.png` that located in `Release`,  `Debug`,  `CSC481_Client`, `CSC481_Server` folders .

### Reference
Some function are referenced to the ZMQ examples.

### Author
Qiuyu Chen

