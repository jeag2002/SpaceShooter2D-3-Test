
#pragma once
#ifndef UTILSPROTOCOL_H_INCLUDED
#define UTILSPROTOCOL_H_INCLUDED

#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL_net.h>
#include <SDL.h>

#include "Constants.h"


namespace UtilsProtocol{

    //CALCULATE CRC16 CCITT
    //http://stackoverflow.com/questions/10564491/function-to-calculate-a-crc16-checksum
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

    //SEPARATE FRACC FROM ABSOLUTE VALUE
    inline int fractional_part_as_int(float number, int number_of_decimal_places) {
        double dummy;
        double frac = modf((double)number,&dummy);
        return round(frac*pow(10,number_of_decimal_places));
    };

    //PARSING REMOTE PACKET ADDRESS
    inline remoteHostData parseRemoteHostData(UDPpacket *packet){
        remoteHostData rHD;

        IPaddress ipAdd;
        memcpy(&ipAdd,&packet->address,sizeof(IPaddress));
        const char *host=SDLNet_ResolveIP(&ipAdd);
        Uint32 ipnum=SDL_SwapBE32(ipAdd.host);
        Uint16 port=SDL_SwapBE16(ipAdd.port);

        if (host){
            rHD.host = host;
        }else{
            char ip[100];
            for(int i=0; i<100; i++){ip[i]='\0';}
            sprintf(ip,"%d.%d.%d.%d",(ipnum>>24),((ipnum>>16)&0xff),((ipnum>>8)&0xff),(ipnum&0xff));
            rHD.host = (const char *)ip;
        }

        rHD.port = port;
        return rHD;
    };

    //GET COEF Lineal REGRESSION
    //http://www.oocities.org/david_swaim/cpp/linregc.htm
    inline coefLinRegresion getCoefLinRegrData(const double *x, const double *y, int sizeOfRegresion){
        coefLinRegresion cPRD;

        double sumX, sumY, sumXsquared, sumYsquared, sumXY = 0.0;

        for(int i=0; i<sizeOfRegresion; i++){
            sumX += x[i];
            sumY += y[i];
            sumXsquared += (x[i] * x[i]);
            sumYsquared += (y[i] * y[i]);
            sumXY += (x[i] * y[i]);
        }

        double b = 0.0;
        double a = 0.0;
        double coefD = 0.0;
        double coefC = 0.0;
        double stdError = 0.0;

        if (abs( double(sizeOfRegresion) * sumXsquared - sumX * sumX) > 0)
        {
            b = ( double(sizeOfRegresion) * sumXY - sumY * sumX) /
                ( double(sizeOfRegresion) * sumXsquared - sumX * sumX);
            a = (sumY - b * sumX) / double(sizeOfRegresion);

            double sx = b * ( sumXY - sumX * sumY / double(sizeOfRegresion));
            double sy2 = sumYsquared - sumY * sumY / double(sizeOfRegresion);
            double sy = sy2 - sx;

            coefD = sx / sy2;
            coefC = sqrt(coefD);
            stdError = sqrt(sy / double(sizeOfRegresion - 2));
        }
        else
        {
            a = b = coefD = coefC = stdError = 0.0;
        }


        cPRD.ACoef = a;
        cPRD.BCoef = b;
        cPRD.CoefD = coefD;
        cPRD.CoefC = coefC;
        cPRD.stdError = stdError;

        return cPRD;
    };

};

#endif // UTILSPROTOCOL_H_INCLUDED
