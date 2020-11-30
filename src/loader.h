#ifndef __FRNUM_LOADER_H__
#define __FRNUM_LOADER_H__

#include <stdio.h>
#include "structs.h"

phoneDB_t *phone_load(FILE *file);
void phone_freeDB(phoneDB_t *db);

#endif