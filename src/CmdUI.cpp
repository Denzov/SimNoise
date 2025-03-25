#include "../include/CmdUI.h"

CMD::LANGUAGE CMD::_language = EN;

const std::string TextUI::PLEASE_PRINT_KEY[CMD::LANGUAGE_SIZE]{
    {"-----PRINT ANY KEY-----"},
    {"----НАЖМИТЕ КЛАВИШУ----"}
};

const std::string TextUI::MAIN_MENU[CMD::LANGUAGE_SIZE][MAIN_MENU_STATES_SIZE]{
    {"Start", "Settings", "Help", "Close"},
    {"Начало", "Настройки", "Помощь", "Выход"}
};

const std::string TextUI::HEADERS[CMD::LANGUAGE_SIZE][HEADERS_SIZE]{
    {"MENU", "RUNNING", "SETTINGS", "HELP"},
    {"МЕНЮ", "В РАБОТЕ", "НАСТРОЙКИ", "ПОМОЩЬ"}
};

const std::string TextUI::RUN_PAGE[CMD::LANGUAGE_SIZE][TextUI::RUN_STRINGS_SIZE]{
    {"# User files is loaded;"},
    {"# Пользовательские файлы подгружены;"}
};

const std::string TextUI::HELP_PAGE[CMD::LANGUAGE_SIZE][TextUI::HELP_STRINGS_SIZE]{
    {"CTRL+C - CLOSE PROGRAM", "UP/DOWN ARROWS - MOVE YOUR CHOOSE", "ENTER | RIGHT/LEFT ARROWS - CHOOSE/CANCEL"},
    {"CTRL+C - ЗАВЕРШИТЬ ПРОГРАММУ", "СТРЕЛКИ ВВЕРХ/ВНИЗ - ПЕРЕМЕЩАТЬ ВЫБОР", "ENTER | СТРЕЛКИ ПРАВАЯ/ЛЕВАЯ - ВЫБРАТЬ/ОТМЕНИТЬ ВЫБОР"}
};  

void CmdUI::init(){
    CMD::SET_STANDART();
    CMD::SET_LANGUAGE(CMD::RU);

}

void CmdUI::get_cur_key(){
    cur_key = _getch();
};

void CmdUI::print_logo(){
    CMD::GOTO(0, 0);

    CMD::COLOR PLANET_COLOR = CMD::WHITE_BLUE;
    CMD::COLOR CIRCLE_COLOR = CMD::YELLOW;

    CMD::PRINT("                                                     ___\n", CIRCLE_COLOR);
    CMD::PRINT("                                                  ,o88888\n", CIRCLE_COLOR);
    CMD::PRINT("                                               ,o8888888'\n", CIRCLE_COLOR);
    CMD::PRINT("                         ,:o:o:oooo.", PLANET_COLOR);
    CMD::PRINT("        ,8O88Pd8888\"\n", CIRCLE_COLOR);
    CMD::PRINT("                     ,.::.::o:ooooOoOoO.", PLANET_COLOR);
    CMD::PRINT(" ,oO8O8Pd888'\"\n", CIRCLE_COLOR);
    CMD::PRINT("                   ,.:.::o:ooOoOoOO8O8OOo.", PLANET_COLOR);
    CMD::PRINT("8OOPd8O8O\n", CIRCLE_COLOR);
    CMD::PRINT("                  , ..:.::o:ooOoOOOO8OOOOo.", PLANET_COLOR);
    CMD::PRINT("FdO8O8\"\n", CIRCLE_COLOR);
    CMD::PRINT("                 , ..:.::", PLANET_COLOR);
    CMD::PRINT("__DENZOV__", CMD::YELLOW);
    CMD::PRINT("888O8O,", PLANET_COLOR);
    CMD::PRINT("COCOO\"\n", CIRCLE_COLOR);
    CMD::PRINT("                , . ..:.::o:ooOoOOOO8OOOO", PLANET_COLOR);
    CMD::PRINT("COCO\"\n", CIRCLE_COLOR);
    CMD::PRINT("                 . ..:.::o:ooOoOoOO8O8O", PLANET_COLOR); 
    CMD::PRINT("CCCC\"", CIRCLE_COLOR);
    CMD::PRINT("o\n", PLANET_COLOR);
    CMD::PRINT("                    . ..:.::o:ooooOoCo", PLANET_COLOR);
    CMD::PRINT("CCC\"", CIRCLE_COLOR);
    CMD::PRINT("o:o\n", PLANET_COLOR);
    CMD::GOTO(15, 11);
    CMD::PRINT("N O I S E  S I M U L A T I O N\n", CMD::YELLOW, CMD::INVERSION);
}

void CmdUI::print_choose_page(){    
    CMD::GOTO(3, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_MENU_TABLE - 3, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    
    CMD::GOTO(0, Y_HEADER);
    CMD::PRINT("  |", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::MAIN], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_HEADER);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    for(uint8_t i = 0; i < MAIN_MENU_STATES_SIZE; i++){
        CMD::GOTO(0, Y_AFTER_HEADER + i);

        if(_choose_state == static_cast<MAIN_MENU_STATE>(i)){
            CMD::PRINT("  |->", CMD::GREEN, CMD::BOLD);
            CMD::PRINT(TextUI::MAIN_MENU[CMD::GET_LANGUAGE()][i], CMD::GREEN, CMD::UNDERLINE);
            
            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_AFTER_HEADER + i);
            CMD::PRINT("|", CMD::PURPLE, CMD::BOLD);
        }
        else{
            CMD::PRINT("  |", CMD::PURPLE, CMD::BOLD);
            CMD::PRINT(TextUI::MAIN_MENU[CMD::GET_LANGUAGE()][i], CMD::BASE_COLOR, CMD::BOLD);

            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_AFTER_HEADER + i);
            CMD::PRINT("|", CMD::PURPLE, CMD::BOLD);
        }
    }   
}

void CmdUI::print_run_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::RUNNING], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    uint8_t shift = 1;
    if(linker.isLoadedUserCode()){
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + shift);
        CMD::PRINT(TextUI::RUN_PAGE[CMD::GET_LANGUAGE()][TextUI::RUN_STRING::FIRST], CMD::YELLOW, CMD::BOLD);
    }
}

void CmdUI::print_settings_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::SETTINGS], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
}

void CmdUI::print_help_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    static const uint8_t VALUE_HELP_STRINGS = 4;
    static const std::string help_en[CMD::LANGUAGE_SIZE][VALUE_HELP_STRINGS];

    uint8_t shift = 0;

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::HELP], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    for(uint8_t shift = 1; shift <= TextUI::HELP_STRINGS_SIZE; shift++){
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + shift);
        CMD::PRINT(TextUI::HELP_PAGE[CMD::GET_LANGUAGE()][shift - 1]);
    }
}

void CmdUI::control_state_machine(){
    switch (_program_state)
    {
    case PROGRAM_STATE::CHOOSE:
        switch (cur_key)
        {
        case UP:
            _choose_state = static_cast<MAIN_MENU_STATE>((_choose_state + MAIN_MENU_STATES_SIZE - 1) % MAIN_MENU_STATES_SIZE);
            break;

        case DOWN:
            _choose_state = static_cast<MAIN_MENU_STATE>((_choose_state + 1) % MAIN_MENU_STATES_SIZE);
            break;
        
        case ENTER:
        case RIGHT:
            switch (_choose_state)
            {
            case START:
                _program_state = RUN;                    

                linker.loadStandartFiles();
                linker.passUserCode();
        
                break;
            
            case SETTINGS:
                _program_state = SETTING_MENU;
                break;    
            
            case HELP:
                _program_state = HELP_MENU;
                break;

            case CLOSE:
                _program_state = STOP;
            }
        }
        break;
    
    case PROGRAM_STATE::RUN:
        switch(cur_key){
            case ENTER:
            case LEFT:
                _choose_state = MAIN_MENU_STATE::START;
                _program_state = PROGRAM_STATE::CHOOSE;
                break;
            }
            
        break;

    case PROGRAM_STATE::SETTING_MENU:
        switch(cur_key){
            case ENTER:
            case LEFT:
                _choose_state = MAIN_MENU_STATE::SETTINGS;
                _program_state = PROGRAM_STATE::CHOOSE;
                break;
        }    
        break;

    case PROGRAM_STATE::HELP_MENU:
        switch (cur_key)
        {
        case ENTER:
        case LEFT:
            _choose_state = MAIN_MENU_STATE::HELP;
            _program_state = PROGRAM_STATE::CHOOSE;
            break;
        }
        break;
    
    case PROGRAM_STATE::STOP:
        break;
    }
}

void CmdUI::display_state_machine(){
    CMD::GOTO(0, Y_HEADER);

    print_choose_page();

    switch(_program_state){
        case PROGRAM_STATE::CHOOSE:
            break;
            
        case PROGRAM_STATE::RUN:
            print_run_page();
            break;

        case PROGRAM_STATE::SETTING_MENU:
            print_settings_page();
            break;
        
        case PROGRAM_STATE::HELP_MENU:
            print_help_page();
            break;

        case PROGRAM_STATE::STOP:
            CMD::CLEAR_ALL();
            _is_stoped = 1;
            break;
    }

    CMD::GOTO(0, Y_END_TABLE);
}

void CmdUI::Run(){
    init();
    
    print_logo();
    
    CMD::GOTO(0, Y_HEADER);
    CMD::PRINT_N_SPACES(19);
    CMD::PRINT(TextUI::PLEASE_PRINT_KEY[CMD::GET_LANGUAGE()], CMD::RED, CMD::INVERSION);
    
    while(!_is_stoped){      
        get_cur_key();
        if(cur_key == CTRL_C) _program_state = STOP;
        control_state_machine();

        CMD::CLEAR_FROME(Y_HEADER);
        display_state_machine();
    }
}   