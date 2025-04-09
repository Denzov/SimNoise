#include "../include/Simulator.h"

uint8_t Simulator::get_random_int_255(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, (1 << 8) - 1);
    
    return dist(gen);
}

float Simulator::get_random_float_1(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(0, 1);
    
    return dist(gen);
}

void Simulator::calc_simulation_block_byte_size(){
    _simulation_block_byte_size = std::ceil(static_cast<float>(_config->decoder_bit_block_size) / BYTE_SIZE);
}

void Simulator::calc_encoder_block_byte_size(){
    _encoder_block_byte_size = std::ceil(static_cast<float>(_config->decoder_bit_block_size) / BYTE_SIZE);
}

void Simulator::calc_decoder_block_byte_size(){
    _decoder_block_byte_size = std::ceil(static_cast<float>(_config->decoder_bit_block_size) / BYTE_SIZE);
}

void Simulator::del_simulated_data(){
    for(int64_t sample = 0; sample < _back_up_samples_size; sample++){
        delete[] _simulated_data[sample];
    }    

    delete[] _simulated_data;
}

void Simulator::del_encoded_data(){
    for(int64_t sample = 0; sample < _back_up_samples_size; sample++){
        delete[] _encoded_data[sample];
    }    

    delete[] _encoded_data;
}

void Simulator::del_decoded_data(){
    for(int64_t sample = 0; sample < _back_up_samples_size; sample++){
        delete[] _decoded_data[sample];
    }    

    delete[] _decoded_data;
}

void Simulator::update_back_up_samples_size(){
    _back_up_samples_size = _config->samples_size;
}

void Simulator::Print(){
    printf("Encoder block size bit: %d\n", _config->encoder_bit_block_size % BYTE_SIZE);
    printf("Encoder block size: %d\n", _encoder_block_byte_size);
    printf("Error change: %f\n\n", _config->error_chance);

    printf("Simulated data:\n");
    for(uint64_t sample = 0; sample < _config->samples_size; sample++){
        for(uint64_t byte = 0; byte < _simulation_block_byte_size; byte++){
            std::cout << std::bitset<8>(_simulated_data[sample][byte]) << '\n';
        }
    }
    
    printf("\nEncoded data:\n");
    for(uint64_t sample = 0; sample < _config->samples_size; sample++){
        for(uint64_t byte = 0; byte < _encoder_block_byte_size; byte++){
            std::cout << std::bitset<8>(_encoded_data[sample][byte]) << '\n';
        }
    }

    printf("\nDecoded data:\n");
    for(uint64_t sample = 0; sample < _config->samples_size; sample++){
        for(uint64_t byte = 0; byte < _encoder_block_byte_size; byte++){
            std::cout << std::bitset<8>(_decoded_data[sample][byte]) << '\n';
        }
    }
}

void Simulator::simulate_data(){
    FLAG_SIMULATED_EVEN_IN_BYTES = _config->decoder_bit_block_size % 8 == 0;

    del_simulated_data();

    _simulated_data = new uint8_t*[_config->samples_size];
    if(FLAG_SIMULATED_EVEN_IN_BYTES){
        for(int64_t sample = 0; sample < _config->samples_size; sample++){
            _simulated_data[sample] = new uint8_t[_simulation_block_byte_size];      
            for(int64_t byte = 0; byte < _simulation_block_byte_size; byte++){
                _simulated_data[sample][byte] = get_random_int_255();
            }
        }
        }
    else{
        for(int64_t sample = 0; sample < _config->samples_size; sample++){
            _simulated_data[sample] = new uint8_t[_simulation_block_byte_size];      
            for(int64_t byte = 0; byte < _simulation_block_byte_size; byte++){
                if(byte == _simulation_block_byte_size - 1){
                    _simulated_data[sample][byte] = get_random_int_255() % (1 << (_config->decoder_bit_block_size % 8));
                }
                else{
                    _simulated_data[sample][byte] = get_random_int_255();
                }
            }
        }
    }
}

void Simulator::encode_data(){
    FLAG_ENCODED_EVEN_IN_BYTES = _config->encoder_bit_block_size % 8 == 0;

    del_encoded_data();

    _encoded_data = new uint8_t*[_config->samples_size];
    for(int64_t sample = 0; sample < _config->samples_size; sample++){
        _encoded_data[sample] = new uint8_t[_encoder_block_byte_size];
        
        _encoder(_simulated_data[sample], _encoded_data[sample]);
    }
}

void Simulator::decode_data(){
    FLAG_DECODED_EVEN_IN_BYTES = _config->decoder_bit_block_size % 8 == 0;

    del_decoded_data();

    _decoded_data = new uint8_t*[_config->samples_size];
    for(int64_t sample = 0; sample < _config->samples_size; sample++){
        _decoded_data[sample] = new uint8_t[_decoder_block_byte_size];
        
        _decoder(_encoded_data[sample], _decoded_data[sample]);
    }
}

void Simulator::add_noise_to_encoded_data(){
    switch (_config->simulation_type)
    {
    case Config::SIM_TYPE::BIT_BY_BIT:
        noise_bit_by_bit();    
        break;

    case Config::SIM_TYPE::BYTE_BY_BYTE:
        noise_byte_by_byte();
        break;
    
    case Config::SIM_TYPE::FROM_LOADING:
        
        break;
    }
}

void Simulator::noise_bit_by_bit(){
    for(int64_t sample = 0; sample < _config->samples_size; sample++){   
        for(uint8_t byte = 0; byte < _encoder_block_byte_size - 1; byte++){
            for(uint8_t bit = 0; bit < BYTE_SIZE; bit++){
                if(get_random_float_1() <= _config->error_chance){
                    _encoded_data[sample][byte] = 
                        (_encoded_data[sample][byte] & ~(1 << bit)) | ((~(_encoded_data[sample][byte] >> bit) & 0b1) << bit);
                } 
            }      
        }
        
        if(FLAG_ENCODED_EVEN_IN_BYTES){
            for(uint8_t bit = 0; bit < BYTE_SIZE; bit++){
                if(get_random_float_1() <= _config->error_chance){
                    _encoded_data[sample][_encoder_block_byte_size - 1] = 
                        (_encoded_data[sample][_encoder_block_byte_size - 1] & ~(1 << bit)) | ((~(_encoded_data[sample][_encoder_block_byte_size - 1] >> bit) & 0b1) << bit);
                } 
            }
        }
        else{
            for(uint8_t bit = 0; bit < _config->encoder_bit_block_size % BYTE_SIZE; bit++){
                if(get_random_float_1() <= _config->error_chance){
                    _encoded_data[sample][_encoder_block_byte_size - 1] = 
                        (_encoded_data[sample][_encoder_block_byte_size - 1] & ~(1 << bit)) | ((~(_encoded_data[sample][_encoder_block_byte_size - 1] >> bit) & 0b1) << bit);
                } 
            }
        }
    }
}

void Simulator::noise_byte_by_byte(){
    
}

Simulator::Simulator(){
    _simulated_data = new uint8_t*[0];
    _encoded_data = new uint8_t*[0];
    _decoded_data = new uint8_t*[0];
}

void Simulator::SetDecoder(Coder decoder){
    _decoder = decoder;
}

void Simulator::SetEncoder(Coder encoder){
    _encoder = encoder;
}

void Simulator::SetConfig(Config* config){
    _config = config;
}

void Simulator::Simulate(){
    calc_simulation_block_byte_size();
    calc_encoder_block_byte_size();
    calc_decoder_block_byte_size(); 

    simulate_data();
    encode_data();
    
    add_noise_to_encoded_data();    

    decode_data();
    
    update_back_up_samples_size();
}