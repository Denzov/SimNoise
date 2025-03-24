#ifndef _CMD_UI_H_
#define _CMD_UI_H_

#include <conio.h>
#include <thread>

#include "Cmd.h"
#include "Linker.h"

enum PROGRAM_STATE : uint8_t{
    CHOOSE = 0,
    RUN,
    SETTING_MENU,
    HELP_MENU,
    STOP,

    PROGRAM_STATE_SIZE
};

enum MAIN_MENU_STATE : uint8_t{
    START = 0,
    SETTINGS,
    HELP,
    CLOSE,

    MAIN_MENU_STATE_SIZE
};

enum INKEY : uint8_t{
    CTRL_C = 3,
    ENTER = 13,
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77
};

class CmdUI{
private:
    char cur_key;
    bool _is_stoped = 0;

    PROGRAM_STATE _program_state = CHOOSE;
    MAIN_MENU_STATE _choose_state = START;

    const uint8_t Y_HEADER = 12;
    const uint8_t Y_AFTER_HEADER = Y_HEADER + 1;
    const uint8_t Y_END_TABLE = 40;
    
    const uint8_t X_AFTER_MENU_TABLE = 15;
    const uint8_t X_AFTER_CHOSED = 50;
    
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