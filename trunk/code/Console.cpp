#include "Console.h"

#include "filesystem/file.h"

#define  ROM_LOAD_ADDRESS  0x00100000

Console::Console ()
{
   // Constructor
   mDMA = new DMAController ();
   
   mCPU = new ARMCPU ();
   mCPU->DMA = mDMA;
   
   mKernelFaker = new KernelFaker();
   
   Reset();
}

Console::~Console ()
{
   // Destructor
   delete mDMA;
   delete mCPU;
}

void Console::Reset()
{
   mCPU->Reset();
   mDMA->Reset();
}

ARMCPU* Console::CPU ()
{
   return mCPU;
}

DMAController* Console::DMA ()
{
   return mDMA;
}

bool Console::loadIso( wxString fileName )
{
	///////////////////////////////////////////////////
	// Actions taken here should emulate the behavior of
	// a 3DO that has set up the operating system for
	// the loaded game
	
	///////////////////////////////////////////////////
	// Open the Launchme of this CD image
	uint32  bytesRead;
	File f( reinterpret_cast<const char *>(fileName.c_str()) );

	if( !f.openFile( "/launchme" ) )
		return false;

	// Load it into memory.
	f.read( mDMA->GetRAMPointer( ROM_LOAD_ADDRESS ), f.getFileSize (), &bytesRead );
	

	//..................................................................//
	//..................................................................//
	//..................................................................//
	//..................................................................//
	//Load ram dump.
	#define READ_START   0x0
	#define READ_LENGTH  0x30000
	FILE* file;
	file = fopen("C:\\FourDO\\roms\\SDA_RAM.bin", "rb");
	fseek( file, READ_START, SEEK_SET );
	fread( (void*)mDMA->GetRAMPointer(READ_START), READ_LENGTH, 1, file );
	fclose(file);
	//..................................................................//
	//..................................................................//
	//..................................................................//
	//..................................................................//
	

	///////////////////////////////////////////////////
	// Set up some initial register values.
	mCPU->ARM.USER[0]  = 0x00000000;
	mCPU->ARM.USER[1]  = 0x00000000;
	mCPU->ARM.USER[2]  = 0x00000000;
	mCPU->ARM.USER[3]  = 0x00000000;
	mCPU->ARM.USER[4]  = 0xFFFFFFFC;
	mCPU->ARM.USER[5]  = 0x00000000;
	mCPU->ARM.USER[6]  = 0x00000000;
	mCPU->ARM.USER[7]  = KernelFaker::getFakeKernelBase();
	mCPU->ARM.USER[8]  = 0x00000000;
	mCPU->ARM.USER[9]  = 0x400002CC;
	mCPU->ARM.USER[10] = 0x00030000;
	mCPU->ARM.USER[11] = 0x00000000;
	mCPU->ARM.USER[12] = 0x00078508;
	mCPU->ARM.USER[13] = 0x00000000;
	mCPU->ARM.USER[14] = 0x00000000;
	mCPU->ARM.USER[15] = ROM_LOAD_ADDRESS;

	// Put the stack pointers somewhere
	mCPU->ARM.USER[13] = 0x00040000;
	mCPU->ARM.SVC[0]   = 0x00041000;
	mCPU->ARM.ABT[0]   = 0x00042000;
	mCPU->ARM.IRQ[0]   = 0x00043000;
	mCPU->ARM.UND[0]   = 0x00044000;
	mCPU->ARM.FIQ[5]   = 0x00045000;	
	
	///////////////////////////////////////////////////
	// Put some crap on the USR mode stack that is 
	// normally there by the time LaunchMe is run
	sprintf( (char*)mDMA->GetRAMPointer( mCPU->ARM.USER[13] ), "$app/Launchme" );
	
	///////////////////////////////////////////////////
	// Create a fake kernel table 
	mKernelFaker->init( mDMA );
	
	return true;
}

bool Console::loadBinary( wxString fileName )
{
	// Open a code file.
	wxFile file;
	
	// Load the code into memory
	if( !file.Open( fileName ) )
		return false;
	
	if( file.Read( mDMA->GetRAMPointer( ROM_LOAD_ADDRESS ), file.Length () ) == wxInvalidOffset )
		return false;
	
	file.Close();

	// Set PC
	mCPU->SetPC( ROM_LOAD_ADDRESS );
	
	// Set to user mode
	mCPU->SetCPSR(0x00000010);
	
	return true;
}
