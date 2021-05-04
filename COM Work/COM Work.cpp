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

int main() {
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


        initscr();
        while (true)
        {
            lenRead = com.bytesToRead();
            if (lenRead >= 528)
            {
                com.read(data, lenRead);
                //cout << "CRC:" << check_crc16(data, 0, 526, &data[526], &data[527]) << endl;

                printw("CRC: %b", check_crc16(data, 0, 526, &data[526], &data[527]));

                uint8_t data1[528] = { *data };

                P_State *ps= new P_State;
                //ps.Parse(data);

                //ps = (P_State*)data;

                memcpy(ps, data, sizeof(P_State));

                //cout << (uint16_t)*ps->ver << endl;

                local_win = newwin(15, 30, 15, 50);
                box(local_win, 0, 0);
                mvwprintw(local_win, 2, 2, "Version %02x%02x", ps->ver[0], ps->ver[1]);
                mvwprintw(local_win, 3, 2, "Name1: ");
                for (size_t i = 0; ps->Name1[i] != '/0'; i++)
                {
                    wprintw(local_win, "%02x", ps->Name1[i]);
                }
                /*for (; ps->Name1 != '\0'; ++(*ps->Name1))
                {
                    wprintw(local_win, "%02x", *ps->Name1);
                    //printf("%02x", *ps->Name1);
                }*/
                //mvwprintw(local_win, 3, 2, "Name1: %02x", *ps->Name1);
                mvwprintw(local_win, 4, 2, "Name2: %02x", *ps->Name2);
                wrefresh(local_win);

                //cout << bitset<sizeof(uint8_t) * 8>((uint8_t)data[0]) << endl;
                //cout << hex << (int)(uint8_t)data[0] << endl;
                r++;
                if (r > 5)
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
                    cout << com.write(dw, 528) << endl;
                    r = 0;
                }


            }

            //system("pause");
            //Sleep(1000);
        }
    }


    endwin();
    system("pause");
    return 0;
}