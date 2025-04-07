#include "../include/Linker.h"

void Linker::config_to_undef(){
    _config.samples_size = 0;
    _config.simulation_type = Config::SIM_TYPE::UNDEF;
    _config.error_change = -1;
    _config.encoder_bit_block_size = 0;
    _config.decoder_bit_block_size = 0;
}

void Linker::update_config_file(){
    std::ofstream config_file(CONFIG_NAME);

    std::string content_config = "";
    content_config += std::string(TEXT_CONFIG_SAMPLES_SIZE) + std::to_string(_config.samples_size) + "\n";
    content_config += std::string(TEXT_CONFIG_SIMULATION_TYPE) + std::to_string(_config.simulation_type) + "\n";
    content_config += std::string(TEXT_CONFIG_ERROR_CHANGE) + std::to_string(_config.error_change) + "\n";
    content_config += std::string(TEXT_CONFIG_ENCODER_BLOCK_SIZE) + std::to_string(_config.encoder_bit_block_size) + "\n";
    content_config += std::string(TEXT_CONFIG_DECODER_BLOCK_SIZE) + std::to_string(_config.decoder_bit_block_size) + "\n";

    config_file << content_config;
}

Coder Linker::getDecoder(){
    return _decoder;
}

Coder Linker::getEncoder(){
    return _encoder;
}

Config* Linker::getConfig(){
    return &_config;
}

void Linker::setSamplesSize(uint64_t value){
    _config.samples_size = value;

    update_config_file();
}

void Linker::setSimulationType(uint8_t value){
    _config.simulation_type = static_cast<Config::SIM_TYPE>(value);

    update_config_file();
}

void Linker::setErrorChange(float value){
    _config.error_change = value;

    update_config_file();
}

void Linker::setEncoderBlockSize(uint64_t value){
    _config.encoder_bit_block_size = value;

    update_config_file();
}

void Linker::setDecoderBlockSize(uint64_t value){
    _config.decoder_bit_block_size = value;

    update_config_file();
}

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

void Linker::passUserFuncs(){
    if(FLAG_USER_CODE_PASSED){
        FreeLibrary(UserDll);
    }
    
    system(CMD_USER_CODE_TO_DLL.c_str());
    UserDll = LoadLibrary(USER_DLL_NAME.c_str());
    
    SetFileAttributes(USER_DLL_NAME.c_str(), FILE_ATTRIBUTE_HIDDEN);
    
    _decoder = (Coder)GetProcAddress(UserDll, "decoder");
    _encoder = (Coder)GetProcAddress(UserDll, "encoder");
    
    FLAG_USER_CODE_PASSED = 1;
}

void Linker::passConfig(){
    if(std::filesystem::exists(CONFIG_NAME)){
        std::ifstream config_file(CONFIG_NAME);
        std::string line;

        config_to_undef();
        
        while(std::getline(config_file, line)){
            if(line.find(TEXT_CONFIG_SAMPLES_SIZE) == 0){
                try{
                    auto cur_value = static_cast<uint64_t>(std::stoull(line.substr(strlen(TEXT_CONFIG_SAMPLES_SIZE))));

                    _config.samples_size = cur_value;
                    FLAG_ERROR_INVALID_SAMPLES_SIZE = 0;
                }
                catch(...){
                    FLAG_ERROR_INVALID_SAMPLES_SIZE = 1;
                }
            }
            else if(line.find(TEXT_CONFIG_SIMULATION_TYPE) == 0){
                try{
                    auto cur_value = static_cast<Config::SIM_TYPE>(std::stoi(line.substr(strlen(TEXT_CONFIG_SIMULATION_TYPE))));

                    _config.simulation_type = static_cast<Config::SIM_TYPE>(cur_value);
                    FLAG_ERROR_INVALID_SIMULATION_TYPE = 0;
                }
                catch(...){
                    FLAG_ERROR_INVALID_SIMULATION_TYPE = 1;
                }
            }
            else if(line.find(TEXT_CONFIG_ERROR_CHANGE) == 0){
                try{
                    auto error_change_value = static_cast<float>(std::stof(line.substr(strlen(TEXT_CONFIG_ERROR_CHANGE))));

                    _config.error_change = error_change_value;
                    FLAG_ERROR_INVALID_ERROR_CHANGE = 0;
                }
                catch(...){
                    FLAG_ERROR_INVALID_ERROR_CHANGE = 1;
                }
                
            }
            else if(line.find(TEXT_CONFIG_ENCODER_BLOCK_SIZE) == 0){
                try{
                    auto cur_value = static_cast<uint64_t>(std::stoull(line.substr(strlen(TEXT_CONFIG_ENCODER_BLOCK_SIZE))));

                        _config.encoder_bit_block_size = cur_value;
                        FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 0;
                }
                catch(...){
                    FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 1;
                }
                
            }
            else if(line.find(TEXT_CONFIG_DECODER_BLOCK_SIZE) == 0){
                try{
                    auto cur_value = static_cast<uint64_t>(std::stoull(line.substr(strlen(TEXT_CONFIG_DECODER_BLOCK_SIZE))));

                    _config.decoder_bit_block_size = cur_value;
                    FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 0;
                }
                catch(...){
                    FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 1;
                }
            }
        }    
    }
}

bool Linker::isValidSamplesSize(){
    return !FLAG_ERROR_INVALID_SAMPLES_SIZE && (_config.samples_size >= SAMPLES_SIZE_MIN_VALUE);
}
bool Linker::isValidSimulationType(){
    return !FLAG_ERROR_INVALID_SIMULATION_TYPE && (_config.simulation_type != Config::SIM_TYPE::UNDEF) 
    && (_config.simulation_type >= SIM_TYPE_MIN_VALUE) && _config.simulation_type <= SIM_TYPE_MAX_VALUE;
}
bool Linker::isValidErrorChange(){
    return !FLAG_ERROR_INVALID_ERROR_CHANGE && (_config.error_change >= ERROR_CHANGE_MIN_VALUE) && (_config.error_change <= ERROR_CHANGE_MAX_VALUE);
}
bool Linker::isValidEncoderBlockSize(){
    return !FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE && (_config.encoder_bit_block_size >= ENCODER_BLOCK_SIZE_MIN_VALUE);
}
bool Linker::isValidDecoderBlockSize(){
    return !FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE && (_config.decoder_bit_block_size >= DECODER_BLOCK_SIZE_MIN_VALUE);
}
