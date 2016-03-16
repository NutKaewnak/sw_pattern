#include <iostream>
#include <fstream>
#include "include/reader.h"

using namespace std;

int main(int argc, char *argv[]){
    std::string file_directory = "/Users/Nicole/ClionProjects/sw_pattern/SyllableDB-V1.dat";

    bool is_64;
    is_64 = Reader::is_64(file_directory);
    ifstream fp(file_directory, ios::binary);
    Reader::FILEID id;
    // read header
    fp.read((char*) &id, sizeof(id));

    while(true){
        if (is_64) {
            Reader::SYLLABLE_DATA_RECORD record;
            // read record header
            fp.read((char*) &record, sizeof(record) - MAX_SYLLABLE_TEXTSIZE - 1);
            if(!fp){
                break;
            }

            // read record text
            fp.getline((char*) &record.szText, MAX_SYLLABLE_TEXTSIZE, 0);
            cout << record.ui32SylID << " " << record.szText << endl;
        }
        else{
            Reader::SYLLABLE_DATA_RECORD_32 record;
            // read record header
            fp.read((char*) &record, sizeof(record) - MAX_SYLLABLE_TEXTSIZE - 1);
            if(!fp){
                break;
            }

            // read record text
            fp.getline((char*) &record.szText, MAX_SYLLABLE_TEXTSIZE, 0);
            cout << record.ui16SylID << " " << record.szText << endl;
        }
    }

    return 0;

}