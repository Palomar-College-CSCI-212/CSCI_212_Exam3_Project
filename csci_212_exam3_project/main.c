// Module Name : main.c
// Description: Main module, tests getMachineCode assembly function
// Date: 11/13/2016
// Author: Lem Davis

#include <stdio.h>
#include <string.h>

//-------------------------------------------------
// Structure used to contain instruction passed to getMachineCode
struct inst {
	char *mnemonic;
	char *op1;
	char *op2;
};

// Prototype
void getMachineCode(struct inst *instPtr, unsigned char*, int*);

//-------------------------------------------------
int main()
{
	struct inst instruction;
	unsigned char machineCode[64];
	int count = 0;
	char *mov = "mov";
	char *op1 = "ebx";
	char *op2 = "32h";

	memset(machineCode, 0, 64);
	instruction.mnemonic = mov;
	instruction.op1 = op1;
	instruction.op2 = op2;

	getMachineCode(&instruction, machineCode, &count);

	printf("Machine code: ");
	for (int i = 0; i < count; i++)
		printf("%02x ", machineCode[i]);
	printf("\n");

	return 0;
}