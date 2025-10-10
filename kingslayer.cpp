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
    ClassChoice(Player1);
    while(true){

        if (Wave == 6){//CHAMPION WAVE
            for(int l = 0; l < 4; l++){
                ColosseumRound(WaveRound, Wave, Floor);
                Battle(Player1, EnemyA);
                if (GameOver == true){
                    return;
                }
                ShuffleTime(Player1);
                EnemyA.Stat.MAXHP *= 1.2; EnemyA.Stat.HP = EnemyA.Stat.MAXHP; EnemyA.Stat.AC += 0.5 * Wave; EnemyA.Stat.ATK += 0.4 * Wave;
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

        for(int l = 0; l < 4; l++){
            ColosseumRound(WaveRound, Wave, Floor);
            Battle(Player1, EnemyA);
            if (GameOver == true){
                return;
            }
            ShuffleTime(Player1);
            EnemyA.Stat.MAXHP *= 1.2; EnemyA.Stat.HP = EnemyA.Stat.MAXHP; EnemyA.Stat.AC += 0.5 * Wave; EnemyA.Stat.ATK += 0.4 * Wave;
        }
        ColosseumRound(WaveRound, Wave, Floor);
        BossA.Stat.MAXHP = EnemyA.Stat.HP * 1.5; BossA.Stat.HP = BossA.Stat.MAXHP; BossA.Stat.AC = EnemyA.Stat.AC * 1.5; BossA.Stat.ATK = EnemyA.Stat.ATK * 1.4;
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

// SPACES: VERTICAL = 28; HORIZONTAL = 118
int main(){
    clear();

    srand (time(0));

    //ColosseumRound(3,6,0);

    //PlaySound(TEXT("BATTLE1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP) ;
    //PlaySound(0, 0, 0) ;
    //g++ kingslayer.cpp -o kingslayer.exe -lwinmm

    Player1.Misc.Class = Gladiator;
    Player1.Name = "Filipe"; //Limit is 15
    Player1.Misc.NameLenght = size (Player1.Name);

    Player2.Name = "Francisco"; //Limit is 15
    Player2.Misc.NameLenght = size (Player2.Name);


    // EnemyA.Name = "Manex";
    // EnemyA.Misc.NameLenght = size (EnemyA.Name);
    // BossA.Name = "Boss";
    // EnemyA.Misc.NameLenght = size (EnemyA.Name);

    //DE_ChampionNoraDeath(Player1);
    //DE_ChampionBattleBegin(Player1);
    //PrisonEvent3(Player1);

    Player1.Misc.Itemslots = 2;
    Player1.Misc.Spellslots = 3;
    Player1.Stat.Gold = 7000;
    EnemyA.Misc.Level = 1;
    Player1.Misc.Level = 1;
    //Player1.Stat.XP = 90;
    RlcInsightfulLenses.Obtained.P1 = true;
    RlcEdibleHeart.Obtained.P1 = true;
    RlcUnderworldSkull.Obtained.P1 = true;

    Player1.ItemBag.Item1 = ItmArmageddon;
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
    //Wave = 3; Floor = 0;
    //CellTime(Player1);

         Player1.SpellBag.SigSpell = SplBlackKnightStance;
        Player1.SpellBag.Spell1 = SplFrigidLaceration;
        Player1.SpellBag.Spell2 = SplChromaticWave;
        Player1.SpellBag.Spell3 = SplPoisonCloud;
        Player1.SpellBag.Spell4 = SplViciousMockery;
        // Player1.SpellBag.Spell5 = SplRoyalKnightStance;
        // Player1.SpellBag.Spell6 = SplKnightStance;
    
         Player1.ItemBag.Item1 = ItmCursedDice;
        Player1.ItemBag.Item2 = ItmHealingPotion;
        Player1.ItemBag.Item3 = ItmStancedCoating;
        // Player1.ItemBag.Item4 = ItmCoinPouch;
        // Player1.ItemBag.Item5 = ItmCoinPouch;


        Player2.SpellBag.SigSpell = SplDuoSlash;
        Player2.SpellBag.Spell1 = SplFrigidLaceration;
        Player2.SpellBag.Spell2 = SplChromaticWave;
        Player2.SpellBag.Spell3 = SplWilloWisp;
        Player2.SpellBag.Spell4 = SplStatisticalLightbeam;
        Player2.SpellBag.Spell5 = NoSpell;
        Player2.SpellBag.Spell6 = NoSpell;
    
        Player2.ItemBag.Item1 = ItmCursedDice;
        Player2.ItemBag.Item2 = ItmHealingPotion;
        Player2.ItemBag.Item3 = ItmStancedCoating;
        // Player2.ItemBag.Item4 = ItmCoinPouch;
        // Player2.ItemBag.Item5 = ItmCoinPouch;
        
        EnemyA.ItemBag.Item1 = ItemGetRandomEnemy();

    //  DE_ChampionBattleDefeated(Player1);
    //  DE_ChampionNoraDeath(Player1);
    BattleChampion(Player1);

    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    // RelicDrop(Player1);
    //BattlePVP(Player1, Player2);
    //BetaGameLoop();
Wave = 6;
    Title:
    MainMenuUI();
    //BetaGameLoop();
    // PlaySound(TEXT("BATTLE1.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP) ;
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
        goto Title;
        break;

        case 4:
        Options();
        goto Title;
        break;

        default:
        cout << "Invalid";
        sleep(1);
        goto Title;
        break;
    }

    if (GameOver == true){
        return 0;
    }

}