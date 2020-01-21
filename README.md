# QuizWiz

Jeffrey Chen and Vincent Fong

Period 5

## Project Description:

QuizWiz is a multiple choice trivia game that has both a single player and a two player mode. In the single player mode, the player tries to answer as many questions as they wish, attempting to climb the leaderboard. In the two player mode, each player plays the quiz game together with the same questions. The game waits on each player to submit their answer before displaying the next question to the other player. The player with the most amount of points at the end of the game wins!

## User Interface:

In the opening menu, players have a choice between the single player and a two player mode. They can also check the leaderboard for the single player mode. In the single player mode, they keep answering questions until they get one wrong. In the two player mode, the two players each answer the same questions with them taking turns answering them one at a time. Then after a certain number of questions as entered by the first player, it displays the winner of the game.

## Project usage:
Upon starting the game, you will be asked whether you want to play single player or multiplayer. Simply press 'S' to start single player, 'M' to start multiplayer, or 'L' to view the leaderboard (capitalization doesn't matter). Just answer the questions on your command prompt by typing in the answer choices: a, b, c, or d (capitalization doesn't matter).

### Single player
Enter number of questions desired and the game will ask up to that many of questions until you get one wrong. The leaderboard will then be updated and it will be displayed.

### Multi player
This works for two players. This requires you (and your friend) to ssh into one of the computers at homer.stuy.edu. Once you both are connected, you both need to run the program at the same time. Once this happens, player #1 (the first player to enter multiplayer mode) will enter the number of questions both will answer. Then, the two players answer questions in the same fashion as in single player; the only difference being that new questions will not appear until the other player has answered their question ie. player #1 will answer question #1 while player #2 waits and then once player #1 answers, player #1 waits for player #2 to answer the same question before moving on to the next question. 

### Leaderboard
This displays the leaderboard for the single player game. The leaderboard only displays the results of games played on the same machine. It displays the size of the leaderboard file as well as when it was last modified.

## Required libraries:
None!

## Other information:
Bugs:
- There's an error if the user enters a number of questions that exceeds the amount in the database (50)
