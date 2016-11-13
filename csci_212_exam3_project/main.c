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
	char buffer[12];           // Buffer for data address
	char *reg32 = "eax";	   // Register name
	char *imm32 = "35003500";  // Immediate 32-bit value (hex)
	unsigned int mem32 = 0;    // Memory 32-bit value

	// Zero out machineCode array
	memset(machineCode, 0, sizeof(machineCode));

	// Set up instruction for reg to reg
	instruction.mnemonic = mov;
	instruction.op1 = op1;
	instruction.op2 = reg32;
	printf("reg32 operand would look something like this: %s\n", reg32);

	// Get the machine code
	getMachineCode(&instruction, machineCode, &count);

	// Print results
	printf("Machine code: ");
	for (int i = 0; i < count; i++)
		printf("%02x ", machineCode[i]);
	printf("\n");

	// Set up op2 for mem32
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "[%08x]", &mem32);
	printf("mem32 operand would look like this: %s\n", buffer);

	// mem32 to reg instruction
	instruction.op2 = buffer;
	memset(machineCode, 0, sizeof(machineCode));
	count = 0;
	getMachineCode(&instruction, machineCode, &count);

	// imm32 to reg instruction
	memset(machineCode, 0, sizeof(machineCode));
	count = 0;
	instruction.op2 = imm32;
	getMachineCode(&instruction, machineCode, &count);
	printf("imm32 operand would look like this: %s\n", imm32);

	printf("Hit return to exit...\n");
	int ret = scanf("");  // Need this so scanf gets linked

	return 0;
}