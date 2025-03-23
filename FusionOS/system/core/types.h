#ifndef FUSION_TYPES_H
#define FUSION_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// System status
typedef struct {
    int battery_level;
    int network_signal;
    char* current_network;
    int security_level;
    bool is_secure_boot;
    bool is_debugging;
} SystemStatus;

#endif // FUSION_TYPES_H
