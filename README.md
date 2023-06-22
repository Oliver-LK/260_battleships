# About

This is a program that runs a version of Battle Ships on the UC Funkit. C Based, make file included.

### Design Choices
Statically allocated memory was used where possible to reduce change of memory leaks or segmentation faults. However the ATMEGA 328 is an 8 bit AVR based MCU with limited computational abilities. To reduce the CPU load the array that stored the board information was allocated dynamically so it could be accessed anywhere within the program rather calling functions to read it.

### Game phases and how to play
The game has main phases. At the beginning, there is a greetings message which asks you to press the Nav switch to continue. This message will continue to display until the NAV is pressed.

When the Nav switch is pressed, the program will enter the ship placement phase. Here, the ships can be moved by using the Nav switch in its respective directions. Ship can be rotated by pressing the NAV switch down. Ships can be placed by pressing the button next to the display. The program prevents ships placement outside the screen and overlapping ships. Once all the ships have been placed by both player the program will exit this phase.

The program will now enter the attack phase where one player will put into shooting mode where they can select the pixel they want to shoot at using the Nav switch. Pressing the Nav switch will select that shot. On the other player's screen they will be displayed their ships in their current state. This means if their ship has been hit at this pixel then it will no longer be displayed. A light will blink on if a hit has been recorded

The game will end when one players ships have all sunk.

To run code enter the following in the terminal:
```bash
    make program
```

