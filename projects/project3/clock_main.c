// DO NOT MODIFY
// 
// LCD Clock simulator. Read a # of seconds from the beginning of the
// day from the command line and show the results of running functions
// from clock_update.c on the screen. Makes use of functions from
// clock_clock.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clock.h"

int main(int argc, char **argv){

  if(argc < 2){                 // Set TIME_OF_DAY_SEC to the actual time
    time_t rawtime;             // Get raw time with system calls
    time( &rawtime );
    struct tm *info;              // Store broken down time
    info = localtime( &rawtime ); // Get a broken down time

    // Calculate the seconds since the beginning of the day
    TIME_OF_DAY_SEC = info->tm_sec + 60*info->tm_min + 60*60*info->tm_hour;
  }
  else{                         // Set time based on argument given
    TIME_OF_DAY_SEC = atoi(argv[1]);
  }
  printf("TIME_OF_DAY_SEC set to: %d\n", TIME_OF_DAY_SEC);

  int time_max = 24 * 60 * 60;
  if(TIME_OF_DAY_SEC >= time_max){
    printf("Time %d exceeds max %d\n",TIME_OF_DAY_SEC,time_max);
    return -1;
  }

  tod_t tod;
  int result = set_tod_from_secs(TIME_OF_DAY_SEC, &tod);

  printf("set_tod_from_secs( %5d, &tod );\n",TIME_OF_DAY_SEC);

  printf("tod is {       \n"); 
  printf("  .hours   = %d\n",tod.hours);
  printf("  .minutes = %d\n",tod.minutes);
  printf("  .seconds = %d\n",tod.seconds);
  printf("  .ispm    = %d\n",tod.ispm);
  printf("}              \n");
  printf("Simulated time is: %02d : %02d : %02d %s\n",
         tod.hours,tod.minutes,tod.seconds,(tod.ispm ? "pm" : "am"));

  if(result != 0){
    printf("set_tod_from_secs() returned non-zero: %d\n",result);
    return 1;
  }

  printf("\nChecking results for display bits\n");
  
  int state;
  result = set_display_bits_from_tod(tod, &state);
  printf("set_display_bits_from_tod(tod, &state);\n");

  printf("\nstate is:\n");
  printf("bits:  "); showbits(state); printf("\n");
  // printf("index: 10987654 32109876 54321098 76543210\n");
  // printf("        30         20         10          \n");

  if(result != 0){
    printf("set_display_bits_from_tod() returned non-zero: %d\n",result);
    return 1;
  }

  printf("\nRunning clock_update()\n");

  clock_update();

  printf("\nCLOCK_DISPLAY_PORT is:\n");
  printf("bits:  "); showbits(CLOCK_DISPLAY_PORT); printf("\n");
  // printf("index: 10987654 32109876 54321098 76543210\n");
  // printf("        30         20         10          \n");

  printf("\nClock Display:\n");
  print_clock();

  return 0;
}
