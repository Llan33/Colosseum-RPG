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
#include "kingslayer_battlesystem.h"

using namespace std;

void BetaGameLoop(){
    PlayerNaming(Player1);
    ClassChoice(Player1);
    while(true){

        if (Wave == 6){//CHAMPION WAVE
            while(WaveRound < 5){
                EnemyScaling(EnemyA);
                ColosseumRound(WaveRound, Wave, Floor);
                Battle(Player1, EnemyA);
                if (GameOver == true){
                    return;
                }
                WaveRound++;
                ShuffleTime(Player1);
            }
            ColosseumRound(WaveRound, Wave, Floor);
            BattleChampion(Player1);
            if (GameOver == true){
                return;
            }
            Wave++;
            WaveRound = 1;
            return;
        }

        if (Floor == 3){//KINGS WAVE
            while(WaveRound < 5){
                EnemyScaling(EnemyA);
                ColosseumRound(WaveRound, Wave, Floor);
                Battle(Player1, EnemyA);
                if (GameOver == true){
                    return;
                }
                WaveRound++;
                ShuffleTime(Player1);
            }
            ColosseumRound(WaveRound, Wave, Floor);
            BattleKings(Player1);
            if (GameOver == true){
                return;
            }
            Wave++;
            WaveRound = 1;
            return;
        }

        while(WaveRound < 5){
            EnemyScaling(EnemyA);
            ColosseumRound(WaveRound, Wave, Floor);
            Battle(Player1, EnemyA);
            if (GameOver == true){
                return;
            }
            WaveRound++;
            ShuffleTime(Player1);
        }
        ColosseumRound(WaveRound, Wave, Floor);
        EnemyScaling(BossA);
        Battle(Player1, BossA);
        if (GameOver == true){
            return;
        }
        Wave++;
        WaveRound = 1;
        RelicDrop(Player1);
        CellTime(Player1);
    }
}

void BetaPVPLoop(){
    clear();
    int totalwave = 0;

    cout << "How many Waves?: ";
    cin >> totalwave;

    PlayerNaming(Player1);
    ClassChoice(Player1);
PlayerSwitchUI();
    PlayerNaming(Player2);
    ClassChoice(Player2);

PlayerSwitchUI();
    while(Wave <= totalwave){

        while(WaveRound < 5){
            EnemyScaling(EnemyA);
            ColosseumRound(WaveRound, Wave, Floor);
            Battle(Player1, EnemyA);
            if (GameOver == true){
                return;
            }
            WaveRound++;
            ShuffleTime(Player1);
        }
        ColosseumRound(WaveRound, Wave, Floor);
        EnemyScaling(BossA);
        Battle(Player1, BossA);
        if (GameOver == true){
            return;
        }
        
        WaveRound = 1;
        RelicDrop(Player1);
        CellTime(Player1);

        PlayerSwitchUI();

        while(WaveRound < 5){
            EnemyScaling(EnemyA);
            ColosseumRound(WaveRound, Wave, Floor);
            Battle(Player2, EnemyA);
            if (GameOver == true){
                return;
            }
            WaveRound++;
            ShuffleTime(Player2);
        }
        ColosseumRound(WaveRound, Wave, Floor);
        EnemyScaling(BossA);
        Battle(Player2, BossA);
        if (GameOver == true){
            return;
        }
        
        WaveRound = 1;
        RelicDrop(Player2);
        CellTime(Player2);

        Wave++;
    }

    BattlePVP(Player1,Player2);

}

// SPACES: VERTICAL = 28; HORIZONTAL = 118
int main(){
    clear();

    srand (time(0));

    //ColosseumRound(3,6,0);

    //PlaySound(TEXT("BATTLE1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP) ;
    //PlaySound(0, 0, 0) ;
    //g++ kingslayer.cpp -o kingslayer.exe -lwinmm

    Player1.Misc.Class = God;
    Player1.Name = "Player"; //Limit is 15
    Player1.Misc.NameLenght = size (Player1.Name);

    Player2.Name = "Francisco"; //Limit is 15
    Player2.Misc.NameLenght = size (Player2.Name);

    // Dialogue(Player1,Hero,Witch,true,"very well","","",0);
    // DialogueDramatic(Player1,Hero,Witch_fierce,false,"Then may you fall damned Warrior","\033[1;96m","","",160000,0);

    //  DE_KingsBattleBegin(Player1);

    // DE_KingsBattleAddisonDeath(Player1);
    // DE_KingsBattleAidenDeath(Player1);

    // EnemyA.Name = "Manex";
    // EnemyA.Misc.NameLenght = size (EnemyA.Name);
    // BossA.Name = "Boss";
    // EnemyA.Misc.NameLenght = size (EnemyA.Name);

    //DE_ChampionNoraDeath(Player1);
    //DE_ChampionBattleBegin(Player1);
    //PrisonEvent3(Player1);

    // Player1.Misc.Itemslots = 2;
    // Player1.Misc.Spellslots = 3;
    // Player1.Stat.Gold = 7000;
    // EnemyA.Misc.Level = 1;
    // Player1.Misc.Level = 1;
    // //Player1.Stat.XP = 90;
    // RlcInsightfulLenses.Obtained.P1 = true;
    // RlcEdibleHeart.Obtained.P1 = true;
    // RlcCheatScroll.Obtained.P1 = true;

    // Player1.ItemBag.Item1 = ItmArmageddon;
    //Battle(Player1,TheChampion);

    //CellTime(Player1);

    // while(true){
    //   Dialogue(Player1,Hero,Witch,true,"\033[91m|\\  |  |    |  |   |    |    |  |   |","| \\ |  |    |  |---| -- |    |  |---|","|  \\|   \\__/   |   |     \\__/   |   |",0);
    //     for (int l = 0; l < 10; l++){
    //         Dialogue(Player1,Hero,Witch_down,false,"\033[92m\\   /  |    |  |   |    |    |  |   |"," \\ /   |    |  |---| -- |    |  |---|","  |     \\__/   |   |     \\__/   |   |",50000);
    //         Dialogue(Player1,Hero,Witch,false,"\033[92m\\   /  |    |  |   |    |    |  |   |"," \\ /   |    |  |---| -- |    |  |---|","  |     \\__/   |   |     \\__/   |   |",50000);
    //     }
    // }

    
    //ArmageddonAnim("\033[43;30m", 1);
    //CellPrisontalk(Player1);
    //PrisonEvent8(Player1);
    //Wave = 7; Floor = 0; WaveRound = 1;
    //CellTime(Player1);

        
        EnemyA.ItemBag.Item1 = ItemGetRandomEnemy();


    //CellTime(Player1);
    //  DE_ChampionBattleDefeated(Player1);
    //  DE_ChampionNoraDeath(Player1);
    //BattleChampion(Player1);

    // RelicDrop(Player1);

    //BattlePVP(Player1, Player2);
    //BetaGameLoop();

    // Player1.Stat.HP = 10;

    BattleKings(Player1);
    

    while (true){
        MainMenuUI();
        //BetaGameLoop();
        // PlaySound(TEXT("BATTLE1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
        // sleep(1);
        //BattlePVP(Player1, Player2);
        // PlaySound(0, 0, 0) ;


        
        cout << "You: ";
        int Action;
        Action = PlayerInput(Action);
        
        switch (Action){
            case 0:
            return 0;
            break;

            case 1:
            clear();
            BetaGameLoop();
            continue;
            break;

            case 2:
            clear();
            BetaPVPLoop();
            break;

            case 4:
            Options();
            continue;
            break;

            default:
            cout << "Invalid";
            sleep(1);
            continue;
            break;
        }


    }
}