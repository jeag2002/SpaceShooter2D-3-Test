#ifndef COMPRESSPACKET_H_INCLUDED
#define COMPRESSPACKET_H_INCLUDED

extern "C"
{
#include "lzo/minilzo.h"
}

#include "LogEngine.h"

#define SIZE_IN 512
#define SIZE_OUT 128

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]


class CompressPacket{

public:

    CompressPacket(LogEngine *_logger){
        logger = _logger;
        clearInputBuffer();
        clearOutputBuffer();
    }

    bool Init(){
        bool res = false;
        if (lzo_init() != LZO_E_OK){
            logger->warn("[CompressPacket::Init] Cannot initialize compression process");
        }else{
            logger->info("[CompressPacket::Init] LZO CONF SUCCESSFUL version [%s], version_date [%s]", lzo_version_string(), lzo_version_date());
            res = true;
        }
        return res;
    }

    unsigned char *CompressionData( char *inputData, int sizeData){
        lzo_uint in_len;
        lzo_uint out_len;
        in_len = sizeData;

        clearInputBuffer();
        clearOutputBuffer();

        lzo_memcpy(in, (unsigned char *)inputData, sizeData);

        int r = lzo1x_1_compress(in,in_len,out,&out_len,wrkmem);

        if (r == LZO_E_OK){
            if (in_len >= out_len){
                logger->debug("[CompressPacket::Compress] INPUT DATA SIZE [%d], OUTPUT DATA SIZE [%d]",in_len,out_len);
            }else{
                logger->warn("[CompressPacket::Compress] CANNOT COMPRESS INPUT DATA SIZE [%d], OUTPUT DATA SIZE [%d]",in_len,out_len);
                clearOutputBuffer();
            }
        }else{
            logger->error("[CompressPacket::Compress] ERROR COMPRESSING DATA");
            clearOutputBuffer();
        }

        return (unsigned char *)out;
    }



     unsigned char *UnCompressionData( char *inputData, int sizeData){

        lzo_uint in_len;
        lzo_uint out_len;
        in_len = sizeData;

        clearInputBuffer();
        clearOutputBuffer();

        lzo_memcpy(in, (unsigned char *)inputData, sizeData);

        int r = lzo1x_decompress(in,in_len,out,&out_len,NULL);

        if (r == LZO_E_OK){
            if (in_len <= out_len){
                logger->debug("[CompressPacket::Compress] INPUT DATA SIZE [%d], OUTPUT DATA SIZE [%d]",in_len,out_len);
            }else{
                logger->warn("[CompressPacket::Compress] CANNOT COMPRESS INPUT DATA SIZE [%d], OUTPUT DATA SIZE [%d]",in_len,out_len);
                clearOutputBuffer();
            }
        }else{
            logger->error("[CompressPacket::Compress] ERROR COMPRESSING DATA");
            clearOutputBuffer();
        }

        return (unsigned char *)out;
    }







    void clearInputBuffer(){
        for(int i=0; i<SIZE_IN; i++){in[i]='\0';}
    }

    void clearOutputBuffer(){
        for(int i=0; i<SIZE_OUT; i++){out[i]='\0';}
    }


    ~CompressPacket(){
    }

private:

unsigned char __LZO_MMODEL in  [ SIZE_IN ];
unsigned char __LZO_MMODEL out [ SIZE_OUT ];
HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);


LogEngine *logger;

};

#endif // COMPRESSPACKET_H_INCLUDED
