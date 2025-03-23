#ifndef FUSION_SECURITY_H
#define FUSION_SECURITY_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    SECURITY_LEVEL_LOW = 0,
    SECURITY_LEVEL_MEDIUM = 1,
    SECURITY_LEVEL_HIGH = 2,
    SECURITY_LEVEL_MAXIMUM = 3
} SecurityLevel;

typedef struct {
    char* module_name;
    SecurityLevel security_level;
    int (*init)(void);
    int (*scan)(void);
    int (*encrypt)(void* data, size_t size);
    int (*decrypt)(void* data, size_t size);
    int (*prevent_root_access)(void);
    int (*secure_boot_verify)(void);
    int (*anti_tampering_check)(void);
} SecurityModule;

void security_init_all(void);
int security_add_module(SecurityModule* module);
int security_scan_system(void);

// New security functions
int security_enable_secure_boot(void);
int security_enable_anti_tampering(void);
int security_enable_data_encryption(void);
int security_lock_bootloader(void);
int security_enable_app_signing(void);
void security_set_system_level(SecurityLevel level);

// Security events
typedef enum {
    SEC_EVENT_NORMAL = 0,
    SEC_EVENT_WARNING = 1,
    SEC_EVENT_CRITICAL = 2
} SecurityEventType;

// Add new functions
void security_register_event_handler(void (*handler)(SecurityEventType, const char*));
void security_scan_background(void);
void security_lock_device(void);
void security_emergency_wipe(void);

#endif
