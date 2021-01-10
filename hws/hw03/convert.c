// Demonstrate a conversion routine
#include <stdio.h>

int convert(char *str, int *num){
  int negate = 0;               // whether to negate
  int total = 0;                // running total
  for(int pos=0; str[pos] != '\0'; pos++){
    int value = 0;
    char digit = str[pos];
    if(0){} // skip for alignment
    else if(digit == '0'){ value = 0; } // determine digit value
    else if(digit == '1'){ value = 1; }
    else if(digit == '2'){ value = 2; }
    else if(digit == '3'){ value = 3; }
    else if(digit == '4'){ value = 4; }
    else if(digit == '5'){ value = 5; }
    else if(digit == '6'){ value = 6; }
    else if(digit == '7'){ value = 7; }
    else if(digit == '8'){ value = 8; }
    else if(digit == '9'){ value = 9; }
    else if(digit == '-' && pos==0){  // negative sign at beginning
      negate = 1;
    }
    else {                      // not a valid digit
      printf("'%c' at pos %d not valid for integers\n", digit, pos); 
      return 1;                 // error
    }
    total = total*10 + value;   // update total
  }
  if(negate){                   // check for negation found
    total = -total;             // do negation
  }
  *num = total;                 // set num to total 
  return 0;                     // return success
}

// main invokes convert() on various data
int main(){
  char *str; 
  int num, err;

  str = "124"; num = 0; 
  err = convert(str, &num); // run conversion
  printf("convert(\"%s\",&num): \tnum = %5d, err = %d\n", str,num,err);

  str = "59217"; num = 0; 
  err = convert(str, &num); // run conversion
  printf("convert(\"%s\",&num): \tnum = %5d, err = %d\n", str,num,err);

  str = "-212"; num = 0; 
  err = convert(str, &num); // run conversion
  printf("convert(\"%s\",&num): \tnum = %5d, err = %d\n", str,num,err);

  str = "51a3"; num = 0; 
  err = convert(str, &num); // run conversion
  printf("convert(\"%s\",&num): \tnum = %5d, err = %d\n", str,num,err);

  str = "513-7"; num = 0; 
  err = convert(str, &num); // run conversion
  printf("convert(\"%s\",&num): \tnum = %5d, err = %d\n", str,num,err);

  return 0;
}
