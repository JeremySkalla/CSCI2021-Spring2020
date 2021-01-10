#ifndef CLOCK_H
#define CLOCK_H 1

////////////////////////////////////////////////////////////////////////////////
// clock_update.c structs/functions

// Breaks time down into 12-hour format
typedef struct{
  short hours;
  short minutes;
  short seconds;
  char ispm;
} tod_t;

// Functions to implement for CLOCK Clock Problem
int set_tod_from_secs(int time_of_day, tod_t *tod);
int set_display_bits_from_tod(tod_t tod, int *display);
int clock_update();


////////////////////////////////////////////////////////////////////////////////
// clock_clock.c structs/functions; do not modify

// Global variable used to control the CLOCK display. Making changes to
// this variable will change the clock time 
extern int CLOCK_DISPLAY_PORT;

// Time of day in seconds; set by the hardward, read only 
extern int TIME_OF_DAY_SEC;

// Convenience struct for representing the clock as characters 
typedef struct {
  char chars[5][32];
} clock_display;

// Use the global CLOCK_DISPLAY_PORT to print the time 
void print_clock();

// utility to show the bits of an integer
void showbits(int x);


#endif
