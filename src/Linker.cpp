#include "../include/Linker.h"

void Linker::loadStandartFiles(){
    if(!std::filesystem::exists(DIR_NAME)){
        std::filesystem::create_directories(DIR_NAME);     
    }
    
    if(!std::filesystem::exists(USER_FILE_NAME)){
        std::ofstream user_file(USER_FILE_NAME);
        user_file << CONTENT_USER_FILE;
        user_file.close();
    }
    
    if(!std::filesystem::exists(CONFIG_NAME)){
        std::ofstream config_file(CONFIG_NAME);
        config_file.close();
    }
}

void Linker::loadUserCode(){
    if(!USER_CODE_LOADED){
        system(cmdUserCodeToDll.c_str());

        HMODULE hLib = LoadLibrary("UserCode/UserCode.dll");

        decoder = (Coder)GetProcAddress(hLib, "decoder");
        encoder = (Coder)GetProcAddress(hLib, "encoder");

        USER_CODE_LOADED = 1;
    }
}