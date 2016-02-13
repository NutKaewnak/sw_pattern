#include <iostream>
#include "creader.h"

using namespace std;

int main(int argc, char *argv[]){
    CReader cReader = CReader::CReader();
//    if(argc < 2){
//        printf("usage: %s filename.dat\n", argv[0]);
//        return 0;
//    }
    FILE* fp = fopen("~/ClionProject/sw_pattern/SyllableDB-V1.dat", "rb");
    cReader.syllable_skip_to_data(fp);

    CReader::DATA_RECORD* record = (CReader::DATA_RECORD*) malloc(sizeof(CReader::DATA_RECORD));
    iconv_t charset = iconv_open("UTF8", "CP874");
    int lastId = 0;
    int timeSize = TIME_DETECT;
    while(!feof(fp)){
        if(cReader.syllable_read_record(fp, charset, record, timeSize) != 1){
            break;
        }

        if(record->header.id != lastId + 1){
            printf("E: Record not continuous. Expecting ID %d, found %d\n", lastId+1, record->header.id);
            return 1;
        }

        lastId = record->header.id;
        timeSize = record->timeSize;

        printf(
                "record %d lang %d length %d tailSpace %d unused %d numeric %d mapfilepos %d timestamp %lld\n",
                record->header.id, record->header.lang, record->header.length, record->header.tailSpace,
                record->header.isUnused, record->header.numeric, record->header.mapFilePos,
                record->timestamp
        );
        printf("%s\n=========\n", record->szText);
    }

    return 0;
}