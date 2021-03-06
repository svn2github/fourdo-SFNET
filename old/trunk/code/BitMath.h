#ifndef _INC_BITMATH
#define _INC_BITMATH

#include "types.h"
#include "wx/wx.h"
#include <string>

#include <math.h>
#include <cstdio>

//////////////////////////////////////////////////
// Inline functions
inline uint32 ByteSwap( uint32 number )
{
	return 
	(
		( (number & 0x000000FF) << 24 )+
		( (number & 0x0000FF00) << 8  )+
		( (number & 0x00FF0000) >> 8  )+
		( (number & 0xFF000000) >> 24 )
	);
}

inline void ByteSwapMem( uint32* memory, uint32 lengthInBytes )
{
	for( uint32 x = 0; x < (lengthInBytes+(sizeof(uint32*)-1))/(sizeof(uint32*)); x++ )
	{
	    memory[x] = ByteSwap(memory[x]);
	}
}

inline uint32 AlignmentSwap( uint32 number )
{
	return (number ^ 0x3);
}

inline uint32 WordAlign( uint32 number )
{
	return 
	(
		(number & 0xFFFFFFFC)
	);
}

//////////////////////////////////////////////////
// Normal functions
uint SetBit  (uint value, int bitNumber, bool bitValue);
uint SetBits (uint value, uint setMask, uint setValue);

wxString CharToBitString (char value);
wxString UintToBitString (uint value);
wxString UintToHexString (uint value);

std::string ReadSwappedString(char* buffer);

#endif //_INC_BITMATH