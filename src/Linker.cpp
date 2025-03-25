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
        config_file << CONTENT_CONFIG;
        config_file.close();
    }
}

bool Linker::isLoadedUserCode(){
    return FLAG_USER_CODE_PASSED;
}

void Linker::passUserCode(){
    if(!FLAG_USER_CODE_PASSED){
        FLAG_USER_CODE_PASSED = 1;
        
        system(cmdUserCodeToDll.c_str());
        HMODULE hLib = LoadLibrary(USER_DLL_NAME.c_str());
        
        system(("attrib +h " + USER_DLL_NAME).c_str());

        decoder = (Coder)GetProcAddress(hLib, "decoder");
        encoder = (Coder)GetProcAddress(hLib, "encoder");
    }
}

void Linker::passConfig(){
    if(!FLAG_CONFIG_PASSED){
        FLAG_CONFIG_PASSED = 1;



    }
}