#pragma once
#include <cstdint>
#include <iostream>

struct P_State
{
	uint8_t* ID = new uint8_t;
	uint16_t *ver = new uint16_t;
	unsigned char *Name1 = new unsigned char[14];
	unsigned char *Name2= new unsigned char[14];
	//uint8_t *un = new uint8_t[2];
	uint8_t *stage = new uint8_t;
	uint16_t *errors = new uint16_t;
	//uint8_t un1[492];
	uint16_t *CRC = new uint16_t;


	void Parse(uint8_t* data)
	{

		//memcpy(ps, data, sizeof(P_State));


		memcpy(ID, data, sizeof(uint8_t));
		data += sizeof(uint8_t);

		//ver = reinterpret_cast<uint16_t*>(data);

		memcpy((uint8_t*)ver+1, data, sizeof(uint8_t));
		memcpy(ver, data+1, sizeof(uint8_t));
		data += sizeof(uint16_t);

		memcpy(Name1, data, 13);
		Name1[13] = '\0';
		data += 13;

		memcpy(Name2, data, 13);
		Name2[13] = '\0';
		data += 13;

		data += 2;
		memcpy(stage, data, sizeof(uint8_t));
		data += sizeof(uint8_t);

		memcpy((uint8_t*)errors + 1, data, sizeof(uint8_t));
		memcpy(errors, data + 1, sizeof(uint8_t));
		data += sizeof(uint16_t);
		data += 492;

		memcpy((uint8_t*)CRC + 1, data, sizeof(uint8_t));
		memcpy(CRC, data + 1, sizeof(uint8_t));
		data += sizeof(uint16_t);

		/*memcpy(CRC, data, sizeof(uint16_t));
		data += sizeof(uint16_t);*/

		/*memcpy(&CRC[1], data, sizeof(uint8_t));
		data += sizeof(uint8_t);*/
		/*ID = data[0];
		ver = (uint16_t*)(data+1);
		Name1 = (char*)(data + 3);
		Name2 = (char *)(data + 16);
		stage = data[31];
		errors = (uint16_t*)(data + 32);*/

		//Name2[13] = '\0';
		//Name1[13] = '\0';


		//std::cout << Name1;
		//std::cout << Name2;
	}
};

struct P_UID
{
	uint8_t ID;
	uint8_t sizeUID;
	uint8_t sizeATS;
};

uint8_t foto1[] = { //-- width: 84, height: 48
0x40,
0x0,0x0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x03, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x03, 0x0c, 0x00, 0x00,
0x00, 0x00, 0xff, 0x7f, 0x00, 0x00,
0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1c, 0x08, 0x00, 0x00,
0x00, 0x00, 0x3e, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x73, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0xc3, 0x0c, 0x00, 0x00,
0x00, 0x00, 0xc3, 0x07, 0x00, 0x00,
0x00, 0x00, 0x83, 0x03, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xe0, 0x01, 0x00, 0x00,
0x00, 0x00, 0xe3, 0x07, 0x00, 0x00,
0x00, 0x00, 0x63, 0x06, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x63, 0x0c, 0x00, 0x00,
0x00, 0x00, 0x66, 0x07, 0x00, 0x00,
0x00, 0x00, 0xfc, 0x03, 0x00, 0x00,
0x00, 0x00, 0xf8, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0xff, 0xff, 0x01, 0x00,
0x00, 0x00, 0xff, 0xff, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x80, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,










0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

uint8_t foto[] = { //-- width: 84, height: 48
	0x40,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,
0x1,0x1,0x1,0xff,0xff,0x1,0x1,0x1,0x1,0x1,0xc0,0xe0,0x30,0x30,0x30,0x30,
0x60,0xe0,0x80,0x0,0x0,0xc0,0xe0,0x30,0x30,0x30,0x30,0x30,0x10,0x0,0x30,0x30,
0xfe,0xfe,0x30,0x30,0x30,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0x0,0x0,0x0,0x0,0x1f,0x3f,0x66,
0xc6,0xc6,0xc6,0xc6,0xc6,0xc7,0x7,0x0,0x0,0xc1,0xc3,0xc3,0xc6,0xc6,0xce,0x7c,
0x38,0x0,0x0,0x0,0x7f,0xff,0xc0,0xc0,0xc0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};