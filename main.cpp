/* main.cpp
    Wordle Reload is a game that allows you to guess either a 3 letter word or 5 letter word.
    You have a set amount of time to guess a word.  At the conlusion of game play
    you will be provided stats on your overall game play.

    Author: Yousef Habeeb, Sohaib Ghani
    Date: 02/25/2022
    Class: CS 141, Spring 2022, UIC
    System: Mac OS Visual Studio code

*/
#include <ctime>  //Needed to set the random number seed to be the current time3
#include <iostream>   // For Input and Output
#include <vector>   // Input file is stored in a vector
#include <fstream> // For file input and output
#include <cassert>//For the assert statement used to validate file open
#include <cctype>  // Allows using the tolower() function
#include <cstdlib>
#include <algorithm>
using namespace std;

//--------------------------------------------------------------------------------

void getDictionaryVector(vector <string> &threeWorddictionary,vector <string> &fiveWorddictionary){
  ifstream inStream;                // Declare an input stream for reading
  inStream.open("wordlewords.txt");    // Open dictionary file
  assert( inStream.fail() == false ); // Ensure file open worked

  string newWord;
  while (inStream >> newWord){            // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
    if (newWord.size() == 3){
      threeWorddictionary.push_back(newWord);
    } else {
      fiveWorddictionary.push_back(newWord);
    }
  }
  inStream.close();     //close the file
}

//used to genertate random words
void random(int& number , int max){
  number  = rand()% max;
}


int binarySearchString(string searchWord, vector< string> dictionary){
   int mid;
   int low;
   int high;
   // Initialize low and high variable
   high = dictionary.size();
   low = 0;

   //Write appropriate while condition below
    while (high >= low) {
      // Calculate the middle of low and high
      mid =(high+low)/2;
      // Save the compared result between 1) the middle index element of dictionary and 2) searchWord
      int searchResult = searchWord.compare(dictionary.at(mid));

      if (searchResult == 0) {
         return mid;
      }
      else if (searchResult < 0) {
         high = mid - 1;
      }
      else {
         low = mid + 1;
      }
   }
  return -1; // not found
}
/////////////////////////////////////////////////////////////////////////////////////////////

// what to do when the letters match or dont match
void word3comparisons(string &l, string w, string o){
  cout<<endl<<endl;
  if(w[0] == o[0]){
    l[2] = o[0];          //capitalizes the letter when it is in the right spot
    l[2]= toupper(l[2]);
  }
  else if ((w[0] != o[0])&&(w[0] == o[1])){
    l[2] = w[0];
  }                 // keeps the letter as a lowercase when it is in the wrong spot
  else if ((w[0] != o[0])&&(w[0]==o[2])){
    l[2] = w[0];
  }        
  if(w[1] == o[1]){
    l[9] = o[1];             //repeat for all the letters (repeats for all possible combninations)
    l[9]= toupper(l[9]);
  }
  else if ((w[1] != o[1])&&(w[1] == o[0])){
    l[9] = w[1];
  }
  else if ((w[1] != o[1])&&(w[1]== o[2])){
    l[9] = w[1];
  }
  if(w[2] == o[2]){
    l[16] = o[2];
    l[16] = toupper(l[16]);
  }
  else if ((w[2] != o[2])&&(w[2] == o[0])){
    l[16] = w[2];
  }
  else if ((w[2] != o[2])&&(w[2] ==o [1])){
    l[16] = w[2];
  }           
}

//prints comments like "nice work" with the number of attempts
void attempt3comments(int a,string w,string o,int &cg, int &streak, vector <int> &dictionarystreak,int &elapsedSeconds,int startTime, vector <int> &timeDictionary){
  //difference of time
  elapsedSeconds = difftime( time( NULL), startTime);

  //if the 1st attempt is corrrect
  if ((a == 4) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])){ 
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< " seconds. \n"<<"  - It took you 1/4 attempts."; 
    timeDictionary.push_back (elapsedSeconds);
    streak+=1; //streaks
    cg+=1;  //correct 
  }
    //if the 2nd attempt is corrrect
  else if ((a == 3) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< " seconds. \n"<<"  - It took you 2/4 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    streak+=1;  //streaks
    cg+=1;   //correct
  }
    //if the 3rd attempt is corrrect
  else if ((a == 2) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< " seconds. \n"<<"  - It took you 3/4 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    streak+=1;  //streaks
    cg+=1;  //correct
  
  }
    //if the 4th attempt is corrrect
  else if ((a == 1) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< " seconds. \n"<<"  - It took you 4/4 attempts."; 
    timeDictionary.push_back (elapsedSeconds);
    streak+=1;  //streaks
    cg+=1;  //correct
  }
  else if(a == 1){         //if the attempt is not correct and over the time limit
    if (elapsedSeconds > 20){
      cout<<"Your time has expired.  Try again. \n"<<"  - You are "<<elapsedSeconds-20<<"seconds over the 20 second time limit.";
    }
    else{        //if the attempt is not correct
    cout<<endl<<"Maximum amount of attempts have been reached. Try again."; 
    dictionarystreak.push_back(streak);
    streak =0;  //streaks
    cg +=0;  //correct
    }
  }
}


//carries instructions for the 3 letter comparisons
void instructions3(string guess, int &cg,int &streak, vector <int> &dictionarystreak, vector <string> threeLetterDictionary, vector <int> &timeDictionary){
 
  int attempts = 4;
  string wrd = guess; //passing down to later funtions
  string user_word;   // the users guess
  vector <string> listAttempts;  //used to store previous attempts
  time_t startTime;
  int elapsedSeconds = 0;
  int stringChecker;

  while(attempts >0){ //keeps the game going while theres still attempts
    if ((attempts == 1||attempts == 2||attempts == 3||attempts == 4) &&(user_word[0] !=wrd[0]||user_word[1] !=wrd[1]||user_word[2] !=wrd[2])){ // if the words do not completely match //
      
      cout<<endl<<"Please enter word -->  ";
      string threeLetters = "[ * ]  [ * ]  [ * ]"; //string that will be chnaged
      cin>>user_word;
      std:: transform(user_word.begin(), user_word.end(), user_word.begin(), ::tolower);// allows use of capital letters

      //checks if the word is in the dictionary (binary search)
      stringChecker = binarySearchString(user_word, threeLetterDictionary);
          
      if (user_word.size() != 3){//word size should be 3
        cout<<endl;
        cout<<"Invalid word entry - please enter a word that is 3 characters long. \n";
        attempts ++;// restores the attempt because invalid entries dont count
      }
      else if (stringChecker != -1) {
        if (attempts == 4 ) {
          // starts the time fromt he first valid entry
          startTime = time(NULL);
        }
        word3comparisons(threeLetters, user_word, wrd);
        // runs the comparisons for each index
  
        listAttempts.push_back(threeLetters);
        for (int i = 0; i < listAttempts.size(); i++){ 
          cout << listAttempts.at(i) << endl;  
          // loops allows the previous attempts to be printed 
        }  attempt3comments(attempts,user_word,wrd,cg,streak,dictionarystreak,elapsedSeconds,startTime,timeDictionary);//comments and stats after each play is displayed
      } 
      else {      // if the word is 3 letters but not in the dictionary
        cout <<endl<< "Not a playable word, please select another word.";
        attempts++; // restores the attempt because invalid entries dont count
      }
    } 
    attempts --;
  }  
}

//carries the directions fo the game as well as function calls
void threeLetterPlay(string guess,int &cg,int &streak, vector <int> &dictionarystreak,vector <string> threeLetterDictionary,vector <int> &timeDictionary){
  cout<<"To get started, enter your first 3 letter word. \n"<<"You have 4 attempts to guess the random word. \n"<<"The timer will start after your first word entry. \n"<<"Try to guess the word within 20 seconds. \n";
  instructions3(guess,cg,streak,dictionarystreak,threeLetterDictionary,timeDictionary); // above function that carries out both comparisons and comments
  cout<<endl<<endl;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//runs the comparison checks 
void word5comparisons(string &l, string w, string o){
  cout<<endl<<endl;
  if(w[0] == o[0]){
    l[2] = o[0];                       //if the letetr is in the right spot, it is capital
    l[2]= toupper(l[2]);
  }
  else if ((w[0] != o[0])&&(w[0] == o[1])){
    l[2] = w[0];
  }
  else if ((w[0] != o[0])&&(w[0]==o[2])){     // if the letter is in the wrong spot, it is lowercase
    l[2] = w[0];
  }
  else if ((w[0] != o[0])&&(w[0]==o[3])){
    l[2] = w[0];
  }
  else if ((w[0] != o[0])&&(w[0]==o[4])){
    l[2] = w[0];
  }
  
  if(w[1] == o[1]){
    l[9] = o[1];
    l[9]= toupper(l[9]);
  }                                          // repeats for all letters / indexes
  else if ((w[1] != o[1])&&(w[1] == o[0])){
    l[9] = w[1];
  }
  else if ((w[1] != o[1])&&(w[1]== o[2])){
    l[9] = w[1];
  }
  else if ((w[1] != o[1])&&(w[1]== o[3])){
    l[9] = w[1];
  }
  else if ((w[1] != o[1])&&(w[1]== o[4])){
    l[9] = w[1];
  }
  
  if(w[2] == o[2]){
    l[16] = o[2];
    l[16]= toupper(l[16]);
  }
  else if ((w[2] != o[2])&&(w[2] == o[0])){
    l[16] = w[2];
  }
  else if ((w[2] != o[2])&&(w[2]==o[1])){
    l[16] = w[2];
  }          
  else if ((w[2] != o[2])&&(w[2] == o[3])){
    l[16] = w[2];
  }
  else if ((w[2] != o[2])&&(w[2] == o[4])){
    l[16] = w[2];
  }

  if(w[3] == o[3]){
    l[23] = o[3];
    l[23]= toupper(l[23]);
  }
  else if ((w[3] != o[3])&&(w[3] == o[0])){
    l[23] = w[3];
  }
  else if ((w[3] != o[3])&&(w[3]==o[1])){
    l[23] = w[3];
  }          
  else if ((w[3] != o[3])&&(w[3] == o[2])){
    l[23] = w[3];
  }
  else if ((w[3] != o[3])&&(w[3] == o[4])){
    l[23] = w[3];
  }

  if(w[4] == o[4]){
    l[30] = o[4];
    l[30]= toupper(l[30]);
  }
  else if ((w[4] != o[4])&&(w[4] == o[0])){
    l[30] = w[4];
  }
  else if ((w[4] != o[4])&&(w[4]==o[1])){
    l[30] = w[4];
  }          
  else if ((w[4] != o[4])&&(w[4] == o[2])){
    l[30] = w[4];
  }
  else if ((w[4] != o[4])&&(w[4] == o[3])){
    l[30] = w[4];
  }
}
//prints out comments according to performance
void attempt5comments(int a,string w,string o,int &cg, int &streak, vector <int> &dictionarystreak,int &elapsedSeconds,int startTime, vector <int> &timeDictionary){
  elapsedSeconds = difftime( time( NULL), startTime);

  //if the 1st attempt is corrent
  if ((a == 6) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){ 
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 1/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);//store the time 
    cg+= 1;    // correct guesses
    streak+=1;  //streaks
  }
    //if the 2nd attempt is correct
  else if ((a == 5) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 2/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    cg+= 1; // correct guesses 
    streak+=1; //streaks
  }
  else if ((a == 4) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 3/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    cg+= 1;  // correct guesses 
    streak+=1;  //streaks
  }
  else if ((a == 3) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 4/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    cg+= 1;  // correct guesses 
    streak+=1;  //streaks
  }
  else if ((a == 2) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 5/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    cg+= 1;  // correct guesses 
    streak+=1;  //streaks
  }
  else if ((a == 1) &&(w[0] ==o[0])&&(w[1] ==o[1])&&(w[2] ==o[2])&&(w[3] ==o[3])&&(w[4] ==o[4])){
    cout<<endl<<"Nice Work!  You guessed the correct word \n"<<"  - You completed the board in: "<<elapsedSeconds<< "seconds. \n"<<"  - It took you 6/6 attempts.";
    timeDictionary.push_back (elapsedSeconds);
    cg+= 1;  // correct guesses 
    streak+=1;  //streaks
  }
  else if(a == 1){ //if the guess isnt not correct and the time expires
    if (elapsedSeconds > 20){
      cout<<"Your time has expired.  Try again. \n"<<"  - You are "<<elapsedSeconds-20<<"seconds over the 20 second time limit.";
    }
    else{  //if the gueess isnt not correct
    cout<<endl<<"Maximum amount of attempts have been reached. Try again."; 
    dictionarystreak.push_back(streak);
    streak =0;  //streaks
    cg +=0;  // correct guesses
    }
  }
}

//instriuctions for five letter words
void instructions5(string guess, int &cg,int &streak, vector <int> &dictionarystreak, vector <string> fiveLetterDictionary,vector <int> &timeDictionary){
  
  int attempts = 6;
  string wrd = guess;  //passed down as the correct word
  string user_word;    // users guess
  time_t startTime; 
  vector <string> listAttempts; //stores previous attempts
  int elapsedSeconds = 0;
  int stringChecker;
  while(attempts >0){
                      // if the words do not completely match //
    if ((attempts == 1||attempts == 2||attempts == 3||attempts == 4||attempts == 5||attempts == 6) &&(user_word[0] !=wrd[0])||(user_word[1] !=wrd[1])||(user_word[2] !=wrd[2])||(user_word[3] !=wrd[3])||(user_word[4] !=wrd[4])){ // if the words do not completely match
      
      cout<<endl<<"Please enter word -->  ";
      string fiveLetters = "[ * ]  [ * ]  [ * ]  [ * ]  [ * ]";
      cin>>user_word; 
      //alllows use of capital letters 
      std:: transform(user_word.begin(), user_word.end(), user_word.begin(), ::tolower);
      
        //checks if the word is in the dictionary
      stringChecker = binarySearchString(user_word, fiveLetterDictionary);
      
      if (user_word.size() != 5){ // validates the size of the letter
          cout<<endl;
          cout<<"Invalid word entry - please enter a word that is 5 characters long. \n";
          attempts ++; // adds an attempt because invalid entries dont count
      }
      else if (stringChecker != -1){
        if (attempts == 6 ){
          startTime = time(NULL); //starts the timer after the user input
        }
          //comparing the letters 
        word5comparisons(fiveLetters, user_word, wrd); // compares the letters/ indexes
          // printing out all the previous tries
        listAttempts.push_back(fiveLetters);
        for (int i = 0; i < listAttempts.size(); i++){
          cout << listAttempts.at(i) << endl;
          
        }//comments and stats on performance
   attempt5comments(attempts,user_word,wrd,cg,streak,dictionarystreak,elapsedSeconds,startTime,timeDictionary);
      } 
      else { //if the word isnt in the dictionary
        cout <<endl<< "Not a playable word, please select another word.";
        attempts++;  // adds an attempt because invalid entries dont count
      }
    } 
    attempts --;
  }  
}

//carries the instructions for five letter words
void fiveLetterPlay(string guess,int &cg,int &streak, vector <int> &dictionarystreak,vector <string> fiveLetterDictionary,vector <int> &timeDictionary){
  cout<<"To get started, enter your first 5 letter word. \n"<<"You have 6 attempts to guess the random word. \n"<<"The timer will start after your first word entry. \n"<<"Try to guess the word within 40 seconds. \n";

  //has comments and compoarisons within the instructions
  instructions5(guess, cg,streak,dictionarystreak,fiveLetterDictionary,timeDictionary);
  cout<<endl<<endl;
 
}

////////////////////////////////////////////////////////////////////////////////////////

void gameDisplayInstructions(){
    cout << "Program 3: Wordle Reload \n"
        << "CS 141, Spring 2022, UIC \n"
        << " \n"
        << "The objective of this game is to guess the randomly selected \n"
        << "word within a given number of attempts. You can select either \n"
        << "a three or five word board. \n"
        << "At the conlusion of the game, stats will be displayed.  \n"
        << "Indicators will be given if characters of the user entered \n"
        << "word are reflected in the guessed word. \n"
        << "  - If the character is in the correct position, the character \n"
        << "    will display as an uppercase value.\n"
        << "  - If the character is within the random word, the character \n"
        << "    will display as a lowercase value.\n"
        << "  - If you enter a character that is not in the word, an asterisk '*' \n"
        << "    will display."
        << " \n"
        << endl;
}

//for entering menu options
void menuOptions(int &userInput){
cout<<"Select a menu option: \n"<<"   1. To play Wordle Reload 3 letter play \n"<<"   2. To play Wordle Reload 5 letter play \n"<<"   3. Exit the program \n"<<"Your choice --> ";
  cin >> userInput;
  cout << endl;
}

int main(){ 
  srand(0); //seeds to 1
  gameDisplayInstructions(); //displays instructions
  vector<string> fiveLetterDictionary;  // stores five letter words 
  vector<string> threeLetterDictionary;  // stores three letter words
  vector <int> dictionaryfortime;     //stores time 
  vector<int> dictionarycg;       //stores correct guesses
  vector<int> dictionarystreak; //stores streaks
  int game = 0; // keeps the while loop going 
  int menuOption;   
  int averageTime = 0;
  string guess1; // random guess for three letters 
  string guess2;  // random guess for five letters 
  int number = 0;   
  int streak = 0;
  int correctGuesses = 0; 
  
  getDictionaryVector(threeLetterDictionary,fiveLetterDictionary); //opens both dictionaries
  
  while (game == 0){
    menuOptions(menuOption);
   
    if(menuOption == 1){  // three letter word play
    random(number, threeLetterDictionary.size()); //random words for three letter words
    guess1 = threeLetterDictionary.at(number);  //random word to guess
      //call 3 letter part of the game
    threeLetterPlay(guess1,correctGuesses,streak,dictionarystreak,threeLetterDictionary,dictionaryfortime);
    }
    else if(menuOption == 2){ // five letter word play
      random(number, fiveLetterDictionary.size()); //random words for three letter words
      guess2 = fiveLetterDictionary.at(number); //random word to guess
      //call 5 letter part of the game
      fiveLetterPlay(guess2,correctGuesses,streak,dictionarystreak,fiveLetterDictionary,dictionaryfortime);
    }
    else if (menuOption == 3){  // exiting program with stats

      if (correctGuesses == 0){  // when not a single guess was correct or wasnt entered
        cout<<"Overall Stats: \n"<<"  - You guessed: "<<correctGuesses<<endl<<"  - Your longest streak is: "<<streak<<endl<<"  - Average word completion time:"<<"N/A"<<endl<<"Exiting program";
        game++; //end the game
        break; 
      }
      else{
      dictionarystreak.push_back(streak); //stores streaks
        //looping throught to find the largest streak
      for (int i = 0; i < dictionarystreak.size(); i++){
        if (streak < dictionarystreak.at(i)){      
          streak = dictionarystreak.at(i);
        }
      }  //looping through the stored time 
        for (int i = 0; i < dictionaryfortime.size(); i++){
          averageTime += dictionaryfortime.at(i);
        }   //finding the average time
        averageTime = averageTime / dictionaryfortime.size();
        
      cout<<"Overall Stats: \n"<<"  - You guessed: "<<correctGuesses<<endl<<"  - Your longest streak is: "<<streak<<endl<<"  - Average word completion time: "<<averageTime<<endl<<"Exiting program";
        game++;
        break; 
      }
    }
    else{
      game++; // ends while loop or game
    }
  }
  return 0;
}//end main()
