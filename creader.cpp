#include "creader.h"

CReader::CReader(void) { }

void CReader::syllable_skip_to_data(FILE* fp){
    fseek(fp, 256, SEEK_SET);
}

int CReader::syllable_read_record(FILE* fp, iconv_t charset, DATA_RECORD* record, int timeSize){
    if(fread(&record->header, sizeof(record->header), 1, fp) != 1){
        return 0;
    }

    // detect
    if(timeSize == TIME_DETECT){
        fseek(fp, 8, SEEK_CUR);
        int success = 1;
        for(int i = 0; i < 4; i++){
            if(fgetc(fp) != 0){
                success = 0;
                fseek(fp, 4-i, SEEK_CUR);
                break;
            }
        }
        if(success == 1){
            timeSize = TIME_64;
        }else{
            timeSize = TIME_32;
        }
        fseek(fp, -8-4, SEEK_CUR);
    }

    record->timeSize = timeSize;

    if(timeSize == TIME_64){
        fread(&record->timestamp, sizeof(int64_t), 1, fp);
        fseek(fp, 4, SEEK_CUR);
    }else if(timeSize == TIME_32){
        int32_t timestamp;
        fread(&timestamp, sizeof(timestamp), 1, fp);
        record->timestamp = (int64_t) timestamp;
    }

    char buffer[1023];
    for(int i = 0; i < sizeof(buffer); i++){
        buffer[i] = fgetc(fp);

        if(buffer[i] == 0){
            break;
        }
    }
    size_t inLeft = 1023;
    size_t outLeft = 1023;
    char *input = &buffer[0];
    char *output = &record->szText[0];
    iconv(charset, &input, &inLeft, &output, &outLeft);
    record->szText[1023] = 0;

    return 1;
}
