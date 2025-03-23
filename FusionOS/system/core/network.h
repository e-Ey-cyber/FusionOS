#ifndef FUSION_NETWORK_H
#define FUSION_NETWORK_H

typedef struct {
    char* interface_name;
    char* ip_address;
    int (*connect)(void);
    int (*disconnect)(void);
} NetworkInterface;

int network_init(void);
int network_scan(void);
int network_connect(const char* ssid);

#endif
