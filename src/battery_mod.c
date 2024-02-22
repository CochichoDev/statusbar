#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "battery_mod.h"

static char *battery;
static int bat_fd;

/*
 *  Initializes the memory structures used by the time module
 */
char *init_battery() {
    if (!battery)
        battery = (char *) malloc(BATSIZE);
    if (!bat_fd) {
        bat_fd = open("/sys/class/power_supply/BAT0/capacity", O_RDONLY);
        //bat_file = fopen("/home/cochicho/test.txt", "r");
        if (!bat_fd) {
            fprintf(stderr, "Couldn't open the battery file. Exiting...\n");
            exit(1);
        }
    }
    return battery;
}

void update_battery_level() {
    int read_bytes = read(bat_fd, battery, BATSIZE);
    battery[read_bytes - 1] = '\0';
    strcat(battery, "\%");
    lseek(bat_fd, 0, SEEK_SET);
}

void destroy_battery() {
    free(battery);
    close(bat_fd);
}
