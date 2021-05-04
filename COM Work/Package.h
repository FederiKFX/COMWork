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