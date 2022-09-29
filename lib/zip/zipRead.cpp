#include "zipRead.hpp"
#include "zip.h"

#if _MSC_VER >= 1900

std::u32string to_utf32(std::string const & s)
{
    std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
    auto asInt = convert.from_bytes(s);
    return std::u32string(reinterpret_cast<char32_t const *>(asInt.data()), asInt.length());
}

#else

std::u32string to_utf32(std::string s){
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv{};
    return conv.from_bytes(s);
}

#endif

bool read(std::filesystem::path path, std::u32string& files){
    std::string strPath{path.string()};
    if (strPath.erase(0, strPath.size() - 8) == ".loc.zip"){
        int err = 0;
        zip *zipFile = zip_open(path.c_str(), 0, &err);

        zip_int64_t numberFile{zip_get_num_entries(zipFile, 0)};

        for (int i = 0; i < numberFile; ++i) {
            struct zip_stat st;
            zip_stat_init(&st);
            zip_stat_index(zipFile, i, 0, &st);
            std::string fileName{st.name};
            if (fileName.erase(0, fileName.size() - 4) == ".loc"){
                char * text = new char [st.size];

                zip_file_t* fileInZip = zip_fopen_index(zipFile, i, 0);
                zip_fread(fileInZip, text, st.size);
                zip_fclose(fileInZip);

                files += to_utf32(std::string{text}) + U'\n';
            }

        }

        return true;
    }
    return false;
}