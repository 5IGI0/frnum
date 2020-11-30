#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>

#include "frnum.h"

#define FWRITE_HCSTR(data, file) fwrite(data, 1, sizeof(data)-1, file);

int main(int argc, char const *argv[]) {
    phoneLookup_t lookup = {0};
    phoneDB_t *phoneDB = NULL;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <phone number>\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        if(sscanf(argv[1], "%u", &lookup.phone) != 1) {
            fprintf(stderr, "usage: %s <phone number>\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    FILE *file = fopen(getenv("NUMLOOKUP_DB_PATH") ? getenv("NUMLOOKUP_DB_PATH") : "./frnum.db", "rb");
    if (file == NULL) {
        perror(getenv("NUMLOOKUP_DB_PATH") ? getenv("NUMLOOKUP_DB_PATH") : "./frnum.db");
        return EXIT_FAILURE;
    }
    
    if((phoneDB = phone_load(file)) == NULL) {
        FWRITE_HCSTR("cannot load the database", stderr);
        if (errno != 0)
            perror("");
        FWRITE_HCSTR("\n", stderr);
        fclose(file);
        return EXIT_FAILURE;
    }

    lookup = phone_lookup(phoneDB, lookup.phone);

    if (lookup.ownerID[0] == 0) {
        puts("not found!");
    } else {
        printf(
            "number: %s\n"
            "owner : %s (%s)\n"
            "area  : %s\n",
            format_phone(lookup.phone),
            lookup.ownerID, lookup.ownerName,
            lookup.area
        );
    }
    
    phone_freeDB(phoneDB);
    fclose(file);

    return EXIT_SUCCESS;
}
