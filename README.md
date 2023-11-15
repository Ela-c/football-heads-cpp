# Football Heads

## A fully functional game project written in C++ showing how to create a game using the splashkit C++ library

![alt text](https://github.com/Ela-c/football-heads-cpp/blob/main/screenshot.png?raw=true)

The project has been developed to create a fully functional football heads game. It
incorporates professional coding practices such as good use of naming conventions and
well-structured code. It also demonstrates proper use of abstraction and modularization
by using different modules to provide services that help handle the game objects. Each
module has an API to handle one of the entities.

### How does the player control the character and head the ball?

The project counts with a procedure called handle_input that enables the user to control
the character and head the ball. The implementation of these procedure follows the
proposed design which helped visualize its connection to the main function of the
program

### Realistic physics simulation for each of the objects involved in the game including correct handling of collisions between other objects

The game achieves realistic physics simulations through the application of conservation
of linear momentum, gravity, friction and elasticity of objects. All the functionalities
work under the name of one procedure called apply_physics.

## Installation

1. Clone this project
2. Download and set up Splashkit (https://splashkit.io/)
3. Build the project typing the following comand on the terminal: skm clang++ program.cpp lib/\*.cpp -o football_heads.exe
4. run ./football_heads.exe to start the game
