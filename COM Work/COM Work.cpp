﻿#define NCURSES_MOUSE_VERSION


#include <iostream>
#include "xserial.hpp"
#include <fstream>
#include <bitset>
#include <iomanip>
#include "Package.h"
#include <curses.h>

using namespace std;

void crc16(uint8_t* pData, int length, uint8_t* crc1, uint8_t* crc0)
{
    uint8_t i;
    uint16_t wCrc = 0xffff;
    while (length--) {
        wCrc ^= *(uint8_t*)pData++ << 8;
        for (i = 0; i < 8; i++)
            wCrc = wCrc & 0x8000 ? (wCrc << 1) ^ 0x1021 : wCrc << 1;
    }
    *crc1 = (wCrc >> 8) & 0xff;
    *crc0 = wCrc & 0xff;
}

//Функция фозвращает значение <>0 если CRC правильная. Параметры функции:
// *d1 - Указатель на буфер для которого вычисляется CRC
// s1 - Позиция в *d1, начиная с которой производится вычисление
// c1 - Число членов в массиве *d1, для которых производится вычисление
// *crc1:*crc0 - До вызова функции - указатель на CRC с которой требуется сравнить
//вычисление. По данному указателю функция возвращает новое CRC.
bool check_crc16(uint8_t* d1, uint16_t s1, uint16_t c1, uint8_t* crc1, uint8_t* crc0)
{
    uint8_t a3;
    uint16_t a1, a2, crc2, a4;
    crc2 = 0xFFFF;
    a4 = ((*crc1) << 8) & 0xFF00;
    a4 = a4 | ((*crc0) & 0xFF);
    for (a1 = 0; a1 < c1; a1++)
    {
        a2 = *(d1 + a1 + s1);
        crc2 ^= a2 << 8;
        for (a3 = 0; a3 < 8; a3++)
        {
            crc2 = crc2 & 0x8000 ? (crc2 << 1) ^ 0x1021 : crc2 << 1;
        }
    }
    *crc1 = (crc2 >> 8) & 0xFF;
    *crc0 = crc2 & 0xFF;
    if (a4 == crc2) { return 1; }
    else { return 0; }
}

#define WIDTH 40
#define HEIGHT 10 

int startx = 0;
int starty = 0;

const char* choices[] = { "Choice 1",
            "Choice 2",
            "Choice 3",
            "Choice 4",
            "Exit",
};

int n_choices = sizeof(choices) / sizeof(char*);

void print_menu(WINDOW* menu_win, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

/* Report the choice according to mouse position */
void report_choice(int mouse_x, int mouse_y, int* p_choice)
{
    int i, j, choice;

    i = startx + 2;
    j = starty + 3;

    for (choice = 0; choice < n_choices; ++choice)
        if (mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice]))
        {
            if (choice == n_choices - 1)
                *p_choice = -1;
            else
                *p_choice = choice + 1;
            break;
        }
}
#include <process.h>

int y, x;
static unsigned __stdcall ThreadFunc(void* num)
{
    xserial::ComPort com(5, 115200, xserial::ComPort::COM_PORT_NOPARITY, 8, xserial::ComPort::COM_PORT_ONESTOPBIT);
    if (!com.getStateComPort()) { // Если порт не открылся
        cout << "Error: com port is not open!" << endl;
    }
    else
    {
        WINDOW* local_win;

        uint8_t* data = new uint8_t[528];

        int lenRead;
        int r = 0, m = 1;
        while (true)
        {

            lenRead = com.bytesToRead();
            if (lenRead >= 528)
            {
                com.read(data, lenRead);
                uint8_t data1[528] = { *data };
                P_State ps;// = new P_State;
                ps.Parse(data);

                resize_term(y, x);
                local_win = newwin(8, 37, 0, x - 37);
                box(local_win, 0, 0);
                mvwprintw(local_win, 1, 2, "Version: %04x", *ps.ver);
                mvwprintw(local_win, 2, 2, "Name1: ");
                for (size_t i = 0; ps.Name1[i] != '\0'; i++)
                {
                    wprintw(local_win, "%02x", ps.Name1[i]);
                }

                mvwprintw(local_win, 3, 2, "Name2: ");
                for (size_t i = 0; ps.Name1[i] != '\0'; i++)
                {
                    wprintw(local_win, "%02x", ps.Name2[i]);
                }
                mvwprintw(local_win, 4, 2, "Stage: %02x", *ps.stage);
                mvwprintw(local_win, 5, 2, "Errors: %04x", *ps.errors);
                mvwprintw(local_win, 6, 2, "CRC: %04x", *ps.CRC);
                wrefresh(local_win);


                uint8_t dw[528] = { 0 };
                for (size_t i = 1; i < 507; i++)
                {
                    i % 2 == 0 ? dw[i] = 0x69 : dw[i] = 0xa7;
                }
                dw[0] = 0x40;
                dw[1] = 0xff;

                crc16(dw, 526, &dw[526], &dw[527]);

                com.write(dw, 528);
            }
        }
    }
}

int main() {
    xserial::ComPort com(5, 115200, xserial::ComPort::COM_PORT_NOPARITY, 8, xserial::ComPort::COM_PORT_ONESTOPBIT);
    if (!com.getStateComPort()) { // Если порт не открылся
        cout << "Error: com port is not open!" << endl;
    }
    else
    {
        MEVENT event;
        WINDOW* menu_win;

        int ch = 0, choice = 0;
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        mmask_t old;
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);

        /* Try to put the window in the middle of screen */
        startx = (80 - WIDTH) / 2;
        starty = (24 - HEIGHT) / 2;

        printw("ПРИВЕТ, МИР!\n");
        wrefresh(stdscr);

        attron(A_REVERSE);
        mvprintw(23, 1, "Вихд Click on Exit to quit (Works best in a virtual console)");
        refresh();
        attroff(A_REVERSE);

        /* Print the menu for the first time */
        menu_win = newwin(HEIGHT, WIDTH, starty, startx);
        print_menu(menu_win, 1);




        WINDOW* local_win;

        uint8_t* data = new uint8_t[528];

        int lenRead;
        int r = 0, m = 1;


        initscr();

        getmaxyx(stdscr, y, x);

        HANDLE hThread = NULL;
        unsigned int ThreadId = NULL;
        DWORD ThreadExit = NULL;
        hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, NULL, &ThreadId);

        for (int i = 0; i < 0x03; i++)
        {
            time_t current_time;
            time(&current_time);
            f << "Main ThreadId: " << GetCurrentThreadId() << ". Time: " << ctime(&current_time) << endl;// запис у файл
            Sleep(2);
        }
        SuspendThread(hThread);
        for (int i = 0; i < 0x03; i++)
        {
            time_t current_time;
            time(&current_time);
            f << "Main ThreadId: " << GetCurrentThreadId() << ". Time: " << ctime(&current_time) << endl;// запис у файл
            Sleep(2);
        }

        while (true)
        {
            ch = getch();
            if (ch == KEY_MOUSE) {
                if (getmouse(&event) == OK)
                {
                    if (event.bstate & BUTTON1_CLICKED) {
                        report_choice(event.x + 1, event.y + 1, &choice);
                        if (choice == -1) //Exit chosen
                            goto end;
                        mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
                        refresh();
                    }
                }
                print_menu(menu_win, choice);
                //break;
            }

            lenRead = com.bytesToRead();
            if (lenRead >= 528)
            {
                com.read(data, lenRead);
                //cout << "CRC:" << check_crc16(data, 0, 526, &data[526], &data[527]) << endl;

                //printw("CRC: %b", check_crc16(data, 0, 526, &data[526], &data[527]));

                uint8_t data1[528] = { *data };

                P_State ps;// = new P_State;
                ps.Parse(data);

                //ps = (P_State*)data;

                //memcpy(ps, data, sizeof(P_State));

                //cout << (uint16_t)*ps->ver << endl;

                resize_term(y, x);
                local_win = newwin(8, 37, 0, x - 37);
                box(local_win, 0, 0);
                mvwprintw(local_win, 1, 2, "Version: %04x", *ps.ver);
                mvwprintw(local_win, 2, 2, "Name1: ");
                for (size_t i = 0; ps.Name1[i] != '\0'; i++)
                {
                    wprintw(local_win, "%02x", ps.Name1[i]);
                }

                mvwprintw(local_win, 3, 2, "Name2: ");
                for (size_t i = 0; ps.Name1[i] != '\0'; i++)
                {
                    wprintw(local_win, "%02x", ps.Name2[i]);
                }
                mvwprintw(local_win, 4, 2, "Stage: %02x", *ps.stage);
                mvwprintw(local_win, 5, 2, "Errors: %04x", *ps.errors);
                mvwprintw(local_win, 6, 2, "CRC: %04x", *ps.CRC);
                //mvwprintw(local_win, 7, 2, "CRC: %02x%02x", data[526], data[527]);
                wrefresh(local_win);

                //cout << bitset<sizeof(uint8_t) * 8>((uint8_t)data[0]) << endl;
                //cout << hex << (int)(uint8_t)data[0] << endl;
                r++;
                //if (r > 5)
                {
                    uint8_t dw[528] = { 0 };
                    for (size_t i = 1; i < 507; i++)
                    {
                        i % 2 == 0 ? dw[i] = 0x69 : dw[i] = 0xa7;
                    }
                    dw[0] = 0x40;
                    dw[1] = 0xff;
                    //dw[2] = 3;

                    crc16(dw, 526, &dw[526], &dw[527]);

                    m++;
                    com.write(dw, 528);
                    r = 0;
                }


            }

            //system("pause");
            //Sleep(1000);
        }

    }

end:
    endwin();
    return 0;
}