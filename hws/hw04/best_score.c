#include <stdio.h>

typedef struct {
  char name[128];               // name of student
  double score;                 // score on exam
} grade_t;
// struct which allows assignment of name/score such as in
//   best = curgrade;
//   printf("best is now: %s %f\n", best.name, best.score);

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("usage: %s <filename>\n", argv[0]);
    printf("<filename> should have columns of names, numbers as in\n");
    printf("Darlene 91.0\n");
    printf("Angela  76.5\n");
    printf("Elliot  94.5\n");
    printf("Tyrell  87.5\n");
    printf("Dom     70.0\n");
    printf("Phillip 55.5\n");
    return 1;
  }

  // FILL IN YOUR CODE HERE

  return 0;
}
