#include <stdio.h>
#include <assert.h>


#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10


#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13


#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

#define INVALID_INPUT (-1)


#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12


#define TRUE 1
#define FALSE 0


#define AET_DAYLIGHT_SAVING_END_STOP 1700
#define AET_DAYLIGHT_SAVING_END_BEGIN 1600
#define AET_DAYLIGHT_SAVING_START_STOP 1600
#define AET_DAYLIGHT_SAVING_START_BEGIN 1600

#define ACT_DAYLIGHT_SAVING_END_STOP 1700
#define ACT_DAYLIGHT_SAVING_END_BEGIN 1600
#define ACT_DAYLIGHT_SAVING_START_STOP 1600
#define ACT_DAYLIGHT_SAVING_START_BEGIN 1600

#define LHT_DAYLIGHT_SAVING_END_STOP 1530
#define LHT_DAYLIGHT_SAVING_END_BEGIN 1500
#define LHT_DAYLIGHT_SAVING_START_STOP 1530
#define LHT_DAYLIGHT_SAVING_START_BEGIN 1530

#define NZ_DAYLIGHT_SAVING_END_STOP 1500
#define NZ_DAYLIGHT_SAVING_END_BEGIN 1400
#define NZ_DAYLIGHT_SAVING_START_STOP 1500
#define NZ_DAYLIGHT_SAVING_START_BEGIN 1500

#define MONTH_DAY_START 1
#define MONTH_DAY_END 31

#define MONTH_START 1
#define MONTH_END 12

#define AUST_FIRST_SUNDAY_OTM 6
#define NZ_FIRST_SUNDAY_OTM 29

#define MAX_MINUTES 60
#define MAX_HOURS 2400

#define HOUR_DIFFERENCE 100

int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);


int aust_daylight_saving_dates(int town, int utc_month, int utc_day, int utc_time);

int ACT_daylight_saving_dates(int town, int utc_month, int utc_day, int utc_time);
int AET_daylight_saving_dates(int town, int utc_month, int utc_day, int utc_time);
int LHT_daylight_saving_dates(int utc_month, int utc_day, int utc_time);
int NZ_daylight_saving_dates(int utc_month, int utc_day, int utc_time);

int minutes_to_hours(int utc_time, int timezone);


int daylight_saving_AET(int town, int utc_month, int utc_day, int utc_time);
int daylight_saving_ACT(int town, int utc_month, int utc_day, int utc_time);
int daylight_saving_LHT(int utc_month, int utc_day, int utc_time);
int daylight_saving_NZT(int utc_month, int utc_day, int utc_time);

int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);

    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}


int get_local_time(int town, int utc_month, int utc_day, int utc_time) {

    int AET, ACT, LHT, NZT, AWST, ACWST, final_time;
    AET = daylight_saving_AET(town, utc_month, utc_day, utc_time);
    ACT = daylight_saving_ACT(town, utc_month, utc_day, utc_time);
    LHT = daylight_saving_LHT(utc_month, utc_day, utc_time);
    NZT = daylight_saving_NZT(utc_month, utc_day, utc_time);
    AWST = TIMEZONE_AWST_OFFSET;
    ACWST = TIMEZONE_ACWST_OFFSET;

    // checking for valid month input
    if (utc_month >= MONTH_START && utc_month <= MONTH_END){

        // checking for valid day input
        if (utc_day >= 1 && utc_day <= 31){

            // checking for valid time input
            if (utc_time >= 0 && utc_time <= 2359){

                // checking for valid town input
                if (town >= 0 || town <= 13){

                    if (town == TOWN_BRISBANE){
                        final_time = minutes_to_hours(utc_time, AET);
                        return final_time;

                    } else if (town == TOWN_CANBERRA){
                        final_time = minutes_to_hours(utc_time, AET);
                        return final_time;

                    } else if (town == TOWN_HOBART){
                        final_time = minutes_to_hours(utc_time, AET);
                        return final_time;

                    } else if (town == TOWN_MELBOURNE){
                        final_time = minutes_to_hours(utc_time, AET);
                        return final_time;

                    } else if (town == TOWN_SYDNEY){
                        final_time = minutes_to_hours(utc_time, AET);
                        return final_time;

                    } else if (town == TOWN_ADELAIDE){
                        final_time = minutes_to_hours(utc_time, ACT);
                        return final_time;

                    } else if (town == TOWN_BROKEN_HILL){
                        final_time = minutes_to_hours(utc_time, ACT);
                        return final_time;

                    } else if (town == TOWN_DARWIN){
                        final_time = minutes_to_hours(utc_time, ACT);
                        return final_time;

                    } else if (town == TOWN_EUCLA){
                        final_time = minutes_to_hours(utc_time, ACWST);
                        return final_time;

                    } else if (town == TOWN_LORD_HOWE_IS){
                        final_time = minutes_to_hours(utc_time, LHT);
                        return final_time;

                    } else if (town == TOWN_PERTH){
                        final_time = minutes_to_hours(utc_time, AWST);
                        return final_time;

                    } else if (town == TOWN_AUCKLAND){
                        final_time = minutes_to_hours(utc_time, NZT);
                        return final_time;

                    } else if (town == TOWN_CHRISTCHURCH){
                        final_time = minutes_to_hours(utc_time, NZT);
                        return final_time;

                    // remaining town not satisfying the above if statements is TOWN_WELLINGTON
                    } else {
                        final_time = minutes_to_hours(utc_time, NZT);
                        return final_time;
                    }

                // ending if statement for invalid town input
                } else {
                    return INVALID_INPUT;
                }

            // ending if statement for invalid time input
            } else {
                return INVALID_INPUT;
            }

        // ending if statement for invalid day input
        } else {
            return INVALID_INPUT;
        }

    // ending if statement for invalid month input
    } else {
        return INVALID_INPUT;
    }

}


int LHT_daylight_saving_dates(int utc_month, int utc_day, int utc_time){
    int daylight_saving_true = TRUE;
    int daylight_saving_false = FALSE;


    // daylight saving from Jan to Feb
    if (utc_month <= FEB && utc_month >= JAN){
        return daylight_saving_true;

    // daylight saving from March 1st to 30th
    } else if (utc_month == MAR && utc_day >= MONTH_DAY_START && utc_day < MONTH_DAY_END){
        return daylight_saving_true;

    // daylight saving on March 31st, stopping at 15:30 UTC
    } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time < LHT_DAYLIGHT_SAVING_END_STOP){
        return daylight_saving_true;

    // stops daylight saving on March 31st, starts standard time from 15:00 UTC
    } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time >= LHT_DAYLIGHT_SAVING_END_BEGIN){
        return daylight_saving_false;

    // standard times from April to September
    } else if (utc_month >= APR && utc_month <= SEP){
        return daylight_saving_false;

    // standard times from 1st Oct to 5th Oct
    } else if (utc_month == OCT && utc_day >= MONTH_DAY_START && utc_day < AUST_FIRST_SUNDAY_OTM){
        return daylight_saving_false;

    // standard times on 6 Oct, stopping at 15:30 UTC
    } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time < LHT_DAYLIGHT_SAVING_START_STOP){
        return daylight_saving_false;

    // daylight saving resumes on 6 Oct, adding 30 mins to the clock
    } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time >= LHT_DAYLIGHT_SAVING_START_BEGIN){
        return daylight_saving_true;

    // daylight saving from the remaining days in Oct to Dec
    } else if (utc_month >= OCT && utc_month <= DEC){
        return daylight_saving_true;

    } else {
        return INVALID_INPUT;

    }
}

int AET_daylight_saving_dates(int town, int utc_month, int utc_day, int utc_time){
    int daylight_saving_true = TRUE;
    int daylight_saving_false = FALSE;

    // towns which dont participate in daylight saving
    if (town == TOWN_BRISBANE){
        return daylight_saving_false;

    } else {

        // daylight saving from Jan to Feb
        if (utc_month <= FEB && utc_month >= JAN){
            return daylight_saving_true;

        // daylight saving from March 1st to 30th
        } else if (utc_month == MAR && utc_day >= MONTH_DAY_START && utc_day < MONTH_DAY_END){
            return daylight_saving_true;

        // daylight saving on March 31st, stopping at 17:00 UTC
        } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time < AET_DAYLIGHT_SAVING_END_STOP){
            return daylight_saving_true;

        // stops daylight saving on March 31st, starts standard time from 16:00 UTC
        } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time >= AET_DAYLIGHT_SAVING_END_BEGIN){
            return daylight_saving_false;

        // standard times from April to September
        } else if (utc_month >= APR && utc_month <= SEP){
            return daylight_saving_false;

        // standard times from 1st Oct to 5th Oct
        } else if (utc_month == OCT && utc_day >= MONTH_DAY_START && utc_day < AUST_FIRST_SUNDAY_OTM){
            return daylight_saving_false;

        // standard times on 6 Oct, stopping at 15:00 UTC
        } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time < AET_DAYLIGHT_SAVING_START_STOP){
            return daylight_saving_false;

        // daylight saving resumes on 6 Oct, adding 1 hour to the clock
        } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time >= AET_DAYLIGHT_SAVING_START_BEGIN){
            return daylight_saving_true;

        // daylight saving from the remaining days in Oct to Dec
        } else if (utc_month >= OCT && utc_month <= DEC){
            return daylight_saving_true;

        } else {
            return INVALID_INPUT;

        }
    }
}

int ACT_daylight_saving_dates(int town, int utc_month, int utc_day, int utc_time){
    int daylight_saving_true = TRUE;
    int daylight_saving_false = FALSE;


    // towns which dont participate in daylight saving
    if (town == TOWN_DARWIN){
        return daylight_saving_false;

    } else {

        // daylight saving from Jan to Feb
        if (utc_month <= FEB && utc_month >= JAN){
            return daylight_saving_true;

        // daylight saving from March 1st to 30th
        } else if (utc_month == MAR && utc_day >= MONTH_DAY_START && utc_day < MONTH_DAY_END){
            return daylight_saving_true;

        // daylight saving on March 31st, stopping at 17:00 UTC
        } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time < ACT_DAYLIGHT_SAVING_END_STOP){
            return daylight_saving_true;

        // stops daylight saving on March 31st, starts standard time from 16:00 UTC
        } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time >= ACT_DAYLIGHT_SAVING_END_BEGIN){
            return daylight_saving_false;

        // standard times from April to September
        } else if (utc_month >= APR && utc_month <= SEP){
            return daylight_saving_false;

        // standard times from 1st Oct to 5th Oct
        } else if (utc_month == OCT && utc_day >= MONTH_DAY_START && utc_day < AUST_FIRST_SUNDAY_OTM){
            return daylight_saving_false;

        // standard times on 6 Oct, stopping at 15:00 UTC
        } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time < ACT_DAYLIGHT_SAVING_START_STOP){
            return daylight_saving_false;

        // daylight saving resumes on 6 Oct, adding 1 hour to the clock
        } else if (utc_month == OCT && utc_day == AUST_FIRST_SUNDAY_OTM && utc_time >= ACT_DAYLIGHT_SAVING_START_BEGIN){
            return daylight_saving_true;

        // daylight saving from the remaining days in Oct to Dec
        } else if (utc_month >= OCT && utc_month <= DEC){
            return daylight_saving_true;

        } else {
            return INVALID_INPUT;

        }
    }
}

int NZ_daylight_saving_dates(int utc_month, int utc_day, int utc_time){
    int daylight_saving_true = TRUE;
    int daylight_saving_false = FALSE;


    // daylight saving from Jan to Feb
    if (utc_month <= FEB && utc_month >= JAN){
        return daylight_saving_true;

    // daylight saving from March 1st to 30th
    } else if (utc_month == MAR && utc_day >= MONTH_DAY_START && utc_day < MONTH_DAY_END){
        return daylight_saving_true;

    // daylight saving on March 31st, stopping at 17:00 UTC
    } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time < NZ_DAYLIGHT_SAVING_END_STOP){
        return daylight_saving_true;

    // stops daylight saving on March 31st, starts standard time from 16:00 UTC
    } else if (utc_month == MAR && utc_day == MONTH_DAY_END && utc_time >= NZ_DAYLIGHT_SAVING_END_BEGIN){
        return daylight_saving_false;

    // standard times from April to August
    } else if (utc_month >= APR && utc_month <= AUG){
        return daylight_saving_false;

    // standard times from 1st Sep to 28th Sep
    } else if (utc_month == SEP && utc_day >= MONTH_DAY_START && utc_day < NZ_FIRST_SUNDAY_OTM){
        return daylight_saving_false;

    // standard times on 29 Sep, stopping at 15:00 UTC
    } else if (utc_month == SEP && utc_day == NZ_FIRST_SUNDAY_OTM && utc_time < NZ_DAYLIGHT_SAVING_START_STOP){
        return daylight_saving_false;

    // daylight saving resumes on 29 Sep, adding 1 hour to the clock
    } else if (utc_month == SEP && utc_day == NZ_FIRST_SUNDAY_OTM && utc_time >= NZ_DAYLIGHT_SAVING_START_BEGIN){
        return daylight_saving_true;

    // daylight saving from Oct to Dec
    } else if (utc_month >= OCT && utc_month <= DEC){
        return daylight_saving_true;

    } else {
        return INVALID_INPUT;

    }
}

int minutes_to_hours (int utc_time, int timezone){
    int hours, minutes;
    // splitting the time offset into hours and minutes
        hours = (timezone/HOUR_DIFFERENCE);
        minutes = (timezone%HOUR_DIFFERENCE);


    int hours_utc, minutes_utc;
    // splitting the UTC time into hours and minutes
        hours_utc = (utc_time/HOUR_DIFFERENCE);
        minutes_utc = (utc_time%HOUR_DIFFERENCE);

    int total_hours;
    int overall_minutes, overall_minutes_leftover_minutes;

    // adding the minutes of both UTC time and offset time
        overall_minutes = minutes_utc + minutes;


        if (overall_minutes >= MAX_MINUTES){
        // getting rid of excess minutes as there can only be 60 mins in an hour
            total_hours = hours + hours_utc + 1;
            overall_minutes_leftover_minutes = overall_minutes - MAX_MINUTES;

        } else {
            total_hours = hours + hours_utc;
            overall_minutes_leftover_minutes = overall_minutes;
        }


    int final_time_uncalculated, final_time_calculated;
        final_time_uncalculated = (total_hours*HOUR_DIFFERENCE) + overall_minutes_leftover_minutes;

        if (final_time_uncalculated >= MAX_HOURS){
        // finalising the calculated time into a 24 hour frame
        final_time_calculated = final_time_uncalculated - MAX_HOURS;
        return final_time_calculated;

        } else {
        final_time_calculated = final_time_uncalculated;
        return final_time_calculated;

        }
}


int daylight_saving_AET (int town, int utc_month, int utc_day, int utc_time){
    int timezone;

	if (AET_daylight_saving_dates(town, utc_month, utc_day, utc_time) == TRUE){
        timezone = TIMEZONE_AEDT_OFFSET;
		return timezone;

	} else if (AET_daylight_saving_dates(town, utc_month, utc_day, utc_time) == FALSE){
        timezone = TIMEZONE_AEST_OFFSET;
		return timezone;

	} else {
		return INVALID_INPUT;

	}
}

int daylight_saving_ACT (int town, int utc_month, int utc_day, int utc_time){
        int timezone;

    if (ACT_daylight_saving_dates(town, utc_month, utc_day, utc_time) == TRUE){
        timezone = TIMEZONE_ACDT_OFFSET;
        return timezone;

    } else if (ACT_daylight_saving_dates(town, utc_month, utc_day, utc_time) == FALSE){
        timezone = TIMEZONE_ACST_OFFSET;
        return timezone;

    } else {
        return INVALID_INPUT;

    }
}

int daylight_saving_LHT(int utc_month, int utc_day, int utc_time){
        int timezone;

     if (LHT_daylight_saving_dates(utc_month, utc_day, utc_time) == TRUE){
        timezone = TIMEZONE_LHDT_OFFSET;
        return timezone;

    } else if (LHT_daylight_saving_dates(utc_month, utc_day, utc_time) == FALSE){
        timezone = TIMEZONE_LHST_OFFSET;
        return timezone;

    } else {
        return INVALID_INPUT;

    }
}

int daylight_saving_NZT(int utc_month, int utc_day, int utc_time){
        int timezone;

    if (NZ_daylight_saving_dates(utc_month, utc_day, utc_time) == TRUE){
        timezone = TIMEZONE_NZDT_OFFSET;
        return timezone;

    } else if (NZ_daylight_saving_dates(utc_month, utc_day, utc_time) == FALSE){
        timezone = TIMEZONE_NZST_OFFSET;
        return timezone;

    } else {
        return INVALID_INPUT;

    }

}


// My testing strategy is to test at the days which daylight saving occurs as it is more likely for errors to occur
// at those areas.

// I made sure to include at least 3 assert statements per timezone (AET, ACT, LHT etc.)
// These assert statements are tested around the time which daylight saving occurs e.g. for AET and ACT
// timezones, this occurs around 1400/1500 UTC.

// For the zones which do not participate in daylight saving, I tested at least twice, one at a random time
// and another around the 23 hour mark. This will ensure that  my minute_to_hour function works as intended.

// I also tested all the invalid possibilities e.g. town 14.
// This will make sure that I do not have problems with my code in detecting invalid inputs.

// To finish off, I used random towns, dates and times to check over my code.


void run_unit_tests(void) {

    // UTC midnight on 20th March -> time in Sydney: 11am AEDT
    assert(get_local_time(TOWN_SYDNEY, 3, 20, 0) == 1100);

    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);

    // 14 is not a valid town
    assert(get_local_time(14, 0, 0, 0) == INVALID_INPUT);

    // 34 is not a valid day
    assert(get_local_time(TOWN_LORD_HOWE_IS, 0, 34, 0) == INVALID_INPUT);

    // 25:35 is not a valid time
    assert(get_local_time(TOWN_CANBERRA, 0, 0, 2535) == INVALID_INPUT);

    // 22:90 is not a valid time
    assert(get_local_time(TOWN_BRISBANE, 0, 0, 2290) == INVALID_INPUT);

    // 14 is not a valid month
    assert(get_local_time(TOWN_DARWIN, 14, 0, 0) == INVALID_INPUT);

    // UTC 17:00 on 31st March -> time in Sydney: 3am
    assert(get_local_time(TOWN_SYDNEY, 3, 31, 1700) == 300);

    // UTC 15:00 on 31st March -> time in Melbourne: 2am
    assert(get_local_time(TOWN_MELBOURNE, 3, 31, 1500) == 200);

    // UTC 16:00 on 6 October -> time in Canberra: 3am
    assert(get_local_time(TOWN_CANBERRA, 10, 6, 1600) == 300);

    // UTC 13:50 on 1st April -> time in Brisbane: 11:50pm
    assert(get_local_time(TOWN_BRISBANE, 4, 1, 1350) == 2350);

    // UTC 23:20 on 31 March -> time in Brisbane: 9:20am
    assert(get_local_time(TOWN_BRISBANE, 3, 31, 2320) == 920);

    // UTC 17:30 on 31 March -> time in Adelaide: 3:00am
    assert(get_local_time(TOWN_ADELAIDE, 3, 31, 1730) == 300);

    // UTC 15:30 on 31 March -> time in Broken Hill: 2:00am
    assert(get_local_time(TOWN_BROKEN_HILL, 3, 31, 1530) == 200);

    // UTC 15:30 on 6 Oct -> time in Adelaide: 1:00am
    assert(get_local_time(TOWN_ADELAIDE, 10, 6, 1530) == 100);

    // UTC 16:30 on 6 Oct -> time in Broken Hill: 3:00am
    assert(get_local_time(TOWN_BROKEN_HILL, 10, 6, 1630) == 300);

    // UTC 16:30 on 6 Oct -> time in Darwin: 2:00am
    assert(get_local_time(TOWN_DARWIN, 10, 6, 1630) == 200);

    // UTC 17:30 on 6 Oct -> time in Darwin: 3:00am
    assert(get_local_time(TOWN_DARWIN, 10, 6, 1730) == 300);

    // UTC 17:30 on 31 March -> time in Darwin: 3:00am
    assert(get_local_time(TOWN_DARWIN, 3, 31, 1730) == 300);

    // UTC 16:30 on 31 March -> time in Darwin: 2:00am
    assert(get_local_time(TOWN_DARWIN, 3, 31, 1630) == 200);

    // UTC 16:00 on 6 Oct -> time in Lord Howes Island: 3:00am
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1600) == 300);

    // UTC 15:00 on 6 Oct -> time in Lord Howes Island: 1:30am
    assert(get_local_time(TOWN_LORD_HOWE_IS, 10, 6, 1500) == 130);

    // UTC 16:30 on 31 Mar -> time in Lord Howes Island: 3:00am
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1630) == 300);

    // UTC 14:30 on 31 Mar -> time in Lord Howes Island: 1:30am
    assert(get_local_time(TOWN_LORD_HOWE_IS, 3, 31, 1430) == 130);

    // UTC 12:00 on 31 Mar -> time in Christchurch: 1:00am
    assert(get_local_time(TOWN_CHRISTCHURCH, 3, 31, 1200) == 100);

    // UTC 12:00 on 29 Sep -> time in Wellington: Midnight

    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1200) == 0);

    // UTC 15:00 on 29 Sep -> time in Christchurch: 4:00am
    assert(get_local_time(TOWN_CHRISTCHURCH, 9, 29, 1500) == 400);

    // UTC 13:00 on 29 Sep -> time in Wellington: 1:00am
    assert(get_local_time(TOWN_WELLINGTON, 9, 29, 1300) == 100);

    // UTC 15:00 on 6th Oct -> time in Wellington: 4:00am
    assert(get_local_time(TOWN_WELLINGTON, 10, 6, 1500) == 400);

    // UTC 23:30 on 6th Feb -> time in Lowd Howe Island: 10:30am
    assert(get_local_time(TOWN_LORD_HOWE_IS, 2, 6, 2330) == 1030);

    // UTC 8:26 on 25th Nov -> time in Hobart: 7:26pm
    assert(get_local_time(TOWN_HOBART, 11, 25, 826) == 1926);

    // UTC 1:09 on 19 Dec -> time in Hobart: 12:09pm
    assert(get_local_time(TOWN_HOBART, 12, 19, 109) == 1209);

    // UTC 9:00 on 28 Nov -> time in Hobart: 8:00pm
    assert(get_local_time(TOWN_HOBART, 11, 28, 900) == 2000);

    // UTC 17:38 on 1 April -> time in Melbourne: 3:38am AEST
    assert(get_local_time(TOWN_MELBOURNE, 4, 1, 1738) == 338);

    // UTC 3:23 on 21 May -> time in Eucla: 12:08pm ACWST
    assert(get_local_time(TOWN_EUCLA, 5, 21, 323) == 1208);

    // UTC 9:40 on 29 July -> time in Adelaide: 7:10pm ACST
    assert(get_local_time(TOWN_ADELAIDE, 7, 29, 940) == 1910);

    // UTC 8:15 on 6 June -> time in Perth: 4:15pm AWST
    assert(get_local_time(TOWN_PERTH, 6, 6, 815) == 1615);

    // UTC 4:02 on 29 May -> time in Wellington: 4:02pm NZST
    assert(get_local_time(TOWN_WELLINGTON, 5, 29, 402) == 1602);

    // UTC 9:32 on 19 Aug -> time in Hobart: 7:32pm AEST
    assert(get_local_time(TOWN_HOBART, 8, 19, 932) == 1932);

    // UTC 8:32 on 21 July -> time in Eucla: 5:15pm ACWST
    assert(get_local_time(TOWN_EUCLA, 7, 21, 832) == 1717);

    // UTC 1:53 on 14 Dec -> time in Melbourne: 12:53pm AEDT
    assert(get_local_time(TOWN_MELBOURNE, 12, 14, 153) == 1253);

    // UTC 9:44 on 7 June -> time in Adelaide: 714pm ACST
    assert(get_local_time(TOWN_ADELAIDE, 6, 7, 944) == 1914);

    // UTC 23:!4 on 3 Feb -> time in Eucla: 7:59am ACWST
    assert(get_local_time(TOWN_EUCLA, 2, 3, 2314) == 759);

    // UTC 0:30 on 19 Jan -> time in Sydney: 11:30am AEDT
    assert(get_local_time(TOWN_SYDNEY, 1, 19, 30) == 1130);

    // UTC 23:39 on 16 Feb -> time in Perth: 7:39am AWST
    assert(get_local_time(TOWN_PERTH, 2, 16, 2339) == 739);

    // UTC 23:25 on 7 March -> time in Adelaide: 9:55am ACDT
    assert(get_local_time(TOWN_ADELAIDE, 3, 7, 2325) == 955);

    // UTC 23:57 on 11 Feb -> time in Wellington: 12:57pm NZDT
    assert(get_local_time(TOWN_WELLINGTON, 2, 11, 2357) == 1257);

    // UTC 21:19 on 4 Sep -> time in Perth: 5:19am AWST
    assert(get_local_time(TOWN_PERTH, 9, 4, 2119) == 519);

    // UTC 22:02 on 5 Oct -> time in Eucla: 6:47am ACWST
    assert(get_local_time(TOWN_EUCLA, 10, 5, 2202) == 647);

    // UTC 0:03 on 12 Nov -> time in Christchurch: 1:03pm NZDT
    assert(get_local_time(TOWN_CHRISTCHURCH, 11, 12, 3) == 1303);

    // UTC 14:59 on 25th Aug -> time in Brisbane: 00:59am AEST
    assert(get_local_time(TOWN_BRISBANE, 8, 25, 1459) == 59);

    // UTC 11:11 on 3 Feb -> time in Auckland: 00:11am NZDT
    assert(get_local_time(TOWN_AUCKLAND, 2, 3, 1111) == 11);

    // UTC 23:15 on 21 Sep -> time in Darwin: 8:45am ACST
    assert(get_local_time(TOWN_DARWIN, 9, 21, 2315) == 845);

}
