// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "treemap.h"



  int main(int argc, char *argv[]){
    int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
    if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
      echo=1;
    }

    printf("TreeMap Editor\n");
    printf("Commands:\n");
    printf("  quit:            exit the program\n");
    printf("  print:           shows contents of the tree in reverse sorted order\n");
    printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
    printf("  get <key>:       prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
    printf("  clear:           eliminates all key/vals from the tree\n");
    printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
    printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
    printf("  load <file>:     clears the current tree and loads the one in the given file\n");

    char cmd[128];
    treemap_t *treemap = malloc(sizeof(treemap_t));
    int success;
    treemap_init(treemap);

    while(1){
      printf("TM> ");                 // print prompt
      success = fscanf(stdin,"%s",cmd); // read a command
      if(success==EOF){                 // check for end of input
        printf("\n");                   // found end of input
        break;                          // break from loop
      }

      if( strcmp("quit", cmd)==0 ){ // quit command
        if(echo){
          printf("quit\n");
        }
        break; // break from loop
      }

      else if( strcmp("print", cmd)==0 ){ // print command
        if(echo){
          printf("print\n");
        }
        treemap_print_revorder(treemap);
      }

      else if( strcmp("add", cmd)==0 ){ // add command
        char key[128];
        char value[128];
        fscanf(stdin,"%s %s", key, value);
        if(echo){
          printf("add %s %s\n", key, value);
        }

        treemap_add(treemap, key, value);
      }

      else if( strcmp("get", cmd)==0 ){ // get command
        char key[128];
        fscanf(stdin,"%s",key); // read a string
        if(echo){
          printf("get %s\n",key);
        }

        char *value = treemap_get(treemap, key);
        if(value == NULL){ // check for success
          printf("NOT FOUND\n");
        }
        else {
          printf("FOUND: %s\n",value);
        }
      }

      else if( strcmp("clear", cmd)==0 ){ // clear command
        if(echo){
          printf("clear\n");
        }
        treemap_clear(treemap);
      }

      else if(strcmp("preorder", cmd)==0){ // contains command
          if(echo){
            printf("preorder\n");
          }
          treemap_print_preorder(treemap);
      }

      else if(strcmp("save", cmd)==0){ // save command
          char fname[128];
          fscanf(stdin,"%s", fname);
          if(echo){
            printf("save %s\n",fname);
          }
          treemap_save(treemap, fname);
      }

      else if(strcmp("load", cmd)==0){ // load command
          char fname[128];
          fscanf(stdin,"%s", fname);
          if(echo){
            printf("load %s\n",fname);
          }
          if (treemap_load(treemap, fname) == 0) {
              printf("load failed\n");
          }
      }

      else{ // unknown command
        if(echo){
          printf("%s\n",cmd);
        }
        printf("unknown command %s\n",cmd);
      }
    }

    // end main while loop
    treemap_clear(treemap);
    free(treemap);
    return 0;
  }
