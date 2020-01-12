# QuizWiz

Jeffrey Chen and Vincent Fong

Period 5

## Project Description:

QuizWiz is a multiple choice trivia game that has both a single player and a two player mode. In the single player mode, the player tries to answer as many questions correctly, attempting to climb the leaderboard. In the two player mode, each player (on a different process) plays the quiz game together. The game waits until each player has submitted their response to reveal the answer, what each player chose, and move on to the next question. The player with the most amount of points at the end of the game wins.

## User Interface:

In the opening menu, players have a choice between the single player and a two player mode. They can also check the leaderboard for the single player mode. In the single player mode, they keep answering questions until they get one wrong. In the two player mode, a question shows up and gives each player 10 seconds to answer the question before showing the results of the question, how each person answered, and then moving on to the next question. Then after a certain number of questions, it displays the winner of the game.

## Technical Design:
Topics Used:
- It will work with files by importing the questions from them.
- Semaphores will be used to protect the leaderboard database.
- Pipes will be used to communicate between the different processes running multiplayer mode.
- Shared memory will be used to store the responses of each player in the multiplayer mode.


Data Structures:
- Arrays
  - Hold leaderboard data
  - Record player’s username and score in single player mode
- Structs
  - Record player’s username, response, and score in multiplayer mode

Algorithms:
- Sorts
  - Sort leaderboard data
  - Sort scores in multiplayer mode

## Timeline:
- By Jan 6: Write parse.c to import and parse questions from files (Vincent)
- By Jan 6: Implement the single player mode in single.c (Jeffrey)
- By Jan 10: Implement the leaderboard (Jeffrey)
- By Jan 13: Implement two player mode
  - Implement running interface that doesn’t move on to the next question until both players answer (Jeffrey)
  - Implement ability to see how other people respond and compare results (Vincent)
- By Jan 17: Debug debug debug (Both)

## Devlog
### 1/3/2020
- Jeffrey: created basic layout

### 1/4/2020
- Vincent: wrote parsing question method

### 1/5/2020
- Vincent: wrote getting N questions method, employs single parseQuestion method to get N questions from a formatted text file
- Jeffrey: debugged this method b/c Vincent writes flawed code

### 1/6/2020
- Jeffrey: successfully figured out problems of N questions method :))
- Jeffrey: wrote single.c and it's mostly done but it needs to be debugged

### 1/7/2020
- Jeffrey: debugged single.c, randomized question order

### 1/8/2020
- Jeffrey: debugged single.c for Linux, wrote basic leaderboard abilities, still need to debug some minor things but otherwise it's good!

### 1/9/2020
- Jeffrey: finished debugging single.c

### 1/10/2020
- Jeffrey: started writing sorting for leaderboard

### 1/12/2020
- Jeffrey: successfully completed and debugged leaderboard sorting. Single player should be all done now!
