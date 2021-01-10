#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"

#define CLOCK_MAX_BITS 30

// Global variable used to control the LCD display on the
// clock. Making changes to this variable will change the clock
// time. Type ensures 32 bits.
int32_t CLOCK_DISPLAY_PORT;

// Time of day in seconds. Tied to a hardware clock that automatically
// increments it 1 time per second starting at midnight. The
// simulatator provides a C global variable to emulate this part of
// the hardware. This variable is present when #include "clock.h" is
// used and should not be declared in any user code.
int TIME_OF_DAY_SEC;

// Reset an clock_display to be empty 
void reset_clock_display(clock_display *clock){
  int i,j;
  for(i=0; i<5; i++){
    for(j=0; j<32; j++){
      clock->chars[i][j] = ' ';
    }
    clock->chars[i][31] = '\0';
  }
  clock->chars[1][12] = 'o';
  clock->chars[3][12] = 'o';
}  

// Print an clock_display 
void print_clock_display(clock_display *clock){
  int i=0;
  for(i=0; i<5; i++){
    printf("%s\n",clock->chars[i]);
  }
}  

// Data and functions to set the state of the lcd clock display 

// Position and char in display 
typedef struct {
  int r,c; char ch;
} charpos;
    
// Collection of characters corresponding to one bit in the state being set 
typedef struct {
  int len;                      // number of chars corresponding to this bit
  charpos pos[2];               // position of chars for this bit
} charpos_coll;

// Correspondence of bit positions to which characters should be set 
charpos_coll bits2chars[CLOCK_MAX_BITS] = {
  { .len=2, .pos={{ 0,19,'~'}, { 0,20,'~'},} }, //  0
  { .len=1, .pos={{ 1,21,'|'},             } }, //  1
  { .len=1, .pos={{ 3,21,'|'},             } }, //  2
  { .len=2, .pos={{ 4,19,'~'}, { 4,20,'~'},} }, //  3
  { .len=1, .pos={{ 3,18,'|'},             } }, //  4
  { .len=1, .pos={{ 1,18,'|'},             } }, //  5
  { .len=2, .pos={{ 2,19,'~'}, { 2,20,'~'},} }, //  6

  { .len=2, .pos={{ 0,14,'~'}, { 0,15,'~'},} }, //  7 
  { .len=1, .pos={{ 1,16,'|'},             } }, //  8 
  { .len=1, .pos={{ 3,16,'|'},             } }, //  9 
  { .len=2, .pos={{ 4,14,'~'}, { 4,15,'~'},} }, // 10 
  { .len=1, .pos={{ 3,13,'|'},             } }, // 11 
  { .len=1, .pos={{ 1,13,'|'},             } }, // 12 
  { .len=2, .pos={{ 2,14,'~'}, { 2,15,'~'},} }, // 13 

  { .len=2, .pos={{ 0, 9,'~'}, { 0,10,'~'},} }, // 14   
  { .len=1, .pos={{ 1,11,'|'},             } }, // 15   
  { .len=1, .pos={{ 3,11,'|'},             } }, // 16   
  { .len=2, .pos={{ 4, 9,'~'}, { 4,10,'~'},} }, // 17   
  { .len=1, .pos={{ 3, 8,'|'},             } }, // 18   
  { .len=1, .pos={{ 1, 8,'|'},             } }, // 19   
  { .len=2, .pos={{ 2, 9,'~'}, { 2,10,'~'},} }, // 20   

  { .len=2, .pos={{ 0, 4,'~'}, { 0, 5,'~'},} }, // 21    
  { .len=1, .pos={{ 1, 6,'|'},             } }, // 22    
  { .len=1, .pos={{ 3, 6,'|'},             } }, // 23    
  { .len=2, .pos={{ 4, 4,'~'}, { 4, 5,'~'},} }, // 24    
  { .len=1, .pos={{ 3, 3,'|'},             } }, // 25    
  { .len=1, .pos={{ 1, 3,'|'},             } }, // 26    
  { .len=2, .pos={{ 2, 4,'~'}, { 2, 5,'~'},} }, // 27    

  { .len=2, .pos={{ 3, 0,'A'}, { 3, 1,'M'},} }, // 28
  { .len=2, .pos={{ 4, 0,'P'}, { 4, 1,'M'},} }, // 29
};

// Assumes ints are at least 32 bits 
void set_clock_display_state(clock_display *clock, int state){
  int i,j;
  int mask = 0x1;
  reset_clock_display(clock);
  for(i=0; i<CLOCK_MAX_BITS; i++){
    //    printf("Checking %d\n",i);
    if( state & (mask << i) ){ // ith bit set, fill in characters 
      //      printf("%d IS SET\n",i);
      charpos_coll coll = bits2chars[i];
      //      printf("Coll len: %d\n",coll.len);
      for(j=0; j<coll.len; j++){
        //        printf("Inner iter %d\n",j);
        charpos pos = coll.pos[j];
        clock->chars[pos.r][pos.c] = pos.ch;
        // print_clock_display(clock);
      }
    }
  }
}


// Use the global CLOCK_DISPLAY_PORT to print the time 
void print_clock(){
  clock_display clock;
  set_clock_display_state(&clock, CLOCK_DISPLAY_PORT);
  print_clock_display(&clock);
  return;
}


// Print the most signficant (right-most) to least signficant bit in
// the integer passed in 
#define INT_BITS 32
void showbits(int x){
  int i;
  int mask = 0x1;
  for(i=INT_BITS-1; i>=0; i--){
    int shifted_mask = mask << i;
    if(shifted_mask & x){
      putchar('1');
    } else {
      putchar('0');
    }
    if(i % 8 == 0){
      putchar(' ');
    }
  }
  // Equivalent short version 
  //    (x&(1<<i)) ? putchar('1'): putchar('0');
}
