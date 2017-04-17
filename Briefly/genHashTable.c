///* 
//* Copyright 2017 Ryan LaRouche 
//*
//* genHashTable.c
//*
//* Generate a Hash Table of keys and values, which can be 
//* searched by element, and add new key value pairs via chaining.
//*
//* To be used by getFile.c to store a file's word (key) 
//* frequency (value) pairs.
//*/
//
//#include <stdio.h> 
//#include <stdlib.h> 
//#include <string.h> 
//
//#define HASHSIZE 2000		// Max unique words in Hash Table
//
///* Function prototypes */
//int genHash(char *);
//int hash(char *key);
//int hash_insert(char *key);
//char* hash_find(char* key);
//void hash_destroy();
//void display_hash();
//
///* Create a structure for Hash Table */
//typedef struct listNode {
//	char Value[128];
//	struct Node *next;
//} listNode;
//
//listNode* HashTable[HASHSIZE];
//
///* Open file, generate table via hash_insert() and prompt user to look up words in Table */
//int genHash(char *filename)
//{
//	FILE *file;
//	int count;
//	char word[15] = { '\0' };
//	int quit = 0;
//	char* p;
//
//	for (count = 0; count < HASHSIZE; count++)
//	{
//		HashTable[count] = NULL;
//	}
//
//	if ((file = fopen(filename, "r")) == NULL)
//	{
//		fprintf(stderr, "File could not open!!\n");
//		return(EXIT_FAILURE);
//	}
//	while (fscanf(file, "%s", word) == 1)
//	{
//		hash_insert(word);
//	}
//	fclose(file);
//
//	while (!quit)
//	{
//		printf("Enter a word (Q to quit): ");
//		fflush(stdout);
//		if (fgets(word, sizeof word, stdin) != NULL) {
//			p = strchr(word, '\n');
//			if (p != NULL)
//				*p = '\0';
//			if ((word[0] == 'q' || word[0] == 'Q') && word[1] == '\0')
//				quit = 1;
//			else {
//				if (hash_find(word) != NULL)
//					printf("Word in dictionary\n");
//				else
//					printf("Word not in dictionary\n");
//			}
//		}
//	}
//	hash_destroy();
//
//	return 0;
//}
//
///* Gets position of passed word (key) in hash table (NULL if not in table) */
//int hash(char *key)
//{
//	unsigned int hash_val = 0;
//
//	while (*key != '\0')
//		hash_val += *(key++);
//
//	return(hash_val % HASHSIZE);
//}
//
///* Returns passed word (key) in hash table if found by hash(), returns NULL if not in table*/
//char* hash_find(char* key)
//{
//	listNode* curr;
//	int pos;
//
//	pos = hash(key);
//	curr = HashTable[pos];
//	while (curr != NULL)
//	{
//		if (!strcmp(curr->Value, key))
//			return key;
//		curr = curr->next;
//	}
//
//	return NULL;
//}
//
///* Inserts passed word (key) in hash table by chaining */
//int hash_insert(char *key)
//{
//	listNode *newptr, *curr;
//	int pos;
//
//	pos = hash(key);
//
//	/* Make sure it's not already in the hash table */
//	curr = HashTable[pos];
//	while (curr != NULL)
//	{
//		if (!strcmp(curr->Value, key))
//			return 1;
//		curr = curr->next;
//	}
//
//	newptr = malloc(sizeof(listNode));
//	if (newptr == NULL)
//	{
//		printf("Not Enough Memory!\n");
//		exit(EXIT_SUCCESS);
//	}
//	strcpy(newptr->Value, key);
//
//
//	newptr->next = NULL;
//
//	if (HashTable[pos] == NULL)
//		HashTable[pos] = newptr;
//	else
//	{
//		listNode* headptr = HashTable[pos];
//		HashTable[pos] = newptr;
//		HashTable[pos]->next = headptr;
//	}
//	return 1;
//}
//
///* Destroys hash table */
//void hash_destroy()
//{
//	int i;
//	listNode* curr;
//	listNode* tmp;
//
//	for (i = 0; i < HASHSIZE; i++)
//	{
//		curr = HashTable[i];
//		while (curr != NULL)
//		{
//			tmp = curr->next;
//			free(curr);
//			curr = tmp;
//		}
//	}
//}
//
///* Display Hash Table*/
//void display_hash()
//{
//	int i;
//	int size = malloc(sizeof(listNode));
//
//	printf("Word\tOccurances\n");
//
//	for (i = 0; i < size; i++)
//	{
//		printf("&s", HashTable[i]->Value);
//	}
//
//}
//
//// GET NUMBER OF OCCURENCES AS VALUES (ADD TO STRUCT, BASE OF WORD POSITION)