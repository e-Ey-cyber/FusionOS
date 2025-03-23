#include "network.h"
#include <stdio.h>
#include <stdlib.h>

static NetworkInterface* current_interface = NULL;

int network_init(void) {
    printf("Initializing network subsystem...\n");
    return 0;
}

int network_scan(void) {
    printf("Scanning for available networks...\n");
    return 0;
}

int network_connect(const char* ssid) {
    if (!ssid) return -1;
    printf("Connecting to network: %s\n", ssid);
    if (current_interface && current_interface->connect) {
        return current_interface->connect();
    }
    return 0;
}
