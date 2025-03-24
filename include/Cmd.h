#ifndef _CMD_H_
#define _CMD_H_

#include <string>
#include <stdint.h>
#include <windows.h>
#include <thread>

class CMD{
public: 
    enum LANGUAGE{
        EN, RU,
        LANGUAGE_SIZE
    };

    enum COLOR{
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        PURPLE,
        WHITE_BLUE,
        BASE_COLOR
    };

    enum FORMATTING{
        BOLD = 1, // жирный
        DIM, // тусклый
        ITALICS, // курсив
        UNDERLINE, // подчеркнутый
        INVERSION = 7, 
        CROSSED = 9,  // зачеркнутый
        BASE_FORMATTING = 0
    };

    static void PRINT(const std::string mes, const COLOR color = BASE_COLOR, 
        const FORMATTING format1 = BASE_FORMATTING, const FORMATTING format2 = BASE_FORMATTING, const FORMATTING format3 = BASE_FORMATTING){
        uint8_t PRINT_COLOR = 30 + static_cast<uint8_t>(color);
        uint8_t PRINT_FORMAT_1 = static_cast<uint8_t>(format1);
        uint8_t PRINT_FORMAT_2 = static_cast<uint8_t>(format2);
        uint8_t PRINT_FORMAT_3 = static_cast<uint8_t>(format3);

        if(format3 == BASE_FORMATTING) PRINT_FORMAT_3 = PRINT_FORMAT_1;
        if(format2 == BASE_FORMATTING) PRINT_FORMAT_2 = PRINT_FORMAT_1;

        printf("\033[%d;%d;%d;%dm%s\033[0m", PRINT_FORMAT_1 , PRINT_FORMAT_2, PRINT_FORMAT_3, PRINT_COLOR, mes.c_str());
    }

    static void PRINT_N_SPACES(uint8_t n_spaces, const COLOR color = BASE_COLOR, 
        const FORMATTING format1 = BASE_FORMATTING, const FORMATTING format2 = BASE_FORMATTING, const FORMATTING format3 = BASE_FORMATTING){
        
        uint8_t PRINT_COLOR = 30 + static_cast<uint8_t>(color);
        uint8_t PRINT_FORMAT_1 = static_cast<uint8_t>(format1);
        uint8_t PRINT_FORMAT_2 = static_cast<uint8_t>(format2);
        uint8_t PRINT_FORMAT_3 = static_cast<uint8_t>(format3);

        if(format3 == BASE_FORMATTING) PRINT_FORMAT_3 = PRINT_FORMAT_1;
        if(format2 == BASE_FORMATTING) PRINT_FORMAT_2 = PRINT_FORMAT_1;

        std::string big_space = "";
        for(uint8_t i = 0; i < n_spaces; i++){
            big_space += " ";
        }

        printf("\033[%d;%d;%d;%dm%s\033[0m", PRINT_FORMAT_1 , PRINT_FORMAT_2, PRINT_FORMAT_3, PRINT_COLOR, big_space.c_str());
    }

    static void GOTO(const uint16_t x, const uint16_t y){
        printf("\033[%d;%dH", y + 1, x + 1);
    }
        
    static void CLEAR_ALL(){
        printf("\033[2J\033[H");
    }

    static void CLEAR_FROME(uint8_t y){
        GOTO(0, y);
        printf("\033[0J\033[H");
        
        fflush(stdout);
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    static void SET_LANGUAGE(LANGUAGE language){
        _language = language;
    }

    static void SET_STANDART(){
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001); 
        
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        
        CLEAR_ALL();
    }

    static LANGUAGE GET_LANGUAGE(){
        return _language;
    }

    static LANGUAGE _language; 
};
            
#endif // !_CMD_H_