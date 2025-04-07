#ifndef _LINKER_H_
#define _LINKER_H_

#include <windows.h>
#include <fstream>
#include <filesystem>
#include <string>

#include "Cmd.h"
#include "SimParams.h"

constexpr const char* TEXT_CONFIG_SAMPLES_SIZE = "SAMPLES_SIZE=";
constexpr const char* TEXT_CONFIG_SIMULATION_TYPE = "SIM_TYPE=";
constexpr const char* TEXT_CONFIG_ERROR_CHANGE = "ERROR_CHANGE=";
constexpr const char* TEXT_CONFIG_ENCODER_BLOCK_SIZE = "ENCODER_BIT_BLOCK_SIZE=";
constexpr const char* TEXT_CONFIG_DECODER_BLOCK_SIZE = "DECODER_BIT_BLOCK_SIZE=";

class Linker{
private:       
    const std::string DIR_NAME = "UserCode\\";  
    const std::string USER_FILE_NAME = DIR_NAME + "UserCode.cpp";
    const std::string CONFIG_NAME = DIR_NAME + "CONFIG";

    const std::string USER_DLL_NAME = DIR_NAME + "UserCode.dll";

    
    
    const std::string CONTENT_USER_FILE = std::string(
        "typedef unsigned char uint8_t;\n") + std::string(
        "typedef long long int64_t;\n\n") + std::string(
        "extern \"C\" __declspec(dllexport)\n") + std::string(
        "void encoder(uint8_t* data, uint8_t* out, int64_t data_length){\n") + std::string(
        "\t/*YOUR USER CODE*/\n}\n\n") + std::string(
        "extern \"C\" __declspec(dllexport)\n") + std::string(
        "void decoder(uint8_t* data, uint8_t* out, int64_t data_length){\n\t/*YOUR USER CODE*/\n}\n");

    const std::string CONTENT_CONFIG = std::string(
        TEXT_CONFIG_SAMPLES_SIZE) + "1\n" + std::string(
        TEXT_CONFIG_SIMULATION_TYPE) + "0\n" + std::string(
        TEXT_CONFIG_ERROR_CHANGE) + "0.0\n" + std::string(
        TEXT_CONFIG_ENCODER_BLOCK_SIZE) + "1\n" + std::string(
        TEXT_CONFIG_DECODER_BLOCK_SIZE) + "1\n";

    const std::string CMD_USER_CODE_TO_DLL = "g++ -shared -o " + USER_DLL_NAME + " " + USER_FILE_NAME;
        
    HMODULE UserDll;

    bool FLAG_USER_CODE_PASSED = 0;
    bool FLAG_ERROR_INVALID_SAMPLES_SIZE = 0;
    bool FLAG_ERROR_INVALID_SIMULATION_TYPE = 0;
    bool FLAG_ERROR_INVALID_ERROR_CHANGE = 0;
    bool FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 0;
    bool FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 0;

    Coder _decoder;
    Coder _encoder;

    Config _config;

    void config_to_undef();
    void update_config_file();
public:
    Coder getDecoder();
    Coder getEncoder();
    Config* getConfig();

    void setSamplesSize(uint64_t value);
    void setSimulationType(uint8_t value);
    void setErrorChange(float value);
    void setEncoderBlockSize(uint64_t value);
    void setDecoderBlockSize(uint64_t value);

    void loadStandartFiles();
    bool isLoadedUserCode();
    
    void passUserFuncs();
    void passConfig();

    bool isValidSamplesSize();
    bool isValidSimulationType();
    bool isValidErrorChange();
    bool isValidEncoderBlockSize();
    bool isValidDecoderBlockSize();    
};

#endif // !_LINKER_H_