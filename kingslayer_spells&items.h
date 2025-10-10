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
#include "kingslayer_stats&dialogue.h"

using namespace std;

int TotalItems = 26;
int TotalSpells = 21;
int TotalRelics = 15;
int TotalUpgrades = 10;

//- General Functions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void StatOverflowCheck(Entity& User){
    if (User.Stat.HP > User.Stat.MAXHP){
        User.Stat.HP = User.Stat.MAXHP;
    }

    if (User.Stat.MANA > User.Stat.MAXMANA){
        User.Stat.MANA = User.Stat.MAXMANA;
    }

    if (User.Stat.CRIT > 100){
        User.Stat.CRIT = 100;
        User.Stat.CRITMULT += 0.02;
    }

    if (User.Stat.DODGE > 75){
        User.Stat.DODGE = 75;
        User.Stat.AC += 3;
    }

    if (User.Stat.Gold < 0){
        User.Stat.Gold = 0;
    }
}

void CriticalHitUI(){
    if (PlayerTurn == true){
        cout << "\t  \033[93m ~~~~~~~~~~~~~~ \033[0m" << endl;
	    cout << "\t    CRITICAL HIT " << endl;
        cout << "\t  \033[93m ~~~~~~~~~~~~~~ \033[0m" << "\n\n";
    }else{
        cout << "\t  \033[91m !------------! \033[0m" << endl;
	    cout << "\t    CRITICAL HIT " << endl;
        cout << "\t  \033[91m !------------! \033[0m" << "\n\n";
    }
}

void InstaKill(Entity& Target){

    ScreenFlash(6);

    sleep(1);

    if (Target.Misc.Type == CHAMPION){
        cout << "\n\tIt somewhat Damages " << Target.Name << "" << "\n\n";
	    Damage = (Target.Stat.MAXHP * 0.3) + 1;
    } else if (Target.Misc.Type == BOSS || Target.Misc.Type == PLAYER1 || Target.Misc.Type == PLAYER2){

        cout << "\n\tIt Heavily Damages " << Target.Name << "!!" << "\n\n";
	    Damage = (Target.Stat.MAXHP * 0.75);

        if (Target.Stat.HP <= Damage){
            Damage = Target.Stat.HP - 1;
        }

    }else{
        cout << "\n\t\033[1;37mIT INSTAKILLS " << Target.Name << "!!!\033[0m" << "\n\n";
	    Damage = Target.Stat.MAXHP;
    }
}
void FullHeal(Entity& User){
    User.Stat.HP = User.Stat.MAXHP;
    User.Stat.MANA = User.Stat.MAXMANA;

    User.Status.Burn = 0;
    User.Status.Poison = 0;
    User.Status.Freeze = 0;
    User.Status.Shock = 0;
}

string NamelenghtBar(Entity& User, string character){
    string bar = "";
    for (int l = 0; l < User.Misc.NameLenght; l++){
        bar += character;
    }
    return bar;
}

string ArrowAnim(int Lenght){
    for (int l = 0; l < Lenght; l++){
        cout << "-";
        usleep(10000);
    }
    return ">";
}

//- Base Battle Actions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void Defend(Entity& User){

    if (PlayerTurn == true){
        sleep (1);
        cout << "\tRecovered " << User.Misc.DefMana * 100 << "% of Mana" << "\n\n";
    }

	User.Stat.DEF *= User.Misc.DefMult;
    User.Stat.MANA += (User.Stat.MAXMANA*User.Misc.DefMana);

    StatOverflowCheck(User);

    usleep(500000);
}

void BasicAttack(Entity& User, Entity& Target){

    usleep(700000);
    Damage = User.Stat.ATK - Target.Stat.DEF;

    if (User.Status.Burn > 0) {//Burn cut damage
        Damage = Damage / 2;
        cout << "[Damage decreased due to Burn]" << "\n\n";
        usleep(500000);
    }

    if (Damage <= 0) {
        Damage = 1;
    }
                
    Chance = rand() % 100 + 1;

    if (User.Stat.CRIT >= Chance) {//Critical hit

        Damage = Damage * User.Stat.CRITMULT; 

        CriticalHitUI();
        sleep (1);
    }
                    
    Chance = rand() % 100 + 1;

    if (Target.Stat.DODGE >= Chance) {//Dodge
        
        Damage = 0;
        if (PlayerTurn == true){ 
            cout << "\tYou missed\n\n";
        }else {
            cout << "\tYou dodged its attack!\n\n";
        } 

        usleep(500000);

    }else if (PlayerTurn == true){
        cout << "\tYou dealt " << Damage << " damage!\n\n";
    }else {
        cout << "\tIt deals " << Damage << " damage\n\n";
    }

        usleep(500000);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------||||

//- Item Classifications - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

                    //Name + Desc char limit is 50 chars coz of shop
Item ItmHealingPotion(HealPotion,   "\033[92mHealing\033[0m Potion", "(Heals 70 HP)", 6, 9);                    //1
Item ItmManaFlask(MpFlask,          "\033[94mMana\033[0m Flask", "(Restores 40 Mana)", 5, 9);
Item ItmStatusPotion(StusPotion,    "\033[96mStatus\033[0m Potion", "(Heals all Status Effects)", 3, 9);
Item ItmMixedFlask(VFlask,         "\033[95mMixed\033[0m Flask", "(Restores 60% HP & Mana)", 7, 9);
Item ItmUltimateFlask(UltFlask,     "\033[1;92mUlt\033[96mim\033[94mate\033[0m Flask", "(Fully Heals HP, Mana & Status)", 15, 21);    //5
Item ItmBloodCoating(BloodCoat,     "\033[31mBlood\033[0m Coating", "(Guaranteed CRIT)", 5, 9);
Item ItmVitalityCoating(VitalCoat,  "\033[92mStamina\033[0m Coating", "(Attack that heals HP & Mana)", 5, 9);
Item ItmFlurryCoating(FlurryCoat,   "\033[93mFlurry\033[0m Coating", "(Flurry of 3-5 Attacks)", 10, 9);
Item ItmStancedCoating(StanceCoat,  "\033[90mStanced\033[0m Coating", "(Attack and Defend)", 3, 9);
Item ItmDeadlyCoating(DeadlyCoat,   "\033[95mDeadly\033[0m Coating", "(Attack w/ Status [Brn/Psn/Frz])", 10, 9);   //10
Item ItmBurningCinders(BurnCinder,  "\033[91mBurning \033[90mCinders\033[0m", "(Burns target for 3 turns)", 3, 14);
Item ItmFlintnSteel(FlintnSteel,    "\033[90mFlint\033[0m & \033[91mSteel\033[0m", "(Burns target for 6 turns)", 7, 18);
Item ItmPoisonDart(PsnDart,         "\033[92mPoison Dart\033[0m", "(Poisons target for 3 turns)", 3, 9);
Item ItmPoisonDagger(PsnDagger,     "\033[92mPoison Dagger\033[0m", "(Poisons target for 6 turns)", 7, 9);
Item ItmIceFlask(IceFlsk,           "\033[96mIce\033[0m Flask", "(Freezes target for 2 Turns)", 4, 9);                    //15
Item ItmChillingOrb(ChillOrb,       "\033[96mChilling\033[0m Orb", "(Freezes target for 4 turns)", 8, 9);
Item ItmDeadlyJar(DeadJar,          "\033[95mDeadly\033[0m Jar", "(Dooms target w/ all Status)", 12, 9);
Item ItmLightninginaJar(LightinJar, "\033[93mLightning in a Jar\033[0m", "(Shocks target for 99 turns)", 10, 9);
Item ItmExplosiveJar(ExplosJar,     "\033[91mExplosive\033[0m Jar", "(Deals 25 Damage)", 4, 9);
Item ItmNiceJar(NiceeeJar,          "\033[95mNice\033[0m Jar", "(Deals 69 Damage)", 69, 9);                        //20
Item ItmCursedDice(CurseDice,       "\033[95mCursed\033[0m Dice", "(Random Effect [1-20])", 5, 9);
Item ItmWeirdDice(WeirDice,         "\033[90mWeird\033[0m Dice", "(1 in 6 chance to INSTAKILL)", 6, 9);
Item ItmCoinPouch(CoinBag,          "\033[93mCoin Pouch\033[0m", "(May have good wealth, or nothing)", 5, 9);
Item ItmVoodooDoll(VoodooDo,        "\033[33mVoodoo Doll\033[0m", "(Damages 1.5 x MAXHP [Sacrifices 10% HP])", 12, 9);
Item ItmPreciseNeedle(PrecNeedle,   "Precise Needle", "(Super low chance to INSTAKILL)", 1, 0);      //25
Item ItmArmageddon(Armagedon,       "Armageddon", "", 100, 0);

//- Item Effects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void ItmEffHealingPotion(Entity& User){// 1
    cout << endl << User.Name << " used a Healing Potion" << "\n\n";
    sleep (1);
    cout << "\n\t" << User.Name << " healed 70 HP" << "\n\n";
    User.Stat.HP += 70;
    StatOverflowCheck(User);
    sleep (2);
    clear();
}
void ItmEffManaFlask(Entity& User){// 2
    cout << endl << User.Name << " used a Mana Flask" << "\n\n";
    sleep (1);
    cout << "\n\t" << User.Name << " restored 40 Mana" << "\n\n";
    User.Stat.MANA += 40;
    StatOverflowCheck(User);
    sleep (2);
    clear();
}
void ItmEffStatusPotion(Entity& User){// 3
    cout << endl << User.Name << " used a Status Potion" << "\n\n";
    sleep (1);
    cout << "\n\t" << User.Name << "'s Status fully recovered" << "\n\n";
    User.Status.Burn = 0, User.Status.Poison = 0, User.Status.Freeze = 0, User.Status.Shock = 0;
    sleep (2);
    clear();
}
void ItmEffMixedFlask(Entity& User){// 4
    cout << endl << User.Name << " used a Mixed Flask" << "\n\n";
    sleep (1);
    cout << "\n\t" << User.Name << "'s Mana and HP restored" << "\n\n";
    User.Stat.HP += ((User.Stat.MAXHP/10)*6);
    User.Stat.MANA += ((User.Stat.MAXMANA/10)*6);
    StatOverflowCheck(User);
    sleep (2);
    clear();
}
void ItmEffUltimateFlask(Entity& User){// 5
    cout << endl << User.Name << " opens the Ultimate Flask, ";
    sleep(2);
    cout << "then drinks it." << "\n\n";
    sleep (2);
    cout << "\n\t" << User.Name << "'s HP, Mana and Status fully recovered" << "\n\n";
    FullHeal(User);
    sleep (3);
    clear();
}
void ItmEffBloodCoating(Entity& User, Entity& Target){// 6
    cout << User.Name << " used a Blood Coating" << "\n\n";
    
    sleep(1);

	Damage = User.Stat.ATK - Target.Stat.DEF;

	if (User.Status.Burn > 0) {//Burn cut damage
        Damage = Damage / 2;
    }

	if (Damage <= 0) {
        Damage = 1;
    }
		
	Damage *= User.Stat.CRITMULT;
    CriticalHitUI();
    sleep (1);
	cout << "\t" << User.Name << " dealt " << Damage << " damage\n\n"; 
    sleep(2);
    clear();
}
void ItmEffVitalityCoating(Entity& User, Entity& Target){// 7
    cout << User.Name << " used a Stamina Coating" << "\n\n";

    BasicAttack(User, Target);

	cout << "And healed " << Damage << " HP + " << Damage / 2 << " Mana" << "\n\n";
    sleep(1);

	User.Stat.HP += Damage;
	User.Stat.MANA += (Damage / 2);

    StatOverflowCheck(User);

    sleep(2);
    clear();
}
void ItmEffFlurryCoating(Entity& User, Entity& Target){// 8
    cout << User.Name << " used a Flurry Coating" << "\n\n";

    sleep(1);
    
    Damage = 0;
    int TotalDamage = 0;
						
	for (int t = rand() % 3 + 3; t > 0; t--){
	Target.Stat.HP -= Damage;
	BasicAttack(User, Target);
    TotalDamage += Damage;
	}

    sleep(1);

    cout << "\t+-----------------+" << endl;
    cout << "\t Total: " << TotalDamage << " Damage" << endl;;
    cout << "\t+-----------------+" << "\n\n";

	sleep(2);

    clear();
}
void ItmEffStancedCoating(Entity& User, Entity& Target){// 9
    cout << User.Name << " used a Stanced Coating" << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << " attacks" << "\n\n";
    BasicAttack(User, Target);

    sleep(1);

    cout << "\t" << User.Name << " defends" << "\n\n";
    Defend(User);

    sleep(1);
    clear();
}
void ItmEffDeadlyCoating(Entity& User, Entity& Target){// 10
    cout << User.Name << " used the Deadly Coating" << "\n\n";
    sleep(1);

    BasicAttack(User, Target);

    Target.Status.Burn += 2;
    Target.Status.Poison += 2;
    Target.Status.Freeze += 1;

    sleep(1);
    cout << Target.Name << " is ";
    sleep(1);
    cout << "Burning, ";
    sleep(1);
    cout << "Poisoned, ";
    sleep(1);
    cout << "and Frozen" << "\n\n";
    sleep(2);

}
void ItmEffBurningCinders(Entity& User, Entity& Target){// 11
    cout << User.Name << " used Burning Cinders" << "\n\n";
    sleep(1);
    Target.Status.Burn += 3;
	cout << User.Name << " tosses the cinders at " << Target.Name << "\n\n";
    sleep(1);
    cout << Target.Name << " is Burning" << "\n\n";
    sleep(2);
    
}
void ItmEffFlintandSteel(Entity& User, Entity& Target){// 12
    cout << User.Name << " picks out a Flint and Steel" << "\n\n";
    sleep(1);
    Target.Status.Burn += 6;
	cout << User.Name << " shouts";
    sleep(1);
    cout << " 'FLINT N' STEEL!'";
    sleep(1);
    cout << " and sets " << Target.Name << " on fire" "\n\n";
    sleep(2);
    cout << Target.Name << " is Scorching in flames" << "\n\n";
    sleep(2);
    
}
void ItmEffPoisonDart(Entity& User, Entity& Target){// 13
    cout << User.Name << " used Poison Dart" << "\n\n";
    sleep(1);
    Target.Status.Poison += 3;
	cout << User.Name << " flings the dart at " << Target.Name << "\n\n";
    sleep(1);
    cout << Target.Name << " is Poisoned" << "\n\n";
    sleep(2);
    
}
void ItmEffPoisonDagger(Entity& User, Entity& Target){// 14
    cout << User.Name << " picks out a Poison Dagger" << "\n\n";
    sleep(2);
    Target.Status.Poison += 6;
	cout << User.Name << " runs towards the " << Target.Name << ", ";
    sleep(1);
    cout << "and STABS it in the chest" << "\n\n";
    sleep(2);
    cout << Target.Name << " is Contaminated in Poison" << "\n\n";
    sleep(2);
}
void ItmEffIceFlask(Entity& User, Entity& Target){// 15
    cout << User.Name << " used Ice Flask" << "\n\n";
    sleep(1);
    Target.Status.Freeze += 2;
	cout << User.Name << " throws the flask at " << Target.Name << "\n\n";
    sleep(1);
    cout << Target.Name << " is Frozen" << "\n\n";
    sleep(2);
}
void ItmEffChillingOrb(Entity& User, Entity& Target){// 16
    cout << User.Name << " picks out a Chilling Orb" << "\n\n";
    sleep(1);
    Target.Status.Freeze += 4;
	cout << User.Name << " throws the orb at " << Target.Name << "\n\n";
    sleep(2);
    cout << "And it waves around it, ";
    sleep(1);
    cout << "making the Temperature drop DRASTICALLY" << "\n\n";
    sleep(3);
    cout << Target.Name << " is Frostbitten" << "\n\n";
    sleep(2);
}
void ItmEffDeadlyJar(Entity& User, Entity& Target){// 17
    cout << User.Name << " used the Deadly Jar" << "\n\n";
    sleep(1);

    cout << User.Name << " tosses the Jar violently at the " << Target.Name << "\n\n";
    sleep(2);

    Target.Status.Burn += 3;
    Target.Status.Poison += 3;
    Target.Status.Freeze += 2;
    Target.Status.Shock += 3;

    cout << Target.Name << " is Overwhelmed with side effects, ";
    sleep(1);
    cout << "it is" << "\n\n";
    usleep(500000);
    cout << "\tBurning [+3]" << endl;
    usleep(500000);
    cout << "\tPoisoned [+3]" << endl;
    usleep(500000);
    cout << "\tFrozen [+2]" << endl;
    usleep(500000);
    cout << "\tAnd Shocked [+3]" << "\n\n";
    sleep(2);

}
void ItmEffLightninginaJar(Entity& User, Entity& Target){// 18
    cout << User.Name << " pops the lid of a Jar with Lightning" << "\n\n";
    sleep(1);
    Target.Status.Shock = 99 + 1;
	cout << "The Lighting inside it escapes uncontrolably" << "\n\n";
    sleep(1);

    for (int l = 0; l < 21; l++){
        cout << "\\";
        usleep(25000);
        cout << "/";
        usleep(25000);
    }
    cout << "\\>>" << "\n\n";
    usleep(50000);

    cout << "And it hits " << Target.Name << "\n\n";
    sleep(2);
    cout << Target.Name << " is Electrified" << "\n\n";
    sleep(2);
}
void ItmEffExplosiveJar(Entity& User, Entity& Target){// 19
    cout << User.Name << " used Explosive Jar" << "\n\n";
    sleep(1);
    Damage = 25;
	cout << User.Name << " throws the jar at " << Target.Name << "\n\n";
    sleep(1);
    cout << "\tIt deals 25 Damage" << "\n\n";
    sleep(2);
    clear();
}
void ItmEffNiceJar(Entity& User, Entity& Target){// 20
    cout << User.Name << " used the Nice Jar" << "\n\n";
    sleep(1);
    Damage = 69;
	cout << User.Name << " opens the jar, ";
    sleep(1);
    cout << "and seduces " << Target.Name << "\n\n";
    sleep(2);
    cout << "BUT THEN! ";
    sleep(1);
    cout << User.Name << " MOCKS and BETRAYS " << Target.Name << ", ";
    sleep(2);
    cout << "leaving it emotionally DEVASTADED." << "\n\n";
    sleep(3);
    cout << "\tIt deals 69(Nice) Damage" << "\n\n";
    sleep(3);

    clear();
}
void ItmEffCursedDice(Entity& User, Entity& Target, bool& ExtraItem){// 21
    cout << User.Name << " rolls a Cursed Dice" << "\n\n";
    sleep(1);

    D20Roll();
    sleep(1);

	cout << "\n\n" << "\t It rolled " << Chance << "\n\n";
    sleep(1);

	switch (Chance) {
		case 1:
	    	cout << Target.Name << " is fully healed" << "\n\n";
			Target.Stat.HP = Target.Stat.MAXHP;
            Target.Stat.MANA = Target.Stat.MAXMANA;
            Target.Status.Burn = 0, Target.Status.Poison = 0, Target.Status.Freeze = 0, Target.Status.Shock = 0;
            break;

		case 2:
		    cout << User.Name << " lost 5g..." << "\n\n";
			User.Stat.Gold -= 5;
            break;

		case 3:
			cout << User.Name << " is Frozen, Burned, and Poisoned for 1 turn..." << "\n\n";
			User.Status.Burn += 1;
            User.Status.Poison += 1;
            User.Status.Freeze += 1;
			break;

		case 4:
			cout << User.Name << " lost 1g..." << "\n\n";
			User.Stat.Gold -= 1;
            break;

		case 5:
			cout << "nothing happens" << "\n\n";
            break;

		case 6:
	    	cout << User.Name << " Defends" << "\n\n";
            usleep(500000);
			Defend(User);
            break;

		case 7:
			cout << User.Name << " gained 6g!" << "\n\n";
			User.Stat.Gold += 6;
			break;

		case 8:
			cout << User.Name << " Attacks" << "\n\n";
            usleep(500000);
			BasicAttack(User, Target);
			break;

		case 9:
			cout << User.Name << " got a random Item!" << "\n\n";
			ExtraItem = true;
			break;

		case 10:
			cout << Target.Name << " got all Status Effects for 1 turn!" << "\n\n";
			Target.Status.Burn += 1;
            Target.Status.Poison += 1;
            Target.Status.Freeze += 1;
            Target.Status.Shock += 1;
			break;

		case 11:
            cout << User.Name << " gained 10g!" << "\n\n";
            User.Stat.Gold += 10;
			break;

		case 12:
            cout << User.Name << " attacks twice!" << "\n\n";
            usleep(500000);
            Damage = 0;
            for (int l = 0; l < 2; l++){
                Target.Stat.HP -= Damage;
                BasicAttack(User, Target);
            }
			break;

		case 13:
            cout << User.Name << " got a random Item and attacks!" << "\n\n";
            usleep(500000);
            BasicAttack(User, Target);
            ExtraItem = true;
			break;

		case 14:
            cout << Target.Name << " got all Status Effects for 2 turns!" << "\n\n";
            Target.Status.Burn += 2;
            Target.Status.Poison += 2;
            Target.Status.Freeze += 2;
            Target.Status.Shock += 2;
			break;

		case 15:
            cout << "All " << Target.Name << "'s stats decreased by 1!!" << "\n\n";
            Target.Stat.MAXHP -= 1, Target.Stat.HP -= 1;
            Target.Stat.ATK -= 1;
            Target.Stat.MA -= 1;
            Target.Stat.AC -= 1;
            Target.Stat.CRIT -= 1;
            Target.Stat.DODGE -= 1;
			break;

		case 16:
            cout << User.Name << " is Fully Healed!" << "\n\n";
            User.Stat.HP = User.Stat.MAXHP;
            User.Stat.MANA = User.Stat.MAXMANA;
            User.Status.Burn = 0, User.Status.Poison = 0, User.Status.Freeze = 0, User.Status.Shock = 0;
			break;

		case 17:
            cout << Target.Name << " got all Status Effects for 3 turns!" << "\n\n";
            Target.Status.Burn += 3;
            Target.Status.Poison += 3;
            Target.Status.Freeze += 3;
            Target.Status.Shock += 3;
			break;

		case 18:
            cout << User.Name << " gained 20g!!" << "\n\n";
            User.Stat.Gold += 20;
			break;

		case 19:
			cout << "All stats increased by 1!!" << "\n\n";
			User.Stat.MAXHP += 1, User.Stat.HP += 1;
            User.Stat.MAXMANA += 1, User.Stat.MANA += 1;
            User.Stat.ATK += 1;
            User.Stat.MA += 1;
            User.Stat.AC += 1;
            User.Stat.CRIT += 1, User.Stat.CRITMULT += 0.1;
            User.Stat.DODGE += 1;
            User.Stat.Gold += 1;
			break;

		case 20:
            InstaKill(Target);
			break;
    }

    StatOverflowCheck(User);
    sleep(2);

}
void ItmEffWeirdDice(Entity& User, Entity& Target){// 22
    cout << User.Name << " rolls a Weird Dice" << "\n\n";
    sleep(1);

    D6Roll();
    sleep(1);

    cout << "\n\n" << "\t It rolled " << Chance << "\n\n";
    sleep(1);

    if (Chance == 6){
        InstaKill(Target);
    }else{
        cout << "\tNothing Happened" << "\n\n";
    }

    sleep(2);
}
void ItmEffCoinPouch(Entity& User, Entity& Target, bool& ExtraItem){// 23

    int GainGold = 0;

    cout << User.Name << " opens the Coin Pouch" << "\n\n";
    sleep(1);

    cout << "Inside the bag... " << "\n\n";
    sleep(1);

    cout << User.Name << " finds";
    sleep(2);

    GainGold = rand() % 6 + 10; // 10 - 15g

    Chance = rand() % 20 + 1;
    if (Chance == 1){ // 50g
        GainGold = 50;
    }

    Chance = rand() % 5 + 1;
    if (Chance == 1){ // 22 - 27g
        GainGold = rand() % 6 + 22;
    }

    Chance = rand() % 5 + 1;
    if (Chance == 1){ // 17 - 21g
        GainGold = rand() % 5 + 17;
    }

    Chance = rand() % 5 + 1;
    if (Chance == 1){
        ExtraItem = true;
    }

    Chance = rand() % 10 + 1;
    if (Chance == 1){
        GainGold = 0;
    }

    if (GainGold == 50){
        cout << " an OVERWHELMING amount of Gold!!!" << "\n\n";
    }else if(GainGold >= 22){
        cout << " a Giant amount of Gold!" << "\n\n";
    }else if(GainGold >= 16){
        cout << " a Big amount of Gold!" << "\n\n";
    }else if(GainGold > 1){
        cout << " a decent amount of Gold!" << "\n\n";
    }else {
        cout << " absolutely no Gold..." << "\n\n";
    }
    sleep(2);

    cout << User.Name << " got " << GainGold << "g ";
    sleep(1);

    if (ExtraItem == true){
        cout << "and an Item!";
        sleep(1);
    }

    User.Stat.Gold += GainGold;

    sleep(1);
    
    cout << "\n\n";
}
void ItmEffVoodooDoll(Entity& User, Entity& Target){// 24
    cout << User.Name << " pins a Voodoo Doll" << "\n\n";
    sleep(1);

    cout << "You sacrificed " << User.Stat.MAXHP / 10 << " HP" << "\n\n";
    sleep(1);

    User.Stat.HP -= (User.Stat.MAXHP / 10);

    if (Target.Misc.Type == PLAYER1 || Target.Misc.Type == PLAYER2){
        Damage = (User.Stat.MAXHP * 0.7);
    }else{
        Damage = (User.Stat.MAXHP * 1.5);
    }

    if (User.Stat.HP <= 0){
        User.Stat.HP = 1;
    }

    cout << "It hurts slightly to you, ";
    sleep(2);

    cout << "but the pain it causes to " << Target.Name << " is much higher" << "\n\n";
    sleep(3);

    cout << "\tIt deals " << Damage << " Damage" << "\n\n";
    sleep(1);

}
void ItmEffPreciseNeedle(Entity& User, Entity& Target){// 25
    cout << User.Name << " used a Precise Needle" << "\n\n";
    sleep(1);

	cout << User.Name << " aims it carefully..." << "\n\n\t";
	sleep(2);

	for (int l = 0; l < 3; l++){
	    cout << ". ";
    	usleep(750000);
	}
    cout << "\n\n";

	Chance = rand() % 50 + 1;

	if (Chance == 33){
        cout << "     ~~~~~~~~~~~~~" << endl;
	    cout << "      PRECISE HIT" << endl;
        cout << "     ~~~~~~~~~~~~~" << "\n\n";
        sleep(2);
        InstaKill(Target);
	}else {
        cout << "But it missed the spot" << "\n\n";
        sleep(1);
        cout << "It dealt 1 damage..." << "\n\n";
        Damage = 1;
    }

	sleep(2);
}
void ItmEffArmageddon(Entity& User, Entity& Target){// 26
    clear();
    cout << "\n\tThe clouds turn dark,";
    sleep(2);
    cout << " and swirl around the colosseum,";
    sleep(1);
    cout << " violently." << "\n\n\n\n";
    sleep(2);
	cout << "\t\t\t\033[1;37m   " << User.Name;
    sleep(1);
    cout << " USED";
    sleep(1);
    cout << " AR"; usleep(500000); cout << "MA"; usleep(500000); cout << "GE"; usleep(500000); cout << "DDON";
    sleep(1);
    clear();
    cout << "\n\n\t ";
	for (int l = 0; l < 3; l++) {
        cout << ". ";
        usleep(800000);
    }
    ArmageddonAnim("\033[47;30m", 1);
    clear();
    
    Damage = 9999;

    if (Target.Misc.Type != CHAMPION){
        cout << "\n\n\n" << "\t\t\033[1;37m IT DEALS \033[1;91m"; 
        usleep(800000);
        for (int l = 0; l < 4; l++){
            usleep(800000);
            cout << 9;
        }
        usleep(800000);
        cout << "\033[1;37m DAMAGE!\033[0m";
        sleep (2);
        clear();
        cout << "\n\n\n";
    }else{
        for (int l = 0; l < 3; l++) {
        cout << ". ";
        usleep(800000);
        }
        Damage = 0;
        Dialogue(User,Hero,Champion,false,"\033[1;95m","Such a fool","\033[0m",0);
        Dialogue(User,Hero,Champion,false,"\033[1;95m","To think I would fall to my own attack","\033[0m",0);
        Dialogue(User,Hero,Champion,false,"\033[1;95m","You cannot vanquish me","\033[0m",0);
    }
}


//- Spell Classifications - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

                //Name + Desc char limit is 50 chars coz of shop    \033[1;37m  \033[0m
//Base Spells
Spell SplSupremeHeal(SupremHeal, "\033[1;95mSupreme \033[92mHeal\033[0m", "(Heals a \033[1;92mSUPERB\033[0m amount of HP [About ~50%])", 5, 1, 27);
Spell SplGreatHeal(GrtHeal, "\033[1;94mGreat \033[92mHeal\033[0m", "(Heals a good amount of HP [Above 30%])", 4, 1, 16);    // 9
Spell SplBloodBinding(BloodBind, "\033[1;31mBlood \033[91mBinding\033[0m", "(Absorbs Target's HP [up to 20%])", 7, 1, 16);     // 10
Spell SplWilloWisp(WillWisp, "\033[1;91mWill\033[90m-o-\033[91mWisp\033[0m", "(Burns Target [3-5 turns])", 5, 1, 21); 
Spell SplIgnitus(Ignits, "\033[1;91mIgnitus\033[0m", "(Massive Fireball [60% Chance to Burn])", 8, 1, 11);
Spell SplPoisonCloud(PsnCloud, "\033[1;92mPoison \033[90mCloud\033[0m", "(Poisons Target [3-5 turns])", 7, 1, 16);
Spell SplInfestation(Infestat, "\033[1;92mInfestation\033[0m", "(Flurry of Poisoning Attacks[2-6])", 9, 1, 11);
Spell SplViciousMockery(VMock, "\033[1;96mVicious \033[95mMockery\033[0m", "(Chance to Freeze [2-3 turns])", 4, 1, 16); // 15
Spell SplFrigidLaceration(FrigLaceration, "\033[1;96mFrigid Laceration\033[0m", "(Stronger Attack that may Freeze)", 5, 1, 11);
Spell SplThunderChain(ThundChain, "\033[1;93mThunder Chain\033[0m", "(4-10 Lightning Shots [25% to Shock])", 6, 1, 11);
Spell SplPolarityShock(PolarShock, "\033[1;94mPolarity \033[93mShock\033[0m", "(Wild ThunderBolt [80% to Shock])", 8, 1, 16);
Spell SplStatisticalLightbeam(StatBeam, "\033[1;93mStatistical LightBeam\033[0m", "(Damage = 20% Total Stats)", 6, 1, 11);
Spell SplMetaphysicalOverload(MetaOverload, "\033[1;95mMetaphysical Overload\033[0m", "(Low chance of INSTAKILL)", 4, 1, 11); // 20
Spell SplChromaticWave(ChromWave, "\033[1;95mCh\033[94mro\033[96mma\033[92mti\033[93mc \033[91mWa\033[95mve\033[0m", "(Uses a \033[1;95mR\033[91ma\033[93mn\033[92md\033[96mo\033[94mm \033[0mSpell's Effect)", 5, 1, 77);
//Class Exclusive Spells
Spell SplDuoSlash(DuoSlsh, "\033[1;33mDuo \033[37mSlash\033[0m", "(Double Slash that Attacks twice)", 4, 0, 16);                 // 2
Spell SplCrossSlash(CrossSlsh, "\033[1;33mCross \033[37mSlash\033[0m", "(Cool Slash that Attacks 3 Times)", 6, 0, 16);
Spell SplMagicaBlast(MBlast, "\033[1;94mMagica \033[37mBlast\033[0m", "(Magic Based Normal Attack [x1.2])", 2, 0, 16);           // 4
Spell SplArcaneBlast(ArcBlast, "\033[1;94mArcane \033[37mBlast\033[0m", "(Stronger Magic Based Attack [x1.8])", 3, 0, 16);
Spell SplTemperedCut(TempnRageCut, "\033[1;91mTempered \033[37mCut\033[0m", "(Guaranteed Critical Hit)", 6, 0, 16);              // 6
Spell SplEnragedCut(TempnRageCut, "\033[1;91mEnraged \033[37mCut\033[0m", "(Cheaper Guaranteed Critical Hit)", 3, 0, 16);        // 6 Both Have Same Effect
Spell SplKnightStance(KnghtStance, "\033[1;37mKnight's Stance\033[0m", "(Attack + Defend at the same time)", 3, 0, 11);
Spell SplRoyalKnightStance(RoylkKnghtStance, "\033[1;91mR\033[37mo\033[93my\033[37ma\033[93ml \033[37mKnight's Stance\033[0m", "(Attack[w/ Status] + Defend)", 5, 0, 36);// 8
//Class Ultimates
Spell SplOmnislash(Omnislsh, "\033[1;33mOmnislash\033[0m", "(Broken Slash that Attacks 5-6 Times)", 8, 0, 11);
Spell SplWarlockBlast(WarBlast, "\033[1;95mWarlock \033[94mBlast\033[0m", "(Massive Magic Based Attack [x3.0])", 4, 0, 16);
Spell SplVengeanceCut(VengCut, "\033[1;31mVengeful Cut\033[0m", "(Guaranteed HP Absorving CRIT)", 4, 0, 11);
Spell SplBlackKnightStance(BlckKnghtStance, "\033[1;90mBlack Knight's Stance\033[0m", "(Attack + Defend[Status x2])", 5, 0, 11);

//- Spell Effects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void SplEffSmallHeal(Entity& User){// 1

    int Heal;

    cout << User.Name << " casted Small Heal" << "\n\n";
    sleep(1);

    Heal = (User.Stat.MAXHP * 0.15) + (User.Stat.MA / 4);

    cout << "It Heals itself slightly" << "\n\n";
    sleep(1);

    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    cout << "\t " << User.Name << " Healed " << Heal << " HP" << endl;
    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    sleep(2);

    User.Stat.HP += Heal;

    StatOverflowCheck(User);

    clear();
}
void SplEffDuoSlash(Entity& User, Entity& Target){// 2
    cout << User.Name << " casted Duo Slash " << "\n\n";
    sleep(1);

    Damage = 0;
    int TotalDamage = 0;
						
	for (int t = 2; t > 0; t--){
	Target.Stat.HP -= Damage;
	BasicAttack(User, Target);
    TotalDamage += Damage;
	}

    sleep(1);

    cout << "\t+-----------------+" << endl;
    cout << "\t Total: " << TotalDamage << " Damage" << endl;;
    cout << "\t+-----------------+" << "\n\n";

	sleep(2);

    clear();
}
void SplEffCrossSlash(Entity& User, Entity& Target){// 3
    cout << User.Name << " casted Cross Slash " << "\n\n";
    sleep(1);

    Damage = 0;
    int TotalDamage = 0;
						
	for (int t = 3; t > 0; t--){
	Target.Stat.HP -= Damage;
	BasicAttack(User, Target);
    TotalDamage += Damage;
	}

    sleep(1);

    cout << "\t+-----------------+" << endl;
    cout << "\t Total: " << TotalDamage << " Damage" << endl;;
    cout << "\t+-----------------+" << "\n\n";

	sleep(2);

    clear();
}
void SplEffMagicaArcaneWarlockBlast(Entity& User, Entity& Target, float DamageMult){// 4-5 & 23
    if (DamageMult < 1.5){
        cout << User.Name << " casted Magica Blast " << "\n\n";
    }else if (DamageMult < 2.5){
        cout << User.Name << " casted Arcane Blast " << "\n\n";
    }else{
        cout << User.Name << " casted Warlock Blast " << "\n\n";
    }
    
    sleep(1);
    Damage = (User.Stat.MA * DamageMult) - Target.Stat.DEF;

    if (Damage <= 0) {
        Damage = 1;
    }
                
    Chance = rand() % 100 + 1;
    if (User.Stat.CRIT >= Chance) {//Critical hit
        Damage = Damage * User.Stat.CRITMULT; 

        CriticalHitUI();
        sleep (1);
    }
                    
    Chance = rand() % 100 + 1;
    if (Target.Stat.DODGE >= Chance) {//Dodge
        Damage = 0; 
            cout << "\t" << User.Name << " missed\n\n";
        usleep(500000);
    }else{
        cout << "\tIt deals " << Damage << " damage\n\n";
    }
        sleep(1);
}
void SplEffTemperedandEnragedCut(Entity& User, Entity& Target){// 6
    cout << User.Name << " casts a precise Attack" << "\n\n";
    
    sleep(1);

	Damage = User.Stat.ATK - Target.Stat.DEF;

	if (User.Status.Burn > 0) {//Burn cut damage
        Damage = Damage / 2;
    }

	if (Damage <= 0) {
        Damage = 1;
    }
		
	Damage *= User.Stat.CRITMULT;
    CriticalHitUI();
    sleep (1);
	cout << "\t" << User.Name << " dealt " << Damage << " damage\n\n"; 
    sleep(2);
    clear();
}
void SplEffKnightStance(Entity& User, Entity& Target){// 7
    cout << User.Name << " casted Knight's Stance" << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << " attacks" << "\n\n";
    BasicAttack(User, Target);

    sleep(1);

    cout << "\t" << User.Name << " defends" << "\n\n";
    Defend(User);

    sleep(1);
    clear();
}
void SplEffRoyalKnightStance(Entity& User, Entity& Target){// 8
    cout << User.Name << " casted the Royal Knight's Stance" << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << " attacks" << "\n\n";
    BasicAttack(User, Target);

    Chance = rand() % 2 + 1;
    if (Chance == 1){//Burn
        cout << "  It Burns" << endl;
        Target.Status.Burn++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Poison
        cout << "  It Poisons" << endl;
        Target.Status.Poison++;
        usleep(500000);
    }
    Chance = rand() % 3 + 1;
    if (Chance == 1){//Freeze
        cout << "  It Freezes" << endl;
        Target.Status.Freeze++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Shock
        cout << "  It Shocks" << endl;
        Target.Status.Shock++;
        usleep(500000);
    }

    sleep(1);

    cout << "\n\t" << User.Name << " defends" << "\n\n";
    Defend(User);

    sleep(1);
    clear();
}
void SplEffGreatHeal(Entity& User){// 9
    
    int Heal;

    cout << User.Name << " casted a Great Heal" << "\n\n";
    sleep(1);

    Chance = rand() % 100 + 1;
    if (User.Stat.CRIT >= Chance){
        Heal = (User.Stat.MAXHP * 0.30) + ((User.Stat.MAXHP * 0.05) * User.Stat.CRITMULT) + (User.Stat.MA / 2);
        cout << "\tIt CRITICALLY Heals itself Greatly!" << "\n\n";
    }else{
        Heal = (User.Stat.MAXHP * 0.30) + (User.Stat.MA / 2);
        cout << "It Heals itself thoroughly" << "\n\n";
    }
    sleep(1);

    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    cout << "\t " << User.Name << " Healed " << Heal << " HP" << endl;
    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    sleep(2);

    User.Stat.HP += Heal;

    StatOverflowCheck(User);

    clear();
}
void SplEffBloodBinding(Entity& User, Entity& Target){// 10

    int Heal;

    cout << User.Name << " casted Blood Binding" << "\n\n";
    sleep(1);

    cout << User.Name << "'s Teeth enlighten\n\n";
    sleep(1);
    
    cout << "And it sprints towards " << Target.Name << " to bite it" << "\n\n";
    sleep(2);

	Chance = rand() % 100 + 1;
	if (User.Stat.CRIT >= Chance) {
        CriticalHitUI();
        sleep(1);
        Damage = (Target.Stat.MAXHP * 0.20) + (User.Stat.MA / 5);
        if (Damage < 8){
            Damage = 8;
        }
        if (Damage > (User.Stat.MAXHP)){
            Damage = User.Stat.MAXHP;
        }
        cout << "\n\t" << User.Name << " CRITICALY absorved " << Damage << " HP!\n\n";
	}else {
        Damage = (Target.Stat.MAXHP * 0.15) + (User.Stat.MA / 8);
        if (Damage < 5){
            Damage = 5;
        }
        if (Damage > (User.Stat.MAXHP * 0.90)){
            Damage = User.Stat.MAXHP * 0.90;
        }
        cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~~~" << endl;
        cout << "\t " << User.Name << " Absorved " << Damage << " HP" << endl;
        cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~~~" << "\n\n";
    }
    sleep (2);
    Heal = Damage;
    User.Stat.HP += Heal;
    StatOverflowCheck(User);
}
void SplEffWilloWisp(Entity& User, Entity& Target){// 11
    
    int Burning = 3;

    cout << User.Name << " casted Will-o-Wisp" << "\n\n";
    sleep(1);

    cout << User.Name << " casts \033[91mfiery\033[0m spirits to surround " << Target.Name << "\n\n";
    sleep(2);

    Chance = rand() % 15 + 1;
	if (User.Stat.MA >= Chance){
        Burning++;
    }

    Chance = rand() % 80 + 1;
	if (User.Stat.CRIT >= Chance){
        Burning++;
	}

    switch (Burning){
        case 3:
        cout << "\t\033[91m" << Target.Name <<" is lightly Burned.\033[0m" << "\n\n";
        break;

        case 4:
        cout << "\t\033[91m" << Target.Name <<" is Burning!\033[0m" << "\n\n";
        break;

        case 5:
        CriticalHitUI();
        sleep(1);
        cout << "\t\033[91m" << Target.Name <<" is CRITICALLY Scorching!!\033[0m" << "\n\n";
        break;
    }
    sleep(2);
        Target.Status.Burn += Burning;
    
}
void SplEffIgnitus(Entity& User, Entity& Target){// 12
    cout << User.Name << " casted Ignitus" << "\n\n";
    sleep(1);

    cout << "Its sword gets red hot,";
    sleep(1);
    cout << " and a gigantic Fireball swirls out of it" << "\n\n";
    sleep(2);

    cout << "\t" << User.Name << ": '\033[91mIGNITUS\033[0m'" << "\n\n";

	Damage = (User.Stat.MA * 3) - Target.Stat.DEF;

    if (Damage <= 0){
        Damage = 3;
    };
    sleep (1);

	Chance = rand() % 100 + 1;
	if (User.Stat.CRIT >= Chance) {
		Damage *= User.Stat.CRITMULT;
		CriticalHitUI();
        sleep (1);
    }
						
	Chance = rand() % 100 + 1;
	if (Target.Stat.DODGE >= Chance) {
		Damage = 0;
		cout << "It missed" << "\n\n";
	}else {
        cout << "It dealt " << Damage << " damage!" << "\n\n"; 
        
					
	    Chance = rand() % 10 + 1;
        if (Chance <= 6) {
            sleep(1);
            Target.Status.Burn += 3;
            cout << "\033[91m" << Target.Name << " is burning!\033[0m" << "\n\n";
        }
    }
    sleep(1);
}
void SplEffPoisonCloud(Entity& User, Entity& Target){// 13

    int Poisoning = 3;

    cout << User.Name << " casted Poison Cloud " << "\n\n";
    sleep(1);

    cout << User.Name << " emits a heavy cloud of toxin to " << Target.Name << "\n\n";
    sleep(2);

    Chance = rand() % 15 + 1;
	if (User.Stat.MA >= Chance){
        Poisoning++;
    }

    Chance = rand() % 80 + 1;
	if (User.Stat.CRIT >= Chance){
        Poisoning++;
	}

    switch (Poisoning){
        case 3:
        cout << "\t\033[92m" << Target.Name <<" is lightly Poisoned.\033[0m" << "\n\n";
        break;

        case 4:
        cout << "\t\033[92m" << Target.Name <<" is Poisoned!\033[0m" << "\n\n";
        break;

        case 5:
        CriticalHitUI();
        sleep(1);
        cout << "\t\033[92m" << Target.Name <<" is CRITICALLY contaminated in Poison!!\033[0m" << "\n\n";
        break;
    }
    sleep(2);
        Target.Status.Poison += Poisoning;
    
}
void SplEffInfestation(Entity& User, Entity& Target){// 14

    int TotalDamage = 0, TotalPoison = 0;

    cout << User.Name << " casted Infestation" << "\n\n";
    sleep(1);

    cout << User.Name << " is prepared to Contaminate" << "\n\n";
    sleep(1);

    Damage = 0;

	for (int t = rand() % 4 + 3; t > 0; t--){

	    Target.Stat.HP -= Damage;
	    Damage = (User.Stat.ATK / 2) - (Target.Stat.DEF / 2);

        if (Damage <= 0){
            Damage = 2;
        }
        usleep (250000);

	    Chance = rand() % 100 + 1;
	    if (User.Stat.CRIT >= Chance) {
	    	Damage *= User.Stat.CRITMULT;
		    CriticalHitUI();
            usleep (800000);
        }
						
	    Chance = rand() % 100 + 1;
	    if (Target.Stat.DODGE >= Chance) {
			Damage = 0;
			cout << "It missed" << "\n\n";
		}else {
            cout << "\tIt dealt " << Damage << " damage! ";

            TotalDamage += Damage;

            Chance = rand() % 100 + 1;
            if (Chance <= (50 + User.Stat.MA)){
                Target.Status.Poison++;
                TotalPoison++;
                cout << "[\033[1;92m+1 Poison!\033[0m]";
            }
            cout << "\n\n";
        }
        usleep(500000);
	}
    sleep(1);
    cout << "   o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o" << endl;
    cout << "    Total: " << TotalDamage << " Damage [\033[1;92m+" << TotalPoison << " Poison\033[0m]" << endl;
    cout << "   o~~~~~~~~~~~~~~~~~~~~~~~~~~~~~o" << "\n\n";
    sleep(1);
}
void SplEffViciousMockery(Entity& User, Entity& Target){// 15
        
    int Frozen = 0;
    bool Effective = false;
    string Succeed[]{ "",// Good Disses
        "Do you know who else sucks at fighting?",
        "You suck royal ass at this",
        "Hmmmmm, Pass",
        "What type of scum are you even?",
        "My dog could swing that weapon better",
    };
    string Fail[]{ "",// Bad Disses
        "You're not that good..!",
        "This is TOO easy",
        "C'mon, I don't have all day",
        "Uhhh.....",
        "Who's this unpopular dummy?",
    };

    cout << User.Name << " casted some Vicious Mockery" << "\n\n";
    sleep(1);

    Chance = rand() % 25 + 1;
	if (User.Stat.MA >= Chance){ // Odds (Magic based and Dodge based)
        Chance = rand() % 100 + 1;
        if (Target.Stat.DODGE <= Chance){
            Effective = true;
            Frozen = 2;
        }
    }
//true
    Chance = rand() % 5 + 1;
    if (Effective == true){ // Random Insult deciding
        cout << "   " << User.Name << ": '" << Succeed[Chance] <<"'"<< "\n\n";
    }else{
        cout << "   " << User.Name << ": '" << Fail[Chance] <<"'"<< "\n\n";
    }
    sleep(2);

    if (Effective == true){ // Crit chance
        Chance = rand() % 100 + 1;
	    if (User.Stat.CRIT >= Chance){
            Frozen++;
	    }
    }

    if (Effective == true){
        cout << "\t\t!!!" << "\n\n";
        sleep(1);
        cout << "\t" << "'THE CROWD ROARS IN EXCITEMENT'" << "\n\n";
        sleep(1);
    }else {
        cout << "\t";
        for (int l = 0; l < 3; l++){
            cout << ". ";
            usleep(500000);
        }
        cout << "\n\n";
    }
    sleep(1);

    switch (Frozen){
        case 2:
        cout  << Target.Name <<" is \033[96mFrozen\033[0m from embarassment!" << "\n\n";
        break;

        case 3:
        CriticalHitUI();
        sleep(1);
        cout << Target.Name <<" is \033[96mCRITICALLY Frostbitten\033[0m with shame!!" << "\n\n";
        break;

        default:
        cout << "   " << "It clearly didn't afect anyone" << "\n\n";
        break;
    }
    sleep(2);
        Target.Status.Freeze += Frozen;
}
void SplEffFrigidLaceration(Entity& User, Entity& Target){// 16
    cout << User.Name << " casted Frigid Laceration" << "\n\n";
    sleep(1);
    cout << User.Name << "'s Sword gets \033[96mFrozen\033[0m, ";
    sleep(1);
    cout << "and it slashes " << Target.Name << "\n\n";
    sleep(1);

	Damage = (User.Stat.ATK + (User.Stat.MA / 2)) - Target.Stat.DEF;
    if (Damage <= 0){
        Damage = 1;
    };
    sleep (1);

	Chance = rand() % 100 + 1;
	if (User.Stat.CRIT >= Chance) {
	    Damage *= User.Stat.CRITMULT;
	    CriticalHitUI();
        sleep (1);
    }

	Chance = rand() % 100 + 1;
	if (Target.Stat.DODGE >= Chance) {
	    Damage = 0;
	    cout << "It missed" << endl << endl;
	}else {
        cout << "\tIt dealt " << Damage << " damage!" << "\n\n";
        sleep(1);

	    Chance = rand() % 20 + 1;
	    if (User.Stat.MA >= Chance){
            Chance = rand() % 100 + 1;
            if (Target.Stat.DODGE <= Chance) {
                cout << "    \033[96m" << NamelenghtBar(Target,"*") << "*******************\033[0m" << endl;
                cout << "    " << Target.Name << "\033[96m FREEZES INTERNALLY\033[0m" << endl;
                cout << "    \033[96m" << NamelenghtBar(Target,"*") << "*******************\033[0m" << "\n\n";
                Target.Status.Freeze++;
                sleep(2);
            }
        }
    }
}
void SplEffThunderChain(Entity& User, Entity& Target){// 17

    int TotalDamage = 0, TotalShock = 0;

    cout << User.Name << " casted a Thunder Chain" << "\n\n";
    sleep(1);

    cout << User.Name << " is ready for some \033[93mShocking\033[0m moves!" << "\n\n";
    sleep(1);

    Damage = 0;

	for (int t = rand() % 7 + 4; t > 0; t--){

	    Target.Stat.HP -= Damage;
	    Damage = (User.Stat.MA/4);

        if (Damage <= 0){
            Damage = 1;
        }
        usleep (250000);

	    Chance = rand() % 100 + 1;
	    if (User.Stat.CRIT >= Chance) {
	    	Damage *= User.Stat.CRITMULT;
		    cout << "       \\/\\\033[93mCRITICAL SHOCK\033[0m/\\/" << "\n\n";
            usleep (800000);
        }
						
	    Chance = rand() % 100 + 1;
	    if (Target.Stat.DODGE >= Chance) {
			Damage = 0;
			cout << "It missed" << "\n\n";
		}else {
            cout << "\tIt dealt " << Damage << " damage! ";

            TotalDamage += Damage;

            Chance = rand() % 4 + 1;
            if (Chance == 3){
                Target.Status.Shock++;
                TotalShock++;
                cout << "[\033[1;93m+1 Shock!\033[0m]";
            }
            cout << "\n\n";
        }
        usleep (400000);
	}
    sleep(1);
    cout << "   \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/" << endl;
    cout << "    Total: " << TotalDamage << " Damage [\033[1;93m+" << TotalShock << " Shock\033[0m]" << endl;
    cout << "   \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/" << "\n\n";
    sleep(1);
}
void SplEffPolarityShock(Entity& User, Entity& Target){// 18
    cout << User.Name << " casted Polarity Shock" << "\n\n";
    sleep(1);

    cout << User.Name << " raises its hand, ";
    sleep(1);
    cout << "and the sky starts to \033[93mFlash\033[0m" << "\n\n";
    sleep(2);

    cout << "\t" << User.Name << ": '\033[93mELECTRIFY\033[0m'" << "\n\n";

	Damage = (User.Stat.MA * 3) - Target.Stat.DEF;

    if (Damage <= 0){
        Damage = 3;
    };
    sleep (1);

	Chance = rand() % 100 + 1;
	if (User.Stat.CRIT >= Chance) {
		Damage *= User.Stat.CRITMULT;
		CriticalHitUI();
        sleep (1);
    }
						
	Chance = rand() % 100 + 1;
	if (Target.Stat.DODGE >= Chance) {
		Damage = 0;
		cout << "It missed" << "\n\n";
	}else {
        cout << "It dealt " << Damage << " damage!" << "\n\n"; 
        
					
	    Chance = rand() % 10 + 1;
        if (Chance <= 8) {
            sleep(1);
            Target.Status.Shock += 3;
            cout << Target.Name << " is \033[93mShocked!\033[0m" << "\n\n";
        }
    }
    sleep(1);
}
void SplEffStatisticalLightBeam(Entity& User, Entity& Target){// 19
    cout << User.Name << " casted Statistical Lightbeam" << "\n\n";
    sleep(1);

    cout << "A violent Godray falls upon " << Target.Name << "\n\n";
    sleep (1);

	Damage = (User.Stat.ATK + User.Stat.MA + User.Stat.CRIT + User.Stat.DODGE + User.Stat.AC + User.Stat.MAXHP + User.Stat.MAXMANA + User.Stat.CRITMULT)/5 - Target.Stat.DEF;
    if (Damage <= 0){
        Damage = 1;
    }

	for (int t = 10; t > 0; t--){
		cout << endl << "                 ||";	//cout << endl << "	     |⣿⣿|";
		usleep(20000);
	}
    cout << endl << "         ._..:'''  ''':.._." << "\n\n";	//cout << endl << "	⣄_⣀⣴⣿⣿⣿⣿⣿⣿⣦⣀_⣠" << "\n\n";

    Chance = rand() % 100 + 1;
	if (User.Stat.CRIT >= Chance) {
		Damage *= User.Stat.CRITMULT;
		CriticalHitUI();
        sleep (1);
    }
						
	Chance = rand() % 100 + 1;
	if (Target.Stat.DODGE >= Chance) {
		Damage = 0;
		cout << "It missed" << "\n\n";
	}else {
        cout << "It dealt " << Damage << " damage!" << "\n\n";
    }
    sleep(1);
}
void SplEffMetaphysicalOverload(Entity& User, Entity& Target){// 20
    cout << User.Name << " casted a Metaphysical Overload" << "\n\n";
    sleep(1);

    cout << "You try to invade its mind..." << "\n\n";
    sleep(1);

    cout << "\t";
    for (int l = 0; l < 3; l++){
        cout << ". ";
        usleep(500000);
    }
    cout << "\n\n";
    sleep(1);

	Chance = rand() % 1000 + 1;
	if (Chance <= (50 + (User.Stat.MA*3))){
        cout << "\t !!!";
        usleep(500000);
        InstaKill(Target);

        if (Target.Misc.Type == ENEMY){
            sleep(2);
            cout << "It looks...";
            sleep(2);
            cout << " dead.\n\n";
        }
	}else{
        cout << "But it failed\n\n";
    }
    sleep(1);
}
void SplEffChromaticWave(Entity& User, Entity& Target){// 21

    string RandomSpell[]{"",
        "Metaphysical Overload",//1
        "    Thunder Chain    ",//2
        "  Frigid Laceration  ",//3
        "    Blood Binding    ",//4
        "       Ignitus       ",//5
        "     Infestation     ",//6
        "Statistical Lightbeam",//7
        "     Will-o-Wisp     ",//8
        "    Poison Cloud     ",//9
        "   Vicious Mockery   ",//10
        "     Great Heal      ",//11
        "     Small Heal      ",//12
        "    Tempered Cut     ",//13
        "    Magica Blast     ",//14
        "      Duo Slash      ",//15
        "     Armageddon      "//Secret 16
    };

    cout << User.Name << " casted the Chromatic Wave" << "\n\n";
    sleep(1);
    clear();

    for(int l = 0; l < 15; l++){

        int Timer = (5000 + (8000 * l));
        Chance = rand() % 100 + 1;
        if(Chance == 33){//Armageddon Chance
            Chance = 16;
        }else{
            Chance = rand() % 15 + 1;
        }

        cout << "\033[94m";
        cout << "\n\t,~~======~~======~~======~~======~~===," << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t^~~======~~======~~======~~======~~===^" << endl;
        usleep(Timer);
        clear();

        cout << "\033[95m";
        cout << "\n\t,==~~======~~======~~======~~======~~=," << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t^======~~======~~======~~======~~=====^" << endl;
        usleep(Timer);
        clear();

        cout << "\033[91m";
        if (l == 14){
            cout << "\033[93m";
        }
        cout << "\n\t,====~~======~~======~~======~~======~," << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t^====~~======~~======~~======~~======~^" << "\n\n";
        usleep(Timer);
        if (l == 14){
            cout << "\033[0m";
            break;
        }
        clear();
        
        cout << "\033[92m";
        cout << "\n\t,======~~======~~======~~======~~=====," << endl;
        cout << "\t/                                     \\" << endl;
        cout << "\t\\                                     /" << endl;
        cout << "\t/        " << RandomSpell[Chance] <<"        \\" << endl;
        cout << "\t^==~~======~~======~~======~~======~~=^" << endl;
        usleep(Timer);
        clear();
    }
    sleep(2);

    switch (Chance){
        case 1:
        SplEffMetaphysicalOverload(User, Target);
        break;
        case 2:
        SplEffThunderChain(User, Target);
        break;
        case 3:
        SplEffFrigidLaceration(User, Target);
        break;
        case 4:
        SplEffBloodBinding(User, Target);
        break;
        case 5:
        SplEffIgnitus(User, Target);
        break;
        case 6:
        SplEffInfestation(User, Target);
        break;
        case 7:
        SplEffStatisticalLightBeam(User, Target);
        break;
        case 8:
        SplEffWilloWisp(User, Target);
        break;
        case 9:
        SplEffPoisonCloud(User, Target);
        break;
        case 10:
        SplEffViciousMockery(User, Target);
        break;
        case 11:
        SplEffGreatHeal(User);
        break;
        case 12:
        SplEffSmallHeal(User);
        break;
        case 13:
        SplEffTemperedandEnragedCut(User, Target);
        break;
        case 14:
        SplEffMagicaArcaneWarlockBlast(User, Target, 1.3);
        break;
        case 15:
        SplEffDuoSlash(User, Target);
        break;
        case 16:
        ItmEffArmageddon(User, Target);
        break;
    }

}
void SplEffOmnislash(Entity& User, Entity& Target){// 22
    cout << User.Name << " casted OmniSlash " << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << ": 'OMNISLASH'" << "\n\n";
    sleep(1);

    Damage = 0;
    int TotalDamage = 0;
						
	for (int t = rand() % 2 + 5; t > 0; t--){
	Target.Stat.HP -= Damage;
	BasicAttack(User, Target);
    TotalDamage += Damage;
	}

    sleep(1);

    cout << "\t+-----------------+" << endl;
    cout << "\t Total: " << TotalDamage << " Damage" << endl;;
    cout << "\t+-----------------+" << "\n\n";

	sleep(2);

    clear();
}
void SplEffVengeanceCut(Entity& User, Entity& Target){// 24

    int Heal;

    cout << User.Name << " casts a Vengeful Cut" << "\n\n";
    sleep(1);

    cout << User.Name << "'s eyes enrage" << "\n\n";
    sleep(1);

	Damage = User.Stat.ATK - Target.Stat.DEF;

	if (User.Status.Burn > 0) {//Burn cut damage
        Damage = Damage / 2;
    }

	if (Damage <= 0) {
        Damage = 1;
    }
		
	Damage *= User.Stat.CRITMULT;
    Heal = Damage * 0.15;
    CriticalHitUI();
    sleep (1);
	cout << "\t" << User.Name << " dealt " << Damage << " damage\n\n";
    sleep(1);
    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    cout << "\t " << User.Name << " Healed " << Heal << " HP" << endl;
    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    sleep(2);
    clear();
}
void SplEffBlackKnightStance(Entity& User, Entity& Target){// 25
    cout << User.Name << " casted the Black Knight's Stance" << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << " gets a grim look behind its helmet" << "\n\n";
    sleep(1);

    cout << "\t" << User.Name << " attacks" << "\n\n";
    BasicAttack(User, Target);

    Chance = rand() % 2 + 1;
    if (Chance == 1){//Burn
        cout << "  It Burns" << endl;
        Target.Status.Burn++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Poison
        cout << "  It Poisons" << endl;
        Target.Status.Poison++;
        usleep(500000);
    }
    Chance = rand() % 3 + 1;
    if (Chance == 1){//Freeze
        cout << "  It Freezes" << endl;
        Target.Status.Freeze++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Shock
        cout << "  It Shocks" << endl;
        Target.Status.Shock++;
        usleep(500000);
    }

    sleep(1);

    cout << "\n\t" << User.Name << " defends" << "\n\n";
    Defend(User);

    Chance = rand() % 2 + 1;
    if (Chance == 1){//Burn
        cout << "  It Burns" << endl;
        Target.Status.Burn++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Poison
        cout << "  It Poisons" << endl;
        Target.Status.Poison++;
        usleep(500000);
    }
    Chance = rand() % 4 + 1;
    if (Chance == 1){//Freeze
        cout << "  It Freezes" << endl;
        Target.Status.Freeze++;
        usleep(500000);
    }
    Chance = rand() % 2 + 1;
    if (Chance == 1){//Shock
        cout << "  It Shocks" << endl;
        Target.Status.Shock++;
        usleep(500000);
    }


    sleep(1);
    clear();
}
void SplEffSupremeHeal(Entity& User){// 26
    int Heal;

    cout << User.Name << " casted a Supreme Heal!" << "\n\n";
    sleep(1);

    Chance = rand() % 75 + 1;
    if (User.Stat.CRIT >= Chance){
        Heal = (User.Stat.MAXHP * 0.40) + ((User.Stat.MAXHP * 0.05) * User.Stat.CRITMULT) + (User.Stat.MA / 1.25);
        cout << "\tIt CRITICALLY Heals itself Supremely!" << "\n\n";
    }else{
        Heal = (User.Stat.MAXHP * 0.40) + (User.Stat.MA / 1.25);
        cout << "It Heals itself incredibly" << "\n\n";
    }
    sleep(1);

    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    cout << "\t " << User.Name << " Healed " << Heal << " HP" << endl;
    cout << "\t" << NamelenghtBar(User, "~") << "~~~~~~~~~~~~~~~" << endl;
    sleep(2);

    User.Stat.HP += Heal;

    StatOverflowCheck(User);

    clear();
}

//- Relic Classifications - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
                
                    //Desc char limit is 36, Name is 17, ImageLines is 10 chars coz of Relic Menu (no Parentesis) + they must all be the limits (Just space them)
Relic RlcHighCarbonSword(CarbonSwrd,   "High Carbon Sword", "    Increases CritDamage [+100%]    ", "    /\\    ", "    ||    ", "    ||    ", "\033[90m  ''TT''  \033[0m", "\033[90m    ||    \033[0m");
Relic RlcArcaneRing(ArcRing,           "   Arcane Ring   ", "      Spells cost 1 less Mana       ", "\033[94m   _,_,_  \033[0m", "\033[94m  (\033[0m#\033[94m____) \033[0m", "\033[93m  /\033[33m/   \\\\ \033[0m", "\033[33m  \\\\___// \033[0m", "\033[33m   '---'  \033[0m");
Relic RlcTarotNecklace(TarotNeckl,     " Tarot Necklace  ", "+Odds of UP Cards having Higher Rank", "   ....   ", " .'    '. ", "'._.--._.'", " |_\033[94m () \033[0m_| ", "   '--'   ");
Relic RlcWarlocksStone(WarlckStone,    " Warlock's Stone ", "          +1 Spell Token            ", "          ", "\033[91m~\033[35m   ___   \033[0m", "\033[35m__.'\033[0m#\033[35m.'\\_\033[91m~\033[0m", "\033[35m\\_'_.'.__]\033[0m", "\033[91m   ~      \033[0m");
Relic RlcCutePouch(CuteBag,            "   Cute Pouch    ", "           +2 Item Slots            ", "\033[93m   ____   \033[0m", "\033[93m   .' \\\033[95m * \033[0m", "\033[95m*\033[93m /\033[0mo o\033[93m '. \033[0m", "\033[93m / \033[0m U \033[93m  |\033[95m*\033[0m", "\033[93m \\______/ \033[0m");// 5
Relic RlcCorruptSigil(CorruptSigl,     "  Corrupt Sigil  ", "     Bosses get slightly weaker     ", "\033[92m#\033[35m    |   \033[91m^\033[0m", "\033[35m  .--|-'' \033[0m", "\033[35m     |    \033[0m", "\033[35m    \\| .'.\033[0m", "\033[93m*\033[35m '.-|'  \033[96m~\033[0m");
Relic RlcLuckyCharm(LuckyChrm,         "   Lucky Charm   ", "        Earn more XP [+30%]         ", "\033[92m    /\\    \033[0m", "  .'\033[92m/\\\033[0m'.  \033[0m", "\033[92m<\033[0m:\033[92m<    >\033[0m:\033[92m>\033[0m", "  '.\033[92m\\/\033[0m.'  \033[0m", "\033[92m    \\/    \033[0m");
Relic RlcCatStatue(CatStatu,           "   Cat Statue    ", " Shop Prices are discounted [-25%]  ", "()\033[93m/\\__/\\  \033[0m", "\033[93m||\033[0m* VV *\033[93m) \033[0m", "\033[93m\\ \\   _/| \033[0m", "\033[93m |   \033[0m(_\033[93m_| \033[0m", "\033[93m |_.__._| \033[0m");
Relic RlcUnderworldSkull(UnderSkull,   " Underworld Skull", "  Upon Death, Revive Once [50% HP]  ", "  ______  ", " /      \\ ", "|\033[91m #  # \033[0m  \\", " \\...-'\\ |", " \\'''_.-:'");
Relic RlcCheatScroll(CheatM,           "  Cheat Scroll   ", " Chance to get an Extra Turn [15%]  ", " \033[90m__----O\033[0m  ", "\033[90mO--**''\033[0m\\  ", " \\      \\ ", "  \\\033[90m __---O\033[0m", "   \033[90mO--**''\033[0m");// 10
Relic RlcInsightfulLenses(InsightLen,  "Insightful Lenses", "  Ability to see the Enemy's Stats  ", " ,,,  ,,, ", " __   __  ", "/  \\ /  \\ ", "\\\033[36m#\033[0m_/ \\\033[36m#\033[0m_/ ", "          ");
Relic RlcCeramicPot(CeramPot,          "   Ceramic Pot   ", " When a Round ends, gain more Gold  ", "  ______  ", "  \\#   /  ", "  /    \\  ", "\033[92m  \\/\\/\\/  \033[0m", "  \\____/  ");
Relic RlcEdibleHeart(EatHeart,         "  Edible Heart   ", "   When a Round ends, heal 15% HP   ", "\033[91m  ..   .. \033[0m", "\033[91m '\033[0m#\033[91m '.'  '\033[0m", "\033[91m '.     .'\033[0m", "\033[91m   '. .'  \033[0m", "\033[91m     '    \033[0m");
Relic RlcEggPal(EggP,                  "     Egg Pal     ", "     Might Attack alongside You     ", " \033[90m  __\033[91m#\033[90m_   \033[0m", "\033[90m <\033[0m......\033[90m> \033[0m", " \033[93m/\033[0m -__- \033[93m\\ \033[0m", " \033[93m|\033[90m______\033[93m|\033[0m ", " \033[90m \\____/ \033[0m ");
Relic RlcMagicaCarnation(MagicaCarnati," Magica Carnation", "When a Round ends, restore more Mana", "\033[36m  \\\033[96m^\033[36m\\\033[96m^\033[36m/\033[96m^\033[36m/ \033[0m", "\033[36m    \\\033[96m^\033[36m/   \033[0m", "\033[92m     |    \033[0m", "\033[92m   '\\|/'  \033[0m", "\033[92m     |    \033[0m");// 15

//- Relic Effects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

void RelicObtainCheck(Entity& Player, Relic *useRelic){
    if (Player.Misc.Type == PLAYER1){
        useRelic->Obtained.P1 = true;
    }else if (Player.Misc.Type == PLAYER2){
        useRelic->Obtained.P2 = true;
    }
}
void RelicEffects(Entity& Player, Relic *useRelic){

    clear();
    RelicObtainCheck(Player, useRelic);

    switch (useRelic->ID){
        case CarbonSwrd:
        Player.Stat.CRITMULT += 1; // High Carbon Sword Check
        break;

        case WarlckStone:
        Player.Misc.Spellslots++; // Warlock's Stone Check
        break;

        case CuteBag:
        Player.Misc.Itemslots += 2; // Cute Pouch Check
        break;

        case LuckyChrm:
        Player.Misc.XPMult += 0.30; // Lucky Charm Check
        break;

        case CatStatu:
        Player.Misc.PriceMult -= 0.25; // Cat Statue Check
        break;

        case CeramPot:
        Player.Misc.GoldMult += 0.35; // Ceramic Pot Check
        break;

        case MagicaCarnati:
        Player.Misc.ManaMult += 0.75; // Magica Carnation Check
        break;
    }
    cout << "\t\t\t\t     " << "-  - - --" << Player.Name << " AQUIRED A RELIC-- - -  -" << "\n\n";
    sleep(1);
    cout << "\t\t\t\t\t\t    " << useRelic->Image.Line1 << endl;
    usleep(100000);
    cout << "\t\t\t\t\t\t    " << useRelic->Image.Line2 << endl;
    usleep(100000);
    cout << "\t\t\t\t\t\t    " << useRelic->Image.Line3 << endl;
    usleep(100000);
    cout << "\t\t\t\t\t\t    " << useRelic->Image.Line4 << endl;
    usleep(100000);
    cout << "\t\t\t\t\t\t    " << useRelic->Image.Line5 << "\n\n";
    usleep(500000);
    cout << "\t\t\t\t\t\t      " << "Got the" << endl;
    usleep(500000);
    cout << "\t\t\t\t\t\t" << "*~~~~~~~~~~~~~~~~~*" << endl;
    cout << "\t\t\t\t\t\t" << " " << useRelic->Name << endl;
    cout << "\t\t\t\t\t\t" << "*~~~~~~~~~~~~~~~~~*" << "\n\n";
    sleep(2);
    EnterShort();
    
}

void BossWeakeningbyCorruptSigil(Entity&Player, Entity& Target){
    if (Player.Misc.Type == PLAYER1){ // Corrupted Sigil Check
        if (RlcCorruptSigil.Obtained.P1 == true){
            Target.Stat.HP *= 0.85;
            Target.Stat.ATK *= 0.9;
            Target.Stat.MA *= 0.9;
            Target.Stat.AC *= 0.8;

        }
    }else if (Player.Misc.Type == PLAYER2){
        if (RlcCorruptSigil.Obtained.P2 == true){
            Target.Stat.HP *= 0.85;
            Target.Stat.ATK *= 0.9;
            Target.Stat.MA *= 0.9;
            Target.Stat.AC *= 0.8;
        }
    }
}
void EggPalAction(Entity&Player, Entity& Target){
    cout << "Egg Pal assists " << Player.Name << "!\n\n";
    sleep(1);

    if (Player.Stat.HP < Player.Stat.MAXHP / 5){
        int Heal = Player.Stat.MA / 3;
        cout << "Egg Pal restored " << Heal << " HP to " << Player.Name << "\n\n";
        Player.Stat.HP += Heal;
    }else{
        Damage = Player.Stat.ATK / 3;
        cout << "Egg Pal deals " << Damage << " Damage!" << "\n\n";
        Target.Stat.HP -= Damage;
    }
    sleep(1);
    StatOverflowCheck(Player);
}

//- Upgrade Classifications - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

                //Name + Desc char limit is 50 chars coz of shop
Upgrade UpgConstitutionBoost(CONSTITUTION, "\033[92mConstitution\033[0m Boost", "(MAX HP + 20% [At Least + 10])", 10, 9);
Upgrade UpgSwordSharpening(SHARPENING, "\033[90mSword\033[0m Sharpening", "(ATK + 20% [At Least + 5])", 10, 9);
Upgrade UpgArcanaBurst(ARCBURST, "\033[94mArcana\033[0m Burst", "(MA + 20% [At Least + 5])", 10, 9);
Upgrade UpgArmorReinforcement(ARMORUP, "\033[90mArmor\033[0m Reinforcement", "(AC + 20% [At Least + 5])", 10, 9);
Upgrade UpgBetterSleightofHand(SLEIGHTOFHAND, "Better \033[95mSleight of Hand\033[0m", "(Increases CRIT% [+5%])", 10, 9);
Upgrade UpgLighterBoots(LIGHTBOOTS, "\033[91mLighter\033[0m Boots", "(Increases DODGE% [+4%])", 10, 9);
Upgrade UpgFullHeal(FULLHEAL, "\033[92mFULL HEAL\033[0m", "(Fully Heals HP, MANA & Status Effects)", 8, 9);
Upgrade UpgWorseTemper(TEMPERBAD, "Worse \033[31mTemper\033[0m", "(Increases CritDamage [+20%])", 8, 9);
Upgrade UpgFourLeafClover(LUCKYCLOVER, "Four Leaf \033[92mClover\033[0m", "(Earn More XP [+5%])", 6, 9);
Upgrade UpgEtherealBreath(ETHEREAL, "\033[94mEthereal\033[0m Breath", "(+3 MAX Mana)", 10, 9);

//- Upgrade Effects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

Upgrade UpgradeGetRandom(){

    Chance = rand() % TotalUpgrades + 1;

    switch (Chance) { // ID to Effect Check

        case 1:
        return UpgConstitutionBoost;
        break;

        case 2:
        return UpgSwordSharpening;
        break;

        case 3:
        return UpgArcanaBurst;
        break;

        case 4:
        return UpgArmorReinforcement;
        break;

        case 5:
        return UpgBetterSleightofHand;
        break;

        case 6:
        return UpgLighterBoots;
        break;

        case 7:
        return UpgFullHeal;
        break;

        case 8:
        return UpgWorseTemper;
        break;

        case 9:
        return UpgFourLeafClover;
        break;

        case 10:
        return UpgEtherealBreath;
        break;
    }
    return NoUpgrade;
}


void UpgradeEffectint(Entity& Player, int& StatUpgraded, int StatBoost, int Minimum, string Message, string Stat){

    if (StatBoost < Minimum){
        StatBoost = Minimum;
    }

    clear();

    cout << "\n\t" << "+------------------------------+" << endl;
    cout << "\t " << Message << endl;
    cout << "\t" << "+------------------------------+" << "\n\n";
    sleep(1);

    cout << "\t\t     " << Stat << " +" << StatBoost << "\n\n";
    sleep(1);

    cout << "\t\t    " << StatUpgraded;
    usleep(500000);
    cout << "  ->  ";
    usleep(500000);
    cout << StatUpgraded + StatBoost << "\n\n";
    sleep(1);

    StatUpgraded += StatBoost;

    EnterShort();
    clear();
}

void UpgradeEffectfloat(Entity& Player, float& StatUpgraded, int StatBoost, int Minimum, string Message, string Stat){

    if (StatBoost < Minimum){
        StatBoost = Minimum;
    }

    clear();

    cout << "\n\t" << "+------------------------------+" << endl;
    cout << "\t " << Message << endl;
    cout << "\t" << "+------------------------------+" << "\n\n";
    sleep(1);

    cout << "\t\t     " << Stat << " +" << StatBoost << "\n\n";
    sleep(1);

    cout << "\t\t    " << StatUpgraded;
    usleep(500000);
    cout << "  ->  ";
    usleep(500000);
    cout << StatUpgraded + StatBoost << "\n\n";
    sleep(1);

    StatUpgraded += StatBoost;

    EnterShort();
    clear();
}

void UpgradeEffectPercent(Entity& Player, float& StatUpgraded, float StatBoost, float Minimum, string Message, string Stat){

    if (StatBoost < Minimum){
        StatBoost = Minimum;
    }

    clear();

    cout << "\n\t" << "+------------------------------+" << endl;
    cout << "\t " << Message << endl;
    cout << "\t" << "+------------------------------+" << "\n\n";
    sleep(1);

    cout << "\t\t     " << Stat << " +" << StatBoost * 100 << "%" << "\n\n";
    sleep(1);

    cout << "\t\t    " << StatUpgraded * 100 << "%";
    usleep(500000);
    cout << "  ->  ";
    usleep(500000);
    cout << (StatUpgraded + StatBoost) * 100 << "%" << "\n\n";
    sleep(1);

    StatUpgraded += StatBoost;

    EnterShort();
    clear();
}
