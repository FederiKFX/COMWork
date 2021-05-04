#pragma once
#include <cstdint>
#include <iostream>

struct P_State
{
	uint8_t ID;
	uint8_t ver[2];
	char Name1[13];
	char Name2[13];
	uint8_t un[2];
	uint8_t stage;
	uint8_t errors[2];
	uint8_t un1[492];
	uint8_t CRC[2];


	/*void Parse(uint8_t* data)
	{
		ID = data[0];
		ver = (uint16_t*)(data+1);
		Name1 = (char*)(data + 3);
		Name2 = (char *)(data + 16);
		stage = data[31];
		errors = (uint16_t*)(data + 32);

		Name2[13] = '\0';
		Name1[13] = '\0';


		std::cout << Name1;
		std::cout << Name2;
	}*/
};

struct P_UID
{
	uint8_t ID;
	uint8_t sizeUID;
	uint8_t sizeATS;
};