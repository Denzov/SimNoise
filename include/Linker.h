#ifndef _LINKER_H_
#define _LINKER_H_

#include <windows.h>
#include <fstream>
#include <filesystem>
#include <string>

#include "Cmd.h"

typedef void (*Coder)(char* data, char* out, char length);

struct Config{
    uint64_t samples_size;

    enum SIM_TYPE : uint8_t{
        bit_by_bit = 0,
        byte_by_byte,
        loading,
        
        SIM_TYPE_SIZE, 
        
        UNDEF 
    } simulation_type;

    float error_change;

    uint64_t encoder_block_size;
    uint64_t decoder_block_size;   
};

constexpr const char* CONFIG_SAMPLES_SIZE = ".SAMPLES_SIZE=";
constexpr const char* CONFIG_SIMULATION_TYPE = ".SIM_TYPE=";
constexpr const char* CONFIG_ERROR_CHANGE = ".ERROR_CHANGE=";
constexpr const char* CONFIG_ENCODER_BLOCK_SIZE = ".ENCODER_BLOCK_SIZE=";
constexpr const char* CONFIG_DECODER_BLOCK_SIZE = ".DECODER_BLOCK_SIZE=";

class Linker{
private:       
    const std::string DIR_NAME = "UserCode\\";
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
        CONFIG_SAMPLES_SIZE) + "1\n" + std::string(
        CONFIG_SIMULATION_TYPE) + "0\n" + std::string(
        CONFIG_ERROR_CHANGE) + "0.0\n" + std::string(
        CONFIG_ENCODER_BLOCK_SIZE) + "0\n" + std::string(
        CONFIG_DECODER_BLOCK_SIZE) + "0\n";

    std::string cmdUserCodeToDll = "g++ -shared -o " + USER_DLL_NAME + " " + USER_FILE_NAME;
        
    bool FLAG_USER_CODE_PASSED = 0;
    bool FLAG_CONFIG_PASSED = 0;

    bool FLAG_ERROR_INVALID_SAMPLES_SIZE = 0;
    bool FLAG_ERROR_INVALID_SIMULATION_TYPE = 0;
    bool FLAG_ERROR_INVALID_ERROR_CHANGE = 0;
    bool FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 0;
    bool FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 0;

    Coder encoder;
    Coder decoder;
    
    Config config;

    bool is_invalid_config_value(int64_t val);
    bool is_invalid_error_change_value(float val);

    void config_to_undef();
public:
    Config& getConfig();

    void loadStandartFiles();
    
    bool isLoadedUserCode();
    void passUserCode();
    
    void passConfig();
    
    bool isPassedConfig();
    bool isValidSamplesSize();
    bool isValidSimulationType();
    bool isValidErrorChange();
    bool isValidEncoderBlockSize();
    bool isValidDecoderBlockSize();

};

#endif // !_LINKER_H_