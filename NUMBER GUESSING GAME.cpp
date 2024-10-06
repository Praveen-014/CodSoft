#include <iostream>
#include <cstdlib>  
#include <ctime>   
using namespace std;
int main() 
{
    srand(static_cast<unsigned int>(time(0)));
    int randomNumber = rand() % 100 + 1;  
    int userGuess = 0;  
    cout << "Welcome to the Guess the Number game!" << endl;
    cout << "I have picked a number between 1 and 100. Try to guess it!" << endl;

        while (true)
 {
        cout << "Enter your guess: ";
        cin >> userGuess;
        if (userGuess > randomNumber)
 {
            cout << "Too high! Try again." << endl;
        } 
            else if (userGuess < randomNumber) 
{
            cout << "Too low! Try again." << endl;
        }
 else
 {
            cout << "Congratulations! You guessed the correct number!" << endl;
            break;          }
    }

    return 0;
}
