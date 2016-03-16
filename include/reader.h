//
// Created by Nicole on 2/12/2016 AD.
//

#ifndef SW_PATTERN_CREADER_H
#define SW_PATTERN_CREADER_H

#include <stdint.h>
#include <stdlib.h>
#include <iconv.h>
#include <time.h>
#include <stdio.h>
#include <iosfwd>
#include <string>
‪#‎include‬ <chrono>

#define c_time int64_t
#define FILEID_SIZE (256)
#define MAX_SYLLABLE_TEXTSIZE (1023)

#define TIME_DETECT 0



typedef std::chrono::time_point<std::chrono::high_resolution_clock> hires_clock;
‪#‎define‬ NOW() std::chrono::high_resolution_clock::now()
#define DIFF(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start).count()
class Reader {
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
    } DATA_RECORD;

    typedef union _fileid_un{
        struct fileid_crack_at
        {
            uint16_t ui16MagicKey;
            uint16_t ui16Type;
            uint16_t ui16EntrySize;
            uint16_t _filler;
            uint32_t ui32NumEntry;
            time_t tTimeStamp;
        } crack;
        char szRaw[FILEID_SIZE];
    }FILEID;

    typedef struct syllable_data_record_at
    {
        uint32_t ui32SylID;
        uint16_t ui2Lang:2;
        uint16_t ui10Len:10;
        uint16_t ui1HasTailSpace:1;
        uint16_t ui1IsUnused:1;
        uint16_t ui1Numeric:1;
        uint16_t _filler:1;
        uint32_t ui32MapFilePos;
        time_t tTimeStamp;
        char szText[MAX_SYLLABLE_TEXTSIZE];
    }SYLLABLE_DATA_RECORD;

    typedef struct syllable_data_record_32
    {
        uint16_t ui16SylID;

        uint16_t ui2Lang:2;
        uint16_t ui10Len:10;
        uint16_t ui1HasTailSpace:1;
        uint16_t ui1IsUnused:1;
        uint16_t ui1Numeric:1;
        uint16_t _filler:1;
        uint32_t ui32MapFilePos;
        time_t tTimeStamp;
        char szText[MAX_SYLLABLE_TEXTSIZE];
    }SYLLABLE_DATA_RECORD_32;

    Reader(void);
    static void syllable_skip_to_data(FILE* fp);
    static bool is_64(std::string file_name);
    static int syllable_read_record(FILE *fp, DATA_RECORD *record, int timeSize);
};


#endif //SW_PATTERN_CREADER_H
