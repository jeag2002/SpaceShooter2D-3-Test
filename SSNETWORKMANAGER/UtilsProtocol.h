
#pragma once
#ifndef UTILSPROTOCOL_H_INCLUDED
#define UTILSPROTOCOL_H_INCLUDED

#include <cmath>
#include <stdint.h>
/*
Calculate crc16 CCITT.
http://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum
*/

namespace UtilsProtocol{

    inline uint16_t calculateCRC16_CCITT(const unsigned char *data_p, unsigned int length){
        //uint16_t crc = 0;

        unsigned char x;
        uint16_t crc = 0xFFFF;

        while (length--){
            x = crc >> 8 ^ *data_p++;
            x ^= x>>4;
            crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x <<5)) ^ ((uint16_t)x);
        }

        return crc;
    };

    inline int fractional_part_as_int(float number, int number_of_decimal_places) {
        double dummy;
        double frac = modf((double)number,&dummy);
        return round(frac*pow(10,number_of_decimal_places));
    }


};


#endif // UTILSPROTOCOL_H_INCLUDED
