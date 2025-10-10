#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include "mmsystem.h"
#include <thread>

using namespace std;

void clear(){
    #ifdef WIN32
	    system("CLS");
    #else
	    system("clear");
    #endif
}
int PlayerInput(int& Action){
    string PlayerInput;
    
    getline (cin, PlayerInput);
    cout << endl;

    if (PlayerInput == "0"){
        Action = 0;
    }else if (PlayerInput == "1" || PlayerInput == "01"){
        Action = 1;
    }else if (PlayerInput == "2" || PlayerInput == "02"){
        Action = 2;
    }else if (PlayerInput == "3" || PlayerInput == "03"){
        Action = 3;
    }else if (PlayerInput == "4" || PlayerInput == "04"){
        Action = 4;
    }else if (PlayerInput == "5" || PlayerInput == "05"){
        Action = 5;
    }else if (PlayerInput == "6" || PlayerInput == "06"){
        Action = 6;
    }else if (PlayerInput == "7" || PlayerInput == "07"){
        Action = 7;
    }else if (PlayerInput == "8" || PlayerInput == "08"){
        Action = 8;
    }else if (PlayerInput == "9" || PlayerInput == "09"){
        Action = 9;
    }else if (PlayerInput == "help" || PlayerInput == "Help" || PlayerInput == "HELP"){
        Action = 33;
    }else if (PlayerInput == "upupdowndownleftrightleftrightba"){
        Action = 999;
    }else{
        Action = -1;
    }

    return Action;
}

//     ________________________________________________________________
//     \ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /
//      |              _    __    ___    ___    __    _              |
//      |\ /\ /\  /\  / \  /  \  /   \  /   \  /  \  / \  /\  /\ /\ /|
//     _|____________________________________________________________|_
//     \ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /
//      |         _      __      ___      ___      __      _         |
//      |\  /\   / \    /  \    /   \    /   \    /  \    / \   /\  /|
//     _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_
//     \ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /
//      |         _      __      ___      ___      __      _         |
//      |\  /\   / \    /  \    /   \    /   \    /  \    / \   /\  /|
//     _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_
//     \ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /
//      |         _      __      ___      ___      __      _         |
//      |\  /\   / \    /  \    /   \    /   \    /  \    / \   /\  /|
//      || |  | |   |  |    |  |     |  |     |  |    |  |   | |  | ||
// _____||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_____

// cout << "\t            ..----..            " << endl;
// cout << "\t       .--''        ''--.       " << endl;
// cout << "\t     .'                  '.     " << endl;
// cout << "\t   .'   +----+----+----+   '.   " << endl;
// cout << "\t  :     |              |     :  " << endl;
// cout << "\t :      +    +    +    +      : " << endl;
// cout << "\t :      |              |      : " << endl;
// cout << "\t :      +    +    +    +      : " << endl;
// cout << "\t  :     |              |     :  " << endl;
// cout << "\t   '.   +----+----+----+   .'   " << endl;
// cout << "\t     '.                  .'     " << endl;
// cout << "\t       '--..        ..--'       " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t            :      :            " << endl;
// cout << "\t             '----'             " << endl;

void CollosseumRollSprites(int sprite, int interval){


    switch (sprite){
        case 1:
        cout << "    ________________________________________________________________" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |   __   ___    ____    _____    _____    ____    ___   __   |" << endl;
        cout << "     |\\ /  \\ /   \\  /    \\  /     \\  /     \\  /    \\  /   \\ /  \\ /|" << endl;
        cout << "    _|____________________________________________________________|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |         _      __      ___      ___      __      _         |" << endl;
        cout << "     |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|" << endl;
        cout << "    _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |         _      __      ___      ___      __      _         |" << endl;
        cout << "     |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|" << endl;
        cout << "    _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |         _      __      ___      ___      __      _         |" << endl;
        cout << "     |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|" << endl;
        cout << "     || |  | |   |  |    |  |     |  |     |  |    |  |   | |  | ||" << endl;
        cout << "_____||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_____" << endl;
        break;

        case 2:
        cout << "    ________________________________________________________________" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |  __   ___    ____    _____    _____    ____    ___   __   _|" << endl;
        cout << "     | /  \\ /   \\  /    \\  /     \\  /     \\  /    \\  /   \\ /  \\ / |" << endl;
        cout << "    _|____________________________________________________________|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |        _      __      ___      ___      __      _          |" << endl;
        cout << "     |  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\   /|" << endl;
        cout << "    _|_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_|_|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |        _      __      ___      ___      __      _          |" << endl;
        cout << "     |  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\   /|" << endl;
        cout << "    _|_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_|_|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |        _      __      ___      ___      __      _          |" << endl;
        cout << "     |  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\   /|" << endl;
        cout << "     | |  | |   |  |    |  |     |  |     |  |    |  |   | |  | | |" << endl;
        cout << "_____|_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_|_|_____" << endl;
        break;

        case 3:
        cout << "    ________________________________________________________________" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     | __   ___    ____    ____    _____    _____    ___   __   __|" << endl;
        cout << "     |/  \\ /   \\  /    \\  /    \\  /     \\  /     \\  /   \\ /  \\ /  |" << endl;
        cout << "    _|____________________________________________________________|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |       _      __      __      ___      ___      _           |" << endl;
        cout << "     | /\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\|" << endl;
        cout << "    _||__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |       _      __      __      ___      ___      _           |" << endl;
        cout << "     | /\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\|" << endl;
        cout << "    _||__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |       _      __      __      ___      ___      _           |" << endl;
        cout << "     | /\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\|" << endl;
        cout << "     ||  | |   |  |    |  |    |  |     |  |     |  |   | |  | |  |" << endl;
        cout << "_____||__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__|_____" << endl;
        break;

        case 4:
        cout << "    ________________________________________________________________" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |__   ___    ____    ____    _____    _____    ___   __   __ |" << endl;
        cout << "     |  \\ /   \\  /    \\  /    \\  /     \\  /     \\  /   \\ /  \\ /  \\|" << endl;
        cout << "    _|____________________________________________________________|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |      _      __      __      ___      ___      _            |" << endl;
        cout << "     |/\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\ |" << endl;
        cout << "    _|__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__||_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |      _      __      __      ___      ___      _            |" << endl;
        cout << "     |/\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\ |" << endl;
        cout << "    _|__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__||_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |      _      __      __      ___      ___      _            |" << endl;
        cout << "     |/\\   / \\    /  \\    /  \\    /   \\    /   \\    / \\   /\\   /\\ |" << endl;
        cout << "     |  | |   |  |    |  |    |  |     |  |     |  |   | |  | |  ||" << endl;
        cout << "_____|__|_|___|__|____|__|____|__|_____|__|_____|__|___|_|__|_|__||_____" << endl;
        break;

        case 5:
        cout << "    ________________________________________________________________" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |_   __    ___    ____    _____    _____    ____   ___   __  |" << endl;
        cout << "     | \\ /  \\  /   \\  /    \\  /     \\  /     \\  /    \\ /   \\ /  \\ |" << endl;
        cout << "    _|____________________________________________________________|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |           _      __      ___      ___      __     _        |" << endl;
        cout << "     |\\   /\\    / \\    /  \\    /   \\    /   \\    /  \\   / \\   /\\  |" << endl;
        cout << "    _|_|_|__|__|___|__|____|__|_____|__|_____|__|____|_|___|_|__|_|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |           _      __      ___      ___      __     _        |" << endl;
        cout << "     |\\   /\\    / \\    /  \\    /   \\    /   \\    /  \\   / \\   /\\  |" << endl;
        cout << "    _|_|_|__|__|___|__|____|__|_____|__|_____|__|____|_|___|_|__|_|_" << endl;
        cout << "    \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /" << endl;
        cout << "     |           _      __      ___      ___      __     _        |" << endl;
        cout << "     |\\   /\\    / \\    /  \\    /   \\    /   \\    /  \\   / \\   /\\  |" << endl;
        cout << "     | | |  |  |   |  |    |  |     |  |     |  |    | |   | |  | |" << endl;
        cout << "_____|_|_|__|__|___|__|____|__|_____|__|_____|__|____|_|___|_|__|_|_____" << endl;
        break;
    }
    usleep(interval);
    clear();
}
void ColosseumRoll(int Rolls, int interval){

    for (int l = 0; l < Rolls; l++){
        CollosseumRollSprites(1,interval);
        CollosseumRollSprites(2,interval);
        CollosseumRollSprites(3,interval);
        CollosseumRollSprites(4,interval);
        CollosseumRollSprites(5,interval);
    }
    clear();
}


void UPCardAquireAnimSprites(int sprite, int interval, bool Clear){
    switch (sprite){
        case 1:
        cout << "\t\t                .-------." << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                `-------`" << endl;
        break;
        case 2:
        cout << "\t\t                 .-----." << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 `-----`" << endl;
        break;
        case 3:
        cout << "\t\t                  .---." << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  `---`" << endl;
        break;
        case 4:
        cout << "\t\t                   .-." << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   `-`" << endl;
        break;
        case 5:
        cout << "\t\t                    ." << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    `" << endl;
        break;
        case 6:
        cout << "\t\t                   .-." << endl;
        cout << "\t\t                   |X|" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   |X|" << endl;
        cout << "\t\t                   `-`" << endl;
        break;
        case 7:
        cout << "\t\t                  .---." << endl; 
        cout << "\t\t                  |/ \\|" << endl;
        cout << "\t\t                  |.:.|" << endl;
        cout << "\t\t                  |':'|" << endl;
        cout << "\t\t                  |\\ /|" << endl;
        cout << "\t\t                  `---`" << endl;
        break;
        case 8:
        cout << "\t\t                 .-----." << endl;
        cout << "\t\t                 |/   \\|" << endl;
        cout << "\t\t                 |.-:-.|" << endl;
        cout << "\t\t                 |'-:-'|" << endl;
        cout << "\t\t                 |\\   /|" << endl;
        cout << "\t\t                 `-----`" << endl;
        break;
        case 9:
        cout << "\t\t                .-------." << endl;
        cout << "\t\t                |/     \\|" << endl;
        cout << "\t\t                | .-:-. |" << endl;
        cout << "\t\t                | '-:-' |" << endl;
        cout << "\t\t                |\\     /|" << endl;
        cout << "\t\t                `-------`" << endl;
        break;
        case 10:
        cout << "\t\t                    ." << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    `" << endl;
        break;
    }

    usleep(interval);
    if (Clear == true){
        clear();
    }
}

void UPCardAquireAnim(int loops, int interval, bool Clear){
    for (int l = 0; l < loops; l++){
        UPCardAquireAnimSprites(1, interval, Clear);
        UPCardAquireAnimSprites(2, interval, Clear);
        UPCardAquireAnimSprites(3, interval, Clear);
        UPCardAquireAnimSprites(4, interval, Clear);
        UPCardAquireAnimSprites(5, interval, Clear);
        UPCardAquireAnimSprites(6, interval, Clear);
        UPCardAquireAnimSprites(7, interval, Clear);
        UPCardAquireAnimSprites(8, interval, Clear);
        UPCardAquireAnimSprites(9, interval, Clear);
        UPCardAquireAnimSprites(8, interval, Clear);
        UPCardAquireAnimSprites(7, interval, Clear);
        UPCardAquireAnimSprites(6, interval, Clear);
        UPCardAquireAnimSprites(10, interval, Clear);
        UPCardAquireAnimSprites(4, interval, Clear);
        UPCardAquireAnimSprites(3, interval, Clear);
        UPCardAquireAnimSprites(2, interval, Clear);
    }
    if (Clear == true){
        clear();
    }
}

void ADNAnimSprites(int sprite, int interval, bool Clear){
    switch (sprite){
        case 0:
        cout << "\t\t               |         |" << endl;
        cout << "\t\t               |         |" << endl;
        cout << "\t\t               |         |" << endl;
        cout << "\t\t               |         |" << endl;
        cout << "\t\t               |         |" << endl;
        cout << "\t\t               |         |" << endl;
        break;
        case 1:
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        cout << "\t\t                |       |" << endl;
        break;
        case 2:
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        cout << "\t\t                 |     |" << endl;
        break;
        case 3:
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        cout << "\t\t                  |   |" << endl;
        break;
        case 4:
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        cout << "\t\t                   | |" << endl;
        break;
        case 5:
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        cout << "\t\t                    |" << endl;
        break;
    }

    usleep(interval);
    if (Clear == true){
        clear();
    }
}

void ADNAnim(int loops, int interval, bool Clear){
    for (int l = 0; l < loops; l++){
        ADNAnimSprites(0, interval, Clear);
        ADNAnimSprites(1, interval, Clear);
        ADNAnimSprites(2, interval, Clear);
        ADNAnimSprites(3, interval, Clear);
        ADNAnimSprites(4, interval, Clear);
        // ADNAnimSprites(5, interval, Clear);
        // ADNAnimSprites(4, interval, Clear);
        ADNAnimSprites(3, interval, Clear);
        ADNAnimSprites(2, interval, Clear);
        ADNAnimSprites(1, interval, Clear);
    }
    if (Clear == true){
        clear();
    }
}


void BattlegateAnim(){
    const int total = 21;
    int space = total - 1;
    int lenght = 2;

    while(space != 0){
        for (int l = 0; l < space; l++){
            cout << endl;
        }

        cout << "\t\t";

        for (int c = 0; c < space; c++){
                cout << " ";
            }

            cout << " ";

            for (int c = 0; c < (total - space) / 4; c++){
                cout << "_";
            }
            for (int i = 0; i < lenght * (total - space); i++){
                cout << "_";
            }
            for (int c = 0; c < (total - space) / 4; c++){
                cout << "_";
            }
            
            for (int c = 0; c < (total - space) / 8; c++){
                cout << endl;
                cout << "\t\t";
                for (int c = 0; c < space; c++){
                    cout << " ";
                }
                cout << "|";
                for (int c = 0; c < (total - space) / 4; c++){
                    cout << " ";
                }
                for (int i = 0; i < lenght * (total - space); i++){
                    cout << " ";
                }
                for (int c = 0; c < (total - space) / 4; c++){
                    cout << " ";
                }
                cout << "|";
            }
            cout << endl;

        for (int l = 0; l < total - space; l++){//#
            cout << "\t\t";
            for (int c = 0; c < space; c++){
                cout << " ";
            }
            cout << "|";
            for (int c = 0; c < (total - space) / 4; c++){
                cout << " ";
            }
            for (int i = 0; i < lenght * (total - space); i++){
                cout << "\033[47m \033[0m";
            }
            for (int c = 0; c < (total - space) / 4; c++){
                cout << " ";
            }
            cout << "|" << endl;
        }

        for (int l = 0; l < (total - space)/3.5; l++){//:
            cout << "\t\t";
            for (int c = 0; c < (total - space) / 4; c++){
                cout << " ";
            }
            cout << " ";
            for (int c = 0; c < space; c++){
                cout << " ";
            }
            for (int i = 0; i < lenght * (total - space); i++){
                cout << ":";
            }
            cout << endl;
        }
        space--;
        usleep(50000 + (space*space*space*30));
        clear();
    }

}


void ArmageddonAnimSprites(int sprite, string colorbg, string colorbeam, int interval){
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "                    " << endl;
    // cout << "  _________      ___" << endl;
    // cout << "  |= = = = \\''''/ =|" << endl;
    // cout << "  |{}_{}_{}_\\_/{}_{|" << endl;
    // cout << "  |_{}_{}_{}_{}_{}_|" << endl;
    // cout << "  |.-. .-.  .-. .-.|" << endl;
    // cout << "  || |_| |__| |_| ||" << endl;
    // cout << "" << endl;
    // cout << "" << endl;

    switch(sprite){
        case 1:// << "\t\t\t\t"
        cout << "\t\t\t\t" << colorbg;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "                    " << endl;
        cout << "\t\t\t\t" << "  _________      ___" << endl;
        cout << "\t\t\t\t" << "  |= = = = \\''''/ =|" << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\_/{}_{|" << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|" << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|" << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << "" << endl;
        cout << "\t\t\t\t" << "" << endl;
        break;
        case 2:
        cout << "" << colorbg;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "          ||        " << endl;
        cout << "\t\t\t\t" << "  ________||     ___" << endl;
        cout << "\t\t\t\t" << "  |= = = = \\''''/ =|" << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\_/{}_{|" << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|" << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|" << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << "" << endl;
        cout << "\t\t\t\t" << "" << endl;
        break;
        case 3:
        cout << "" << colorbg;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "          "<<colorbeam<<"  "<<colorbg<<"        " << endl;
        cout << "\t\t\t\t" << "  ________"<<colorbeam<<"  "<<colorbg<<"     ___" << endl;
        cout << "\t\t\t\t" << "  |= = = = \\''''/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\_/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << "" << endl;
        cout << "\t\t\t\t" << "" << endl;
        break;
        case 4:
        cout << colorbg;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "         "<<colorbeam<<"    "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "  _______"<<colorbeam<<"    "<<colorbg<<"    ___" << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<" "<<colorbg<<"'''/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\_/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << "  '''  '''  '''  ''' " << endl;
        cout << "\t\t\t\t" << "                      " << endl;
        break;
        case 5:
        cout << colorbg;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "       "<<colorbeam<<"        "<<colorbg<<"       " << endl;
        cout << "\t\t\t\t" << "  _____"<<colorbeam<<"        "<<colorbg<<"  ___  " << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<"  "<<colorbg<<"''/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\"<<colorbeam<<" "<<colorbg<<"/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << " .::'  :::  :::  '::. " << endl;
        cout << "\t\t\t\t" << "                      " << endl;
        break;
        case 6:
        cout << colorbg;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "  ____"<<colorbeam<<"          "<<colorbg<<"____  " << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<"    "<<colorbg<<"/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\"<<colorbeam<<" "<<colorbg<<"/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << " .::'  :::  :::  '::. " << endl;
        cout << "\t\t\t\t" << "'''   '''    '''   '''" << endl;
        break;
        case 7:
        cout << colorbg; // "<<colorbeam<<"
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "  ___"<<colorbeam<<"            "<<colorbg<<"___  " << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<"    "<<colorbg<<"/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\"<<colorbeam<<" "<<colorbg<<"/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << " .::'  :::  :::  '::. " << endl;
        cout << "\t\t\t\t" << "'''   '''    '''   '''" << endl;
        break;
        case 8:
        cout << colorbg;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "  __"<<colorbeam<<"              "<<colorbg<<"__  " << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<"    "<<colorbg<<"/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\"<<colorbeam<<" "<<colorbg<<"/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << " .::'  :::  :::  '::. " << endl;
        cout << "\t\t\t\t" << "'''   '''    '''   '''" << endl;
        break;
        case 9:
        cout << colorbg;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "      "<<colorbeam<<"          "<<colorbg<<"      " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "     "<<colorbeam<<"            "<<colorbg<<"     " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "    "<<colorbeam<<"              "<<colorbg<<"    " << endl;
        cout << "\t\t\t\t" << "  ___"<<colorbeam<<"            "<<colorbg<<"___  " << endl;
        cout << "\t\t\t\t" << "  |= = = = \\"<<colorbeam<<"    "<<colorbg<<"/ =|  " << endl;
        cout << "\t\t\t\t" << "  |{}_{}_{}_\\"<<colorbeam<<" "<<colorbg<<"/{}_{|  " << endl;
        cout << "\t\t\t\t" << "  |_{}_{}_{}_{}_{}_|  " << endl;
        cout << "\t\t\t\t" << "  |.-. .-.  .-. .-.|  " << endl;
        cout << "\t\t\t\t" << " _|| |_| |__| |_| ||_ " << endl;
        cout << "\t\t\t\t" << " .::'  :::  :::  '::. " << endl;
        cout << "\t\t\t\t" << "'''   '''    '''   '''" << endl;
        break;
    }
    usleep(interval);
    clear();
}
void ArmageddonAnim(string color, int tmult){
    clear();

    ArmageddonAnimSprites(1,"\033[0m",color, 1000000);
    for (int l = 0; l < 15; l++){
        ArmageddonAnimSprites(1,"\033[0m",color, 10000 * tmult);
        ArmageddonAnimSprites(2,"\033[0m",color, 10000 * tmult);
    }
    ArmageddonAnimSprites(3,"\033[0m",color, 20000 * tmult);
    ArmageddonAnimSprites(4,"\033[0m",color, 20000 * tmult);
    ArmageddonAnimSprites(5,color,"\033[0m", 20000 * tmult);

    ArmageddonAnimSprites(6,"\033[0m",color, 20000 * tmult);
    ArmageddonAnimSprites(7,color,"\033[0m", 20000 * tmult);
    ArmageddonAnimSprites(8,"\033[0m",color, 20000 * tmult);
    ArmageddonAnimSprites(9,color,"\033[0m", 20000 * tmult);
    for (int l = 0; l < 10; l++){
        ArmageddonAnimSprites(6,color,"\033[0m", 60000 * tmult);
        ArmageddonAnimSprites(7,color,"\033[0m", 60000 * tmult);
        ArmageddonAnimSprites(8,color,"\033[0m", 60000 * tmult);
        ArmageddonAnimSprites(9,color,"\033[0m", 60000 * tmult);
    }
    ArmageddonAnimSprites(6,"\033[0m",color, 70000 * tmult);
    ArmageddonAnimSprites(7,"\033[0m",color, 80000 * tmult);
    ArmageddonAnimSprites(8,"\033[0m",color, 90000 * tmult);
    ArmageddonAnimSprites(9,"\033[0m",color, 100000 * tmult);

    ArmageddonAnimSprites(6,"\033[0m",color, 110000 * tmult);
    ArmageddonAnimSprites(7,"\033[0m",color, 120000 * tmult);
    ArmageddonAnimSprites(8,"\033[0m",color, 130000 * tmult);
    ArmageddonAnimSprites(9,"\033[0m",color, 140000 * tmult);

    ArmageddonAnimSprites(5,"\033[0m",color, 150000 * tmult);
    ArmageddonAnimSprites(4,"\033[0m",color, 160000 * tmult);
    ArmageddonAnimSprites(3,"\033[0m",color, 180000 * tmult);
    ArmageddonAnimSprites(2,"\033[0m",color, 50000 * tmult);
    for (int l = 0; l < 4; l++){
        ArmageddonAnimSprites(2,"\033[0m",color, 50000 + (l*10000 * tmult));
        ArmageddonAnimSprites(1,"\033[0m",color, 50000 + (l*10000 * tmult));
    }
    ArmageddonAnimSprites(1,"\033[0m",color, 5000000);
}


//--------LOCKPICK MINIGAMES------------------------------------------------------------------------------------------------------------------------------------#

string Lockpicktick(bool option, string number){
    if (option == true){
        return "\033[1;93m" + number + "\033[0m";
    }else{
        return "\033[90m" + number + "\033[0m";
    }
    return "ER";
}
bool boolswitch(bool& variable){
    if (variable == true){
        variable = false;
    }else{
        variable = true;
    }
    return variable;
}

//| " << Lockpicktick(switches[1], "01") << "   " << Lockpicktick(switches[2], "02") << "   " << Lockpicktick(switches[3], "03") << " |"
void LockpickGame1UI(bool switches[], int tries){
    cout << "Lockpick Strenght:" << endl;
    cout << "     ["; for (int l = 0; l < tries; l++){cout << "\033[1;93m#\033[0m";} cout << "]" << endl;
    cout << "\t            ..----..   "          << "\033[90m(Turn them all \033[93mYELLOW\033[90m to unlock)\033[0m" << endl;
    cout << "\t       .--''        ''--.       " << endl;
    cout << "\t     .'                  '.     " << endl;
    cout << "\t   .'   +----+----+----+   '.   " << endl;
    cout << "\t  :     | " << Lockpicktick(switches[1], "01") << "   " << Lockpicktick(switches[2], "02") << "   " << Lockpicktick(switches[3], "03") << " |     :  " << endl;
    cout << "\t :      +    +    +    +      : " << endl;
    cout << "\t :      | " << Lockpicktick(switches[4], "04") << "   " << Lockpicktick(switches[5], "05") << "   " << Lockpicktick(switches[6], "06") << " |      : " << endl;
    cout << "\t :      +    +    +    +      : " << endl;
    cout << "\t  :     | " << Lockpicktick(switches[7], "07") << "   " << Lockpicktick(switches[8], "08") << "   " << Lockpicktick(switches[9], "09") << " |     :  " << endl;
    cout << "\t   '.   +----+----+----+   .'   " << endl;
    cout << "\t     '.                  .'     " << endl;
    cout << "\t       '--..        ..--'       " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t             '----'             " << endl;
}
void LockpickGame1(){
    int input, Tries = 18;
    bool Switches[] = {false, true, false, true, false, true, false, true, false, true};

    while (true){
        clear();

        LockpickGame1UI(Switches, Tries);
        cout << "You: ";
        PlayerInput(input);
        Tries--;

        switch (input){
            case 1:
            boolswitch(Switches[1]);
            boolswitch(Switches[2]);
            boolswitch(Switches[4]);
            break;

            case 2:
            boolswitch(Switches[2]);
            boolswitch(Switches[1]);
            boolswitch(Switches[3]);
            boolswitch(Switches[5]);
            break;

            case 3:
            boolswitch(Switches[3]);
            boolswitch(Switches[2]);
            boolswitch(Switches[6]);
            break;

            case 4:
            boolswitch(Switches[4]);
            boolswitch(Switches[1]);
            boolswitch(Switches[7]);
            boolswitch(Switches[5]);
            break;

            case 5:
            boolswitch(Switches[5]);
            boolswitch(Switches[2]);
            boolswitch(Switches[4]);
            boolswitch(Switches[6]);
            boolswitch(Switches[8]);
            break;

            case 6:
            boolswitch(Switches[6]);
            boolswitch(Switches[3]);
            boolswitch(Switches[5]);
            boolswitch(Switches[9]);
            break;

            case 7:
            boolswitch(Switches[7]);
            boolswitch(Switches[4]);
            boolswitch(Switches[8]);
            break;

            case 8:
            boolswitch(Switches[8]);
            boolswitch(Switches[7]);
            boolswitch(Switches[5]);
            boolswitch(Switches[9]);
            break;

            case 9:
            boolswitch(Switches[9]);
            boolswitch(Switches[8]);
            boolswitch(Switches[6]);
            break;

            default:
            cout << "Invalid choice";
            Tries++;
            sleep(1);
            clear();
            break;
        }

        if (Switches[1] == true && Switches[2] == true && Switches[3] == true && 
            Switches[4] == true && Switches[5] == true && Switches[6] == true &&
             Switches[7] == true && Switches[8] == true && Switches[9] == true)
             {
                clear();
                LockpickGame1UI(Switches, Tries);
                sleep(1);
                cout << "You unlocked the door" << endl;
                sleep(2);
                break;
            }else if(Tries <= 0){
                clear();
                LockpickGame1UI(Switches, Tries);
                sleep(1);
                cout << "\n\t The Lockpick Broke";
                sleep(2);
                break;
            }

    }
}

void LockpickGame2UI(bool switches[], int tries){
    cout << "Lockpick Strenght:" << endl;
    cout << "     ["; for (int l = 0; l < tries; l++){cout << "\033[1;93m#\033[0m";} cout << "]" << endl;
    cout << "\t            ..----..   "          << "\033[90m(Turn them all \033[93mYELLOW\033[90m to unlock)\033[0m" << endl;
    cout << "\t       .--''        ''--.       " << endl;
    cout << "\t     .'                  '.     " << endl;
    cout << "\t   .'                      '.   " << endl;
    cout << "\t  :   +----+----+----+----+  :  " << endl;
    cout << "\t :    | " << Lockpicktick(switches[1], "01") << "   " << Lockpicktick(switches[2], "02") << "   " << Lockpicktick(switches[3], "03") << "   " << Lockpicktick(switches[4], "04") << " |   : " << endl;
    cout << "\t :    +    +    +    +    +   : " << endl;
    cout << "\t :    | " << Lockpicktick(switches[5], "05") << "   " << Lockpicktick(switches[6], "06") << "   " << Lockpicktick(switches[7], "07") << "   " << Lockpicktick(switches[8], "08") << " |   : " << endl;
    cout << "\t  :   +----+----+----+----+  :  " << endl;
    cout << "\t   '.                      .'   " << endl;
    cout << "\t     '.                  .'     " << endl;
    cout << "\t       '--..        ..--'       " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t             '----'             " << endl;
}
void LockpickGame2(){
    int input, Tries = 22;
    bool Switches[] = {false, false, true, true, true, false, false, true, false, true};

    while (true){
        clear();

        LockpickGame2UI(Switches, Tries);
        cout << "You: ";
        cin >> input;
        Tries--;

        switch (input){
            case 1:
            boolswitch(Switches[1]);
            boolswitch(Switches[2]);
            boolswitch(Switches[5]);
            break;

            case 2:
            boolswitch(Switches[2]);
            boolswitch(Switches[1]);
            boolswitch(Switches[3]);
            boolswitch(Switches[6]);
            break;

            case 3:
            boolswitch(Switches[3]);
            boolswitch(Switches[2]);
            boolswitch(Switches[7]);
            boolswitch(Switches[4]);
            break;

            case 4:
            boolswitch(Switches[4]);
            boolswitch(Switches[8]);
            boolswitch(Switches[3]);
            break;

            case 5:
            boolswitch(Switches[5]);
            boolswitch(Switches[6]);
            boolswitch(Switches[1]);
            break;

            case 6:
            boolswitch(Switches[6]);
            boolswitch(Switches[2]);
            boolswitch(Switches[5]);
            boolswitch(Switches[7]);
            break;

            case 7:
            boolswitch(Switches[7]);
            boolswitch(Switches[3]);
            boolswitch(Switches[6]);
            boolswitch(Switches[8]);
            break;

            case 8:
            boolswitch(Switches[8]);
            boolswitch(Switches[7]);
            boolswitch(Switches[4]);
            break;

            default:
            cout << "Invalid choice";
            Tries++;
            sleep(1);
            clear();
            break;
        }

        if (Switches[1] == true && Switches[2] == true && Switches[3] == true && 
            Switches[4] == true && Switches[5] == true && Switches[6] == true &&
             Switches[7] == true && Switches[8] == true)
             {
                clear();
                LockpickGame2UI(Switches, Tries);
                sleep(1);
                cout << "You unlocked the door" << endl;
                sleep(2);
                break;
            }else if(Tries <= 0){
                clear();
                LockpickGame2UI(Switches, Tries);
                sleep(1);
                cout << "\n\t The Lockpick Broke";
                sleep(2);
                break;
            }

    }
}

void LockpickGame3UI(bool switches[], int tries){
    cout << "Lockpick Strenght:" << endl;
    cout << "     ["; for (int l = 0; l < tries; l++){cout << "\033[1;93m#\033[0m";} cout << "]" << endl;
    cout << "\t            ..----..   "          << "\033[90m(Turn them all \033[93mYELLOW\033[90m to unlock)\033[0m" << endl;
    cout << "\t       .--''        ''--.       " << endl;
    cout << "\t     .' +----+----+      '.     " << endl;
    cout << "\t   .'   | " << Lockpicktick(switches[1], "01") << "   " << Lockpicktick(switches[2], "02") << " |        '.   " << endl;
    cout << "\t  :     +    +    +          :  " << endl;
    cout << "\t :      | " << Lockpicktick(switches[3], "03") << "   " << Lockpicktick(switches[4], "04") << " |           : " << endl;
    cout << "\t :      +----+    +----+      : " << endl;
    cout << "\t :           | " << Lockpicktick(switches[5], "05") << "   " << Lockpicktick(switches[6], "06") << " |      : " << endl;
    cout << "\t  :          +    +    +     :  " << endl;
    cout << "\t   '.        | " << Lockpicktick(switches[7], "07") << "   " << Lockpicktick(switches[8], "08") << " |   .'   " << endl;
    cout << "\t     '.      +----+----+ .'     " << endl;
    cout << "\t       '--..        ..--'       " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t            :      :            " << endl;
    cout << "\t             '----'             " << endl;
}
void LockpickGame3(){
    int input, Tries = 20;
    bool Switches[] = {false, false, true, true, true, false, false, true, false, true};

    while (true){
        clear();

        LockpickGame3UI(Switches, Tries);
        cout << "You: ";
        cin >> input;
        Tries--;

        switch (input){
            case 1:
            boolswitch(Switches[1]);
            boolswitch(Switches[2]);
            boolswitch(Switches[3]);
            break;

            case 2:
            boolswitch(Switches[2]);
            boolswitch(Switches[1]);
            boolswitch(Switches[4]);
            break;

            case 3:
            boolswitch(Switches[3]);
            boolswitch(Switches[1]);
            boolswitch(Switches[4]);
            break;

            case 4:
            boolswitch(Switches[4]);
            boolswitch(Switches[2]);
            boolswitch(Switches[3]);
            boolswitch(Switches[5]);
            break;

            case 5:
            boolswitch(Switches[5]);
            boolswitch(Switches[6]);
            boolswitch(Switches[4]);
            boolswitch(Switches[7]);
            break;

            case 6:
            boolswitch(Switches[6]);
            boolswitch(Switches[8]);
            boolswitch(Switches[5]);
            break;

            case 7:
            boolswitch(Switches[7]);
            boolswitch(Switches[5]);
            boolswitch(Switches[8]);
            break;

            case 8:
            boolswitch(Switches[8]);
            boolswitch(Switches[7]);
            boolswitch(Switches[6]);
            break;

            default:
            cout << "Invalid choice";
            Tries++;
            sleep(1);
            clear();
            break;
        }

        if (Switches[1] == true && Switches[2] == true && Switches[3] == true && 
            Switches[4] == true && Switches[5] == true && Switches[6] == true &&
             Switches[7] == true && Switches[8] == true)
             {
                clear();
                LockpickGame3UI(Switches, Tries);
                sleep(1);
                cout << "You unlocked the door" << endl;
                sleep(2);
                break;
            }else if(Tries <= 0){
                clear();
                LockpickGame3UI(Switches, Tries);
                sleep(1);
                cout << "\n\t The Lockpick Broke";
                sleep(2);
                break;
            }

    }
}


void Starwalker(){
    cout << "                \033[43m  \033[0m" << endl;
    cout << "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "                  \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "    \033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m" << endl;
    cout << "\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[47m  \033[0m" << endl;
    cout << "    \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[43m  \033[0m" << endl;
    cout << "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[43m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
    cout << "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m" << endl;
}

void ChampionAppearAnimSprites(int sprite, int interval){
    clear();
    cout << "\033[1;95m";
    switch (sprite){
        case 0:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "                                           " << endl;
        cout << "                                        " << endl;
        cout << "                                        " << endl;
        cout << "                                        " << endl;
        cout << "                                      " << endl;
        cout << "                                 " << endl;
        cout << "                   < >             " << endl;
        cout << "                                " << endl;
        cout << "                                 " << endl;
        cout << "                                  " << endl;
        cout << "                                  " << endl;
        cout << "                               " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 1:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "                                           " << endl;
        cout << "                                        " << endl;
        cout << "                                        " << endl;
        cout << "                                        " << endl;
        cout << "                '       '               " << endl;
        cout << "                  \\ ^ /            " << endl;
        cout << "                  < x >              " << endl;
        cout << "                  / v \\         " << endl;
        cout << "                .       .         " << endl;
        cout << "                                  " << endl;
        cout << "                                  " << endl;
        cout << "                               " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 2:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "                                           " << endl;
        cout << "                                        " << endl;
        cout << "                                        " << endl;
        cout << "                    '                   " << endl;
        cout << "                    |                  " << endl;
        cout << "                  . ^ .            " << endl;
        cout << "              - - < + > - -          " << endl;
        cout << "                  ' v '         " << endl;
        cout << "                    |            " << endl;
        cout << "                    .             " << endl;
        cout << "                                  " << endl;
        cout << "                               " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 3:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "                                           " << endl;
        cout << "                                        " << endl;
        cout << "                    |                   " << endl;
        cout << "                   |.|                   " << endl;
        cout << "                  |.:.|                " << endl;
        cout << "           ..   .' ::: '.   ..          " << endl;
        cout << "           : '-'::::|::::'-' :        " << endl;
        cout << "            '-._ '::|::' _.-'    " << endl;
        cout << "                '. ::: .'  " << endl;
        cout << "                  |':'|          " << endl;
        cout << "                   |'|            " << endl;
        cout << "                    |             " << endl;
        cout << "                               " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 4:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "                      " << endl;
        cout << "                    |                      " << endl;
        cout << "                   |:|                   " << endl;
        cout << "                  |.:.|                   " << endl;
        cout << "                 | ::: |                 " << endl;
        cout << "        '.     .'  :|:  '.     .'         " << endl;
        cout << "        : '---'.::::|::::.'---' :    " << endl;
        cout << "        '.':::::|||||||||:::::'.'      " << endl;
        cout << "          ''--. '::|||::' .--''  " << endl;
        cout << "               '.  :|:  .'       " << endl;
        cout << "                 | ::: |            " << endl;
        cout << "                  |':'|          " << endl;
        cout << "                   |:|          " << endl;
        cout << "                    |" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 5:
        cout << "                      " << endl;
        cout << "                    |          " << endl;
        cout << "                 | .:. |              " << endl;
        cout << "                   :::                       " << endl;
        cout << "     .          |  :|:  |          .       " << endl;
        cout << "         .         :|:         .           " << endl;
        cout << "    |       '  '   :|:   '  '       |      " << endl;
        cout << "       :.          |||          .:              " << endl;
        cout << "    '  ':::|||:.. .|||. ..:|||:::'  '           " << endl;
        cout << "      .    ':|||||||||||||||:'    .        " << endl;
        cout << "          .    ':|||||||:'    .        " << endl;
        cout << "             .    '|||'    .        " << endl;
        cout << "               .   |||   .           " << endl;
        cout << "                   :|:               " << endl;
        cout << "                |  :|:  |           " << endl;
        cout << "                   :::  " << endl;
        cout << "                 | ':' |           " << endl;
        cout << "                    |                       " << endl;
        cout << "                                       " << endl;
        break;
        case 6:
        cout << "                    |              " << endl;
        cout << "                                       " << endl;
        cout << "               |   .|.   |                   " << endl;
        cout << "                   :|:                       " << endl;
        cout << "   '   .      |    :|:    |      .   '       " << endl;
        cout << "           '       |||       '              " << endl;
        cout << "  |                |||                |      " << endl;
        cout << "       :.          |||          .:              " << endl;
        cout << "  .    '::|||||.. .|||. ..|||||::'    .           " << endl;
        cout << "           ':|||||||||||||||:'             " << endl;
        cout << "    '          '|||||||||'          '     " << endl;
        cout << "       '          '|||'          '      " << endl;
        cout << "          '        |||        '       " << endl;
        cout << "             '     |||     '         " << endl;
        cout << "              |    :|:    |           " << endl;
        cout << "                   :|:                    " << endl;
        cout << "               |   '|'   |           " << endl;
        cout << "                                           " << endl;
        cout << "                    |                  " << endl;
        break;
        case 7:
        cout << "                    '              " << endl;
        cout << "                                       " << endl;
        cout << "             .     .|.     .                 " << endl;
        cout << "                   |||                       " << endl;
        cout << "            .      |||      .                " << endl;
        cout << ".                  |||                  .   " << endl;
        cout << "                   |||                       " << endl;
        cout << "       :.          |||          .:              " << endl;
        cout << "       '|||||||.. .|||. ..|||||||'                " << endl;
        cout << "           '|||||||||||||||||'             " << endl;
        cout << "               '|||||||||'                " << endl;
        cout << "                  '|||'                 " << endl;
        cout << "                   |||                " << endl;
        cout << "                   |||               " << endl;
        cout << "            '      |||      '         " << endl;
        cout << "                   |||                    " << endl;
        cout << "             '     '|'     '         " << endl;
        cout << "                                           " << endl;
        cout << "                    .                  " << endl;
        break;
        case 8:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "                   .|." << endl;
        cout << "                   |||                       " << endl;
        cout << "                   |||                     " << endl;
        cout << "                   |||                     " << endl;
        cout << "                   |||                     " << endl;
        cout << "       |.          |||          .|              " << endl;
        cout << "       '|||||||.. .|||. ..|||||||'              " << endl;
        cout << "           '|||||||||||||||||'             " << endl;
        cout << "               '|||||||||'             " << endl;
        cout << "                  '|||'             " << endl;
        cout << "                   |||               " << endl;
        cout << "                   |||               " << endl;
        cout << "                   |||             " << endl;
        cout << "                   |||" << endl;
        cout << "                   '|'" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 9:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "                   |                        " << endl;
        cout << "                   ||                     " << endl;
        cout << "                   ||                     " << endl;
        cout << "                   ||                     " << endl;
        cout << "          |        ||        .|              " << endl;
        cout << "          '||||..  ||. ..||||'              " << endl;
        cout << "              '||||||||||'              " << endl;
        cout << "                  '||'              " << endl;
        cout << "                   ||              " << endl;
        cout << "                   ||               " << endl;
        cout << "                   ||               " << endl;
        cout << "                   ||             " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 10:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "                |                        " << endl;
        cout << "                 |.                    " << endl;
        cout << "                 ||                     " << endl;
        cout << "                  ||                     " << endl;
        cout << "          |.      ||         .|              " << endl;
        cout << "          '||||.  ||.  ..|||'              " << endl;
        cout << "              '||||||||||'              " << endl;
        cout << "                  ||'              " << endl;
        cout << "                  ||              " << endl;
        cout << "                  ||               " << endl;
        cout << "                  ||               " << endl;
        cout << "                   |_              " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 11:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "               \\                        " << endl;
        cout << "                |                     " << endl;
        cout << "                ||                     " << endl;
        cout << "                 ||                     " << endl;
        cout << "           |     ||         .|              " << endl;
        cout << "           '|||  ||.   ..|||'              " << endl;
        cout << "              '||||||||||'              " << endl;
        cout << "                  ||'              " << endl;
        cout << "                  ||              " << endl;
        cout << "                  ||               " << endl;
        cout << "                  ||               " << endl;
        cout << "                   ||_              " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 12:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "              \\                        " << endl;
        cout << "               |                     " << endl;
        cout << "               ||                     " << endl;
        cout << "                ||                     " << endl;
        cout << "            |   ||          .|              " << endl;
        cout << "            '||  ||.   ..||||'              " << endl;
        cout << "              '||||||||||'              " << endl;
        cout << "                  ||'              " << endl;
        cout << "                  ||              " << endl;
        cout << "                   ||              " << endl;
        cout << "                   ||              " << endl;
        cout << "                    ||_              " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        default:
        break;
    }
    cout << "\033[0m";
    usleep(interval);
}
void ChampionAppearAnim(){
    ChampionAppearAnimSprites(0,100000);
    ChampionAppearAnimSprites(1,100000);
    ChampionAppearAnimSprites(2,100000);
    ChampionAppearAnimSprites(1,100000);
    ChampionAppearAnimSprites(2,100000);
    ChampionAppearAnimSprites(1,100000);
    ChampionAppearAnimSprites(0,100000);
    ChampionAppearAnimSprites(999,100000);

    ChampionAppearAnimSprites(0,100000);
    ChampionAppearAnimSprites(1,90000);
    ChampionAppearAnimSprites(2,80000);
    ChampionAppearAnimSprites(1,70000);
    ChampionAppearAnimSprites(2,80000);
    ChampionAppearAnimSprites(3,100000);
    ChampionAppearAnimSprites(4,100000);
    ChampionAppearAnimSprites(5,100000);
    ChampionAppearAnimSprites(6,100000);
    ChampionAppearAnimSprites(7,100000);
    ChampionAppearAnimSprites(8,300000);
    ChampionAppearAnimSprites(9,100000);
    ChampionAppearAnimSprites(10,100000);
    ChampionAppearAnimSprites(11,100000);
    ChampionAppearAnimSprites(12,100000);
}

int main(){

//UPCardAquireAnim(800, 80000, true);
//ADNAnim(800, 80000, false);
//ColosseumRoll(800, 40000);
//BattlegateAnim();
//LockpickGame1();
//ArmageddonAnim("\033[47;30m", 1);
//Starwalker();
ChampionAppearAnim();

}
// \033[47m
// \033[0m
// Name            FG  BG
// Black           30  40
// Red             31  41
// Green           32  42
// Yellow          33  43
// Blue            34  44
// Magenta         35  45
// Cyan            36  46
// White           37  47
// Bright Black    90  100
// Bright Red      91  101
// Bright Green    92  102
// Bright Yellow   93  103
// Bright Blue     94  104
// Bright Magenta  95  105
// Bright Cyan     96  106
// Bright White    97  107