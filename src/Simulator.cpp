#include "../include/Simulator.h"

uint8_t Simulator::get_random_int_255(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, (1 << 8) - 1);
    
    return dist(gen);
}

double Simulator::get_random_double_1(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0, 1);
    
    return dist(gen);
}

void Simulator::print_simulated_data(){
    uint64_t byte_encoder_block_size = std::ceil(static_cast<float>(_config->encoder_block_size) / BYTE_SIZE);

    for(uint64_t sample = 0; sample < _config->samples_size; sample++){
        for(uint64_t byte = 0; byte < byte_encoder_block_size; byte++){
            printf("%d\n", _simulated_data[sample][byte]);
        }
    }
}

void Simulator::load_simulated_data(){
    _byte_encoder_block_size = std::ceil(static_cast<float>(_config->encoder_block_size) / BYTE_SIZE);
    FLAG_SIMULATED_EVEN_IN_BYTES = _config->encoder_block_size % 8 == 0;

    _simulated_data = new uint8_t*[_config->samples_size];

    if(FLAG_SIMULATED_EVEN_IN_BYTES){
        for(uint64_t sample = 0; sample < _config->samples_size; sample++){
            _simulated_data[sample] = new uint8_t[_byte_encoder_block_size];      
            for(uint64_t byte = 0; byte < _byte_encoder_block_size; byte++){
                _simulated_data[sample][byte] = get_random_int_255();
            }
        }
    }
    else{
        for(uint64_t sample = 0; sample < _config->samples_size; sample++){
            _simulated_data[sample] = new uint8_t[_byte_encoder_block_size];      
            for(uint64_t byte = 0; byte < _byte_encoder_block_size; byte++){
                if(byte == _byte_encoder_block_size - 1){
                    _simulated_data[sample][byte] = get_random_int_255() % (1 << (_config->encoder_block_size % 8));
                }
                else{
                    _simulated_data[sample][byte] = get_random_int_255();
                }
            }
        }
    }
}

voidC Simulator::load_encoded_data(){

}

void Simulator::Init(){

}

void Simulator::SetDecoder(Coder* decoder){
    _decoder = decoder;
}

void Simulator::SetEncoder(Coder* encoder){
    _encoder = encoder;
}

void Simulator::SetConfig(Config* config){
    _config = config;
}

