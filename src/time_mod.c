#include <time.h>
#include "time_mod.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static char *date_buf, *time_buf;
static Timedate_info *info;

/*
 *  Initializes the memory structures used by the time module
 */
Timedate_info *init_time() {
    if (!date_buf)
        date_buf = (char *) malloc(DATESIZE);
    if (!time_buf)
        time_buf = (char *) malloc(TIMESIZE);
    if (!info) {
        info = (Timedate_info *) malloc( sizeof(Timedate_info) );
        info->date = date_buf;
        info->time = time_buf;
    }
    if (time_buf && date_buf && info)
        return info;

    return NULL;
}

void get_timedate_info() {
    time_t cur_time = time(&cur_time);
    struct tm *time_info = localtime(&cur_time);

    sprintf(date_buf, "%02d/%02d/%4d", time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900);
    sprintf(time_buf, "%02d:%02d:%02d", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

void destroy_time() {
    free(date_buf);
    free(time_buf);
    free(info);
}
