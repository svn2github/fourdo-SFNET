#ifndef _INC_ARMREGISTERS
#define _INC_ARMREGISTERS

#include "types.h"

// This structure stores all the registers
typedef struct
{
	uint32 USER[16];
	uint32 CASH[7];
    uint32 SVC[2];
    uint32 ABT[2];
    uint32 FIQ[7];
    uint32 IRQ[2];
    uint32 UND[2];
    uint32 SPSR[6];
	uint32 CPSR;
	
	bool nFIQ; //������� ����������, ��������������� ������� ������������
	bool SecondROM;	//�������� ��� (��� � �����)	
	bool MAS_Access_Exept;	//�������� ��� ���������� ������� � ������
	int CYCLES;	//����� ������� �����			
}ARMRegisters;

#endif