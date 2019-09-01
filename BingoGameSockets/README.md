# Project Bingo C++

The Coordinator ("JogoServer") application will function as a TCP / IP server.
The Player ("JogoClient") application will be the client.
The Coordinator should start and listen. As soon as the Player is presented, the “Connected” event should be launched.
The Player, when receiving the “Connected” event, sends a “Game” request.

The game consists of a mini bingo:
- a card with 10 numbers (random between 1 and 50, no repetitions)
- a draw of balls until the card is filled.
Upon receiving the request “Game” the Coordinator will send the set of 10 card numbers. Numbers are sent at one time.
The Coordinator should only start sending the draw after knowing Player has received the card numbers.
Draw numbers must be submitted independently and at least 1 second apart until you receive the Won event.

The Player, when given a number, warns if it is contained on the card and how many free numbers you have left.
By the time all card numbers have been drawn The command "Won" is sent to the Coordinator.

Extra: It should be possible to turn off and turn on the Player app and give continuity of the game.