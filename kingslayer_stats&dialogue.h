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
    Armagedon = 26
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
    ETHEREAL = 10
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

    struct TextImage{
        string Line1;
        string Line2;
        string Line3;
        string Line4;
        string Line5;
    }Image;

    Relic(RelicID id, string name, string desc, string line1, string line2, string line3, string line4, string line5){
        ID = id;
        Name = name;
        Desc = desc;
        Image.Line1 = line1;
        Image.Line2 = line2;
        Image.Line3 = line3;
        Image.Line4 = line4;
        Image.Line5 = line5;
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

//- The Entity Class - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ||

enum Classes{// Player Game Classes
    NOCLASS,
    Gladiator,
    Wanderer,
    Berserker,
    BlackKnight,
    God
};
enum EntityType{
    PLAYER1,
    PLAYER2,
    ENEMY,
    FALLEN,
    BOSS,
    CHAMPION,
    KING
};
class Entity {
    public:
        
    string Name = "ERROR";
        
    struct Miscelaneous {
        Classes Class = NOCLASS;
        uint16_t Level = 1;
        int Spellslots = 3;
        uint16_t Itemslots = 3;
        uint32_t XPThreshold = 100;
        float XPMult = 1;
        float GoldMult = 1;
        float ManaMult = 1;
        float PriceMult = 1;
        float DefMult = 2;
        float DefMana = 0.15;
        int NameLenght;
        EntityType Type;
    }Misc;
        
    struct Stats {
        int MAXHP, HP;
        int MAXMANA, MANA;
        float ATK;
        float MA;
        float AC, DEF;
        float CRIT;
        float CRITMULT = 2;
        float DODGE;
        int Gold;
        int XP = 0;
        int Kindness = 0;
    }Stat;
        
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
        
    Entity (int maxhp, int maxmana, float atk, float ma, float ac, float crit, float dodge, int gold, EntityType type, string name){
        Stat.MAXHP = maxhp;
        Stat.HP = maxhp;
        Stat.MAXMANA = maxmana;
        Stat.MANA = maxmana;
        Stat.ATK = atk;
        Stat.MA = ma;
        Stat.AC = ac;
        Stat.DEF = ac / 2;
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
    Witch,
    Witch_down,
    Sogro_prison,
    Prisoner,
    Prisoner_Free,
    Addison,
    Aiden,
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
       Cside.PortraitLine[13] = "     |  .'   .    \033[1;91m  _-'  .'   \033[37m |   |    ";
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
        Cside.PortraitLine[7] = "\033[90m            | .-'     |     |           ";
        Cside.PortraitLine[8] = "\033[90m            | |       \\     |           ";
        Cside.PortraitLine[9] = "\033[90m            | |        |     \\          ";
       Cside.PortraitLine[10] = "\033[90m            |  \\_      \\      |         ";
       Cside.PortraitLine[11] = "\033[90m             \\   |     |      |         ";
       Cside.PortraitLine[12] = "         \033[92m    -\033[90m|  |  \033[92m .-\033[90m/   |\033[92m'-:\033[90m         ";
       Cside.PortraitLine[13] = "          \033[92m.''\033[90m/  / \033[92m''' \033[90m/   /   \033[92m ' \033[90m       ";
       Cside.PortraitLine[14] = "        \033[92m ' \033[90m  |  |     |   |    \033[92m '  \033[90m     ";
       Cside.PortraitLine[15] = "        \033[92m' \033[90m  /  /      /   /     \033[92m ' \033[90m     ";
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
        DialogueDramatic(Player,Hero,Champion,false,"","","Then let the Battles begin","\033[1;95m",150000,1200000);
        break;

        case 2:
       Dialogue(Player,Hero,Champion,false,"\033[1;95m","That's too bad, for you","\033[0m",0);
       DialogueDramatic(Player,Hero,Champion,false,"","","Let the Battles begin","\033[1;95m",150000,1200000);
        break;
    }
}
void DE_ChampionBattleDefeated(Entity Player){
    DialogueDramatic(Player,Hero,Champion,false,"","",". . .","\033[1;95m",150000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","What","\033[1;95m",120000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","Impossible","\033[1;95m",120000,0);
    DialogueDramatic(Player,Hero,Champion,false,"","","You can't...","\033[1;95m",120000,800000);
    DialogueDramatic(Player,Hero,Champion,false,"","","You...","\033[1;95m",120000,700000);
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
    DialogueWhite(Player,Hero,Nora,false,". . .","Now I can die in peace","",0);
    DialogueWhite(Player,Hero,Nora,true,"You're... welcome","I suppose","",0);
    DialogueWhite(Player,Hero,Nora,false,"Yes, yes","Thank you","",0);
    DialogueWhite(Player,Hero,Nora,false,"You killed me, so...","That makes you the second Champion, no?","",0);
    DialogueWhite(Player,Hero,Nora,true,"Correct","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Hmm....","","",0);
    DialogueWhite(Player,Hero,Nora,false,"Whatever you do, don't drink the prize Tonic","","",0);
    DialogueWhite(Player,Hero,Nora,true,"The Violet Tonic?","","",0);
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
//
//\033[1;XX = Bold Text
