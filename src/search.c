#include <stdlib.h>
#include <string.h>

#include "structs.h"

unsigned char *phone_getOwnerName(phoneDB_t *phoneDB, char *ownerID) {
    size_t i = 0;

    for (i = 0; i < phoneDB->majrioSize; i++) {
        if (strcmp(phoneDB->majrioRecords[i].ownerID, ownerID) == 0)
            return phoneDB->majrioRecords[i].ownerName;
    }

    return (unsigned char *)"unknown";
}

phoneLookup_t phone_lookup(phoneDB_t *phoneDB, uint32_t number) {
    size_t i = 0; // iterator
    phoneLookup_t lookup = {0};
    lookup.phone = number;

    for (i = 0; i < phoneDB->majnumSize; i++) {
        if (phoneDB->majnumRecords[i].min <= lookup.phone && lookup.phone <= phoneDB->majnumRecords[i].max) {
            memcpy(lookup.ownerID, phoneDB->majnumRecords[i].ownerID, 4);
            lookup.area = phoneDB->majnumRecords[i].areaName;
            lookup.ownerName = phone_getOwnerName(phoneDB, lookup.ownerID);
            break;
        }
    }

    return lookup;
}