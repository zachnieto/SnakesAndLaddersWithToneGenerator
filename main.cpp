#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include "Speaker.h"

using namespace std;


Speaker * display;
const int UNLUCKINESS = 4;


void playFallSound() {
  display -> Sound(1108.7, .3);
  display -> Sound(932.33, .3);
  display -> Sound(830.61, .3);
  display -> Sound(739.99, .3);
  display -> Sound(622.25, .3);
}

void playClimbSound() {
  display -> Sound(622.25, .3);
  display -> Sound(739.99, .3);
  display -> Sound(830.61, .3);
  display -> Sound(932.33, .3);
  display -> Sound(1108.7, .3);
}

void playCorrectAnswer() {
  display -> Sound(523.25, .3);
  display -> Sound(783.99, .3);
  display -> Sound(698.46, .3);
  display -> Sound(783.99, .3);
  display -> Sound(1046.50, .6);
}

void playWrongAnswer() {
  display -> Sound(466.16, .3);
  display -> Sound(440, .3);
  display -> Sound(415.3, .3);
  display -> Sound(392, .6);
}

int TriviaQuestion() {

  srand(time(NULL));
  
  const int numQuestions = 8;
  bool questionsHad[numQuestions];
  
  for (int i = 0; i < numQuestions; i++) { // no questions have been given
    questionsHad[i] = false;
  }

  

  int question = (rand() % numQuestions);

  while (questionsHad[question]) {
    question = rand() % numQuestions;
  }

  int ret = 6;

  cout << string(5, '\n');
  cout << "BONUS QUESTION" << endl;
  cout << string(3, '\n');

  if (question == 0 && !questionsHad[question]) {
    questionsHad[question] = true;
    cout << "What color does Red + Green make?" << '\n' <<
      "a) Blue" << '\n' << "b) Orange" << '\n' <<
      "c) Yellow" << '\n' << "d) Brown" << endl;
    string answer;
    cin >> answer;
    if (answer == "c") {
      ret = 12;
    } else {
      ret = 5;
    }
  } else if (question == 1 && !questionsHad[question]) {
    questionsHad[question] = true;
    cout << "What is the virus responsible for the 2020 shutdown?" << '\n' <<
      "a) Ebola" << '\n' << "b) Covid-20" << '\n' <<
      "c) Covid-19" << '\n' << "d) Influenza" << endl;
    string answer;
    cin >> answer;
    if (answer == "c") {
      ret = 10;
    } else {
      ret = 4;
    }
  } else if (question == 2) { // this question can be called infinite times
    int a = (rand() % 10) + 1;
    int b = (rand() % 10) + 1;
    cout << "What is " << a << " times " << b << "?" << endl;
    int answer;
    cin >> answer;
    if (answer == (a * b)) {
      ret = 11;
    } else {
      ret = 4;
    }
  } else if (question == 3) { // this question can be called infinite times
    int a = (rand() % 20) + 1;
    int b = (rand() % 20) + 1;
    cout << "What is " << a << " plus " << b << "?" << endl;
    int answer;
    cin >> answer;
    if (answer == (a + b)) {
      ret = 10;
    } else {
      ret = 4;
    }
  } else if (question == 4) { // this question can be called infinite times
    int a = (rand() % 10) + 1;
    cout << "What is " << a << " squared?" << endl;
    int answer;
    cin >> answer;
    if (answer == (a * a)) {
      ret = 9;
    } else {
      ret = 4;
    }
  } else if (question == 5 && !questionsHad[question]) {
    questionsHad[question] = true;
    cout << "What is the capital of Massachusetts?" << '\n' <<
      "a) Cambridge" << '\n' << "b) Worchester" << '\n' <<
      "c) Salem" << '\n' << "d) Boston" << endl;
    string answer;
    cin >> answer;
    if (answer == "d") {
      ret = 10;
    } else {
      ret = 4;
    }
  } else if (question == 6 && !questionsHad[question]) {
    questionsHad[question] = true;
    cout << "How many protons does Carbon have" << '\n' <<
      "a) 5" << '\n' << "b) 6" << '\n' <<
      "c) 7" << '\n' << "d) 8" << endl;
    string answer;
    cin >> answer;
    if (answer == "b") {
      ret = 16;
    } else {
      ret = 4;
    }
  } else if (question == 7) {
    int a = (rand() % 10) + 1;
    cout << "What is the square root of " << (a * a) << "?" << endl;
    int answer;
    cin >> answer;
    if (answer == a) {
      ret = 14;
    } else {
      ret = 5;
    }
  }

  if (ret > 6) {
    cout << "Correct! Your dice is now " << ret << " sided!" << endl;
    playCorrectAnswer();
  } else {
    cout << "Incorrect! Your dice is now only " << ret << " sided!" << endl;
    playWrongAnswer();
  }

  return ret;
}

void playToneGenerator() {
  bool addingSounds = true;

    vector < string > notes;
    vector < int > timings;

    while (addingSounds) {
      cout << "Enter a tone(C4 to C6, or rest): ";
      string note;
      cin >> note;
      cout << endl << "Enter a time(in seconds): ";
      float time;
      cin >> time;

      notes.push_back(note);
      timings.push_back(time);

      cout << "Add another note? (y/n): ";
      string moreNotes;
      cin >> moreNotes;

      if (moreNotes == "n")
        addingSounds = false;
    }

    map < string, int > noteToFreq;
    noteToFreq["rest"] = 1;
    noteToFreq["C4"] = 261.63;
    noteToFreq["D4"] = 293.66;
    noteToFreq["E4"] = 329.63;
    noteToFreq["F4"] = 349.23;
    noteToFreq["G4"] = 392.00;
    noteToFreq["A4"] = 440.00;
    noteToFreq["B4"] = 493.88;
    noteToFreq["C5"] = 523.25;
    noteToFreq["D5"] = 587.33;
    noteToFreq["E5"] = 659.25;
    noteToFreq["F5"] = 698.46;
    noteToFreq["G5"] = 783.99;
    noteToFreq["A5"] = 880.00;
    noteToFreq["B5"] = 987.77;
    noteToFreq["C6"] = 1046.50;
    noteToFreq["D6"] = 1174.66;
    noteToFreq["E6"] = 1318.51;
    noteToFreq["F6"] = 1396.91;
    noteToFreq["G6"] = 1567.98;
    noteToFreq["A6"] = 1760.00;
    noteToFreq["B6"] = 1975.53;

    for (int i = 0; i < notes.size(); i++) {
      display -> Sound(noteToFreq[notes[i]], timings[i]);
    }

    vector < string > ().swap(notes); // free memory
    vector < int > ().swap(timings);
}

void playSnakesAndLadders() {
  int turns = 0;

    display -> Sound(830.61, .3);
    display -> Sound(932.33, .3);
    display -> Sound(1108.7, .3);

    int board[100];
    int playerPosition = 1;
    int cpuPosition = 1;
    bool playing = true;

    for (int i = 1; i <= 100; i++) {
      board[i - 1] = i;
    }

    int numOfSnakes = (rand() % 7) + 5;
    int numOfLadders = (rand() % 7) + 5;

    int snakeHeads[numOfSnakes];
    int snakeTails[numOfSnakes];
    int ladderHeads[numOfLadders];
    int ladderTails[numOfLadders];

    for (int i = 0; i < numOfSnakes; i++) {
      snakeHeads[i] = (rand() % 90) + 10; // 10 -> 99
      snakeTails[i] = (rand() % snakeHeads[i]);
    }

    for (int i = 0; i < numOfLadders; i++) {
      ladderHeads[i] = (rand() % 90) + 10;
      ladderTails[i] = (rand() % (ladderHeads[i] - 1)) + 1;

      for (int j = 0; j < numOfSnakes; j++) {
        if (snakeHeads[j] == ladderHeads[i] ||
          snakeHeads[j] == ladderTails[i] ||
          snakeTails[j] == ladderHeads[i] ||
          snakeTails[j] == ladderTails[i]) {
          i--;
          break;
        }
      }
    }

    bool playerTurn = true;

    while (playing) {

      if (playing && playerTurn) {

        int diceSides = 6;
        if (rand() % UNLUCKINESS == 0 && turns != 0)
          diceSides = TriviaQuestion();

        turns++;

        cout << "Type 'r' to roll the die!" << endl;
        string roll;
        cin >> roll;
        cout << string(80, '\n');

        if (roll != "r") { // exit the game
          return;
        }

        int spaces;
        cout << "Rolling: ";
        int rollMax = (rand() % 7) + 70;
        for (int i = 1; i < rollMax; i++) {
          spaces = i % diceSides + 1;
          cout << spaces << flush;
          display -> Sound(523.25, .02);
          usleep(pow(1.07, i) * 1000);

          if (spaces >= 10)
            cout << "\b \b";

          cout << '\b' << flush;
        }

        cout << string(9, '\b') << endl << "You rolled a " << spaces << "!" << endl;

        playerPosition += spaces;
        if (playerPosition > 100)
          playerPosition = 100;

      } else {
        usleep(5000000);
        cout << string(80, '\n');
        int spaces = (rand() % 6) + 1;
        cout << "Opponent rolled a " << spaces << "!" << endl;
        cpuPosition += spaces;
        if (cpuPosition > 100)
          cpuPosition = 100;
      }

      if (playerPosition == 100) { // player win?
        cout << "You win!" << endl;
        playCorrectAnswer();
        playing = false;
      } else if (cpuPosition == 100) { // cpu win?
        cout << "You lose!" << endl;
        playWrongAnswer();
        playing = false;
      }
      else {
        for (int i = 0; i < numOfSnakes; i++) { // check for snake/ladder interactions
          if (playerTurn && playerPosition == snakeHeads[i]) {
            playerPosition = snakeTails[i];
            cout << "You landed on the snake at " << snakeHeads[i] <<
              " and fell to " << playerPosition << "!" << endl;
            playFallSound();
          } else if (cpuPosition == snakeHeads[i]) {
            cpuPosition = snakeTails[i];
            cout << "Opponent landed on the snake at " << snakeHeads[i] <<
              " and fell to " << cpuPosition << "!" << endl;
          }
        }
        for (int i = 0; i < numOfLadders; i++) {
          if (playerTurn && playerPosition == ladderTails[i]) {
            playerPosition = ladderHeads[i];
            cout << "You took the ladder from " << ladderTails[i] <<
              " to " << playerPosition << "!" << endl;
            playClimbSound();
          } else if (cpuPosition == ladderTails[i]) {
            cpuPosition = ladderHeads[i];
            cout << "Opponent took the ladder from " << ladderTails[i] <<
              " to " << cpuPosition << "!" << endl;
          }
        }
      }

      cout << "---------------------------------------------------------------------" << endl;
      for (int i = 100; i > 0; i--) {
        cout << board[i - 1];
        string pos = "  ";

        if (playerPosition == i) {
          if (cpuPosition == playerPosition)
            pos = "OX";
          else
            pos = " X";
        } else if (cpuPosition == i) {
          pos = " O";
        }

        if (board[i - 1] > 99)
          cout << pos << "| ";
        else if (board[i - 1] > 9)
          cout << pos << " | ";
        else
          cout << pos << "  | ";

        if ((i - 1) % 10 == 0) {
          cout << endl << "---------------------------------------------------------------------" << endl;
          for (int j = i - 11; j < i - 1; j++) {
            cout << board[j];

            pos = "  ";

            if (playerPosition == (j + 1)) {
              if (cpuPosition == playerPosition)
                pos = "OX";
              else
                pos = " X";
            } else if (cpuPosition == (j + 1)) {
              pos = " O";
            }

            if (board[j] > 99)
              cout << pos << "| ";
            else if (board[j] > 9)
              cout << pos << " | ";
            else
              cout << pos << "  | ";

          }
          cout << endl << "---------------------------------------------------------------------" << endl;
          i -= 10;
        }
      }

      cout << "Snakes:  (Head) ";
      for (int i = 0; i < numOfSnakes; i++) {
        if (snakeHeads[i] < 10)
          cout << " ";

        cout << snakeHeads[i] << " ";
      }

      cout << endl << "         (Tail) ";
      for (int i = 0; i < numOfSnakes; i++) {
        if (snakeTails[i] < 10)
          cout << " ";
        cout << snakeTails[i] << " ";
      }

      cout << endl << "Ladders:  (Top) ";
      for (int i = 0; i < numOfLadders; i++) {
        if (ladderHeads[i] < 10)
          cout << " ";
        cout << ladderHeads[i] << " ";
      }

      cout << endl << "       (Bottom) ";
      for (int i = 0; i < numOfLadders; i++) {
        if (ladderTails[i] < 10)
          cout << " ";
        cout << ladderTails[i] << " ";
      }
      cout << endl << endl;
      playerTurn = !playerTurn;
    }
    delete[] board;
}

/*** Main operates the DE1-SoC 7-Segment Displays
 * This program writes an integer number on the 7-Segment Displays
 */
int main(void) {
  display = new Speaker;
  cout << "Program Starting...!" << endl;

  cout << "Main Menu:" << endl <<
    "1) Tone Generator" << endl <<
    "2) Snakes and Ladders" << endl;

  int gameMode;
  cin >> gameMode;

  if (gameMode == 1) {
    
    playToneGenerator();

  } else if (gameMode == 2) {
    
    playSnakesAndLadders();
    
  }

  delete display;
  return 0;
}