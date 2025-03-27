#include "../include/CmdUI.h"

CMD::LANGUAGE CMD::_language = EN;

const std::string TextUI::PLEASE_PRINT_KEY[CMD::LANGUAGE_SIZE]{
    {"-----PRINT ANY KEY-----"},
    {"----НАЖМИТЕ КЛАВИШУ----"}
};

const std::string TextUI::MAIN_MENU[CMD::LANGUAGE_SIZE][MAIN_MENU_STATES_SIZE]{
    {"Start", "Config", "Help", "Language", "Logo", "Close"},
    {"Начало", "Конфиг", "Помощь", "Язык", "Логотип","Выход"}
};

const std::string TextUI::HEADERS[CMD::LANGUAGE_SIZE][HEADERS_SIZE]{
    {"MENU", "RUNNING", "CONFIG", "HELP"},
    {"МЕНЮ", "В РАБОТЕ", "КОНФИГ","ПОМОЩЬ"}
};

const std::string TextUI::RUN_PAGE[CMD::LANGUAGE_SIZE][TextUI::RUN_STRINGS_SIZE]{
    {"# User files is loaded;"},
    {"# Пользовательские файлы подгружены;"}
};

const std::string TextUI::CONFIG_SIM_TYPES[Config::SIM_TYPE::SIM_TYPE_SIZE]{ 
    "BIT_BY_BIT", "BYTE_BIT_BYTE", "LOADING"    
};

const std::string TextUI::HELP_PAGE[CMD::LANGUAGE_SIZE][TextUI::HELP_STRINGS_SIZE]{
    {"CONTROL:", "\tCTRL+C - CLOSE PROGRAM", "\tUP/DOWN ARROWS - MOVE YOUR CHOOSE", "\tENTER | RIGHT/LEFT ARROWS - CHOOSE/CANCEL",
    "", "TO SET AN ATTRIBUTE IN A CONFIG, YOU MUST WRITE THE ATTRIBUTE NAME", "\tIN THE CONFIG ITSELF, STARTING WITH A DOT, AND THEN IMMEDIATELY SET ITS VALUE VIA \"=\"",
    "", "ATTRIBUTES OF CONFIG:", "\t.SAMPLES_SIZE=[int]", "\t.SIM_TYPE=[int]", "\t.ERROR_CHANGE=[float, value is between 0 and 1]", "\t.ENCODER_BLOCK_SIZE=[int]", "\t.DECODER_BLOCK_SIZE=[int]",
    "", "THE SYM_TYPE ATTRIBUTE IS DIVIDED INTO FIRST, SECOND, THIRD:", 
    "\t- FIRST IS A SIMULATION BIT-BY-BIT", "\t- SECOND IS A SIMULATION BYTE-BY-BYTE", "\t- THIRD IS SIMULATION WITH YOUR DATA LOADING"}, 

    {"УПРАВЛЕНИЕ:", "\tCTRL+C - ЗАВЕРШИТЬ ПРОГРАММУ", "\tСТРЕЛКИ ВВЕРХ/ВНИЗ - ПЕРЕМЕЩАТЬ ВЫБОР", "\tENTER | СТРЕЛКИ ПРАВАЯ/ЛЕВАЯ - ВЫБРАТЬ/ОТМЕНИТЬ ВЫБОР",
    "", "ЧТОБЫ УСТАНОВИТЬ АТРИБУТ В КОНФИГ-ФАЙЛЕ НЕОБХОДИМО В САМОМ ФАЙЛЕ \"CONFIG\"", "\tПРОПИСАТЬ, НАЧИНАЯ С ТОЧКИ, НАЗВАНИЕ АТРИБУТА, ПОТОМ СРАЗУ ЖЕ ВЫСТАВИТЬ ЕГО ЗНАЧЕНИЕ ЧЕРЕЗ \"=\"",
    "", "АТРИБУТЫ КОНФИГ-ФАЙЛА:", "\t.SAMPLES_SIZE=[int]", "\t.SIM_TYPE=[int]", "\t.ERROR_CHANGE=[float, значение между 0 и 1]", "\t.ENCODER_BLOCK_SIZE=[int]", "\t.DECODER_BLOCK_SIZE=[int]",
    "", "АТРИБУТ SYM_TYPE РАЗДЕЛЕН НА ПЕРВЫЙ, ВТОРОЙ И ТРЕТИЙ:",
    "\t- ПЕРВЫЙ - СИМУЛЯЦИЯ БИТ ЗА БИТОМ", "\t- ВТОРОЙ - СИМУЛЯЦИЯ БАЙТ ЗА БАЙТОМ", "\t- ТРЕТЬЯ - СИМУЛЯЦИЯ С ПОДГРУЗКОЙ ВАШИХ ДАННЫХ"}
};  

void CmdUI::init(){
    CMD::SET_STANDART();
}

void CmdUI::get_cur_key(){
    _cur_key = _getch();
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

    CMD::GOTO(0, 0);
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

void CmdUI::print_config_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::CONFIG], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    if(linker.isPassedConfig()){
        uint8_t shift = 0;

        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + ++shift);
        CMD::PRINT(CONFIG_SAMPLES_SIZE, CMD::BASE_COLOR, CMD::BOLD);
        if(linker.isValidSamplesSize()){
            CMD::PRINT(std::to_string(linker.getConfig().samples_size), CMD::YELLOW, CMD::BOLD);
        }
        else{
            CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
        }
        
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + ++shift);
        CMD::PRINT(CONFIG_SIMULATION_TYPE, CMD::BASE_COLOR, CMD::BOLD);
        if(linker.isValidSimulationType()){
            CMD::PRINT(TextUI::CONFIG_SIM_TYPES[linker.getConfig().simulation_type], CMD::YELLOW, CMD::BOLD);
        }
        else{
            CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
        }

        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + ++shift);
        CMD::PRINT(CONFIG_ERROR_CHANGE, CMD::BASE_COLOR, CMD::BOLD);
        if(linker.isValidErrorChange()){
            CMD::PRINT(std::to_string(linker.getConfig().error_change), CMD::YELLOW, CMD::BOLD);
        }
        else{
            CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
        }

        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + ++shift);
        CMD::PRINT(CONFIG_ENCODER_BLOCK_SIZE, CMD::BASE_COLOR, CMD::BOLD);
        if(linker.isValidEncoderBlockSize()){
            CMD::PRINT(std::to_string(linker.getConfig().encoder_block_size), CMD::YELLOW, CMD::BOLD);
        }
        else{
            CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
        }

        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + ++shift);
        CMD::PRINT(CONFIG_DECODER_BLOCK_SIZE, CMD::BASE_COLOR, CMD::BOLD);
        if(linker.isValidDecoderBlockSize()){
            CMD::PRINT(std::to_string(linker.getConfig().decoder_block_size), CMD::YELLOW, CMD::BOLD);
        }
        else{
            CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
        }
    }
    else{
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + 1);
        CMD::PRINT("FORMATTING ERROR IN CONFIG");
    }

}

void CmdUI::print_help_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);
    // CMD::PRINT("|", CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    uint8_t shift = 0;

    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT(TextUI::HEADERS[CMD::GET_LANGUAGE()][TextUI::HELP], CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

    for(uint8_t shift = 1; shift <= TextUI::HELP_STRINGS_SIZE; shift++){
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + shift);
        CMD::PRINT(TextUI::HELP_PAGE[CMD::GET_LANGUAGE()][shift - 1]);
        
        if(Y_HEADER + shift > Y_END_CHOOSE_MENU){
            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_HEADER + shift);
            CMD::PRINT("|", CMD::PURPLE, CMD::BOLD);
        }
    }
}

void CmdUI::control_state_machine(){
    switch (_program_state)
    {
    case PROGRAM_STATE::WELCOME_PAGE:
        _program_state = CHOOSE;
        break;

    case PROGRAM_STATE::CHOOSE:
        switch (_cur_key)
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
                linker.passConfig();
                break;
            
            case CONFIG:
                _program_state = CONFIG_PAGE;

                linker.loadStandartFiles();
                    
                linker.passUserCode();
                linker.passConfig();
                break;
            
            case HELP:
                _program_state = HELP_PAGE;
                break;

            case LANGUAGE:
                CMD::SET_LANGUAGE(static_cast<CMD::LANGUAGE>((CMD::GET_LANGUAGE() + 1) % CMD::LANGUAGE_SIZE));
                break;    
            
            case PRINT_LOGO:
                _program_state = WELCOME_PAGE;
                break;

            case CLOSE:
                _program_state = STOP;
            }
        }
        break;
    
    case PROGRAM_STATE::RUN:
        switch(_cur_key){
            case ENTER:
            case LEFT:
                _choose_state = MAIN_MENU_STATE::START;
                _program_state = PROGRAM_STATE::CHOOSE;
                break;
            }
        break;
    
    case PROGRAM_STATE::CONFIG_PAGE:
        switch(_cur_key){    
            case ENTER:
            case LEFT:
                _choose_state = MAIN_MENU_STATE::CONFIG;
                _program_state = PROGRAM_STATE::CHOOSE;
                break;
        }
        break;

    case PROGRAM_STATE::HELP_PAGE:
        switch (_cur_key)
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
    CMD::GOTO(0, 0);

    switch(_program_state){
        case PROGRAM_STATE::WELCOME_PAGE:
            print_logo();

            CMD::GOTO(0, Y_END_LOGO);
            CMD::PRINT_N_SPACES(19);
            CMD::PRINT(TextUI::PLEASE_PRINT_KEY[CMD::GET_LANGUAGE()], CMD::RED, CMD::INVERSION);
            break;

        case PROGRAM_STATE::CHOOSE:
            print_choose_page();
            break;
            
        case PROGRAM_STATE::RUN:
            print_choose_page();    
            print_run_page();

            break;

        case PROGRAM_STATE::CONFIG_PAGE:
            print_choose_page();    
            print_config_page();
            break;
        
        case PROGRAM_STATE::HELP_PAGE:
            print_choose_page();
            print_help_page();
            break;

        case PROGRAM_STATE::STOP:
            CMD::CLEAR_ALL();
            _is_stoped = 1;
            break;
    }

    CMD::GOTO(0, Y_VIRTUAL_END);
}

void CmdUI::Run(){
    init();

    display_state_machine();

    while(!_is_stoped){      
        get_cur_key();
        if(_cur_key == CTRL_C) _program_state = STOP;
        control_state_machine();

        CMD::CLEAR_FROME(Y_HEADER);
        display_state_machine();
    }
}   