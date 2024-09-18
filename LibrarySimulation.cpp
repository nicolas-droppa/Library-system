#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define lineLength		100

void showMenu() {
	printf("+---------------------------+\n");
	printf("Press 1 to add a book\n");
	printf("Press 2 to remove a book\n");
	printf("Press 3 to close the program\n");
	printf("+---------------------------+\n");
}

char getChoice() {
	char choice;
	
	while (1) {
		choice = getch();
		switch (choice) {
			case '1':
			case '2':
			case '3':
				return choice;
			default:
				continue;
		}
	}
}

int alreadyInDatabase(char **database, char *title, int *dbLineCount) {
	char line[lineLength];
	int shiftString = 1;
	
	for (int i = 0; i < (*dbLineCount); i++) {
		for (int j = 0; j < strlen(database[i]); j++) {
			if(database[i][j] == ' ')
				break;
			shiftString++;
		}
		
        if (strcmp(database[i] + shiftString, title) == 0)
        	return 1;
        	
        shiftString = 1;
    }

    return 0;
}

int countDigits(int number) {
    int count = 0;

    if (number == 0) {
        return 1;
    }

    while (number != 0) {
        number = number / 10;
        ++count;
    }

    return count;
}

void AddBookToDB(char **database, int *dbLineCount) {
	char title[lineLength];
	unsigned int errorState = 0;

	while(1) {
		system("cls");
		printf("+---AddBook----------+\n\n");
		printf("Write EXIT! to return\n\n");
		printf("+--------------------+\n");
		
		if (errorState) {
			printf("[ERROR] Book is already in database!\n\n");
			errorState = 0;
		}
		
		printf("Enter Title: ");
		fgets(title, sizeof(title), stdin);
		
		if (strcmp(title, "EXIT!\n") == 0) {
			return;
		}
		
		if (alreadyInDatabase(database, title, dbLineCount)) {
			errorState = 1;
			continue;
		} else {
			for (int i = 0; i < (*dbLineCount); i++) {
				if (strcmp(database[i], "\n") == 0) {
					snprintf(database[i], sizeof(title) + i+2, "%d %s", i+1, title);
					return;
				}
    		}
    		
    		database = (char **)realloc(database, ((*dbLineCount) + 1) * sizeof(char *));
	        database[(*dbLineCount)] = (char *)malloc((strlen(title) + countDigits((*dbLineCount))+1) * sizeof(char));
	        snprintf(database[(*dbLineCount)], sizeof(title) + countDigits((*dbLineCount))+1, "%d %s", (*dbLineCount)+1, title);
	        (*dbLineCount)++;
	        return;
		}	
	}
}

void RemoveBookFromDB(char **database, int *dbLineCount) {
	char title[lineLength];
	unsigned int errorState = 0;
	
	while(1) {
		system("cls");
		printf("+---RemoveBook-------+\n\n");
		printf("Write EXIT! to return\n\n");
		printf("+--------------------+\n");
		
		if (errorState) {
			printf("[ERROR] Book is not in database!\n\n");
			errorState = 0;
		}
		
		printf("Enter Title: ");
		fgets(title, sizeof(title), stdin);
		
		if (strcmp(title, "EXIT!\n") == 0) {
			return;
		}
		
		if (!alreadyInDatabase(database, title, dbLineCount)) {
			errorState = 1;
			continue;
		} else {
			for (int i = 0; i < (*dbLineCount); i++) {				
				int shiftString = 1;
				
				for (int j = 0; j < strlen(database[i]); j++) {
					if(database[i][j] == ' ')
						break;
					shiftString++;
				}
				
		        if (strcmp(database[i] + shiftString, title) == 0) {
		        	database[i] = (char *)realloc(database[i], (1) * sizeof(char ));
					strcpy(database[i], "\n");
					return;
				}
    		}
		}	
	}
}

int choiceHandler(char choice, char **database, int *dbLineCount) {
	switch(choice) {
		case '1':
			AddBookToDB(database, dbLineCount);
		break;
		case '2':
			RemoveBookFromDB(database, dbLineCount);
		break;
		case '3':
			return 0;
		break;
		default:
			return 1;
	}
}

char **loadDatabase(int *dbLineCount) {	
	FILE *bookDatabase;	
	
	if((bookDatabase = fopen("bookDatabase.txt", "r")) == NULL) {	
		printf("Database does not exist... Creating new database!\n");	
		bookDatabase = fopen("bookDatabase.txt", "w");	
		fclose(bookDatabase);
		bookDatabase = fopen("bookDatabase.txt", "r");
	}	
		
	char line[lineLength];
	
	int lineCounter = 0;
	char **database = (char **)malloc(1 * sizeof(char *));
	
	while (fgets(line, sizeof(line), bookDatabase) != NULL) {
        database = (char **)realloc(database, (lineCounter + 1) * sizeof(char *));
        database[lineCounter] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        strcpy(database[lineCounter], line);
        lineCounter++;
    }

    fclose(bookDatabase);
    *dbLineCount = lineCounter;
	return database;
}

void saveDatabase(char **database, int dbLineCount) {
	FILE *bookDatabase;	
	
	if((bookDatabase = fopen("bookDatabase.txt", "w")) == NULL) {	
		printf("An error has occured while opening database... Ending program!\n");	
		exit(0);
	}
	
	for (int i = 0; i < dbLineCount; i++) {
		fputs(database[i], bookDatabase);
        free(database[i]);
    }
    
    free(database);
    fclose(bookDatabase);
}

void printDatabase(char **database, int dbLineCount) {
	for (int i = 0; i < dbLineCount; i++) {
		if(!strcmp(database[i], "\n") == 0) // skip empty slot
			printf("%s", database[i]);
    }
}

int main() {
	int dbLineCount = 0;
	char **database = loadDatabase(&dbLineCount);
	
	while(1) {
		printDatabase(database, dbLineCount);
		showMenu();
		if(choiceHandler(getChoice(), database, &dbLineCount) == 0)
			break;
	}
	saveDatabase(database, dbLineCount);
}
