#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define lineLength		100
#define indentation		3

void showMenu() {
	printf("+---------------------------+\n");
	printf("Press 1 to add a book\n");
	printf("Press 2 to remove a book\n");
	printf("Press 3 to close the program\n");
	printf("+---------------------------+\n");
}

FILE *createDatabase(FILE *bookDatabase) {
	printf("Database does not exist... Creating new database!\n");
	bookDatabase = fopen("bookDatabase.txt", "w");
	fprintf(bookDatabase, "{\n%*s\"books\":\n%*s[\n\n%*s],""\n%*s\"users\":\n%*s[\n\n%*s]\n}\n\n"
					   , indentation, "", indentation*2, "", indentation*2, "", indentation, ""
					   , indentation*2, "", indentation*2, "");
	fclose(bookDatabase);
	return bookDatabase;
}

char **loadDatabase(int *dbLineCount) {
	FILE *bookDatabase;

	if((bookDatabase = fopen("bookDatabase.txt", "r")) == NULL) {
		createDatabase(bookDatabase);
		bookDatabase = fopen("bookDatabase.txt", "r");
	}

	char line[lineLength];

	int lineCounter = 0;
	char **database = (char **)malloc(1 * sizeof(char *));

	while (fgets(line, sizeof(line), bookDatabase) != NULL) {
        database = (char **)realloc(database, (lineCounter + 1) * sizeof(char *));
        database[lineCounter] = (char *)malloc((strlen(line) + 1) * sizeof(char));
        strcpy(database[lineCounter], line);
		//replace \0 for \n in line
		printf("nehe", database[lineCounter]);
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
		printf("%s", database[i]);
    }
}

int addBook(char **database, int dbLineCount) {

}

char getChoice() {
	char choice;
	int errorState = 0;

	while (1) {
		if (errorState == 1) {
			printf("Error\n");
		}
		showMenu();
		printf("Please enter an option: ");

		scanf("%c", &choice);

		switch(choice) {
			case '1':
				exit(1);
			case '2':
				exit(2);
			case '3':
				exit(0);
			default:
				errorState = 1;
		}
	}
}

int main() {
	int dbLineCount = 0;
	char **database = loadDatabase(&dbLineCount);

	while(1) {
		printDatabase(database, dbLineCount);
		getChoice();
	}
	saveDatabase(database, dbLineCount);
}
