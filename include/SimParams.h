#ifndef _SIM_PARAMS_H
#define _SIM_PARAMS_H

#include <stdint.h>

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

#define SAMPLES_SIZE_MIN_VALUE (1)

#define SIM_TYPE_MIN_VALUE (0)
#define SIM_TYPE_MAX_VALUE (Config::SIM_TYPE::SIM_TYPE_SIZE - 1)

#define ERROR_CHANGE_MIN_VALUE (0) 
#define ERROR_CHANGE_MAX_VALUE (1)

#define ENCODER_BLOCK_SIZE_MIN_VALUE (1)

#define DECODER_BLOCK_SIZE_MIN_VALUE (ENCODER_BLOCK_SIZE_MIN_VALUE)

#endif