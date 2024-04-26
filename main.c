#include "include/binary_search_tree.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "include/tab_dynamique.h"
#include "include/MD5.h"


#define PATHMAX 4096
char pathname[PATHMAX] = { 0 };

void argument_manager(int argc, char *argv[]) {
	if (argc == 1)
		strcpy(pathname, "test/Shakespeare/1henryiv.txt");

	if (argc == 2)
		strcpy(pathname, argv[1]);
	if (argc > 2) {
		dprintf(STDERR_FILENO, "Erreur mauvais nombre d'argument\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);
	FILE *file = fopen(pathname, 'r');
	char buf[129] = { 0 };

	bst *b = bst_create_empty();
	table_dynamique tab;
	constTabDyn(&tab, 10);
	while(fgets(buf, 128, file) != NULL) {
		memset(buf, 0, 129);
		buf[strlen(buf)] = '\0';
		uint128_t *u = MD5(buf);
		if (!bst_search(b, *u)) {
			bst_add(*u, b);
			addElement(tab, );
		}
	}

	return 0;
}