#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_

#include <random>
#include <cmath>

#include "SimParams.h"

#define BYTE_SIZE (8)

class Simulator{
private:
    Coder* _decoder;
    Coder* _encoder;

    Config* _config;

    uint8_t** _simulated_data;
    
    uint8_t** _encoded_data;
    uint8_t** _encoded_data;

    uint8_t* _data_block;
    uint64_t _byte_encoder_block_size;

    bool FLAG_SIMULATED_EVEN_IN_BYTES = 0;

    uint8_t get_random_int_255();
    double get_random_double_1();  
    
public:
    void print_simulated_data();

    void load_simulated_data();
    void load_encoded_data();
    
    void Init();
    void SetDecoder(Coder* decoder);
    void SetEncoder(Coder* encoder);
    void SetConfig(Config* config);

};

#endif // !_SIMULATOR_H_