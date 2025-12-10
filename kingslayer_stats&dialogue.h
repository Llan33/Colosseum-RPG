#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "mmsystem.h"

#pragma comment(lib, "Winmm.lib" );
#include "kingslayer_animations&globals.h"

using namespace std;

//- Classes and ID's - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

enum ItemID{
    NONE = 0,
    HealPotion = 1,
    MpFlask = 2,
    StusPotion = 3,
    VFlask = 4,
    UltFlask = 5,
    BloodCoat = 6,
    VitalCoat = 7,
    FlurryCoat = 8,
    StanceCoat = 9,
    DeadlyCoat = 10,
    BurnCinder = 11,
    FlintnSteel = 12,
    PsnDart = 13,
    PsnDagger = 14,
    IceFlsk = 15,
    ChillOrb = 16,
    DeadJar = 17,
    LightinJar = 18,
    ExplosJar = 19,
    NiceeeJar = 20,
    CurseDice = 21,
    WeirDice = 22,
    CoinBag = 23,
    VoodooDo = 24,
    PrecNeedle = 25,
    Armagedon = 26,
    Tonic = 27,
};
enum SpellID{
    NOSPELL = 0,
    SHeal = 1,
    DuoSlsh = 2,
    CrossSlsh = 3,
    MBlast = 4,
    ArcBlast = 5,
    TempnRageCut = 6,
    KnghtStance = 7,
    RoylkKnghtStance = 8,
    GrtHeal = 9,
    BloodBind = 10,// Real Shop Spells Start Here
    WillWisp = 11,
    Ignits = 12,
    PsnCloud = 13,
    Infestat = 14,
    VMock = 15,
    FrigLaceration = 16,
    ThundChain = 17,
    PolarShock = 18,
    StatBeam = 19,
    MetaOverload = 20,
    ChromWave = 21,
    Omnislsh = 22,
    WarBlast = 23,
    VengCut = 24,
    BlckKnghtStance = 25,
    SupremHeal = 26
};
enum RelicID{
    NORELIC = 0,
    CarbonSwrd = 1,
    ArcRing = 2,
    TarotNeckl = 3,
    WarlckStone = 4,
    CuteBag = 5,
    CorruptSigl = 6,
    LuckyChrm = 7,
    CatStatu = 8,
    UnderSkull = 9,
    CheatM = 10,
    InsightLen = 11,
    CeramPot = 12,
    EatHeart = 13,
    EggP = 14,
    MagicaCarnati = 15,
};
enum UpgradeID{
    NOUP = 0,
    CONSTITUTION = 1,
    SHARPENING = 2,
    ARCBURST = 3,
    ARMORUP = 4,
    SLEIGHTOFHAND = 5,
    LIGHTBOOTS = 6,
    FULLHEAL = 7,
    TEMPERBAD = 8,
    LUCKYCLOVER = 9,
    ETHEREAL = 10,
    STOKEN = 11
};

class Item {
    public:

    ItemID ID = NONE;
    string Name;
    string Desc;
    int Price;
    int CC; //Color Chars

    Item (ItemID id, string name, string desc, int price, int cc){
        ID = id;
        Name = name;
        Desc = desc;
        Price = price;
        CC = cc;
    }
    Item() = default;
};

class Spell {
    public:

    SpellID ID = NOSPELL;
    string Name;
    string Desc;
    int ManaCost;
    int Price;
    int CC; //Color Chars

    Spell (SpellID id, string name, string desc, int mcost, int price, int cc){
        ID = id;
        Name = name;
        Desc = desc;
        ManaCost = mcost;
        Price = price;
        CC = cc;
    }
    Spell() = default;
};

class Relic{
    public:

    RelicID ID;
    string Name;
    string Desc;

    struct Obtained{
        bool P1 = false;
        bool P2 = false;
    }Obtained;


    string Lines[5];


    Relic(RelicID id, string name, string desc, string line1, string line2, string line3, string line4, string line5){
        ID = id;
        Name = name;
        Desc = desc;
        Lines[0] = line1;
        Lines[1] = line2;
        Lines[2] = line3;
        Lines[3] = line4;
        Lines[4] = line5;
    }
    Relic() = default;
};

class Upgrade{
    public:

    UpgradeID ID;
    string Name;
    string Desc;
    int Price;
    int CC; //Color Chars

    Upgrade(UpgradeID id, string name, string desc, int price, int cc){
        ID = id;
        Name = name;
        Desc = desc;
        Price = price;
        CC = cc;
    }
    Upgrade() = default;
};

//- Pre-Declared Objects - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||
    
    Item NoItem(NONE, "", "", 0, 0);
    Spell NoSpell(NOSPELL, "", "", 0, 0, 0);
    Upgrade NoUpgrade(NOUP, "", "", 0, 0);
    Relic NoRelic(NORELIC, "", "", "","","","","");
    
    Spell SplHealSmall(SHeal, "\033[1;96mSmall \033[92mHeal\033[0m", "(Heals a small amount of HP [About 15%])", 2, 0, 16);// 1
    Item ItmVioletTonic(Tonic,          "\033[1;95mViolet Tonic\033[0m", "(Become \033[1;95mOmnipotent\033[0m)",0,21);

//- The Entity Class - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

enum Classes{// Player Game Classes
    NOCLASS,
    Gladiator,
    Wanderer,
    Berserker,
    BlackKnight,
    Thief,
    God
};
enum EntityType{
    PLAYER1,
    PLAYER2,
    ENEMY,
    FALLEN,
    BOSS,
    WITCH,
    CHAMPION,
    KING
};
class Entity {
    public:
        
    string Name = "ERROR";
        
    struct Miscelaneous {
        Classes Class = NOCLASS;
        string Color = "";
        uint16_t Level = 1;
        int Spellslots = 1;
        int Tokens = 3;
        uint16_t Itemslots = 3;
        uint32_t XPThreshold = 100;
        int NameLenght;
        EntityType Type;
        int Revive = 0;
        bool AllStatusImmunity = false;
    }Misc;
        
    struct Stats {
        int MAXHP, HP;
        int MAXMANA, MANA;
        float ATK;
        float MA;
        float DEF, Block = DEF;
        float CRIT;
        float CRITMULT = 2;
        float DODGE;
        int Gold;
        int XP = 0;
        int HPRegen = 0;
        int Kindness = 0;
    }Stat;

    struct Multipliers {
    float XPMult = 1;
    float GoldMult = 1;
    float ManaMult = 0.10;
    float PriceMult = 1;
    float DefMult = 2;
    float ATKMult = 1;
    float MAGICMult = 1;
    float ACMult = 1;
    }Multiplier;
        
    struct Status{
        int16_t Burn = 0;
        int16_t Poison = 0;
        int16_t Freeze = 0;
        int16_t Shock = 0;
    }Status;
        
    struct ItemBag{
        Item Item1;
        Item Item2;
        Item Item3;
        Item Item4;
        Item Item5;
    }ItemBag;
        
    struct SpellBag{
        Spell DefaultSpell = SplHealSmall;
        Spell SigSpell;
        Spell Spell1;
        Spell Spell2;
        Spell Spell3;
        Spell Spell4;
        Spell Spell5;
        Spell Spell6;
    }SpellBag;
        
    Entity (int maxhp, int maxmana, float atk, float ma, float def, float crit, float dodge, int gold, EntityType type, string name){
        Stat.MAXHP = maxhp;
        Stat.HP = maxhp;
        Stat.MAXMANA = maxmana;
        Stat.MANA = maxmana;
        Stat.ATK = atk;
        Stat.MA = ma;
        Stat.DEF = def;
        Stat.Block = def;
        Stat.CRIT = crit;
        Stat.DODGE = dodge;
        Stat.Gold = gold;
        Misc.Type = type;
        Name = name;
        Misc.NameLenght = size (name);
    }
    Entity() = default;
};





//-----------DIALOG--------------------------------------------------------------------------------------------------------------------------------------------------------------||

enum Portrait {
    Nochar,
    Hero,
    Hero_halfChamp,
    Hero_Champ,
    Dawg,
    Dawg_dead,
    Witch,
    Witch_down,
    Witch_fierce,
    Witch_broken,
    Sogro_prison,
    Prisoner,
    Prisoner_Free,
    Fallen,
    Addison,
    Addison_dead,
    Addison_power,
    Aiden,
    Aiden_dead,
    Aiden_power,
    Nora,
    Champion,
    Starwalker,
};
class DialogueC {//Dialogue Character
    public:
    
    Portrait character;
    string Name;
    string Ncolor;
    string PortraitLine[16];
};
DialogueC CharacterL, CharacterR;

// - -Dialogue Portraits- (They are x40 * 16y) & Etc.- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||

void PlayerPortraits(Entity& Player, DialogueC& Cside){

    Cside.Name = Player.Name;

    switch (Player.Misc.Class){
        case NOCLASS:
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "                                        ";
        Cside.PortraitLine[5] = "                                        ";
        Cside.PortraitLine[6] = "                                        ";
        Cside.PortraitLine[7] = "                                        ";
        Cside.PortraitLine[8] = "                                        ";
        Cside.PortraitLine[9] = "                                        ";
       Cside.PortraitLine[10] = "                                        ";
       Cside.PortraitLine[11] = "                                        ";
       Cside.PortraitLine[12] = "                                        ";
       Cside.PortraitLine[13] = "                                        ";
       Cside.PortraitLine[14] = "                                        ";
       Cside.PortraitLine[15] = "                                        ";
        break;

        case Gladiator:
        Cside.PortraitLine[0] = "\033[1;91m                  _.'||                 \033[37m";
        Cside.PortraitLine[1] = "\033[1;91m               .-'   ||                 \033[37m";
        Cside.PortraitLine[2] = "\033[1;91m              |\033[1;93m_.----\033[1;91m||\033[1;93m.                \033[37m";
        Cside.PortraitLine[3] = "\033[1;93m              /\033[37m .: \033[1;93m     \\               \033[37m";
        Cside.PortraitLine[4] = "\033[1;93m             | \033[37m.:  \033[1;93m      |              \033[37m";
        Cside.PortraitLine[5] = "\033[1;93m             | \033[37m:   \033[1;93m  .-':'-._           \033[37m";
        Cside.PortraitLine[6] = "\033[1;93m            .'    ..'\033[1;93m  | \033[1;93m'.  '.         \033[37m";
        Cside.PortraitLine[7] = "\033[1;93m        .-''-.__.' \033[37m- - \033[1;93m|\033[37m-\033[1;93m |\033[1;93m_..'     \033[37m    ";
        Cside.PortraitLine[8] = "\033[1;93m         ''-.'    \033[37m - - \033[1;93m|\033[37m- \033[1;93m|             \033[37m";
        Cside.PortraitLine[9] = "\033[1;90m        __\033[1;93m   ''.       \033[1;93m| \033[1;93m |            \033[37m ";
       Cside.PortraitLine[10] = "\033[1;90m       /  \\\033[37m    |\033[1;93m'.    |  :              \033[37m";
       Cside.PortraitLine[11] = "\033[1;90m      |\033[37m : \033[1;90m \\\033[37m.-' \033[1;93m '-__|_-'\033[37m_\033[1;93m...\033[37m_          ";
       Cside.PortraitLine[12] = "\033[1;90m     | \033[37m.: \033[1;90m  |\033[1;93m':.          : :\033[37m  '.       ";
       Cside.PortraitLine[13] = "\033[1;90m     | \033[37m.: \033[1;90m  |\033[1;93m   '--..___.' .'\033[37m    |      ";
       Cside.PortraitLine[14] = "\033[1;90m    |  \033[37m:  \033[1;90m  |\033[1;93m.---....____ '. \033[37m'    \\     ";
       Cside.PortraitLine[15] = "\033[1;90m    |  \033[37m:\033[1;90m   | \033[1;93m            :  '\033[37m|     \\    ";
        break;

        case Wanderer:
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "\033[1;34m                     .                  \033[37m";
        Cside.PortraitLine[3] = "\033[1;34m                  .-' '-.               \033[37m";
        Cside.PortraitLine[4] = "\033[1;34m     ___......--''       '-.            \033[37m";
        Cside.PortraitLine[5] = "\033[1;34m    '::                     ''--..__    \033[37m";
        Cside.PortraitLine[6] = "\033[1;34m       '''---....                 ..::. \033[37m";
        Cside.PortraitLine[7] = "            |\033[1;94m    ''':---...----'''      \033[37m";
        Cside.PortraitLine[8] = "            |     |       ||            ";
        Cside.PortraitLine[9] = "            |     |       ||            ";
       Cside.PortraitLine[10] = "            |     |      | |            ";
       Cside.PortraitLine[11] = "            |     |----''  |            ";
       Cside.PortraitLine[12] = "         \033[1;34m  .----.\033[37m_|  \\_____|\033[1;34m-.          \033[37m";
       Cside.PortraitLine[13] = "\033[1;34m         .'       \\_\033[1;96m/\\\033[1;34m_/      '      \033[37m   ";
       Cside.PortraitLine[14] = "\033[1;34m        :          :\033[1;96m\\/\033[1;34m:.       :        \033[37m";
       Cside.PortraitLine[15] = "\033[1;34m      .'         .'    :       :       \033[37m ";
        break;

        case Berserker:
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "            \033[1;90m    __________            \033[37m  ";
        Cside.PortraitLine[2] = "         \033[1;90m      /          \\          \033[37m   ";
        Cside.PortraitLine[3] = "     \033[1;90m         /  /'-_______|          \033[37m  ";
        Cside.PortraitLine[4] = "  \033[1;90m           |  /        \033[37m |             ";
        Cside.PortraitLine[5] = "\033[1;90m             | |   \033[37m       |             ";
        Cside.PortraitLine[6] = " \033[1;90m            | |\033[1;91m'-. \033[1;90m __\033[37m_\\\033[1;90m_\033[37m|             ";
        Cside.PortraitLine[7] = "\033[1;90m             |_/\033[1;91m'-. \033[1;90m|     \\         \033[37m    ";
        Cside.PortraitLine[8] = "\033[1;90m               /\\__/       |        \033[37m    ";
        Cside.PortraitLine[9] = "\033[1;90m               \\___        |\033[1;91m--..__      \033[37m";
       Cside.PortraitLine[10] = "           __..'   :\033[1;90m\\______|\033[1;91m.     ''-_  \033[37m";
       Cside.PortraitLine[11] = "       _-''   .-  '      '\033[1;91m_.'  _.---.._\\\033[37m";
       Cside.PortraitLine[12] = "      ' :'   '      '.'\033[1;91m_-' _.''   \033[37m \\    ";
       Cside.PortraitLine[13] = "     |  .'   .    \033[1;91m  _-'  .'   \033[37m |    |   ";
       Cside.PortraitLine[14] = "     |       .'\033[1;91m _.-'   .'     \033[37m |    |   ";
       Cside.PortraitLine[15] = "    |    .   |\033[1;91m-'     .'     * \033[37m /    |   ";
        break;

        case BlackKnight:
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "\033[1;90m                     .   .              ";
        Cside.PortraitLine[2] = "\033[1;90m             ____---' |  |'.            ";
        Cside.PortraitLine[3] = "\033[1;90m            |         |''| |            ";
        Cside.PortraitLine[4] = "\033[1;90m            |         |  | |            ";
        Cside.PortraitLine[5] = "\033[1;90m             \\        |  | |            ";
        Cside.PortraitLine[6] = "\033[1;90m              \\____/''-\\/-'|            ";
        Cside.PortraitLine[7] = "\033[1;37m          ___  \033[1;90m|  \\'._    .|            ";
        Cside.PortraitLine[8] = "\033[1;37m    _.-'''_..\\\033[1;90m |   \\_ |  | |\033[1;37m'''-._      ";
        Cside.PortraitLine[9] = "\033[1;37m  .'--''''    |\033[1;90m|_    ||  |||\033[1;37m.'''--''-.  ";
       Cside.PortraitLine[10] = " \033[1;37m '''''''''''' \033[1;91m '':'--'.-''':\033[1;37m'-------'  ";
       Cside.PortraitLine[11] = "\033[1;91m       /        /'--'''''--._    |      ";
       Cside.PortraitLine[12] = "\033[1;91m      |        /\033[1;90m'.\033[1;90m     |  \033[1;90m:''\033[1;91m|   |      ";
       Cside.PortraitLine[13] = "\033[1;91m      |       /\033[1;90m.' \033[1;90m  ___|__\033[1;90m '.\033[1;91m|    |     ";
       Cside.PortraitLine[14] = "\033[1;91m     |       |\033[1;90m'.  \033[1;90m     |  \033[1;90m ./\033[1;91m|    |     ";
       Cside.PortraitLine[15] = "\033[1;91m     |      | \033[1;90m|'. \033[1;90m     | \033[1;90m.'|  \033[1;91m|   |     ";
        break;

        case God:
        Cside.PortraitLine[0] = "                \033[43m  \033[0m                      ";
        Cside.PortraitLine[1] = "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m                    ";
        Cside.PortraitLine[2] = "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m                    ";
        Cside.PortraitLine[3] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m                  ";
        Cside.PortraitLine[4] = "                  \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m                ";
        Cside.PortraitLine[5] = "    \033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m                          ";
        Cside.PortraitLine[6] = "\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[47m  \033[0m            ";
        Cside.PortraitLine[7] = "    \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[43m  \033[0m        ";
        Cside.PortraitLine[8] = "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m    ";
        Cside.PortraitLine[9] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[10] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m    ";
       Cside.PortraitLine[11] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[43m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m        ";
       Cside.PortraitLine[12] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m          ";
       Cside.PortraitLine[13] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m            ";
       Cside.PortraitLine[14] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m            ";
       Cside.PortraitLine[15] = "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m              ";
        break;

        default:
        Cside.PortraitLine[0] = "+-  -  -  -  -  - - - - - - - -- -- ---+";
        Cside.PortraitLine[1] = "|                                      |";
        Cside.PortraitLine[2] = "|                                      |";
        Cside.PortraitLine[3] = "|                                      |";
        Cside.PortraitLine[4] = "|                                      |";
        Cside.PortraitLine[5] = "|     ____ ____  ____   ___  ____      |";
        Cside.PortraitLine[6] = "|     |    |___| |___| |   | |___|     |";
        Cside.PortraitLine[7] = "|     |--- | |   | |   |   | | |       |";
        Cside.PortraitLine[8] = "|     |___ |  |  |  |  |___| |  |      |";
        Cside.PortraitLine[9] = "|                                      |";
       Cside.PortraitLine[10] = "|     (Missing Character Portrait)     |";
       Cside.PortraitLine[11] = "|                                      |";
       Cside.PortraitLine[12] = "|                                      |";
       Cside.PortraitLine[13] = "|                                      |";
       Cside.PortraitLine[14] = "+-  -  -  -  -  - - - - - - - -- -- ---+";
       Cside.PortraitLine[15] = "+--- -- -- - - - - - - -  -  -  -  -  -+";
        break;
    }
}
void CharacterPortraits(DialogueC& Cside, Portrait character, Entity& Player){

    if (character == Hero){
        PlayerPortraits(Player, Cside);
        return;
    }

    switch (character){
        case Nochar:
        Cside.Ncolor = "";
        Cside.Name = "";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "                                        ";
        Cside.PortraitLine[5] = "                                        ";
        Cside.PortraitLine[6] = "                                        ";
        Cside.PortraitLine[7] = "                                        ";
        Cside.PortraitLine[8] = "                                        ";
        Cside.PortraitLine[9] = "                                        ";
       Cside.PortraitLine[10] = "                                        ";
       Cside.PortraitLine[11] = "                                        ";
       Cside.PortraitLine[12] = "                                        ";
       Cside.PortraitLine[13] = "                                        ";
       Cside.PortraitLine[14] = "                                        ";
       Cside.PortraitLine[15] = "                                        ";
        break;

        case Witch:
        Cside.Ncolor = "\033[95m";
        Cside.Name = "Witch";
        Cside.PortraitLine[0] = "\033[95m                   /\\                   \033[0m";
        Cside.PortraitLine[1] = "\033[95m                  / \\\\                  \033[0m";
        Cside.PortraitLine[2] = "\033[95m                 /   \\'                 \033[0m";
        Cside.PortraitLine[3] = "\033[95m                /     \\                 \033[0m";
        Cside.PortraitLine[4] = "\033[95m               /       \\                \033[0m";
        Cside.PortraitLine[5] = "\033[95m              /         \\               \033[0m";
        Cside.PortraitLine[6] = "\033[95m             /           \'''''------.  \033[0m";
        Cside.PortraitLine[7] = "\033[95m .-----'''''/   \033[93m[]\033[95m         ...---''''   \033[0m";
        Cside.PortraitLine[8] = "\033[95m  '''''----...______..--'''\033[1;90m|             \033[0m";
        Cside.PortraitLine[9] = "          \033[1;90m|\033[37m :  __     \033[1;90m\\    |            \033[0m";
       Cside.PortraitLine[10] = "          \033[1;90m|\033[37m :-'  ''---'\033[1;90m|   |            \033[0m";
       Cside.PortraitLine[11] = "          \033[1;90m|\033[37m  '.  \033[93m_\033[37m   .'\033[1;90m|   |            \033[0m";
       Cside.PortraitLine[12] = "          \033[1;90m| .\033[37m  '\033[93m/ \\\033[37m--  \033[1;90m|  .'\033[95m.           \033[0m";
       Cside.PortraitLine[13] = "          \033[1;90m:'\033[95m '-.\033[93m\\_/\033[95m.-''\033[1;90m|-'  \033[95m:           \033[0m";
       Cside.PortraitLine[14] = "\033[95m         :      .--.         :          \033[0m";
       Cside.PortraitLine[15] = "\033[95m         '     .'   '.       '          \033[0m";
        break;

        case Witch_down:
        Cside.Ncolor = "\033[95m";
        Cside.Name = "Witch";
        Cside.PortraitLine[0] = "\033[95m                   /\\                   \033[0m";
        Cside.PortraitLine[1] = "\033[95m                  / \\\\                   \033[0m";
        Cside.PortraitLine[2] = "\033[95m                 /   \\'                 \033[0m";
        Cside.PortraitLine[3] = "\033[95m                /     \\                 \033[0m";
        Cside.PortraitLine[4] = "\033[95m               /       \\                \033[0m";
        Cside.PortraitLine[5] = "\033[95m              /         \\.....          \033[0m";
        Cside.PortraitLine[6] = "\033[95m          .../           \\    ''''---.  \033[0m";
        Cside.PortraitLine[7] = "\033[95m .----''''  /   \033[93m[]\033[95m             ..-'''   \033[0m";
        Cside.PortraitLine[8] = "\033[95m  '''--..                ..--''         \033[0m";
        Cside.PortraitLine[9] = "\033[95m         ''--..____..--''  \033[1;90m|            \033[0m";
       Cside.PortraitLine[10] = "          \033[1;90m|\033[0m :  ___   .\033[1;90m\\    |            ";
       Cside.PortraitLine[11] = "          \033[1;90m|\033[0m :''  \033[93m_\033[0m''' .\033[1;90m|   |            \033[0m";
       Cside.PortraitLine[12] = "          \033[1;90m|\033[0m  '..\033[93m/ \\\033[0m.-' \033[1;90m|  .'\033[95m.           \033[0m";
       Cside.PortraitLine[13] = "          \033[1;90m|\033[95m.''-.\033[93m\\_/\033[95m.-''\033[1;90m|-'   \033[95m:          \033[0m";
       Cside.PortraitLine[14] = "\033[95m          :     .--.         :          \033[0m";
       Cside.PortraitLine[15] = "\033[95m         '     .'   '.       '          \033[0m";
        break;

        case Witch_fierce:
        Cside.Ncolor = "\033[95m";
        Cside.Name = "Witch";
        Cside.PortraitLine[0] = "                 \033[95m  /\\ \033[1;96m    .'''.   .     \033[0m";
        Cside.PortraitLine[1] = "\033[1;96m  .            \033[95m   / \\\\ \033[1;96m  :  :  '.       \033[0m";
        Cside.PortraitLine[2] = "\033[1;96m      ...      \033[95m  /   \\' \033[1;96m  '. '''        \033[0m";
        Cside.PortraitLine[3] = "\033[1;96m   .''   '.   \033[95m  /     \\  \033[1;96m :  '.   ..    \033[0m";
        Cside.PortraitLine[4] = "\033[1;96m   : .'.   : \033[95m  /       \\\033[1;96m.'  .'   '. :   \033[0m";
        Cside.PortraitLine[5] = "\033[1;96m    '  ' .'  \033[95m /         \\..'.. \033[1;96m .' .'   \033[0m";
        Cside.PortraitLine[6] = "\033[1;96m    .'' :\033[95m .../           \\    '''''--.  \033[0m";
        Cside.PortraitLine[7] = "\033[95m .----''''  /  \033[96m [] \033[95m            ..-'''   \033[0m";
        Cside.PortraitLine[8] = "\033[1;96m  :\033[95m''--..       \033[1;96m   |    \033[95m ..- ''   \033[1;96m   .  \033[0m";
        Cside.PortraitLine[9] = "\033[1;96m :   .'  \033[95m'--..____\033[1;96m.'.\033[95m--''\033[0m  |\033[1;96m .'''-.     \033[0m";
       Cside.PortraitLine[10] = "\033[1;96m '.   '..\033[0m | :  \033[1;96m--- \033[1;95m*\033[1;96m --- \033[0m  |\033[1;96m: :  '  :   \033[0m";
       Cside.PortraitLine[11] = "\033[1;96m.  '     '\033[0m| :'' \033[1;96m _'.' \033[0m.|   |\033[1;96m.'  '  .    \033[0m";
       Cside.PortraitLine[12] = "\033[1;96m :'.:    \033[0m |  '..\033[1;96m/ \\|\033[0m-' |  .'\033[95m.  \033[1;96m :.' :   \033[0m";
       Cside.PortraitLine[13] = " \033[1;96m '.   \033[0m   |\033[1;95m.''-.\033[1;96m\\_/\033[95m.-''\033[0m|-'  \033[95m : \033[1;96m    .'   \033[0m";
       Cside.PortraitLine[14] = " \033[1;96m   :  \033[95m   :     .--.         :  \033[1;96m  '.    \033[0m";
       Cside.PortraitLine[15] = " \033[1;96m .'  \033[95m   '     .'   '.       '  \033[1;96m    '.. \033[0m";
        break;

        case Witch_broken:
        Cside.Ncolor = "\033[95m";
        Cside.Name = "Witch";
        Cside.PortraitLine[0] = "\033[95m                   /.                   ";
        Cside.PortraitLine[1] = "\033[95m                  / \\                   ";
        Cside.PortraitLine[2] = "\033[95m                 /   \\                  ";
        Cside.PortraitLine[3] = "\033[95m                 _\\   \\                 ";
        Cside.PortraitLine[4] = "\033[95m               _/     /                 ";
        Cside.PortraitLine[5] = "\033[95m              /       ''.   ..          ";
        Cside.PortraitLine[6] = "\033[95m            ./           \\-'  ''''---.  ";
        Cside.PortraitLine[7] = "\033[95m .--.-'''-''/   \033[1;90m[] \033[95m        .--'-.-'''   ";
        Cside.PortraitLine[8] = "\033[95m  '''-''...              ..-'           ";
        Cside.PortraitLine[9] = "\033[1;90m          /\033[95m'-..-'--..--'' \033[1;90m |            ";
       Cside.PortraitLine[10] = "\033[1;90m          |\033[0m :  ___   .\033[1;90m\\    |            ";
       Cside.PortraitLine[11] = "\033[1;90m          |\033[0m :'' \033[90m _\033[1;0m''' .\033[1;90m|   |            ";
       Cside.PortraitLine[12] = "\033[1;90m          |\033[0m  '..\033[90m/ \\\033[0m.-' \033[1;90m|  \033[95m.'.           ";
       Cside.PortraitLine[13] = "\033[1;90m          |\033[0;95m.''-.\033[90m\\_/\033[1;95m.-''\033[1;90m|\033[95m-'  '.          ";
       Cside.PortraitLine[14] = "\033[95m           :    .--.         '.         ";
       Cside.PortraitLine[15] = "\033[95m          '    .'   '.        '         ";
        break;

        case Aiden:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "King Aiden";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "             .-\033[1;93m|____|\033[0m..                 ";
        Cside.PortraitLine[4] = "          \033[1;93m >\033[0m: \033[1;93m   .     \033[0m'.               ";
        Cside.PortraitLine[5] = "           :.''-  \033[1;93m''>-_  \033[0m:              ";
        Cside.PortraitLine[6] = "           ::   '.-.  \033[1;93m-''>.             \033[0m";
        Cside.PortraitLine[7] = "           '|\033[1;93m 0   0\033[0m '-.  :              ";
        Cside.PortraitLine[8] = "            |  /       : :              ";
        Cside.PortraitLine[9] = "             |         : :              ";
       Cside.PortraitLine[10] = "             |         ::'              ";
       Cside.PortraitLine[11] = "              \\___..--'                 ";
       Cside.PortraitLine[12] = "\033[91m             .-\033[0m|     |\033[91m''-..             \033[0m";
       Cside.PortraitLine[13] = "\033[91m           .'  \033[0m|\033[1;93m\\_-_-/\033[91m|   ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[91m         .''\033[1;93m.\033[91m'\033[1;93m.\033[91m\\ \033[1;93m ' ' \033[91m/\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[91m       .'\033[1;93m'.'.'.'\033[91m|\033[1;93m __ \033[91m|\033[1;93m'.'.'.'.'.\033[91m'.      \033[0m";
        break;

        case Aiden_power:
        Cside.Ncolor = "\033[1;95m";
        Cside.Name = "King Aiden";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "\033[1;95m             .-\033[1;93m|____|\033[1;95m..                 \033[0m";
        Cside.PortraitLine[4] = "          \033[1;93m >\033[1;95m: \033[1;93m   .     \033[1;95m'.               \033[0m";
        Cside.PortraitLine[5] = "\033[1;95m           :.''-  \033[1;93m''>-_  \033[1;95m:              \033[0m";
        Cside.PortraitLine[6] = "\033[1;95m           :: \033[1;93m|\033[1;95m '.\033[1;93m|\033[1;95m.  \033[1;93m-''>.             \033[0m";
        Cside.PortraitLine[7] = "\033[1;95m           '\033[0m\033[1;93m--\033[1;95m@\033[1;93m---\033[1;95m@\033[1;93m--\033[1;95m'.  :              ";
        Cside.PortraitLine[8] = "            | \033[1;93m|   |    \033[1;95m: :              ";
        Cside.PortraitLine[9] = "             |         \033[1;95m: :              ";
       Cside.PortraitLine[10] = "             |         \033[1;95m::'              ";
       Cside.PortraitLine[11] = "              \\___..--'                 ";
       Cside.PortraitLine[12] = "\033[91m             .-\033[0m|     |\033[91m''-..             \033[0m";
       Cside.PortraitLine[13] = "\033[91m           .'  \033[0m|\033[1;93m\\_-_-/\033[91m|   ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[91m         .''\033[1;93m.\033[91m'\033[1;93m.\033[91m\\ \033[1;93m ' ' \033[91m/\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[91m       .'\033[1;93m'.'.'.'\033[91m|\033[1;93m __ \033[91m|\033[1;93m'.'.'.'.'.\033[91m'.      \033[0m";
        break;

        case Aiden_dead:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "King Aiden";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "             .-\033[1;93m|____|\033[0m..                 ";
        Cside.PortraitLine[4] = "          \033[1;93m >\033[0m: \033[1;93m   .     \033[0m'.               ";
        Cside.PortraitLine[5] = "           :.''-  \033[1;93m''>-_  \033[0m:              ";
        Cside.PortraitLine[6] = "           ::   '.-.  \033[1;93m-''>.             \033[0m";
        Cside.PortraitLine[7] = "           '|\033[1;93m      \033[0m '-.  :              ";
        Cside.PortraitLine[8] = "            |  /       : :              ";
        Cside.PortraitLine[9] = "             |         : :              ";
       Cside.PortraitLine[10] = "             |         ::'              ";
       Cside.PortraitLine[11] = "              \\___..--'                 ";
       Cside.PortraitLine[12] = "\033[91m             .-\033[0m|     |\033[91m''-..             \033[0m";
       Cside.PortraitLine[13] = "\033[91m           .'  \033[0m|\033[1;93m\\_-_-/\033[91m|   ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[91m         .''\033[1;93m.\033[91m'\033[1;93m.\033[91m\\ \033[1;93m ' ' \033[91m/\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'\033[1;93m.\033[91m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[91m       .'\033[1;93m'.'.'.'\033[91m|\033[1;93m __ \033[91m|\033[1;93m'.'.'.'.'.\033[91m'.      \033[0m";
        break;

        case Addison:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "King Addison";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "               \033[1;93m|____|\033[0m.                  ";
        Cside.PortraitLine[4] = "           \033[1;93m>\033[0m.''       '.                ";
        Cside.PortraitLine[5] = "           :  ..  \033[1;93m'->_ \033[0m :               ";
        Cside.PortraitLine[6] = "           :.'_ ''_.  \033[1;93m''>-              \033[0m";
        Cside.PortraitLine[7] = "           ::\033[1;m O   O \033[0m:.  :               ";
        Cside.PortraitLine[8] = "           :|  /    ' : :               ";
        Cside.PortraitLine[9] = "           '|         : :               ";
       Cside.PortraitLine[10] = "             |      .' .'               ";
       Cside.PortraitLine[11] = "             '-----' |'                 ";
       Cside.PortraitLine[12] = "\033[94m              .\033[0m|\033[1;4;93m-----\033[0m|\033[94m''-.              \033[0m";
       Cside.PortraitLine[13] = "\033[94m           .'' \033[94m\\     \033[94m/    ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[94m         .'\033[1;93m-.-.-\033[94m|    \033[94m|\033[1;93m-.-.-.-.\033[94m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[94m       .'\033[1;93m.-.-.-.\033[94m|    \033[94m|\033[1;93m.-.-.-.-.-\033[94m'.      \033[0m";
        break;

        case Addison_power:
        Cside.Ncolor = "\033[1;95m";
        Cside.Name = "King Addison";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "               \033[1;93m|____|\033[1;95m.                  \033[0m";
        Cside.PortraitLine[4] = "           \033[1;93m>\033[1;95m.''       '.               \033[0m ";
        Cside.PortraitLine[5] = "          \033[1;95m :  .. \033[1;93m '->_  \033[1;95m:               \033[0m";
        Cside.PortraitLine[6] = "\033[1;95m           :.'\033[1;93m|\033[1;95m ''\033[1;93m|\033[1;95m.  \033[1;93m''>-              \033[0m";
        Cside.PortraitLine[7] = "\033[1;95m           :\033[1;93m--\033[1;95m@\033[1;93m---\033[1;95m@\033[1;93m--\033[1;95m.  :               ";
        Cside.PortraitLine[8] = "\033[1;95m           :\033[0m|\033[1;93m |   | \033[1;95m' : :               ";
        Cside.PortraitLine[9] = "\033[1;95m           '\033[0m|         \033[1;95m: :               ";
       Cside.PortraitLine[10] = "             |      .' \033[1;95m.'               ";
       Cside.PortraitLine[11] = "             '-----' |\033[1;95m'                 ";
       Cside.PortraitLine[12] = "\033[94m              .\033[0m|\033[1;4;93m-----\033[0m|\033[94m''-.              \033[0m";
       Cside.PortraitLine[13] = "\033[94m           .'' \033[94m\\     \033[94m/    ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[94m         .'\033[1;93m-.-.-\033[94m|    \033[94m|\033[1;93m-.-.-.-.\033[94m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[94m       .'\033[1;93m.-.-.-.\033[94m|    \033[94m|\033[1;93m.-.-.-.-.-\033[94m'.      \033[0m";
        break;

        case Addison_dead:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "King Addison";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "               \033[1;93m|\\/\\/|                   \033[0m";
        Cside.PortraitLine[3] = "               \033[1;93m|____|\033[0m.                  ";
        Cside.PortraitLine[4] = "           \033[1;93m>\033[0m.''       '.                ";
        Cside.PortraitLine[5] = "           :  ..  \033[1;93m'->_ \033[0m :               ";
        Cside.PortraitLine[6] = "           :.'  ''-.  \033[1;93m''>-              \033[0m";
        Cside.PortraitLine[7] = "           ::\033[1;m       \033[0m:.  :               ";
        Cside.PortraitLine[8] = "           :|  /    ' : :               ";
        Cside.PortraitLine[9] = "           '|         : :               ";
       Cside.PortraitLine[10] = "             |      .' .'               ";
       Cside.PortraitLine[11] = "             '-----' |'                 ";
       Cside.PortraitLine[12] = "\033[94m              .\033[0m|\033[1;4;93m-----\033[0m|\033[94m''-.              \033[0m";
       Cside.PortraitLine[13] = "\033[94m           .'' \033[94m\\     \033[94m/    ''-.          \033[0m";
       Cside.PortraitLine[14] = "\033[94m         .'\033[1;93m-.-.-\033[94m|    \033[94m|\033[1;93m-.-.-.-.\033[94m'.        \033[0m";
       Cside.PortraitLine[15] = "\033[94m       .'\033[1;93m.-.-.-.\033[94m|    \033[94m|\033[1;93m.-.-.-.-.-\033[94m'.      \033[0m";
        break;

        case Prisoner:
        Cside.Ncolor = "\033[1;90m";
        Cside.Name = "Prisoner";
        Cside.PortraitLine[0] = " |\"\"=====____                           ";
        Cside.PortraitLine[1] = " |.=====_____\"\"\"\"\"\"\"\"====____           ";
        Cside.PortraitLine[2] = " ||\033[90m-|_|_ :  .\033[0m\"\"\"=====____    \"\"\"\"====__ ";
        Cside.PortraitLine[3] = " ||\033[90m | | -|--|-_|_  :   . \033[0m\"\"\"\"=====___  |";
        Cside.PortraitLine[4] = " ||\033[90m-|_|_ |  |  | --|--_|__  |    :   \033[0m| |";
        Cside.PortraitLine[5] = " ||\033[90m | | -|--|-_|_\033[91m*\033[90m |\033[91m*\033[90m  |  --|--__|__ \033[0m| |";
        Cside.PortraitLine[6] = " ||\033[90m-|_|_ |  |  | --|--_|__  |    |  -\033[0m| |";
        Cside.PortraitLine[7] = " ||\033[90m | | -|-\033[0m| \\\033[90m |_  |   |  --|--__|__ \033[0m| |";
        Cside.PortraitLine[8] = " ||\033[90m-|_|_ | \033[0m|_/\033[90m | -\033[0m/ |\033[90m _|__  |    |  -\033[0m| |";
        Cside.PortraitLine[9] = " ||\033[90m | | -|--|-_|_ \033[0m\\_|\033[90m  |  --|--__|__ \033[0m| |";
       Cside.PortraitLine[10] = " ||\033[90m-|_|_ |  |  | --|--_|__ \033[0m(+)\033[90m   |  -\033[0m| |";
       Cside.PortraitLine[11] = " ||\033[90m | | -|--|-_|_  |   |  -\033[0m|'|\033[90m-__|__ \033[0m| |";
       Cside.PortraitLine[12] = ".''.' \033[90m:  |  |  | --|--_|__  |    |  -\033[0m| |";
       Cside.PortraitLine[13] = " .' .' .'  .'  \033[90m:   |   |  --|--__|__ \033[0m| |";
       Cside.PortraitLine[14] = "' .' .'  .'  .'  .'   .'    :   \033[90m |  -\033[0m| |";
       Cside.PortraitLine[15] = ".' .'  .'  .'  .'   .'    .'    .'  .|_|";
        break;

        case Sogro_prison:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "Sogro";
        Cside.PortraitLine[0] = " |\"\"=====____                           ";
        Cside.PortraitLine[1] = " |.=====_____\"\"\"\"\"\"\"\"====____           ";
        Cside.PortraitLine[2] = " ||\033[90m-|_|_ :  .\033[0m\"\"\"=====____    \"\"\"\"====__ ";
        Cside.PortraitLine[3] = " ||\033[90m | | -|--|-_|_  :   . \033[0m\"\"\"\"=====___  |";
        Cside.PortraitLine[4] = " ||\033[90m-|_|_ |  |  | --|--_|__  |    :   \033[0m| |";
        Cside.PortraitLine[5] = " ||\033[90m | | -|--|-_|_\033[93m*\033[90m |\033[93m*\033[90m  |  --|--__|__ \033[0m| |";
        Cside.PortraitLine[6] = " ||\033[90m-|_|_ |  |  | --|--_|__  |    |  -\033[0m| |";
        Cside.PortraitLine[7] = " ||\033[90m | | -|-\033[0m| \\\033[90m |_  |   |  --|--__|__ \033[0m| |";
        Cside.PortraitLine[8] = " ||\033[90m-|_|_ | \033[0m|_/\033[90m | -\033[0m/ |\033[90m _|__  |    |  -\033[0m| |";
        Cside.PortraitLine[9] = " ||\033[90m | | -|--|-_|_ \033[0m\\_|\033[90m  |  --|--__|__ \033[0m| |";
       Cside.PortraitLine[10] = " ||\033[90m-|_|_ |  |  | --|--_|__ \033[0m(+)\033[90m   |  -\033[0m| |";
       Cside.PortraitLine[11] = " ||\033[90m | | -|--|-_|_  |   |  -\033[0m|'|\033[90m-__|__ \033[0m| |";
       Cside.PortraitLine[12] = ".''.' \033[90m:  |  |  | --|--_|__  |    |  -\033[0m| |";
       Cside.PortraitLine[13] = " .' .' .'  .'  \033[90m:   |   |  --|--__|__ \033[0m| |";
       Cside.PortraitLine[14] = "' .' .'  .'  .'  .'   .'    :   \033[90m |  -\033[0m| |";
       Cside.PortraitLine[15] = ".' .'  .'  .'  .'   .'    .'    .'  .|_|";
        break;

        case Prisoner_Free:
        Cside.Ncolor = "\033[1;90m";
        Cside.Name = "Prisoner";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "              .-'''''-.                 ";
        Cside.PortraitLine[5] = "             /         \\                ";
        Cside.PortraitLine[6] = "            |           |               ";
        Cside.PortraitLine[7] = "           |            |               ";
        Cside.PortraitLine[8] = "           | \033[91m *   *  \033[0m   |               ";
        Cside.PortraitLine[9] = "            |          /                ";
       Cside.PortraitLine[10] = "             |        /                 ";
       Cside.PortraitLine[11] = "              \\______/|                  ";
       Cside.PortraitLine[12] = "\033[90m              .\033[0m|       '-..             ";
       Cside.PortraitLine[13] = "\033[90m         .'''' '..  ...'  ''''-.        \033[0m";
       Cside.PortraitLine[14] = "\033[90m       .'         ''            '.      \033[0m";
       Cside.PortraitLine[15] = "\033[90m       '                         '      \033[0m";
        break;

        case Fallen:
        Cside.Ncolor = "\033[95m";
        Cside.Name = "Fallen";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "              .-'''''-.                 ";
        Cside.PortraitLine[5] = "             / \033[91m:       \033[0m\\                ";
        Cside.PortraitLine[6] = "            | \033[91m:     .   \033[0m|               ";
        Cside.PortraitLine[7] = "           |       \033[91m  :  \033[0m|               ";
        Cside.PortraitLine[8] = "           |  _   _ \033[91m  '.\033[0m|               ";
        Cside.PortraitLine[9] = "            |       \033[91m   :                \033[0m";
       Cside.PortraitLine[10] = "             |    \033[91m .' :                 \033[0m";
       Cside.PortraitLine[11] = "              \\______/|                 \033[0m";
       Cside.PortraitLine[12] = "\033[90m              .\033[0m|  \033[91m ' : \033[90m'-..             \033[0m";
       Cside.PortraitLine[13] = "\033[90m         .--'' '.. \033[91m . ' \033[90m.'''''-.        \033[0m";
       Cside.PortraitLine[14] = "\033[90m       .'         '' : :        '.      \033[0m";
       Cside.PortraitLine[15] = "\033[90m       '       \033[91m:'.    :.       .\033[90m '    \033[0m  ";
        break;

        case Champion:
        Cside.Ncolor = "\033[1;95m";
        Cside.Name = "CHAMPION";
        Cside.PortraitLine[0] = "\033[1;95m  \\                                     ";
        Cside.PortraitLine[1] = "\033[1;95m   |  \033[1;90m .-'''''--..                      ";
        Cside.PortraitLine[2] = "\033[1;95m   || \033[1;90m'  :   ''.. ''.                   ";
        Cside.PortraitLine[3] = "\033[1;95m    ||  \033[1;90m'  :     ''  :                  ";
        Cside.PortraitLine[4] = "\033[1;95m|   ||  \033[1;90m  :    \033[1;95m .| \033[1;90m   :                 ";
        Cside.PortraitLine[5] = "\033[1;95m'||  ||.   ..||||'  \033[1;90m   :                ";
        Cside.PortraitLine[6] = "\033[1;95m  '||||||||||'    \033[1;90m  .  :                ";
        Cside.PortraitLine[7] = "\033[1;90m   . \033[1;95m ||'       \033[1;90m   :   :                ";
        Cside.PortraitLine[8] = "\033[1;90m   : \033[1;95m ||       \033[1;90m   :    :                ";
        Cside.PortraitLine[9] = "\033[1;90m   : \033[1;95m  || \033[1;90m  :     '    :                ";
       Cside.PortraitLine[10] = "\033[1;90m    : \033[1;95m ||  \033[1;90m  :         :                ";
       Cside.PortraitLine[11] = "\033[1;90m    :  \033[1;95m ||_ \033[1;90m :  :      :                ";
       Cside.PortraitLine[12] = "\033[1;90m    :        '   :   '  :               ";
       Cside.PortraitLine[13] = "\033[1;90m    :      .     :       :              ";
       Cside.PortraitLine[14] = "\033[1;90m    :   ..'       '.      :             ";
       Cside.PortraitLine[15] = "\033[1;90m   :  .'           '.      :            ";
        break;

        case Nora:
        Cside.Ncolor = "\033[1;92m";
        Cside.Name = "Nora";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "\033[90m               .--------._              ";
        Cside.PortraitLine[4] = "\033[90m              /           \\             ";
        Cside.PortraitLine[5] = "\033[90m             /      _      \\            ";
        Cside.PortraitLine[6] = "\033[90m            |    .-' \\      |           ";
        Cside.PortraitLine[7] = "\033[90m            |   :     |     |           ";
        Cside.PortraitLine[8] = "\033[90m            | .'      \\     |           ";
        Cside.PortraitLine[9] = "\033[90m            | |        |     \\          ";
       Cside.PortraitLine[10] = "\033[90m            |  \\_      \\      |         ";
       Cside.PortraitLine[11] = "\033[90m             \\   |     |      |         ";
       Cside.PortraitLine[12] = "         \033[92m    -\033[90m|  |  \033[92m .-\033[90m/   |\033[92m'-:\033[90m         ";
       Cside.PortraitLine[13] = "          \033[92m.''\033[90m/  / \033[92m''' \033[90m/   /   \033[92m ' \033[90m       ";
       Cside.PortraitLine[14] = "        \033[92m ' \033[90m  |  |     |   |    \033[92m '  \033[90m     ";
       Cside.PortraitLine[15] = "        \033[92m' \033[90m  /  /      /   /     \033[92m ' \033[90m     ";
        break;

        case Dawg:
        Cside.Ncolor = "\033[1;37m";
        Cside.Name = "Dog";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "                                        ";
        Cside.PortraitLine[5] =  "\033[1;90m                        _               ";
        Cside.PortraitLine[6] = "\033[1;90m              |\\       / |              ";
        Cside.PortraitLine[7] = "\033[1;90m              | \\_____/  |              ";
        Cside.PortraitLine[8] = "\033[1;90m              |          |              ";
        Cside.PortraitLine[9] = "\033[1;90m             | \033[37m.   .  \033[90m   |           .--";
       Cside.PortraitLine[10] = "\033[1;37m        __\033[90m------         |          / .-";
       Cside.PortraitLine[11] = "\033[1;37m       /__\\\033[90m              |         / /  ";
       Cside.PortraitLine[12] = "\033[1;90m       \\________         |        | |   ";
       Cside.PortraitLine[13] = "\033[1;91m          |  |\033[90m|          |        '.'   ";
       Cside.PortraitLine[14] = "\033[1;91m          |__|\033[90m \\          \\_____________";
       Cside.PortraitLine[15] = "\033[1;90m                |                       ";
        break;

        case Dawg_dead:
        Cside.Ncolor = "\033[1;37m";
        Cside.Name = "Dog";
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "                                        ";
        Cside.PortraitLine[2] = "                                        ";
        Cside.PortraitLine[3] = "                                        ";
        Cside.PortraitLine[4] = "                                        ";
        Cside.PortraitLine[5] = "                                        ";
        Cside.PortraitLine[6] = "                                        ";
        Cside.PortraitLine[7] = "                                        ";
        Cside.PortraitLine[8] = "                                        ";
        Cside.PortraitLine[9] = "\033[1;90m                                     .--";
       Cside.PortraitLine[10] = "\033[1;90m                                    / .-";
       Cside.PortraitLine[11] = "\033[1;91m                     __..\033[90m          / /  ";
       Cside.PortraitLine[12] = "\033[1;91m                 _.-'_.-'\033[90m|        | |   ";
       Cside.PortraitLine[13] = "\033[1;91m               .:--:':'  \033[90m|        '.'   ";
       Cside.PortraitLine[14] = "\033[1;90m               \\\033[91m'  : '    \033[90m\\_____________";
       Cside.PortraitLine[15] = "\033[1;90m                |\033[91m  '                    ";
        break;

        case Starwalker:
        Cside.Ncolor = "\033[1;93m";
        Cside.Name = "Starwalker";
        Cside.PortraitLine[0] = "                \033[43m  \033[0m";
        Cside.PortraitLine[1] = "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[2] = "              \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[3] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[4] = "                  \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[5] = "    \033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m";
        Cside.PortraitLine[6] = "\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[47m  \033[0m";
        Cside.PortraitLine[7] = "    \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[47m  \033[0m\033[0m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[8] = "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        Cside.PortraitLine[9] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[10] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[11] = "            \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[43m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[12] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[13] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[14] = "          \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
       Cside.PortraitLine[15] = "        \033[43m  \033[0m\033[43m  \033[0m\033[43m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[0m  \033[0m\033[43m  \033[0m\033[43m  \033[0m";
        break;

        case Hero_halfChamp:
        Cside.Ncolor = Player.Misc.Color;
        Cside.Name =  Player.Name;
        Cside.PortraitLine[0] = "                                        ";
        Cside.PortraitLine[1] = "               _______                  ";
        Cside.PortraitLine[2] = "             .'       '.                ";
        Cside.PortraitLine[3] = "            /  .'       \\               ";
        Cside.PortraitLine[4] = "           :             :              ";
        Cside.PortraitLine[5] = "           :     .    .  :              ";
        Cside.PortraitLine[6] = "           :    -+-  -+- :              ";
        Cside.PortraitLine[7] = "            \\    '    '  :              ";
        Cside.PortraitLine[8] = "             \\ :         :              ";
        Cside.PortraitLine[9] = "           .-': '       /.              ";
       Cside.PortraitLine[10] = "        .-'      '.____/  ''--.         ";
       Cside.PortraitLine[11] = "      .:     :            :    '.       ";
       Cside.PortraitLine[12] = "     .:       :         .'      :.      ";
       Cside.PortraitLine[13] = "     :  .   '. '.       :    .   :      ";
       Cside.PortraitLine[14] = "    :  :      :               :   :     ";
       Cside.PortraitLine[15] = "   :  :       :     .          :   :    ";
        break;

        case Hero_Champ:
        Cside.Ncolor = Player.Misc.Color;
        Cside.Name =  Player.Name;
        Cside.PortraitLine[0] = "\033[1;90m               ..--'''-.                ";
        Cside.PortraitLine[1] = "\033[1;90m             .' .' : '. ' \033[95m.             ";
        Cside.PortraitLine[2] = "\033[1;90m            :     '    \033[95m //              ";
        Cside.PortraitLine[3] = "\033[1;90m           :     .   \033[95m  // \033[90m.             ";
        Cside.PortraitLine[4] = "\033[1;90m           :   \033[95m . \033[90m': \033[95m ||  \033[90m:             ";
        Cside.PortraitLine[5] = "\033[1;90m           :     \033[95m'====||==='            ";
        Cside.PortraitLine[6] = "\033[1;90m           '. :    ' \033[95m ||  \033[90m:             ";
        Cside.PortraitLine[7] = "\033[1;90m            : :     \033[95m //  \033[90m.'             ";
        Cside.PortraitLine[8] = "\033[1;90m            .' '.  \033[95m //   \033[90m ''.           ";
        Cside.PortraitLine[9] = "\033[1;90m         .-'     :     .     '-.        ";
       Cside.PortraitLine[10] = "\033[1;90m       .:   :    :    '   :    '.       ";
       Cside.PortraitLine[11] = "\033[1;90m      :   .'      '      :      :.      ";
       Cside.PortraitLine[12] = "\033[1;90m     .:   :             '.  '.   :.     ";
       Cside.PortraitLine[13] = "\033[1;90m     :           :       :    :   :     ";
       Cside.PortraitLine[14] = "\033[1;90m    :  .     :    :            :   :    ";
       Cside.PortraitLine[15] = "\033[1;90m    :                             .'    ";
        break;

        default:
        Cside.Name = "MISSINGCHARA.";
        Cside.PortraitLine[0] = "+-  -  -  -  -  - - - - - - - -- -- ---+";
        Cside.PortraitLine[1] = "|                                      |";
        Cside.PortraitLine[2] = "|                                      |";
        Cside.PortraitLine[3] = "|                                      |";
        Cside.PortraitLine[4] = "|                                      |";
        Cside.PortraitLine[5] = "|     ____ ____  ____   ___  ____      |";
        Cside.PortraitLine[6] = "|     |    |___| |___| |   | |___|     |";
        Cside.PortraitLine[7] = "|     |--- | |   | |   |   | | |       |";
        Cside.PortraitLine[8] = "|     |___ |  |  |  |  |___| |  |      |";
        Cside.PortraitLine[9] = "|                                      |";
       Cside.PortraitLine[10] = "|     (Missing Character Portrait)     |";
       Cside.PortraitLine[11] = "|                                      |";
       Cside.PortraitLine[12] = "|                                      |";
       Cside.PortraitLine[13] = "|                                      |";
       Cside.PortraitLine[14] = "+-  -  -  -  -  - - - - - - - -- -- ---+";
       Cside.PortraitLine[15] = "+--- -- -- - - - - - - -  -  -  -  -  -+";
        break;
    }
}


string CharName(string name){// Limit is 15 chars
    int TotalSpace = 15;
    int NameSpace = size(name);
    bool Extra;
    if (size(name) % 2 == 0){
        Extra = true;
    }else{
        Extra = false;
    }

    int Space = TotalSpace - NameSpace;

    for (int l = 0; l < Space / 2; l++){
        cout << " ";
    }

    cout << name;

    for (int l = 0; l < Space / 2; l++){
        cout << " ";
    }
    if (Extra == true){
        return " ";
    }else{
        return "";
    }
    return "";
}

// - -MAIN DIALOGUE BOXES- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||

void Dialogue(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string TextLine1, string TextLine2, string TextLine3, int automiliseconds){
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);
    
    if (LeftTalk == true){
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<<  endl << "\033[1;37m";
        cout << "\t             .-'-.-'-.-'-.-'-.                           \033[0m"<<CharacterR.PortraitLine[15]     << endl << "\033[1;37m";
        cout << "\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<CharName(CharacterL.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << TextLine1 << "\n\n";

        cout << "\t       " << TextLine2 << "\n\n";

        cout << "\t       " << TextLine3 << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";
    }else{
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[15]<<"\033[1;37m                   .-'-.-'-.-'-.-'-." << endl;
        cout << "\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<CharName(CharacterR.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t                                                             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << TextLine1 << "\n\n";

        cout << "\t       " << TextLine2 << "\n\n";

        cout << "\t       " << TextLine3 << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";

    }

    if (automiliseconds <= 0){
    EnterShort();
    }else{
        usleep(automiliseconds);
    }

    clear();
}
void DialogueNoFace(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string TextLine1, string TextLine2, string TextLine3, int automiliseconds){

    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);
    
    if (LeftTalk == true){
        cout << "\033[1;37m";
        cout << "\t             .-'-.-'-.-'-.-'-.                           " << endl;
        cout << "\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<CharName(CharacterL.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << TextLine1 << "\n\n";

        cout << "\t       " << TextLine2 << "\n\n";

        cout << "\t       " << TextLine3 << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";
    }else{
        cout << "\033[1;37m";
        cout << "\t                                                             .-'-.-'-.-'-.-'-." << endl;
        cout << "\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<CharName(CharacterR.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t                                                             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << TextLine1 << "\n\n";

        cout << "\t       " << TextLine2 << "\n\n";

        cout << "\t       " << TextLine3 << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";

    }
    
    if (automiliseconds <= 0){
    EnterShort();
    }else{
        usleep(automiliseconds);
    }

    clear();
}

string ChoiceUI(string choice, int number, int& TotalChoices){
    if (choice != ""){
        TotalChoices++;
        cout << "\033[1;93m" << number << "\033[37m - \033[0m";
        return choice;
    }else{
        return " ---";
    }
}
void DialogueChoice(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string Choice1, string Choice2, string Choice3, int& Action){
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);

    while (true){
    int TotalChoices = 0;
    
    if (LeftTalk == true){
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<<  endl << "\033[1;37m";
        cout << "\t             .-'-.-'-.-'-.-'-.                           \033[0m"<<CharacterR.PortraitLine[15]     << endl << "\033[1;37m";
        cout << "\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<CharName(CharacterL.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t    " << ChoiceUI(Choice1,1,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice2,2,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice3,3,TotalChoices) << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";
    }else{
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[15]<<"\033[1;37m                   .-'-.-'-.-'-.-'-." << endl;
        cout << "\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<CharName(CharacterR.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t                                                             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t    " << ChoiceUI(Choice1,1,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice2,2,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice3,3,TotalChoices) << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";

    }

    cout << "You: ";
    PlayerInput(Action);

    if (Action <= 0 || Action > TotalChoices){
        cout << "Invalid choice";
        usleep(200000);
    }else{
        break;
    }

    clear();
    }
    clear();
}
void DialogueChoiceNoFace(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string Choice1, string Choice2, string Choice3, int& Action){

    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);

    while (true){
    int TotalChoices = 0;
    
    if (LeftTalk == true){
        cout << "\033[1;37m";
        cout << "\t             .-'-.-'-.-'-.-'-.             " << endl << "\033[1;37m";
        cout << "\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<CharName(CharacterL.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t    " << ChoiceUI(Choice1,1,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice2,2,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice3,3,TotalChoices) << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";
    }else{
        cout << "\033[1;37m";
        cout << "\t                                                             .-'-.-'-.-'-.-'-." << endl;
        cout << "\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<CharName(CharacterR.Name)<<"\033[1;37m:-.-'-.-'-.-'-.-'-.-#\033[1;37m" << endl;
        cout << "\t                                                             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t    " << ChoiceUI(Choice1,1,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice2,2,TotalChoices) << "\n\n";

        cout << "\t    " << ChoiceUI(Choice3,3,TotalChoices) << "\n\n \033[1;37m";

        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";

    }

    cout << "You: ";
    PlayerInput(Action);

    if (Action <= 0 || Action > TotalChoices){
        cout << "Invalid choice";
        usleep(200000);
    }else{
        break;
    }

    clear();
    }
    clear();
}

void DialogueFlash(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string flashcolor){
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);

    for (int l = 0; l < 11; l++){
        clear();

        string color = flashcolor;
        if (l % 2 == 0){
            color = "\033[1;37m";
        }
    
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<< endl << color;
        cout << "\t             .-'-.-'-.-'-.-'-.                           \033[0m"<<CharacterR.PortraitLine[15]     <<"\033[0m"<< endl << color;
        cout << "\t #-.-'-.-'-.-:               :-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#" << color << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'" << "\n\n\n\n\n\n\n\n";







        cout << "\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << "\n\n";
        usleep(25000);
    }
    usleep(500000);
    clear();
}

void DialogueWhite(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string TextLine1, string TextLine2, string TextLine3, int automiliseconds){//Only works on right character talk
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);
    
    if (LeftTalk == true){
        cout << "\033[47m";
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[0]  << "\033[47m               " <<       CharacterR.PortraitLine[0]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[1]  << "\033[47m               " <<       CharacterR.PortraitLine[1]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[2]  << "\033[47m               " <<       CharacterR.PortraitLine[2]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[3]  << "\033[47m               " <<       CharacterR.PortraitLine[3]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[4]  << "\033[47m               " <<       CharacterR.PortraitLine[4]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[5]  << "\033[47m               " <<       CharacterR.PortraitLine[5]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[6]  << "\033[47m               " <<       CharacterR.PortraitLine[6]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[7]  << "\033[47m               " <<       CharacterR.PortraitLine[7]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[8]  << "\033[47m               " <<       CharacterR.PortraitLine[8]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[9]  << "\033[47m               " <<       CharacterR.PortraitLine[9]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[10]  << "\033[47m               " <<      CharacterR.PortraitLine[10]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[11]  << "\033[47m               " <<      CharacterR.PortraitLine[11]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[12]  << "\033[47m               " <<      CharacterR.PortraitLine[12]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[13]  << "\033[47m               " <<      CharacterR.PortraitLine[13]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[14]  << "\033[47m               " <<      CharacterR.PortraitLine[14]     << endl << "\033[1;90;47m";
        cout << "\033[47m\t             .-'-.-'-.-'-.-'-.                           \033[47m"<<CharacterR.PortraitLine[15]     << endl << "\033[1;90;47m";
        cout << "\033[47m\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<"\033[47m"<<CharName(CharacterL.Name)<<"\033[1;90;47m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;90;47m" << endl;
        cout << "\033[47m\t             '-.-'-.-'-.-'-.-'\033[0;47m" << "\n\033[47m\n";

        cout << "\033[47m\t       " << TextLine1 << "\033[47m\n\033[47m\n\033[47m";

        cout << "\033[47m\t       " << TextLine2 << "\033[47m\n\033[47m\n\033[47m";

        cout << "\033[47m\t       " << TextLine3 << "\033[47m\n\033[47m\n \033[1;90;47m";

        cout << "\033[47m\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0;47m" << "\n\n";

    }else{
        cout << "\033[47m";
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[0]  << "\033[47m               " <<       CharacterR.PortraitLine[0]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[1]  << "\033[47m               " <<       CharacterR.PortraitLine[1]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[2]  << "\033[47m               " <<       CharacterR.PortraitLine[2]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[3]  << "\033[47m               " <<       CharacterR.PortraitLine[3]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[4]  << "\033[47m               " <<       CharacterR.PortraitLine[4]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[5]  << "\033[47m               " <<       CharacterR.PortraitLine[5]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[6]  << "\033[47m               " <<       CharacterR.PortraitLine[6]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[7]  << "\033[47m               " <<       CharacterR.PortraitLine[7]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[8]  << "\033[47m               " <<       CharacterR.PortraitLine[8]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[9]  << "\033[47m               " <<       CharacterR.PortraitLine[9]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[10]  << "\033[47m               " <<      CharacterR.PortraitLine[10]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[11]  << "\033[47m               " <<      CharacterR.PortraitLine[11]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[12]  << "\033[47m               " <<      CharacterR.PortraitLine[12]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[13]  << "\033[47m               " <<      CharacterR.PortraitLine[13]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[14]  << "\033[47m               " <<      CharacterR.PortraitLine[14]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[15]<<"\033[1;90;47m                   .-'-.-'-.-'-.-'-." << endl;
        cout << "\033[47m\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<"\033[47m"<<CharName(CharacterR.Name)<<"\033[1;90;47m:-.-'-.-'-.-'-.-'-.-#\033[1;90;47m" << endl;
        cout << "\033[47m\t                                                             '-.-'-.-'-.-'-.-'\033[0;47m" << "\n\n";

        cout << "\033[47m\t       " << TextLine1 << "\n\n";

        cout << "\033[47m\t       " << TextLine2 << "\n\n";

        cout << "\033[47m\t       " << TextLine3 << "\n\n \033[1;90;47m";

        cout << "\033[47m\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0;47m" << "\n\n";

    }

    if (automiliseconds <= 0){
    EnterShort();
    }else{
        usleep(automiliseconds);
    }

    clear();
}


void DialogueColored(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string TextLine1, string TextLine2, string TextLine3, int automiliseconds, string bgcolor){//Only works on right character talk
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);
    
    if (LeftTalk == true){
        cout << bgcolor;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[0]   << bgcolor << "               " <<       CharacterR.PortraitLine[0]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[1]   << bgcolor << "               " <<       CharacterR.PortraitLine[1]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[2]   << bgcolor << "               " <<       CharacterR.PortraitLine[2]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[3]   << bgcolor << "               " <<       CharacterR.PortraitLine[3]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[4]   << bgcolor << "               " <<       CharacterR.PortraitLine[4]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[5]   << bgcolor << "               " <<       CharacterR.PortraitLine[5]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[6]   << bgcolor << "               " <<       CharacterR.PortraitLine[6]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[7]   << bgcolor << "               " <<       CharacterR.PortraitLine[7]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[8]   << bgcolor << "               " <<       CharacterR.PortraitLine[8]     << endl;
        cout << bgcolor << "\t  "   <<  CharacterL.PortraitLine[9]   << bgcolor << "               " <<       CharacterR.PortraitLine[9]     << endl;
        cout << bgcolor << "\t  "   << CharacterL.PortraitLine[10]   << bgcolor << "               " <<      CharacterR.PortraitLine[10]     << endl;
        cout << bgcolor << "\t  "   << CharacterL.PortraitLine[11]   << bgcolor << "               " <<      CharacterR.PortraitLine[11]     << endl;
        cout << bgcolor << "\t  "   << CharacterL.PortraitLine[12]   << bgcolor << "               " <<      CharacterR.PortraitLine[12]     << endl;
        cout << bgcolor << "\t  "   << CharacterL.PortraitLine[13]   << bgcolor << "               " <<      CharacterR.PortraitLine[13]     << endl;
        cout << bgcolor << "\t  "   << CharacterL.PortraitLine[14]   << bgcolor << "               " <<      CharacterR.PortraitLine[14]     << endl << "\033[1;90m";
        cout << bgcolor << "\t             .-'-.-'-.-'-.-'-.                           "<< bgcolor<<CharacterR.PortraitLine[15]     << endl << "\033[1;90m";
        cout << bgcolor << "\t #-.-'-.-'-.-:"<<CharacterL.Ncolor<<bgcolor<<CharName(CharacterL.Name)<<bgcolor<<"\033[1;90m:-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-#\033[1;90m" << endl;
        cout << bgcolor << "\t             '-.-'-.-'-.-'-.-'" << bgcolor << "\n"<<bgcolor<<"\n";

        cout << bgcolor<<"\t       " << TextLine1 << bgcolor << "\n\n";

        cout << bgcolor<<"\t       " << TextLine2 << bgcolor << "\n\n";

        cout << bgcolor<<"\t       " << TextLine3 << bgcolor << "\033[1;90m" << "\n\n";

        cout << bgcolor<<"\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0m" << bgcolor << "\n\n";

    }else{
        cout << "\033[47m";
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[0]  << "\033[47m               " <<       CharacterR.PortraitLine[0]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[1]  << "\033[47m               " <<       CharacterR.PortraitLine[1]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[2]  << "\033[47m               " <<       CharacterR.PortraitLine[2]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[3]  << "\033[47m               " <<       CharacterR.PortraitLine[3]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[4]  << "\033[47m               " <<       CharacterR.PortraitLine[4]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[5]  << "\033[47m               " <<       CharacterR.PortraitLine[5]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[6]  << "\033[47m               " <<       CharacterR.PortraitLine[6]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[7]  << "\033[47m               " <<       CharacterR.PortraitLine[7]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[8]  << "\033[47m               " <<       CharacterR.PortraitLine[8]     << endl;
        cout << "\033[47m\t  "   <<  CharacterL.PortraitLine[9]  << "\033[47m               " <<       CharacterR.PortraitLine[9]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[10]  << "\033[47m               " <<      CharacterR.PortraitLine[10]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[11]  << "\033[47m               " <<      CharacterR.PortraitLine[11]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[12]  << "\033[47m               " <<      CharacterR.PortraitLine[12]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[13]  << "\033[47m               " <<      CharacterR.PortraitLine[13]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[14]  << "\033[47m               " <<      CharacterR.PortraitLine[14]     << endl;
        cout << "\033[47m\t  "   << CharacterL.PortraitLine[15]<<"\033[1;90;47m                   .-'-.-'-.-'-.-'-." << endl;
        cout << "\033[47m\t #-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-:"<<CharacterR.Ncolor<<"\033[47m"<<CharName(CharacterR.Name)<<"\033[1;90;47m:-.-'-.-'-.-'-.-'-.-#\033[1;90;47m" << endl;
        cout << "\033[47m\t                                                             '-.-'-.-'-.-'-.-'\033[0;47m" << "\n\n";

        cout << "\033[47m\t       " << TextLine1 << "\n\n";

        cout << "\033[47m\t       " << TextLine2 << "\n\n";

        cout << "\033[47m\t       " << TextLine3 << "\n\n \033[1;90;47m";

        cout << "\033[47m\t #-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-.-'-#\033[0;47m" << "\n\n";

    }

    if (automiliseconds <= 0){
    EnterShort();
    }else{
        usleep(automiliseconds);
    }

    clear();
}


string DramaticLine(string text, string color, int slowness){
    usleep(slowness*1.5);

    int Size = size(text);
    cout << color;
    for (int l = 0; l < Size; l++){
        cout << text[l];
        usleep(slowness);
    }
    return "";
}
void DialogueDramatic(Entity& Player, Portrait LeftCharacter, Portrait RightCharacter, bool LeftTalk, string TextLine1, string Line1color, string TextLine2,  string Line2color, int textslowness, int automiliseconds){
    clear();
    CharacterL.Ncolor = "\033[0m";
    CharacterR.Ncolor = "\033[0m";
    CharacterPortraits(CharacterL, LeftCharacter, Player);
    CharacterPortraits(CharacterR, RightCharacter, Player);
    
    if (LeftTalk == true){
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<<  endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<<  endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<<  endl << "\033[1;37m";
        cout << "\t             .-'-.-'-.-'-.-'-.                           \033[0m"<<CharacterR.PortraitLine[15]     << endl << "\033[1;37m";
        cout << "\t              "<<CharacterL.Ncolor<<CharName(CharacterL.Name)<<"\033[1;37m\033[1;37m" << endl;
        cout << "\t             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << DramaticLine(TextLine1,Line1color,textslowness) << "\n\n";

        cout << "\t       " << DramaticLine(TextLine2,Line2color,textslowness) << "\n\n";

        cout << "\t       " << "\n\n \033[1;37m";

        cout << "\t" << "\n\n";
    }else{
        cout << "\t  "   <<  CharacterL.PortraitLine[0]  << "\033[0m               " <<       CharacterR.PortraitLine[0]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[1]  << "\033[0m               " <<       CharacterR.PortraitLine[1]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[2]  << "\033[0m               " <<       CharacterR.PortraitLine[2]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[3]  << "\033[0m               " <<       CharacterR.PortraitLine[3]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[4]  << "\033[0m               " <<       CharacterR.PortraitLine[4]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[5]  << "\033[0m               " <<       CharacterR.PortraitLine[5]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[6]  << "\033[0m               " <<       CharacterR.PortraitLine[6]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[7]  << "\033[0m               " <<       CharacterR.PortraitLine[7]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[8]  << "\033[0m               " <<       CharacterR.PortraitLine[8]     <<"\033[0m"<< endl;
        cout << "\t  "   <<  CharacterL.PortraitLine[9]  << "\033[0m               " <<       CharacterR.PortraitLine[9]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[10]  << "\033[0m               " <<      CharacterR.PortraitLine[10]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[11]  << "\033[0m               " <<      CharacterR.PortraitLine[11]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[12]  << "\033[0m               " <<      CharacterR.PortraitLine[12]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[13]  << "\033[0m               " <<      CharacterR.PortraitLine[13]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[14]  << "\033[0m               " <<      CharacterR.PortraitLine[14]     <<"\033[0m"<< endl;
        cout << "\t  "   << CharacterL.PortraitLine[15]<<"\033[1;37m                   .-'-.-'-.-'-.-'-." << endl;
        cout << "\t                                                              "<<CharacterR.Ncolor<<CharName(CharacterR.Name)<<"\033[1;37m\033[1;37m" << endl;
        cout << "\t                                                             '-.-'-.-'-.-'-.-'\033[0m" << "\n\n";

        cout << "\t       " << DramaticLine(TextLine1,Line1color,textslowness) << "\n\n";

        cout << "\t       " << DramaticLine(TextLine2,Line2color,textslowness) << "\n\n";

        cout << "\t       " << "\n\n \033[1;37m";

        cout << "\t" << "\n\n";

    }

    if (automiliseconds <= 0){
    EnterShort();
    }else{
        usleep(automiliseconds);
    }

    clear();
}


// - -DIALOGUE EVENTS- - - (DE = Dialog Event) (EE = Easter Egg) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||

void DE_KingRoomArrival(Entity Player){
    string ClassMention;
    string ClassMentionCaps;
    string Pronoun;
    switch (Player.Misc.Class){
        case Gladiator:
        ClassMention = "Gladiator";
        ClassMentionCaps = "GLADIATOR";
        Pronoun = "him";
        break;
        case Wanderer:
        ClassMention = "Wanderer";
        ClassMentionCaps = "WANDERER";
        Pronoun = "her";
        break;
        case Berserker:
        ClassMention = "Berserker";
        ClassMentionCaps = "BERSERKER";
        Pronoun = "him";
        break;
        case BlackKnight:
        ClassMention = "Black Knight";
        ClassMentionCaps = "BLACK KNIGHT";
        Pronoun = "her";
        break;
        default:
        ClassMention = "Warrior";
        ClassMentionCaps = "WARRIOR";
        Pronoun = "him";
        break;
    }

    Dialogue(Player,Hero,Aiden,false,"Well Well Well, if it isn't our esteemed " + ClassMention,"Congratulations on your arrival here.","",0);
    Dialogue(Player,Hero,Aiden,true,"Cut the bullshit Aiden","I demand the \033[95mViolet Tonic\033[0m and my Dog back","",0);
    Dialogue(Player,Aiden,Addison,false,"Brother, I think we can give "+Pronoun+" the Dog at least...","","",0);
    Dialogue(Player,Aiden,Addison,true,"Shush Addison, spare your idiocies","","",0);
    Dialogue(Player,Hero,Aiden,true,"Answer me Aiden","","",0);
    Dialogue(Player,Hero,Aiden,false,"Oh my HAVE SOME RESPECT","YOU SHALL REFER ME AS KING, UNWORTHY " + ClassMentionCaps,"",0);
    Dialogue(Player,Hero,Aiden,true,". . .","","",0);
    SlashAnim("\033[1;91m", 60000, false, true);
    Dialogue(Player,Hero,Aiden,false,"AHHH","","",500000);
    DialogueDramatic(Player,Hero,Aiden,true,"  No.","\033[1;91m","","",200000,0);
    DialogueDramatic(Player,Hero,Aiden,true,"Choose one, the sword or my demand","\033[1;91m","","",80000,0);
    Dialogue(Player,Hero,Aiden,false,"ADDISON! ADDISON!","DOG! KNIFEPOINT! NOW!","",0);
    DialogueDramatic(Player,Hero,Aiden,true,"What","","","",70000,0);
    Dialogue(Player,Aiden,Addison,false,"O-On it","","",0);
    Dialogue(Player,Addison,Dawg,false,"Woof","","",0);
    Dialogue(Player,Addison,Dawg,true,"Please don't kill brother...","I-I'll have to kill the Dog if you do","",0);
    Dialogue(Player,Hero,Aiden,false,"YOU SEEK NOT ONLY YOUR DEMANDS, BUT VEANGEANCE TOO, NO?","YOU ARE MAD THAT YOUR VILLAGE BURNED DOWN BECAUSE OF US!","",0);
    Dialogue(Player,Hero,Aiden,false,"SO YOU CHOOSE NOW!","\033[1;91mKILL ME\033[0m, GET THE \033[1;95mTONIC\033[0m, BUT ADDISON OVER THERE \033[1;91mKILLS THE DOG\033[0m","OR \033[1;93mSPARE ME\033[0m AND LEAVE WITH \033[1;93mTHE DOG ALIVE\033[0m",0);
    DialogueDramatic(Player,Hero,Aiden,false,"MAKE YOUR CHOICE COWARD","\033[1;93m","","",100000,1000000);
}

void DE_KingsBattleBegin(Entity Player){
    string ClassMention;
    string Pronoun;
    switch (Player.Misc.Class){
        case Gladiator:
        ClassMention = "GLADIATOR";
        Pronoun = "sir";
        break;
        case Wanderer:
        ClassMention = "WANDERER";
        Pronoun = "ma'am";
        break;
        case Berserker:
        ClassMention = "BERSERKER";
        Pronoun = "sir";
        break;
        case BlackKnight:
        ClassMention = "BLACK KNIGHT";
        Pronoun = "ma'am";
        break;
        default:
        ClassMention = "SCOUNDREL";
        Pronoun = "sir";
        break;
    }

    Dialogue(Player,Hero,Aiden,true,". . .","","",0);
    Dialogue(Player,Hero,Aiden,true,"I'll spare you","","",0);
    Dialogue(Player,Hero,Aiden,false,"What?","","",0);
    Dialogue(Player,Hero,Addison,true,"Addison, let go of the dog","","",0);
    Dialogue(Player,Addison,Dawg,true,"Y-yes "+Pronoun+"...","","",0);
    Dialogue(Player,Dawg,Addison,true,"Arf","","",0);
    Dialogue(Player,Hero,Dawg,true,"Good boy...","I'll be taking the \033[95mTonic\033[0m aswell","",0);
    Dialogue(Player,Aiden,Hero,false,"\033[90m(You take the \033[95mViolet Tonic\033[90m from under the throne)","","",0);
    Dialogue(Player,Aiden,Hero,true,"H-How did you know that-","","",0);
    Dialogue(Player,Aiden,Hero,false,"A certain \033[95mWitch\033[0m told me","","",0);
    Dialogue(Player,Aiden,Hero,true,"Damn you...","","",0);
    Dialogue(Player,Dawg,Hero,false,"\033[90m(You take the \033[95mViolet Tonic\033[90m and your trusty Dog with you)\033[0m","\033[90m(Your job here is done)\033[0m","",0);
    Dialogue(Player,Dawg,Hero,false,"\033[90m(You leave for-\033[0m","","",600000);
    SlashAnim("\033[1;93m", 60000, true, true);
    Dialogue(Player,Aiden,Hero,false,"AHGK","","",600000);
    Dialogue(Player,Hero,Aiden,false,"DO YOU REALLY THINK WE'LL LET YOU LEAVE AFTER THIS THREAT AND WITH THE \033[95mTONIC\033[0m?!","THAT WE'LL LET YOU LEAVE UNPUNISHED?!","",0);
    Dialogue(Player,Aiden,Addison,false,"Brother...","We needn't start another fight-","",0);
    Dialogue(Player,Aiden,Addison,true,"SHUT UP ADDISON","DRINK SOME OF IT","",0);
    Dialogue(Player,Hero,Aiden,true,"\033[90m(Aiden snatches the \033[95mViolet Tonic\033[90m and takes a sip from it and hands it to Addison,\033[0m","\033[90m who drinks aswell)\033[0m","",0);
    Dialogue(Player,Hero,Addison,false,"Tastes bad...","Feels bad...","I don't want to do this...",0);
    Dialogue(Player,Hero,Aiden,false,"AHAHAHAHAHAAHAAHAHAHHAHAHAHAHAHHAHAHHAHAHAHAHAHHAAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHHAAAHAHAH","FEELS BAD?! THIS IS POWER!","",0);
    DialogueDramatic(Player,Hero,Aiden,false,"DIE " + ClassMention + ", DIE!!!","\033[1;93m","","",100000,1000000);

    KingsIncomingUI();
}
void DE_KingsBattleAidenDeath(Entity Player){
    Dialogue(Player,Hero,Addison,false,"Brother...","Brother please wake up","...",0);
    Dialogue(Player,Aiden_dead,Addison,true,"","","",0);
    Dialogue(Player,Aiden_dead,Addison,false,"... I see","Just do what he told you Addison, just do it, ","\"If I die, drink the rest of the Tonic\"...",0);
    Dialogue(Player,Hero,Addison,true,"\033[90m(Addison drinks the rest of the \033[95mViolet Tonic\033[90m hesitantly, not leaving a single drop left)\033[0m","","",0);
    Dialogue(Player,Hero,Addison,false,"I'm afraid Brother...","But I'll do this","I'll do this for you",0);
    DialogueDramatic(Player,Hero,Addison_power,false,"I will AVENGE YOU","\033[1;93m","","",120000,1000000);
    KingAddisonIncomingUI();
}
void DE_KingsBattleAddisonDeath(Entity Player){
    Dialogue(Player,Hero,Aiden,false,"ADDISON!?","ADDISON TALK TO ME","",0);
    Dialogue(Player,Addison_dead,Aiden,true,"","","",0);
    Dialogue(Player,Addison_dead,Aiden,false,"oh my god","you are FUCKING USELESS","",0);
    Dialogue(Player,Hero,Aiden,false,"FINE GOD DAMN IT","I'LL DO IT MYSELF","",0);
    Dialogue(Player,Hero,Aiden,true,"\033[90m(Aiden drinks the rest of the \033[95mViolet Tonic\033[90m, not leaving a single drop left)\033[0m","","",0);
    DialogueDramatic(Player,Hero,Aiden_power,false,"TO HELL WITH YOU","\033[1;93m","","",120000,1000000);
    KingAidenIncomingUI();
}
void DE_KingsBattleAidenFinalDeath(Entity Player){
    Dialogue(Player,Hero,Aiden_power,false,". . .","","",0);
    Dialogue(Player,Hero,Aiden_power,false,"Oh","","",0);
    Dialogue(Player,Hero,Aiden_power,true,"That's right...","Beat you both","",0);
    Dialogue(Player,Hero,Aiden_power,false,"Drats, you bastard...","","",0);
    Dialogue(Player,Hero,Aiden_power,true,"Heh","","",0);
    DialogueDramatic(Player,Hero,Aiden_power,false,"Damn...","","","",120000,0);
    DialogueDramatic(Player,Hero,Aiden,false,"You...","","","",120000,0);
    DialogueDramatic(Player,Hero,Aiden_dead,false,Player.Name + "...","","","",200000,0);
    Dialogue(Player,Hero,Aiden_dead,true,"","","",0);
}
void DE_KingsBattleAddisonFinalDeath(Entity Player){
    Dialogue(Player,Hero,Addison_power,false,". . .","","",0);
    Dialogue(Player,Hero,Addison_power,false,"I-I see","","",0);
    Dialogue(Player,Hero,Addison_power,true,"That's right...","Beat you both","",0);
    Dialogue(Player,Hero,Addison_power,false,"That's okay, you fought well","We deserved to die...","",0);
    Dialogue(Player,Hero,Addison_power,true,"Your humbleness is honorable...","I respect it","",0);
    Dialogue(Player,Hero,Addison_power,false,"Ha ha...","Thank you","",0);
    DialogueDramatic(Player,Hero,Addison_power,false,"Live...","","","",120000,0);
    DialogueDramatic(Player,Hero,Addison,false,"On...","","","",120000,0);
    DialogueDramatic(Player,Hero,Addison_dead,false,Player.Name + "...","","","",200000,0);
    Dialogue(Player,Hero,Addison_dead,true,"","","",0);
}


void DE_RandomFallenTalk(Entity Player){
    int Random = rand() % 20 + 1;

    switch (Random){
        case 1:
        Dialogue(Player,Hero,Fallen,false,"You will die before you know it...","","",0);
        break;

        case 2:
        Dialogue(Player,Hero,Fallen,false,"Back off before it's too late...","","",0);
        break;

        case 3:
        Dialogue(Player,Hero,Fallen,false,"It is unstopable...","","",0);
        break;

        case 4:
        Dialogue(Player,Hero,Fallen,false,"Just let go...","","",0);
        break;

        case 5:
        Dialogue(Player,Hero,Fallen,false,"The hunt will end soon...","","",0);
        break;

        case 6:
        Dialogue(Player,Hero,Fallen,false,"You can't defeat it...","","",0);
        break;

        case 7:
        Dialogue(Player,Hero,Fallen,false,"It is merciless...","","",0);
        break;

        case 8:
        Dialogue(Player,Hero,Fallen,false,"It is unhuman...","","",0);
        break;

        case 9:
        Dialogue(Player,Hero,Fallen,false,"That thing... scares me...","","",0);
        break;

        case 10:
        Dialogue(Player,Hero,Fallen,false,"You should be afraid...","","",0);
        break;

        case 11:
        Dialogue(Player,Hero,Fallen,false,"Your time here is running out...","","",0);
        break;

        case 12:
        Dialogue(Player,Hero,Fallen,false,"It's not worth the risk...","","",0);
        break;

        case 13:
        Dialogue(Player,Hero,Fallen,false,"It is surreal...","","",0);
        break;

        case 14:
        Dialogue(Player,Hero,Fallen,false,"No one can beat it...","","",0);
        break;

        case 15:
        Dialogue(Player,Hero,Fallen,false,"It has never been vanquished before...","","",0);
        break;

        case 16:
        Dialogue(Player,Hero,Fallen,false,"Save yourself...","","",0);
        break;

        case 17:
        Dialogue(Player,Hero,Fallen,false,"It's an unfair fight...","","",0);
        break;

        case 18:
        Dialogue(Player,Hero,Fallen,false,"Give up...","","",0);
        break;

        case 19:
        Dialogue(Player,Hero,Fallen,false,"It's not worth it...","","",0);
        break;

        case 20:
        Dialogue(Player,Hero,Fallen,false,"You too, will be doomed...","","",0);
        break;
    }
}

void DE_ChampionBattleBegin(Entity Player){
    Dialogue(Player,Hero,Champion,false,"\033[1;95m","\t\t\t\t\t\t. . .","\033[0m",0);
    Dialogue(Player,Hero,Champion,false,"\033[1;95m","\t\t\t\t\t\tYou...","\033[0m",0);
    Dialogue(Player,Hero,Champion,false,"\033[1;95m","Are you this decade's final opponent?","\033[0m",0);

    DialogueChoice(Player,Hero,Champion,false, "That would be me", "Perhaps", "I challenge you", Chance);
    switch (Chance){
        case 1:
        Dialogue(Player,Hero,Champion,true,"That would be me, yes","","",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Very Well","\033[0m",0);
        break;

        case 2:
        Dialogue(Player,Hero,Champion,true,"Perhaps, perhaps not","","",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Don't act so foolishly in front of a God","\033[0m",0);
        break;

        case 3:
        Dialogue(Player,Hero,Champion,true,"I challenge you for this final fight,\033[1;95m Champion\033[0m","","",0);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Don't get cocky, Warrior","\033[0m",0);
        break;
    }
    Dialogue(Player,Hero,Champion,false,"\033[1;95m","Now...","\033[0m",0);
    Dialogue(Player,Hero,Champion,false,"\033[1;95m","Are you ready?","\033[0m",0);

    DialogueChoice(Player,Hero,Champion,false, "I'm ready", "Not yet", "", Chance);
    switch (Chance){
        case 1:
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","Good","\033[0m",0);
        DialogueDramatic(Player,Hero,Champion,false,"","","Then let the Battles begin","\033[1;95m",100000,1200000);
        break;

        case 2:
       Dialogue(Player,Hero,Champion,false,"\033[1;95m","That's too bad, for you","\033[0m",0);
       DialogueDramatic(Player,Hero,Champion,false,"","","Let the Battles begin","\033[1;95m",100000,1200000);
        break;
    }
}
void DE_ChampionBattleDefeated(Entity Player){
    DialogueDramatic(Player,Hero,Champion,false,"","",". . .","\033[1;95m",150000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","What","\033[1;95m",100000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","Impossible","\033[1;95m",100000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","You can't...","\033[1;95m",100000,800000);
    DialogueDramatic(Player,Hero,Champion,false,"","","You...","\033[1;95m",120000,600000);
    DialogueDramatic(Player,Hero,Champion,false,"","","YOU","\033[1;95m",120000,300000);
    for (int l = 8; l > 0; l--){
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);

        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);

        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAEEHHHHHHHHEHHHH","\033[0m",1);
        Dialogue(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAEEHHHHHHHHEHHHH","\033[0m",3500 * l);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        DialogueWhite(Player,Hero,Champion,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);

        if (l <= 3){
            Dialogue(Player,Hero,Nochar,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAEEHHHHHHHHEHHHH","\033[0m",1);
        Dialogue(Player,Hero,Nochar,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAEEHHHHHHHHEHHHH","\033[0m",3500 * l);
        DialogueWhite(Player,Hero,Nochar,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",1);
        DialogueWhite(Player,Hero,Nochar,false,"\033[1;95m","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEHHHHHHHHEHHHH","\033[0m",3500 * l);

        }
    }
    for (int l = 0; l < 5; l++){
        for(int i = 0; i < 300; i++){
            cout << "\033[47m                                            \033[0m";
        }
        usleep(50000);
        clear();
        usleep(50000);
    }
}
void DE_ChampionNoraDeath(Entity Player){
    DialogueWhite(Player,Hero,Nochar,false,"","","",1);
    DialogueWhite(Player,Hero,Nochar,true,"","","",0);
    DialogueWhite(Player,Hero,Nochar,true,". . .","","",0);
    DialogueWhite(Player,Hero,Nochar,true,"Hello?","","",0);
    DialogueWhite(Player,Hero,Nochar,true,"Is anyone there?","","",0);
    DialogueWhite(Player,Hero,Nora,false,". . .","","",0);
    DialogueWhite(Player,Hero,Nora,false,"You vanquished me","","",0);
    DialogueWhite(Player,Hero,Nora,true,"Oh, uh..","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Thank you","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Being trapped by such power was insuferable","","",0);
    DialogueWhite(Player,Hero,Nora,false,"I was living a never ending nightmare every day inside the shell of a \"Champion\"","","",0);
    DialogueWhite(Player,Hero,Nora,false,"But now, now I'm free","Now I can rest","Now I can...",0);
    DialogueWhite(Player,Hero,Nora,false,"Now I can die in peace","","",0);
    DialogueWhite(Player,Hero,Nora,true,"You're, welcome","I suppose","",0);
    DialogueWhite(Player,Hero,Nora,false,"Yes,","Thank you","",0);
    DialogueWhite(Player,Hero,Nora,false,"You killed me, so...","That makes you the second Champion, no?","",0);
    DialogueWhite(Player,Hero,Nora,true,"Correct","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Hmm....","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Whatever you do, don't drink the \033[35mprize Tonic\033[0m","","",0);
    DialogueWhite(Player,Hero,Nora,true,"The \033[35mViolet Tonic\033[0m?","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Yes, you saw what happened to me","Please don't commit the same mistake","",0);
    DialogueWhite(Player,Hero,Nora,true,"Alright","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Very well,","I think we're done here","",0);
    DialogueWhite(Player,Hero,Nora,false,"You have my eternal gratitude","Farewell, victorious Warrior","",0);
    DialogueWhite(Player,Hero,Nora,true,"Farew-","","",400000);
    Dialogue(Player,Hero,Nochar,true,"","","",1);
    Dialogue(Player,Hero,Nochar,true,"","","",100000);
    for (int l = 0; l < 3; l++){
    DialogueWhite(Player,Hero,Nochar,true,"","","",1);
    DialogueWhite(Player,Hero,Nochar,true,"","","",100000);
    Dialogue(Player,Hero,Nochar,true,"","","",1);
    Dialogue(Player,Hero,Nochar,true,"","","",100000);
    }
    Dialogue(Player,Hero,Nochar,true,"","","",800000);
    Dialogue(Player,Hero,Nochar,true,". . .","","",0);
    Dialogue(Player,Hero,Nochar,true,"\033[90m(The arena is scattered with desmembered tentacles and remains of the\033[1;95m Champion\033[90m)","","\033[0m",0);
    Dialogue(Player,Hero,Nochar,true,"\033[90m(You walked away to claim your prize)","","\033[0m",0);
}
void DE_VioletTonicAwarding(Entity& Player){
    string ClassMention;
    switch (Player.Misc.Class){
        case Gladiator:
        ClassMention = "Gladiator";
        break;
        case Wanderer:
        ClassMention = "Wanderer";
        break;
        case Berserker:
        ClassMention = "Berserker";
        break;
        case BlackKnight:
        ClassMention = "Black Knight";
        break;
        default:
        ClassMention = "Warrior";
        break;
    }

    int Choice = 0;

    Dialogue(Player,Hero,Nochar,true,"\033[90m(The crowd cheers you on excitedly from your impossible Victory)\033[0m","\033[90m(You're filled with praise and pride)\033[0m","",0);
    Dialogue(Player,Hero,Aiden,true,"\033[90m(The \033[93mTwin Kings\033[90m approach to congratulate you)\033[0m","","",0);
    Dialogue(Player,Hero,Aiden,false,"Congratulations on your Accomplishment " + ClassMention,"You achieved something thought to be impossible!","",0);
    Dialogue(Player,Aiden,Addison,false,"Yes, yes. Congratulations Warrior","","",0);
    Dialogue(Player,Hero,Aiden,false,"It's been a while since we had a new Champion","Addison! How long has it been since the last champion?","",0);
    Dialogue(Player,Aiden,Addison,false,"Oh uh, Hmmm","It's been... 5 decades, Brother","He's our second Champion ever, actually",0);
    Dialogue(Player,Hero,Aiden,false,"Oh, really?","Well anyways, I believe this... Canine creature, is yours","Since you Won and I don't see any use for it, you may keep it again",0);
    Dialogue(Player,Hero,Dawg,false,"Arf","","",0);
    Dialogue(Player,Hero,Dawg,true,"OHH","DOG!","",0);
    DialogueChoice(Player,Hero,Dawg,true,"Pet the Dog","","",Choice);
    Dialogue(Player,Hero,Dawg,true,"\033[90m(You pet your trusty Dog, happy to have him back)\033[0m","","",0);
    Dialogue(Player,Hero,Dawg,false,"Woof","","",0);
    Dialogue(Player,Hero,Aiden,false,"Good dog, Good dog...","Let us wrap this up quickly, here's the \033[95mPromised Prize\033[0m","And now let us start the ceremony",0);
    Dialogue(Player,Hero,Nochar,true,"\033[90m(\033[93mKing Aiden\033[90m puts the \033[95mViolet Tonic\033[90m in your \033[96mItems Bag\033[90m)\033[0m","","",0);
    Player.ItemBag.Item1 = ItmVioletTonic;
    Player.ItemBag.Item2 = NoItem;
    Player.ItemBag.Item3 = NoItem;
    Player.ItemBag.Item4 = NoItem;
    Player.ItemBag.Item5 = NoItem;
    Player.Misc.Itemslots = 0;
    Dialogue(Player,Aiden,Nochar,true,"DEAR AUDIENCE PRESENT TODAY IN THIS COLOSSEUM","I PRESENT TO YOU OUR NEWEST CHAMPION IN 50 YEARS","",0);
    DialogueDramatic(Player,Aiden,Hero,true,"GIVE A ROUND OF APPLAUSES FOR " + Player.Name + "!!!","\033[1;93m","","",90000,0);
    DialogueNoFace(Player,Nochar,Nochar,true,"And with this victory, "+Player.Name+"'s freedom and its pet Dog were returned","","",0);
    DialogueNoFace(Player,Nochar,Nochar,true,Player.Name+" packed its remaining stuff, played with the Dog, and headed to the","Colosseum's Entrance to leave, ready to start over its life again","",0);
    DialogueNoFace(Player,Nochar,Nochar,true,"THE END","","",0);
}

void DE_WitchEndingBattleBegin(Entity& Player){
    int Choice = 0;
    DialogueNoFace(Player,Nochar,Nochar,true,"","","",0);
    Dialogue(Player,Hero,Nochar,true,"","","",0);
    Dialogue(Player,Hero,Witch_down,true,"\033[90m(You spot the Witch, standing at the entrance while looking at the ground)\033[0m","","",0);
    Dialogue(Player,Hero,Witch_down,true,"Witch, I'm glad to find you here","I wanted to thank you for your assistance, and give you the \033[95mViolet Tonic\033[0m as part of","our deal",0);
    Dialogue(Player,Hero,Witch_down,false,". . .","","",0);
    Dialogue(Player,Hero,Witch,false,"I no longer need it, bastard","","",0);
    Dialogue(Player,Hero,Witch,true,"What?","","",0);
    Dialogue(Player,Hero,Witch_down,false,"I told you I wanted to use it to cure the \033[95mChampion\033[0m, but you killed her now","So it's no longer of any use to me...","",0);
    Dialogue(Player,Hero,Witch_down,true,"Why would you even want to cure the \033[95mChampion\033[0m?","","",0);
    Dialogue(Player,Hero,Witch,false,"Because... because she was my daughter god damn it...","","",0);
    Dialogue(Player,Hero,Witch_down,true,". . .","","",0);
    Dialogue(Player,Hero,Witch,false,"Listen,","Aren't you at least sorry for what you've done?","Now that you know this?",0);
    DialogueChoice(Player,Hero,Witch,true,"Yes, I'm sorry","No, I'm not","",Choice);
    switch (Choice){
        case 1:
        Dialogue(Player,Hero,Witch_down,false,". . . Good","I'm relieved you said that","",0);
        Dialogue(Player,Hero,Witch,false,"But I can't let you leave just like that","You don't deserve freedom","",0);
        DialogueDramatic(Player,Hero,Witch_fierce,false,"So fall, damned Warrior","\033[1;96m","","",160000,1000000);
        break;

        case 2:
        Dialogue(Player,Hero,Witch_down,false,". . . I see","I guess I was too naive to trust you","",0);
        Dialogue(Player,Hero,Witch,false,"Very well then","","",0);
        DialogueDramatic(Player,Hero,Witch_fierce,false,"May you fall, damned Warrior","\033[1;96m","","",160000,1000000);
        break;
    }
    WitchIncomingUI();
}


void ENDING_TrueEnding(Entity& Player){


    THEENDscreen("\033[1;92m");
    Credits();
}
void ENDING_KingEnding(Entity& Player){
    Dialogue(Player,Hero,Dawg,false,"Arf?","","",0);
    SlashAnim("\033[1;93m", 60000, true, true);
    usleep(80000);
    Dialogue(Player,Hero,Dawg_dead,false," ","","",0);
    Dialogue(Player,Hero,Dawg_dead,true,"No...","","",0);
    Dialogue(Player,Hero,Dawg_dead,false," ","","",0);

    THEENDscreen("\033[1;93m");
    Credits();
}
void ENDING_ChampionEnding(Entity& Player){
    int Choice;
    Dialogue(Player,Hero_Champ,Witch_broken,false,". . .","","",0);
    Dialogue(Player,Hero_Champ,Witch_broken,false,"Damn it...","I didn't think you'd drink it...","",0);
    Dialogue(Player,Hero_Champ,Witch_broken,true,"","\033[1;95m. . .\033[0m","",0);
    Dialogue(Player,Hero_Champ,Witch_broken,false,"You are doomed for good now","You unhuman piece of crap...","",0);
    Dialogue(Player,Hero_Champ,Witch_broken,true,"","\033[1;95m. . .\033[0m","",0);
    DialogueDramatic(Player,Hero_Champ,Witch_broken,false,"God damn you "+Player.Name+"...","","","",200000,1000000);
    Dialogue(Player,Hero_Champ,Nochar,true,"\033[90m(You watch the Witch, falling down on her knee as she withers away)\033[0m","\033[90m(You feel nothing)\033[0m","",0);
    Dialogue(Player,Hero_Champ,Nochar,true,"\033[90m(Suddenly, you hear a couple voices coming your way)\033[0m","","",0);
    Dialogue(Player,Hero_Champ,Aiden,false,"Well well well, if it isn't our esteemed Champion... hmm...","","",0);
    Dialogue(Player,Aiden,Addison,false,"Champion " + Player.Name + ", brother","","",0);
    Dialogue(Player,Aiden,Addison,true,"I know Addison, I know","","",0);
    Dialogue(Player,Hero_Champ,Aiden,true,"","\033[1;95mMore... I want more...\033[0m","",0);
    Dialogue(Player,Hero_Champ,Aiden,false,"We know you do,","So come stay with us, obey us and we'll let you in on the next tournament","",0);
    Dialogue(Player,Aiden,Addison,false,"W-Which in turn will let you aquire the next \033[95mViolet Tonic\033[0m, since you'll likely win","","",0);
    Dialogue(Player,Hero_Champ,Aiden,false,"Exactly","So, do we have ourselves a deal?","",0);
    Dialogue(Player,Hero_Champ,Aiden,true,"","\033[1;95m. . .\033[0m","",0);
    DialogueChoice(Player,Hero_Champ,Aiden,true,"\033[1;95mYes\033[0m","\033[1;95mYes\033[0m","\033[1;95mYes\033[0m",Choice);
    Dialogue(Player,Hero_Champ,Aiden,true,"","\033[1;95mYes...\033[0m","",0);
    Dialogue(Player,Hero_Champ,Aiden,false,"Good","","",0);
    DialogueNoFace(Player,Nochar,Nochar,true,"After this sudden turn of events, "+Player.Name+"'s freedom quickly disapeared as it lost","itself with the Tonic and is now under the Twin King's orders","",0);
    DialogueNoFace(Player,Nochar,Nochar,true,"And time went on for the \"new\" " + Player.Name,"Who ended up becoming nothing less than a Beast, a Slave and a Fool of itself","",0);
    THEENDscreen("\033[1;95m");
    Credits();
}

void EE_Starwalker(Entity Player){
    Dialogue(Player,Hero,Starwalker,false,"These Gladiators are \033[93mpissing\033[0m me off","","",0);
    Dialogue(Player,Hero,Starwalker,false,"I'm the original","","",0);
    Dialogue(Player,Hero,Starwalker,false,"","","",0);
    Dialogue(Player,Hero,Starwalker,false,"","","",0);
    Dialogue(Player,Hero,Starwalker,false,"\033[1;93mStarwalker\033[0m","","",0);
}

//-------------------MINIGAMES-----------------------------------------------------------------------------------------------------------------------------------||
// - -LOCKPICK- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||
string Lockpicktick(bool option, string number){
    if (option == true){
        return "\033[1;93m" + number + "\033[0m";
    }else{
        return "\033[90m" + number + "\033[0m";
    }
    return "ER";
}

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
void LockpickGame1(bool& unlocked){
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
                unlocked = true;
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
    clear();
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
void LockpickGame2(bool& unlocked){
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
                unlocked = true;
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
    clear();
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
void LockpickGame3(bool& unlocked){
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
                unlocked = true;
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
    clear();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -||

// Old Shop Design
//           +-'-.-'-.-'-.-'-+                                                        +-------------+                 
//           | SHUFFLE TIME! |                          +-----------+-----------+      Savings: 9g                   
//           +-.-'-.-'-.-'-.-+                          |  7 - Sell | 8 - Stats |     +-------------+                
//                                                      +-----------+-----------+        Tokens: 3                    
//                                           TAGS:                                    +-------------+                
//UP Cards:                              +---------------------------------------------------------------------------+
//   .-------.   .-------.   .-------.    (4) - Item - Name (Description) - 100g        
//   |       |   |       |   |       |   *---------------------------------------------------------------------------*
//   |       |   |       |   |       |    (5) - Item - Name (Description) - 100g      
//   |       |   |       |   |       |   *---------------------------------------------------------------------------*
//   |Rnk:   |   |Rnk:   |   |Rnk:   |    (6) - Item - Name (Description) - 100g      
//   `-------`   `-------`   `-------`   +---------------------------------------------------------------------------+
//      (1)         (2)         (3)                                  (0) - Reroll - 3g                                
