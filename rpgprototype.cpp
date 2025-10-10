#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int Damage, Shop, Chance, AllVar, Turn, Action, eAction = 1, Gold = 9, GainGold, GainMANA, Heal, Consumable = 9, SpellSlots = 4, Round = 0, BossRound = 0, BattleActive = 0, Temp1 = 5;
int E1, MPrice, Price, UpOpt1, UpOpt2, UpOpt3, PayOpt, PayUp, PayItem, PaySpell, ShopChoice, Class;
int Pcloud = 1, Igni = 1, FrigL = 1, Thund = 1, MPOver = 0, HPSteal = 1, HealS = 1, LightB = 0, VMock = 1;
float Tarot = 0, Ares = 2, Athena = 1;
int Burn = 0, eBurn = 0, Freeze = 0, eFreeze = 0, Poison = 0, ePoison = 0;

string P1, Enter;
char Confirm;

string ActionNames[] = {"Defend", "Attack", "Spell","Consumable"};

string RelicNames[] = {};
string UpgradeName[] = {"","ATK + 3","MA + 3","Max HP + 6","Heal 50%","AC + 2", "CRIT% + 2%","DODGE% + 1%"};

// (Deal 5x the HP you Sacrifice)
// (HP & Mana = 100% & Status Heal)

string ItemName[] = {"","Precise Needle","Cursed Dice","Status Potion","Ice Flask","Burning Cinders","Blood Coating","Vitality Coating","Energy Coating",
					"Healing Potion","Poison Dart","Mana Flask","Violet Flask","Ultimate Flask","Armageddon"};

string ItemDesc[] = {""," (Tiny chance of InstaKill)"," (Random Effect)"," (Heals Status)"," (Apply Freeze [2 turns])"," (Apply Burn [3 turns])"," (Guaranteed CRIT)",
						" (Attack that heals some HP & Mana)"," (Flurry of 3-5 attacks)"," (HP = 100%)"," (Apply Poison [3 turns])"," (Mana = 100%)",
						" (Restores 50% HP & Mana)"," (HP & Mana = 100% & Status Heal)",""};

string BuyUpName[] = {"","Sword Upgrade (ATK + 30%)","Arcana Burst (MA + 30%)","Better Constitution (MaxHP + 30%)","Armor Upgrade (AC + 5)",
						"Better Sleight of Hand (CRIT% + 5%)", "Lighter Boots (DODGE% + 3%)","FULL HEAL (HP, Mana & Status)"};

string SpellName[] = {"","Poison Cloud","Ignitus","Frigid Laceration",
					"Thunder Chain","Metaphisical Overload","Life Steal",
						"Self Heal","Statistical LightBeam","Vicious Mockery"};

string SpellDesc[] = {"",".          (Poisons Target [3-5 turns])                  : ",".               (Ultra damaging Fireball [50% Chance to burn]): ",
						".     (Better basic Attack that can freeze [1 turn]): ",".         (3-10 Lightning Shots [Ignores Defense])      : ",
						". (Low chance of INSTAKILL [or 70% of Boss HP]) : ",".            (Steals 20% of Enemy HP)                      : ",
						".             (Heals 25% HP + Extra based on MA)            : ",". (Deals 25% of total Stat count as damage)     : ",
						".       (Chance to Freeze Enemy [2-3 turns])          : "};

//Stats
int MAXHP = 20, HP = MAXHP, CRIT = 5, DODGE = 5, MAXMANA = 15, MANA = MAXMANA;
int eMAXHP = 8, eHP = eMAXHP, eCRIT = 0, eDODGE = 0, eMAXMANA = 5, eMANA = eMAXMANA;
double ATK = 6, MA = 5, AC = 2, DEF;
double eATK = 4, eMA = 2, eAC = 0, eDEF;

string eName[] = {"","Soldier","Slave","Gladiator","Barbarian","Knight","","","","","","","","","","","","","","","","Boss"};
string DeathMSG[] = {"","You suddenly feel Lightheaded","You can't feel your legs","Your Body is Numb","You feel a sharp weapon tearing your torso","It's... cold"};

void clear(){ system("CLS");}

void Intro(){}

void LevelUp(){ clear();
	cout << "You feel... Invincible!\n\n"; sleep(1); clear();
	cout << "LEVEL UP:"; sleep(1); cout << "\n\n MAXHP + 5"; usleep(350000); cout << "\t MAXMana + 5"; usleep(350000); cout << "\n\n ATK + 2"; usleep(350000); cout << "\n\n MA + 2"; usleep(350000);
	cout << "\n\n AC + 2"; usleep(350000); cout << "\n\n CRIT% + 2"; usleep(350000); cout << "\t DODGE% + 1"; sleep(1);

	MAXHP = MAXHP + 5; HP = HP + 5; MAXMANA = MAXMANA + 5; MANA = MAXMANA; ATK = ATK + 2; MA = MA + 2; AC = AC + 2; CRIT = CRIT + 1; DODGE = DODGE + 1;

						cout << "\n\n\nPRESS ENTER:";
						cin.ignore(); cin.get();
						clear();

}

void BasicAttack(double& x, double& y, int& c, int& d, int& b){

		usleep(700000);

	Damage = x - y;
		if (b > 0) {Damage = Damage / 2;}//Burn cut damage
		if (Damage <= 0) {Damage = 1;}
					
		Chance = rand() % 100 + 1;
		if (c >= Chance) {
			if (Action != 0){ Damage = Damage * Ares; }else {Damage = Damage * 2;}
			cout << "CRITICAL HIT\n\n"; sleep (1);};
						
			Chance = rand() % 100 + 1;
		if (d >= Chance) {
			Damage = 0;
			if (Action != 0){ cout << "You missed\n\n";}else {cout << "You dodged its attack!\n\n";}; usleep(500000);
		}else {	if (Action != 0){cout << "You dealt " << Damage << " damage!\n\n";}else {cout << "It deals " << Damage << " damage\n\n";};} usleep(500000);
	

}

void Defend(double& x, int& y, int& z){
	x = x * 2.5,	 y = y + (z/10);	if (y > MAXMANA){y = z;}	usleep(500000);
	}

void PlayerSpell(){}

void UseItem(){}

void PlayerDeath(){
	//Player Death
			   if (HP <= 0){
					HP = 0; Chance = rand() % 5 + 1;
				cout << P1 << ": " << HP << "/" << MAXHP << " HP" << endl << endl; sleep(2);
					 clear();
			      cout << P1 << ": " << HP << "/" << MAXHP << " HP" << endl << endl; sleep(2);
				  cout << DeathMSG[Chance] << "..." << endl << endl; sleep(2);
			      cout << "It seems... "; sleep(2); cout << "you have succumbed to the " << eName[E1] << "." << endl << endl; sleep(3);
				  cout << "What a truly "; sleep(1); cout << "foolish "; sleep(1); cout << "end..." << endl << endl; sleep(2);
				   cout << "GAME OVER" << endl << endl; sleep(2); cout << "You got through " << Round - 1 << " Rounds." << endl << endl;
			      return;
			   }
}
//ShopSystem
void ShopTime(){
				while (Shop > 0){

			cout << " _ EMIL's SHOP _ " << endl << endl << endl;
			cout << "(1) - " << UpgradeName[UpOpt1] << "\t(2) - " << UpgradeName[UpOpt2] << "\t(3) - " << UpgradeName[UpOpt3] << endl;

			if (PayOpt == 3) {cout << "\t\t\t\t\t\t\t\t" << "(4) - " << BuyUpName[PayUp] << ": " << Price << "g" << endl << endl;
			}else if (PayOpt == 2) {cout << "\t\t\t\t\t\t\t\t" << "(4) - Item -  " << ItemName[PayItem] << ItemDesc[PayItem] << ": " << Price << "g" << endl << endl;
			}else if (PayOpt == 1) {cout << "\t\t\t\t\t\t\t\t" << "(4) - Spell - " << SpellName[PaySpell] << ": " << Price << "g" << endl << endl;
			}else if (PayOpt == 0) {cout << "\t\t\t\t\t\t\t\t" << "(4) - " << "SOLD OUT -" << endl << endl;}
				
			cout << "Savings: " << Gold << "g\n" << P1 << ": ";
			cin >> ShopChoice;

			if (ShopChoice > 4){
						cout << endl << "Sorry,";sleep(1); cout << " we don't have that"; sleep(1); clear();
				}else if (ShopChoice < 1){
						cout << endl << "Sorry,";sleep(1); cout << " we don't have that"; sleep(1); clear();
				}else {Shop = 0;};//Shop end, put Shop = 0

				if (ShopChoice == 4){
					Shop = 1;
					if (Gold >= Price) {
						Gold = Gold - Price, Price = 999999;
						if (PayOpt == 3) {
								clear();
							if (PayUp == 1){cout << "Your Sword feels more powerfull.\n\n"; sleep(1); cout << "   ATK " << ATK << " -> ";
											ATK = ATK * 1.3; cout << ATK << endl << endl;}
							if (PayUp == 2){cout << "You feel the energy flowing through you.\n\n"; sleep(1); cout << "   MA " << MA << " -> ";
											MA = MA * 1.3; cout << MA << endl << endl;}
							if (PayUp == 3){cout << "You feel tougher than before.\n\n"; sleep(1); HP = MAXHP; cout << "   Max HP " << MAXHP << " -> ";
											MAXHP = MAXHP * 1.3; cout << MAXHP << endl << endl;}
							if (PayUp == 4){cout << "Your armor is..."; sleep(1); cout << " shinier.\n\n"; sleep(1); cout << "   AC " << AC << " -> ";
											AC = AC + 5; cout << AC << endl << endl;}
							if (PayUp == 5){cout << "Your hand movements feel Smoother.\n\n"; sleep(1); cout << "   CRIT% " << CRIT << " -> ";
											CRIT = CRIT + 5; cout << CRIT << endl << endl;}
							if (PayUp == 6){cout << "You feel faster than ever.\n\n"; sleep(1); cout << "   DODGE% " << DODGE << " -> ";
											DODGE = DODGE + 3; cout << DODGE << endl << endl;}
							if (PayUp == 7){  HP = MAXHP; MANA = MAXMANA; Freeze = 0; Burn = 0; Poison = 0;
					cout << "\nHealth,"; sleep(1); cout << " Mana"; sleep(1); cout << " & Status fully Restored.\n\n";}

						sleep (1); cout << endl << "PRESS ENTER:";
							cin.ignore(); cin.get();
						clear();}
						if (PayOpt == 2) {Consumable = PayItem;}									
						if (PayOpt == 1) {clear(); SpellSlots--;

								if (PaySpell == 1){Pcloud = 1;}
								if (PaySpell == 2){Igni = 1;}
								if (PaySpell == 3){FrigL = 1;}
								if (PaySpell == 4){Thund = 1;}
								if (PaySpell == 5){MPOver = 1;}
								if (PaySpell == 6){HPSteal = 1;}
								if (PaySpell == 7){HealS = 1;}
								if (PaySpell == 8){LightB = 1;}
								if (PaySpell == 9){VMock = 1;}

								 cout << endl << SpellName[PaySpell] << " was added to the Arcana Compendium\n\n"; sleep(2);
								cout << "\nPRESS ENTER:";
									cin.ignore(); cin.get();
								clear();}

					PayOpt = 0;
					}else if (PayOpt == 0) {cout << "\nIt's sold out"; sleep(1); cout << " bucko.\n"; sleep(1); clear();
					}else {cout << "\nNot enough gold"; sleep(1); cout << " mate.\n"; sleep(1); clear();}	
				}

				clear();

				if (ShopChoice == 1){cout << endl << "	";
					if (UpOpt1 == 1){cout << "Attack Upgraded" << endl << endl << endl; ATK = ATK + 3;}
					if (UpOpt1 == 2){cout << "Magic Upgraded" << endl << endl << endl; MA = MA + 3;}
					if (UpOpt1 == 3){cout << "Max HP Extended" << endl << endl << endl; MAXHP = MAXHP + 6, HP = HP + 6;}
					if (UpOpt1 == 4){cout << "Healed half Health (& restored some Mana)" << endl << endl << endl; HP = HP + (MAXHP/2), MANA = MANA + (MAXMANA/5);}
					if (UpOpt1 == 5){cout << "Armor Class Upgraded" << endl << endl << endl; AC = AC + 2;}
					if (UpOpt1 == 6){cout << "Critical Hit Enhanced" << endl << endl << endl; CRIT = CRIT + 2;}
					if (UpOpt1 == 7){cout << "Dodge Enhanced" << endl << endl << endl; DODGE = DODGE + 1;}
				}	
				if (ShopChoice == 2){cout << endl << "	";
					if (UpOpt2 == 1){cout << "Attack Upgraded" << endl << endl << endl; ATK = ATK + 3;}
					if (UpOpt2 == 2){cout << "Magic Upgraded" << endl << endl << endl; MA = MA + 3;}
					if (UpOpt2 == 3){cout << "Max HP Extended" << endl << endl << endl; MAXHP = MAXHP + 6, HP = HP + 6;}
					if (UpOpt2 == 4){cout << "Healed half Health (& restored some Mana)" << endl << endl << endl; HP = HP + (MAXHP/2), MANA = MANA + (MAXMANA/5);}
					if (UpOpt2 == 5){cout << "Armor Class Upgraded" << endl << endl << endl; AC = AC + 2;}
					if (UpOpt2 == 6){cout << "Critical Hit Enhanced" << endl << endl << endl; CRIT = CRIT + 2;}
					if (UpOpt2 == 7){cout << "Dodge Enhanced" << endl << endl << endl; DODGE = DODGE + 1;}
				}	
				if (ShopChoice == 3){cout << endl << "	";
					if (UpOpt3 == 1){cout << "Attack Upgraded" << endl << endl << endl; ATK = ATK + 3;}
					if (UpOpt3 == 2){cout << "Magic Upgraded" << endl << endl << endl; MA = MA + 3;}
					if (UpOpt3 == 3){cout << "Max HP Extended" << endl << endl << endl; MAXHP = MAXHP + 6, HP = HP + 6;}
					if (UpOpt3 == 4){cout << "Healed half Health (& restored some Mana)" << endl << endl << endl; HP = HP + (MAXHP/2), MANA = MANA + (MAXMANA/5);}
					if (UpOpt3 == 5){cout << "Armor Class Upgraded" << endl << endl << endl; AC = AC + 2;}
					if (UpOpt3 == 6){cout << "Critical Hit Enhanced" << endl << endl << endl; CRIT = CRIT + 2;}
					if (UpOpt3 == 7){cout << "Dodge Enhanced" << endl << endl << endl; DODGE = DODGE + 1;}
				}	


				
			}
}
//BattleSystem
void BattleStart(){
	while (BattleActive > 0) {
			   
				PlayerDeath();
				if (HP <= 0){ return;}
			   
				//Player Turn
				Damage = 0, DEF = (AC/2) * Athena, Turn = 1;


				if (Freeze == 0){
					while (Turn > 0){ 
			cout << P1 << ": " << HP << "/" << MAXHP << " HP\t" << MANA << "/" << MAXMANA << " Mana\t\t" << eName[E1] << ": " << eHP << "/" << eMAXHP << " HP\n\n\n";

			cout << "1 - Attack\t 2 - Spells\t 3 - "; if (Consumable == 0){cout << "None";}else {cout << ItemName[Consumable];}; cout << "\t 0 - Defend" << endl;

					cout << "Your turn: ";
					cin >> Action;

					if (Action > 4){
						cout << "\nInvalid move" << endl << endl; sleep(1); clear();
					}else if (Action < 0){
						cout << "\nInvalid move" << endl << endl; sleep(1); clear();
					}else if (Action == 3){
						if (Consumable == 0){cout << "\nNo Item available" << endl << endl; sleep(1); clear();} else {Turn = 0;}
					}else if (Action == 2){
						if (MANA == 0){cout << "\nNo Mana left" << endl << endl; sleep(1); clear();} else {Turn = 0;}}else {Turn = 0;}
					if (Action == 4){Turn = 1; clear();
					cout << "STATS:\t" << P1 << "\n\n    MAX HP = " << MAXHP << "\t\tMAX Mana = " << MAXMANA << "\nCurrent HP = " << HP << "\t    Current Mana = " << MANA;
					cout << "\n\n   ATK = " << ATK << "\n    MA = " << MA << "\n    AC = " << AC << "\n CRIT% = " << CRIT << "%\nDODGE% = " << DODGE << "%\n\n";
					cout << "Total Stat Count = " << ATK + MAXHP + MAXMANA + MA + AC + CRIT + DODGE << "\n\n";
					cout << "\tItem - "; if (Consumable == 0){cout << "None";}else {cout << ItemName[Consumable] << ItemDesc[Consumable];}

						 cout << "\n\nPRESS ENTER:";
						cin.ignore(); cin.get();
						clear();
					}

				}

				if (Action < 2) {cout << endl << P1 << " used " << ActionNames[Action] << endl << endl;}
               
               //Normal Attack
				if (Action == 1) { BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn); }

				//Consumable
				if (Action == 3){ clear();
				 if (Consumable < 14){cout << endl << P1 << " used " << ItemName[Consumable] << endl << endl;}
				 usleep(500000);

				 switch (Consumable) {

					case 1://Precise Needle
						usleep(500000);
						cout << "You aim it carefully..." << endl << endl;
						sleep(1);

						for (int l = 0; l < 3; l++){
							cout << ". ";
						usleep(500000);
						}

						Chance = rand() % 50 + 1;
						if (Chance == 33){ sleep (1);
							cout << endl << endl << "	PRECISE HIT" << endl << endl; eHP = 0;
						}else {cout << endl << endl << "It dealt 1 damage..." << endl << endl; Damage = 1;}

						sleep(1); break;
					
					case 2://Cursed Dice
						Chance = rand() % 20 + 1; usleep(500000);
						cout << "\tIt rolled " << Chance << "\n\n"; sleep(1);

						switch (Chance) {
							case 1:
								cout << eName[E1] << " is fully healed\n\n";
								eHP = eMAXHP; eMANA = eMAXMANA; eBurn = 0; ePoison = 0; eFreeze = 0;
								break;

							case 2:
								cout << "You lost 5g...\n\n";
								Gold = Gold - 5;
								if (Gold < 0){Gold = 0;}
								break;

							case 3:
								cout << "You're frozen, burned, and poisoned for 1 turn...\n\n";
								Burn = Burn + 1; Poison = Poison + 1; Freeze = Freeze + 1;
								break;

							case 4:
								cout << "You lost 1g...\n\n";
								Gold = Gold - 1;
								if (Gold < 0){Gold = 0;}
								break;

							case 5:
								cout << "nothing happens\n\n";
								break;

							case 6:
								cout << "You Defend\n\n"; usleep(500000);
								Defend(DEF,MANA,MAXMANA);
								break;

							case 7:
								cout << "You gained 5g!\n\n";
								Gold = Gold + 5;
								break;

							case 8:
								cout << "You attack\n\n"; usleep(500000);
								BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn);
								break;

							case 9:
								cout << "You got a random Item!\n\n";
								AllVar = 1;
								break;

							case 10:
								cout << eName[E1] << " is frozen, burned, and poisoned for 1 turn!\n\n";
								eBurn = eBurn + 1; ePoison = ePoison + 1; eFreeze = eFreeze + 1;
								break;

							case 11:
								cout << "You healed some Mana!\n\n";
								MANA = MANA + (MAXMANA / 2);
								if (MANA > MAXMANA){MANA = MAXMANA;}
								break;

							case 12:
								cout << "You gained 10g!\n\n";
								Gold = Gold + 10;
								break;

							case 13:
								cout << "You attack twice!\n\n"; usleep(500000); Damage = 0;
								for (int l = 0; l < 2; l++){eHP = eHP - Damage; BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn);}
								break;

							case 14:
								cout << "You healed some HP!\n\n";
								HP = HP + (MAXHP / 2);
								if (HP > MAXHP){HP = MAXHP;}
								break;

							case 15:
								cout << "You got a random Item and you attack!\n\n"; usleep(500000);
								BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn);
								AllVar = 1;
								break;

							case 16:
								cout << eName[E1] << " is frozen, burned, and poisoned for 2 turns!\n\n";
								eBurn = eBurn + 2; ePoison = ePoison + 2; eFreeze = eFreeze + 2;
								break;

							case 17:
								cout << "All enemy stats decreased by 1!!\n\n";
								eMAXHP = eMAXHP - 1; eHP = eHP - 1; eATK = eATK - 1; eAC = eAC - 1; eMA = eMA - 1; eCRIT = eCRIT - 1; eDODGE = eDODGE - 1;
								break;

							case 18:
								cout << "You gained 20g!!\n\n";
								Gold = Gold + 20;
								break;

							case 19:
								cout << "All stats increased by 1!!\n\n";
								MAXHP = MAXHP + 1; HP = HP + 1; ATK = ATK + 1; AC = AC + 1; MA = MA + 1; CRIT = CRIT + 1; DODGE = DODGE + 1;
								break;

							case 20:
								cout << "It instantly Kills the " << eName[E1] << "!!!\n\n";
								Damage = eMAXHP;
								break;
						}
					sleep(1); break;

					case 3://Status Potion
						Freeze = 0; Burn = 0; Poison = 0;
						cout << "\n\tStatus fully healed"; sleep (2); clear(); break;
					
					case 4://Ice Flask
						eFreeze = eFreeze + 2; sleep(1);
						cout << "You throw the flask at the " << eName[E1]; sleep(1); cout << "\n\nYou froze the " << eName[E1]; sleep(1); clear(); break;
					
					case 5://Burning Cinders
						eBurn = eBurn + 3; sleep(1);
						cout << "You toss the cinders around the " << eName[E1]; sleep(1); cout << "\n\nYou burned the " << eName[E1]; sleep(1); clear(); break;
					
					case 6://Blood Coating
						sleep(1);
						Damage = ATK - eDEF;
						if (Burn > 0) {Damage = Damage / 2;}//Burn cut damage
						if (Damage <= 0) {Damage = 1;}
					
						Damage = Damage * Ares;
						cout << "\tCRITICAL HIT\n\n"; sleep (1);
						
						cout << "You dealt " << Damage << " damage!\n\n"; sleep(1); break;
					
					case 7://Vitality Coating
						BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn);
						cout << "And you healed " << Damage << " HP + " << Damage / 3 << " Mana\n\n"; sleep(1);
						HP = HP + Damage; if (HP > MAXHP){HP = MAXHP;}
						MANA = MANA + (Damage / 3); if (MANA > MAXMANA){MANA = MAXMANA;} break;
					
					case 8://Energy Coating
						Damage = 0;
						
						for (int t = rand() % 3 + 3; t > 0; t--){
							eHP = eHP - Damage;
							BasicAttack(ATK,eDEF,CRIT,eDODGE,Burn);
						}
						sleep(1); break;
					
					case 9://Healing Potion
						sleep (1); cout << "\n\tHP fully healed" << endl << endl; HP = MAXHP; sleep (2); clear(); break;
					
					case 10://Poison Dart
						ePoison = ePoison + 3; sleep(1);
						cout << "You fling the dart at the " << eName[E1]; sleep(1); cout << "\n\nYou poisoned the " << eName[E1]; sleep(1); clear(); break;
					
					case 11://Mana Flask
						sleep (1); cout << "\n\tMana fully restored" << endl << endl; MANA = MAXMANA; sleep (2); clear(); break;
					
					case 12://Violet Flask

						cout << "Healed half Health and restored half Mana\n\n"; sleep(1);

						HP = HP + (MAXHP / 2); MANA = MANA + (MAXMANA / 2);
						if (HP > MAXHP){HP = MAXHP;}	if (MANA > MAXMANA){MANA = MAXMANA;} break;
					
					case 13://Ultimate Flask
						HP = MAXHP; MANA = MAXMANA; Freeze = 0; Burn = 0; Poison = 0;
						sleep (1); cout << "Health,"; sleep(1); cout << " Mana"; sleep(1); cout << " & Status fully Restored.\n\n"; sleep (2); clear(); break;

					case 14://Armageddon
						cout << "The clouds turn dark,"; sleep(2); cout << " and swirl around the colosseum"; sleep(2); cout << " violently.\n\n\t"; sleep(2);
						cout << P1; sleep(1); cout << " USED"; sleep(1); cout << " AR"; usleep(500000); cout << "MA"; usleep(500000); cout << "GE"; usleep(500000); cout << "DDON"; sleep(1); clear(); cout << "\n\t";
						for (int l = 0; l < 3; l++) {cout << ". "; usleep(500000);} sleep(1); clear(); Damage = 9999;
						for (int l = 0; l < 100000; l++){cout << "#   #   #   #   #   "; usleep(999);} clear(); sleep(2);
						cout << "\n\t IT DEALS "; for (int l = 0; l < 4; l++){usleep(500000); cout << 9;} usleep(500000); cout << " DAMAGE!\n\n"; sleep (2); clear(); break;
					
				 }
				if (AllVar == 1) {Consumable = rand() % 14 + 1; AllVar = 0;}else {Consumable = 0;}
			}

				//Spell Attack
				if (Action == 2){ Turn = 1;

				 while (Turn > 0) {
					clear();
					cout << "SPELLS:" << endl << endl << P1 << ": " << HP << "/" << MAXHP << " HP    " << MANA << "/" << MAXMANA << " Mana" << endl << endl;
					if (Pcloud == 1){cout << "1 - " << SpellName[1] << SpellDesc[1] << 10 - Tarot << " Mana" << endl;}
					if (Igni == 1){cout << "2 - " << SpellName[2] << SpellDesc[2] << 9 - Tarot << " Mana" << endl;}
					if (FrigL == 1){cout << "3 - " << SpellName[3] << SpellDesc[3] << 3 - Tarot << " Mana" << endl;}
					if (Thund == 1){cout << "4 - " << SpellName[4] << SpellDesc[4] << 6 - Tarot << " Mana" << endl;}
					if (MPOver == 1){cout << "5 - " << SpellName[5] << SpellDesc[5] << 4 - Tarot << " Mana" << endl;}
					if (HPSteal == 1){cout << "6 - " << SpellName[6] << SpellDesc[6] << 8 - Tarot << " Mana" << endl;}
					if (HealS == 1){cout << "7 - " << SpellName[7] << SpellDesc[7] << 2 - Tarot << " Mana" << endl;}
					if (LightB == 1){cout << "8 - " << SpellName[8] << SpellDesc[8] << 7 - Tarot << " Mana" << endl;}
					if (VMock == 1){cout << "9 - " << SpellName[9] << SpellDesc[9] << 3 - Tarot << " Mana" << endl;}

					cout << endl << "Choose: ";
					cin >> Action;

					switch (Action){
				 //Poison Cloud
				case 1:	MPrice = 10 - Tarot; if (Pcloud == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

					MANA = MANA - MPrice; sleep(1); clear();

				Chance = rand() % 10 + 1;
				if (MA >= Chance){ Chance = rand() % 50 + 1; 
				if (MA >= Chance){cout << eName[E1] << " is CRITICALLY Poisoned!" << endl << endl; ePoison = ePoison + 5;
				}else {cout << eName[E1] << " is Poisoned!" << endl << endl; ePoison = ePoison + 4;}
				}else{cout << eName[E1] <<" is lightly Poisoned." << endl << endl; ePoison = ePoison + 3;}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;
				 
				 //Ignitus
				case 2: MPrice = 9 - Tarot; if (Igni == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

					MANA = MANA - MPrice; sleep(1); clear();

					cout << "A gigantic Fireball swirls out of your sword" << endl << endl;
					Damage = (MA*3) - eDEF; if (Damage <= 0){Damage = 0;}; sleep (1);

					Chance = rand() % 100 + 1;
					if (CRIT >= Chance) {
						Damage = Damage * Ares;
						cout << "CRITICAL HIT" << endl << endl; sleep (1);}
						
						Chance = rand() % 100 + 1;
					if (eDODGE >= Chance) {
						Damage = 0;
						cout << "It missed" << endl << endl;
					}else {cout << "It dealt " << Damage << " damage!" << endl << endl; 
					
					Chance = rand() % 2 + 1; if (Chance == 1) {eBurn = eBurn + 2; cout << eName[E1] << " is burning!" << endl << endl;};};

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Frigid Laceration
				case 3: MPrice = 3 - Tarot; if (FrigL == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

					MANA = MANA - MPrice; sleep(1); clear();

					cout << "Your Sword gets Frozen, you slash at the " << eName[E1] << endl << endl;
					Damage = (ATK + (MA/3)) - eDEF; if (Damage <= 0){Damage = 1;}; sleep (1);

					Chance = rand() % 100 + 1;
					if (CRIT >= Chance) {
						Damage = Damage * Ares;
						cout << "CRITICAL HIT" << endl << endl; sleep (1);}
						
						Chance = rand() % 100 + 1;
					if (eDODGE >= Chance) {
						Damage = 0;
						cout << "It missed" << endl << endl;
					}else {cout << "It dealt " << Damage << " damage!" << endl << endl;

					Chance = rand() % 20 + 1;
					if (MA >= Chance){cout << eName[E1] << " is Frozen!" << endl << endl; eFreeze = eFreeze + 1;}}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Thunder Chain
				case 4: MPrice = 6 - Tarot; if (Thund == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

					MANA = MANA - MPrice; sleep(1); clear(); Damage = 0;

					cout << "You're ready for some Shocking moves\n\n"; sleep(1);

				for (int t = rand() % 8 + 3; t > 0; t--){

					eHP = eHP - Damage;
					Damage = (MA/4); if (Damage <= 0){Damage = 1;}; usleep (250000);

					Chance = rand() % 100 + 1;
					if (CRIT >= Chance) {
						Damage = Damage * Ares;
						cout << "CRITICAL SHOCK" << endl << endl; usleep (800000);}
						
						Chance = rand() % 100 + 1;
					if (eDODGE >= Chance) {
						Damage = 0;
						cout << "It missed" << endl << endl; usleep (400000);
					}else {cout << "It dealt " << Damage << " damage!" << endl << endl;  usleep (400000);}
				}


				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";};break;

				 //Metaphisical Overload
				case 5: MPrice = 4 - Tarot; if (MPOver == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

					MANA = MANA - MPrice; sleep(1); clear();

					cout << "You try to invade its mind..." << endl << endl; sleep(1);

					Chance = rand() % 1000 + 1;
					if (Chance <= (50 + (MA*2))){cout << "Its brain crumples,"; sleep(1); cout << " until it blows out of its head\n\n"; sleep(2);
						if (BossRound == 1){Damage = eMAXHP * 0.7; cout << "It deals " << Damage << " damage!\n\n";
						}else{Damage = eMAXHP; cout << "It looks..."; sleep(2); cout << " dead.\n\n";}
					}else{cout << "But it failed\n\n";}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Life Steal
				case 6: MPrice = 8 - Tarot; if (HPSteal == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

				MANA = MANA - MPrice; sleep(1); clear();

					cout << "Your Teeth enlighten\n"; sleep(1); cout << "You sprint towards the " << eName[E1] << " to bite it" << endl << endl;

					Chance = rand() % 80;
					if (MA >= Chance) { Damage = (eMAXHP * 0.33); if (Damage < 5){Damage = 5;}; cout << "CRITICALY absorved " << Damage << " HP!\n\n";
					}else { Damage = (eMAXHP * 0.20); if (Damage < 3){Damage = 3;}; cout << "Absorved " << Damage << " HP\n\n";} sleep (1);
							eHP = eHP - Damage; 	HP = HP + Damage;	if (HP > MAXHP){HP = MAXHP;}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Self Heal
				case 7: MPrice = 2 - Tarot; if (HealS == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

				MANA = MANA - MPrice; sleep(1); clear();

				Heal = (MAXHP/4) + (MA/2);
				HP = HP + Heal;

				cout << "You healed " << Heal << " HP." << endl << endl;
				if (HP > MAXHP){ HP = MAXHP;}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Statistical Lightbeam
				case 8: MPrice = 7 - Tarot; if (LightB == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

				MANA = MANA - MPrice; sleep(1); clear();

					cout << "A violent Godray falls upon the " << eName[E1] << endl << endl;
					Damage = (ATK + MA + CRIT + DODGE + AC + MAXHP + MAXMANA)/4 - eDEF; if (Damage <= 0){Damage = 1;}; sleep (1);

					for (int t = 10; t > 0; t--){
						cout << endl << "	     ||";	//cout << endl << "	     |⣿⣿|";
						usleep(20000);
					}cout << endl << "     ._..:'''  ''':.._." << endl << endl;	//cout << endl << "	⣄_⣀⣴⣿⣿⣿⣿⣿⣿⣦⣀_⣠" << endl << endl;

					Chance = rand() % 100 + 1;
					if (CRIT >= Chance) {
						Damage = Damage * Ares;
						cout << "CRITICAL HIT" << endl << endl; sleep (1);}
						
						Chance = rand() % 100 + 1;
					if (eDODGE >= Chance) {
						Damage = 0;
						cout << "It missed" << endl << endl;
					}else {cout << "It dealt " << Damage << " damage!" << endl << endl;}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;

				 //Vicious Mockery
				case 9: MPrice = 3 - Tarot; if (VMock == 1){ if (MANA >= MPrice) {cout << endl << P1 << " used " << SpellName[Action] << endl << endl;Turn = 0;

				MANA = MANA - MPrice; sleep(1); clear();

				Chance = rand() % 25 + 1;
				if (MA >= Chance){ Chance = rand() % 80 + 1; 
				if (MA >= Chance){cout << eName[E1] << " is CRITICALLY Frozen from embarassment!" << endl << endl; eFreeze = eFreeze + 3;
				}else {cout << eName[E1] << " is Frozen from embarassment!" << endl << endl; eFreeze = eFreeze + 2;}
				}else{cout << "But it failed to provoke." << endl << endl;}

				}else{cout << "\nNot enough Mana\n\n";}; }else{cout << "\nInvalid move\n\n";} break;
				
				default: cout << "\nInvalid move\n\n"; break;

				  }sleep(1);
				 }
				}

				//Defend
				if (Action == 0) {Defend(DEF,MANA,MAXMANA);}

					eHP = eHP - Damage;

				}else {sleep(1); cout << "You're Frozen in place" << endl << endl; sleep(1); Freeze--;}

				//Enemy Poison and Burn
					 if (ePoison > 0){Damage = eMAXHP*0.05; if(Damage < 3){Damage = 3;} ePoison--;
					cout << eName[E1] << " is hurt by poison! (" << Damage << " damage)" << endl << endl; sleep(1); eHP = eHP - Damage;}
					 if (eBurn > 0){Damage = 3; eBurn--;
					cout << eName[E1] << " is burned! (" << Damage << " damage)" << endl << endl; sleep(1); eHP = eHP - Damage;}

				//Enemy Death
				if (eHP <= 0) {
					eHP = 0;
					cout << eName[E1] << " has been slayed." << endl << endl;
					BattleActive--;

				} else if (BattleActive > 0) {
				   

				//Enemy Turn
					Action = 0, Damage = 0, eDEF = (eAC/2);
					cout << P1 << ": " << HP << "/" << MAXHP << " HP" << "      " << eName[E1] << ": " << eHP << "/" << eMAXHP << " HP" << endl << endl;

				if (eFreeze == 0){

					cout << eName[E1] << " used " << ActionNames[eAction] << endl << endl;
					
               //Normal Attack
					if (eAction == 1) {BasicAttack(eATK,DEF,eCRIT,DODGE,eBurn);}

					//Defend
				if (eAction == 0) {Defend(eDEF,eMANA,eMAXMANA);}

					 	HP = HP - Damage;

				}else {sleep(1); cout << eName[E1] << " is Frozen" << endl << endl; sleep(1); eFreeze--;}

				//Player Poison and Burn
					 if (Poison > 0){Damage = MAXHP*0.05; if(Damage < 3){Damage = 3;} Poison--;
					cout << P1 << " is hurt by poison (" << Damage << " damage)" << endl << endl; sleep(1); HP = HP - Damage;}
					 if (Burn > 0){Damage = 3; Burn--;
					cout << P1 << " is burned (" << Damage << " damage)" << endl << endl; sleep(1); HP = HP - Damage;}

				}

			}//End of Battle
}


int main() {clear();
	srand(time(0));

	cout << "So,"; sleep(1); cout << " what's your Name?\n\nYou: ";
	getline(cin,P1);	clear();


	for(int wave = 0; wave < 1000; wave ++) {

		for(int battle = 0; battle < 5; battle++) {
		   
		   Round++;		BattleActive = 1;	E1 = rand() % 5 + 1;
		 DEF = (AC/2) * Athena; eDEF = (eAC/2), Damage = 0;
		 eHP = eMAXHP; ePoison = 0; eBurn = 0; eFreeze = 0;
		 cout << "ROUND: " << Round << endl << endl;

         //Battle Start
			BattleStart();
			if (HP <= 0){ sleep(4); return 0;}

		//End of Battle

			GainGold = 3 + (eMAXHP/20) + (Gold/10);	Gold = Gold + GainGold;	
			GainMANA = MAXMANA / 5; MANA = MANA + GainMANA; if (MANA >= MAXMANA){ MANA = MAXMANA;}


			if (Temp1 > 0){eMAXHP = eMAXHP + 1; eHP = eMAXHP; eAC = eAC + 0.1; eATK = eATK + 0.2; Temp1--;

									} else	{eMAXHP = eMAXHP * 1.5; eHP = eMAXHP; eAC = eAC + 1; eATK = eATK + 1.5;}//ENEMY STAT UPGRADE
			
			cout << "You won the fight\nYou obtained " << GainGold << " g.\nAnd Recovered " << GainMANA << " Mana" << endl << endl;

		//Shop and Price deciding
			Shop = 1;
			UpOpt1 = rand() % 7 + 1, UpOpt2 = rand() % 7 + 1, UpOpt3 = rand() % 7 + 1;
			PayOpt = rand() % 3 + 1,  PayUp = rand() % 7 + 1, PayItem = rand() % 14 + 1;
							//3 + 1
				if (PayOpt == 1){ if (SpellSlots == 0){ PayOpt = 3; } }

				if (PayOpt == 1){Turn = 1;

					while(Turn > 0){Turn = 0;

						 PaySpell = rand() % 9 + 1;

						if (PaySpell == 1){ if (Pcloud == 1){Turn++;}}
						if (PaySpell == 2){ if (Igni == 1){Turn++;}}
						if (PaySpell == 3){ if (FrigL == 1){Turn++;}}
						if (PaySpell == 4){ if (Thund == 1){Turn++;}}
						if (PaySpell == 5){ if (MPOver == 1){Turn++;}}
						if (PaySpell == 6){ if (HPSteal == 1){Turn++;}}
						if (PaySpell == 7){ if (HealS == 1){Turn++;}}
						if (PaySpell == 8){ if (LightB == 1){Turn++;}}
						if (PaySpell == 9){ if (VMock == 1){Turn++;}}
					}
				}

				if (PayOpt == 3) {Price = 10;
			}else if (PayOpt == 1) {Price = 20;
			}else if (PayOpt == 2) {
					if (PayItem < 13) {Price = 5;}
					if (PayItem > 7) {Price = 10;}
					if (PayItem == 1) {Price = 1;}
					if (PayItem == 10) {Price = 5;}
					if (PayItem == 13) {Price = 20;}
					if (PayItem == 14) {Price = 100;}
				}

			cout << "PRESS ENTER:";
			cin.ignore(); cin.get();
			clear();

		//Shop
			ShopTime();

		  if(HP > MAXHP){HP = MAXHP;}	if(MANA > MAXMANA){MANA = MAXMANA;}
			sleep (1); cout << "Ready to fight?\n\nPRESS ENTER:"; cin.ignore(); cin.get();
						clear();
 	}

		cout << "\n\t BOSS INCOMING\n\n";
		cout << "PRESS ENTER:";
			cin.ignore(); //cin.get();
						clear();

						Round++; BossRound = 1;		BattleActive = 1;	E1 = 21;	cout << "BOSS ROUND: \n\n";
		 		DEF = (AC/2) * Athena; eDEF = (eAC/2), Damage = 0;
		 		eHP = eMAXHP; ePoison = 0; eBurn = 0; eFreeze = 0;
		 		
					eMAXHP = eMAXHP / 1.1; eHP = eMAXHP; eAC = eAC - 0.4; eATK = eATK - 0.6;
						eMAXHP = eMAXHP * 1.5; eHP = eMAXHP; eAC = eAC * 1.5; eATK = eATK * 1.4;//BOSS STAT UPGRADE

				BattleStart();		if (HP <= 0){ sleep(4); return 0;}

				cout << eName[E1] << ": " << 0 << "/" << eMAXHP << " HP\n\n"; sleep(1);
				cout << eName[E1] << " has been slain!\n\n";
				LevelUp();
				
					eMAXHP = eMAXHP / 1.5; eHP = eMAXHP; eAC = eAC / 1.5; eATK = eATK / 1.4;	BossRound = 0;
						eMAXHP = eMAXHP * 1.2; eHP = eMAXHP; eAC = eAC + 0.5; eATK = eATK + 0.8;//ENEMY STAT UPGRADE

 }

	return 0;
}