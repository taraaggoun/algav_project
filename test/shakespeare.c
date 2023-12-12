/* -------------------------------- INCLUDE --------------------------------- */

#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/MD5.h"
#include "../include/binary_search_tree.h"

/* -------------------------------- DEFINE ---------------------------------- */

#define PATHMAX 4096

/* ---------------------------- GLOBAL VARIABLES ---------------------------- */

size_t nb_word_unique = 0;
size_t nb_word = 0;

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Ajoute un mot a la liste de moi si il est pas deja dedans
*/
static void add_list_word(list_words **words, char *word) {
	nb_word++;
	if (*words == NULL) {
		*words = calloc(1, sizeof(list_words));
        	if (*words == NULL) {
            		dprintf(STDERR_FILENO, "Erreur creation list word\n");
            		exit(EXIT_FAILURE);
        	}
        	(*words)->name = calloc(1, strlen(word) + 1);
	        if ((*words)->name == NULL) {
        		dprintf(STDERR_FILENO, "Erreur allocation list word\n");
            		exit(EXIT_FAILURE);
        	}
		strncpy((*words)->name, word, strlen(word));
    	}
	else {
		list_words *cur = *words;
		while(cur->next != NULL) {
			if (strcmp(cur->name, word) == 0)
				return; // Le mot existe déjà dans la liste
		        cur = cur->next;
		}
		if (strcmp(cur->name, word) == 0)
        		return; // Le mot existe déjà dans la liste

		// Le mot n'existe pas dans la liste
        	list_words *w = calloc(1, sizeof(list_words));
        	if (w == NULL) {
        		dprintf(STDERR_FILENO, "Erreur calloc add word\n");
        		exit(EXIT_FAILURE);
        	}
	        w->name = calloc(1, strlen(word) + 1);
        	if (w->name == NULL) {
            		dprintf(STDERR_FILENO, "Erreur calloc add word\n");
            		exit(EXIT_FAILURE);
        	}

        	strncpy(w->name, word, strlen(word));
        	cur->next = w;
	}
	nb_word_unique++;
}

/**
 * Affiche la liste
*/
static void print_list_word(list_words *list) {
	printf("\n---------------------------------------- LISTE DE MOT UNIQUE ----------------------------------------\n");
	while (list != NULL) {
		printf("%s ", list->name);
		list = list->next;
	}
	printf("\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
}

/**
 * Affiche les colisions
*/
static void print_collision(bst *t) {
	if (t == NULL)
		return;
	if (t->left != NULL)
		print_collision(t->left);
	if (t->right != NULL)
		print_collision(t->right);
	if (t->words.name != NULL && t->words.next !=  NULL) {
		list_words *cur = &(t->words);
		printf("collision entre ");
		while (cur->next != NULL) {
			printf("%s ", cur->name);
			cur = cur->next;
		}
		printf("%s ", cur->name);
		printf("\n");
	}
}

/**
 * Lis ligne par ligne dans le fichier et ajoute dans les structures
*/
static void bst_manager(FILE *f, bst **t, list_words **words) {
	char buf[129] = { 0 };
	while(fgets(buf, 128, f) != NULL) {
		buf[strlen(buf) - 1] = '\0';
		uint128_t u = md5(buf);
		bst_add_word(t, buf, u);
		add_list_word(words, buf);
	}
}

/**
 * Ouvres tout les fichiers et lis a l'interieur
*/
void file_manager(bst **t, list_words **words) {
	DIR *dir = opendir("test/Shakespeare");
	if(dir == NULL) {
   		dprintf(STDERR_FILENO ,"Erreur opendir\n");
    		exit(EXIT_FAILURE);
	}
	struct dirent *entry;
	while((entry = readdir(dir))) {
		if (entry->d_name[0] == '.')
			continue;

		char pathname[PATHMAX] = { 0 };
		strncpy(pathname, "test/Shakespeare/", 18);
		strncpy(pathname + 17, entry->d_name, strlen(entry->d_name));
		FILE *f = fopen(pathname, "r");
		if (f == NULL) {
			dprintf(STDERR_FILENO ,"Erreur fopen\n");
    			exit(EXIT_FAILURE);
		}

		bst_manager(f, t, words);

		fclose(f);
	}
	closedir(dir);
}

/* ---------------------------------- MAIN ---------------------------------- */

int main(void) {
	// Creation de l'arbre vide et de la liste vide
	bst *t = bst_create_empty();
	list_words *words = NULL;
	
	// Lis dans les fichier et ajoute dans les structures
	file_manager(&t, &words);

	// Affiche les resultats
	// bst_print(t);
	print_list_word(words);
	printf("\nIl y a %ld mots unique sur %ld mots\n", nb_word_unique, nb_word);
	printf("\n---------------------------------------- COLLISION ----------------------------------------\n");
	print_collision(t);
	printf("-------------------------------------- FIN COLLISION --------------------------------------\n\n");
	bst_free(t);

	return 0;
}

/* -------------------------------------------------------------------------- */
