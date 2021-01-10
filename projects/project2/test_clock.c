#include "clock.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRINT_TEST sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\"} P==1{print}' %s", __LINE__, __FILE__); \
                   system(sysbuf);

void test_print_tod(tod_t tod){
  printf("tod = {\n"); 
  printf("  .hours   = %d,\n",tod.hours);
  printf("  .minutes = %d,\n",tod.minutes);
  printf("  .seconds = %d,\n",tod.seconds);
  printf("  .ispm    = %d,\n",tod.ispm);
  printf("}\n");
}

int main(int argc, char *argv[]){
  int all = 0;
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  if(strcmp(test_name, "all")==0){
    all = 1;
  }

  if(0){}

  if( all==1 || strcmp( test_name, "midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 0;               // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "midnight-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 12,
      .minutes = 0,
      .seconds = 0,
      .ispm    = 0,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  = 0;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST


  if( all==1 || strcmp( test_name, "after-midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 101;             // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-midnight-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 12,
      .minutes = 1,
      .seconds = 41,
      .ispm    = 0,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   101;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1am-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 4170;            // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1am-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 1,
      .minutes = 9,
      .seconds = 30,
      .ispm    = 0,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1am-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   4170;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST


  if( all==1 || strcmp( test_name, "nearly-noon-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 43199;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-noon-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 11,
      .minutes = 59,
      .seconds = 59,
      .ispm    = 0,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-noon-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   43199;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST


  if( all==1 || strcmp( test_name, "is-noon-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 43200;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "is-noon-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 12,
      .minutes = 0,
      .seconds = 0,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "is-noon-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   43200;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1pm-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 47089;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1pm-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 1,
      .minutes = 4,
      .seconds = 49,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-1pm-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   47089;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-six-pm-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 67089;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-six-pm-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 6,
      .minutes = 38,
      .seconds = 9,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "after-six-pm-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   67089;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-midnight-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 86399;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-midnight-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 11,
      .minutes = 59,
      .seconds = 59,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "nearly-midnight-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   86399;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "afternoon-set" )==0 ) {
    PRINT_TEST;
    // Tests whether set_tod_from_secs() sets
    // the time correctly for input SECS
    int SECS = 46348;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // should be changed
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "afternoon-bits" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() sets
    // the the specified integer bits correctly from
    // a tod struct
    tod_t tod = {
      .hours   = 12,
      .minutes = 52,
      .seconds = 28,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST

  if( all==1 || strcmp( test_name, "afternoon-update" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly changes
    // CLOCK_DISPLAY_PORT to target bits based on
    // TIME_OF_DAY_SEC
    TIME_OF_DAY_SEC  =   46348;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // updates DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST


  if( all==1 || strcmp( test_name, "seconds-negative" )==0 ) {
    PRINT_TEST;
    // Tests whether the set_tod_from_secs() function
    // returns an error if passed an out-of-range
    // seconds. Should return 1 and not change the tod.
    int SECS = -128;            // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // SHOULD NOT CHANGE
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");

  } // ENDTEST


  if( all==1 || strcmp( test_name, "seconds-too-big" )==0 ) {
    PRINT_TEST;
    // Tests whether the set_tod_from_secs() function
    // returns an error if passed an out-of-range
    // seconds. Should return 1 and not change the tod.
    int SECS = 90000;           // arg to set_tod()
    tod_t tod = {
      .hours   = -3,
      .minutes = -5,
      .seconds = -7,
      .ispm    = -1,
    };                          // SHOULD NOT CHANGE
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int ret = set_tod_from_secs( SECS, &tod );

    printf("returned: %d\n",ret);
    test_print_tod( tod );
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT);
    printf("\n");

  } // ENDTEST

  if( all==1 || strcmp( test_name, "minutes-range" )==0 ) {
    PRINT_TEST;
    // Tests whether set_display_bits_from_tod() checks
    // ranges and returns and error. Should return 1
    // and not change the bits integer.
    tod_t tod = {
      .hours   = 8,
      .minutes = 72,
      .seconds = 23,
      .ispm    = 1,
    };
    TIME_OF_DAY_SEC  = -1;      // should stay -1
    CLOCK_DISPLAY_PORT = -1;    // should stay -1

    int bits = -1;              // SHOULD NOT CHANGE
    int ret = set_display_bits_from_tod(tod, &bits);
    
    printf("returned: %d\n",ret);
    printf("bits:               ");
    showbits( bits ); printf("\n");
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST


  if( all==1 || strcmp( test_name, "update-fails" )==0 ) {
    PRINT_TEST;
    // Tests whether clock_update() correctly fails on
    // bad seconds.
    TIME_OF_DAY_SEC  =   91234;
    CLOCK_DISPLAY_PORT = -1;

    int ret = clock_update();   // don't change DISPLAY

    printf("returned: %d\n",ret);
    printf("TIME_OF_DAY_SEC: %d\n",TIME_OF_DAY_SEC);
    printf("CLOCK_DISPLAY_PORT: ");
    showbits(CLOCK_DISPLAY_PORT); printf("\n");
  } // ENDTEST



  // else{
  //   printf("No test named '%s' found\n",test_name);
  //   return 1;
  // }
  return 0;
}
