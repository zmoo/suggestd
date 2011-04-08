#include <stdlib.h>
#include <stdio.h>
#include "node.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "USAGE: cmd <prefix>\n");
		return 1;
	}
	char *prefix = argv[1];

	Node *root = node_new('\0');
	node_suffixes_add(root, "Nicolas Martin");
	node_suffixes_add(root, "Martin Nicolas");
	node_suffixes_add(root, "Marion Durand");
	node_suffixes_add(root, "Durand Marion");
	node_suffixes_add(root, "Albert Dupont");
	node_suffixes_add(root, "Dupont Albert");

	Node *node = node_suffixes_find(root, prefix);
	if (node != NULL) {
		char buf[64];
		char *list[15];
		unsigned int count = 0;
		node_suffixes_fetch(node, buf, sizeof(buf), 0, list, NULL, 15, &count);

		int i;
		for (i = 0; i < count; i++) {
			printf("%s%s\n", prefix, list[i]);
			free(list[i]);
		}
	}

	return 0;
}
