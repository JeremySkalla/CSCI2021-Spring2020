#include <stdio.h>
typedef struct{
  double weight;
  int age;
  char name[8];
} dog_t;

void init_dog(dog_t *d){
  strcpy(d->name, "Rolf");
  d->age = 0;
  d->weight = 5.0;
  ////// POSITION A
  return;
}

void birthday(int num, dog_t *d){
  int next = d->age + num;
  if(next < 3){
    d->weight += 10.0;
  }
  ////// POSITION B
  d->age = next;
  return;
}

int main(){
  dog_t dog;
  init_dog(&dog);
  double curwgt = dog.weight;
  birthday(2, &dog);
  printf("%s gained %f pounds\n",
         dog.name, dog.weight-curwgt);
  return 0;
}
