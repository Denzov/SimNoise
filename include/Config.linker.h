constexpr const char* CONFIG_SAMPLES_SIZE = ".SAMPLES_SIZE=";
constexpr const char* CONFIG_SIMULATION_TYPE = ".SIM_TYPE=";
constexpr const char* CONFIG_ERROR_CHANGE = ".ERROR_CHANGE=";
constexpr const char* CONFIG_ENCODER_BLOCK_SIZE = ".ENCODER_BLOCK_SIZE=";
constexpr const char* CONFIG_DECODER_BLOCK_SIZE = ".DECODER_BLOCK_SIZE=";

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
#define SIM_TYPE_MAX_VALUE (Config::SIM_TYPE::UNDEF)

#define ERROR_CHANGE_MIN_VALUE (0) 
#define ERROR_CHANGE_MAX_VALUE (1)

#define ENCODER_BLOCK_SIZE_MIN_VALUE (1)

#define DECODER_BLOCK_SIZE_MIN_VALUE (ENCODER_BLOCK_SIZE_MIN_VALUE)