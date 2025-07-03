// main.c
#include "adventure_game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int processCommand(adventureGame *ag);

int main() {
    // Initialize the adventureGame structure with default values
adventureGame ag = {
    .monster = 1,
    .room = 0,
    .playerHP = 40,
    .playerXP = 0,
    .rooms = {"Radiant Hall", "Gourmet Gallery", "Zombie Sanctuary", "Wellness Retreat", "Howling Haven", "Whimsical Hideaway", "Dracula's Domain",
                "Mystic Chamber", "Ethereal Elixir Hall", "Serpent Sanctum", "Veiled Vista", "Luminous Haven", "Dragon's Lair"},
    .lookArray = {
    "You are in Radiant Hall. To the south is Whimsical Hideaway, and to the east is Gourmet Gallery.\n",
    "You are in Gourmet Gallery. To the west is Radiant Hall, and to the east is Zombie Sanctuary.\n",
    "You are in Zombie Sanctuary. To the west is Gourmet Gallery, and to the east is Wellness Retreat. To the south is Mystic Chamber.\n",
    "You are in Wellness Retreat. To the west is Zombie Sanctuary, and to the east is Howling Haven. To the south is Ethereal Elixir Hall.\n",
    "You are in Howling Haven. To the west is Wellness Retreat. To the south is Serpent Sanctum. However, Serpent Sanctum is locked by a bronze door that requires a bronze key in Mystic Chamber.\n",
    "You are in Whimsical Hideaway. To the north is Radiant Hall.\n",
    "You are in Dracula's Domain. To the east is Mystic Chamber, and to the south is Veiled Vista.\n",
    "You are in Mystic Chamber. To the west is Dracula's Domain, and to the east is Ethereal Elixir Hall. To the south is Luminous Haven, and to the north is Zombie Sanctuary.\n",
    "You are in Ethereal Elixir Hall. To the west is Mystic Chamber, and to the north is Wellness Retreat.\n",
    "You are in Serpent Sanctum. To the north is Howling Haven.\n",
    "You are in Veiled Vista. To the north is Dracula's Domain, and to the east is Luminous Haven.\n",
    "You are in Luminous Haven. To the west is Veiled Vista, and to the east is Dragon's Lair. To the north is Mystic Chamber. However, Dragon's Lair is locked by a copper door that requires a copper key in Dracula's Domain.\n",
    "You are in Dragon's Lair. To the west is Luminous Haven.\n"
},
    .moveArray = {
    {"Unable to move north", "You go south to Whimsical Hideaway", "You go east to Gourmet Gallery", "Unable to move west"}, //Radiant Hall
    {"Unable to move north", "Unable to move south", "You go east to Zombie Sanctuary", "You go west to Radiant Hall"}, //Gourmet Gallery
    {"Unable to move north", "You go south to Mystic Chamber", "You go east to Wellness Retreat", "You go west to Gourmet Gallery"}, //Zombie Sanctuary
    {"Unable to go north", "You go south to Ethereal Elixir Hall", "You go east to Howling Haven", "You go west to Zombie Sanctuary"}, //Wellness Retreat
    {"Unable to go north", "You go south to Serpent Sanctum", "Unable to move east", "You go west to Wellness Retreat"}, //Howling Haven
    {"You go north to Radiant Hall", "Unable to move south", "Unable to move east", "Unable to move west"}, //Whimsical Hideaway
    {"Unable to move north", "You go south to Veiled Vista", "You go east to Mystic Chamber", "Unable to move west"}, //Dracula's Domain
    {"You go north to Zombie Sanctuary", "You go south to Luminous Haven", "You go east to Ethereal Elixir Hall", "You go west to Dracula's Domain"}, //Mystic Chamber
    {"You go north to Wellness Retreat", "Unable to move south", "Unable to move east", "You go west to Mystic Chamber"}, //Ethereal Elixir Hall
    {"You go north to Howling Haven", "Unable to move south", "Unable to move east", "Unable to move west"}, //Serpent Sanctum
    {"Unable to move north", "Unable to move south", "You go east to Luminous Haven", "You go west to Dracula's Domain"}, //Veiled Vista
    {"You go north to Mystic Chamber", "Unable to move south", "You go east to Dragon's Lair", "You go west to Veiled Vista"}, //Luminous Haven
    {"Unable to move north", "Unable to move south", "Unable to move east", "You go west to Luminous Haven"} //Dragon's Lair
},
    .moveToArray = {
    {-1, 5, 1, -1},     // Room 1 movements
    {-1, -1, 2, 0},     // Gourmet Gallery movements
    {-1, 7, 3, 1},      // Zombie Sanctuary movements
    {3, 8, 4, 2},       // Wellness Retreat movements
    {4, -1, -1, 3},     // Howling Haven movements(assuming the door to Serpent Sanctum is locked)
    {0, -1, -1, -1},    // Whimsical Hideaway movements
    {-1, 10, 7, -1},    // Dracula's Domain movements
    {2, 11, 8, 6},     // Mystic Chamber movements
    {3, -1, -1, 7},     // Ethereal Elixir Hall movements
    {4, -1, -1, -1},    // Serpent Sanctum movements
    {-1, -1, 11, 6},    // Veiled Vista movements
    {7, -1, -1, 10},    // Luminous Haven movements (assuming the door to Dragon's Lair is locked)
    {-1, -1, -1, 11}    // Dragon's Lair movements
},
    .monsterArray = {"Zombie","Werewolf","Monster","Dracula","Lizardman","Bride of Dracula","Dragon"},
    .monsterLoc = {2, 4, 5, 6, 9, 10, 12},
    .monsterStatusArray = {5, 12, 4, 12, 5, 7, 12}, // Example health values for monsters
    .N_artifact = 9,
    .artifact = {"Sword", "Golden Chalice", "Medpack", "Food", "Bronze Key",
                     "Silver Spear", "Diamond Cross", "Copper Key", "Elixir"},
    .artifactLoc = {5, 12, 3, 1, 7, 11, 9, 6, 8},
};
printf("Welcome to the Adventure Game!\n\n");
printf("Below are the instructions and gameplay rules of the game:\n\n");
printf("You initialed by 12HP, but your Maximum HP is up to 40HP, you can increase by using a few items that are initialed in the game.\n\n");
printf("Killing any monster gain you 10XP, and getting the Golden Chalice Artifact will gain you extra 50XP.\n\n");
printf("There are several weakness of the monster in the game:\n\n");
printf("Having the Diamond Cross in your inventory will boost your damage twice against the vampires. While having a Silver Spear in your inventory will greatly boost your damage against the Werewolf.\n\n");
printf("Several rooms are locked, and there are also rooms that require you to defeat the monster in order to enter.\n\n");
printf("You may use the 'help' command to check out the commands in the game!\n\n");

char lastCommand[1000] = "";  // Variable to store the last valid command

    while (ag.playerHP > 0) {
        // Print "Enter command:" at the start of each inner loop iteration
        printf("Enter command: ");

        // Read and process user input
        while (fgets(ag.command, 1000, stdin)) {
            // Remove newline character from input
            ag.command[strcspn(ag.command, "\n")] = 0;
            // Check if the command is empty and auto-repeat the last command
            if (strlen(ag.command) == 0) {
                if (strlen(ag.lastCommand) > 0) {
                    strcpy(ag.command, ag.lastCommand);
                } else {
                    printf("Unknown command.\n");
                    continue;  // Ask for another command
                }
            }

            // Process the command and check if it was recognized
            if (!processCommand(&ag)) {
                printf("Unknown command: %s\n", ag.command);
                continue;  // Ask for another command
            }

            // Update lastCommand if the command was recognized
            strcpy(ag.lastCommand, ag.command);

            // Print "Enter command:" again for the next iteration
            printf("Enter command: ");
        }

        // Check if the processCommand function returned 0 (indicating exit)
        if (processCommand(&ag) == 0) {
            printf("\nGame over. Your score: %d\n", ag.playerXP);
        }
    }

    return 0;
}


