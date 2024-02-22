#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <xcb/xcb.h>

#include "time_mod.h"
#include "battery_mod.h"

int main() {
    // Initialize a xcb connection (access X server)
    xcb_connection_t *conn = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(conn)) {
        fprintf(stderr, "Couldn't connect to X server. Exiting...\n");
        exit(1);
    }
    // Get information about the connection (usefull to iterate over screens)
    const xcb_setup_t *setup = xcb_get_setup(conn);
    // Get the main screen
    xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data;
    // Finally get the root window
    xcb_window_t root_window = screen->root;

    char input[256];

    Timedate_info *time_mod = init_time();
    char *battery = init_battery();

    while(1) {
        get_timedate_info();
        update_battery_level();

        strcpy(input, "| \uf0e7 ");
        strcat(input, battery);
        strcat(input, " \uf0e7");
        strcat(input, " | \ue641 ");
        strcat(input, time_mod->time);
        strcat(input, " \ue641");
        strcat(input, " | ");
        strcat(input, "\ueab0 ");
        strcat(input, time_mod->date);
        strcat(input, " \ueab0 ");

        // Change the title of the root window
        xcb_change_property(conn, XCB_PROP_MODE_REPLACE, root_window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen(input), input);
        xcb_flush(conn);

        sleep(1);
    }
    
    destroy_time();

    // Disconnect from the X server
    xcb_disconnect(conn);

	return 0;
}
