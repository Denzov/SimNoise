#include "../include/CmdUI.h"

CMD::LANGUAGE CMD::_language = EN;

void CmdUI::init(){
    CMD::SET_STANDART();
    CMD::SET_LANGUAGE(CMD::EN);

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
    switch(CMD::GET_LANGUAGE()){
        case CMD::EN:
            CMD::GOTO(3, Y_HEADER);
            CMD::PRINT_N_SPACES(X_AFTER_MENU_TABLE - 3, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
            
            CMD::GOTO(0, Y_HEADER);
            CMD::PRINT("--|MENU", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_HEADER);
            CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
            break;

        case CMD::RU:

            break;
    }

    for(uint8_t i = 0; i < MAIN_MENU_STATE_SIZE; i++){
        static std::string choose_options_en[CMD::LANGUAGE_SIZE][MAIN_MENU_STATE_SIZE] = {"Start", "Settings", "Help", "Close"};
    
        CMD::GOTO(0, Y_AFTER_HEADER + i);

        if(_choose_state == static_cast<MAIN_MENU_STATE>(i)){
            CMD::PRINT("  |->", CMD::GREEN);
            CMD::PRINT(choose_options_en[CMD::GET_LANGUAGE()][i], CMD::GREEN, CMD::UNDERLINE);
            
            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_AFTER_HEADER + i);
            CMD::PRINT("|");
        }
        else{
            CMD::PRINT("  |");
            CMD::PRINT(choose_options_en[CMD::GET_LANGUAGE()][i]);

            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_AFTER_HEADER + i);
            CMD::PRINT("|");
        }
    }   
}

void CmdUI::print_run_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT("RUN", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
}

void CmdUI::print_settings_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT("SETTINGS", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
}

void CmdUI::print_help_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT("HELP", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + 1);
    CMD::PRINT("CTRL+C - CLOSE PROGRAM\n");

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + 2);
    CMD::PRINT("UP/DOWN ARROWS - MOVE YOUR CHOOSE");
    
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + 3);
    CMD::PRINT("ENTER | RIGHT/LEFT ARROWS - CHOOSE/CANCEL");
}

void CmdUI::control_state_machine(){
    switch (_program_state)
    {
    case PROGRAM_STATE::CHOOSE:
        switch (cur_key)
        {
        case UP:
            _choose_state = static_cast<MAIN_MENU_STATE>((_choose_state + MAIN_MENU_STATE_SIZE - 1) % MAIN_MENU_STATE_SIZE);
            break;

        case DOWN:
            _choose_state = static_cast<MAIN_MENU_STATE>((_choose_state + 1) % MAIN_MENU_STATE_SIZE);
            break;
        
        case ENTER:
        case RIGHT:
            switch (_choose_state)
            {
            case START:
                _program_state = RUN;                    
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
            linker.loadStandartFiles();
            linker.loadUserCode();
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
    CMD::PRINT("_____PRINT ANY KEY_____\n", CMD::RED, CMD::INVERSION);
    
    while(!_is_stoped){      
        get_cur_key();
        if(cur_key == CTRL_C) _program_state = STOP;
        control_state_machine();

        CMD::CLEAR_FROME(Y_HEADER);
        display_state_machine();
    }
}   