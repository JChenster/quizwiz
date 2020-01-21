# QuizWiz

Jeffrey Chen and Vincent Fong

Period 5

## Project Description:

QuizWiz is a multiple choice trivia game that has both a single player and a two player mode. In the single player mode, the player tries to answer as many questions correctly, attempting to climb the leaderboard. In the two player mode, each player (on a different process) plays the quiz game together. The game waits until each player has submitted their response to reveal the answer, what each player chose, and move on to the next question. The player with the most amount of points at the end of the game wins.

## User Interface:

In the opening menu, players have a choice between the single player and a two player mode. They can also check the leaderboard for the single player mode. In the single player mode, they keep answering questions until they get one wrong. In the two player mode, a question shows up and gives each player 10 seconds to answer the question before showing the results of the question, how each person answered, and then moving on to the next question. Then after a certain number of questions, it displays the winner of the game.

## Project usage:
Upon starting the game, you will be asked whether you want to play single player or multiplayer. Simply press 's' or 'S' to start single player, and 'm'/'M' to start multiplayer.

### Single player
Just answer the questions on your command prompt by typing in the answer choices and hitting enter!

### Multi player
This requires you (and your friend) to ssh into one of the computers at homer.stuy.edu. Once you both are connected, you both need to run the program at the same time. Once this happens, you will then answer questions in the same fashion as you would in single player; the only difference being that new questions will not appear until the other player has answered their question.

## Required libraries:
None!

## Important citations and things:
Please do not just end the program by interrupting! It messes up the shared memory. Just play through the game....
