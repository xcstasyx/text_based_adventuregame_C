#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CW2.h"
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

int unlockRoom10(adventureGame *ag);
int unlockRoom13(adventureGame *ag);

// Function to process a command entered by the player
int processCommand(adventureGame *ag) {
    // Remove newline character from input
ag->command[strcspn(ag->command, "\n")] = 0;

if (strlen(ag->command) == 0) {
    printf("Unknown command.\n");
    return 1; // Indicate failure
}

    // Update lastCommand with the current command
strcpy(ag->lastCommand, ag->command);

    if (strncmp(ag->command, "help", 4) == 0) {
        helpCommands(ag, ag->command); // Pass ag->command as the argument
        return 1;

    } else if (strcmp(ag->command, "exit") == 0) {
        printf("Exiting the game.\n");
        printf("Game over. Your score: %d\n", ag->playerXP);
        exit(0); // Exit the game

    } else if (strcmp(ag->command, "hp") == 0) {
        printf("Current HP: %d\n", ag->playerHP);
        return 1;

    } else if (strcmp(ag->command, "xp") == 0) {
        printf("Current XP: %d\n", ag->playerXP);
        return 1;

    } else if (ag->room == 4 && hasKey(ag, "Bronze Key") && (strcasecmp(ag->command, "unlock door") == 0)) {
        return unlockRoom10(ag);

    } else if (ag->room == 11 && hasKey(ag, "Copper Key") && (strcasecmp(ag->command, "unlock door") == 0)) {
        return unlockRoom13(ag);

    } else if ((strncmp(ag->command, "inventory", 9) == 0) || (strncmp(ag->command, "i", 1) == 0)) {
        displayInventory(ag);
        return 1;

    } else if (strncasecmp(ag->command, "get ", 4) == 0) {
        const char *itemName = ag->command + 4;
        return processGet(ag, itemName);

    } else if ((strcmp(ag->command, "look") == 0) || (strcmp(ag->command, "l") == 0)) {
        processLook(ag);
        return 1;

    } else if (strncmp(ag->command, "drop ", 5) == 0) {
        const char *itemName = ag->command + 5;
        processDrop(ag, itemName);
        return 1;

    } else if ((strcasecmp(ag->command, "killMonster") == 0) || (strncmp(ag->command, "km", 2) == 0)) {
        return processKillMonster(ag, NULL);

    } else if (strcasecmp(ag->command, "kill zombie") == 0) {
        return processKillMonster(ag, "Zombie");

    } else if (strcasecmp(ag->command, "kill werewolf") == 0) {
        return processKillMonster(ag, "Werewolf");

    } else if (strcasecmp(ag->command, "kill dragon") == 0) {
        return processKillMonster(ag, "Dragon");

    } else if (strcasecmp(ag->command, "kill dracula") == 0) {
        return processKillMonster(ag, "Dracula");

    } else if (strcasecmp(ag->command, "kill bride of dracula") == 0) {
        return processKillMonster(ag, "Bride of Dracula");

    } else if (strcasecmp(ag->command, "kill lizardman") == 0) {
        return processKillMonster(ag, "Lizardman");

    } else if (strcasecmp(ag->command, "eat food") == 0) {
        useFood(ag);
        return 1;

    } else if (strcasecmp(ag->command, "use medpack") == 0) {
        useMedpack(ag);
        return 1;

    } else if (strcasecmp(ag->command, "drink elixir") == 0) {
        useElixir(ag);
        return 1;

    } else if (processMovement(ag)) {
        return 1;
    }
}

int processLook(adventureGame *ag) {
    printf("%s\n", ag->lookArray[ag->room]); // Print the main room description

    // Check if there is a monster in the current room
    int monsterIndex = -1;
    for (int i = 0; i < sizeof(ag->monsterLoc) / sizeof(ag->monsterLoc[0]); i++) {
        if (ag->monsterLoc[i] == ag->room) {
            monsterIndex = i;
            break;
        }
    }

    // Process any monster in the room
    if (monsterIndex != -1) {
        if (ag->monsterStatusArray[monsterIndex] > 0) {
            printf("Here in %s, there is a %s with %d HP here!\n\n", ag->rooms[ag->room], ag->monsterArray[monsterIndex], ag->monsterStatusArray[monsterIndex]);
        } else {
            printf("You see a dead %s lying on the ground.\n\n", ag->monsterArray[monsterIndex]);
        }
    }

    // Process any artifact that may be in the room
    for (int i = 0; i < ag->N_artifact; i++) {
        if (ag->artifactLoc[i] == ag->room) {
            printf("Look! There is a %s on the ground!\n\n", ag->artifact[i]);
        }
    }

    return 1;
}

int processMovement(adventureGame *ag){
    if((strncmp(ag->command,"north",5)==0) || (strncmp(ag->command,"n",1)==0)){
        if(ag->moveToArray[ag->room][0] != -1){
        printf("%s\n", ag->moveArray[ag->room][0]);
            ag->room = ag->moveToArray[ag->room][0];
        }
        else{
            printf("Unable to move north.\n");
        }
        return(1);
    }

    else if ((strncmp(ag->command, "south", 5) == 0) || (strncmp(ag->command, "s", 1) == 0)) {
        if (ag->room == 4) {
            int werewolfIndex = 1; // Adjust this index based on your actual werewolf index
            if (ag->monsterStatusArray[werewolfIndex] > 0) {
            printf("A fierce werewolf blocks your way to Room 10. You need to deal with the werewolf first in order to proceed!\n");
            printf("Hint: Silver Spear greatly boost your damage on the Werewolf.\n");
            return 1; // Return 1 to indicate the command was processed but unsuccessful
        }
    }
        if (ag->room == 4) {
        if (!hasKey(ag, "Bronze Key")) {
            printf("You need a bronze key to unlock this door.\n");
            return 1; // Return 1 to indicate the command was processed but unsuccessful
        }
    }
    if (ag->moveToArray[ag->room][1] != -1) {
        printf("%s\n", ag->moveArray[ag->room][1]);
        ag->room = ag->moveToArray[ag->room][1];
        return 1; // Return 1 to indicate a successful move
    } else {
        printf("Unable to move south.\n");
        return 1; // Return 1 to indicate the command was processed but unsuccessful
    }
}
    else if ((strncmp(ag->command, "east", 4) == 0) || (strncmp(ag->command, "e", 1) == 0)) {
        if (ag->room == 11) {
        if (!hasKey(ag, "Copper Key")) {
            printf("You need a copper key to unlock this door.\n");
            return 1; // Return 1 to indicate the command was processed but unsuccessful
        }
    }

    if (ag->moveToArray[ag->room][2] != -1) {
        printf("%s\n", ag->moveArray[ag->room][2]);
        ag->room = ag->moveToArray[ag->room][2];
        return 1;
    } else {
        printf("Unable to move east.\n");
        return 1;
    }
}
    else if ((strncmp(ag->command, "west", 4) == 0) || (strncmp(ag->command, "w", 1) == 0)) {
        if (ag->room == 1) {
        if (hasArtifact(ag, "Golden Chalice")) {
            printf("Congratulations! You have successfully completed the adventure!\n");
            printf("Total XP earned: %d\n", ag->playerXP);
            exit(0);  // You can handle game completion differently if needed
        }
    }

    if (ag->moveToArray[ag->room][3] != -1) {
        printf("%s\n", ag->moveArray[ag->room][3]);
        ag->room = ag->moveToArray[ag->room][3];
        return 1;  // Return 1 to indicate the command was processed successfully
    } else {
        printf("Unable to move west.\n");
        return 1;  // Return 1 to indicate the command was processed but unsuccessful
    }
}
        return(1);
    }

int hasKey(adventureGame *ag, const char *key) {
    for (int i = 0; i < ag->inventoryCount; i++) {
        if (strcmp(ag->artifact[ag->inventory[i]], key) == 0) {
            return 1; // Key found
        }
    }
    return 0; // Key not found
}

int unlockRoom10(adventureGame *ag) {
    // Check if the door to Room 10 is locked
    if (ag->moveToArray[ag->room][1] == -1) {
        printf("You use the Bronze Key to unlock the door to Room 10!\n");

        // Create a separate array to hold the modified movement information
        int newMoveToArray[13][4];
        memcpy(newMoveToArray, ag->moveToArray, sizeof(ag->moveToArray));

        // Update the modified array to allow movement to Room 10
        newMoveToArray[ag->room][1] = 9;

        // Copy the modified array back to the original array
        memcpy(ag->moveToArray, newMoveToArray, sizeof(ag->moveToArray));

        // Inform the player about the successful unlock
        printf("The door to Room 10 is now unlocked. You can move south to Room 10.\n");

        return 1; // Return 1 to indicate the command was processed successfully
    } else {
        printf("The door is not locked.\n");
        return 1; // Return 1 to indicate the command was processed but unsuccessful
    }
}

int unlockRoom13(adventureGame *ag) {
    // Check if the door to Room 13 is locked
    if (ag->moveToArray[ag->room][2] == -1) {
        printf("You use the Copper Key to unlock the door to Room 13!\n");

        // Create a separate array to hold the modified movement information
        int newMoveToArray[13][4];
        memcpy(newMoveToArray, ag->moveToArray, sizeof(ag->moveToArray));

        // Update the modified array to allow movement to Room 13
        newMoveToArray[ag->room][2] = 12;

        // Copy the modified array back to the original array
        memcpy(ag->moveToArray, newMoveToArray, sizeof(ag->moveToArray));

        // Inform the player about the successful unlock
        printf("The door to Room 13 is now unlocked. You can move east to Room 13.\n");

        return 1; // Return 1 to indicate the command was processed successfully
    } else {
        printf("The door is not locked.\n");
        return 1; // Return 1 to indicate the command was processed but unsuccessful
    }
}

int processGet(adventureGame *ag, const char *item) {
    // Check if the item is in the current room
    int itemIndex = -1;
    for (int i = 0; i < ag->N_artifact; i++) {
        if (strcasecmp(ag->artifact[i], item) == 0) {
            itemIndex = i;
            break;
        }
    }

    // Check if the item is not in the current room
    if (itemIndex == -1 || ag->artifactLoc[itemIndex] != ag->room) {
        printf("There is no %s here.\n\n", item);
        return 1; // Item not in current room
    }

    // Check if the item has already been picked up
    for (int i = 0; i < ag->inventoryCount; i++) {
        if (ag->inventory[i] == itemIndex) {
            printf("You have already picked up the %s.\n\n", item);
            return 1; // Item already picked up
        }
    }

    if (strcasecmp(item, "Golden Chalice") == 0){
        int dragonIndex = 6;
        if (ag->room == 12 && ag->monsterStatusArray[dragonIndex] > 0){
            printf("The Dragon is guarding the Golden Chalice. Defeat him first!\n\n");
            return 1;
        }
    }

    // Check for monster-specific conditions
    if (strcasecmp(item, "Copper Key") == 0) {
        // Check if Dracula in Room 8 is defeated
        int draculaIndex = 3; // Assuming Dracula's index in the monster array is 12
        if (ag->room == 6 && ag->monsterStatusArray[draculaIndex] > 0) {
            printf("Dracula is guarding the Copper Key. Defeat him first!\n\n");
            return 1; // Cannot pick up the item
        }

        // Check if the player already has the Copper Key
        if (hasKey(ag, "Copper Key")) {
            printf("You already have the Copper Key.\n\n");
            return 1; // Cannot pick up the item
        }
    }

    if (strcasecmp(item, "Bronze Key") == 0 && ag->room == 7 && hasKey(ag, "Bronze Key")) {
        printf("You already have the Bronze Key.\n\n");
        return 1;
    }
    if (strcasecmp(item, "Diamond Cross") == 0){
        int lizardManIndex = 4;
        if (ag->room == 9 && ag->monsterStatusArray[lizardManIndex] > 0){
            printf("The Lizard Man is guarding the Diamond Cross. Defeat him first!\n\n");
            return 1; // Cannot pick up the item
        }
    }

    // Check if the player's inventory is full
    if (ag->inventoryCount >= MaximumInventory) {
        printf("You cannot carry more than 3 items. You must drop something first.\n\n");
        return 1;
    }

    // Logic for successfully picking up an item
    printf("You have picked up the %s.\n\n", item);
    ag->artifactLoc[itemIndex] = -1; // Item is now with the player, not in the room

    // Update hasSword if the player picks up the sword
    if (strcasecmp(item, "Sword") == 0) {
        ag->hasSword = 1;
        printf("You wield a Sword in your hands now! Your damage is increased by 3.\n\n");
    }

    if (strcasecmp(item, "Golden Chalice")==0){
        ag->playerXP +=50;
        printf("You have obtained the Golden Chalice. Now, return to Radiant Hall in order to gain victory!\n\n");
    }

    // Add item to inventory and increment the inventory count
    ag->inventory[ag->inventoryCount] = itemIndex;
    ag->inventoryCount++;

    return 1; // Item picked up successfully
}

int processDrop(adventureGame *ag, const char *item) {
    // First, check if the player actually has the item in their inventory
    int itemIndex = -1;
    for (int i = 0; i < ag->inventoryCount; i++) {
        if (strcasecmp(ag->artifact[ag->inventory[i]], item) == 0) {
            itemIndex = ag->inventory[i];
            break;
        }
    }

    if (itemIndex == -1) {
        printf("You do not have the %s to drop.\n\n", item);
        return 0; // Item not in inventory
    }

    // Drop the item in the current room
    printf("You have dropped the %s.\n\n", item);
    ag->artifactLoc[itemIndex] = ag->room; // Item is now in the current room

    // Remove the item from the inventory and shift the rest of the items down
    for (int i = 0; i < ag->inventoryCount - 1; i++) {
        if (ag->inventory[i] == itemIndex) {
            for (int j = i; j < ag->inventoryCount - 1; j++) {
                ag->inventory[j] = ag->inventory[j + 1];
            }
            break;
        }
    }
    ag->inventoryCount--; // Decrement the inventory count

    return 1; // Item dropped successfully
}

int combatAdvantage(adventureGame *ag, int monsterIndex) {
    int baseDamageToMonster = 2; // Base damage to monster without any artifact

    // Check for special weapon effects
    if (ag->hasSword) {
        baseDamageToMonster += SWORD_DAMAGE;
    }

    // Check for extra damage with Diamond Cross
    if (hasArtifact(ag, "Diamond Cross") && (strcmp(ag->monsterArray[monsterIndex], "Bride of Dracula") == 0 || strcmp(ag->monsterArray[monsterIndex], "Dracula") == 0)) {
        baseDamageToMonster += 1.0 * baseDamageToMonster; // Add 80% extra damage
    }

    // Check for extra damage against the werewolf with Silver Spear
    if (hasArtifact(ag, "Silver Spear") && strcmp(ag->monsterArray[monsterIndex], "Werewolf") == 0) {
        baseDamageToMonster *= 2; // Double the damage against the werewolf with Silver Spear
    }

    // Monster takes damage
    ag->monsterStatusArray[monsterIndex] -= baseDamageToMonster;
    printf("You deal %d damage to the %s.\n", baseDamageToMonster, ag->monsterArray[monsterIndex]);

    // Check if monster is defeated
    if (ag->monsterStatusArray[monsterIndex] <= 0) {
        printf("You have slain the %s!\n", ag->monsterArray[monsterIndex]);
        ag->playerXP += 10; // Award XP for killing the monster
        return 1; // Monster is defeated
    }

    // Player takes damage
    int damageToPlayer = rand() % 4 + 4;
    ag->playerHP -= damageToPlayer;
    printf("The %s deals %d damage to you.\n", ag->monsterArray[monsterIndex], damageToPlayer);

    // Check if player is defeated
    if (ag->playerHP <= 0) {
        printf("You have been defeated by the %s...\n", ag->monsterArray[monsterIndex]);
        return 0; // Player is defeated, game over
    }

    return 1; // Combat continues
}

int processKillMonster(adventureGame *ag, const char *specificMonster) {
    // Find the monster index based on the current room
    int monsterIndex = -1;

    if (specificMonster != NULL) {
        // If a specific monster is provided, find its index
        for (int i = 0; i < sizeof(ag->monsterLoc) / sizeof(ag->monsterLoc[0]); i++) {
            if (ag->monsterLoc[i] == ag->room && strcmp(ag->monsterArray[i], specificMonster) == 0) {
                monsterIndex = i;
                break;
            }
        }
    } else {
        // If no specific monster is provided, find the first monster in the room
        for (int i = 0; i < sizeof(ag->monsterLoc) / sizeof(ag->monsterLoc[0]); i++) {
            if (ag->monsterLoc[i] == ag->room) {
                monsterIndex = i;
                break;
            }
        }
    }

    if (monsterIndex == -1) {
        if (specificMonster != NULL) {
            printf("There is no %s in this room.\n", specificMonster);
        } else {
            printf("There is no monster to kill in this room.\n");
        }
        return 1; // No specific monster to kill
    }

    if (ag->monsterStatusArray[monsterIndex] > 0) {
        // Engage in combat
        if (combatAdvantage(ag, monsterIndex) == 0) {
            // Player died
            printf("Game over. Your score: %d\n", ag->playerXP);
            exit(0); // End the game
        }
    } else {
        printf("The %s is already dead\n", ag->monsterArray[monsterIndex]);
    }
    return 1;
}

void useFood(adventureGame *ag) {
    int healthGain = 15;

    // Check if there is food in the inventory
    if (ag->inventoryCount> 0) {
        ag->inventoryCount--;  // Decrease the count of food in the inventory

        ag->playerHP += healthGain;
        if (ag->playerHP > MaximumHp) {
            ag->playerHP = MaximumHp;
        }
        printf("You have eaten food and restored %d health.\n", healthGain);
    } else {
        printf("You don't have any food in your inventory.\n");
    }
}

void useMedpack(adventureGame *ag) {
    int healthGain = 20;

    if (ag->inventoryCount> 0){
        ag->inventoryCount--;  // Decrease the count of Medpack in the inventory

        ag->playerHP += healthGain;
        if (ag->playerHP > MaximumHp) {
            ag->playerHP = MaximumHp;
        }
        printf("You have use Medpack and restored %d health.\n", healthGain);
    } else {
        printf("You don't have any Medpack in your inventory.\n");
    }
}

void useElixir(adventureGame *ag) {
    int healthGain= MaximumHp;
    ag->playerHP = MaximumHp;

    if (ag->inventoryCount> 0){
        ag->inventoryCount--;  // Decrease the count of Medpack in the inventory

        ag->playerHP += healthGain;
        if (ag->playerHP > MaximumHp) {
            ag->playerHP = MaximumHp;
        }
        printf("You have drunk the Elixir and restored %d health.\n", healthGain);
    } else {
        printf("You don't have any Elixir in your inventory.\n");
    }
}

int helpCommands(adventureGame *ag, const char *command) {
    if (strncmp(command, "help", 4) == 0) {
        printf("______________________________________________________________________________________________________________________\n");
        printf("**Take not that Artifact's name can be in either Capital or Small Letter.**\n\n");
        printf("Here is a list of commands that you can use in the game:\n\n");
        printf("Movement Commands : north, n, south, s, east, e, west, w \n\n");
        printf("Look Commands : look, l \n\n");
        printf("Fight Commands : killMonster,km \n\n");
        printf("Alternate Commands : kill zombie, kill werewolf, kill dragon, kill bride of dracula, kill dracula, kill lizardman \n\n");
        printf("Get Commands : get Diamond Cross, get Sword, get Elixir, get Food, get Copper Key, get Bronze Key, get Silver Spear, get Golden Chalice, get Medpack,\n\n");
        printf("Drop Commands: drop Diamond Cross, drop Sword, drop Elixir, drop Food, drop Copper Key, drop Bronze Key, drop Silver Spear, drop Golden Chalice, drop Medpack.\n\n");
        printf("Inventory Command :inventory, i: list what the player is carrying\n\n");
        printf("Healing Commands : eat Food, drink Elixir, use Medpack\n\n");
        printf("Unlocking Door Command : unlock door\n\n");
        printf("Exit Command : exit\n");
        printf("_______________________________________________________________________________________________________________________\n");

        return 0;  // Return 0 to indicate the command hasn't been fully processed
        }
    return 1;  // Return 1 for other cases where the command is not "help"
    }

void displayInventory(adventureGame *ag) {
    printf("Inventory:\n");

    if (ag->inventoryCount == 0) {
        printf("Your inventory is empty.\n");
    } else {
        for (int i = 0; i < ag->inventoryCount; i++) {
            int itemIndex = ag->inventory[i];
            printf("%s\n", ag->artifact[itemIndex]);
        }
    }
}

int hasArtifact(adventureGame *ag, const char *artifactName) {
    for (int i = 0; i < ag->inventoryCount; i++) {
        if (strcmp(ag->artifact[ag->inventory[i]], artifactName) == 0) {
            return 1; // Player has the specified artifact
        }
    }
    return 0; // Player does not have the specified artifact
}






