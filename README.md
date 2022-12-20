# MatrixProject

This is the final Matrix Game. I used a breadboard, a joystick and a button to develop a retro game controller. To the Arduino Uno I connected an LCD Screen too where it should display the menu of the future game.

### Implementation Ideas
 I tought the menu as a DFA. I created a matrix of movements like the transition function. START GAME state is connected to the GAMEPLAY state, SETTINGS state is connected to the Username state which is related as well with Difficulty state and so on.
 
 The game should store those info somewhere and I prepared it to be written on Arduino UNO's EEPROM. I defined a struct for the system's info(eg. matrix brightness) and a struct for player's info(his 3 letters name and his score). The EEPROM should be updated with the system info and the highscores of 3 best players only when it was changed  because we should avoid excesivly excessively writing on this type of memory.
 
 The refresh time of the LCD display is 250ms which means the refresh frequency rate is 4Hz.
 
 One move UP or DOWN of the joystick can iterate only to the next state, even if the user is holding it. The exception is made at username, you cand iterate trough all characters just by holding it UP or DOWN because it's faster to choose your name. In the first place I used one move one itaration for the username too but it was too slow. 

 **[Link Video 1](https://youtu.be/Jl3W35kquCA)**

 # Snake Logic
 I used a 8x8 matrix of 1 and 0 to keep in memory the states of each of the matrix leds. For the logic of the snake there is one deque list to store every position of the snake's points that form the actual snake.
 At every step one point is cut from the tail and one is added on the head. The head is generated carefully, in order to fit the snake's direction.
 
Generating food for snake is done by pseudo-random values that must not spawn under our character.

The refresh time of the game is 600ms.
When score 5 is hit, every time it eats a generated food the difficulty increases by 25. The difficulty of the game consists of decreasing the refresh time of the game by the value of difficulty (refresh_time - difficulty). 

e.g. Score 5 => refresh_time = 600 - 0,

 Score 6 => refresh_time = 600 - 25,
 
 Score 7 => refresh_time = 600 - 50 and so on until difficulty value hits 225.
 

 
  **[Link Video Gameplay](https://youtu.be/J5X2srdYE_4)** 
 
 ![45](https://user-images.githubusercontent.com/39965333/205901945-74db2116-aab8-4e4e-985e-de2d674d6b8a.jpg)

![WhatsApp Image 2022-12-06 at 13 34 54](https://user-images.githubusercontent.com/39965333/205901969-38a0934f-de2e-4c71-9ebf-ad9014b5fbf0.jpg)
