#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_TEAMS 20
#define SQUAD_SIZE 25

/*Defining a struct called player_t*/
typedef struct {
    char name[25]; /*Full name of player*/
    int kitNumber; 
    char club[25];
    struct {
        int day;
        int month;
        int year;
    } dob;         /* Player's Date of Birth*/
    char position[25]; /*Player's Position*/
} player_t;

/*Defining a struct called team_t*/
typedef struct {
    char name[25];  /*Club Name*/
    player_t players[SQUAD_SIZE];
    int activeSize;  /*Current Squad Size of team*/
} team_t;

/*Function Prototypes*/
int display_menu();
void enroll_club(team_t teams[], int *numTeams);
void add_player(team_t teams[], int numTeams);
void search_update(team_t teams[], int numTeams);
void display_club_statistics(team_t teams[], int numTeams);
void handle_error(char *message);
int is_valid_date(int day, int month, int year);

int main() {
    team_t teams[NUM_TEAMS]; /* Array for teams*/
    int numTeams = 0;        /*Initializing number of teams*/

    while (1) {
        int choice = display_menu(); 

        switch (choice) {
            case 1:
                enroll_club(teams, &numTeams);
                break;
            case 2:
                add_player(teams, numTeams);
                break;
            case 3:
                search_update(teams, numTeams);
                break;
            case 4:
                display_club_statistics(teams, numTeams);
                break;
            case 5:
                printf("Exiting the program...\n");
                return 0;
        }
    }
}

int display_menu() {
    int choice;

    printf("\nWelcome to Transfer Market\n");
    printf("1. Enroll a club\n");
    printf("2. Add a player\n");
    printf("3. Search and update player\n");
    printf("4. Display club statistics\n");
    printf("5. Exit\n");
    printf("Enter your choice (1-5): ");

/* Validate the user's input */
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
        printf("Error: Invalid input. Exiting the program...\n");
        exit(1); 
    }

    return choice;
}


void enroll_club(team_t teams[], int *numTeams) {
    /*Checking if the maximum number of clubs have been reached*/
    if (*numTeams >= NUM_TEAMS) {  
        handle_error("Maximum number of clubs already enrolled.");
        return;
    }

    printf("Enter the name of the club: ");
    scanf(" %[^\n]%*c", teams[*numTeams].name); /*Allows spaces between the words*/

    for (int i = 0; i < *numTeams; i++) {
        if (strcmp(teams[i].name, teams[*numTeams].name) == 0) {
            handle_error("Club already enrolled. Please enter a unique club name.");
            return;
        }
    }

    (*numTeams)++; /*Increments the number of teams*/
    printf("Club '%s' enrolled successfully.\n", teams[*numTeams - 1].name);
}

void add_player(team_t teams[], int numTeams) {
    int selectedTeam;
    player_t newPlayer;
    /* Display the list of enrolled clubs */
    printf("Enrolled clubs:\n");
    for (int i = 0; i < numTeams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }

    printf("Select a club to add a player (1-%d): ", numTeams);
    if (scanf("%d", &selectedTeam) != 1 || selectedTeam < 1 || selectedTeam > numTeams) {
        handle_error("Invalid club selection.");
        while (getchar() != '\n'); /*Clears the buffer*/
        return;
    }
    selectedTeam--; /*Adjust for zero based indexing*/

    if (teams[selectedTeam].activeSize >= SQUAD_SIZE) {  /*Checks if current size of team is more than max squad size*/
        handle_error("Squad is full. Cannot add more players.");
        return;
    }

    printf("Enter player name: ");
    scanf(" %[^\n]%*c", newPlayer.name);

    for (int i = 0; i < teams[selectedTeam].activeSize; i++) {
        if (strcmp(teams[selectedTeam].players[i].name, newPlayer.name) == 0) {
            printf("Player '%s' already enrolled in club '%s'.\n", newPlayer.name, teams[selectedTeam].name);
            handle_error("Please enter a unique player name.");
            return;
        }
    }

    printf("Enter player kit number: ");
    if (scanf("%d", &newPlayer.kitNumber) != 1) {
        handle_error("Invalid kit number input.");
        while (getchar() != '\n'); /*Clears buffer*/
        return;
    }

    for (int i = 0; i < teams[selectedTeam].activeSize; i++) {
        if (teams[selectedTeam].players[i].kitNumber == newPlayer.kitNumber) {
            printf("Kit number %d already assigned to player '%s' in club '%s'.\n",
                   newPlayer.kitNumber, teams[selectedTeam].players[i].name, teams[selectedTeam].name);
            handle_error("Please enter a unique kit number.");
            return;
        }
    }
    /* Get the player's date of birth and position */
    printf("Enter player date of birth (DD MM YYYY): ");
    if (scanf("%d %d %d", &newPlayer.dob.day, &newPlayer.dob.month, &newPlayer.dob.year) != 3 ||
        !is_valid_date(newPlayer.dob.day, newPlayer.dob.month, newPlayer.dob.year)) {
        handle_error("Invalid date input.");
        return;
    }

    printf("Enter player position: ");
    scanf(" %[^\n]%*c", newPlayer.position);

    /* Set the player's club and add the player to the team */
    strncpy(newPlayer.club, teams[selectedTeam].name, sizeof(newPlayer.club));
    newPlayer.club[sizeof(newPlayer.club) - 1] = '\0'; 

    teams[selectedTeam].players[teams[selectedTeam].activeSize++] = newPlayer;
    printf("Player '%s' added to club '%s' successfully.\n", newPlayer.name, teams[selectedTeam].name);
}


void search_update(team_t teams[], int numTeams) {
    int searchByKitNumber;
    int kitNumber;
    char name[25];
    int found = 0;
    /* Get the user's choice to search by kit number or name */
    printf("Search by:\n1. Kit Number\n2. Name\nEnter your choice (1 or 2): ");
    if (scanf("%d", &searchByKitNumber) != 1 || (searchByKitNumber != 1 && searchByKitNumber != 2)) {
        handle_error("Invalid choice. Please enter 1 for Kit Number or 2 for Name.");
        while (getchar() != '\n'); 
        return;
    }

    if (searchByKitNumber == 1) {
        printf("Enter kit number to search: ");
        if (scanf("%d", &kitNumber) != 1) {
            handle_error("Invalid kit number input.");
            while (getchar() != '\n');
            return;
        }
    } else {
        printf("Enter player name to search: ");
        scanf(" %[^\n]%*c", name);
    }
    /* Search for the player and display the details if found */
    for (int i = 0; i < numTeams; i++) {
        for (int j = 0; j < teams[i].activeSize; j++) {
            int is_match = 0;
            
            if (searchByKitNumber == 1) {
                is_match = (teams[i].players[j].kitNumber == kitNumber);
            } else {
                is_match = (strcasecmp(teams[i].players[j].name, name) == 0);
            }

            if (is_match) {
                found = 1;
                printf("Player found:\n");
                printf("Name: %s\n", teams[i].players[j].name);
                printf("Kit number: %d\n", teams[i].players[j].kitNumber);
                printf("Club: %s\n", teams[i].players[j].club);
                printf("Date of birth: %02d/%02d/%04d\n", teams[i].players[j].dob.day, teams[i].players[j].dob.month, teams[i].players[j].dob.year);
                printf("Position: %s\n", teams[i].players[j].position);
                 /* Ask the user if they want to update the player's details */
                printf("Do you want to update the player details? (y/n) ");
                char choice;
                scanf(" %c", &choice);
                if (choice == 'y' || choice == 'Y') {
                    printf("Enter new kit number: ");
                    scanf("%d", &teams[i].players[j].kitNumber);
                    printf("Enter new date of birth (DD MM YYYY): ");
                    scanf("%d %d %d", &teams[i].players[j].dob.day, &teams[i].players[j].dob.month, &teams[i].players[j].dob.year);
                    printf("Enter new position: ");
                    scanf(" %[^\n]%*c", teams[i].players[j].position);
                    printf("Player details updated successfully.\n");
                }
                return;
            }
        }
    }

    if (!found) {
        handle_error("Player not found.");
    }
}

void display_club_statistics(team_t teams[], int numTeams) {
    printf("Club Statistics:\n");
    for (int i = 0; i < numTeams; i++) {
        printf("Club: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].activeSize);

        int totalAge = 0;
        int validAges = 0;
        /* Display the details of all players in the current club */
        if (teams[i].activeSize > 0) {
            printf("Player Details:\n");
            printf("------------------------------------------------------------\n");
            printf("| %-25s | %-12s | %-5s |\n", "Name", "Position", "Age");
            printf("------------------------------------------------------------\n");
        }

        for (int j = 0; j < teams[i].activeSize; j++) {
            int age = 2024 - teams[i].players[j].dob.year;

            /* Check for valid age */
            if (age >= 0 && age <= 100) {
                totalAge += age;
                validAges++;
            } else {
                printf("Warning: Unreasonable age (%d) for player %s.\n", age, teams[i].players[j].name);
                continue; /* Skip displaying players with unreasonable ages */
            }

            /*Display the players details*/
            printf("| %-25s | %-12s | %-5d |\n",
                   teams[i].players[j].name,
                   teams[i].players[j].position,
                   age);
        }

        if (teams[i].activeSize > 0) {
            printf("------------------------------------------------------------\n");
        }

        /* Display the average age of the players in the current club */
        if (validAges > 0) {
            int averageAge = totalAge / validAges;
            printf("Average age of players: %d\n", averageAge);
        } else {
            printf("No players with reasonable ages to calculate average.\n");
        }
        printf("\n");
    }
}

/* Function to handle and display error messages */
void handle_error(char *message) {
    printf("Error: %s\n", message);
}
/* Function to check if a given date is valid */
int is_valid_date(int day, int month, int year) {
    return (year >= 1900 && year <= 2023) && (month >= 1 && month <= 12);
}
