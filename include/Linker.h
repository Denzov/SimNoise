#ifndef _LINKER_H_
#define _LINKER_H_

#include <windows.h>
#include <fstream>
#include <filesystem>
#include <string>

#include "Cmd.h"

typedef void (*Coder)(char* data, char* out, char length);

struct Settings{
    enum SIM_TYPE{
        bit_by_bit,
        byte_by_byte,
        loading
    } simulation_type;

    float error_change;

    uint16_t encoder_block_size;
    uint16_t decoder_block_size;
    
    CMD::LANGUAGE language;
};

class Linker{
private:       
    const std::string DIR_NAME = "UserCode/";
    const std::string USER_FILE_NAME = DIR_NAME + "UserCode.cpp";
    const std::string CONFIG_NAME = DIR_NAME + "CONFIG";

    const std::string USER_DLL_NAME = DIR_NAME + "UserCode.dll";

    const std::string CONTENT_USER_FILE = std::string(
        "extern \"C\" __declspec(dllexport)\n") + std::string(
        "void encoder(char* data, char* out, char length){\n") + std::string(
        "\t/*YOUR USER CODE*/\n}\n\n") + std::string(
        "extern \"C\" __declspec(dllexport)\n") + std::string(
        "void decoder(char* data, char* out, char length){\n\t/*YOUR USER CODE*/\n}\n");

    const std::string CONTENT_CONFIG = std::string(
        
    );
    std::string cmdUserCodeToDll = "g++ -shared -o " + USER_DLL_NAME + " " + USER_FILE_NAME;
        
    bool FLAG_USER_CODE_PASSED = 0;
    bool FLAG_CONFIG_PASSED = 0;

    Settings settings;

    Coder encoder;
    Coder decoder;
    
public:
    void loadStandartFiles();
    
    bool isLoadedUserCode();
    void passUserCode();

    void passConfig();
};

#endif // !_LINKER_H_