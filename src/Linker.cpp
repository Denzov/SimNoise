#include "../include/Linker.h"

bool Linker::is_invalid_config_value(int64_t val){
    return val < 0;
}

Config& Linker::getConfig(){
    return config;
}

void Linker::config_to_undef(){
    config.samples_size = 0;
    config.simulation_type = Config::SIM_TYPE::UNDEF;
    config.error_change = 0;
    config.encoder_block_size = 0;
    config.decoder_block_size = 0;
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
    if(std::filesystem::exists(CONFIG_NAME)){
        FLAG_CONFIG_PASSED = 1;        

        std::ifstream config_file(CONFIG_NAME);
        std::string line;

        config_to_undef();
        
        try
        {
            int64_t cur_value = 0;
            while(std::getline(config_file, line)){
                if(line.find(CONFIG_SAMPLES_SIZE) == 0){
                    cur_value = static_cast<int64_t>(std::stoi(line.substr(strlen(CONFIG_SAMPLES_SIZE))));

                    if(is_invalid_config_value(cur_value)){
                        FLAG_ERROR_INVALID_SAMPLES_SIZE = 1;
                    }
                    else{
                        FLAG_ERROR_INVALID_SAMPLES_SIZE = 0;
                        config.samples_size = cur_value;
                    }
                }
                else if(line.find(CONFIG_SIMULATION_TYPE) == 0){
                    cur_value = static_cast<Config::SIM_TYPE>(std::stoi(line.substr(strlen(CONFIG_SIMULATION_TYPE))));

                    if(cur_value < 0 || cur_value > Config::SIM_TYPE::SIM_TYPE_SIZE){
                        FLAG_ERROR_INVALID_SIMULATION_TYPE = 1;
                    }
                    else{
                        FLAG_ERROR_INVALID_SIMULATION_TYPE = 0;
                        config.simulation_type = static_cast<Config::SIM_TYPE>(cur_value);
                    }
                }
                else if(line.find(CONFIG_ERROR_CHANGE) == 0){
                    float error_change_value = static_cast<float>(std::stof(line.substr(strlen(CONFIG_ERROR_CHANGE))));

                    if(error_change_value < 0 || error_change_value > 1){
                        FLAG_ERROR_INVALID_ERROR_CHANGE = 1;
                    }
                    else{
                        FLAG_ERROR_INVALID_ERROR_CHANGE = 0;
                        config.error_change = error_change_value;
                    }
                }
                else if(line.find(CONFIG_ENCODER_BLOCK_SIZE) == 0){
                    cur_value = static_cast<int64_t>(std::stoi(line.substr(strlen(CONFIG_ENCODER_BLOCK_SIZE))));

                    if(is_invalid_config_value(cur_value)){
                        FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 1;
                    }
                    else{
                        FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE = 0;
                        config.encoder_block_size = cur_value;
                    }
                }
                else if(line.find(CONFIG_DECODER_BLOCK_SIZE) == 0){
                    cur_value = static_cast<int64_t>(std::stoi(line.substr(strlen(CONFIG_DECODER_BLOCK_SIZE))));

                    if(is_invalid_config_value(cur_value)){
                        FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 1;
                    }
                    else{
                        FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE = 0;
                        config.decoder_block_size = cur_value;
                    }
                }
            }    
        }
        catch(...)
        {
            FLAG_CONFIG_PASSED = 0;
        }
    }
}

bool Linker::isPassedConfig(){
    return FLAG_CONFIG_PASSED;
}

bool Linker::isValidSamplesSize(){
    return !FLAG_ERROR_INVALID_SAMPLES_SIZE && (config.samples_size != 0);
}
bool Linker::isValidSimulationType(){
    return !FLAG_ERROR_INVALID_SIMULATION_TYPE && (config.simulation_type != Config::SIM_TYPE::UNDEF);
}
bool Linker::isValidErrorChange(){
    return !FLAG_ERROR_INVALID_ERROR_CHANGE && (config.error_change != -1);
}
bool Linker::isValidEncoderBlockSize(){
    return !FLAG_ERROR_INVALID_ENCODER_BLOCK_SIZE && (config.encoder_block_size != 0);
}
bool Linker::isValidDecoderBlockSize(){
    return !FLAG_ERROR_INVALID_DECODER_BLOCK_SIZE && (config.decoder_block_size != 0);
}