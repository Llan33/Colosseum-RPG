#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include "mmsystem.h"

#pragma comment(lib, "Winmm.lib" );

using namespace std;

//- GLOBAL VARIABLES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

int Chance, Damage;
int WaveRound = 1, TotalRound = 1, Wave = 1, Floor = 0;
bool PlayerTurn;
bool GameOver = false, ExitGame = false;

    //Event Variables (Global)
    bool PrisonLoreCheck = false;

//- General Functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
void clear(){
    #ifdef WIN32
	    system("CLS");
    #else
	    system("clear");
    #endif
}
void Enter(){
    cout << "PRESS ENTER:";
	cin.ignore();
    cin.get();
	clear();
}
void EnterShort(){
    cout << "PRESS ENTER:";
    cin.get();
	clear();
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
    }else if (PlayerInput == "upupdowndownleftrightleftrightba" || PlayerInput == "upupdowndownleftrightleftrightBA"){
        Action = 999;
    }else if (PlayerInput == "Starwalker" || PlayerInput == "starwalker"){
        Action = 1225;
    }else{
        Action = -1;
    }

    return Action;
}

void ScreenFlash(int FlashLoops){
    clear();
    for (int l = 0; l < FlashLoops; l++){
        for(int i = 0; i < 300; i++){
            cout << "\033[47m                                            \033[0m";
        }
        usleep(50000);
        clear();
        usleep(50000);
    }
    sleep(1);
}
//- Text Icons - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
string XX(){
    return "\033[1;91mXX\033[0m";
}
string YX(){
    return "\033[1;93mXX\033[0m";
}
string PX(){
    return "\033[1;95mXX\033[0m";
}
string Pos(){
    return "\033[1;92m[]\033[0m";
}

string Red(string input){
    string text = "\033[91m" + input + "\033[0m";
    return text;
}
string Green(string input){
    string text = "\033[92m" + input + "\033[0m";
    return text;
}
string Cyan(string input){
    string text = "\033[96m" + input + "\033[0m";
    return text;
}
string Yellow(string input){
    string text = "\033[93m" + input + "\033[0m";
    return text;
}
string Purple(string input){
    string text = "\033[95m" + input + "\033[0m";
    return text;
}
string Blue(string input){
    string text = "\033[94m" + input + "\033[0m";
    return text;
}
string Gray(string input){
    string text = "\033[90m" + input + "\033[0m";
    return text;
}


string RandColor(){
    int random;
    random = rand() % 6 + 1;
    switch (random){
        case 1:
        return "\033[91m";

        case 2:
        return "\033[92m";

        case 3:
        return "\033[93m";

        case 4:
        return "\033[94m";

        case 5:
        return "\033[95m";

        case 6:
        return "\033[96m";
    }

    return "\033[95m";
}

string goldshow(){
    return "\033[33mg\033[0m";
}
string tokensshow(){
    return "\033[95mTokens\033[0m";
}
string hpshow(){
    return "\033[91mHP\033[0m";
}
string manashow(){
    return "\033[94mMana\033[0m";
}
string atkshow(){
    return "\033[91mATK\033[0m";
}
string acshow(){
    return "\033[90mAC\033[0m";
}
string mashow(){
    return "\033[92mMA\033[0m";
}
string critshow(){
    return "\033[31mCRIT\033[0m";
}
string dodgeshow(){
    return "\033[93mDODGE\033[0m";
}

//- OPTIONS MENU - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
    //Option Variables (Global)
    bool Introskip = false;

string ONOFFtick(bool option){// true = ON; false = OFF
    if (option == true){
        return "\033[1;93mON\033[0m/\033[90mOFF\033[0m";
    }else{
        return "\033[90mON\033[0m/\033[1;93mOFF\033[0m";
    }
    return "ON/OFF";
}

bool boolswitch(bool& variable){
    if (variable == true){
        variable = false;
    }else{
        variable = true;
    }
    return variable;
}

void OptionsUI(){
    cout << "|------------<OPTIONS>------------|" << endl;
    cout << "" << endl;
    cout << "            Skip Intro: " << ONOFFtick(Introskip) << endl;
    cout << "               (1)" << endl;
    cout << "                          " << endl;
    cout << " Still gotta do the rest of this :P" << endl;
    cout << "                                    " << endl;
    cout << "                                   " << endl;
    cout << "|-- 0 > Go Back ------------------|" << "\n\n";
}
void Options(){
    
    clear();
    int Action;
    bool validchoice = false;

    while(true){

        OptionsUI();

        cout << "You: ";
        PlayerInput(Action);

        switch (Action){
            case 0:
            validchoice = true;
            break;

            case 1:
            boolswitch(Introskip);
            break;

            default:
            invalid:
            cout << "Invalid choice";
            sleep (1);
            clear();
            break;
        }

        clear();

        if (validchoice == true){
            break;
        }
    }
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
//- ANIMATIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void ClassMenuUIAnim(){
    string CLASS;
    for (int l = 0; l < 40; l++){
        cout << "           ";
        for (int i = 0; i < 40 - l; i++){
            cout << " ";
        }
        cout << "{";

        int change = 0;
        for (int i = 0; i < l; i++){
            change++;
        if (change > 4){
            change = 1;
        }
            switch (change) {
                case 2:
                cout << ".";
                break;

                case 4:
                cout << "'";
                break;

                default:
                cout << "-";
                break;
            }
        }
        switch (l){
            case 4:
            CLASS = "\033[1;37mC\033[0m";
            break;

            case 8:
            CLASS = "\033[1;37mCL\033[0m";
            break;

            case 12:
            CLASS = "\033[1;37mCLA\033[0m";
            break;

            case 17:
            CLASS = "\033[1;37mCLAS\033[0m";
            break;

            case 22:
            CLASS = "\033[1;37mCLASS\033[0m";
            break;

            case 28:
            CLASS = "\033[1;37mCLASSE\033[0m";
            break;

            case 35:
            CLASS = "\033[1;37mCLASSES\033[0m";
            break;
        }

        cout << CLASS;
        change = 0;
        for (int i = 0; i < l; i++){
            change++;
        if (change > 4){
            change = 1;
        }
            switch (change) {
                case 2:
                cout << ".";
                break;

                case 4:
                cout << "'";
                break;

                default:
                cout << "-";
                break;
            }
        }

        cout << "}";
        usleep(10000 - (l * 175));
        clear();
    }
    if (true){
    cout << "           {-.-'-.-'-.-'-.-'-.'-.-'-.-'-.-'-.-'-.-'-.-\033[1;37mCLASSES\033[0m-.-'-.-'-.-'-.-'-.'-.-'-.-'-.-'-.-'-.-'-.-}" << "\n\n";
    usleep(35000);
    cout << " .-----------------------.    .-----------------------.    .-----------------------.    .-----------------------. " << endl;
    usleep(32000);
    cout << "/                         \\  /                         \\  /                         \\  /                         \\" << endl;
    usleep(30000);
    cout << "| _______________________ |  | _______________________ |  | _______________________ |  | _______________________ |" << endl;
    usleep(29000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(28000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(27000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(26000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(25000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(22000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(21000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(19000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(17000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(15000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(13000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(11000);
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    usleep(9000);
    cout << "\\'''''''''''''''''''''''''/  \\'''''''''''''''''''''''''/  \\'''''''''''''''''''''''''/  \\'''''''''''''''''''''''''/" << endl;
    usleep(7000);
    cout << " '-----------------------'    '-----------------------'    '-----------------------'    '-----------------------' " << endl;
    usleep(5000);
    clear();
    for(int i = 0; i < 300; i++){
        cout << "\033[47m                                            \033[0m";
    }
    usleep(50000);
    clear();
    }
}

void LevelUPAnimSprites(int sprite){
    switch (sprite){
        case 1:
        cout << "\n\n\n\n\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 2:
        cout << "\n\n\n\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 3:
        cout << "\n\n\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << "-'-.-'-.-'-.-'-.-|       | -----   \\    /   | ----- |            |        | |_____/-'-.-'-.-'-.-'-.-" << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 4:
        cout << "\n\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |       |       \\        / |       |            |        |  _____                  " << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << ".-'-.-'-.-'-.-'-.|       | -----   \\    /   | ----- |            |        | |_____/.-'-.-'-.-'-.-'-." << endl;
        cout << "                 |       |          \\  /    |       |            |        | |                       " << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 5:
        cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |        ______             ______              |        |                         " << endl;
        cout << "                 |       |       \\        / |       |            |        |  _____                  " << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << "-.-'-.-'-.-'-.-'-|       | -----   \\    /   | ----- |            |        | |_____/-.-'-.-'-.-'-.-'-" << endl;
        cout << "                 |       |          \\  /    |       |            |        | |                       " << endl;
        cout << "                 |______ |______     \\/     |______ |_____        \\______/  |                       " << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 6:
        cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |        ______             ______              |        |                         " << endl;
        cout << "                 |       |       \\        / |       |            |        |  _____                  " << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << "'-.-'-.-'-.-'-.-'|       | -----   \\    /   | ----- |            |        | |_____/'-.-'-.-'-.-'-.-'" << endl;
        cout << "                 |       |          \\  /    |       |            |        | |                       " << endl;
        cout << "                 |______ |______     \\/     |______ |_____        \\______/  |                       " << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 7:
        cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |        ______             ______              |        |                         " << endl;
        cout << "                 |       |       \\        / |       |            |        |  _____                  " << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << "-'-.-'-.-'-.-'-.-|       | -----   \\    /   | ----- |            |        | |_____/-'-.-'-.-'-.-'-.-" << endl;
        cout << "                 |       |          \\  /    |       |            |        | |                       " << endl;
        cout << "                 |______ |______     \\/     |______ |_____        \\______/  |                       " << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;

        case 8:
        cout << "\n\n";
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        cout << "                 |        ______             ______              |        |                         " << endl;
        cout << "                 |       |       \\        / |       |            |        |  _____                  " << endl;
        cout << "                 |       |        \\      /  |       |            |        | |     \\                 " << endl;
        cout << ".-'-.-'-.-'-.-'-.|       | -----   \\    /   | ----- |            |        | |_____/.-'-.-'-.-'-.-'-." << endl;
        cout << "                 |       |          \\  /    |       |            |        | |                       " << endl;
        cout << "                 |______ |______     \\/     |______ |_____        \\______/  |                       " << endl;
        cout << "----------------------------------------------------------------------------------------------------" << endl;
        break;
    }
}
void LevelUPAnim(){
    cout << "\n\n\n\n\n\n";
    for (int l = 0; l < 33; l++){
        cout << "---";
        usleep(1000);
    }
    usleep(10000); clear();

    LevelUPAnimSprites(1); usleep(10000); clear(); 
    LevelUPAnimSprites(2); usleep(10000); clear(); cout << "\033[1;92m";
    LevelUPAnimSprites(3); usleep(10000); clear(); cout << "\033[0m";
    LevelUPAnimSprites(4); usleep(10000); clear(); cout << "\033[1;92m";
    for (int l = 0; l < 7; l++){
        LevelUPAnimSprites(5); usleep(10000); clear(); cout << "\033[0m";
        LevelUPAnimSprites(6); usleep(10000); clear(); cout << "\033[1;92m";
        LevelUPAnimSprites(7); usleep(10000); clear(); cout << "\033[0m";
        LevelUPAnimSprites(8); usleep(10000); clear(); cout << "\033[1;92m";
    }
    LevelUPAnimSprites(4); usleep(10000); clear(); cout << "\033[0m";
    LevelUPAnimSprites(3); usleep(10000); clear();
    LevelUPAnimSprites(2); usleep(10000); clear();
    LevelUPAnimSprites(1); usleep(10000); clear();


}

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

void UPCardAquireAnimSprites(int sprite, int interval, bool Clear, bool Shop, int& Spaces){
    if (Shop == true){
        if (Spaces % 2 == 0){
            cout << RandColor();
        }
            cout << endl << "\t\t~ ~~ ~~~ UP CARD BOOST ACQUIRED ~~~ ~~  ~\033[0m" << "\n\n";
            for (int l = 0; l < Spaces; l++){
                //if (l % 2 != 0){
                    cout << endl;
                //}
            }
            Spaces--;
    }
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
void UPCardAquireAnim(int loops, int interval, bool Clear, bool Shop){

        int Spaces = loops * 16;

        if (Shop == true){
            clear();
            cout << endl;
            cout << "\t\t~ ~~ ~~~ UP CARD BOOST ACQUIRED ~~~ ~~  ~" << "\n\n";
            for (int l = 0; l < Spaces; l++){
                cout << endl;
            }
            cout << "\t\t                .-------." << endl;
            cout << "\t\t                |       |" << endl;
            cout << "\t\t                |       |" << endl;
            cout << "\t\t                |       |" << endl;
            cout << "\t\t                |       |" << endl;
            cout << "\t\t                `-------`" << endl;
            usleep(30000);
            clear();
        }

        for (int l = 0; l < loops; l++){
        UPCardAquireAnimSprites(1, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(2, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(3, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(4, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(5, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(6, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(7, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(8, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(9, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(8, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(7, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(6, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(10, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(4, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(3, interval, Clear, Shop, Spaces);
        UPCardAquireAnimSprites(2, interval, Clear, Shop, Spaces);
    }
    if (Clear == true){
        clear();
    }
}

void BossIncomingUI(){
    for (int l = 0; l < 12; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << "\033[1;91m";
        }else{
            cout << "\033[1;37m";
        }
        cout << "\t+-|-_____ - -____- - ____- -____- - - ___-___- ___ -____ - ____- ___- - ___-___-___- ___ -____-|-+" << endl;
        cout << "\t' | |    \\  /    \\  /    \\ /    \\      |   |\\   |  /      /    \\  |\\    /|   |   |\\   |  /     | ." << endl;
        cout << "\t' | |____/ |      | \\___   \\___        |   | \\  | |      |      | | \\  / |   |   | \\  | |  __  | ." << endl;
        cout << "\t' | |    \\ |      |      \\      \\      |   |  \\ | |      |      | |  \\/  |   |   |  \\ | |    \\ | ." << endl;
        cout << "\t' * |____/  \\____/  \\____/ \\____/     _|_ _|_  \\|  \\____  \\____/ _|_    _|_ _|_ _|_  \\|  \\___/ * ." << endl;
        cout << "\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+\033[0m" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}


void ChampionIncomingUI(){
    for (int l = 0; l < 18; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << "\033[1;95m";
        }else{
            cout << "\033[1;90m";
        }
        cout << "\t+- _______-___ -___-_____- - - ____-___- ___ - __- -___- - ___-_____ -_____- ____- ___ -___-+" << endl;
        cout << "\t'     |     |    |  |         /      |    |   /  \\   |\\    /|  |    \\   |   /    \\  |\\   |  ." << endl;
        cout << "\t'     |     |____|  |____    |       |____|  |____|  | \\  / |  |____/   |  |      | | \\  |  ." << endl;
        cout << "\t'     |     |    |  |        |       |    |  |    |  |  \\/  |  |        |  |      | |  \\ |  ." << endl;
        cout << "\t'     |    _|_  _|_ |____     \\____ _|_  _|_ |    | _|_    _|_ |      __|__ \\____/ _|_  \\|  ." << endl;
        cout << "\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}
void KingsIncomingUI(){
    for (int l = 0; l < 18; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << "\033[1;93m";
        }else{
            cout << RandColor();
        }
        cout << "\t\t+- _______-___ -___-_____- -___  __ _____-___  ___ -____- -____- - -+" << endl;
        cout << "\t\t'     |     |    |  |        |  /     |    |\\   |  /      /    \\    ." << endl;
        cout << "\t\t'     |     |____|  |____    |_/      |    | \\  | |   __  \\____     ." << endl;
        cout << "\t\t'     |     |    |  |        | \\      |    |  \\ | |     |      \\    ." << endl;
        cout << "\t\t'     |    _|_  _|_ |____   _|_ \\__ __|__ _|_  \\|  \\____/ \\____/    ." << endl;
        cout << "\t\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +\033[0m" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}
void KingAidenIncomingUI(){
    for (int l = 0; l < 18; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << "\033[1;93m";
        }else{
            cout << RandColor();
        }
        cout << "\t\t+- -___  __ _____-___  ___ -____- - - -__ - _____ -___ - _____-___- ___- - +" << endl;
        cout << "\t\t'    |  /     |    |\\   |  /          /  \\    |   |   \\  |      |\\   |     ." << endl;
        cout << "\t\t'    |_/      |    | \\  | |   __     |____|   |   |    \\ |____  | \\  |     ." << endl;
        cout << "\t\t'    | \\      |    |  \\ | |     |    |    |   |   |    / |      |  \\ |     ." << endl;
        cout << "\t\t'   _|_ \\__ __|__ _|_  \\|  \\____/    |    | __|__ |___/  |____ _|_  \\|     ." << endl;
        cout << "\t\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+\033[0m" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}
void KingAddisonIncomingUI(){
    for (int l = 0; l < 18; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << "\033[1;93m";
        }else{
            cout << RandColor();
        }
        cout << "\t+- -___  __ _____-___  ___ -____- - - -__- - ___ - -___- -_____- ____ - -____- -___ -___- +" << endl;
        cout << "\t'    |  /     |    |\\   |  /          /  \\  |   \\  |   \\    |   /    \\  /    \\   |\\   |   ." << endl;
        cout << "\t'    |_/      |    | \\  | |   __     |____| |    \\ |    \\   |   \\____  |      |  | \\  |   ." << endl;
        cout << "\t'    | \\      |    |  \\ | |     |    |    | |    / |    /   |        \\ |      |  |  \\ |   ." << endl;
        cout << "\t'   _|_ \\__ __|__ _|_  \\|  \\____/    |    | |___/  |___/  __|__ \\____/  \\____/  _|_  \\|   ." << endl;
        cout << "\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - - - - - - - - - -+\033[0m" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}


void RelicDropPopupUI(){
        for (int l = 0; l < 12; l++){
        cout << "\n\n\n\033[1;37m";
        cout << "\t\t+- ____ - ____- - - -___ - -____- - - ___ - -____ - -____ - -____- +" << endl;
        cout << "\t\t' |    \\ |     |      |    /         |   \\  |    \\  /    \\  |    \\ ." << endl;
        cout << "\t\t' |____/ |___  |      |   |          |    \\ |____/ |      | |____/ ." << endl;
        cout << "\t\t' |  \\   |     |      |   |          |    / |  \\   |      | |      ." << endl;
        cout << "\t\t' |   \\_ |____ |____ _|_   \\____     |___/  |   \\_  \\____/  |      ." << endl;
        cout << "\t\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+\033[0m" << endl;
        usleep(40000);
        clear();
        usleep(40000);
    }
}

void ExtraTurnPopupUI(){
    clear();
        for (int l = 0; l < 18; l++){
        cout << "\n\n\n";
        if (l % 2 == 0){
            cout << RandColor();
        }else{
            cout << "\033[1;30m";
        }
        cout << "\t\t+- _____-__- __-_______ -____- - __- - -_______- _ - - _ -____ -___- ___ +" << endl;
        cout << "\t\t'  |      \\  /     |    |    \\  /  \\       |     |     | |    \\  |\\   |  ." << endl;
        cout << "\t\t'  |____   \\/      |    |____/ |____|      |     |     | |____/  | \\  |  ." << endl;
        cout << "\t\t'  |       /\\      |    |  \\   |    |      |     |     | |  \\    |  \\ |  ." << endl;
        cout << "\t\t'  |____ _/  \\_    |    |   \\_ |    |      |      \\___/  |   \\_ _|_  \\|  ." << endl;
        cout << "\t\t+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
        usleep(30000);
        clear();
        usleep(30000);
    }
}

void ColosseumImage(int Floor){

    cout << "     \033[1;37m_______________________                                _________  " << endl;
    cout << "     \\ _______ ___ __ __ _  \\\033[90m------------------------------\033[1;37m/_______ /  " << endl;
    cout << "      |              _    __ \\\033[90m.    ..    ..    ..    .. \033[1;37m__/        |   " << endl;
    if (Floor == 3){
    cout << "      |\\ /\\ /\\  /\\  / \\  /  \\ \\\033[90m:  :  :  :  :  :  :  :\033[1;37m__//\\  /\\ /\\ /|    <--- \033[1;4;93mYou\033[0;1;37m" << endl;
    }else{
    cout << "      |\\ /\\ /\\  /\\  / \\  /  \\ \\\033[90m:  :  :  :  :  :  :  :\033[1;37m__//\\  /\\ /\\ /|   " << endl;
    }
    cout << "     _|________________________\\\033[90m--------------------\033[1;37m/______________|_  " << endl;
    cout << "     \\ _______ ___ __ __ _ _  _ \\__\033[90m..    ..    .. \033[1;37m_/_ __ ___ ______ /  " << endl;
    cout << "      |         _      __      ___ \\_\033[90m:  :  :  :  \033[1;37m/_      _         |   " << endl;
    if (Floor == 2){
    cout << "      |\\  /\\   / \\    /  \\    /   \\  \\\033[90m----------\033[1;37m/  \\    / \\   /\\  /|    <--- \033[1;4;93mYou\033[0;1;37m" << endl;
    }else{
    cout << "      |\\  /\\   / \\    /  \\    /   \\  \\\033[90m----------\033[1;37m/  \\    / \\   /\\  /|   " << endl;
    }
    cout << "     _||_|__|_|___|__|____|__|_____|__\\\033[90m .. \033[1;37m_\033[90m  .\033[1;37m/____|__|___|_|__|_||_  " << endl;
    cout << "     \033[1;37m\\ _______ ___ __ __ _ _  _   _    \\__/ \\_/ _ __ __ ___ _______ /  " << endl;
    cout << "      |         _      __      ___      ___      __      _         |   " << endl;
    if (Floor == 1){
    cout << "      |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|    <--- \033[1;4;93mYou\033[0;1;37m" << endl;
    }else{
    cout << "      |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|   " << endl;
    }
    cout << "     _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_  " << endl;
    cout << "     \\ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /  " << endl;
    cout << "      |         _      __      ___      ___      __      _         |   " << endl;
    cout << "      |\\  /\\   / \\    /  \\    /   \\    /   \\    /  \\    / \\   /\\  /|   " << endl;
    if (Floor == 0){
    cout << "      || |  | |   |  |    |  |     |  |     |  |    |  |   | |  | ||    <--- \033[1;4;93mYou\033[0;1;37m" << endl;
    }else{
    cout << "      || |  | |   |  |    |  |     |  |     |  |    |  |   | |  | ||" << endl;
    }
    cout << " _ ___||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||___ _\033[0m" << "\n\n";

}
void ColosseumRoundBar(int WaveRound, int Wave, int Floor){

//                                                                   
//    +''''+         +''''+         +''''+         +''''+         |\_/\_/|
//    |    | - - - - |    | - - - - |    | - - - - |    | - - - - |      |
//    +....+         +....+         +....+         +....+         '------'
//    Round 1        Round 2        Round 3        Round 4         *KING*

    switch (Floor){
        case 0:
            if (Wave == 6){
                    cout << "                                                              '-\033[1;95m|\\__/|\033[0m-'" << endl;
                    cout << "    +-  -+         +-  -+         +-  -+         +-  -+        '\033[1;95m/    \\\033[0m' " << endl;
                switch (WaveRound){
                case 1:
                cout << "    | "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;95m\\    / \033[0m" << endl;
                break;

                case 2:
                cout << "    | "<< PX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;95m\\    / \033[0m" << endl;
                break;

                case 3:
                cout << "    | "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;95m\\    / \033[0m" << endl;
                break;

                case 4:
                cout << "    | "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[1;95m\\    / \033[0m" << endl;
                break;

                case 5:
                cout << "    | "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[0m| "<< PX() <<" |\033[1m - - - - \033[1;95m\\ \033[0m"<< Pos() <<" \033[1;95m/ \033[0m" << endl;
                break;
                }
                    cout << "    +-  -+         +-  -+         +-  -+         +-  -+         '\033[1;95m\\__/\033[0m'  " << endl;
                    cout << "    Round 1        Round 2        Round 3        Round 4       \033[1;95mCHAMPION\033[0m   " << endl;
            }else{
                    cout << "                                                                 ____  " << endl;
                    cout << "    +-  -+         +-  -+         +-  -+         +-  -+         /    \\ " << endl;
                switch (WaveRound){
                case 1:
                cout << "    | "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 2:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 3:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 4:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 5:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m\\ "<< Pos() <<" / " << endl;
                break;
                }
                    cout << "    +-  -+         +-  -+         +-  -+         +-  -+          \\__/  " << endl;
                    cout << "    Round " << Cyan("1") << "        Round " << Green("2") << "        Round " << Yellow("3") << "        Round " << Purple("4") << "         " << Red("BOSS") << "   " << endl;
            }
        break;

        case 1:
                    cout << "                                                                 |" << Yellow("F1") << "|" << endl;
                    cout << "    +~  ~+         +~  ~+         +~  ~+         +~  ~+         /'--'\\ " << endl;
                switch (WaveRound){
                case 1:
                cout << "    | "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 2:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 3:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 4:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 5:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m\\ "<< Pos() <<" / " << endl;
                break;
                }
                    cout << "    +~  ~+         +~  ~+         +~  ~+         +~  ~+          \\__/" << endl;
                    cout << "    Round " << Cyan("1") << "        Round " << Green("2") << "        Round " << Yellow("3") << "        Round " << Purple("4") << "         " << Yellow("BOSS") << "   " << endl;
        break;

        case 2:
                    cout << "                                                                 |" << Yellow("F2") << "|" << endl;
                    cout << "    +~  ~+         +~  ~+         +~  ~+         +~  ~+         /'--'\\ " << endl;
                switch (WaveRound){
                case 1:
                cout << "    | "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 2:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 3:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 4:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m\\    / " << endl;
                break;

                case 5:
                cout << "    | "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m| "<< XX() <<" |\033[1m - - - - \033[0m\\ "<< Pos() <<" / " << endl;
                break;
                }
                    cout << "    +~  ~+         +~  ~+         +~  ~+         +~  ~+          \\__/" << endl;
                    cout << "    Round " << Cyan("1") << "        Round " << Green("2") << "        Round " << Yellow("3") << "        Round " << Purple("4") << "         " << Yellow("BOSS") << "   " << endl;
        break;

        case 3:
                    cout << "                                                                        " << endl;
                    cout << "    +''''+         +''''+         +''''+         +''''+         \033[1;93m|\\_/\\_/|\033[0m" << endl;
                switch (WaveRound){
                case 1:
                cout << "    | "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;93m|      |\033[0m" << endl;
                break;

                case 2:
                cout << "    | "<< YX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;93m|      |\033[0m" << endl;
                break;

                case 3:
                cout << "    | "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[0m|    |\033[90m - - - - \033[1;93m|      |\033[0m" << endl;
                break;

                case 4:
                cout << "    | "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[0m| "<< Pos() <<" |\033[90m - - - - \033[1;93m|      |\033[0m" << endl;
                break;

                case 5:
                cout << "    | "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[0m| "<< YX() <<" |\033[1m - - - - \033[1;93m|  \033[0m"<< Pos() <<"\033[1;93m  |\033[0m" << endl;
                break;
                }
                    cout << "    +....+         +....+         +....+         +....+         \033[1;93m'------'\033[0m" << endl;
                    cout << "    Round " << Yellow("1") << "        Round " << Yellow("2") << "        Round " << Yellow("3") << "        Round " << Yellow("4") << "          \033[1;93mKING\033[0m" << endl;
        break;
    }

}
void ColosseumRound(int WaveRound, int Wave, int Floor){
//
//             ~~~~~ ~~~~ ~~~ ~~ ~ WAVE 1 ~ ~~ ~~~ ~~~~ ~~~~~
//
//     _______________________                                _________
//     \ _______ ___ __ __ _  \------------------------------/_______ /
//      |              _    __ \.    ..    ..    ..    .. __/        |
//      |\ /\ /\  /\  / \  /  \ \:  :  :  :  :  :  :  :__//\  /\ /\ /|
//     _|________________________\--------------------/______________|_
//     \ _______ ___ __ __ _ _  _ \__..    ..    .. _/_ __ ___ ______ /
//      |         _      __      ___ \_:  :  :  :  /_      _         |
//      |\  /\   / \    /  \    /   \  \----------/  \    / \   /\  /|
//     _||_|__|_|___|__|____|__|_____|__\ .. _  ./____|__|___|_|__|_||_
//     \ _______ ___ __ __ _ _  _   _    \__/ \_/ _ __ __ ___ _______ /
//      |         _      __      ___      ___      __      _         |
//      |\  /\   / \    /  \    /   \    /   \    /  \    / \   /\  /|
//     _||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||_
//     \ _______ ___ __ __ _ _  _   _    _   _  _ _ __ __ ___ _______ /
//      |         _      __      ___      ___      __      _         |
//      |\  /\   / \    /  \    /   \    /   \    /  \    / \   /\  /|
//      || |  | |   |  |    |  |     |  |     |  |    |  |   | |  | ||    <--- You
// _ ___||_|__|_|___|__|____|__|_____|__|_____|__|____|__|___|_|__|_||___ _
//
//                                                                 ____  
//    +-  -+         +-  -+         +-  -+         +-  -+         /    \ 
//    |    | - - - - |    | - - - - |    | - - - - |    | - - - - \    / 
//    +-  -+         +-  -+         +-  -+         +-  -+          \__/  
//    Round 1        Round 2        Round 3        Round 4         BOSS  
    clear();
    cout << endl;
    if (Floor == 0){
        if (Wave == 6){
            cout << "\033[1;95m"<< "             ~~~~~ ~~~~ ~~~ ~~ ~FINAL WAVE~ ~~ ~~~ ~~~~ ~~~~~" << endl;
        }else{
            cout << RandColor() << "             ~~~~~ ~~~~ ~~~ ~~ ~ WAVE " << Wave << " ~ ~~ ~~~ ~~~~ ~~~~~" << endl;
        }
    }else if (Floor == 3){
        cout << "\033[1;93m"<<     "             ----- ---- --- -- |\\ KING'S FLOOR /| -- --- ---- -----" << endl;
    }else {
        cout << RandColor() <<     "             ----- ---- --- -- - FLOOR " << Floor << " - -- --- ---- -----" << endl;
    }

    ColosseumImage(Floor);

    ColosseumRoundBar(WaveRound, Wave, Floor);

    usleep(300000);
    cout << endl << "Ready to Fight?" << endl;
    EnterShort();

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
        usleep(50000 + (space*space*space*space));
        clear();
    }

}

void D6Roll(){
    for (int l = 0; l < 40; l++){
        Chance = rand() % 6 + 1;
        clear();
        cout << "\n\n\n\n";
        switch (Chance){

            case 1:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t|         |" << endl;
            cout << "\t\t\t|\033[30m    *    \033[0m|" << endl;
            cout << "\t\t\t|         |" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;

            case 2:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t|       * |" << endl;
            cout << "\t\t\t|         |" << endl;
            cout << "\t\t\t| *       |" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;

            case 3:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t|       * |" << endl;
            cout << "\t\t\t|    *    |" << endl;
            cout << "\t\t\t| *       |" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;

            case 4:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t| *     * |" << endl;
            cout << "\t\t\t|         |" << endl;
            cout << "\t\t\t| *     * |" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;

            case 5:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t| *     * |" << endl;
            cout << "\t\t\t|    *    |" << endl;
            cout << "\t\t\t| *     * |" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;

            case 6:
            cout << "\t\t\t.---------." << endl;
            cout << "\t\t\t|\033[33m *     * \033[0m|" << endl;
            cout << "\t\t\t|\033[33m *     * \033[0m|" << endl;
            cout << "\t\t\t|\033[33m *     * \033[0m|" << endl;
            cout << "\t\t\t'---------'" << endl;
            break;
        }
        usleep(10000 + (5000 * l));
    }
}
void D20Roll(){
    for (int l = 0; l < 35; l++){
        Chance = rand() % 20 + 1;
        clear();

        cout << "\t    ______     " << endl;
        cout << "\t  .'.____.'.   " << endl;
        cout << "\t /./      \\.\\" << endl;
        if(Chance < 10){
        cout << "\t| |   " << Chance << "    | |" << endl;
        }else{
        cout << "\t| |   " << Chance << "   | |" << endl;
        }
        cout << "\t \\'\\ ____ /'/" << endl;
        cout << "\t  ':______:'   " << endl;

        usleep(10000 + (4500 * l));
    }
}


void ArmageddonAnimSprites(int sprite, string colorbg, string colorbeam, int interval){
    //            _________       __
    // cout << "  |= = = = \_    /=|" << endl;
    // cout << "  |{}_{}_{}__\_/_{]|" << endl;
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
    ArmageddonAnimSprites(1,"\033[0m",color, 2000000);
}


void ChampionAppearAnimSprites(int sprite, int interval){
    clear();
    cout << "\033[1;95m";
    switch (sprite){
        case 0:
        cout << "\t\t\t\t\t" << "" << endl;
        cout << "\t\t\t\t\t" "                    " << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "                                           " << endl;
        cout << "\t\t\t\t\t" "                                        " << endl;
        cout << "\t\t\t\t\t" "                                        " << endl;
        cout << "\t\t\t\t\t" "                                        " << endl;
        cout << "\t\t\t\t\t" "                                      " << endl;
        cout << "\t\t\t\t\t" "                                 " << endl;
        cout << "\t\t\t\t\t" "                                < >             " << endl;
        cout << "\t\t\t\t\t" "                                " << endl;
        cout << "\t\t\t\t\t" "                                 " << endl;
        cout << "\t\t\t\t\t" "                                  " << endl;
        cout << "\t\t\t\t\t" "                                  " << endl;
        cout << "\t\t\t\t\t" "                               " << endl;
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
        cout << "\t\t\t\t\t" "                             '       '               " << endl;
        cout << "\t\t\t\t\t" "                               \\ ^ /            " << endl;
        cout << "\t\t\t\t\t" "                               < x >              " << endl;
        cout << "\t\t\t\t\t" "                               / v \\         " << endl;
        cout << "\t\t\t\t\t" "                             .       .         " << endl;
        cout << "\t\t\t\t\t" "                                               " << endl;
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
        cout << "\t\t\t\t\t" "                                 '                   " << endl;
        cout << "\t\t\t\t\t" "                                 |                  " << endl;
        cout << "\t\t\t\t\t" "                               . ^ .            " << endl;
        cout << "\t\t\t\t\t" "                           - - < + > - -          " << endl;
        cout << "\t\t\t\t\t" "                               ' v '         " << endl;
        cout << "\t\t\t\t\t" "                                 |            " << endl;
        cout <<  "\t\t\t\t\t""                                 .             " << endl;
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
        cout << "\t\t\t\t\t" "                                 |                   " << endl;
        cout << "\t\t\t\t\t" "                                |.|                   " << endl;
        cout << "\t\t\t\t\t" "                               |.:.|                " << endl;
        cout << "\t\t\t\t\t" "                        ..   .' ::: '.   ..          " << endl;
        cout << "\t\t\t\t\t" "                        : '-'::::|::::'-' :        " << endl;
        cout << "\t\t\t\t\t" "                         '-._ '::|::' _.-'    " << endl;
        cout << "\t\t\t\t\t" "                             '. ::: .'  " << endl;
        cout << "\t\t\t\t\t" "                               |':'|          " << endl;
        cout << "\t\t\t\t\t" "                                |'|            " << endl;
        cout << "\t\t\t\t\t" "                                 |             " << endl;
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
        cout << "\t\t\t\t\t" "                                 |                      " << endl;
        cout << "\t\t\t\t\t" "                                |:|                   " << endl;
        cout << "\t\t\t\t\t" "                               |.:.|                   " << endl;
        cout << "\t\t\t\t\t" "                              | ::: |                 " << endl;
        cout << "\t\t\t\t\t" "                     '.     .'  :|:  '.     .'         " << endl;
        cout << "\t\t\t\t\t" "                     : '---'.::::|::::.'---' :    " << endl;
        cout << "\t\t\t\t\t" "                     '.':::::|||||||||:::::'.'      " << endl;
        cout << "\t\t\t\t\t" "                       ''--. '::|||::' .--''  " << endl;
        cout << "\t\t\t\t\t" "                            '.  :|:  .'       " << endl;
        cout << "\t\t\t\t\t" "                              | ::: |            " << endl;
        cout << "\t\t\t\t\t" "                               |':'|          " << endl;
        cout << "\t\t\t\t\t" "                                |:|          " << endl;
        cout << "\t\t\t\t\t" "                                 |" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "" << endl;
        break;
        case 5:
        cout << "                      " << endl;
        cout << "\t\t\t\t\t" "                                 |          " << endl;
        cout << "\t\t\t\t\t" "                              | .:. |              " << endl;
        cout << "\t\t\t\t\t" "                                :::                       " << endl;
        cout << "\t\t\t\t\t" "                  .          |  :|:  |          .       " << endl;
        cout << "\t\t\t\t\t" "                      .         :|:         .           " << endl;
        cout << "\t\t\t\t\t" "                 |       '  '   :|:   '  '       |      " << endl;
        cout << "\t\t\t\t\t" "                    :.          |||          .:              " << endl;
        cout << "\t\t\t\t\t" "                 '  ':::|||:.. .|||. ..:|||:::'  '           " << endl;
        cout << "\t\t\t\t\t" "                   .    ':|||||||||||||||:'    .        " << endl;
        cout << "\t\t\t\t\t" "                       .    ':|||||||:'    .        " << endl;
        cout << "\t\t\t\t\t" "                          .    '|||'    .        " << endl;
        cout << "\t\t\t\t\t" "                            .   |||   .           " << endl;
        cout << "\t\t\t\t\t" "                                :|:               " << endl;
        cout << "\t\t\t\t\t" "                             |  :|:  |           " << endl;
        cout << "\t\t\t\t\t" "                                :::  " << endl;
        cout << "\t\t\t\t\t" "                              | ':' |           " << endl;
        cout << "\t\t\t\t\t" "                                 |                       " << endl;
        cout << "                                       " << endl;
        break;
        case 6:
        cout << "\t\t\t\t\t" "                                 |              " << endl;
        cout << "\t\t\t\t\t" "                                                    " << endl;
        cout << "\t\t\t\t\t" "                            |   .|.   |                   " << endl;
        cout << "\t\t\t\t\t" "                                :|:                       " << endl;
        cout << "\t\t\t\t\t" "                '   .      |    :|:    |      .   '       " << endl;
        cout << "\t\t\t\t\t" "                        '       |||       '              " << endl;
        cout << "\t\t\t\t\t" "               |                |||                |      " << endl;
        cout << "\t\t\t\t\t" "                    :.          |||          .:              " << endl;
        cout << "\t\t\t\t\t" "               .    '::|||||.. .|||. ..|||||::'    .           " << endl;
        cout << "\t\t\t\t\t" "                        ':|||||||||||||||:'             " << endl;
        cout << "\t\t\t\t\t" "                 '          '|||||||||'          '     " << endl;
        cout << "\t\t\t\t\t" "                    '          '|||'          '      " << endl;
        cout << "\t\t\t\t\t" "                       '        |||        '       " << endl;
        cout << "\t\t\t\t\t" "                          '     |||     '         " << endl;
        cout << "\t\t\t\t\t" "                           |    :|:    |           " << endl;
        cout << "\t\t\t\t\t" "                                :|:                    " << endl;
        cout << "\t\t\t\t\t" "                            |   '|'   |           " << endl;
        cout << "\t\t\t\t\t" "                                                        " << endl;
        cout << "\t\t\t\t\t" "                                 |                  " << endl;
        break;
        case 7:
        cout << "\t\t\t\t\t" "                                 '              " << endl;
        cout << "\t\t\t\t\t" "                                                    " << endl;
        cout << "\t\t\t\t\t" "                          .     .|.     .                 " << endl;
        cout << "\t\t\t\t\t" "                                |||                       " << endl;
        cout << "\t\t\t\t\t" "                         .      |||      .                " << endl;
        cout << "\t\t\t\t\t" "             .                  |||                  .   " << endl;
        cout << "\t\t\t\t\t" "                                |||                       " << endl;
        cout << "\t\t\t\t\t" "                    :.          |||          .:              " << endl;
        cout << "\t\t\t\t\t" "                    '|||||||.. .|||. ..|||||||'                " << endl;
        cout << "\t\t\t\t\t" "                        '|||||||||||||||||'             " << endl;
        cout << "\t\t\t\t\t" "                            '|||||||||'                " << endl;
        cout << "\t\t\t\t\t" "                               '|||'                 " << endl;
        cout << "\t\t\t\t\t" "                                |||                " << endl;
        cout << "\t\t\t\t\t" "                                |||               " << endl;
        cout << "\t\t\t\t\t" "                         '      |||      '         " << endl;
        cout << "\t\t\t\t\t" "                                |||                    " << endl;
        cout << "\t\t\t\t\t" "                          '     '|'     '         " << endl;
        cout << "\t\t\t\t\t" "                                                        " << endl;
        cout << "\t\t\t\t\t" "                                 .                  " << endl;
        break;
        case 8:
        cout << "" << endl;
        cout << "\t\t\t\t\t" "                                 " << endl;
        cout << "\t\t\t\t\t" "                                .|." << endl;
        cout << "\t\t\t\t\t" "                                |||                       " << endl;
        cout << "\t\t\t\t\t" "                                |||                     " << endl;
        cout << "\t\t\t\t\t" "                                |||                     " << endl;
        cout << "\t\t\t\t\t" "                                |||                     " << endl;
        cout << "\t\t\t\t\t" "                    |.          |||          .|              " << endl;
        cout << "\t\t\t\t\t" "                    '|||||||.. .|||. ..|||||||'              " << endl;
        cout << "\t\t\t\t\t" "                        '|||||||||||||||||'             " << endl;
        cout << "\t\t\t\t\t" "                            '|||||||||'             " << endl;
        cout << "\t\t\t\t\t" "                               '|||'             " << endl;
        cout << "\t\t\t\t\t" "                                |||               " << endl;
        cout << "\t\t\t\t\t" "                                |||               " << endl;
        cout << "\t\t\t\t\t" "                                |||             " << endl;
        cout << "\t\t\t\t\t" "                                |||" << endl;
        cout << "\t\t\t\t\t" "                                '|'" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "" << endl;
        break;
        case 9:
        cout << "" << endl;
        cout << "                    " << endl;
        cout << "" << endl;
        cout << "\t\t\t\t\t" "                                |                        " << endl;
        cout << "\t\t\t\t\t" "                                ||                     " << endl;
        cout << "\t\t\t\t\t" "                                ||                     " << endl;
        cout << "\t\t\t\t\t" "                                ||                     " << endl;
        cout << "\t\t\t\t\t" "                       |        ||        .|              " << endl;
        cout << "\t\t\t\t\t" "                       '||||..  ||. ..||||'              " << endl;
        cout << "\t\t\t\t\t" "                           '||||||||||'              " << endl;
        cout << "\t\t\t\t\t" "                               '||'              " << endl;
        cout << "\t\t\t\t\t" "                                ||              " << endl;
        cout << "\t\t\t\t\t" "                                ||               " << endl;
        cout << "\t\t\t\t\t" "                                ||               " << endl;
        cout << "\t\t\t\t\t" "                                ||             " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        break;
        case 10:
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "                    " << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "                             |                        " << endl;
        cout << "\t\t\t\t\t" "                              |.                    " << endl;
        cout << "\t\t\t\t\t" "                              ||                     " << endl;
        cout << "\t\t\t\t\t" "                               ||                     " << endl;
        cout << "\t\t\t\t\t" "                       |.      ||         .|              " << endl;
        cout << "\t\t\t\t\t" "                       '||||.  ||.  ..|||'              " << endl;
        cout << "\t\t\t\t\t" "                           '||||||||||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||              " << endl;
        cout << "\t\t\t\t\t" "                               ||               " << endl;
        cout << "\t\t\t\t\t" "                               ||               " << endl;
        cout << "\t\t\t\t\t" "                                |_              " << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        break;
        case 11:
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "                    " << endl;
        cout << "\t\t\t\t\t" "                            \\                        " << endl;
        cout << "\t\t\t\t\t" "                             |                     " << endl;
        cout << "\t\t\t\t\t" "                             ||                     " << endl;
        cout << "\t\t\t\t\t" "                              ||                     " << endl;
        cout << "\t\t\t\t\t" "                        |     ||         .|              " << endl;
        cout << "\t\t\t\t\t" "                        '|||  ||.   ..|||'              " << endl;
        cout << "\t\t\t\t\t" "                           '||||||||||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||              " << endl;
        cout << "\t\t\t\t\t" "                               ||               " << endl;
        cout << "\t\t\t\t\t" "                               ||               " << endl;
        cout << "\t\t\t\t\t" "                                ||_              " << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout <<  "\t\t\t\t\t""" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        break;
        case 12:
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "                           \\                        " << endl;
        cout << "\t\t\t\t\t" "                            |                     " << endl;
        cout << "\t\t\t\t\t" "                            ||                     " << endl;
        cout << "\t\t\t\t\t" "                             ||                     " << endl;
        cout << "\t\t\t\t\t" "                         |   ||          .|              " << endl;
        cout << "\t\t\t\t\t" "                         '||  ||.   ..||||'              " << endl;
        cout << "\t\t\t\t\t" "                           '||||||||||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||'              " << endl;
        cout << "\t\t\t\t\t" "                               ||              " << endl;
        cout << "\t\t\t\t\t" "                                ||              " << endl;
        cout << "\t\t\t\t\t" "                                ||              " << endl;
        cout << "\t\t\t\t\t" "                                 ||_              " << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
        cout << "\t\t\t\t\t" "" << endl;
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
    ChampionAppearAnimSprites(999,100000);//Blink

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
    ChampionAppearAnimSprites(8,400000);// Big one with pause
    ChampionAppearAnimSprites(9,100000);
    ChampionAppearAnimSprites(10,100000);
    ChampionAppearAnimSprites(11,100000);
    ChampionAppearAnimSprites(12,100000);
}
