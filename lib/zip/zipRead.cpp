#include "zipRead.hpp"
#include "zip.h"
#include <option_result/option_result.hpp>

orl::Option<std::string> read(std::filesystem::path path){
    std::string strPath{path.string()};
    if (strPath.erase(0, strPath.size() - 8) == ".loc.zip"){
		std::string result;
        int err = 0;
        zip *zipFile = zip_open(path.c_str(), 0, &err);

        zip_int64_t numberFile{zip_get_num_entries(zipFile, 0)};

        for (int i = 0; i < numberFile; ++i) {
            struct zip_stat st;
            zip_stat_init(&st);
            zip_stat_index(zipFile, i, 0, &st);
            std::string fileName{st.name};
            if (fileName.erase(0, fileName.size() - 4) == ".loc"){
                char * text = new char [st.size - 1];
				
                zip_file_t* fileInZip = zip_fopen_index(zipFile, i, 0);
                zip_fread(fileInZip, text, st.size - 1);
                zip_fclose(fileInZip);
				
                result += std::string{text} + '\n';
            }

        }

        return result;
    }
    return {};
}