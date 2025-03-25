#ifndef _CMD_UI_H_
#define _CMD_UI_H_

#include <conio.h>
#include <thread>

#include "Cmd.h"
#include "Linker.h"

enum PROGRAM_STATE : uint8_t{
    WELCOME_PAGE = 0,
    CHOOSE,
    RUN,
    SETTING_MENU,
    HELP_MENU,
    STOP,

    PROGRAM_STATES_SIZE
};

enum MAIN_MENU_STATE : uint8_t{
    START = 0,
    SETTINGS,
    HELP,
    PRINT_LOGO,
    CLOSE,

    MAIN_MENU_STATES_SIZE
};

enum INKEY : uint8_t{
    CTRL_C = 3,
    ENTER = 13,
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77
};


struct TextUI{
    static const std::string PLEASE_PRINT_KEY[CMD::LANGUAGE_SIZE];

    enum HEADER{ MAIN, RUNNING, SETTINGS, HELP, HEADERS_SIZE};
    static const std::string HEADERS[CMD::LANGUAGE_SIZE][HEADERS_SIZE];
    static const std::string MAIN_MENU[CMD::LANGUAGE_SIZE][MAIN_MENU_STATES_SIZE];

    enum RUN_STRING{FIRST, RUN_STRINGS_SIZE};
    static const std::string RUN_PAGE[CMD::LANGUAGE_SIZE][RUN_STRINGS_SIZE];

    static constexpr uint8_t HELP_STRINGS_SIZE = 18;
    static const std::string HELP_PAGE[CMD::LANGUAGE_SIZE][HELP_STRINGS_SIZE];
};

class CmdUI{
private:
    char cur_key;
    bool _is_stoped = 0;

    PROGRAM_STATE _program_state = WELCOME_PAGE;
    MAIN_MENU_STATE _choose_state = START;

    const uint8_t Y_VIRTUAL_END = 50;  
    const uint8_t Y_END_LOGO = 12;  
    const uint8_t Y_HEADER = 0;
    const uint8_t Y_AFTER_HEADER = Y_HEADER + 1;
    const uint8_t Y_END_CHOOSE_MENU = Y_HEADER + 4;
    
    const uint8_t X_AFTER_MENU_TABLE = 15;
    const uint8_t X_AFTER_CHOSED = X_AFTER_MENU_TABLE + 35;
    
    Linker linker;

    void init();
    
    void print_logo();
    
    void print_choose_page();
    void print_run_page();
    void print_settings_page();
    void print_help_page();
   
    void get_cur_key();
    
    void control_state_machine();
    void display_state_machine();
    
public:
    void Run();

};


#endif // !_CMD_UI_H_