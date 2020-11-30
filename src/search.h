#ifndef __FRNUM_SEARCH_H__
#define __FRNUM_SEARCH_H__

#include "structs.h"

unsigned char *phone_getOwnerName(phoneDB_t *phoneDB, char *ownerID);
phoneLookup_t phone_lookup(phoneDB_t *phoneDB, uint32_t number);

#endif