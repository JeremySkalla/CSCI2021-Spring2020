// Jeremy Skalla

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clock.h"

// int set_tod_from_secs(int time_of_day_sec, tod_t *tod) {
//     if (time_of_day_sec > 86400 || time_of_day_sec < 0) {
//         return 1;
//     }
//     if (time_of_day_sec >= 43200) {
//         tod->ispm = 1;
//     }
//     else {
//         tod->ispm = 0;
//     }
//     // Hours changing if over 12 hours (because we're not using a 24 hour clock)
//     tod->hours = time_of_day_sec / 3600;
//     if (tod->hours > 12) {
//         tod->hours -= 12;
//     }
//     // If hours is 0, set to 12 (for 12:00-12:59 AM)
//     else if (tod->hours == 0) {
//         tod->hours = 12;
//     }
//     time_of_day_sec %= 3600;
//     tod->minutes = time_of_day_sec / 60;
//     tod->seconds = time_of_day_sec % 60;
//     return 0;
// }

// int set_display_bits_from_tod(tod_t tod, int *display) {
//     if (tod.hours > 12 || tod.hours < 0 || tod.minutes > 60 || tod.minutes < 0 || tod.seconds > 60 || tod.seconds < 0) {
//         return 1;
//     }
//
//     // Setting up bit array
//     int bits[10];
//     bits[0] = 0b0111111;
//     bits[1] = 0b0000110;
//     bits[2] = 0b1011011;
//     bits[3] = 0b1001111;
//     bits[4] = 0b1100110;
//     bits[5] = 0b1101101;
//     bits[6] = 0b1111101;
//     bits[7] = 0b0000111;
//     bits[8] = 0b1111111;
//     bits[9] = 0b1101111;
//
//     // Getting integers for each place on clock
//     int min_ones = tod.minutes % 10;
//     int min_tens = (tod.minutes - min_ones)/10;
//     int hour_ones = tod.hours % 10;
//     int hour_tens = (tod.hours - hour_ones)/10;
//     int am_or_pm = 0b1;
//     if (tod.ispm == 1) {
//         am_or_pm = am_or_pm << 29;
//     }
//     else {
//         am_or_pm = am_or_pm << 28;
//     }
//
//     // Updating display with proper bits
//     *display = 0b0000000;
//     min_ones = bits[min_ones];
//     min_tens = bits[min_tens] << 7;
//     hour_ones = bits[hour_ones] << 14;
//     if (hour_tens == 1) {
//         hour_tens = bits[1] << 21;
//     }
//     else {
//         hour_tens = 0b0000000 << 21;
//     }
//     *display = am_or_pm | hour_tens | hour_ones | min_tens | min_ones;
//     return 0;
// }

// int clock_update() {
//     // Haha
//     tod_t myClockIsHuge;
//     if (set_tod_from_secs(TIME_OF_DAY_SEC, &myClockIsHuge) == 1) {
//         return 1;
//     }
//     //Check if display doesn't work
//     if (set_display_bits_from_tod(myClockIsHuge, &CLOCK_DISPLAY_PORT) == 1) {
//         return 1;
//     }
//     return 0;
// }
