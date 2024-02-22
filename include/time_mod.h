#include <stdint.h>

// CONSTANT DECLARATION
#define TIMESIZE 10
#define DATESIZE 20

typedef struct {
    char *date;
    char *time;
} Timedate_info;

Timedate_info *init_time();
void get_timedate_info();
void destroy_time();
