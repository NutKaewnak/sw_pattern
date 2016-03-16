#include "include/reader.h"

Reader::Reader(void) { }

void Reader::syllable_skip_to_data(FILE* fp){
    fseek(fp, 256, SEEK_SET);
}

bool Reader::is_64(std::string file_name) {
    FILE* fp = fopen(file_name.c_str(), "rb");
    Reader::syllable_skip_to_data(fp);
    Reader::DATA_RECORD* record = (Reader::DATA_RECORD*) malloc(sizeof(Reader::DATA_RECORD));
    int timeSize = TIME_DETECT;
    int out = Reader::syllable_read_record(fp, record, timeSize);
    return out == 1;
}

int Reader::syllable_read_record(FILE *fp, Reader::DATA_RECORD *record, int timeSize) {
    if (fread(&record->header, sizeof(record->header), 1, fp) != 1) {
        return 0;
    }
    // detect
    if (timeSize == TIME_DETECT) {
        fseek(fp, 8, SEEK_CUR);
        int success = 1;
        for (int i = 0; i < 4; i++) {
            if (fgetc(fp) != 0) {
                success = 0;
                fseek(fp, 4 - i, SEEK_CUR);
                break;
            }
        }
        return success;
    }
    return 1;
}
