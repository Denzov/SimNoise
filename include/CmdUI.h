#ifndef _CMD_UI_H_
#define _CMD_UI_H_

#include <conio.h>
#include <thread>
#include <iostream>

#include "Cmd.h"
#include "Linker.h"
#include "Simulator.h"

enum PROGRAM_STATE : uint8_t{
    WELCOME_PAGE = 0,
    CHOOSE,
    RUN,
    CONFIG_PAGE,
    HELP_PAGE,
    STOP,

    PROGRAM_STATES_SIZE
};

enum MAIN_MENU_CHOOSE_STATE : uint8_t{
    START = 0,
    CONFIG,
    HELP,
    LANGUAGE,
    PRINT_LOGO,
    CLOSE,

    MAIN_MENU_CHOOSE_STATES_SIZE
};

enum CONFIG_CHOOSE_STATE : uint8_t{
    SAMPLES_SIZE = 0, 
    SIM_TYPE,
    ERROR_CHANGE,
    ENCODER_BLOCK_SIZE,
    DECODER_BLOCK_SIZE,

    CONFIG_CHOOSE_STATES_SIZE
};

enum INKEY : uint16_t{
    CTRL_C = 3,
    
    TAB = 9,
    CTRL_TAB = 148,
    ENTER = 13,
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77
};

struct TextUI{
    static const std::string PLEASE_PRINT_KEY[CMD::LANGUAGE_SIZE];

    enum HEADER : uint8_t {MAIN, RUNNING, CONFIG, HELP, HEADERS_SIZE};
    static const std::string HEADERS[CMD::LANGUAGE_SIZE][HEADERS_SIZE];
    static const std::string MAIN_MENU_CHOOSE[CMD::LANGUAGE_SIZE][MAIN_MENU_CHOOSE_STATES_SIZE];

    enum RUN_STRING{FIRST, RUN_STRINGS_SIZE};
    static const std::string RUN_PAGE[CMD::LANGUAGE_SIZE][RUN_STRINGS_SIZE];

    static const std::string CONFIG_CHOOSE[CONFIG_CHOOSE_STATES_SIZE];
    static const std::string CONFIG_SIM_TYPES[Config::SIM_TYPE::SIM_TYPE_SIZE];

    static constexpr uint8_t HELP_STRINGS_SIZE = 19;
    static const std::string HELP_PAGE[CMD::LANGUAGE_SIZE][HELP_STRINGS_SIZE];
};

class CmdUI{
private:
    uint16_t _cur_key;
    bool _is_stoped = 0;

    PROGRAM_STATE _program_state = WELCOME_PAGE;

    MAIN_MENU_CHOOSE_STATE _main_menu_choose_state = static_cast<MAIN_MENU_CHOOSE_STATE>(0);
    CONFIG_CHOOSE_STATE _config_choose_state = static_cast<CONFIG_CHOOSE_STATE>(0);

    const uint8_t Y_VIRTUAL_END = 29;  
    const uint8_t Y_END_LOGO = 12;  
    const uint8_t Y_HEADER = 0;
    const uint8_t Y_AFTER_HEADER = Y_HEADER + 1;
    const uint8_t Y_END_CHOOSE_MENU = Y_HEADER + 4;
    
    const uint8_t X_AFTER_MENU_TABLE = 15;
    const uint8_t X_AFTER_CHOSED = X_AFTER_MENU_TABLE + 36;
    
    Linker _linker;
    Simulator _simulator;

    void init();
    
    void print_logo();
    
    void print_choose_page();
    void print_run_page();
    void print_config_page();
    void print_help_page();
   
    void config_input_handler();

    void get_cur_key();
    
    void control_state_machine();
    void display_state_machine();
    
public:
    void Run();

};


#endif // !_CMD_UI_H_