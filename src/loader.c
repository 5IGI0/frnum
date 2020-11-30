#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "structs.h"
#include "loader.h"

phoneDB_t *phone_load(FILE *file) {
    size_t i = 0; // iterator
    phoneDB_t *phoneDB = calloc(1, sizeof(phoneDB_t));

    if (phoneDB == NULL)
        return NULL;

    if (fread(&phoneDB->majnumSize, 1, 2, file) != 2) {
        phone_freeDB(phoneDB);
        return NULL;
    }

    phoneDB->majnumSize = ntohs(phoneDB->majnumSize);
    phoneDB->majnumRecords = calloc(phoneDB->majnumSize, sizeof(phoneDBMajnum_t));

    if (phoneDB->majnumRecords == NULL) {
        phone_freeDB(phoneDB);
        return NULL;
    }

    for (i = 0; i < phoneDB->majnumSize; i++) {

        uint32_t tmp = 0;
        uint8_t tmptmp = 0;

        if(fread(&tmp, 1, 4, file) != 4) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        phoneDB->majnumRecords[i].min = ntohl(tmp);

        if(fread(&tmp, 1, 4, file) != 4) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        phoneDB->majnumRecords[i].max = ntohl(tmp);

        if(fread(phoneDB->majnumRecords[i].ownerID, 1, 4, file) != 4) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        if (phoneDB->majnumRecords[i].max < phoneDB->majnumRecords[i].min) {
            phone_freeDB(phoneDB);
            return NULL;
        }
        

        if(fread(&tmptmp, 1, 1, file) != 1) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        phoneDB->majnumRecords[i].areaName = calloc(tmptmp+1, 1);

        if (phoneDB->majnumRecords[i].areaName == NULL) {
            phone_freeDB(phoneDB);
            return NULL;
        }
        
        if(fread(phoneDB->majnumRecords[i].areaName, tmptmp, 1, file) != 1) {
            phone_freeDB(phoneDB);
            return NULL;
        }
    }

    if(fread(&phoneDB->majrioSize, 1, 1, file) != 1) {
        phone_freeDB(phoneDB);
        return NULL;
    }

    phoneDB->majrioRecords = calloc(phoneDB->majrioSize, sizeof(phoneDBMajrio_t));

    if(phoneDB->majrioRecords == NULL) {
        phone_freeDB(phoneDB);
        return NULL;
    }

    for(i = 0; i < phoneDB->majrioSize; i++) {
        uint8_t tmp = 0;
        if(fread(phoneDB->majrioRecords[i].ownerID, 1, 4, file) != 4) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        if(fread(&tmp, 1, 1, file) != 1) {
            phone_freeDB(phoneDB);
            return NULL;
        }
        
        phoneDB->majrioRecords[i].ownerName = calloc(tmp+1, 1);

        if (phoneDB->majrioRecords[i].ownerName == NULL) {
            phone_freeDB(phoneDB);
            return NULL;
        }

        if(fread(phoneDB->majrioRecords[i].ownerName, 1, tmp, file) != tmp) {
            phone_freeDB(phoneDB);
            return NULL;
        }
    }    

    return phoneDB;
}

void phone_freeDB(phoneDB_t *db) {
    size_t i = 0; // iterator

    if (db->majnumRecords != NULL) {
        for (i = 0; i < db->majnumSize; i++)
            free(db->majnumRecords[i].areaName);
        free(db->majnumRecords);
    }
    
    if (db->majrioRecords != NULL) {
        for (i = 0; i < db->majrioSize; i++)
            free(db->majrioRecords[i].ownerName);

        free(db->majrioRecords);
    }
    free(db);
}