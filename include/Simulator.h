#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <random>
#include <string>
#include <bitset>
#include <cmath>
#include <iostream>

#include "SimParams.h"

#define BYTE_SIZE (8)

class Simulator{
private:
    Coder _decoder;
    Coder _encoder;

    Config* _config;

    int64_t _back_up_samples_size = 0;  

    uint8_t** _simulated_data;
    
    uint8_t** _encoded_data;
    uint8_t** _decoded_data;

    uint8_t* _data_block;
    uint64_t _simulation_block_byte_size;
    uint64_t _encoder_block_byte_size;
    uint64_t _decoder_block_byte_size;

    bool FLAG_SIMULATED_EVEN_IN_BYTES = 0;
    bool FLAG_ENCODED_EVEN_IN_BYTES = 0;
    bool FLAG_DECODED_EVEN_IN_BYTES = 0;

    uint8_t get_random_int_255();
    float get_random_float_1();  
    
    void calc_simulation_block_byte_size();
    void calc_encoder_block_byte_size();
    void calc_decoder_block_byte_size();

    void del_simulated_data();
    void del_encoded_data();
    void del_decoded_data();

    void simulate_data();
    void encode_data();
    void decode_data();

    void add_noise_to_encoded_data();
    void noise_bit_by_bit();
    void noise_byte_by_byte();

    void update_back_up_samples_size();    
public:
    Simulator();
    
    void SetDecoder(Coder decoder);
    void SetEncoder(Coder encoder);
    void SetConfig(Config* config);
    
    void Print();
    void Simulate();
};

#endif // !_SIMULATOR_H_