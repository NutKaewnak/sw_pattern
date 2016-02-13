//
// Created by Nicole on 2/12/2016 AD.
//

#ifndef SW_PATTERN_CREADER_H
#define SW_PATTERN_CREADER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iconv.h>

#define c_time int64_t

#define TIME_DETECT 0
#define TIME_64 1
#define TIME_32 2

class CReader {
public:
    typedef struct DATA_RECORD{
        struct header{
            uint32_t id;
            // 00    000000,0000 0       0      0        0
            // lang  length     tailSpc unused numeric filler
            uint16_t lang:2;     // 2
            uint16_t length:10;  // 12
            uint16_t tailSpace:1; // 13*
            uint16_t isUnused:1;  // 14
            uint16_t numeric:1;   // 15
            uint16_t _filler:1;   // 16 -> 2 byte
            uint32_t mapFilePos;
        } header;
        int timeSize;
        c_time timestamp;
        char szText[1024];
    }DATA_RECORD;

    CReader(void);
    void syllable_skip_to_data(FILE* fp);
    int syllable_read_record(FILE* fp, iconv_t charset, DATA_RECORD* record, int timeSize);

};


#endif //SW_PATTERN_CREADER_H
