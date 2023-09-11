#include <iostream>
using namespace std;

int main(){
  int playerChoice;
  int computerChoice;

  /* seed the rng with current time
  before since it was pseudo random,
  it gave the same response which nullifies the game lol */
  std::srand(static_cast<unsigned int>(time(nullptr)));

  // choose num from 1-100
  computerChoice = std::rand() % 100 + 1;

  int guesses = 1;

  do{
    cout << "Guess What Number I'm Thinking of: ";
    cin >> playerChoice;

    if(playerChoice == computerChoice){
      cout << "Nice Job! My number was " << computerChoice << "\nYou got it in " << guesses << " guesses";
    } else if (playerChoice > computerChoice){
      cout << "My number is smaller!\n";
    } else if (playerChoice < computerChoice){
      cout << "My number is larger!\n";
    } else {cout << "how did you do this. this shouldnt happen\n";}
    ++guesses;
  } while (playerChoice != computerChoice);

  // normalize input
  playerChoice = std::toupper(playerChoice);
  return 0;
}
