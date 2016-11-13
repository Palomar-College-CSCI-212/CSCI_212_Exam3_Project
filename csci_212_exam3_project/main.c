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
	char buffer[12];

	char *reg32 = "eax";		// Register name
	char *imm32 = "35003500";  // Immediate 32-bit value (hex)
	unsigned int mem32 = 0;    // Memory 32-bit value

	memset(machineCode, 0, sizeof(machineCode));
	instruction.mnemonic = mov;
	instruction.op1 = op1;
	instruction.op2 = op2;

	getMachineCode(&instruction, machineCode, &count);

	printf("Machine code: ");
	for (int i = 0; i < count; i++)
		printf("%02x ", machineCode[i]);
	printf("\n");

	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "[%08x]", &mem32);
	instruction.op2 = buffer;
	printf("mem32 operand would look like this: %s\n", buffer);

	memset(machineCode, 0, sizeof(machineCode));
	count = 0;
	getMachineCode(&instruction, machineCode, &count);

	instruction.op2 = reg32;
	memset(machineCode, 0, sizeof(machineCode));
	count = 0;
	getMachineCode(&instruction, machineCode, &count);

	return 0;
}