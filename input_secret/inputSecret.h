#pragma once
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>
#include <ranges>
#include <string_view>

namespace fs = std::filesystem;

size_t BYTE_OFFSET = 797184;

size_t utf8_unicode_count(std::u8string_view str) {
    return std::ranges::count_if(str, [](char8_t c) {
        return (c & 0xC0) != 0x80;  
    });
}

fs::path get_downloads_path() {
    PWSTR path = nullptr;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &path))) {
        std::wstring ws(path);
        CoTaskMemFree(path);
        return fs::path(std::string(ws.begin(), ws.end()));
    }
    return fs::path("");
}

fs::path copy_file_to_downloads(const fs::path& source_file){
    fs::path dest_folder = get_downloads_path();
    fs::path dest_file = dest_folder / source_file.filename();
    fs::copy(source_file, dest_file, fs::copy_options::overwrite_existing);
    return dest_file;
}

void embed_secret(const fs::path& filename, std::string new_text){
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);
    
    //if i change the displaySecret.exe then manually find the BYTE_OFFSET
    // const std::string target = "default text";
    // file.seekg(0, std::ios::end);
    // size_t file_size = file.tellg();
    // file.seekg(0);
    // std::vector<char> file_data(file_size);
    // file.read(file_data.data(), file_size);
    // auto it = std::search(file_data.begin(), file_data.end(), target.begin(), target.end());
    // if (it == file_data.end()) {
    //     throw std::runtime_error("corrupted original binary file. no target defualt text found");
    // }
    // size_t byte_offset = it - file_data.begin();
    // std::cout << "Target found at byte offset: " << byte_offset << std::endl;
    //BYTE_OFFSET = byte_offset

    file.seekp(BYTE_OFFSET);
    file.write(new_text.c_str(), new_text.size());
}


void self_sign_executable(fs::path& filepath){
    std::string exe_path = filepath.string();
    std::string cert_path = R"(.\..\KristoCert.pfx)";
    const std::string cert_password = "aaaa";  

    std::string command = 
        "signtool sign "
        "/f \"" + cert_path + "\" "      
        "/p " + cert_password + " "     
        "/fd SHA256 "                  
        "/tr http://timestamp.digicert.com " 
        "/td SHA256 "                  
        "\"" + exe_path + "\"";          
    
    int result = system(command.c_str());

    if (result != 0) {
        std::string err = std::string("Signing failed with error code: %d", result);
        throw std::runtime_error(err);
    }
}



