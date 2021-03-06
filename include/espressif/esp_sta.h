/*
 *  Copyright (C) 2013 -2014  Espressif System
 *
 */

#ifndef __ESP_STA_H__
#define __ESP_STA_H__

#include "queue.h"

struct station_config {
    uint8 ssid[32];
    uint8 password[64];
    uint8 bssid_set;
    uint8 bssid[6];
};

bool wifi_station_get_config(struct station_config *config);
bool wifi_station_set_config(struct station_config *config);

bool wifi_station_connect(void);
bool wifi_station_disconnect(void);

struct scan_config {
    uint8 *ssid;
    uint8 *bssid;
    uint8 channel;
    uint8 show_hidden;
};

struct bss_info {
    STAILQ_ENTRY(bss_info)     next;

    uint8 bssid[6];
    uint8 ssid[32];
    uint8 channel;
    sint8 rssi;
    uint8 authmode;
    uint8 is_hidden;
};

typedef void (* scan_done_cb_t)(void *arg, STATUS status);

bool wifi_station_scan(struct scan_config *config, scan_done_cb_t cb);

uint8 wifi_station_get_auto_connect(void);
bool wifi_station_set_auto_connect(uint8 set);

enum {
    STATION_IDLE = 0,
    STATION_CONNECTING,
    STATION_WRONG_PASSWORD,
    STATION_NO_AP_FOUND,
    STATION_CONNECT_FAIL,
    STATION_GOT_IP
};

uint8 wifi_station_get_connect_status(void);

#endif
