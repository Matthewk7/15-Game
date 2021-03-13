/* Name: Matthew Kale, 5005997901, Assignment #1
 * Description: Program to play the game 15 puzzle
 * Input: Starting board file and game moves
 * Output: Game board and steps to play
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "LL.h"

using namespace std;

int main(){
    bool playGame = true;

    while (playGame == true){
            
        // Get input file
        string puzzleFile;
        ifstream infile;

        // Repeat until file is opened
        do {
            cout << endl << "Enter puzzle file: ";
            cin >> puzzleFile;
            infile.open(puzzleFile);
        } while (!infile.is_open());

        // Create the array of the linked list
        LL<int> board[4];
        int value = 0;
        for(int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                infile >> value;
                board[i].tailInsert(value);
            }
        }

        // Iterator
        LL<int>::iterator it;
        LL<int>::iterator tempIt;

        char selection;
        bool invalid = true;
        bool zeroFound = false;
        bool gameOver = false;
        int temp = 0;
        int temp2 = 0;
        
        while(gameOver == false){
            do{
                // Print out the linked list
                cout << endl;
                for(int i = 0; i < 4; i++){
                    it = board[i].begin();
                    for (int j = 0; j < 4; j++){
                        if (*it == 0){
                            cout << setw(4) << right << "-";
                        }
                        else{
                            cout << setw(4) << right << *it;
                        }
                        it++;    
                    }
                    cout << endl;
                }
                cout << endl;

                cout << "Please make your choice, (L)eft, (R)ight, (U)p, (D)own, (Q)uit: ";
                cin >> selection;
                selection = toupper(selection);
                
                switch (selection)
                {
                case 'L':
                    // Traverse Linked list
                    for(int i = 0; i < 4; i++){
                        it = board[i].begin();
                        for (int j = 0; j < 3; j++){
                            // If node is 0
                            if (*it == 0){
                                zeroFound = true;
                                break;
                            }
                            zeroFound = false;
                            it++;    
                        }
                        if (zeroFound == true){
                            break;
                        }  
                    }

                    // Swap with next node if zero is found
                    if (zeroFound == true){
                        temp = *it;
                        temp2 = *it++;

                        board[0].update(it, temp);
                        board[0].update(it--, temp2);
                    }

                    break;
                
                case 'R':
                    // Traverse Linked list
                    for(int i = 0; i < 4; i++){
                        it = board[i].begin();
                        it++;
                        for (int j = 0; j < 3; j++){
                            // If node is 0
                            if (*it == 0){
                                zeroFound = true;
                                break;
                            }
                            zeroFound = false;
                            it++;    
                        }
                        if (zeroFound == true){
                            break;
                        }  
                    }

                    // Swap with previous node if zero is found
                    if (zeroFound == true){                
                        temp = *it;
                        temp2 = *it--;

                        board[0].update(it, temp);
                        board[0].update(it++, temp2);
                    }

                    break;
                
                case 'U':
                    // Traverse Linked list
                    for(int i = 0; i < 3; i++){
                        it = board[i].begin();
                        tempIt = board[i+1].begin();
                        for (int j = 0; j < 4; j++){
                            // If node is 0
                            if (*it == 0){
                                zeroFound = true;
                                break;
                            }
                            zeroFound = false;
                            it++;    
                            tempIt++;
                        }
                        if (zeroFound == true){
                            break;
                        }  
                    }  
                    // Swap with node below if zero is found
                    if (zeroFound == true){                
                        temp = *it;

                        board[0].update(it, *tempIt);
                        board[0].update(tempIt, temp);
                    }


                    break;
                case 'D': 
                    // Traverse Linked list
                    for(int i = 1; i < 4; i++){
                        it = board[i].begin();
                        tempIt = board[i-1].begin();
                        for (int j = 0; j < 4; j++){
                            // If node is 0
                            if (*it == 0){
                                zeroFound = true;
                                break;
                            }
                            zeroFound = false;
                            it++;    
                            tempIt++;
                        }
                        if (zeroFound == true){
                            break;
                        }  
                    }  
                    // Swap with node below if zero is found
                    if (zeroFound == true){                
                        temp = *it;

                        board[0].update(it, *tempIt);
                        board[0].update(tempIt, temp);
                    }

                    break;

                case 'Q':
                    cout << "Quitter..." << endl;
                    return 0;
                    break;
                default:
                    cout << "Invalid selection!" << endl << endl;
                    invalid = true;
                }

            } while (invalid == false);

            gameOver = true;
            for (int i = 0; i < 4; i++){
                it = board[i].begin();
                for (int j = 0; j < 4; j++){
                    if (*it == 0 && ((i * 4) + j) + 1 == 16){
                        continue;
                    }
                    else{ 
                        if (*it != ((i * 4) + j) + 1){
                            gameOver = false;
                        }
                        it++;
                    }

                }

            }
        }

        // Print out the linked list
        cout << endl;
        for(int i = 0; i < 4; i++){
            it = board[i].begin();
            for (int j = 0; j < 4; j++){
                if (*it == 0){
                    cout << setw(4) << right << "-";
                }
                else{
                    cout << setw(4) << right << *it;
                }
                it++;    
            }
            cout << endl;
        }
        cout << endl;

        cout << "You Win!!!" << endl << endl;

        cout << "Play again? (Y/N): ";
        char playAgain;
        cin >> playAgain;
    
        playAgain = toupper(playAgain);

        if (playAgain == 'N'){
            cout << endl << endl;
            playGame = false;
            cout << "Yeah I don't blame you for not wanting to play anymore" << endl;
            cout << "This game is like league...except it actually makes sense :D" << endl << endl;
        }
        else{
            cout << endl;
            playGame = true;
        }
    }

    // 12. If the game is over, output that the user won ask them if they wish to continue, they must enter Y or
    //     N (case insensitive), repeat this step if Y or N is not entered

    // 13. If N was entered, terminate the program, if Y was entered go to step 1
}