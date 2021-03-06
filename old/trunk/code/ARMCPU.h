/////////////////////////////////////////////////////////////////////////////
//
// Phoenix ARM60-emulator source code 
//(from 2007,  used for FreeDO Project - www.freedo.org)
// Written by Maxim L. Grishin ( homepage - http://altmer.arts-union.ru )
//.desrever sthgir llA ;)
//
// Adapted for FourDO by Johnny... many, many thanks to Altmer!
//
// This replaces my slower ARM emulator that never saw a full release. :(
//
/////////////////////////////////////////////////////////////////////////////
 
#ifndef _INC_ARMCPU
#define _INC_ARMCPU

#include <math.h>
#include "types.h"
#include "ARMRegisters.h"
#include "DMA.hpp"

#ifdef GENRE_UNIX
	#define __fastcall __attribute__((fastcall)) 
#endif

class ARMCPU
{
public:
	ARMCPU();
	~ARMCPU();

    DMA*            DMA;
	ARMRegisters    ARM;

	unsigned int GetFIQ();
	void __fastcall SetFIQ( void );
	void SetPC( unsigned int addr );

	void Reset();

	int __fastcall Execute( unsigned int MCLKs );
	void SetCPSR( unsigned int a );
	
protected:
	__inline bool ALU_Exec(uint32 inst, uint8 opc, uint32 op1, uint32 op2, uint32 *Rd);
	void inline __fastcall decode_swi(unsigned int i);

	unsigned int __fastcall calcbits(unsigned int num);
	__inline uint32 SHIFT_NSC(uint32 value, uint8 shift, uint8 type);
	__inline uint32 SHIFT_SC(uint32 value, uint8 shift, uint8 type);
	__inline uint32 ROTR(uint32 op, uint32 val);
	__inline bool SWAP(uint32 cmd);
	
	__inline void SET_CV_sub(uint32 rd, uint32 op1, uint32 op2);
	__inline void SET_CV(uint32 rd, uint32 op1, uint32 op2);
	__inline void SETN( bool a );
	__inline void SETZ( bool a );
	__inline void SETC( bool a );
	__inline void SETV( bool a );
	__inline void SETI( bool a );
	__inline void SETF( bool a );
	__inline void SETM( unsigned int a );
	
	void __fastcall Change_ModeSafe( uint32 mode );
	__inline void RestUserRONS();
	__inline void RestFiqRONS();
	__inline void RestIrqRONS();
	__inline void RestSvcRONS();
	__inline void RestUndRONS();
	__inline void RestAbtRONS();
	
	void  __fastcall loadusr( unsigned int n, unsigned int val );
	void __fastcall load( unsigned int rn, unsigned int val );
	unsigned int __fastcall rread( unsigned int rn );
	unsigned int __fastcall rreadusr( unsigned int n );

	void __inline __fastcall mwritew(unsigned int addr, unsigned int val);
	unsigned int __inline __fastcall mreadw(unsigned int addr);
	void __inline __fastcall mwriteb(unsigned int addr, unsigned int val);
	unsigned int __inline __fastcall mreadb(unsigned int addr);
	
	void __inline bdt_core(unsigned int opc);
	
	__inline void ldm_accur(unsigned int opc, unsigned int base, unsigned int rn_ind);
	__inline void stm_accur(unsigned int opc, unsigned int base, unsigned int rn_ind);
	
	__inline unsigned int* can_multy_read_direct(unsigned int base, unsigned int opc);
	__inline unsigned int* can_multy_write_direct(unsigned int base, unsigned int opc);
};

#endif // _INC_ARMCPU
