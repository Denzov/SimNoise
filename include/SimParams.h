#ifndef _SIM_PARAMS_H
#define _SIM_PARAMS_H

#include <stdint.h>

typedef void (*Coder)(uint8_t* data, uint8_t* out, int64_t data_length);

struct Config{
    int64_t samples_size;
    
    enum SIM_TYPE : uint8_t{
        BIT_BY_BIT = 0,
        BYTE_BY_BYTE,
        FROM_LOADING,
        
        SIM_TYPE_SIZE, 
        
        UNDEF 
    } simulation_type;

    float error_change;

    int64_t encoder_bit_block_size;
    int64_t decoder_bit_block_size;   
};

#define SAMPLES_SIZE_MIN_VALUE (1)

#define SIM_TYPE_MIN_VALUE (0)
#define SIM_TYPE_MAX_VALUE (Config::SIM_TYPE::SIM_TYPE_SIZE - 1)

#define ERROR_CHANGE_MIN_VALUE (0) 
#define ERROR_CHANGE_MAX_VALUE (1)

#define ENCODER_BLOCK_SIZE_MIN_VALUE (1)

#define DECODER_BLOCK_SIZE_MIN_VALUE (ENCODER_BLOCK_SIZE_MIN_VALUE)

#endif