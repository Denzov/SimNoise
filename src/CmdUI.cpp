#include "../include/CmdUI.h"

CMD::LANGUAGE CMD::_language = EN;

const std::string TextUI::PLEASE_PRINT_KEY[CMD::LANGUAGE_SIZE]{
    {"-----PRINT ANY KEY-----"},
    {"----НАЖМИТЕ КЛАВИШУ----"}
};

const std::string TextUI::MAIN_MENU_CHOOSE[CMD::LANGUAGE_SIZE][MAIN_MENU_CHOOSE_STATES_SIZE]{
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

const std::string TextUI::CONFIG_CHOOSE[CONFIG_CHOOSE_STATES_SIZE]{
    std::string(TEXT_CONFIG_SAMPLES_SIZE),
    std::string(TEXT_CONFIG_SIMULATION_TYPE),
    std::string(TEXT_CONFIG_ERROR_CHANGE),
    std::string(TEXT_CONFIG_ENCODER_BLOCK_SIZE),
    std::string(TEXT_CONFIG_DECODER_BLOCK_SIZE)
};

const std::string TextUI::CONFIG_SIM_TYPES[Config::SIM_TYPE::SIM_TYPE_SIZE]{ 
    "BIT_BY_BIT", "BYTE_BY_BYTE", "FROM_LOADING"    
};

const std::string TextUI::HELP_PAGE[CMD::LANGUAGE_SIZE][TextUI::HELP_STRINGS_SIZE]{
    {"CONTROL:", "\tCTRL+C - CLOSE PROGRAM", "\tUP/DOWN ARROWS - MOVE YOUR CHOOSE", "\tENTER | RIGHT/LEFT ARROWS - CHOOSE/CANCEL",
    "", "TO SET AN ATTRIBUTE IN A CONFIG, YOU MUST WRITE THE ATTRIBUTE NAME", "\tIN THE CONFIG ITSELF, STARTING WITH A DOT, AND THEN IMMEDIATELY SET ITS VALUE VIA \"=\"",
    "", "ATTRIBUTES OF CONFIG:", "\t.SAMPLES_SIZE=[int, value is between 1 and 2^63 inclusive]",
    "\t.SIM_TYPE=[int, value is between 1 and 2^63 inclusive]", "\t.ERROR_CHANGE=[float, value is between 0 and 1 inclusive]", 
    "\t.ENCODER_BLOCK_SIZE=[int, value is between 1 and 2^63 inclusive]", "\t.DECODER_BLOCK_SIZE=[int, value is between 1 and 2^63 inclusive]",
    "", "THE SYM_TYPE ATTRIBUTE IS DIVIDED INTO NULL, FIRST AND SECOND:", 
    "\t- NULL IS A SIMULATION BIT-BY-BIT", "\t- FIRST IS A SIMULATION BYTE-BY-BYTE", "\t- SECOND IS SIMULATION WITH YOUR DATA LOADING"}, 

    {"УПРАВЛЕНИЕ:", "\tCTRL+C - ЗАВЕРШИТЬ ПРОГРАММУ", "\tСТРЕЛКИ ВВЕРХ/ВНИЗ - ПЕРЕМЕЩАТЬ ВЫБОР", "\tENTER | СТРЕЛКИ ПРАВАЯ/ЛЕВАЯ - ВЫБРАТЬ/ОТМЕНИТЬ ВЫБОР",
    "", "ЧТОБЫ УСТАНОВИТЬ АТРИБУТ В КОНФИГ-ФАЙЛЕ НЕОБХОДИМО В САМОМ ФАЙЛЕ \"CONFIG\"", "\tПРОПИСАТЬ, НАЧИНАЯ С ТОЧКИ, НАЗВАНИЕ АТРИБУТА, ПОТОМ СРАЗУ ЖЕ ВЫСТАВИТЬ ЕГО ЗНАЧЕНИЕ ЧЕРЕЗ \"=\"",
    "", "АТРИБУТЫ КОНФИГ-ФАЙЛА:", "\t.SAMPLES_SIZE=[int, значение между 1 и 2^63 включительно]",
    "\t.SIM_TYPE=[int, значение между 1 и 2^63 включительно]", "\t.ERROR_CHANGE=[float, значение между 0 и 1 включительно]", 
    "\t.ENCODER_BLOCK_SIZE=[int, значение между 1 и 2^63 включительно]", "\t.DECODER_BLOCK_SIZE=[int, значение между 1 и 2^63 включительно]",
    "", "АТРИБУТ SYM_TYPE РАЗДЕЛЕН НА НУЛЕВОЙ, ПЕРВЫЙ И ВТОРОЙ:",
    "\t- ПЕРВЫЙ - СИМУЛЯЦИЯ БИТ ЗА БИТОМ", "\t- ВТОРОЙ - СИМУЛЯЦИЯ БАЙТ ЗА БАЙТОМ", "\t- ТРЕТЬЯ - СИМУЛЯЦИЯ С ПОДГРУЗКОЙ ВАШИХ ДАННЫХ"}
};  

void CmdUI::init(){
    CMD::SET_STANDART();

    _simulator.SetConfig(_linker.getConfig());
    _simulator.SetDecoder(_linker.getDecoder());
    _simulator.SetEncoder(_linker.getEncoder());
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

    for(uint8_t i = 0; i < MAIN_MENU_CHOOSE_STATES_SIZE; i++){
        CMD::GOTO(0, Y_AFTER_HEADER + i);

        if(_main_menu_choose_state == static_cast<MAIN_MENU_CHOOSE_STATE>(i)){
            CMD::PRINT("  |->", CMD::GREEN, CMD::BOLD);
            CMD::PRINT(TextUI::MAIN_MENU_CHOOSE[CMD::GET_LANGUAGE()][i], CMD::GREEN, CMD::UNDERLINE);
            
            CMD::GOTO(X_AFTER_MENU_TABLE - 1, Y_AFTER_HEADER + i);
            CMD::PRINT("|", CMD::PURPLE, CMD::BOLD);
        }
        else{
            CMD::PRINT("  |", CMD::PURPLE, CMD::BOLD);
            CMD::PRINT(TextUI::MAIN_MENU_CHOOSE[CMD::GET_LANGUAGE()][i], CMD::BASE_COLOR, CMD::BOLD);

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
    if(_linker.isLoadedUserCode()){
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

    for(uint8_t shift = 0; shift < CONFIG_CHOOSE_STATES_SIZE; shift++){
        CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER + shift + 1);

        if(_config_choose_state == shift){
            CMD::PRINT(TextUI::CONFIG_CHOOSE[shift], CMD::GREEN, CMD::BOLD);
        }
        else{
            CMD::PRINT(TextUI::CONFIG_CHOOSE[shift], CMD::BASE_COLOR, CMD::BOLD);
        }
        
        std::string str_attribute_value = "";
        
        switch (static_cast<CONFIG_CHOOSE_STATE>(shift))
        {
        case CONFIG_CHOOSE_STATE::SAMPLES_SIZE:
            str_attribute_value = std::to_string(_linker.getConfig()->samples_size);
            
            if(_linker.isValidSamplesSize()){
                CMD::PRINT(str_attribute_value, CMD::YELLOW, CMD::BOLD);
            }
            else{
                CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
            }  
            break;

        case CONFIG_CHOOSE_STATE::SIM_TYPE:
            str_attribute_value = TextUI::CONFIG_SIM_TYPES[_linker.getConfig()->simulation_type];
            
            if(_linker.isValidSimulationType()){
                CMD::PRINT(str_attribute_value, CMD::YELLOW, CMD::BOLD);
            }
            else{
                CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
            }  
            break;
        
        case CONFIG_CHOOSE_STATE::ERROR_CHANGE:
            str_attribute_value = std::to_string(_linker.getConfig()->error_change);
            
            if(_linker.isValidErrorChange()){
                CMD::PRINT(str_attribute_value, CMD::YELLOW, CMD::BOLD);
            }
            else{
                CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
            }  
            break;

        case CONFIG_CHOOSE_STATE::ENCODER_BLOCK_SIZE:
            str_attribute_value = std::to_string(_linker.getConfig()->encoder_block_size);

            if(_linker.isValidEncoderBlockSize()){
                CMD::PRINT(str_attribute_value, CMD::YELLOW, CMD::BOLD);
            }
            else{
                CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
            }  
            break;

        case CONFIG_CHOOSE_STATE::DECODER_BLOCK_SIZE:
            str_attribute_value = std::to_string(_linker.getConfig()->decoder_block_size);

            if(_linker.isValidDecoderBlockSize()){
                CMD::PRINT(str_attribute_value, CMD::YELLOW, CMD::BOLD);
            }
            else{
                CMD::PRINT("INVALID_VALUE", CMD::RED, CMD::BOLD);
            }  
            break;
        }
    }
}

void CmdUI::print_help_page(){
    CMD::GOTO(X_AFTER_MENU_TABLE, Y_HEADER);
    CMD::PRINT_N_SPACES(X_AFTER_CHOSED - X_AFTER_MENU_TABLE, CMD::PURPLE, CMD::BOLD, CMD::UNDERLINE);

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

void CmdUI::config_input_handler(){
    CMD::GOTO(X_AFTER_MENU_TABLE + strlen(TextUI::CONFIG_CHOOSE[_config_choose_state].c_str()), Y_HEADER + 1 + _config_choose_state);
    CMD::PRINT_N_SPACES(20);
    CMD::GOTO(X_AFTER_MENU_TABLE + strlen(TextUI::CONFIG_CHOOSE[_config_choose_state].c_str()), Y_HEADER + 1 + _config_choose_state);
    
    
    std::string input_string = "";
    std::getline(std::cin, input_string);
    try
    {
        if(input_string != ""){
            switch (_config_choose_state){
                case CONFIG_CHOOSE_STATE::SAMPLES_SIZE: 
                if(std::stoi(input_string) >= SAMPLES_SIZE_MIN_VALUE){
                    _linker.setSamplesSize(std::stoi(input_string));
                }
                break;

            case CONFIG_CHOOSE_STATE::SIM_TYPE:
                if(std::stoi(input_string) >= SIM_TYPE_MIN_VALUE && std::stoi(input_string) <= SIM_TYPE_MAX_VALUE){
                    _linker.setSimulationType(std::stoi(input_string));
                }
                break;

            case CONFIG_CHOOSE_STATE::ERROR_CHANGE:
                if(std::stoi(input_string) >= ERROR_CHANGE_MIN_VALUE && std::stoi(input_string) <= ERROR_CHANGE_MAX_VALUE){
                    _linker.setErrorChange(std::stof(input_string));
                }
                break;

            case CONFIG_CHOOSE_STATE::ENCODER_BLOCK_SIZE:
                if(std::stoi(input_string) >= ENCODER_BLOCK_SIZE_MIN_VALUE){
                    _linker.setEncoderBlockSize(std::stoi(input_string));
                }
                break;

            case CONFIG_CHOOSE_STATE::DECODER_BLOCK_SIZE:
                if(std::stoi(input_string) >= DECODER_BLOCK_SIZE_MIN_VALUE){
                    _linker.setDecoderBlockSize(std::stoi(input_string));
                }
                break;
            }
        }
    }
    catch(...){}
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
            _main_menu_choose_state = static_cast<MAIN_MENU_CHOOSE_STATE>((_main_menu_choose_state + MAIN_MENU_CHOOSE_STATES_SIZE - 1) % MAIN_MENU_CHOOSE_STATES_SIZE);
            break;
        
        case TAB:
        case DOWN:
            _main_menu_choose_state = static_cast<MAIN_MENU_CHOOSE_STATE>((_main_menu_choose_state + 1) % MAIN_MENU_CHOOSE_STATES_SIZE);
            break;
        
        case ENTER:
        case RIGHT:
        case CTRL_TAB:
        switch (_main_menu_choose_state)
            {
            case START:
                _program_state = RUN;                    

                _linker.loadStandartFiles();
                
                _linker.passUserFuncs();
                _linker.passConfig();

                _simulator.load_simulated_data();
                break;
            
            case CONFIG:
                _program_state = CONFIG_PAGE;

                _linker.loadStandartFiles();
                    
                _linker.passUserFuncs();
                _linker.passConfig();
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
        case CTRL_TAB:
            _main_menu_choose_state = MAIN_MENU_CHOOSE_STATE::START;
            _program_state = PROGRAM_STATE::CHOOSE;
            break;
        }
        break;
    
    case PROGRAM_STATE::CONFIG_PAGE:
        switch(_cur_key){    
        case ENTER:
        case LEFT:
            _main_menu_choose_state = MAIN_MENU_CHOOSE_STATE::CONFIG;
            _program_state = PROGRAM_STATE::CHOOSE;
            break;

        case UP:
            _config_choose_state = static_cast<CONFIG_CHOOSE_STATE>((_config_choose_state + CONFIG_CHOOSE_STATES_SIZE - 1) % CONFIG_CHOOSE_STATES_SIZE);
            break;

        case TAB:
        case DOWN:
            _config_choose_state = static_cast<CONFIG_CHOOSE_STATE>((_config_choose_state + 1) % CONFIG_CHOOSE_STATES_SIZE);
            break;

        case RIGHT:
        case CTRL_TAB:
            config_input_handler();
            break;
        }
        break;

    case PROGRAM_STATE::HELP_PAGE:
        switch (_cur_key)
        {
        case ENTER:
        case LEFT:
        case CTRL_TAB:
            _main_menu_choose_state = MAIN_MENU_CHOOSE_STATE::HELP;
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

        CMD::GOTO(10, 20);
        CMD::PRINT("data\n");

        _simulator.print_simulated_data();

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