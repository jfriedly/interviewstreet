#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE *f;

struct tm * parseTime(char * str);

// "Wed Dec 21 22:08:04 2011 200 529 /"
struct tm * parseTime(char * str) {
    struct tm * time;
    char weekday[3], month[3];
    int year;

    sscanf(str, "%s %s %d %d:%d:%d %d %*d %*d %*s", weekday, month, \
                                                    &(time -> tm_mday), \
                                                    &(time -> tm_hour), \
                                                    &(time -> tm_min), \
                                                    &(time -> tm_sec), \
                                                    &year);
    year -= 1900;
    time -> tm_year = year;

    if (weekday[0] == 'S'){
        if (weekday[1] == 'a') {       // Saturday
            time -> tm_wday = 6;
        } else {
            time -> tm_wday = 0;    // Sunday
        }
    } else if (weekday[0] == 'M') {    // Monday
        time -> tm_wday = 1;
    } else if (weekday[0] == 'T') {
        if (weekday[1] == 'u') {       // Tuesday
            time -> tm_wday = 2;
        } else {
            time -> tm_wday = 4;    // Thursday
        }
    } else if (weekday[0] == 'W') {    // Wednesday
        time -> tm_wday = 3;
    } else if (weekday[0] == 'F') {    // Friday
        time -> tm_wday = 5;
    }

    if (month[0] == 'J') {
        if (month[1] == 'a') {       // January
            time -> tm_mon = 0;
        } else if (month[6] == 'n') {// June
            time -> tm_mon = 5;
        } else {
            time -> tm_mon = 6;     // July
        }
    } else if (month[0] == 'F') {    // February
        time -> tm_mon = 1;
    } else if (month[0] == 'M') {
        if (month[6] == 'r') {       // March
            time -> tm_mon = 2;
        } else {
            time -> tm_mon = 4;     // May
        }
    } else if (month[0] == 'A') {
        if (month[1] == 'p') {       // April
            time -> tm_mon = 3;
        } else {
            time -> tm_mon = 7;     // August
        }
    } else if (month[0] == 'S') {    // September
        time -> tm_mon = 8;
    } else if (month[0] == 'O') {    // October
        time -> tm_mon = 9;
    } else if (month[0] == 'N') {    // November
        time -> tm_mon = 10;
    } else if (month[0] == 'D') {    // December
        time -> tm_mon = 11;
    } 

    int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (time -> tm_year % 4 == 0) {
        mdays[1] = 29;
    }
    int i = 0;
    for (i = 0; i < time -> tm_mon; i++) {
        time -> tm_yday += mdays[i];
    }
    /* Days:     1 2 3 4 5 6 7  8  9  0  1  2  3  4
     * Earliest: S M T W T F S |S| M  T  W  T  F  S       mday - wday = 8, 8
     * Earlier:  S S M T W T F  S |S| M  T  W  T  F       mday - wday = 2, 9
     * Early:    F S S M T W T  F  S |S| M  T  W  T       mday - wday = 3, 10
     * Brunch:   T F S S M T W  T  F  S |S| M  T  W       mday - wday = 4, 11
     * Middle:   W T F S S M T  W  T  F  S |S| M  T       mday - wday = 5, 12
     * Late:     T W T F S S M  T  W  T  F  S |S| M       mday - wday = 6, 13
     * Latest:   M T W T F S S  M  T  W  T  F  S |S|      mday - wday = 7, 14
     *
     */

    if (time -> tm_year > 106) {                                // Special DST rules for after 2007
        if (time -> tm_mon > 10 || time -> tm_mon < 2) {
            time -> tm_isdst = 0;
        } else if (time -> tm_mon > 2 && time -> tm_mon < 10) {
            time -> tm_isdst = 1;
        } else if (time -> tm_mon == 2) {                       // Starts on second Sunday in March
            if (time -> tm_mday < 8) {
                time -> tm_isdst = 0;
            } else if (time -> tm_mday > 14) {
                time -> tm_isdst = 1;                           
            } else if (time -> tm_wday != 0) {                  
                if (time -> tm_mday - time -> tm_wday < 8) {    
                    time -> tm_isdst = 0;
                } else if (time -> tm_mday - time -> tm_wday > 8) {
                    time -> tm_isdst = 1;
                } else if (time -> tm_hour < 2) {
                    time -> tm_isdst = 0;
                } else if (time -> tm_hour > 2) {
                    time -> tm_isdst = 1;
                }
            }                                                   
        } else if (time -> tm_mon == 10) {                      // Ends on first Sunday in November
            if (time -> tm_mday > 7) {
                time -> tm_isdst = 0;
            } else if (time -> tm_wday != 0) {
                time -> tm_isdst = 1;
            } else if (time -> tm_hour < 2) {
                time -> tm_isdst = 1;
            } else if (time -> tm_hour > 2) {
                time -> tm_isdst = 0;
            }
        }
    } else {
        printf("Year before 2006!");
    }

    return time;
}


// "Wed Dec 21 22:08:04 2011 200 529 /"
int main(int argc, char *argv[]) // argc = num args, argv[] = args, argv[0] = script
{
    char* filename = argv[1];
    time_t start_time = atoi(argv[2]), end_time = atoi(argv[3]), current_time;
    struct tm * current_tm;
    char line[200];
    int code, time, requests = 0, fofs = 0;
    long response_time = 0;

    f = fopen(filename, "r");
    while(fgets(line, 200, f) != NULL) {
        current_tm = parseTime(line);
        current_time = mktime(current_tm);
        if ((int) start_time <= (int) current_time && (int) current_time <= (int) end_time) {
            requests++;
            sscanf(line, "%*s %*s %*d %*d:%*d:%*d %*d %d %d %*s", &code, &time);
            if (code == 404) {
                fofs++;
            } else {
                response_time += time;
            }
        }
    }

    printf("%d\n", requests);
    printf("%d\n", fofs);
    printf("%f\n", response_time / (float) (requests - fofs));
}
