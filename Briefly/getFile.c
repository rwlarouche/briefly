/* 
* Copyright 2017 Ryan LaRouche
*
* getFile.c
*
* This file prompts the user for a FULL file path and reads
* the file to calculate the wordcount, a list of all words, and
* a hash table to track how many times each word appears.
*
* Generates a Hash Table of keys and values, which can be 
* searched by element, and add new key value pairs via chaining.
* To be used by getFile.c to store a file's word (key) 
* frequency (value) pairs.
*
* For testing:
* C:\Users\rwlar\OneDrive\Documents\GitHub\Briefly\Briefly\Test.txt
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 997 

/* Function prototypes */
void getFileName();
void openFile(char *);
void readFile(FILE *, char *);
void analyzeFile(struct fileInfo*, FILE *, char *[], int);

int genHash(char *);
int hash(char *key);
int hash_insert(char *key);
char* hash_find(char* key);
void hash_destroy();
void display_hash();

/* Create a structure for file data */
struct fileInfo {
	char *name;
	char *words[2000];
	int wordcount;
};

/* Create a structure for Hash Table */
typedef struct listNode {
	char Value[128];
	int loc[500];
	struct Node *next;
} listNode;

listNode* HashTable[HASHSIZE];

/* main */
int main(void)
{
	getFileName();					// Get file name as input
	return 0;
}

/* Gets the name of a .txt file from user input */
void getFileName()
{
	char fname[128];						// Max input length of 128 characters
	printf("Enter the FULL path of a .txt file: ");
	scanf("%123s", &fname);
	openFile(fname);						// Open, read, analyze file					
}

/* Opens the .txt file corresponding to user input */
void openFile(char *inputfile) {
	printf("Opening %s", inputfile);			// Print opening file statement
	printf("...\n");

	FILE *inputf;
	if (((inputf = fopen(inputfile, "r"))) && (inputf != NULL))		// Open file if not NULL
	{
		readFile(inputf, inputfile);	// Pass open file and its name
	}
	else if (inputf == NULL)	// If NULL, print error and ask for another file name
	{
		perror("Error", EXIT_FAILURE);
		getFileName();
	}
}

/* Manages functions that read the file */
void readFile(FILE *readf, char *fopenname)
{
	char *words[2000];			// Max words a file can contain = 2000
	int maxwords = 2000;		

	struct fileInfo originalfile;	// Create filInfo struct for original file, set its name and itialize wordcount
	originalfile.name = fopenname;
	originalfile.wordcount = 0;
	
	analyzeFile(&originalfile, readf, words, maxwords); // Get analysis of readf file
	genHash(originalfile.name);

	genHash(fopenname);
}

/* Calculates number of words in the file and compiles an array of the words */
void analyzeFile(struct fileInfo* file_struct, FILE *countf, char *words[], int maxwords) 
{
	int i;
	char temp[100];								// Assuming the words cannot be too long (max length of 100 characters)

	for (i = 0; i < maxwords; ++i)
	{
		if (fscanf(countf, "%s", temp) != 1)	// Read a word from the file
			break;								// Note: "!=1" checks for end-of-file

		file_struct->words[i] = strdup(temp);	// Add word to array at address of passed struct
	}

	file_struct->wordcount = i;					// Change wordcount value at address of passed struct

	fclose(countf);
}

/* Open file, generate table via hash_insert() and prompt user to look up words in Table */
int genHash(char *filename)
{
	FILE *hashf;
	int count;
	char word[15] = { '\0' };
	int quit = 0;
	char* p;

	for (count = 0; count < HASHSIZE; count++)
	{
		HashTable[count] = NULL;
	}

	if ((hashf = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "File could not open!!\n");
		return(EXIT_FAILURE);
	}
	while (fscanf(hashf, "%s", word) == 1)
	{
		hash_insert(word);
	}
	fclose(hashf);

	while (!quit)
	{
		printf("Enter a word (Q to quit): ");
		fflush(stdout);
		if (fgets(word, sizeof word, stdin) != NULL) {
			p = strchr(word, '\n');
			if (p != NULL)
				*p = '\0';
			if ((word[0] == 'q' || word[0] == 'Q') && word[1] == '\0')
				quit = 1;
			else {
				if (hash_find(word) != NULL)
					printf("Word in dictionary\n");
				else
					printf("Word not in dictionary\n");
			}
		}
	}
	display_hash();
	hash_destroy();

	return 0;
}

/* Gets position of passed word (key) in hash table (NULL if not in table) */
int hash(char *key)
{
	unsigned int hash_val = 0;

	while (*key != '\0')
		hash_val += *(key++);

	return(hash_val % HASHSIZE);
}

/* Returns passed word (key) in hash table if found by hash(), returns NULL if not in table*/
char* hash_find(char* key)
{
	listNode* curr;
	int pos;

	pos = hash(key);
	curr = HashTable[pos];
	while (curr != NULL)
	{
		if (!strcmp(curr->Value, key))
			return key;
		curr = curr->next;
	}

	return NULL;
}

/* Inserts passed word (key) in hash table by chaining */
int hash_insert(char *key)
{
	listNode *newptr, *curr;
	int pos;

	pos = hash(key);

	/* Make sure it's not already in the hash table */
	curr = HashTable[pos];
	while (curr != NULL)
	{
		if (!strcmp(curr->Value, key))
			return 1;
		curr = curr->next;
	}

	newptr = malloc(sizeof(listNode));
	if (newptr == NULL)
	{
		printf("Not Enough Memory!\n");
		exit(EXIT_SUCCESS);
	}
	strcpy(newptr->Value, key);


	newptr->next = NULL;

	int uniquewords = 0;

	if (HashTable[pos] == NULL)
	{
		HashTable[pos] = newptr;
		HashTable[uniquewords] = pos;
		printf("%d", HashTable[uniquewords]);
		printf("%s", HashTable[pos]->Value);		// NOT IN A FOR LOOP, Make an array of pos and access that way (current method will overight words after a certain
													// number of words
	}
	else
	{
		listNode* headptr = HashTable[pos];
		HashTable[pos] = newptr;
	}
	if (HashTable[pos] == NULL)
	{
		HashTable[uniquewords] = pos;
		printf("%d", HashTable[281]);
	}
	return 1;
}

/* Destroys hash table */
void hash_destroy()
{
	int i;
	listNode* curr;
	listNode* tmp;

	for (i = 0; i < HASHSIZE; i++)
	{
		curr = HashTable[i];
		while (curr != NULL)
		{
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
	}
}

/* Display Hash Table*/
void display_hash()
{
	int i;
	int size = malloc(sizeof(listNode));

	//printf(HashTable[0]->loc[0]);
	printf("Word\tOccurances\n");

	//for (i = 0; i < size; i++)
	//{
	//	fprintf("&s\t", HashTable[i]->Value);
	//	struct listNode *ptr;
	//	ptr = HashTable[i]->next;
	//	while (ptr != NULL)
	//	{
	//		
	//	}
	//	printf("\n");
	//}

}

// GET NUMBER OF OCCURENCES AS VALUES (ADD TO STRUCT, BASE OF WORD POSITION)
