#ifndef CW2_H
#define CW2_H

// Constants for gameplay mechanics
#define MaximumHp 40
#define SWORD_DAMAGE 3
#define SPEAR_DAMAGE 10
#define CROSS_DAMAGE 8
#define MaximumInventory 3

typedef struct adventureGame {
    char command[1000];
    char lastCommand[1000];         // Command typed by the user
    int monster;                      // Indicates the presence of a monster
    int room;                         // The room the player is in
    int playerHP;                     // Player's health points
    int playerXP;                     // Player's experience points
    int hasSword;                     // Flag for having the sword
    int hasSpear;                     // Flag for having the silver spear
    int hasCross;                     // Flag for having the diamond cross
    const char *rooms[13];            // Descriptions of rooms
    const char *lookArray[13];        // Descriptions when looking
    const char *moveArray[13][4];     // Movement descriptions
    const int moveToArray[13][4];     // Room connectivity
    const char *monsterArray[7];      // Monster names
    int monsterLoc[7];                // Monster locations
    int monsterStatusArray[7];        // Monster health/status
    int N_artifact;                   // Number of artifacts
    const char *artifact[9];          // Artifact names
    int artifactLoc[9];               // Artifact locations
    int inventory[MaximumInventory]; // Player's inventory
    int inventoryCount;                // Number of items in inventory
} adventureGame;

// Function declarations
int combatAdvantage(adventureGame *ag, int monsterIndex);
void useFood(adventureGame *ag);
void useMedpack(adventureGame *ag);
void useElixir(adventureGame *ag);
int helpCommands(adventureGame *ag, const char *command);
void displayInventory(adventureGame *ag);
int processGet(adventureGame *ag, const char *item);
int processDrop(adventureGame *ag, const char *item);
int processCommand(adventureGame *ag);
int processLook(adventureGame *ag);
int processMovement(adventureGame *ag);
int processKillMonster(adventureGame *ag, const char *specificMonster);
int unlockRoom10(adventureGame *ag);
int unlockRoom13(adventureGame *ag);
int hasKey(adventureGame *ag, const char *key);

#endif // ADVENTUREGAME_H

