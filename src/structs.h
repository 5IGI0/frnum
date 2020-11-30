#ifndef __FRNUM_STRUCTS_H__
#define __FRNUM_STRUCTS_H__

#include <stdint.h>

typedef struct {
    uint32_t min;
    uint32_t max;
    char ownerID[5];
    unsigned char *areaName;
} phoneDBMajnum_t;

typedef struct {
    char ownerID[5];
    unsigned char *ownerName;
} phoneDBMajrio_t;

typedef struct {
    uint16_t majnumSize;
    phoneDBMajnum_t *majnumRecords;
    uint8_t majrioSize;
    phoneDBMajrio_t *majrioRecords;
} phoneDB_t;

typedef struct {
    uint32_t phone; // lookuped phone number
    char ownerID[5];  // owner ID, eg: FRTE
    unsigned char *ownerName; // owner name, eg: Orange
    unsigned char *area; // area, eg: "Nice"
} phoneLookup_t;

#endif