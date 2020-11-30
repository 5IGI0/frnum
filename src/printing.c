#include <stdio.h>
#include <stdint.h>

char *format_phone(uint32_t phone) {
    static char phoneStr[21] = "";

    if (phone >= 100000000 && phone <= 999999999) {
        sprintf(phoneStr,"0%u.%02u.%02u.%02u.%02u", 
            phone / 100000000,
            (phone / 1000000) % 100,
            (phone / 10000) % 100,
            (phone / 100) % 100,
            phone % 100
        );
    } else if(phone >= 100000 && phone <= 999999) {
        sprintf(phoneStr,"%03u %03u",
            (phone / 1000) % 1000,
            phone % 1000
        );
    } else if(phone >= 1000 && phone <= 9999) {
        sprintf(phoneStr,"%02u %02u",
            (phone / 100) % 100,
            phone % 100
        );
    } else {
        sprintf(phoneStr, "%u", phone);
    }
    
    
    return phoneStr;
}