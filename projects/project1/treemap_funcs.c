// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "treemap.h"

void treemap_init(treemap_t *tree) { // init function
    tree->root = NULL;
    tree->size = 0;
}

int treemap_add(treemap_t *tree, char key[], char val[]) {
    node_t **leaf = &tree->root; // Assigning root to a variable for iteration later
    while (*leaf != NULL) {
        if ((strcmp(key, (*leaf)->key)) == 0) { // If key is already found
            strcpy((*leaf)->val, val);
            printf("modified existing key\n");
            return 0;
        }
        else if ((strcmp(key, (*leaf)->key)) > 0) { // If key is greater than current key
            leaf = &(*leaf)->right;
        }
        else if ((strcmp(key, (*leaf)->key)) < 0) { // If key is less than current key
            leaf = &(*leaf)->left;
        }
    }

    //If the current node (leaf) is NULL
    *leaf = malloc(sizeof(node_t));
    strcpy((*leaf)->key, key); // Using strcpy to not waste memory
    strcpy((*leaf)->val, val);
    (*leaf)->right = NULL;
    (*leaf)->left = NULL;
    return 1;
}

char *treemap_get(treemap_t *tree, char key[]) { // Get function
    node_t *leaf = tree->root; // Assigning root to a variable for iteration later
    while (leaf != NULL) {
        if ((strcmp(key, leaf->key)) == 0) { // If query matches key
            char *val = leaf->val;
            return val;
        }
        else if ((strcmp(key, leaf->key)) > 0) { // If key is greater than current key
            leaf = leaf->right;
        }
        else if ((strcmp(key, leaf->key)) < 0) { // If key is less than current key
            leaf = leaf->left;
        }
    }
    return NULL; // If while loop fails, key was not found
}

void treemap_clear (treemap_t *tree){ // Clear function
    node_remove_all(tree->root);
    tree->root = NULL;
}

void node_remove_all (node_t *cur){ // Remove all function (clear helper)
    if (cur != NULL) {
        node_remove_all(cur->left);
        node_remove_all(cur->right);
        free(cur);
    }
}

void treemap_print_revorder(treemap_t *tree) { // Print reverse order function
    node_print_revorder(tree->root, 0);
}

void node_print_revorder(node_t *cur, int indent) { // Reverse Order helper function
    if (cur != NULL) {
        node_print_revorder(cur->right, indent+1);
        for (int i=0; i < indent; i++) { // Number of spaces
            printf("  ");
        }
        printf("%s -> %s\n", cur->key, cur->val);
        node_print_revorder(cur->left, indent+1);
    }
}

void treemap_print_preorder(treemap_t *tree) { // Preorder function
    node_write_preorder(tree->root, stdout, 0);
}

void treemap_save(treemap_t *tree, char *fname) { // Save function
    FILE *outputFile = fopen(fname, "w+");
    node_write_preorder(tree->root, outputFile, 0);
    fclose(outputFile);
}

void node_write_preorder(node_t *cur, FILE *out, int depth) { // Preorder helper function
    if (cur == NULL) {
        return;
    }
    for (int i=0; i < depth; i++) { // Number of spaces
        fprintf(out, "  ");
    }
    fprintf(out, "%s %s\n", cur->key, cur->val);
    node_write_preorder(cur->left, out, depth+1);
    node_write_preorder(cur->right, out, depth+1);
}

int treemap_load(treemap_t *tree, char *fname) {
    FILE *inputFile = fopen(fname, "r");
    if (inputFile == NULL) { // if file isn't found
        printf("ERROR: could not open file '%s'\n", fname);
        return 0;
    }
    treemap_clear(tree);
    char str1[128], str2[128]; // temp strings for loading
    while (fscanf(inputFile, "%s %s", str1, str2) != EOF) {
        treemap_add(tree, str1, str2);
    }
    fclose(inputFile);
    return 1;
}
