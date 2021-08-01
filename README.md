# TonicEngine - A 2D Engine + QBert
![MainMenu](/Screenshots/MainMenu_Animated.gif)

## Description
A custom 2D engine written in C++ with a euphemism as its name (for the record, this doesn’t imply anything on behalf of the quality of the engine though). This project was a final assignment for the “Programming 4” course, with the goal of finishing the start of a given base engine (former “Minigin”) and re-creating the famous QBert game using your own engine version. 

The engine supports a few neat features which makes for the success of a fun and nostalgic QBert, and has been revisited a few times for refactoring/cleaning of the code. 

## Features/Patterns
### Features
* 3 Playable Levels
* Score and Health System
* Menu's and UI
* Keyboard + Controller Support
* 2D Collision System
* 2D Spritesheet Animations
* Hexagonal Grid-System
* Enemy Game AI for Hexagonal Grid
* Multithreading
* SDL Audio
* .JSON Game Info Parsing

### Patterns
“Patterns?”, you might ask yourself. Yes, I’m referring to [Game Programming Patterns](https://gameprogrammingpatterns.com/), a highly recommended book I used as a help/reference for any situations that fitted my needs.

* Commands
* Observers
* Singleton
* Game Loop
* Update Method
* Components
* Event Queue's
* Service Locators
* Dirty Flags

## Gameplay
As QBert, your goal is to make sure all the cubes on the map are lit up to advance further. While doing so, you'll be challenged by a few enemies like Ugg and Wrongway (purple enemies) who can kill you on impact. Sam and Slick (green enemies) act like QBert and toggle cubes they land on. On the side of the map you'll find spinning disk that can save you from a risky situation and transport you back to the top.

### Level 1
Requires 1 jump on each cube to light up. Once all cubes are lit up the level is finished.
![Level1](/Screenshots/Level1.gif)

### Level 2
Requires 2 jumps on each cube to light up. Once all cubes are lit up the level is finished.
![Level2](/Screenshots/Level2.gif)

### Level 3
Each jump toggles the cube on/off. Once all cubes are lit up the level is finished.
![Level3](/Screenshots/Level3.gif)

## Contributors
Credits to the two lectures Alex Vanden Abeele and Tom Tesch for the base engine implementation. 

![WinningScreen](/Screenshots/WinningScreen.png)
