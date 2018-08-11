#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

//Creates the dictionary struct node and returns its address
dict_t *createDict() {
	dict_t *pd = malloc(sizeof(dict_t));
	assert(pd);
	pd->head = NULL;
	pd->n = 0;
	return pd;
}


//Create a seperate record for the data
record_t *createRec(char *name, char *data) {
	
	record_t *pr = malloc(sizeof(record_t));
	pr->lesser = NULL;
	pr->larger = NULL;
	pr->name = strdup(name);
	pr->data = strdup(data);
	
	assert(pr);
	
	return pr;
}

void changeAddress(record_t **p1, record_t *p2) {
 *p1 = p2;
}

//Reads in a record and places it in the dictionary
void insert( dict_t *pd, char *name, char *data) {
	//Checks if first element
	int compare;
	if(pd->head == NULL) {
		pd->head = createRec(name, data);
		
	} else {
		
		record_t *pr = pd->head;
		
		//While not at the end of the dictionary
		while (1) {
			compare = strcmp(name, pr->name);
			if (compare > 0) {
				if(pr->larger == NULL) {
					pr->larger = createRec(name, data);
				//	free(pr);
					return;
					
				}
				pr = pr->larger;
			
				
			//If lesser or equal
			} else if (compare <= 0){
				if(pr->lesser == NULL) {
					pr->lesser = createRec(name, data);
				//	free(pr);
					return;
				}
				pr = pr->lesser;
			}
		}
	}
}


void search(char *name, dict_t *pd) {
	int compare, cmp = 0, found = 0;
	
	if(pd->head == NULL) {
		printf("no tree found");
		exit(EXIT_FAILURE);
		
	} else {
		
		record_t *pr = pd->head;
		
		//While not at the end of the tree
		while (1) {
				
			compare = strcmp(name, pr->name);
			cmp++;
			
			if (compare > 0) {
				if(pr->larger == NULL) {
					break;
				}
				pr = pr->larger;
			
				//If lesser or equal
			} else if(compare < 0) {
				if (pr->lesser == NULL) {
					break;
				}
				pr = pr->lesser;
			} else if(compare == 0) {
				printToFile(pr, cmp); 
				found++;
				if (pr->lesser == NULL) {
					break;
				}
				pr = pr->lesser;
			} else {
				printf("error in strcmp\n");
			}
		}
	} 
	if (!found) {
		printNotFound(name);
	}
	printf("%s --> %d\n", name, cmp);
}

void printNotFound(char *name) {
	FILE *fp;
	fp=fopen(OUTPUTFILE,"ab");
	fprintf(fp, "%s --> NOTFOUND\n\n", name);
	fclose(fp);
}

void printToFile(record_t *pr, int cmp) {
	FILE *fp;
	fp=fopen(OUTPUTFILE,"ab");
	fprintf(fp, "%s --> %s\n", pr->name, pr->data);
	fclose(fp);
}
	
void printKey(record_t *node, int cmp) {
	printf("%s --> %d\n", node->name, cmp);
}

void free_tree(record_t *node) {
	if (node == NULL) {
		return;
	}
	
	free_tree(node->lesser);
	free_tree(node->larger);
	
	free(node->name);
	free(node->data);
	free(node);
}