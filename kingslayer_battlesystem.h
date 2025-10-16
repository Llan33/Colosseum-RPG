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

#include "kingslayer_spells&items.h"


using namespace std;

   //- Battle Subjects -
Entity Player1(50,40,150,5,2,20,5,9, PLAYER1, "Player1");
Entity Player2(50,15,10,5,2,5,5,9, PLAYER2, "Player2");
Entity EnemyA(9,5,4,3,0,0,0,0, ENEMY, "Enemy");
Entity BossA(30,10,6,6,4,5,5,0, BOSS, "Boss");

Entity TheChampion(999,999,999,999,50,999,0,3309, CHAMPION, "\033[1;95mThe Champion\033[0m");

//- General Functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void MainMenuUI(){
    Start:
    clear();
    usleep(100000);
    cout << endl;
    cout << "    ______  |\\	      _____   __      __                      _    _  __   _    _   _______     " << endl; usleep(30000);
    cout << "   /  ____\\ | |   ---/ ___ \\-\\  \\--  /  / _____        ___   | | / / |  | | \\  | | |  _____\\  " << endl; usleep(50000);
    cout << "---- /____  | |     / /___\\ \\ \\  \\  /  /    |   |   | |      | |/ /  |  | |  \\ | | | | ____    " << endl; usleep(70000);
    cout << "  \\_____  \\ | |     |  ___  |  \\  \\/  /     |   |---| |--    |   |   |  | |   \\| | | | \\_  |  " << endl; usleep(90000);
    cout << "   ____/ ---| |--___| |   | |-- \\    /      |   |   | |___   | |\\ \\  |  | | |\\   | | |___| |    " << endl; usleep(110000);
    cout << "  /______/  |______/|_|   |_|    /  /                        |_| \\_\\ |  | |_| \\__| |___   _|     " << endl; usleep(130000);
    cout << "                                /  /                                _|  |_             \\ |         " << endl; usleep(140000);
    cout << "                               /  /                                \033[33m |\033[31m'\033[35m'\033[36m'\033[32m'\033[33m|  \033[0m            ||          " << endl; usleep(150000);
    cout << "                              /__/                                \033[33m  |/\\/\\| \033[0m             ||        " << endl; usleep(160000);
    cout << "                                                                                        ||         " << endl; usleep(170000);
    cout << "                                                                         _  _ __ _______||_______ __ _  _ " << endl; usleep(250000);
    cout << "        .-------.              .-------.              .-------.         +--------------------------------+           " << endl;
    cout << "        |       |              |       |              |       |                    (4) Options            " << endl;
    cout << "        | Main  |              |2Player|              | Extras|         *--------------------------------*" << endl; 
    cout << "        | Story |              |Versus |              |       |                    (5) Credits            " << endl;
    cout << "        |       |              |       |              |       |         *--------------------------------*" << endl;
    cout << "        `-------`              `-------`              `-------`                     (0)  Quit             " << endl;
    cout << "           (1)                    (2)                    (3)            +--------------------------------+" << endl;
    cout << "                                                                        " << endl;

}

void XPBar(Entity& Player){
    cout << " \033[1;92mXP\033[0m [";
    for (int l = 1; l < 26; l++){
        if (Player.Stat.XP >= (Player.Misc.XPThreshold*(0.04*l)))
            {cout <<"\033[1;92m=\033[0m";
        }else{
            cout <<"\033[90m-\033[0m";
        }
    }
    cout << "](" << Player.Stat.XP <<"/"<< Player.Misc.XPThreshold <<")" << endl;
}

//- In-Game UI's - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void EntityBoxEdgeUI(Entity User){
    cout << "+-";
     for (int l = 0; l < User.Misc.NameLenght; l++){
        cout << "-";
    }
    cout << "-+";
}
void EntityNameStringUI(Entity User, bool ShowMana, bool Box){
    if (Box == true){
        cout << "| ";
    }
    cout << User.Name << ": " << User.Stat.HP << "/" << User.Stat.MAXHP << " \033[91mHP\033[0m";

    if (ShowMana == true){
        cout << "   " << User.Stat.MANA << "/" << User.Stat.MAXMANA << " \033[94mMana\033[0m";
    }
}
void EntityBoxUI(Entity User, bool ShowMana, bool Menu){

    if (Menu == true){
        cout << "   ";
    }
    EntityBoxEdgeUI(User);
    cout << endl;

    if (Menu == true){
        cout << "   ";
    }
    EntityNameStringUI(User, ShowMana, true);
    cout << endl;

    if (Menu == true){
        cout << "   ";
    }
    EntityBoxEdgeUI(User);
    cout << endl;
}

void HPMPspaceCheck(Entity Player){
    if(Player.Stat.HP > 99){
        cout << "   ";
    }else if(Player.Stat.HP > 9){
        cout << "  ";
    }else{
        cout << " ";
    }
    if(Player.Stat.MAXHP > 99){
        cout << "   ";
    }else{
        cout << "  ";
    }
    if(Player.Stat.MANA > 9){
        cout << "  ";
    }else{
        cout << " ";
    }
    cout << "             "; //13 spaces
}
void StatusCheckUI(Entity User){
  
    if (User.Status.Burn > 0){
        cout << " " << "|\033[1;91mBRN\033[0m|" << User.Status.Burn;
    }

    if (User.Status.Poison > 0){
        cout << " " << "|\033[1;92mPSN\033[0m|" << User.Status.Poison;
    }

    if (User.Status.Freeze > 0){
        cout << " " << "|\033[1;96mFRZ\033[0m|" << User.Status.Freeze;
    }

    if (User.Status.Shock > 0){
        cout << " " << "|\033[1;93mSHO\033[0m|" << User.Status.Shock;
    }
}
void BattleUI(Entity& Player, Entity& Enemy, bool Insight){
    cout << endl;
            cout << " "; EntityBoxEdgeUI(Player);// P Box
                StatusCheckUI(Player);
            cout << endl << " ";

    EntityNameStringUI(Player, true, true);//Main Player Name

            cout << "       "; EntityBoxEdgeUI(Enemy);// E Box
                StatusCheckUI(Enemy);
            cout << endl << " ";
            EntityBoxEdgeUI(Player);// P Box

            HPMPspaceCheck(Player);

    cout << "         ";
    EntityNameStringUI(Enemy, false, true);//Main Enemy Name
    cout << endl;

            HPMPspaceCheck(Player);

            for (int l = 0; l < Player.Misc.NameLenght + 4; l++){cout << " ";}
            cout << "          "; EntityBoxEdgeUI(Enemy);//E Box

            cout << "\n\n";

    if (PlayerTurn == true){
        if (Insight == false){
        cout << "  +- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +" << endl;
        cout << "  | 1 - \033[1;91mAttack\033[0m   2 - \033[1;94mSpells\033[0m   3 - \033[1;96mItems\033[0m   0 - \033[1;90mDefend\033[0m   4 - Stats |" << endl;
        cout << "  + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << "\n\n";
        }else{
        cout << " +- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +" << endl;
        cout << " | 1 - \033[1;91mAttack\033[0m   2 - \033[1;94mSpells\033[0m   3 - \033[1;96mItems\033[0m   0 - \033[1;90mDefend\033[0m   4 & 5 - Stats |" << endl;
        cout << " + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << "\n\n";
        }
    }

}

void SpellMenuSpell(Entity& Player, int& Menucount, Spell MenuSpell){

    int ManaDiscount = 0;

    if (Player.Misc.Type == PLAYER1){
        if (RlcArcaneRing.Obtained.P1 == true){
            ManaDiscount = 1;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcArcaneRing.Obtained.P2 == true){
            ManaDiscount = 1;
        }
    }

    if (MenuSpell.ID != NOSPELL){
        Menucount++;
        cout << "| " << Menucount << " - " << MenuSpell.Name << " " << MenuSpell.Desc << " : " << MenuSpell.ManaCost - ManaDiscount << " " << Blue("Mana") << endl;
        cout << "| " << endl;
    }
}
void SpellMenuUI(Entity& Player){
    clear();
    int Menucount = 0;

    
    cout << "~ \033[1;94mSPELLS\033[0m: ~" << "\n\n";
    
    EntityBoxUI(Player, true, true);

    cout << "                                       Spell Tokens: " << Player.Misc.Spellslots << " " << tokensshow() << endl;
    cout << "+ - 0 > Go Back - - - - - - - - - - - - - - - - - - - - - - - - ~" << "\n|\n";

    SpellMenuSpell(Player, Menucount,Player.SpellBag.DefaultSpell);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.SigSpell);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell1);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell2);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell3);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell4);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell5);
    SpellMenuSpell(Player, Menucount,Player.SpellBag.Spell6);

    for (int l = 0; l < Player.Misc.Spellslots; l++){
        cout << "| --" << endl;
        cout << "| " << endl;
    }

    cout << "+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ~" << "\n\n";
}

void ItemMenuItem(int& Menucount, Item MenuItem){
    if (MenuItem.ID != NONE){
        Menucount++;
        cout << "| " << Menucount << " - " << MenuItem.Name << " " << MenuItem.Desc << endl;
        cout << "| " << endl;
    }
}
void ItemMenuUI(Entity& Player){
    clear();
    int Menucount = 0;

    cout << "# \033[1;96mITEMS\033[0m: #" << "\n\n";

    EntityBoxUI(Player, true, true);
    cout << endl;

    cout << "+ - 0 > Go Back - - - - - - - - - - - - - - - - - - - - - - #" << "\n|\n";

    ItemMenuItem(Menucount,Player.ItemBag.Item1);
    ItemMenuItem(Menucount,Player.ItemBag.Item2);
    ItemMenuItem(Menucount,Player.ItemBag.Item3);
    ItemMenuItem(Menucount,Player.ItemBag.Item4);
    ItemMenuItem(Menucount,Player.ItemBag.Item5);

    for (int l = 0; l < Player.Misc.Itemslots; l++){
        cout << "| --" << endl;
        cout << "| " << endl;
    }

    cout << "+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #" << "\n\n";
}

void RelicMenuUI(Relic& Option1, Relic& Option2, Relic& Option3, Relic& Option4){

    cout << "              -   -   -  -  -  - - - - -- --- ---- -----\033[1mRELICS\033[0m----- ---- --- -- - - - -  -  -  -   -   -" << endl;
    cout << endl;
    cout << "                             " << Option1.Image.Line1 << "                                        " << Option2.Image.Line1 << endl;
    cout << "                             " << Option1.Image.Line2 << "                                        " << Option2.Image.Line2 << endl;
    cout << "                             " << Option1.Image.Line3 << "                                        " << Option2.Image.Line3 << endl;
    cout << "                             " << Option1.Image.Line4 << "                                        " << Option2.Image.Line4 << endl;
    cout << "                             " << Option1.Image.Line5 << "                                        " << Option2.Image.Line5 << "\n\n";
    cout << "                          " << Option1.Name << "                                 " << Option2.Name << endl;
    cout << "               *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*            *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*" << endl;
    cout << "                "         << Option1.Desc <<       "              "       << Option2.Desc << endl;
    cout << "               *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*            *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*" << endl;
    cout << "                                (1)                                                (2)                  " << "\n\n";

    cout << "                             " << Option3.Image.Line1 << "                                        " << Option4.Image.Line1 << endl;
    cout << "                             " << Option3.Image.Line2 << "                                        " << Option4.Image.Line2 << endl;
    cout << "                             " << Option3.Image.Line3 << "                                        " << Option4.Image.Line3 << endl;
    cout << "                             " << Option3.Image.Line4 << "                                        " << Option4.Image.Line4 << endl;
    cout << "                             " << Option3.Image.Line5 << "                                        " << Option4.Image.Line5 << "\n\n";
    cout << "                          " << Option3.Name << "                                 " << Option4.Name << endl;
    cout << "               *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*            *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*" << endl;
    cout << "                "         << Option3.Desc <<       "              "       << Option4.Desc << endl;
    cout << "               *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*            *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*" << endl;
    cout << "                                (3)                                                (4)                  " << "\n\n";

    cout << "              -   -   -  -  -  - - - - -- --- ---- -------  ------- ---- --- -- - - - -  -  -  -   -   -" << endl;
    
    

}

void PlayerSwitchUI(){
    sleep(1);
    clear();
    for (int l = 0; l < 20; l++){
        cout << "\n\n\n\n";
        cout << "\t>- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ->" << endl << "\t";
        for (int i = 0; i < l; i++){
            cout << "   ";
        }
        cout << "\033[1;37mPLAYER SWITCH\033[0m" << endl;
        cout << "\t>- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ->" << endl;
        usleep(25000);
        clear();
    }
}

//- Complex Battle Actions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

Spell SpellGetRandomShop(){

    Chance = rand() % 12 + 10;

    switch (Chance){

        case 10:
        return SplBloodBinding;
        break;

        case 11:
        return SplWilloWisp;
        break;

        case 12:
        return SplIgnitus;
        break;

        case 13:
        return SplPoisonCloud;
        break;

        case 14:
        return SplInfestation;
        break;

        case 15:
        return SplViciousMockery;
        break;

        case 16:
        return SplFrigidLaceration;
        break;

        case 17:
        return SplThunderChain;
        break;

        case 18:
        return SplPolarityShock;
        break;

        case 19:
        return SplStatisticalLightbeam;
        break;

        case 20:
        return SplMetaphysicalOverload;
        break;

        case 21:
        return SplChromaticWave;
        break;
    }
    return NoSpell;
};
void SpellUseEffect(Entity& User, Entity& Target, Spell& useSpell){
    clear();
    cout << endl;

    switch (useSpell.ID) { // ID to Effect Check

        case SHeal:
        SplEffSmallHeal(User);
        break;

        case DuoSlsh:
        SplEffDuoSlash(User, Target);
        break;

        case CrossSlsh:
        SplEffCrossSlash(User, Target);
        break;

        case MBlast:
        SplEffMagicaArcaneWarlockBlast(User, Target, 1.2);
        break;

        case ArcBlast:
        SplEffMagicaArcaneWarlockBlast(User, Target, 1.8);
        break;

        case TempnRageCut:
        SplEffTemperedandEnragedCut(User, Target);
        break;

        case KnghtStance:
        SplEffKnightStance(User, Target);
        break;

        case RoylkKnghtStance:
        SplEffRoyalKnightStance(User, Target);
        break;

        case GrtHeal:
        SplEffGreatHeal(User);
        break;

        case BloodBind:
        SplEffBloodBinding(User, Target);
        break;

        case WillWisp:
        SplEffWilloWisp(User, Target);
        break;

        case Ignits:
        SplEffIgnitus(User, Target);
        break;

        case PsnCloud:
        SplEffPoisonCloud(User, Target);
        break;

        case Infestat:
        SplEffInfestation(User, Target);
        break;

        case VMock:
        SplEffViciousMockery(User, Target);
        break;

        case FrigLaceration:
        SplEffFrigidLaceration(User, Target);
        break;

        case ThundChain:
        SplEffThunderChain(User, Target);
        break;

        case PolarShock:
        SplEffPolarityShock(User, Target);
        break;

        case StatBeam:
        SplEffStatisticalLightBeam(User, Target);
        break;

        case MetaOverload:
        SplEffMetaphysicalOverload(User, Target);
        break;

        case ChromWave:
        SplEffChromaticWave(User, Target);
        break;

        case Omnislsh:
        SplEffOmnislash(User, Target);
        break;

        case WarBlast:
        SplEffMagicaArcaneWarlockBlast(User, Target, 3.0);
        break;

        case VengCut:
        SplEffVengeanceCut(User, Target);
        break;

        case BlckKnghtStance:
        SplEffBlackKnightStance(User, Target);
        break;

        case SupremHeal:
        SplEffSupremeHeal(User);
        break;
    }

}
void SpellValidCheck(Entity& Player, Entity& Enemy, bool& validspell, Spell& useSpell){

    int ManaDiscount = 0;

    if (Player.Misc.Type == PLAYER1){// Arcane Ring Check
        if (RlcArcaneRing.Obtained.P1 == true){
            ManaDiscount = 1;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcArcaneRing.Obtained.P2 == true){
            ManaDiscount = 1;
        }
    }

    if (useSpell.ID != NOSPELL){

        if (Player.Stat.MANA >= (useSpell.ManaCost - ManaDiscount)){

            Player.Stat.MANA -= (useSpell.ManaCost - ManaDiscount);
            SpellUseEffect(Player, Enemy, useSpell);

        }else{
            goto nomana;
        }

    }else{
        goto invalid;
    }

    return;

    invalid:
    cout << "Invalid move";
    validspell = false;
    sleep (1);
    clear();
    return;

    nomana:
    cout << "Not enough Mana";
    validspell = false;
    sleep (1);
    clear();
    return;

}
void SpellPlayerAction(Entity& Player, Entity& Enemy, bool& validturn){

    int Action;
    
    while (true){

        SpellMenuUI(Player);

        cout << "Choose: ";
        PlayerInput(Action);

        bool validspell = true;

        switch (Action){

            case 0:
                validturn = false;
                clear();
                break;

            case 1:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.DefaultSpell);
                break;

            case 2:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.SigSpell);
                break;

            case 3:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell1);
                break;
            
            case 4:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell2);
                break;

            case 5:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell3);
                break;

            case 6:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell4);
                break;

            case 7:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell5);
                break;

            case 8:
                SpellValidCheck(Player, Enemy, validspell, Player.SpellBag.Spell6);
                break;

            default:
                cout << "Invalid move";
                validspell = false;
                sleep (1);
                clear();
                break;
        }

        if (validspell == true){
            break;
        }
    }

}

Item ItemGetRandomEnemy(){

    Chance = rand() % 10 + 1;

    switch (Chance) { // ID to Effect Check

        case 1:
        return ItmManaFlask;
        break;

        case 2:
        return ItmStatusPotion;
        break;

        case 3:
        return ItmMixedFlask;
        break;

        case 4:
        return ItmBloodCoating;
        break;

        case 5:
        return ItmVitalityCoating;
        break;

        case 6:
        return ItmStancedCoating;
        break;

        case 7:
        return ItmBurningCinders;
        break;

        case 8:
        return ItmPoisonDart;
        break;

        case 9:
        return ItmIceFlask;
        break;

        case 10:
        return ItmCoinPouch;
        break;
    }
    return NoItem;
}
Item ItemGetRandom(){

    Chance = rand() % TotalItems + 1;

    switch (Chance) { // ID to Item Check

        case 1:
        return ItmHealingPotion;
        break;

        case 2:
        return ItmManaFlask;
        break;

        case 3:
        return ItmStatusPotion;
        break;

        case 4:
        return ItmMixedFlask;
        break;

        case 5:
        return ItmUltimateFlask;
        break;

        case 6:
        return ItmBloodCoating;
        break;

        case 7:
        return ItmVitalityCoating;
        break;

        case 8:
        return ItmFlurryCoating;
        break;

        case 9:
        return ItmStancedCoating;
        break;

        case 10:
        return ItmDeadlyCoating;
        break;

        case 11:
        return ItmBurningCinders;
        break;

        case 12:
        return ItmFlintnSteel;
        break;

        case 13:
        return ItmPoisonDart;
        break;

        case 14:
        return ItmPoisonDagger;
        break;

        case 15:
        return ItmIceFlask;
        break;

        case 16:
        return ItmChillingOrb;
        break;

        case 17:
        return ItmDeadlyJar;
        break;

        case 18:
        return ItmLightninginaJar;
        break;

        case 19:
        return ItmExplosiveJar;
        break;

        case 20:
        return ItmNiceJar;
        break;

        case 21:
        return ItmCursedDice;
        break;

        case 22:
        return ItmWeirdDice;
        break;

        case 23:
        return ItmCoinPouch;
        break;

        case 24:
        return ItmVoodooDoll;
        break;

        case 25:
        return ItmPreciseNeedle;
        break;

        case 26:
        return ItmArmageddon;
        break;
    }
    return NoItem;
}
void ItemSlotPlayerCheck(Entity& Player, Item& getItem, bool& SlotAvailable){
    SlotAvailable = true;
    if (Player.Misc.Itemslots != 0){
        if (Player.ItemBag.Item1.ID == NONE){
            Player.ItemBag.Item1 = getItem;

        }else if (Player.ItemBag.Item2.ID == NONE){
            Player.ItemBag.Item2 = getItem;

        }else if (Player.ItemBag.Item3.ID == NONE){
            Player.ItemBag.Item3 = getItem;

        }else if (Player.ItemBag.Item4.ID == NONE){
            Player.ItemBag.Item4 = getItem;

        }else if (Player.ItemBag.Item5.ID == NONE){
            Player.ItemBag.Item5 = getItem;
        }else{
            SlotAvailable = false;
        }
    }else{
        SlotAvailable = false;
    }
    
    if (SlotAvailable == true){
        Player.Misc.Itemslots--;
    }
}
void ItemSlotPass(Item& RecievingSlot, Item& PassingSlot){

    if (RecievingSlot.ID == NONE){

        if (PassingSlot.ID != NONE){
            RecievingSlot = PassingSlot;
            PassingSlot = NoItem;
        }

    }
}
void ItemUseEffect(Entity& User, Entity& Target, Item& useItem, uint16_t& Itemslot){
    clear();
    cout << endl;

    bool ExtraItem = false;

    switch (useItem.ID) { // ID to Effect Check

        case HealPotion:
        ItmEffHealingPotion(User);
        break;

        case MpFlask:
        ItmEffManaFlask(User);
        break;

        case StusPotion:
        ItmEffStatusPotion(User);
        break;

        case VFlask:
        ItmEffMixedFlask(User);
        break;

        case UltFlask:
        ItmEffUltimateFlask(User);
        break;

        case BloodCoat:
        ItmEffBloodCoating(User, Target);
        break;

        case VitalCoat:
        ItmEffVitalityCoating(User,Target);
        break;

        case FlurryCoat:
        ItmEffFlurryCoating(User, Target);
        break;

        case StanceCoat:
        ItmEffStancedCoating(User, Target);
        break;

        case DeadlyCoat:
        ItmEffDeadlyCoating(User, Target);
        break;

        case BurnCinder:
        ItmEffBurningCinders(User, Target);
        break;

        case FlintnSteel:
        ItmEffFlintandSteel(User, Target);
        break;

        case PsnDart:
        ItmEffPoisonDart(User, Target);
        break;

        case PsnDagger:
        ItmEffPoisonDagger(User, Target);
        break;

        case IceFlsk:
        ItmEffIceFlask(User, Target);
        break;

        case ChillOrb:
        ItmEffChillingOrb(User, Target);
        break;

        case DeadJar:
        ItmEffDeadlyJar(User, Target);
        break;

        case LightinJar:
        ItmEffLightninginaJar(User, Target);
        break;

        case ExplosJar:
        ItmEffExplosiveJar(User, Target);
        break;

        case NiceeeJar:
        ItmEffNiceJar(User, Target);
        break;

        case CurseDice:
        ItmEffCursedDice(User, Target, ExtraItem);
        break;

        case WeirDice:
        ItmEffWeirdDice(User, Target);
        break;

        case CoinBag:
        ItmEffCoinPouch(User, Target, ExtraItem);
        break;

        case VoodooDo:
        ItmEffVoodooDoll(User, Target);
        break;

        case PrecNeedle:
        ItmEffPreciseNeedle(User, Target);
        break;

        case Armagedon:
        ItmEffArmageddon(User, Target);
        break;
    }

    useItem = NoItem;

    Itemslot++;

    if (ExtraItem == true){
        Itemslot--;
        useItem = ItemGetRandom();
    }

    for (int l = 0; l < 5; l++){// Item Slot Passing (To keep number arranged)
        ItemSlotPass(User.ItemBag.Item4, User.ItemBag.Item5);
        ItemSlotPass(User.ItemBag.Item3, User.ItemBag.Item4);
        ItemSlotPass(User.ItemBag.Item2, User.ItemBag.Item3);
        ItemSlotPass(User.ItemBag.Item1, User.ItemBag.Item2);
    }

}
void ItemPlayerAction(Entity& Player, Entity& Enemy, bool& validturn){

    int Action;
    
    while (true){

        ItemMenuUI(Player);

        cout << "Pick: ";
        PlayerInput(Action);

        bool validitemchoice = false;

        switch (Action){

            case 0:
                validturn = false;
                clear();
                break;

            case 1:
                if (Player.ItemBag.Item1.ID != NONE){
                    ItemUseEffect(Player, Enemy, Player.ItemBag.Item1, Player.Misc.Itemslots);
                }else{
                    goto invalid;
                }
                break;
            
            case 2:
                if (Player.ItemBag.Item2.ID != NONE){
                    ItemUseEffect(Player, Enemy, Player.ItemBag.Item2, Player.Misc.Itemslots);
                }else{
                    goto invalid;
                }
                break;
    
            case 3:
                if (Player.ItemBag.Item3.ID != NONE){
                    ItemUseEffect(Player, Enemy, Player.ItemBag.Item3, Player.Misc.Itemslots);
                }else{
                    goto invalid;
                }
                break;
    
            case 4:
                if (Player.ItemBag.Item4.ID != NONE){
                    ItemUseEffect(Player, Enemy, Player.ItemBag.Item4, Player.Misc.Itemslots);
                }else{
                    goto invalid;
                }
                break;
    
            case 5:
                if (Player.ItemBag.Item5.ID != NONE){
                    ItemUseEffect(Player, Enemy, Player.ItemBag.Item5, Player.Misc.Itemslots);
                }else{
                    goto invalid;
                }
                break;

            default:
            invalid:
                cout << "Invalid move";
                validitemchoice = true;
                sleep (1);
                clear();
                break;
        }

        if (validitemchoice == false){
            break;
        }
    }

}

void StatMenuRelicCheck(Entity& Player, Relic Relic){
    if (Player.Misc.Type == PLAYER1){
        if (Relic.Obtained.P1 == true){
            cout << "  " << Relic.Name << " (" << Relic.Desc << ")" << endl;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (Relic.Obtained.P2 == true){
            cout << "  " << Relic.Name << " (" << Relic.Desc << ")" << endl;
        }
    }
}
void StatMenu(Entity& User){
    string CLASS;
    float TotalStats = User.Stat.ATK + User.Stat.MAXHP + User.Stat.MAXMANA + User.Stat.MA + User.Stat.AC + User.Stat.CRIT + User.Stat.DODGE;

    switch (User.Misc.Class){
        case Gladiator:
        CLASS = "\033[1;93mGladiator\033[0m";
        break;
        case Wanderer:
        CLASS = "\033[1;94mWanderer\033[0m";
        break;
        case Berserker:
        CLASS = "\033[1;91mBerserker\033[0m";
        break;
        case BlackKnight:
        CLASS = "\033[1;90mBlack Knight\033[0m";
        break;
        case God:
        CLASS = "\033[1;33mGOD\033[0m";
        break;
        default:
        switch (User.Misc.Type){
            case CHAMPION:
            CLASS = "\033[1;95mChampion\033[0m";
            break;
            case KING:
            CLASS = "\033[1;93mKing\033[0m";
            break;
            default:
            CLASS = "\033[1;37mEnemy\033[0m";
            break;
        }
        break;
    }
    if (User.Misc.Type == BOSS){
        CLASS = "\033[1;91mBOSS\033[0m";
    }else if (User.Misc.Type == KING){
        CLASS = "\033[1;33mKING\033[0m";
    }

    clear();
    cout << "\t+----------------------------------------+" << endl;
    if (User.Misc.Level >= 10){
        cout << "\t\t STATS: " << User.Name << " [Lv MAX]" << "\t Class: " << CLASS << endl;
    }else{
        cout << "\t\t STATS: " << User.Name << " [Lv " << User.Misc.Level << "]" << "\t Class: " << CLASS << endl;
    }
    cout << "\t+----------------------------------------+" << endl;
    cout << "\t |\033[91mBRN\033[0m| = " << User.Status.Burn << " |\033[92mPSN\033[0m| = " << User.Status.Poison << " |\033[96mFRZ\033[0m| = " << User.Status.Freeze << " |\033[93mSHO\033[0m| = " << User.Status.Shock << endl;
    cout << "\t+----------------------------------------+" << endl;
    cout << "\t|     MAX \033[91mHP\033[0m = " << User.Stat.MAXHP << "       MAX \033[94mMana\033[0m = " << User.Stat.MAXMANA << "\t |" << endl;
    cout << "\t| Current \033[91mHP\033[0m = " << User.Stat.HP << "   Current \033[94mMana\033[0m = " << User.Stat.MANA << "\t |" << endl;
    cout << "\t+-----------------+----------------------+" << endl;
	cout << "\t|   ATK = " << User.Stat.ATK << "\t  |     \033[33mGold\033[0m   = " << User.Stat.Gold << goldshow() << " \t |\033[90m ATK = Attack\033[0m" << endl;
    cout << "\t|    MA = " << User.Stat.MA  << "\t  |    \033[95mTokens\033[0m  = " << User.Misc.Spellslots << " \t |\033[90m MA = Magic\033[0m" << endl;
    cout << "\t|    AC = " << User.Stat.AC << "\t  |   [Defense = " << User.Stat.DEF << "]" << " \t |\033[90m AC = Armor Class  [Defense = AC / 2]\033[0m" << endl;
    cout << "\t|  CRIT = " << User.Stat.CRIT << "%" << "\t  |   [CritDmg = " << User.Stat.CRITMULT*100 << "%]" << " \t |\033[90m CRIT = Critical Hit%\033[0m" << endl;
    cout << "\t| DODGE = " << User.Stat.DODGE << "%" <<"\t  |   [XP Gain = " << User.Misc.XPMult*100 << "%]" << " \t |\033[90m DODGE = Dodge Chance%\033[0m" << endl;
    cout << "\t+-----------------+----------------------+" << endl;

    if (User.Misc.Type == PLAYER1 || User.Misc.Type == PLAYER2){

    cout << "\t"; XPBar(User);
    cout << "\t+----------------------------------------+" << endl;
    cout << "\t          Total Stat Count = " << TotalStats << "\n\n";

    cout << "-RELICS-" << "\n\n";
    StatMenuRelicCheck(User, RlcHighCarbonSword);
    StatMenuRelicCheck(User, RlcArcaneRing);
    StatMenuRelicCheck(User, RlcTarotNecklace);
    StatMenuRelicCheck(User, RlcWarlocksStone);
    StatMenuRelicCheck(User, RlcCutePouch);
    StatMenuRelicCheck(User, RlcCorruptSigil);
    StatMenuRelicCheck(User, RlcLuckyCharm);
    StatMenuRelicCheck(User, RlcCatStatue);
    StatMenuRelicCheck(User, RlcUnderworldSkull);
    StatMenuRelicCheck(User, RlcCheatScroll);
    StatMenuRelicCheck(User, RlcInsightfulLenses);
    StatMenuRelicCheck(User, RlcCeramicPot);
    StatMenuRelicCheck(User, RlcEdibleHeart);
    StatMenuRelicCheck(User, RlcEggPal);
    StatMenuRelicCheck(User, RlcMagicaCarnation);

    }else{
        cout << "\t          Total Stat Count = " << TotalStats << "\n\n";

        int Menucount = 0;

        cout << "ITEMS:" << endl;
        ItemMenuItem(Menucount, User.ItemBag.Item1);
        ItemMenuItem(Menucount, User.ItemBag.Item2);
        ItemMenuItem(Menucount, User.ItemBag.Item3);
        ItemMenuItem(Menucount, User.ItemBag.Item4);
        ItemMenuItem(Menucount, User.ItemBag.Item5);

        Menucount = 0;

        cout << "SPELLS:" << endl;
        SpellMenuSpell(User, Menucount, User.SpellBag.DefaultSpell);
        SpellMenuSpell(User, Menucount, User.SpellBag.SigSpell);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell1);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell2);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell3);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell4);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell5);
        SpellMenuSpell(User, Menucount, User.SpellBag.Spell6);
    }

    cout << "\n\n";
    EnterShort();

}

//- Battle Events - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void RevivebyUnderworldSkull(Entity&Player, Entity&Killer){

    if(Killer.Misc.Type == CHAMPION){
        if (Player.Misc.Type == PLAYER1){
                RlcUnderworldSkull.Obtained.P1 = false;
        }else if (Player.Misc.Type == PLAYER2){
            RlcUnderworldSkull.Obtained.P2 = false;    
        }
    }


    if (Player.Misc.Type == PLAYER1){
        if (RlcUnderworldSkull.Obtained.P1 == true){
            RlcUnderworldSkull.Obtained.P1 = false;
            goto Start;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcUnderworldSkull.Obtained.P2 == true){
            RlcUnderworldSkull.Obtained.P2 = false;
            goto Start;
        }
    }
    goto End;

    Start:
    clear();
    GameOver = false;
    Player.Stat.HP = 0;
    cout << "\n\n\n\n\n\n\n\n\n\n\n" << "\t\t\t\t\t\t\t";

        EntityBoxEdgeUI(Player);
        cout << endl << "\t\t\t\t\t\t\t";
        cout << "| " << Player.Name << ": " << Player.Stat.HP << "/" << Player.Stat.MAXHP << " HP";
        cout << endl << "\t\t\t\t\t\t\t";
        EntityBoxEdgeUI(Player);
        cout << endl;

        sleep(3);
        clear();

        EntityBoxUI(Player, false, false);
        sleep(2);

        cout << endl << Player.Name << " fell on his knee... ";
        sleep(2);
        cout << "but then stood right back up" << "\n\n";
        sleep(2);
        cout << "\t (Sacrificed the Underworld Skull)" << "\n\n";
        sleep(2);
        Player.Stat.HP = Player.Stat.MAXHP/2;
        
        EntityBoxUI(Player, false, false);
        sleep(2);

        cout << endl << Player.Name << " didn't succumb to " << Killer.Name << "." << "\n\n";
        sleep(3);
        clear();

    End:
    return;
}
void PlayerDeath(Entity& Player, Entity& Killer){

    RevivebyUnderworldSkull(Player, Killer);
    
    if (GameOver == true){

        Player.Stat.HP = 0; 

        string DeathMSG[] = {
            "You suddenly feel Lightheaded",
            "You can't feel your legs",
            "Your Body is Numb",
            "You feel a sharp weapon tearing your torso",
            "It's... cold"
        };

        Chance = rand() % 5;

        sleep(1);

        clear();

        cout << "\n\n\n\n\n\n\n\n\n\n\n" << "\t\t\t\t\t\t\t";

        EntityBoxEdgeUI(Player);
        cout << endl << "\t\t\t\t\t\t\t";
        cout << "| " << Player.Name << ": " << Player.Stat.HP << "/" << Player.Stat.MAXHP << " HP";
        cout << endl << "\t\t\t\t\t\t\t";
        EntityBoxEdgeUI(Player);
        cout << endl;

        sleep(3);

        clear();

        EntityBoxUI(Player, false, false);
        sleep(2);

        cout << endl << DeathMSG[Chance] << "..." << "\n\n";
        sleep(2);

        cout << "It seems... ";
        sleep(2);
        cout << "you have succumbed to the " << Killer.Name << "." << "\n\n";
        sleep(3);

        cout << "What a truly "; sleep(1); cout << "foolish "; sleep(1); cout << "end..." << "\n\n";
        sleep(2);

        cout << "GAME OVER" << "\n\n";
        sleep(2);

        cout << "You got through " << TotalRound - 1 << " Rounds." << "\n\n";
        sleep(2);

        EnterShort();

        return;
   }
}

void StatusEffectsDamage(Entity& Target){

    if (Target.Status.Poison > 0){
        Damage = Target.Stat.MAXHP * 0.09;
        if(Damage < 3){
            Damage = 3;
        }
        if (Target.Status.Shock > 0){
            Damage *= 1.5;
        }
        if (Damage > 99){
            Damage = 99;
        }

        Target.Status.Poison--;

        cout << Target.Name << " is hurt by poison (" << Damage << " damage";
        if (Target.Status.Shock > 0) {
            cout << " [Shock Boost]";
        }
        cout << ")" << "\n\n";

        sleep(1);
        Target.Stat.HP -= Damage;
    }

     if (Target.Status.Burn > 0){

        Damage = (Target.Stat.MAXHP * 0.03) + Target.Status.Burn;
        if (Target.Status.Shock > 0){
            Damage *= 1.5;
        }

        Target.Status.Burn--;

        cout << Target.Name << " is burned (" << Damage << " damage";
        if (Target.Status.Shock > 0) {
            cout << " [Shock Boost]";
        }
        cout << ")" << "\n\n";

        sleep(1);
        Target.Stat.HP -= Damage;
    }

    if (Target.Status.Shock > 0){
        Target.Status.Shock--;
    }

    Damage = 0;
}

void LevelUPStatSpread(Entity& Player, int maxhp,int maxmana,float atk,float ma,float ac,float crit,float dodge){
    // Levels 2, 4, 6, 8 give a token; level 3 gives Great Heal and 9 gives Supreme Heal; Levels 5 and 10(MAX) give class spell upgrades; 1,2,3,4,5,6,,8,9,10
    Spell ClassSpellLv2;
    Spell ClassSpellLv3;
    int GiveToken = 0;
    string SpellUpgradeName = "No";
    Player.Misc.Level++;

    switch (Player.Misc.Class){
        case Gladiator:
        ClassSpellLv2 = SplCrossSlash;
        ClassSpellLv3 = SplOmnislash;
        break;

        case Wanderer:
        ClassSpellLv2 = SplArcaneBlast;
        ClassSpellLv3 = SplWarlockBlast;
        break;

        case Berserker:
        ClassSpellLv2 = SplEnragedCut;
        ClassSpellLv3 = SplVengeanceCut;
        break;

        case BlackKnight:
        ClassSpellLv2 = SplRoyalKnightStance;
        ClassSpellLv3 = SplBlackKnightStance;
        break;

        case God:
        ClassSpellLv2 = SplOmnislash;
        ClassSpellLv3 = SplOmnislash;
        break;

        default:
        ClassSpellLv2 = SplCrossSlash;
        ClassSpellLv3 = SplOmnislash;
        break;
    }
    
    switch (Player.Misc.Level) {
        case 2:
        GiveToken++;
        break;

        case 3:
        SpellUpgradeName = Player.SpellBag.DefaultSpell.Name;
        Player.SpellBag.DefaultSpell = SplGreatHeal;
        break;

        case 4:
        GiveToken++;
        break;

        case 5:
        SpellUpgradeName = Player.SpellBag.SigSpell.Name;
        Player.SpellBag.SigSpell = ClassSpellLv2;
        break;

        case 6:
        GiveToken++;
        break;

        case 8:
        GiveToken++;
        break;

        case 9:
        SpellUpgradeName = Player.SpellBag.DefaultSpell.Name;
        Player.SpellBag.DefaultSpell = SplSupremeHeal;
        break;

        case 10:
        SpellUpgradeName = Player.SpellBag.SigSpell.Name;
        Player.SpellBag.SigSpell = ClassSpellLv3;
        break;

        default:
        break;
    }

    cout << "-.-'-.-'-.-'-.-'-.-'-.-'-.-LEVEL UP-.-'-.-'-.-'-.-'-.-'-.-'-.-" << "\n\n"; sleep(1);

    cout << "                         " << Player.Name  << endl; usleep(500000);
    if (Player.Misc.Level == 10){
    cout << "        Lv " << Player.Misc.Level - 1 << "    "; usleep(50000); cout << ArrowAnim(28); usleep(50000); cout << "     Lv MAX      " << "\n\n"; sleep(1);
    }else{
    cout << "        Lv " << Player.Misc.Level - 1 << "    "; usleep(50000); cout << ArrowAnim(28); usleep(50000); cout << "     Lv " << Player.Misc.Level << "      " << "\n\n"; usleep(500000);
    }

    cout << "        MAX HP (" << Player.Stat.MAXHP << ")     "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"    MAX HP (" << Player.Stat.MAXHP + maxhp << ") [+" << maxhp << "]    " << endl; usleep(100000);
    cout << "      MAX Mana (" << Player.Stat.MAXMANA << ")     "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"  MAX Mana (" << Player.Stat.MAXMANA + maxmana << ") [+" << maxmana << "]    " << "\n\n"; usleep(100000);

    cout << "           ATK (" << Player.Stat.ATK << ")     "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"       ATK (" << Player.Stat.ATK + atk << ") [+" << atk << "]     " << "\n\n"; usleep(100000);

    cout << "            MA (" << Player.Stat.MA << ")     "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"        MA (" << Player.Stat.MA + ma << ") [+" << ma << "]     " << "\n\n"; usleep(100000);

    cout << "            AC (" << Player.Stat.AC << ")     "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"        AC (" << Player.Stat.AC + ac << ") [+" << ac << "]     " << "\n\n"; usleep(100000);

    cout << "         CRIT% (" << Player.Stat.CRIT << "%)    "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"     CRIT% (" << Player.Stat.CRIT + crit << "%) [+" << crit << "%]   " << endl; usleep(100000);
    cout << "        DODGE% (" << Player.Stat.DODGE << "%)    "; usleep(50000); cout << ArrowAnim(11); usleep(50000); cout <<"    DODGE% (" << Player.Stat.DODGE + dodge << "%) [+" << dodge << "%]  " << "\n\n"; usleep(100000);

    usleep(500000);

    if (GiveToken >= 1){
    cout << "   [+1 Spell Token!]" << "\n\n";
        usleep(500000);
    }
    if (SpellUpgradeName != "No"){
    cout << "   [Your '" << SpellUpgradeName << "' spell has been Upgraded!]" << "\n\n";
        usleep(500000);
    }
    
    cout << "-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.'-.-'-.-'-.-'-.-'-.-'-.-'-.-" << "\n\n";
    sleep(1);

    Player.Stat.MAXHP += maxhp;
    Player.Stat.HP += maxhp;
    Player.Stat.MAXMANA += maxmana;
    Player.Stat.MANA += maxmana;
    Player.Stat.ATK += atk;
    Player.Stat.MA += ma;
    Player.Stat.AC += ac;
    Player.Stat.CRIT += crit;
    Player.Stat.DODGE += dodge;
    Player.Misc.Spellslots += GiveToken;

    StatOverflowCheck(Player);

    EnterShort();
}
void LevelUP(Entity& Player){

    LevelUPAnim();

    switch (Player.Misc.Class){
        case Gladiator:
        LevelUPStatSpread(Player, 5, 4, 2, 2, 3, 1, 1.5);
        break;

        case Wanderer:
        LevelUPStatSpread(Player, 4, 5, 1, 4, 2, 1, 1);
        break;

        case Berserker:
        LevelUPStatSpread(Player, 6, 3, 3, 1, 2, 2, 1);
        break;

        case BlackKnight:
        LevelUPStatSpread(Player, 5, 4, 3, 3, 3, 0.5, 0.5);
        break;

        case God:
        LevelUPStatSpread(Player, 10, 5, 5, 5, 5, 3.5, 2.5);
        break;

        default:
        LevelUPStatSpread(Player, 1, 1, 1, 1, 1, 1, 1);
        break;
    }

    if (Player.Misc.Level >= 10){
        Player.Misc.XPThreshold = 0;
    }

}

void VictoryScreen(Entity& Player, Entity& Enemy){

    bool HPValid = false, AvailableItemSlot = true;
    int GainGold, GainXP, GainMana, GainHP = 0;

    int EnemyTotalStats = (Enemy.Stat.MAXHP + Enemy.Stat.AC + Enemy.Stat.ATK + Enemy.Stat.MA + Enemy.Stat.CRIT + Enemy.Stat.DODGE);

    Item SpoilItem = NoItem;
    SpoilItem.Name = "           None";

    FullHeal(Enemy);

    GainGold = ((Player.Misc.Level/2 + 1) + Enemy.Misc.Level + (Player.Stat.Gold/10) + 1) * Player.Misc.GoldMult;
    GainXP =   ((EnemyTotalStats) * ((Enemy.Misc.Level * 0.25) + 1) * Player.Misc.XPMult);
    GainMana = (Player.Stat.MAXMANA / 5) * Player.Misc.ManaMult;

    WaveRound++;
    TotalRound++;

    if (Player.Misc.Type == PLAYER1){ // EdibleHeart Check
        if (RlcEdibleHeart.Obtained.P1 == true){
            HPValid = true;
            GainHP = Player.Stat.MAXHP * 0.15;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcEdibleHeart.Obtained.P2 == true){
            HPValid = true;
            GainHP = Player.Stat.MAXHP * 0.15;
        }
    }

    if (Enemy.ItemBag.Item1.ID != NONE){
        SpoilItem = Enemy.ItemBag.Item1;
        ItemSlotPlayerCheck(Player, SpoilItem, AvailableItemSlot);
        if (AvailableItemSlot == false){
            SpoilItem = NoItem;
            SpoilItem.Name = "           None";
        }
    }

    clear();
    cout << "\n\n\033[92m";
    cout << "\t   \\    /.  __ ___ ___  ___        |" << endl;
    cout << "\t    \\  / | /    | /   \\ |__) \\  /  |\033[0m" << endl;
    cout << "\t+- - \033[92m\\/  | \\__  | \\___/ |  \\  \\/   .\033[0m - -+" << endl;
    cout << "\t*                           \033[92m  /  \033[0m       *" << endl;
    cout << "\t* \033[33mMoney\033[0m Gained:                 " << GainGold << goldshow() << " \t*" << endl;
    cout << "\t*                                       *" << endl;
    cout << "\t* \033[92mXP\033[0m earned:                    " << GainXP << " \033[92mXP\033[0m\t*" << endl;
    cout << "\t*                                       *" << endl;
    cout << "\t* \033[94mMana\033[0m Restored:                " << GainMana << " \033[94mMana\033[0m\t*" << endl;
    cout << "\t*                                       *" << endl;
    if (HPValid == true){
    cout << "\t* \033[91mHP\033[0m Healed:                    " << GainHP << " \033[91mHP\033[0m \t*" << endl;
    cout << "\t*                                       *" << endl;
    }
    cout << "\t*   Spoils:        " << SpoilItem.Name << "     \t*" << endl;
    cout << "\t*                                       *" << endl;
    cout << "\t+ - - - - - - - - - - - - - - - - - - - +" << "\n\n";

    Player.Stat.Gold += GainGold;
    Player.Stat.XP += GainXP;
    Player.Stat.MANA += GainMana;
    Player.Stat.HP += GainHP;

    cout << "\t"; XPBar(Player);
    cout << endl;
    sleep(1);

    

    StatOverflowCheck(Player);

    EnterShort();

    if (Player.Stat.XP >= Player.Misc.XPThreshold && Player.Misc.Level < 10){

        int threshholds[] = {0, 100, 150, 220, 300, 400, 500, 600, 720, 860, 999}; // 4849 total XP needed

        Player.Stat.XP -= Player.Misc.XPThreshold;
        LevelUP(Player);
        Player.Misc.XPThreshold = threshholds[Player.Misc.Level];
    }
}

Relic* RelicRandom(Relic *getRelic){
    Chance = rand() % TotalRelics + 1;

    switch (Chance){
        case 1:
        return &RlcHighCarbonSword;
        break;

        case 2:
        return &RlcArcaneRing;
        break;

        case 3:
        return &RlcTarotNecklace;
        break;

        case 4:
        return &RlcWarlocksStone;
        break;

        case 5:
        return &RlcCutePouch;
        break;

        case 6:
        return &RlcCorruptSigil;
        break;

        case 7:
        return &RlcLuckyCharm;
        break;

        case 8:
        return &RlcCatStatue;
        break;

        case 9:
        return &RlcUnderworldSkull;
        break;

        case 10:
        return &RlcCheatScroll;
        break;

        case 11:
        return &RlcInsightfulLenses;
        break;

        case 12:
        return &RlcCeramicPot;
        break;

        case 13:
        return &RlcEdibleHeart;
        break;

        case 14:
        return &RlcEggPal;
        break;

        case 15:
        return &RlcMagicaCarnation;
        break;
    }
    return &NoRelic;
}
void RelicDrop(Entity& Player){
    clear();

    int Action;
    bool validchoice = false;

    Relic* Option1 = RelicRandom(Option1);
    Relic* Option2 = RelicRandom(Option2);
    Relic* Option3 = RelicRandom(Option3);
    Relic* Option4 = RelicRandom(Option4);

    while(true){// Relic Choice 1 Deciding
    Relic1:
    Option1 = RelicRandom(Option1);

        if (Player.Misc.Type == PLAYER1){
            if(Option1->Obtained.P1 == false){
                break;
            }else{goto Relic1;}

        }else if (Player.Misc.Type == PLAYER2){
            if(Option1->Obtained.P2 == false){
                break;
            }else{goto Relic1;}
        }
    }
    while(true){// Relic Choice 2 Deciding
    Relic2:
    Option2 = RelicRandom(Option2);

        if (Option2 == Option1){
            goto Relic2;
        }

        if (Player.Misc.Type == PLAYER1){
            if(Option2->Obtained.P1 == false){
                break;
            }else{goto Relic2;}

        }else if (Player.Misc.Type == PLAYER2){
            if(Option2->Obtained.P2 == false){
                break;
            }else{goto Relic2;}
        }
    }
    while(true){// Relic Choice 3 Deciding
    Relic3:
    Option3 = RelicRandom(Option3);

        if (Option3 == Option2 || Option3 == Option1){
            goto Relic3;
        }   

        if (Player.Misc.Type == PLAYER1){
            if(Option3->Obtained.P1 == false){
                break;
            }else{goto Relic3;}

        }else if (Player.Misc.Type == PLAYER2){
            if(Option3->Obtained.P2 == false){
                break;
            }else{goto Relic3;}
        }
    }
    while(true){// Relic Choice 4 Deciding
    Relic4:
    Option4 = RelicRandom(Option4);

        if (Option4 == Option3 || Option4 == Option2 || Option4 == Option1){
            goto Relic4;
        }   

        if (Player.Misc.Type == PLAYER1){
            if(Option4->Obtained.P1 == false){
                break;
            }else{goto Relic4;}

        }else if (Player.Misc.Type == PLAYER2){
            if(Option4->Obtained.P2 == false){
                break;
            }else{goto Relic4;}
        }
    }

    RelicDropPopupUI();

    while(true){

        RelicMenuUI(*Option1, *Option2, *Option3, *Option4);

        cout << "Choose one: ";
        PlayerInput(Action);

        switch (Action){
            case 1:
            validchoice = true;
            RelicEffects(Player, Option1);
            break;

            case 2:
            validchoice = true;
            RelicEffects(Player, Option2);
            break;

            case 3:
            validchoice = true;
            RelicEffects(Player, Option3);
            break;

            case 4:
            validchoice = true;
            RelicEffects(Player, Option4);
            break;

            default:
            cout << "Invalid Choice";
            sleep(1);
            clear();
            break;
        }

        if(validchoice == true){
            break;
        }
    }
    clear();
}

void EnemyScaling(Entity& enemy){

    enemy.ItemBag.Item1 = ItemGetRandomEnemy();

    EntityType Type = enemy.Misc.Type;

Entity F3(96,30,36,3,20,0,5,0, Type, "Enemy");
Entity F2(74,25,30,3,14,0,4,0, Type, "Enemy");
Entity F1(50,20,22,3,10,0,3,0, Type, "Enemy");

Entity W6(1,70,4,3,0,0,0,0, FALLEN, "Fallen");
Entity W5(112,25,27,11,0,0,4,0, Type, "Enemy");
Entity W4(70,20,19,3,8,0,3,0, Type, "Enemy");
Entity W3(40,15,13,3,5,0,2,0, Type, "Enemy");
Entity W2(24,10,8,3,2,0,1,0, Type, "Enemy");
Entity W1(16,5,4,3,0,0,0,0, Type, "Enemy");

    float AttackScale = 0.5;
    int AttackScaleMult = 1;

    float ACScale = 0.25;
    int ACScaleMult = 1;

    switch (Floor){
        case 3:
        enemy = F3;
        AttackScaleMult = 4;
        ACScaleMult = 4;
        break;

        case 2:
        enemy = F2;
        AttackScaleMult = 3;
        ACScaleMult = 4;
        break;

        case 1:
        enemy = F1;
        AttackScaleMult = 3;
        ACScaleMult = 3;
        break;
        
        case 0:
            switch (Wave){
                case 6:
                enemy = W6;
                break;

                case 5:
                enemy = W5;
                AttackScaleMult = 4;
                ACScaleMult = 4;
                break;

                case 4:
                enemy = W4;
                AttackScaleMult = 3;
                ACScaleMult = 4;
                break;

                case 3:
                enemy = W3;
                AttackScaleMult = 2;
                ACScaleMult = 3;
                break;

                case 2:
                enemy = W2;
                AttackScaleMult = 2;
                ACScaleMult = 2;
                break;

                case 1:
                enemy = W1;
                break;
            }
        break;
    }

    switch (WaveRound){
        case 1:
        enemy.Stat.MAXHP *= 1;
        enemy.Stat.ATK += (AttackScale * WaveRound) * AttackScaleMult;
        enemy.Stat.AC += (ACScale * WaveRound) * ACScaleMult;
        break;
        case 2:
        enemy.Stat.MAXHP *= 1.20;
        enemy.Stat.ATK += (AttackScale * WaveRound) * AttackScaleMult;
        enemy.Stat.AC += (ACScale * WaveRound) * ACScaleMult;
        break;
        case 3:
        enemy.Stat.MAXHP *= 1.40;
        enemy.Stat.ATK += (AttackScale * WaveRound) * AttackScaleMult;
        enemy.Stat.AC += (ACScale * WaveRound) * ACScaleMult;
        break;
        case 4:
        enemy.Stat.MAXHP *= 1.60;
        enemy.Stat.ATK += (AttackScale * WaveRound) * AttackScaleMult;
        enemy.Stat.AC += (ACScale * WaveRound) * ACScaleMult;
        break;
        case 5:
        enemy.Stat.MAXHP *= 2;
        enemy.Stat.ATK += (AttackScale * WaveRound) * AttackScaleMult * 1.25;
        enemy.Stat.AC += (ACScale * WaveRound) * ACScaleMult * 1.25;
        enemy.Stat.CRIT = 5;
        break;
    }

    enemy.Stat.HP = enemy.Stat.MAXHP;
}

//- Battle Turns and Battles - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void PlayerTurnBattle(Entity& Player, Entity& Enemy){
Start:
    PlayerTurn = true;
    Damage = 0;
    Player.Stat.DEF = Player.Stat.AC / 2;

    bool validturn = false;
    bool Insight = false;
    int Action; // 0 = Defend, 1 = Attack, 2 = Spells, 3 = Consumable, 4 = Stats

    
    if (Player.Misc.Type == PLAYER1){ // Insightful Lenses Check
        if (RlcInsightfulLenses.Obtained.P1 == true){
            Insight = true;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcInsightfulLenses.Obtained.P2 == true){
            Insight = true;
        }
    }


    if (Player.Status.Shock > 0){// Shock Check
        Player.Stat.DEF /= 3;
    }
    if (Player.Status.Freeze > 0){//Freeze Check
        PlayerTurn = false;
        BattleUI(Player, Enemy, Insight);
        sleep(1);
        cout << "You're Frozen" << endl << endl;
        sleep(1);
        Player.Status.Freeze--;
        return;
    }

        while (true){

            BattleUI(Player, Enemy, Insight);

            cout << "Your Turn: ";
            PlayerInput(Action);

            validturn = true;

            switch (Action) {

                case 0:
                    cout << Player.Name << " used Defend" << "\n\n";
                    Defend(Player);
                    break;

                case 1:
                    cout << Player.Name << " used Attack" << "\n\n";
                    BasicAttack(Player, Enemy);
                    break;

                case 2:
                    SpellPlayerAction(Player, Enemy, validturn);
                    break;

                case 3:
                    ItemPlayerAction(Player, Enemy, validturn);
                    break;

                case 4:
                    StatMenu(Player);
                    validturn = false;
                    break;

                case 5:
                if(Insight == true){
                    StatMenu(Enemy);
                    validturn = false;
                    break;
                }else{goto invalid;}

                default:
                    invalid:
                    cout << "Invalid move";
                    validturn = false;
                    sleep (1);
                    clear();
            }

            if (validturn == true){
                PlayerTurn = false;
                break;
            }

        }

    Enemy.Stat.HP -= Damage;
    StatusEffectsDamage(Enemy);

            
    if (Player.Misc.Type == PLAYER1){ // EggPal Check
        if (RlcEggPal.Obtained.P1 == true){
            Chance = rand() % 2 + 1;
            if (Chance == 2){// 50% chance
                EggPalAction(Player, Enemy);
            }
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcEggPal.Obtained.P2 == true){
            Chance = rand() % 2 + 1;
            if (Chance == 2){// 50% chance
                EggPalAction(Player, Enemy);
            }
        }
    }

    if (Enemy.Stat.HP <= 0){ //Return if dead enemy
        return;
    }    

    if (Player.Misc.Type == PLAYER1){ // CheatScroll Check
        if (RlcCheatScroll.Obtained.P1 == true){
            Chance = rand() % 20 + 1;
            if (Chance <= 3){// 15% chance
                cout << endl << "_  _  _ _ _ ____EXTRA TURN____ _ _ _  _  _" << "\n\n";
                goto Start;
            }
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcCheatScroll.Obtained.P2 == true){
            Chance = rand() % 20 + 1;
            if (Chance <= 3){
                cout << endl << "_  _  _ _ _ ____EXTRA TURN____ _ _ _  _  _" << "\n\n";
                goto Start;
            }
        }
    }

    usleep(500000);
    clear();
}
void EnemyTurnBattle(Entity& Enemy, Entity& Player){

    Damage = 0;
    Enemy.Stat.DEF = Enemy.Stat.AC / 2;
    bool Insight;

    if (Enemy.Status.Shock > 0){
        Enemy.Stat.DEF /= 3;
    }

    if (Enemy.Status.Freeze > 0){//Freeze Check
        cout << Enemy.Name << " is \033[1;96mFrozen\033[0m" << endl << endl;
        sleep(1);
        Enemy.Status.Freeze--;
        return;
    }

    BattleUI(Player, Enemy, Insight);
    usleep(350000);

        int EnemyAction = 1;

        if (Enemy.Stat.HP <= (Enemy.Stat.MAXHP / 4) ){ //Defend Chance
            Chance = rand() % 3 + 1;
            if (Chance == 3){
                EnemyAction = 0;
            }
        }

        switch (EnemyAction){ //0 - Defend  1 - Attack

            case 0:
                cout << Enemy.Name << " used Defend" << "\n\n";
                Defend(Enemy);
                break;

            case 1:
                cout << Enemy.Name << " used Attack" << "\n\n";
                BasicAttack(Enemy, Player);
                break;

        }

    Player.Stat.HP -= Damage;
    StatusEffectsDamage(Player);

    usleep(500000);
    clear();
}

void ChampionTurnBattle(Entity& Player, int& ChargeTurns){
    
    Damage = 0;
    TheChampion.Stat.DEF = TheChampion.Stat.AC / 2;
    bool Insight;

    if (TheChampion.Status.Shock > 0){
        TheChampion.Stat.DEF /= 3;
    }

    //BattleUI(Player, TheChampion, Insight);

    if (TheChampion.Status.Freeze > 0){//Freeze Check
        cout << TheChampion.Name << " is Frozen" << endl << endl;
        sleep(1);
        TheChampion.Status.Freeze--;
        return;
    }

    switch (ChargeTurns){ //Dialogue(Player,Hero,Champion,false,"\033[1;95m","","\033[0m",0);
        case 5:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t_______","\t\t\t\t\t\t|_____","\t\t\t\t\t\t______|\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","5 waves of brutal fights that lead you here","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Just to end up vanquished like the others","\033[0m",0);
        break;
        case 4:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t|     |","\t\t\t\t\t\t|_____|","\t\t\t\t\t\t      |\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","4 Warriors who attempted to become victorious","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","All have succumbed to me","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","You are no diferent","\033[0m",0);
        break;
        case 3:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t_______","\t\t\t\t\t\t______|","\t\t\t\t\t\t______|\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Mother Dasha... Father Sogro...","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Family... I want to forget","\033[0m",0);
        break;
        case 2:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t_______","\t\t\t\t\t\t______|","\t\t\t\t\t\t|______\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","The Twin Kings, who's greed cannot be exceed","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","They will bring this land to ruin","\033[0m",0);
        break;
        case 1:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t   /|","\t\t\t\t\t\t '  |","\t\t\t\t\t\t ___|___\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","You, one last insignificant Warrior, whom stands in my path for eternal power","\033[0m",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Take your last breath","\033[0m",0);
        break;
        case 0:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m\t\t\t\t\t\t ______","\t\t\t\t\t\t|      |","\t\t\t\t\t\t|______|\033[0m",0);
        DialogueDramatic(Player,Hero,Champion,false,"","","Time's up","\033[1;95m",120000,800000);
        DialogueDramatic(Player,Hero,Champion,false,"","","May you be remebered for your efforts","\033[1;95m",120000,800000);
        DialogueDramatic(Player,Hero,Champion,false,"","","Farewell, fallen Warrior","\033[1;95m",250000,1200000);

        ArmageddonAnim("\033[45;30m", 1.3);
        Damage = 9999;
        break;
    }

    ChargeTurns--;
    Player.Stat.HP -= Damage;
    StatusEffectsDamage(Player);
}



void Battle(Entity& Player, Entity& Enemy){
    if (Enemy.Misc.Type == BOSS){
        BossIncomingUI();
        BossWeakeningbyCorruptSigil(Player, Enemy); // Corrupt Sigil Check
        cout << "- -BOSS ROUND- -" << "\n\n";
    }else{
        cout << "< ROUND: " << WaveRound << " >\n\n";
    }
    
    Enemy.Stat.DEF = Enemy.Stat.AC / 2;

    while (true){

        if (Player.Stat.HP <= 0){//Player Death
            GameOver = true;
            PlayerDeath(Player, Enemy);
            return;
        }

            PlayerTurnBattle(Player, Enemy);

        if (Enemy.Stat.HP <= 0) {//Enemy Death
            Enemy.Stat.HP = 0;
            cout << Enemy.Name << " has been slayed." << "\n\n";
            sleep(1);
            break;
        }

            EnemyTurnBattle(Enemy, Player);

    }
    VictoryScreen(Player, Enemy);
}


void BattleChampion(Entity& Player){

        int ChargeTurns = 5;

        BossWeakeningbyCorruptSigil(Player, TheChampion); // Corrupt Sigil Check

        cout << "\033[1;95m< FINAL ROUND >\033[0m\n\n";
    
    TheChampion.Stat.DEF = TheChampion.Stat.AC / 2;
    ChampionAppearAnim();
    DE_ChampionBattleBegin(Player);

    ChampionIncomingUI();
    while (true){

        if (Player.Stat.HP <= 0){//Player Death
            GameOver = true;
            PlayerDeath(Player, TheChampion);
            return;
        }

            PlayerTurnBattle(Player, TheChampion);

        if (TheChampion.Stat.HP <= 0) {//Champion Death
            TheChampion.Stat.HP = 0;
            sleep(1);
            ScreenFlash(6);
            DE_ChampionBattleDefeated(Player1);
            DialogueWhite(Player1,Nochar,Nochar,true,"","","",1);
            sleep(1);
            DE_ChampionNoraDeath(Player1);
            break;
        }

            ChampionTurnBattle(Player, ChargeTurns);

    }
    
    VictoryScreen(Player, TheChampion);

}


void BattlePVP(Entity& Player1, Entity& Player2){ 
    cout << "- -PVP Round- -" << "\n\n";
    BossWeakeningbyCorruptSigil(Player1, Player2);
    BossWeakeningbyCorruptSigil(Player2, Player1);
    
    Player2.Stat.DEF = EnemyA.Stat.AC / 2;
    goto begin;

    while (true){

        if (Player1.Stat.HP <= 0){//Player1 Death
            GameOver = true;
            PlayerDeath(Player1, Player2);
            return;
        }else{PlayerSwitchUI();}

        begin:
            PlayerTurnBattle(Player1, Player2);

            if (Player2.Stat.HP <= 0){//Player2 Death
                GameOver = true;
                PlayerDeath(Player2, Player1);
                return;
            }else {PlayerSwitchUI();}

        PlayerTurnBattle(Player2, Player1);

    }

}


//---SHOP OR SHUFFLE TIME------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------||||
//- Cards and Tag Classes - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

enum TagID{
    UPGRADE = 1,
    ITEM = 2,
    SPELL = 3
};
enum UpCardID{
    MAXHP = 1,
    ATK = 2,
    MA = 3,
    AC = 4,
    CRIT = 5,
    DODGE = 6,
    HEAL = 7
};

class UpCard{
    public:

    UpCardID ID;
    float StatBoost;//
    int Rank = 1;//
    string StatName;
    string RankShow;//
    string BoostShow;//
};
UpCard Card1, Card2, Card3;

class ShopTag{
    public:

    TagID ID;
    Item TagItem = NoItem;
    Spell TagSpell = NoSpell;
    Upgrade TagUpgrade = NoUpgrade;
    bool SoldOut = false;
    int Price;
    struct TagUI{
        string Type;
        string Name;
        string Desc;
        string Currency;
    }UI;
};
ShopTag Tag1, Tag2, Tag3;

//- Shuffle Time - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

                    // SBRN = Stat-Boost-Name-Rank     
void UPCardClassification(Entity& Player, UpCard& Card, float SBR1, string SBNR1, float SBR2, string SBNR2, float SBR3, string SBNR3, float SBR4, string SBNR4, float SBR5, string SBNR5){

    Card.Rank = 1;

    int PlayerRankChance = Player.Misc.Level;

    if (Player.Misc.Type == PLAYER1){// Tarot Necklace Check
        if (RlcTarotNecklace.Obtained.P1 == true){
            PlayerRankChance += 3;
        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcTarotNecklace.Obtained.P2 == true){
            PlayerRankChance += 3;
        }
    }


    Chance = rand() % 4 + 1;// + Ranks Chance
    if (Chance <= PlayerRankChance){
        Card.Rank++;
    }
    Chance = rand() % 10 + 1;
    if (Chance <= PlayerRankChance){
        Card.Rank++;
    }
    Chance = rand() % 18 + 1;
    if (Chance <= PlayerRankChance){
        Card.Rank++;
    }
    Chance = rand() % 25 + 1;
    if (Chance <= PlayerRankChance){
        Card.Rank++;
    }


    switch(Card.Rank){
        case 1:
        Card.BoostShow = SBNR1;
        Card.StatBoost = SBR1;
        Card.RankShow = "\033[1;37m * \033[0m";
        break;

        case 2:
        Card.BoostShow = SBNR2;
        Card.StatBoost = SBR2;
        Card.RankShow = "\033[1;37m **\033[0m";
        break;

        case 3:
        Card.BoostShow = SBNR3;
        Card.StatBoost = SBR3;
        Card.RankShow = "\033[1;37m***\033[0m";
        break;

        case 4:
        Card.BoostShow = SBNR4;
        Card.StatBoost = SBR4;
        Card.RankShow = "\033[1;37m 4*\033[0m";
        break;

        case 5:
        Card.BoostShow = SBNR5;
        Card.StatBoost = SBR5;
        Card.RankShow = "\033[1;37m 5*\033[0m";
        break;
    }
}
void UPCardRandomizer(Entity& Player, UpCard& Card){
    Chance = rand() % 7 + 1;

    switch (Chance){
        case 1:
        Card.ID = MAXHP;
        Card.StatName = "\033[1;92mMAXHP\033[0m";
        UPCardClassification(Player, Card, 2, " + 2 ", 4, " + 4 ", 6, " + 6 ", 8, " + 8 ", 10, "+ 10 ");
        break;

        case 2:
        Card.ID = ATK;
        Card.StatName = "\033[1;91m ATK \033[0m";
        UPCardClassification(Player, Card, 1, " + 1 ", 2, " + 2 ", 3, " + 3 ", 4, " + 4 ", 5, " + 5 ");
        break;

        case 3:
        Card.ID = MA;
        Card.StatName = "\033[1;94m  MA \033[0m";
        UPCardClassification(Player, Card, 1, " + 1 ", 2, " + 2 ", 3, " + 3 ", 4, " + 4 ", 5, " + 5 ");
        break;

        case 4:
        Card.ID = AC;
        Card.StatName = "\033[1;90m  AC \033[0m";
        UPCardClassification(Player, Card, 1, " + 1 ", 2, " + 2 ", 3, " + 3 ", 4, " + 4 ", 5, " + 5 ");
        break;

        case 5:
        Card.ID = CRIT;
        Card.StatName = "\033[1;31m CRIT\033[0m";
        UPCardClassification(Player, Card, 1, " + 1 ", 1.5, "+ 1.5", 2, " + 2 ", 3, " + 3 ", 3.5, "+ 3.5");
        break;

        case 6:
        Card.ID = DODGE;
        Card.StatName = "\033[1;93mDODGE\033[0m";
        UPCardClassification(Player, Card, 0.5, "+ 0.5", 1, " + 1 ", 1.5, "+ 1.5", 2, " + 2 ", 2.5, "+ 2.5");
        break;

        case 7:
        Card.ID = HEAL;
        Card.StatName = "\033[1;92m Heal\033[0m";
        UPCardClassification(Player, Card, 0.20, " 20% ", 0.35, " 35% ", 0.50, " 50% ", 0.60, " 60% ", 0.75, " 75% ");
        break;
    }
}
void TagRandomizer(ShopTag& Tag, Entity& Player){

    Tag.TagItem = ItemGetRandom();
    Tag.TagUpgrade = UpgradeGetRandom();

    while(true){
        Tag.TagSpell = SpellGetRandomShop();
        if (Tag.TagSpell.ID != Player.SpellBag.Spell1.ID){
        if (Tag.TagSpell.ID != Player.SpellBag.Spell2.ID){
        if (Tag.TagSpell.ID != Player.SpellBag.Spell3.ID){
        if (Tag.TagSpell.ID != Player.SpellBag.Spell4.ID){
        if (Tag.TagSpell.ID != Player.SpellBag.Spell5.ID){
        if (Tag.TagSpell.ID != Player.SpellBag.Spell6.ID){

            break;

        }}}}}}
    }

    SpellSubstitue:
    Chance = rand() % 3 + 1;

    switch (Chance){
        case 1:
        Tag.ID = UPGRADE;
        Tag.UI.Type = "\033[1;93mUpgrade\033[0m";
        Tag.UI.Name = Tag.TagUpgrade.Name;
        Tag.UI.Desc = Tag.TagUpgrade.Desc;
        Tag.Price = Tag.TagUpgrade.Price * Player.Misc.PriceMult;
        Tag.UI.Currency = goldshow();
        break;

        case 2:
        Tag.ID = ITEM;
        Tag.UI.Type = "-\033[1;92mItem\033[0m--";
        Tag.UI.Name = Tag.TagItem.Name;
        Tag.UI.Desc = Tag.TagItem.Desc;
        Tag.Price = Tag.TagItem.Price * Player.Misc.PriceMult;
        Tag.UI.Currency = goldshow();
        break;

        case 3:
        if (Player.Misc.Spellslots != 0){
        Tag.ID = SPELL;
        Tag.UI.Type = "-\033[1;94mSpell\033[0m-";
        Tag.UI.Name = Tag.TagSpell.Name;
        Tag.UI.Desc = Tag.TagSpell.Desc;
        Tag.Price = Tag.TagSpell.Price;
        Tag.UI.Currency = "\033[1;95m Token\033[0m";
        }else{goto SpellSubstitue;}
        break;
    }
}

void RerollShuffleTime(Entity& Player){

    UPCardRandomizer(Player, Card1);
    UPCardRandomizer(Player, Card2);
    UPCardRandomizer(Player, Card3);

    Tag1.SoldOut = false;
    Tag2.SoldOut = false;
    Tag3.SoldOut = false;

    Tag1:
    TagRandomizer(Tag1, Player);

    Tag2:
    TagRandomizer(Tag2, Player);
    if (Tag2.TagSpell.ID == Tag1.TagSpell.ID){goto Tag2;}

    Tag3:
    TagRandomizer(Tag3, Player);
    if (Tag3.TagSpell.ID == Tag1.TagSpell.ID || Tag3.TagSpell.ID == Tag2.TagSpell.ID){goto Tag3;}
}

void ItemSellMenuItem(int& Menucount, Item MenuItem){
    if (MenuItem.ID != NONE){
        Menucount++;
        cout << "| " << Menucount << " - " << MenuItem.Name << " " << MenuItem.Desc << " - " << (MenuItem.Price/2) + 1 << goldshow() << endl;
        cout << "| " << endl;
    }
}
void ItemSellMenuUI(Entity& Player){
    clear();
    int Menucount = 0;

    cout << "$ " << Yellow("SELL ITEM:") << " $" << "\n\n";

    EntityBoxUI(Player, true, true);
    cout << "                  Savings: " << Player.Stat.Gold << goldshow() << endl;

    cout << "+ - 0 > Go Back - - - - - - - - - - - - - - - - - - - - - - #" << "\n|\n";

    ItemSellMenuItem(Menucount,Player.ItemBag.Item1);
    ItemSellMenuItem(Menucount,Player.ItemBag.Item2);
    ItemSellMenuItem(Menucount,Player.ItemBag.Item3);
    ItemSellMenuItem(Menucount,Player.ItemBag.Item4);
    ItemSellMenuItem(Menucount,Player.ItemBag.Item5);

    for (int l = 0; l < Player.Misc.Itemslots; l++){
        cout << "| --" << endl;
        cout << "| " << endl;
    }

    cout << "+ - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #" << "\n\n";
}
void ItemPlayerSell(Entity& Player){

    int Action;
    
    while (true){

        ItemSellMenuUI(Player);

        cout << "Sell: ";
        PlayerInput(Action);

        bool validitemchoice = true;

        switch (Action){

            case 0:
                validitemchoice = false;
                clear();
                break;

            case 1:
                if (Player.ItemBag.Item1.ID != NONE){
                    Player.Stat.Gold += (Player.ItemBag.Item1.Price/2) + 1;
                    Player.ItemBag.Item1 = NoItem;
                    Player.Misc.Itemslots++;
                }else{goto invalid;}
                break;
            
            case 2:
            if (Player.ItemBag.Item2.ID != NONE){
                Player.Stat.Gold += (Player.ItemBag.Item2.Price/2) + 1;
                Player.ItemBag.Item2 = NoItem;
                Player.Misc.Itemslots++;
            }else{goto invalid;}
                break;
    
            case 3:
            if (Player.ItemBag.Item3.ID != NONE){
                Player.Stat.Gold += (Player.ItemBag.Item3.Price/2) + 1;
                Player.ItemBag.Item3 = NoItem;
                Player.Misc.Itemslots++;
            }else{goto invalid;}
                break;
    
            case 4:
            if (Player.ItemBag.Item4.ID != NONE){
                Player.Stat.Gold += (Player.ItemBag.Item4.Price/2) + 1;
                Player.ItemBag.Item4 = NoItem;
                Player.Misc.Itemslots++;
            }else{goto invalid;}
                break;
    
            case 5:
            if (Player.ItemBag.Item5.ID != NONE){
                Player.Stat.Gold += (Player.ItemBag.Item5.Price/2) + 1;
                Player.ItemBag.Item5 = NoItem;
                Player.Misc.Itemslots++;
            }else{goto invalid;}
                break;

            default:
            invalid:
                cout << "Invalid choice";
                sleep (1);
                clear();
                break;
        }

        for (int l = 0; l < 5; l++){// Item Slot Passing (To keep number arranged)
            ItemSlotPass(Player.ItemBag.Item4, Player.ItemBag.Item5);
            ItemSlotPass(Player.ItemBag.Item3, Player.ItemBag.Item4);
            ItemSlotPass(Player.ItemBag.Item2, Player.ItemBag.Item3);
            ItemSlotPass(Player.ItemBag.Item1, Player.ItemBag.Item2);
        }

        if (validitemchoice == false){
            break;
        }
    }

}

void SpellSlotPlayerCheck(Entity& Player, Spell& getSpell){
    if (Player.Misc.Spellslots != 0){
        if (Player.SpellBag.Spell1.ID == NOSPELL){
            Player.SpellBag.Spell1 = getSpell;

        }else if (Player.SpellBag.Spell2.ID == NOSPELL){
            Player.SpellBag.Spell2 = getSpell;

        }else if (Player.SpellBag.Spell3.ID == NOSPELL){
            Player.SpellBag.Spell3 = getSpell;

        }else if (Player.SpellBag.Spell4.ID == NOSPELL){
            Player.SpellBag.Spell4 = getSpell;

        }else if (Player.SpellBag.Spell5.ID == NOSPELL){
            Player.SpellBag.Spell5 = getSpell;

        }else if (Player.SpellBag.Spell6.ID == NOSPELL){
            Player.SpellBag.Spell6 = getSpell;
        }
    }  
}

void UpgradeTagBought(ShopTag& Tag, Entity& Player){

    int randomval = rand() % 20 + 1;

    if (randomval == 3){// 5% chance for slightly better upgrade and different message
        switch (Tag.TagUpgrade.ID){
            case CONSTITUTION:
            UpgradeEffectint(Player, Player.Stat.MAXHP, Player.Stat.MAXHP * 0.25, 12, "      You are Invincible      ", "MAXHP");
            Player.Stat.HP += 12;
            break;

            case SHARPENING:
            UpgradeEffectfloat(Player, Player.Stat.ATK, Player.Stat.ATK * 0.25, 6, "   Your Sword looks Fierce    ", " ATK ");
            break;

            case ARCBURST:
            UpgradeEffectfloat(Player, Player.Stat.MA, Player.Stat.MA * 0.25, 6, "The means whom all is revealed", "  MA ");
            break;

            case ARMORUP:
            UpgradeEffectfloat(Player, Player.Stat.AC, Player.Stat.AC * 0.25, 6, "Hey nice armor pal, very shiny", "  AC ");
            break;

            case SLEIGHTOFHAND:
            UpgradeEffectfloat(Player, Player.Stat.CRIT, 6, 0, "You're like a smooth criminal ", " CRIT");
            break;

            case LIGHTBOOTS:
            UpgradeEffectfloat(Player, Player.Stat.DODGE, 5, 0, " You're ready to dodge it all ", "DODGE");
            break;

            case FULLHEAL:
            FullHeal(Player);
            clear();
            cout << "\n   +" << NamelenghtBar(Player, "-") << "---------------------------------+" << endl;
            cout << "    " << Player.Name << " Fully Healed (and got refunded!)" << endl;
            cout << "   +" << NamelenghtBar(Player, "-") << "---------------------------------+" << "\n\n";
            Player.Stat.Gold += 10;
            sleep(1);
            EnterShort();
            clear();
            break;

            case TEMPERBAD:
            UpgradeEffectPercent(Player, Player.Stat.CRITMULT, 0.3, 0, "    You're out of Patience    ", "CritDmg");
            break;

            case LUCKYCLOVER:
            UpgradeEffectPercent(Player, Player.Misc.XPMult, 0.10, 0, "It's actually a 5-leaf clover!", "XP Gain");
            break;

            case ETHEREAL:
            UpgradeEffectint(Player, Player.Stat.MAXMANA, 5, 0, " You could say it's over 9000 ", " MANA");
            Player.Stat.MANA += 5;
            break;
        }
    }else{// Normal upgrades
        switch (Tag.TagUpgrade.ID){
            case CONSTITUTION:
            UpgradeEffectint(Player, Player.Stat.MAXHP, Player.Stat.MAXHP * 0.20, 10, " You feel Tougher than before ", "MAXHP");
            Player.Stat.HP += 10;
            break;

            case SHARPENING:
            UpgradeEffectfloat(Player, Player.Stat.ATK, Player.Stat.ATK * 0.20, 5, "   Your Sword looks Sharper   ", " ATK ");
            break;

            case ARCBURST:
            UpgradeEffectfloat(Player, Player.Stat.MA, Player.Stat.MA * 0.20, 5, "   Your Arcana is Revealed    ", "  MA ");
            break;

            case ARMORUP:
            UpgradeEffectfloat(Player, Player.Stat.AC, Player.Stat.AC * 0.20, 5, "   Your Armor is... Shinier   ", "  AC ");
            break;

            case SLEIGHTOFHAND:
            UpgradeEffectfloat(Player, Player.Stat.CRIT, 5, 0, "You're like a smooth trickster", " CRIT");
            break;

            case LIGHTBOOTS:
            UpgradeEffectfloat(Player, Player.Stat.DODGE, 4, 0, "You're ready to dodge anything", "DODGE");
            break;

            case FULLHEAL:
            FullHeal(Player);
            clear();
            cout << "\n\t+" << NamelenghtBar(Player, "-") << "-------------+" << endl;
            cout << "\t " << Player.Name << " Fully Healed" << endl;
            cout << "\t+" << NamelenghtBar(Player, "-") << "-------------+" << "\n\n";
            sleep(1);
            EnterShort();
            clear();
            break;

            case TEMPERBAD:
            UpgradeEffectPercent(Player, Player.Stat.CRITMULT, 0.2, 0, " Your Patience is running out ", "CritDmg");
            break;

            case LUCKYCLOVER:
            UpgradeEffectPercent(Player, Player.Misc.XPMult, 0.05, 0, "        You feel Lucky!       ", "XP Gain");
            break;

            case ETHEREAL:
            UpgradeEffectint(Player, Player.Stat.MAXMANA, 3, 0, " You feel calm and collected  ", " MANA");
            Player.Stat.MANA += 3;
            break;
        }
    }
    
}
void TagBought(Entity& Player, ShopTag& Tag){

    bool filler;

    if (Tag.SoldOut == true){// Sold Out
        cout << "It's sold out, ";
        sleep(1);
        cout << "bucko.";
        sleep(1);
        return;
    }

    switch (Tag.ID){
        case UPGRADE:
        if (Player.Stat.Gold < Tag.Price){// Not enough Gold
            cout << "Not enough gold, ";
            sleep(1);
            cout << "mate.";
            sleep(1);
            return;
        }
        UpgradeTagBought(Tag, Player);
        break;

        case ITEM:
        if (Player.Stat.Gold < Tag.Price){// Not enough Gold
            cout << "Not enough gold, ";
            sleep(1);
            cout << "mate.";
            sleep(1);
            return;
        }
        if (Player.Misc.Itemslots == 0){// Not enough Item Slots
            cout << "No space left, ";
            sleep(1);
            cout << "pal.";
            sleep(1);
            return;
        }
        ItemSlotPlayerCheck(Player, Tag.TagItem, filler);
        break;

        case SPELL:
        if (Player.Misc.Spellslots == 0){// Not enough Tokens/SpellSlots
            cout << "No more Tokens left, ";
            sleep(1);
            cout << "mano.";
            sleep(1);
            return;
        }
        SpellSlotPlayerCheck(Player, Tag.TagSpell);
        break;
    }

    if (Tag.UI.Currency == goldshow()){
        Player.Stat.Gold -= Tag.Price;
    }else{
        Player.Misc.Spellslots -= Tag.Price;
    }
    
    Tag.SoldOut = true;
}

void UPCardEffect(Entity& Player, UpCard& Card){

    switch (Card.ID){
        case MAXHP:
        Player.Stat.MAXHP += Card.StatBoost;
        Player.Stat.HP += Card.StatBoost;
        break;

        case ATK:
        Player.Stat.ATK += Card.StatBoost;
        break;

        case MA:
        Player.Stat.MA += Card.StatBoost;
        break;

        case AC:
        Player.Stat.AC += Card.StatBoost;
        break;

        case CRIT:
        Player.Stat.CRIT += Card.StatBoost;
        break;

        case DODGE:
        Player.Stat.DODGE += Card.StatBoost;
        break;

        case HEAL:
        Player.Stat.HP += (Player.Stat.MAXHP * Card.StatBoost);
        Player.Stat.MANA += (Player.Stat.MAXMANA * Card.StatBoost);
        break;
    }

    StatOverflowCheck(Player);

}
void UPCardAquire(Entity& Player, UpCard& Card){
    clear();
    UPCardAquireAnim(1, 30000, true, true);
    cout << "\033[0m";
    clear();

    cout << endl;
    cout << "\t\t~ ~~ ~~~ UP CARD BOOST ACQUIRED ~~~ ~~  ~" << "\n\n";

    cout << "\t\t                .-------." << endl;
    cout << "\t\t                | " << Card.StatName << " |" << endl;
    cout << "\t\t                | " << Card.BoostShow << " |" << endl;
    cout << "\t\t                |       |" << endl;
    cout << "\t\t                |Rnk:" << Card.RankShow <<"|" << endl;
    cout << "\t\t                `-------`" << "\n\n";
    sleep(2);

    UPCardEffect(Player, Card);
    clear();
}


string TagUI(ShopTag Tag, int UIpart){// UIpart: 1 is for the Type of tag; 2 is for Name and Desc; 3 is for Currency;
    string result;
    int space;
    int spaceend;
    switch(UIpart){
        case 1:
        if(Tag.SoldOut == false){
            result = Tag.UI.Type;
        }else{
            result = "\033[1m-------";
        }
        break;
        case 2:
        cout << "  |";

        if(Tag.UI.Type == "-\033[1;94mSpell\033[0m-"){
            space = (74 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagSpell.CC)) / 2;
            spaceend = (74 - space) - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagSpell.CC);
        }else if(Tag.UI.Type == "-\033[1;92mItem\033[0m--"){
            space = (74 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagItem.CC)) / 2;
            spaceend = (74 - space) - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagItem.CC);
        }else{
            space = (74 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagUpgrade.CC)) / 2;
            spaceend = (74 - space) - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagUpgrade.CC);
        }


        if (Tag.SoldOut == false){
            for (int l = 0; l < space; l++){
                cout << " ";
            }

            cout << Tag.UI.Name + " " + Tag.UI.Desc;

            if(Tag.UI.Type == "-\033[1;94mSpell\033[0m-"){
                space = (75 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagSpell.CC)) / 2;
            }else if(Tag.UI.Type == "-\033[1;92mItem\033[0m--"){
                space = (75 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagItem.CC)) / 2;
            }else{
                space = (74 - ((size(Tag.UI.Name) + size(Tag.UI.Desc)) - Tag.TagUpgrade.CC)) / 2;
            }

            for (int l = 0; l < spaceend; l++){
                cout << " ";
            }
            cout << "|";
            return "";
        }else{
            result = "                              -  SOLD OUT  -                               |";
        }
        break;
        case 3:
        if(Tag.SoldOut == false){
            if(Tag.UI.Currency == goldshow()){
                if (Tag.Price < 10){
                    cout << "-  " << Tag.Price;
                    result = Tag.UI.Currency + " -";
                }else if (Tag.Price > 99){
                    cout << "-" << Tag.Price;
                    result = Tag.UI.Currency + " -";
                }else{
                    cout << "- " << Tag.Price;
                    result = Tag.UI.Currency + " -";
                }
            }else{
                cout << Tag.Price;
                result = Tag.UI.Currency;
            }
        }else{
            cout << "       ";
        }
        break;
    }
    return result;
}
void ShuffleTimeUI(Entity& Player, int& RerollPrice){

    cout << "                              /'-'-.-'-.-'-.-'\\ " << endl;
    cout << "                              | SHUFFLE TIME! |" << endl;
    cout << "                              \\.-.-'-.-'-.-'-./" << endl;
    cout << "" << endl;
    cout << " +-----------+    UP Cards:                                      " <<                                                          "+-------------+" << endl;
    cout << " | 7 - "<<Yellow("Sell")<<"  |       .-------.     .-------.     .-------.       " <<                                          " Savings: " << Player.Stat.Gold << goldshow() << endl;
    cout << " +-----------+       | " << Card1.StatName << " |     | " << Card2.StatName << " |     | " << Card3.StatName << " |      "<<  " +-------------+" << endl;
    cout << " | 8 - Stats |       | " << Card1.BoostShow << " |     | " << Card2.BoostShow << " |     | " << Card3.BoostShow << " |          " << tokensshow() << ": " << Player.Misc.Spellslots << endl;
    cout << " +-----------+       |       |     |       |     |       |       " <<                                                          "+-------------+" << endl;
    cout << " |9 - Options|       |Rnk:" << Card1.RankShow << "|     |Rnk:" << Card2.RankShow << "|     |Rnk:" << Card3.RankShow << "|                       " << endl;
    cout << " +-----------+       `-------`     `-------`     `-------`     (0) - " << Green("Reroll") << " - " << RerollPrice << goldshow() << endl;
    cout << "                        (1)           (2)           (3)                          " << endl;
    cout << "#-'-.-TAGS:-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#" << endl;
    cout << "\033[1m  +--TagA---------------------------" << TagUI(Tag1,1) << "\033[1m-----------------------------------+  \033[0m" << endl;
    cout <<                                           TagUI(Tag1,2) << endl; 
    cout <<        "  |                                 " << TagUI(Tag1,3) << "                                   |" << endl;
    cout << "\033[1m  +-----------------------------------(4)-------------------------------------+  \033[0m" << "\n\n";

    cout << "\033[1m  +--TagB---------------------------" << TagUI(Tag2,1) << "\033[1m-----------------------------------+  \033[0m" << endl;
    cout <<                                           TagUI(Tag2,2) << endl; 
    cout <<        "  |                                 " << TagUI(Tag2,3) << "                                   |" << endl;
    cout << "\033[1m  +-----------------------------------(5)-------------------------------------+  \033[0m" << "\n\n";

    cout << "\033[1m  +--TagC---------------------------" << TagUI(Tag3,1) << "\033[1m-----------------------------------+  \033[0m" << endl;
    cout <<                                           TagUI(Tag3,2) << endl; 
    cout <<        "  |                                 " << TagUI(Tag3,3) << "                                   |" << endl;
    cout << "\033[1m  +-----------------------------------(6)-------------------------------------+  \033[0m" << endl;
    cout << "#-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#" << endl;
}

void ShuffleTime(Entity& Player){

    int RerollPrice = 3;
    int Action;
    bool validchoice = false;

    RerollShuffleTime(Player);

    while(true){

        ShuffleTimeUI(Player, RerollPrice);


        cout << Player.Name << ": ";
        PlayerInput(Action);

        switch (Action){
            case 0:
            if (Player.Stat.Gold >= RerollPrice){//Reroll Shop
                Player.Stat.Gold -= RerollPrice;
                RerollPrice += 2;
                RerollShuffleTime(Player);
            }else{
                cout << "Not enough Gold, ";
                sleep(1);
                cout << "mate.";
                sleep(1);
            }
            break;

            case 1:
            UPCardAquire(Player, Card1);
            validchoice = true;
            break;

            case 2:
            UPCardAquire(Player, Card2);
            validchoice = true;
            break;

            case 3:
            UPCardAquire(Player, Card3);
            validchoice = true;
            break;

            case 4:
            TagBought(Player, Tag1);
            break;

            case 5:
            TagBought(Player, Tag2);
            break;

            case 6:
            TagBought(Player, Tag3);
            break;

            case 7:
            ItemPlayerSell(Player);
            break;

            case 8:
            StatMenu(Player);
            break;

            case 9:
            Options();
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


//--Cell Interactions-------------------------------------------------------------------------------------------------------------------------------------------------------------------------||

    //Prison Talk Events - - - - - - - - - - - - - - - - - - - - - - - -||
    void PrisonEvent1(Entity& Player){//DONE

        int SpecATK = Player.Stat.ATK/3;
        int SpecMAXHP = Player.Stat.MAXHP/2.5;
        int SpecAC = Player.Stat.AC/2;

        Entity PrisonerBad(SpecMAXHP,10,SpecATK,5,SpecAC,0,35,5,ENEMY, "Prisoner");

    Dialogue(Player, Hero, Prisoner, false, "Hello there buddy","","",0);
    Dialogue(Player, Hero, Prisoner, true, "May I ask what made you end up in this cell?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Oh, me?","I'll tell you","Come closer",0);
    DialogueChoice(Player,Hero,Prisoner,true,"Aproach him","Don't","",Chance);
    switch (Chance){
        case 1:
        DialogueFlash(Player, Hero, Prisoner, true,"\033[91m");
        Dialogue(Player, Hero, Prisoner, false, "GOT YOU \033[91mBUDDY\033[0m","","",0);
        Battle(Player, PrisonerBad);
        Player.Stat.Kindness += 3;
        Player.Stat.Gold += 10;
        Dialogue(Player, Hero, Nochar, true, "That was sudden...","","",0);
        Dialogue(Player, Hero, Nochar, true, "Looks like he dropped some extra \033[93mMoolah\033[0m at least...","","",0);
        Dialogue(Player, Hero, Nochar, true, "\033[90m(Looks like you got an extra \033[93m10g\033[0m)","","",0);
        Dialogue(Player, Hero, Nochar, true, "\033[90m(You walked away, back to the Arena)","","",0);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I don't trust you, sorry","","",0);
        Dialogue(Player, Hero, Prisoner, false, "I SAID COME CLOSER YOU \033[91mBASTARD\033[0m","","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(You ran away, back to the Arena)","","",0);
        break;
    }
    
}
    void PrisonEvent2(Entity& Player){//DONE
        int GambleGold = 0;
    
    Dialogue(Player, Hero, Prisoner, false, "Ahoy there pretty one!","","",0);
    Dialogue(Player, Hero, Prisoner, true, "May I ask what made you end up in this cell?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Ohoho,","Funny question|","It was \033[93mGambling\033[0m darling!",0);
    Dialogue(Player, Hero, Prisoner, true, "O-oh, really?","I've heard about going bankrupt from it, but never arrested","How did you even manage that?",0);
    Dialogue(Player, Hero, Prisoner, false, "The \033[93mKings\033[0m made gambling \033[91millegal\033[0m outside of the Colosseum...","Something about disrespect and making more money by only having them here or something.","",0);
    Dialogue(Player, Hero, Prisoner, false, "BUT THAT DIDN'T STOP ME SWEETHEART!","I KEPT GAMBLING 'TILL MY \033[1mLAST ROLL\033[0m","'TILL THERE WERE NO MORE \033[1;96mCHIPS\033[0m TO GIVE",0);
    Dialogue(Player, Hero, Prisoner, true, "Quite... Impressive? Sassy one...","\033[90m(This guy is nuts over this addiction)\033[0m","",0);
    Dialogue(Player, Hero, Prisoner, false, "Say dear, wouldn't you like to perform a little gamble?","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Me? I'm not su-","","",900000);
    Dialogue(Player, Hero, Prisoner, false, "IT'S A SIMPLE NUMBERS GAME","You will rool a D6, and for each amount of number you get, I will give you \033[93m5g\033[0m!","        \033[90m(Dice with 6 numbers)\033[0m                  How does that sound sweetheart?",0);
    Dialogue(Player, Hero, Prisoner, true, "What... What about on my part?","You just end up loosing money like that...","Why would you do that?",0);
    Dialogue(Player, Hero, Prisoner, false, "IT'S FOR THE KICK OF IT DARLING!","THE EXCITEMENT OF THE ROLL","THE SMELL OF THE GAME",0);
    Dialogue(Player, Hero, Prisoner, false, "I JUST WANT TO SEE IT ONCE MORE, SO...","Ahem","Will you roll?",0);

    DialogueChoice(Player,Hero,Prisoner,true,"GAMBLE!","Turn down the offer","",Chance);
    switch (Chance){
        case 1:
        Player.Stat.Kindness += 3;
        Dialogue(Player, Hero, Prisoner, true, "Sure, let us enjoy this Gamble","","",0);
        Dialogue(Player, Hero, Prisoner, false, "YESS!","I KNEW YOU'D BE DOWN DEAR","",0);

        DialogueChoice(Player,Hero,Prisoner,true,"Roll the Dice","","",Chance);
        D6Roll();
        GambleGold = Chance * 5;
        usleep(600000);
        cout << "\n\t\t\t5";
        usleep(600000);
        cout << " x \033[93m";
        usleep(600000);
        cout << Chance << "\033[0m";
        usleep(600000);
        cout << " = \033[93m";
        usleep(600000);
        cout << GambleGold << "g\033[0m!";
        sleep(2);
        Player.Stat.Gold += GambleGold;

        Dialogue(Player, Hero, Prisoner, true, "\033[90m(The prisioner put the \033[93mreward gold\033[90m in your pocket)\033[0m","","",0);
        switch (Chance){
            case 1:
            Dialogue(Player, Hero, Prisoner, false, "OOOOO...","Not very lucky now, are we dear...","Welp! It was still worth a shot",0);
            break;
            case 6:
            Dialogue(Player, Hero, Prisoner, false, "GREAT HEAVENS!","OHOHOHOHOHO","",0);
            Dialogue(Player, Hero, Prisoner, false, "IMPECABLE!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "PRECISE!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "TASTY!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "SATISFYING!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "DELICATE!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "SCRUMPTIOUS!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "DELICIOUS!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "IMPRESSIVE!","","",300000);
            Dialogue(Player, Hero, Prisoner, false, "THAT!","","",750000);
            Dialogue(Player, Hero, Prisoner, false, "WAS!","","",750000);
            Dialogue(Player, Hero, Prisoner, false, "AMAZING DARLING!","","",0);
            break;
            default:
            Dialogue(Player, Hero, Prisoner, false, "Great show sweetheart!","Great Show!","",0);
            break;
        }
        Dialogue(Player, Hero, Prisoner, true, "Thank you for the game Sassy one, it was very satisfying indeed","","",0);
        Dialogue(Player, Hero, Prisoner, false, "Oh! Darling!","That's enough flattery!","",0);
        Dialogue(Player, Hero, Prisoner, true, "Farewell then","","",0);
        Dialogue(Player, Hero, Prisoner, false, "Bye Bye!","","",0);
        break;
        case 2:
        Dialogue(Player, Hero, Prisoner, true, "Yeeeaahhh.... No.","I will not be putting myself into these kinds of games","Now if you excuse me...",0);
        Dialogue(Player, Hero, Prisoner, false, "Oh darling!","Why'd you have to be such a party pooper...","",0);
        break;
    }
}
    void PrisonEvent3(Entity& Player){//The Lore one Done
    
    Dialogue(Player, Hero, Prisoner, false, "Hmph,","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Sir? Is there anyone there?","","",0);
    Dialogue(Player, Hero, Prisoner, false, ". . .","It's none of your concern, \033[91mscoundrel\033[0m","",0);
    Dialogue(Player, Hero, Prisoner, true, "!!","I'm no-..","Well, anyhow",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Insist to talk with him","Just leave","",Chance);
    if (Chance == 2){
        Dialogue(Player, Hero, Prisoner, true, "I'll be taking my leave then,","farewell.","",0);
        Dialogue(Player, Hero, Prisoner, false, ". . .","","",0);
        return;
    }

    Dialogue(Player, Hero, Prisoner, true, "May I ask, how did you end up locked up?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Hmmphf. . .","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Sir? How did you end u-","","",1500000);
    DialogueFlash(Player, Hero, Prisoner, true, "\033[91m");
    Dialogue(Player, Hero, Prisoner, false, "I SAID IT IS \033[1;91mNONE\033[0m OF YOUR CONCERN, BRAT","","",0);
    Dialogue(Player, Hero, Prisoner, true, "S-sorry","","",0);

    Objection:
    DialogueChoice(Player,Hero,Prisoner,true,"Insist further","Give up and leave","Object",Chance);
    switch (Chance){
        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I-I'll be taking my leave then,","excuse me.","",0);
        Dialogue(Player, Hero, Prisoner, false, ". . .","","",0);
        return;
        break;

        case 3:
        Dialogue(Player, Hero, Prisoner, true, "I mean","","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[1;47;91mOBJECTION!\033[0m","","",0);
        Dialogue(Player, Hero, Prisoner, false, "WHA-","what","Object what?",0);
        Dialogue(Player, Hero, Prisoner, false, "This isn't a courtroom kid","It's a prison","",0);
        Dialogue(Player, Hero, Prisoner, true, "Right..","Sorry I got excited...","",0);
        Dialogue(Player, Hero, Prisoner, false, ". . .","sure","",0);
        goto Objection;
        break;
    }

    Dialogue(Player, Hero, Prisoner, true, "Excuse me, but I refuse to leave until you answer me","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Tsk...","And why would you want to know such nonsense?","",0);
    Dialogue(Player, Hero, Prisoner, false, "Is it pity?","Respect?","Annoyance?",0);
    Dialogue(Player, Hero, Prisoner, false, "Or is it just pure, naive curiosity?","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Curiosity, Sir","","",0);
    Dialogue(Player, Hero, Prisoner, false, ". . .","Fine","What's your name?",0);
    Dialogue(Player, Hero, Prisoner, true, Player.Name + ", sir","What about yours?","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Name's \033[93mSogro\033[0m","Anyhow, it was the twin \033[93mKings\033[0m, ","They locked me here after my plea for a small amount of the \033[95mViolet Tonic\033[0m",0);
    Dialogue(Player, Hero, Sogro_prison, false, "They were ofended, flabbergasted by such a request","But I begged and kept begging, so much...","Thus, they left me here to rot",0);
    Dialogue(Player, Hero, Sogro_prison, false, "This was \033[91m5 decades\033[0m ago,","Soon after the first ever tournament took place","",0);
    
    bool WitchReveal = false;
    bool ChampionReveal = false;
    bool PrisonerReveal = false;
    violetQuestion:
    DialogueChoice(Player,Hero, Sogro_prison,true,"Why did you need some of the \033[95mViolet Tonic\033[0m?","What's a \033[95mViolet Tonic\033[0m again?","Ask about the first tournament",Chance);
    switch (Chance){
        case 2:
        WitchReveal = true;
        Dialogue(Player, Hero, Sogro_prison, false, "The \033[95mViolet Tonic\033[0m?","It's a special mixture that takes a \033[93mDecade\033[0m to brew,","It has always been the prize for the Winner ever since the very first tournament",0);
        Dialogue(Player, Hero, Sogro_prison, false, "And is also the reason as to why every tournament is held only once per \033[93mDecade\033[0m.","Nobody knows what it's made of or where it comes from,","But the effects it has on people...",0);
        Dialogue(Player, Hero, Sogro_prison, false, "If you drink one, you become instantly invigorated with power and your","aging slows down dramtically. Thus why every fighter in this damned country wants it...","What they don't realize at first glance, is that...",0);
        Dialogue(Player, Hero, Sogro_prison, false, "The more you drink it, the more \033[95mTwisted\033[0m and \033[91mUnhuman\033[0m you become.","You end up \033[91mUnrecognisable\033[0m.","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "Anyhow, aren't you competing for it anyway?","","",0);
        Dialogue(Player, Hero, Sogro_prison, true, "Yes and no.","","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "What do you mean?","","",0);
        Dialogue(Player, Hero, Sogro_prison, true, "Yes, I am competing and fighting","But I'm not here to \033[93mWin\033[0m the Tonic","I'm here to go up the colosseum and slay the twin \033[93mKings\033[0m, and \033[93mthen steal\033[0m the Tonic",0);
        Dialogue(Player, Hero, Sogro_prison, false, "You are insane","How do you plan on doing that?","",0);
        Dialogue(Player, Hero, Sogro_prison, true, "I'm having the aid of a powerful \033[95mWitch\033[0m","She told me she needed that tonic (like you), and would offer me aid if I were to get it","She also told me I wouldn't be able to defeat the \033[95mChampion\033[0m,",0);
        Dialogue(Player, Hero, Sogro_prison, true, "So that's why I'm targeting the \033[93mKings\033[0m,","That, and \033[91mPersonal business\033[0m.","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "A \033[95mWitch\033[0m...","...","!",0);
        Dialogue(Player, Hero, Sogro_prison, true, "?","\033[90m(He looked surprised after I mentioned the Witch...)\033[0m","",0);
        goto violetQuestion;
        break;

        case 3:
        ChampionReveal = true;
        Dialogue(Player, Hero, Sogro_prison, false, "The first tournament happened \033[91m5 decades\033[0m ago, so this makes it the 6th tournament, no?","","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "The prize has always been the \033[95mViolet Tonic\033[0m,","And so have been the hosts","",0);
        Dialogue(Player, Hero, Sogro_prison, true, "Same hosts? The twin \033[93mKings\033[0m?","How is that possible?","They still look young",0);
        Dialogue(Player, Hero, Sogro_prison, false, "My guess is that they sip a miniscule fraction of the \033[95mViolet Tonic\033[0m every now and then,","Just enough to keep their youth without any \033[91mside effects\033[0m.","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "And the rest of the tonic itself is what the winners get","Or rather, what the winner gets","It has always been the same \033[95mChampion\033[0m ever since the first tournament",0);
        Dialogue(Player, Hero, Sogro_prison, true, "The \033[95mChampion\033[0m...","Do you perhaps know who it was?","",0);
        Dialogue(Player, Hero, Sogro_prison, false, ". . .","","",0);
        Dialogue(Player, Hero, Sogro_prison, false, "She was my \033[95mDaughter\033[0m,","\033[92mNora\033[0m...","",0);
        goto violetQuestion;
        break;
    }

    if (ChampionReveal == true){
    Dialogue(Player, Hero, Sogro_prison, false, "I wanted it to create a \033[93mcure\033[0m for my \033[95mDaughter\033[0m, the \033[95mChampion\033[0m","Whom has become... clearly \033[95mCorrupted\033[0m by the Tonic's power","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "As a Father, I hold a lot of sorrow and worry for her...","I was so proud when she won the first tournament, but now... I'm terrified of her...","So I did all I could to get my \033[95mDaughter\033[0m back",0);
    Dialogue(Player, Hero, Sogro_prison, false, "But now I'm here, stuck in prison without a \033[93mcure\033[0m for her...","I suppose dying for the right cause is the most human thing we can do...","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "I see...","And, are you able to create such a medicine for her?","",0);
    }else{
    Dialogue(Player, Hero, Sogro_prison, false, "I wanted it to create a \033[93mcure\033[0m for those who drank it and became \033[91mUnhuman\033[0m.","","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "You can create such medicine?","","",0);
    }

    Dialogue(Player, Hero, Sogro_prison, false, "Personaly, not very well...","But my Wife does that kind of stuff really well","I hope she's doing fine...",0);

    if (WitchReveal == true){
    DialogueChoice(Player,Hero, Sogro_prison,true,"I'm done with the questions","Is the Witch is your wife?","",Chance);
    }else{
    DialogueChoice(Player,Hero, Sogro_prison,true,"I'm done with the questions","","",Chance);
    }
    
    if (Chance == 2){
    PrisonerReveal = true;
    Dialogue(Player, Hero, Sogro_prison, false, ". . .","You're quite the spotter " + Player.Name,"",0);
    Dialogue(Player, Hero, Sogro_prison, false, "The \033[95mWitch\033[0m you talked about... \033[95mDacha\033[0m...","With these coincidences, she might be","If so, you're in good hands",0);
    Dialogue(Player, Hero, Sogro_prison, false, "When you see her again, please give her this","","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "\033[90m(He gave you a letter, likely a love one)\033[0m","","",0);
    }else if (WitchReveal == true){
    Dialogue(Player, Hero, Sogro_prison, true, "I have nothing else to say","Thank you for your time","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Hold it,","Could you do me a favor?","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "Hm?","Sure","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "\033[90m(He hands you a letter)\033[0m","","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Could you give this to the \033[95mWitch\033[0m you spoke about?","","",0);
    }else{
    Dialogue(Player, Hero, Sogro_prison, true, "I have nothing else to say","Thank you for your time","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Wait,","Can you do me a favor?","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "Hm?","Sure","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Have you perhaps seen a \033[95mWitch\033[0m somewhere in the Colosseum?","","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "Perhaps","Why?","",0);
    Dialogue(Player, Hero, Sogro_prison, true, "\033[90m(The prisoner hands you a letter)\033[0m","","",0);
    Dialogue(Player, Hero, Sogro_prison, false, "If you run into her, please give her this","","",0);
    }

    Dialogue(Player, Hero, Sogro_prison, true, "Rest assured I will deliver this.","Thank you for speaking with me, Sogro.","Farewell",0);
    Dialogue(Player, Hero, Sogro_prison, false, "Thank you, trully.","Farewell.","",0);

    DialogueNoFace(Player, Hero, Witch, true, "\033[90m(You went back upstairs, and looked for the Witch)\033[0m","","",0);
    Dialogue(Player, Hero, Witch, true, "Witch?","","",0);
    Dialogue(Player, Hero, Witch, false, "Ah,","What is it Warrior?","",0);
    Dialogue(Player, Hero, Witch, true, "\033[90m(You hand her the letter)\033[0m","","",0);

    if(PrisonerReveal == true){
    Dialogue(Player, Hero, Witch, true, "I believe a special someone wanted you to have this","","",0);
    Dialogue(Player, Hero, Witch_down, false, "Oh... Sogro... oh my...","Did you meet him?","",0);
    Dialogue(Player, Hero, Witch_down, true, "Just talked for a while","He's a nice guy","\033[90m(When he wants to...)\033[0m",0);
    Dialogue(Player, Hero, Witch, false, "Thank you Warrior,","I'm thankful for this","It brings me joy knowing that he's alive and still on my side",0);
    }else{
    Dialogue(Player, Hero, Witch, true, "Some Prisoner wanted you to have that","","",0);
    Dialogue(Player, Hero, Witch_down, false, "Oh my...","You did good Warrior","This is Joyful",0);
    Dialogue(Player, Hero, Witch_down, true, "Really?","What does it sa-","",1500000);
    Dialogue(Player, Hero, Witch, false, "Nothing of matter to you,","but hey","",0);
    }

    Dialogue(Player, Hero, Witch, false, "You can have these for free","As a Bonus for this little trinket","",0);

    PrisonLoreCheck = true;
    Player.Stat.Kindness += 6;
    UpgradeEffectPercent(Player, Player.Misc.XPMult, 0.05, 0, "        You feel Lucky!       ", "XP Gain");
    UpgradeEffectPercent(Player, Player.Stat.CRITMULT, 0.2, 0, " Your Patience is running out ", "CritDmg");
    UpgradeEffectint(Player, Player.Stat.MAXMANA, 3, 0, " You feel calm and collected  ", " MANA");

    Dialogue(Player, Hero, Witch, true, "Thank you Witch","This will prove useful","",0);
    Dialogue(Player, Hero, Witch_down, false, "Now now, enough with the flatery and joy","The Arena is up ahead","Goodluck Warrior",0);
}
    void PrisonEvent4(Entity& Player){//Done

    Dialogue(Player, Hero, Prisoner, false, "Greetings, Fighter","","",0);
    Dialogue(Player, Hero, Prisoner, true, "What made you end up in this cell?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Me?","I used to be a craftsman, but my sources for materials were...","Well...",0);
    Dialogue(Player, Hero, Prisoner, false, "\033[91mIllegal\033[0m.","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Oh, ","","",0);
    Dialogue(Player, Hero, Prisoner, false, "That shield of yours...","Would you mind if I take a look at it?","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Hand him the shield","Deny","",Chance);
    switch(Chance){
        case 1:
        Player.Stat.Kindness += 3;
        Player.Misc.DefMana += 0.1;
        Dialogue(Player, Hero, Prisoner, false, "Let me seee...","","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(It looks like the craftsman is adding something to it)\033[0m","\033[90m(Probably with those illegal materials...)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, false, "There,","Your shield should produce more \033[94mEnergy\033[0m when you defend with it","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(When you use DEFEND, you will now recover an additional 10% of " + manashow() + "\033[90m)\033[0m","","",0);
        Dialogue(Player, Hero, Prisoner, true, "This will prove quite useful in battle","You have my gratitude Craftsman","",0);
        Dialogue(Player, Hero, Prisoner, false, "Heh heh,","Glad I could be useful","",0);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I'm afraid I would mind, sir","","",0);
        Dialogue(Player, Hero, Prisoner, false, "What a shame, perhaps I could've worked on it","Oh well","",0);
        break;

    }

    Dialogue(Player, Hero, Prisoner, false, "Farewell, Fighter","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Farewell","","",0);
}
    void PrisonEvent5(Entity& Player){//Done

    Dialogue(Player, Hero, Prisoner, false, "Hmmmmmm... Oh,","Hello there youngster","",0);
    Dialogue(Player, Hero, Prisoner, true, "What made you reside in this cell, miss?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Oh dear...","I have been very misjudged","",0);
    Dialogue(Player, Hero, Prisoner, false, "I'm an especialist on meditation, a spiritual advisor.","I have helped many locals heal emotionally in the past and","I also used to help foreigners and people from diferent nations and races, but...",0);
    Dialogue(Player, Hero, Prisoner, false, "The Twin \033[93mKings\033[0m... ","They didn't like that","They demanded I stopped helping them",0);
    Dialogue(Player, Hero, Prisoner, false, "But I didn't...","So they \033[91mlocked\033[0m me here","",0);
    Dialogue(Player, Hero, Prisoner, true, "I'm very sorry to hear that","I think you did what was right nonetheless","",0);
    Dialogue(Player, Hero, Prisoner, false, "Thank you dear...","If you're tired, you can sit down and meditate with me","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Meditate with her","Refuse","Refuse kindly",Chance);
    switch(Chance){
        case 1:
        Player.Stat.Kindness += 3;
        Player.Stat.MAXMANA += 5;
        FullHeal(Player);

        Dialogue(Player, Hero, Prisoner, true, "Sure,","I'll accept the offer","",0);
        Dialogue(Player, Hero, Prisoner, false, "Oh, how wonderful!","I'm overjoyed yougster","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(You meditated with her for a while)\033[0m","","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(...)\033[0m","","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(Your were \033[92mFULLY HEALED\033[90m!)\033[0m","\033[90m(Your \033[94mMAX Mana\033[90m has been increased by 5!)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, true, "That was nice, perhaps I needed a pause from the battles","Thank you very much miss","",0);
        Dialogue(Player, Hero, Prisoner, false, "Hehe, don't mention it","","",0);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I'm fine miss, don't worry about it","","",0);
        Dialogue(Player, Hero, Prisoner, false, "Alright then, no problem","","",0);
        break;

        case 3:
        Player.Stat.Kindness++;

        Dialogue(Player, Hero, Prisoner, true, "I'm touched by the offer,","But I shouldn't rest until the fights are over","Thank you nonetheless ",0);
        Dialogue(Player, Hero, Prisoner, false, "Hehe, don't mention it","","",0);
        break;
    }

    Dialogue(Player, Hero, Prisoner, false, "Safe travels, youngster","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Farewell, miss","","",0);
}
    void PrisonEvent6(Entity& Player){//Done

    Dialogue(Player, Hero, Prisoner, false, "Hey there Pal","","",0);
    Dialogue(Player, Hero, Prisoner, true, "What happened for you to end up in this cell?","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Oh I don't remember","I have pretty bad memory issues pal","But if I'm here, then it must've been pretty bad!",0);
    Dialogue(Player, Hero, Prisoner, false, "Or maybe another unfair judgement from the \033[93mKings\033[0m,","Ya never knowe!","",0);
    Dialogue(Player, Hero, Prisoner, false, "All I know is that I used to be a pretty good Blacksmith","Bet I still have that flame in me!","",0);
    Dialogue(Player, Hero, Prisoner, false, "You have some pretty interesting equipment pal","Especially that \033[93mShield\033[0m, looks like it channels energy around","",0);
    Dialogue(Player, Hero, Prisoner, false, "Say, If ya want to, perhaps I could Reinforce it!","Or, y'know, I can also sharpen the boring weapon","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Reinforce Shield","Sharpen Weapon","Refuse",Chance);
    switch(Chance){
        case 1:
        Player.Stat.Kindness += 3;
        Player.Misc.DefMult += 1;

        Dialogue(Player, Hero, Prisoner, false, "Aha!","I knew you would want to reinforce the shield!","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(He reinforces the Shield with passion and love, making it even more sturdy!)\033[0m","\033[90m(When you use \033[93mDefend\033[90m, the damage will be further decreased!)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, false, "Here you go Pal!","","",0);
        Dialogue(Player, Hero, Prisoner, true, "Oh wow,","This is quite an impressive work","",0);
        Dialogue(Player, Hero, Prisoner, false, "You could say that twice!","Hope you have fun with it","",0);
        Dialogue(Player, Hero, Prisoner, false, "Welp,","Nice seeing'ya pal","",0);
        break;

        case 2:
        Player.Stat.ATK += 5;

        Dialogue(Player, Hero, Prisoner, false, "The weapon?","Ehh... Sure","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(He Sharpens the weapon uninspired and bored, but enough to make it deadlier)\033[0m","\033[90m(Your \033[91mAttack\033[90m has increased by 5!)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, false, "There you go...","","",0);
        Dialogue(Player, Hero, Prisoner, true, "Much apreciated","","",0);
        break;

        case 3:
        Dialogue(Player, Hero, Prisoner, true, "I won't be needing your help, forgetful one","But it's apreciated","",0);
        Dialogue(Player, Hero, Prisoner, false, "Ahh shucks...","the shield looked fun","",0);
        break;

    }

    Dialogue(Player, Hero, Prisoner, true, "Farewell forgetful one","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Who are you again?","Oh! Your shield looks nice pal","",0);
    Dialogue(Player, Hero, Prisoner, true, "N-nothing...","Forget it","",0);
    
}
    void PrisonEvent7(Entity& Player){//Done

    Dialogue(Player, Hero, Prisoner, false, "Eh?","Who's there?","",0);
    Dialogue(Player, Hero, Prisoner, true, "No one harmful, just a fighter from upst-","","",1800000);
    DialogueFlash(Player, Hero, Prisoner, true, "\033[93m");
    Dialogue(Player, Hero, Prisoner, false, "OHHHHH!","AHAHA!","A FELLOW FIGHTER!",0);
    Dialogue(Player, Hero, Prisoner, true, "Y-yes, that's righ-","","",1000000);
    Dialogue(Player, Hero, Prisoner, false, "THIS IS QUITE THE EXCITING","","",0);
    Dialogue(Player, Hero, Prisoner, true, "I'm sure it i-","","",1000000);
    Dialogue(Player, Hero, Prisoner, false, "VERY VERY VERY VERY VERY","VERYYYY EXCITING!!","",0);
    Dialogue(Player, Hero, Prisoner, false, "TELL ME FELLA, WHAT'S YOUR AMBITION?!","","",0);
    Dialogue(Player, Hero, Prisoner, true, "To.. ","To fight the twin \033[93mKings\033[0m, sir","",0);
    Dialogue(Player, Hero, Prisoner, false, "oh",". . .","",0);
    Dialogue(Player, Hero, Prisoner, false, ". . .","","",0);
    Dialogue(Player, Hero, Prisoner, false, "I tried that too almost a decade ago",". . .","Now I'm here",0);
    Dialogue(Player, Hero, Prisoner, true, "O-oh","I see...","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Ask him for fellow fighter tips","Say you're sorry and leave","",Chance);
    switch (Chance){
        case 1:
        Player.Stat.Kindness += 3;
        Player.Stat.XP += 200;

        Dialogue(Player, Hero, Prisoner, true, "Perhaps, since you attempted such a risk aswell","Might you have any tips for a fellow fighter?","",0);
        Dialogue(Player, Hero, Prisoner, false, ". . .","Tips?","",0);
        Dialogue(Player, Hero, Prisoner, true, "Yes plea-","","",1000000);
        DialogueFlash(Player, Hero, Prisoner, true, "\033[93m");
        Dialogue(Player, Hero, Prisoner, false, "AHAHAHAHA","SURELY FELLA!","ANYTHING FOR A FELLOW FIGHTER!",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(You spent a while listening to your fella talking about his fights)\033[0m","\033[90m(He explains everything in detail and with extreme passion)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(You feel more experienced)\033[0m","\033[90m(Gained +200 \033[92mXP\033[90m!)\033[0m","",0);
        Dialogue(Player, Hero, Prisoner, false, "That was quite the parley!","I hope these stories prove useful to you fella!","",0);
        Dialogue(Player, Hero, Prisoner, true, "Indeed they will","Thank you for your time, and I wish you luck fellow fighter","",0);
        Dialogue(Player, Hero, Prisoner, false, "The feeling's mutual!","Have a good one","",0);
        Dialogue(Player, Hero, Prisoner, true, "Farewell","","",0);
        break;
        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I'm sorry for you, fighter","But I should head back to the arena","",0);
        Dialogue(Player, Hero, Prisoner, false, ". . .","Be careful fella...","",0);
        break;
    }
    
}
    void PrisonEvent8(Entity& Player){//Done
    bool unlocked = false;

    Dialogue(Player, Hero, Prisoner, false, "Hello lad","Won't help out a brother?","",0);
    Dialogue(Player, Hero, Prisoner, true, "Oh, sure","What do you need?","",0);
    Dialogue(Player, Hero, Prisoner, true, "\033[90m(He handed me a lockpick he had)\033[0m","","",0);
    Dialogue(Player, Hero, Prisoner, false, "I beg you, please help me leave this damned place...","","",0);
    Dialogue(Player, Hero, Prisoner, false, "I'll give you one of my \033[93mRelics\033[0m if you do.","So...","Will you help me?",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Attempt to unlock the cell","Deny","",Chance);
    switch(Chance){
        case 1:
        LockpickGame3(unlocked);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I'm very sorry","I'm afraid that's a favor I shouldn't do","Freeing a prisoner is'nt right",0);
        Dialogue(Player, Hero, Prisoner, false, "Ah yes yes,","It's a valid reason, don't worry lad","Farewell",0);
        Dialogue(Player, Hero, Prisoner, true, "Farewell","","",0);
        return;
        break;
    }

    if (unlocked == true){
    Dialogue(Player, Hero, Prisoner, false, "Aha!","","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Splendit!","You actually did it!","",0);
    Dialogue(Player, Hero, Prisoner_Free, true, "That's right","","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Here here!","Take one lad!","",0);
    RelicDrop(Player);
    Dialogue(Player, Hero, Prisoner_Free, true, "Glad you kept your promise","Thank you prisoner, and Farewell","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Absolutely","Farewell","",0);
    }else{
    Dialogue(Player, Hero, Prisoner, true, "Ahh...","I think it broke...","",0);
    Dialogue(Player, Hero, Prisoner, false, "Oh","Well that's unfortunate...","Thanks for tying still lad",0);
    Dialogue(Player, Hero, Prisoner, true, "Anytime","Farewell Prisoner","",0);
    Dialogue(Player, Hero, Prisoner, false, "Farewell lad","","",0);
    }
}
    void PrisonEvent9(Entity& Player){//DONE
    bool unlocked = false;

    Dialogue(Player, Hero, Prisoner, false, "Hey there, man","How're you doing?","",0);
    Dialogue(Player, Hero, Prisoner, true, "Oh, I'm doing fine","What about you?","",0);
    Dialogue(Player, Hero, Prisoner, false, "Good good...","","Hey take this",0);
    Dialogue(Player, Hero, Prisoner, true, "\033[90m(He handed me a metal string he dented masterfully, looking like a lockpick)\033[0m","","",0);
    Dialogue(Player, Hero, Prisoner, false, "FOR THE LOVE OF GOD HELP ME GET OUT OF HERE","","",0);
    Dialogue(Player, Hero, Prisoner, true, "Eh?","And why would I do that?","",0);
    Dialogue(Player, Hero, Prisoner, false, "I promise I'll give you something","So please help me","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Attempt to unlock the cell","Refuse","",Chance);
    switch(Chance){
        case 1:
        LockpickGame2(unlocked);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "I'm sorry","I don't think I should...","",0);
        Dialogue(Player, Hero, Prisoner, false, "DAMMIT, PLEASE","I'VE BEEN HERE FOR LONGER THAN YOU THINK","LONGER THAN YOU THINK!",0);
        Dialogue(Player, Hero, Prisoner, true, "\033[90m(You rushed and left the catacombs)\033[0m","","",0);
        return;
        break;
    }

    if (unlocked == true){
    Dialogue(Player, Hero, Prisoner, false, "!!!","","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "OH GOD THANK YOU","Thank you so much!","",0);
    Dialogue(Player, Hero, Prisoner_Free, true, "That's okay","You're welcome","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "I don't have much, but please take this!","","",0);
    RelicDrop(Player);
    Dialogue(Player, Hero, Prisoner_Free, true, "Oh my, this is very useful","Thank you, and take care prisoner","Farewell",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Thanks again","Goodbye","",0);
    }else{
    Dialogue(Player, Hero, Prisoner, true, "Ahh...","I think it broke...","",0);
    Dialogue(Player, Hero, Prisoner, false, "WHAAAT","HOW?","I MADE THE BEST LOCKPICK I COULD",0);
    Dialogue(Player, Hero, Prisoner, true, "I'm sorry,","I don't think I can help you","",0);
    Dialogue(Player, Hero, Prisoner, true, "\033[90m(You left in a hurry, back to the arena)\033[0m","","",0);
    }
}
    void PrisonEvent10(Entity& Player){//DONE
    bool unlocked = false;

    Dialogue(Player, Hero, Prisoner, false, "Oi there mate, do me a favor pretty please","","",0);
    Dialogue(Player, Hero, Prisoner, true, "A favor?","","",0);
    Dialogue(Player, Hero, Prisoner, true, "\033[90m(He handed me a lockpick he found on the ground)\033[0m","","",0);
    Dialogue(Player, Hero, Prisoner, false, "Help me get outta here,","I'll reward you handsomely if you do","",0);
    Dialogue(Player, Hero, Prisoner, true, "Hmmm...","","",0);

    DialogueChoice(Player,Hero,Prisoner,true,"Try to unlock the cell","Deny","",Chance);
    switch(Chance){
        case 1:
        LockpickGame1(unlocked);
        break;

        case 2:
        Dialogue(Player, Hero, Prisoner, true, "You're locked up for a reason","I'm not going to free a criminal","",0);
        Dialogue(Player, Hero, Prisoner, false, "Ahh... just like the others...","Guess it was worth the shot","",0);
        return;
        break;
    }

    if (unlocked == true){
    Dialogue(Player, Hero, Prisoner_Free, false, "Aha! Excelsior!","Thank you mate","",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Here,","your handsome reward, as promised!","",0);
    RelicDrop(Player);
    Dialogue(Player, Hero, Prisoner_Free, true, "Thank you prisoner","Be careful","Farewell",0);
    Dialogue(Player, Hero, Prisoner_Free, false, "Take care mate","","",0);
    }else{
    Dialogue(Player, Hero, Prisoner, true, "Ahh...","I think it broke...","",0);
    Dialogue(Player, Hero, Prisoner, false, "Oh such a shame... at least you tried","I'm thankful for that","Farewell mate",0);
    Dialogue(Player, Hero, Prisoner, true, "Farewell","","",0);
    }
}
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||
void CellPrisontalk(Entity&Player){
    cout << "\t" << Player.Name << " went down to the catacombs";
    sleep(2);
    Dialogue(Player, Hero, Nochar, true, ". . .","","",1750000);
    Dialogue(Player, Hero, Prisoner, true, "Hello?","","",0);

    CellRetry:
    Chance = rand() % 10 + 1;
    switch (Chance){
        case 1:
        PrisonEvent1(Player);
        break;
        case 2:
        PrisonEvent2(Player);
        break;

        case 3:
        if (PrisonLoreCheck == false && Wave <= 6){
        PrisonEvent3(Player);
        }else{
            goto CellRetry;
        }
        break;

        case 4:
        PrisonEvent4(Player);
        break;

        case 5:
        PrisonEvent5(Player);
        break;

        case 6:
        PrisonEvent6(Player);
        break;

        case 7:
        PrisonEvent7(Player);
        break;

        case 8:
        PrisonEvent8(Player);
        break;

        case 9:
        PrisonEvent9(Player);
        break;

        case 10:
        PrisonEvent10(Player);
        break;
    }

}
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||

void CellRest(Entity& Player){

    clear();
    int interval = 100000;
    FullHeal(Player);

    cout << "\n\n\t" << Player.Name << " went to sleep in its bed." << "\n\n\n";
    sleep(1);

    for (int l = 0; l < 10; l++){
        cout << " .";
        interval += 10000;
        usleep(interval);
    }
    for (int l = 0; l < 8; l++){
        cout << " z";
        interval += 20000;
        usleep(interval);
    }
    for (int l = 0; l < 5; l++){
        interval += 100000;
        usleep(interval);
        cout << " Z";
    }

    usleep(interval);
    cout << "\n\n\n";
    sleep(1);

    cout << "\t\t    \033[91mHP fully healed" << "\n\n";
    usleep(500000);
    cout << "\t\t  \033[94mMana fully restored" << "\n\n";
    usleep(500000);
    cout << "\t\t\033[92mAll Status effects cured" << "\n\n";
    usleep(1500000);

    cout << "\033[0m" << Player.Name << " woke up, ";
    sleep(1);
    cout << "and heads on to the next battle.";
    sleep(2);
    clear();
}

void CellTimeUI(int floor, int wave){
    if (floor == 0){
        if (wave > 3){
            cout << "\033[90m|----|----|----|----|----|----|----|----|----|----|----|----|----+----+----+----+----+----+----|\033[0m" << endl;
            cout << "\033[90m     |    |    |    |    |    |    |    |\033[1;37m  - -CELL- -\033[0;90m  |    |    | \033[1;37m 4 -> Stats \033[0;90m |\033[1;37m 5 -> Options  " << endl;
            cout << "\033[0;90m|----|----|----|----|----|----|----|----|----|----|----|----|----+----+----+----+----+----+----|" << endl;
            cout << "\033[90m|         |    |         |         |    |    |              |    |         |    |         |    |" << endl;
            cout << "\033[90m|     What would you like to do?        |    |                             |                   |" << endl;
            cout << "\033[90m|                                                                                              |\033[0m" << endl;
            cout << "      \033[1mNEXT \033[47m     \033[0m \033[1mFLOOR            Rest            Straight to Battle         Prison Talk      \033[0m" << endl;
            cout << "          \033[47m       \033[0m                                           __                                  " << endl;
            cout << "         \033[47m         \033[0m              ______                      ||             _|__|_               " << endl;
            cout << "         \033[47m         \033[0m             |___   |                     ||              |  | |--|-.__._     " << endl;
            cout << "      ___\033[47m         \033[0m___             /  /                  ____||____         _|__|" << Red("*") << "|" << Red("*") << " | |  |      " << endl;
            cout << "      /  :::::::::  \\            /  /__   ....         | ________ |         |  |-|--|-|__|_     " << endl;
            cout << "      \033[47m_______________\033[0m           |______|    /          |/  | /|  \\|        _|__|_|  |" << Red("*") << "|" << Red("*") << " |      " << endl;
            cout << "     /   ':::::::'   \\                     /...            |//|             '  | |--|-|__|_     " << endl;
            cout << "     \033[47m_________________\033[0m                  Z                 .:/.|.                 '  | |  |      " << endl;
            cout << "    /      '''''      \\                             _.-'-'  ' ' '-.__                 '  |      " << endl;
            cout << "    \033[47m___________________\033[0m\033[90m          [Full Heal]        [Gets you a Shop]    [Talk with Prisoners]  \033[0m" << endl;
            cout << "\033[90m|\033[0m           (0)                      (1)                   (2)                    (3)         \033[90m |" << endl;
            cout << "|    |                        |                        |         |                             |" << endl;
            cout << "|    |    |              |    |         |              |         |    |         |    |         |" << endl;
            cout << "|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
            cout << "|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|\033[0m" << "\n\n";
        }else{
            cout << "\033[90m|----|----|----|----|----|----|----|----|----|----|----|----|----+----+----+----+----+----+----|\033[0m" << endl;
            cout << "\033[90m     |    |    |    |    |    |    |    |\033[1;37m  - -CELL- -\033[0;90m  |    |    | \033[1;37m 4 -> Stats \033[0;90m |\033[1;37m 5 -> Options  " << endl;
            cout << "\033[0;90m|----|----|----|----|----|----|----|----|----|----|----|----|----+----+----+----+----+----+----|" << endl;
            cout << "|         |    |         |         |    |    |              |    |         |    |         |    |" << endl;
            cout << "|     What would you like to do?        |    |                             |                   |" << endl;
            cout << "|        \033[0m  _____  \033[90m                                                                             |\033[0m" << endl;
            cout << "   Locked |.---.|  Door  \033[1m           Rest            Straight to Battle         Prison Talk      \033[0m" << endl;
            cout << "         | |___| |                                          __                                  " << endl;
            cout << "        |       O |             ______                      ||             _|__|_               " << endl;
            cout << "        |       ' |            |___   |                     ||              |  | |--|-.__._     " << endl;
            cout << "     ___|_ _ _ _ _|___            /  /                  ____||____         _|__|" << Red("*") << "|" << Red("*") << " | |  |      " << endl;
            cout << "      /_____________\\            /  /__   ....         | ________ |         |  |-|--|-|__|_     " << endl;
            cout << "     |_______________|          |______|    /          |/  | /|  \\|        _|__|_|  |" << Red("*") << "|" << Red("*") << " |      " << endl;
            cout << "     /_______________\\                     /...            |//|             '  | |--|-|__|_     " << endl;
            cout << "    |_________________|                 Z                 .:/.|.                 '  | |  |      " << endl;
            cout << "    /_________________\\                             _.-'-'  ' ' '-.__                 '  |      " << endl;
            cout << "   |___________________| \033[90m        [Full Heal]        [Gets you a Shop]    [Talk with Prisoners]  \033[0m" << endl;
            cout << "\033[90m|      Does Nothing? \033[0m                (1)                   (2)                    (3)         \033[90m |" << endl;
            cout << "|    |                        |                        |         |                             |" << endl;
            cout << "|    |    |              |    |         |              |         |    |         |    |         |" << endl;
            cout << "|    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
            cout << "|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|\033[0m" << "\n\n";
        }
    }else{
        cout << "                        \033[47m             \033[0m" << endl;
        cout << "                       \033[47m               \033[0m" << endl;
        cout << "                      \033[47m                 \033[0m" << endl;
        cout << "                     \033[47m                   \033[0m" << endl;
        cout << "                    \033[47m                     \033[0m" << endl;
        cout << "                   \033[47m                       \033[0m" << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m   " << endl;
        cout << "                  \033[47m                         \033[0m" << endl;
        cout << " _________________\033[47m                         \033[0m________________" << endl;
        cout << "                  :::::::::::::::::::::::::" << endl;
        cout << "_________         :::::::::::::::::::::::::         _________" << endl;
        cout << "        /         :::::::::::::::::::::::::         \\" << endl;
        cout << "        \033[47m                                             \033[0m" << endl;
        cout << "        \033[47m_____________________________________________\033[0m" << endl;
        cout << "        /         :::::::::::::::::::::::::         \\" << endl;
        cout << "       /           :::::::::::::::::::::::           \\" << endl;
        cout << "_______\033[47m                                               \033[0m_______" << endl;
        cout << "       \033[47m_______________________________________________\033[0m" << endl;
        cout << "       /              :::::::::::::::::              \\" << endl;
        cout << "      /                :::::::::::::::                \\" << endl;
        cout << "      \033[47m                                                 \033[0m" << endl;
        cout << "      \033[47m_________________________________________________\033[0m" << endl;
    }
}

void CellTime(Entity& Player){

    int Action;
    bool validchoice = false;


    while(true){

        CellTimeUI(Floor, Wave);


        cout << Player.Name << ": ";
        PlayerInput(Action);

        switch (Action){
            case 0:
            if (Wave > 3){
                Floor++;
                validchoice = true;
            }else{
                goto invalid;
            }
            break;

            case 1:
            CellRest(Player);
            validchoice = true;
            break;

            case 2:
            cout << "\t" << Player.Name << " moves toward the arena's gate";
            sleep(2);
            clear();
            BattlegateAnim();
            clear();
            ShuffleTime(Player);
            validchoice = true;
            break;

            case 3:
            CellPrisontalk(Player);
            validchoice = true;
            break;

            case 4:
            StatMenu(Player);
            break;

            case 5:
            Options();
            break;

            case 1225:
            EE_Starwalker(Player);
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


//--CLASSES-------------------------------------------------------------------------------------------------------------------------------------------------------------------------||

void ClassMenuUI(){
    cout << "           {-.-'-.-'-.-'-.-'-.'-.-'-.-'-.-'-.-'-.-'-.-\033[1;37mCLASSES\033[0m-.-'-.-'-.-'-.-'-.'-.-'-.-'-.-'-.-'-.-'-.-}" << "\n\n";

    cout << " .-----------------------.    .-----------------------.    .-----------------------.    .-----------------------. " << endl;
    cout << "/  \033[93m*,*,\033[1;33mThe Gladiator\033[0;93m,*,*\033[0m  \\  /  \033[1;96m~~~~\033[94mThe Wanderer\033[96m~~~~\033[0m   \\  /  \033[1;90m^<>^\033[91mThe Berserker\033[90m^<>^\033[0m  \\  / \033[35m#-#\033[1;90mThe Black Knight\033[0;35m#-#\033[0m  \\" << endl;
    cout << "| _______________________ |  | _______________________ |  | _______________________ |  | _______________________ |" << endl;
    cout << "||  \033[1;37mHP\033[0m: 28    \033[1;37mMana\033[0m: 20   ||  ||  \033[1;37mHP\033[0m: 24    \033[1;37mMana\033[0m: 25   ||  ||  \033[1;37mHP\033[0m: 32    \033[1;37mMana\033[0m: 15   ||  ||  \033[1;37mHP\033[0m: 40    \033[1;37mMana\033[0m: 20   ||" << endl;
    cout << "||            \033[1;37mGold\033[0m: 9" << goldshow() << "   ||  ||            \033[1;37mGold\033[0m: 16" << goldshow() << "  ||  ||            \033[1;37mGold\033[0m: 9" << goldshow() << "   ||  ||            \033[1;37mGold\033[0m: 5" << goldshow() << "   ||" << endl;
    cout << "||  \033[1;37mATK\033[0m: 6               ||  ||  \033[1;37mATK\033[0m: 4               ||  ||  \033[1;37mATK\033[0m: 12              ||  ||  \033[1;37mATK\033[0m: 8               ||" << endl;
    cout << "||   \033[1;37mMA\033[0m: 6               ||  ||   \033[1;37mMA\033[0m: 12              ||  ||   \033[1;37mMA\033[0m: 4               ||  ||   \033[1;37mMA\033[0m: 8               ||" << endl;
    cout << "||   \033[1;37mAC\033[0m: 8               ||  ||   \033[1;37mAC\033[0m: 4               ||  ||   \033[1;37mAC\033[0m: 4               ||  ||   \033[1;37mAC\033[0m: 6               ||" << endl;
    cout << "||\033[1;37mCRIT\033[0m%: 5%   \033[1;37mDODGE\033[0m%: 10%||  ||\033[1;37mCRIT\033[0m%: 5%   \033[1;37mDODGE\033[0m%: 5% ||  ||\033[1;37mCRIT\033[0m%: 10%   \033[1;37mDODGE\033[0m%: 5%||  ||\033[1;37mCRIT\033[0m%: 0%   \033[1;37mDODGE\033[0m%: 0% ||" << endl;
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    cout << "||\033[1;92mItem\033[0m: Flurry Coat      ||  ||\033[1;92mItem\033[0m: Cursed Dice      ||  ||\033[1;92mItem\033[0m: Explosive Jar    ||  ||\033[1;92mItem\033[0m: Voodoo Doll      ||" << endl;
    cout << "||\033[1;94mSpell\033[0m: Duo Slash       ||  ||\033[1;94mSpell\033[0m: Magica Blast    ||  ||\033[1;94mSpell\033[0m: Tempered Cut    ||  ||\033[1;94mSpell\033[0m: Knight's Stance ||" << endl;
    cout << "||                       ||  ||                       ||  ||                       ||  ||                       ||" << endl;
    cout << "||\033[1;93mBoon\033[0m: Earn +10% XP     ||  ||\033[1;93mBoon\033[0m: Restore more Mana||  ||\033[1;93mBoon\033[0m: +50% CritDamage  ||  ||\033[1;93mBoon\033[0m: Gain +10% Gold   ||" << endl;
    cout << "||\033[1;95mCurse\033[0m: None            ||  ||\033[1;95mCurse\033[0m: Gain -10% XP    ||  ||\033[1;95mCurse\033[0m: -1 Spell Token  ||  ||\033[1;95mCurse\033[0m: No Defend Mana  ||" << endl;
    cout << "\\'-----------------------'/  \\'-----------------------'/  \\'-----------------------'/  \\'-----------------------'/" << endl;
    cout << " '-----------------------'    '-----------------------'    '-----------------------'    '-----------------------' " << endl;
    cout << "            (1)                          (2)                          (3)                          (4)            " << "\n\n";
}

void ClassClassification(Entity& Player,Classes classchoice,int maxhp,int maxmana,float atk,float ma,float ac,float crit,float dodge,int gold,int tokens,Item classitem,Spell classspell,float critmult,float xpmult,float manamult,float goldmult, float defmult, float defmana){
    Player.Misc.Class = classchoice;
    
    Player.Stat.MAXHP = maxhp; Player.Stat.HP = maxhp;
    Player.Stat.MAXMANA = maxmana; Player.Stat.MANA = maxmana;
    Player.Stat.ATK = atk;
    Player.Stat.MA = ma;
    Player.Stat.AC = ac;
    Player.Stat.CRIT = crit;
    Player.Stat.DODGE = dodge;
    Player.Stat.Gold = gold;
    Player.Misc.Spellslots = tokens;
    Player.ItemBag.Item1 = classitem;
    Player.SpellBag.SigSpell = classspell;
    Player.Stat.CRITMULT += critmult;
    Player.Misc.XPMult += xpmult;
    Player.Misc.ManaMult += manamult;
    Player.Misc.GoldMult += goldmult;
    Player.Misc.DefMult += defmult;
    Player.Misc.DefMana += defmana;
}

void ClassChoice(Entity& Player){

    int Action;

    clear();
    ClassMenuUIAnim();
    Start:
    clear();
    ClassMenuUI();

    cout << "You: ";
    Action = PlayerInput(Action);

    switch (Action) {
        case 1:
        ClassClassification(Player,Gladiator, 28, 20, 6, 6, 8, 5, 10, 9, 2, ItmFlurryCoating, SplDuoSlash, 0, 0.1, 0, 0, 0, 0);
        break;

        case 2:
        ClassClassification(Player,Wanderer, 24, 25, 4, 12, 4, 5, 5, 16, 2, ItmCursedDice, SplMagicaBlast, 0, -0.1, 0.1, 0, 0, 0);
        break;

        case 3:
        ClassClassification(Player,Berserker, 32, 15, 12, 4, 4, 10, 5, 9, 1, ItmExplosiveJar, SplTemperedCut, 0.5, 0, 0, 0, 0, 0);
        break;

        case 4:
        ClassClassification(Player,BlackKnight, 40, 20, 8, 8, 6, 0, 0, 5, 2, ItmVoodooDoll, SplKnightStance, 0, 0, 0, 0.1, 0, -0.15);
        break;

        case 999:
        ClassClassification(Player,God, 50, 30, 15, 15, 10, 20, 20, 99, 2, ItmArmageddon, SplOmnislash, 1, 1, 1, 1, 1, 1);
        break;

        default:
        cout << "Invalid choice";
        sleep(1);
        goto Start;
        break;
    }
    clear();
}


