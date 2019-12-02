// TWEAKMOD - A utility for Shape files (*.mod) found in Pikmin 1.
// Created by The JustGreat Minty Meeo

#include "ansi_include.h"
#include "define.h"
#include "input.h"
#include "output.h"
#include "debug.h"
#include "utility.h"


void printHelp();
void printError();

int main( unsigned int argc, char* argv[] ) {
	
	if ( argc == 1 || !strcmp( argv[1], "/?" ) ) { printHelp();		return -1; }	// Triggers for help popup
	
	
	shape mainShape;									// Main struct (see define.h)
	
	for ( unsigned int i = 1; i < argc; i++ ) {
		
		std::cout << "Errand: " << argv[i] << std::endl;		// [DEBUG] Relay what errand is being attempted
		
		// Read current errand
		/**/ if ( !strcmp( argv[i], "in-MOD" ) ) 			{ fromShape( mainShape, argv[i+1] ); i++; }				// Read MOD file
		else if ( !strcmp( argv[i], "in-OBJ" ) ) 			{ fromWavefrontObj( mainShape, argv[i+1] ); i++; }		// Read OBJ file
		
		else if ( !strcmp( argv[i], "out-MOD" ) )			{ toShape( mainShape, argv[i+1] ); }					// Write MOD file
		else if ( !strcmp( argv[i], "out-OBJ" ) )			{ toWavefrontObj( mainShape, argv[i+1] ); i++; }		// Write OBJ file
		else if ( !strcmp( argv[i], "out-DMD" ) )			{ toDolphinModel( mainShape, argv[i+1] ); i++; }		// Write DMD file
		
		else if ( !strcmp( argv[i], "export-INI" ) )		{ exportINI( mainShape, argv[i+1] ); i++; }				// Export INI
		else if ( !strcmp( argv[i], "export-BTI" ) )		{ exportBTI( mainShape, argv[i+1] ); i++; }				// Export TXE
		
//		else if ( !strcmp( argv[i], "import-TXE" ) )		{ importTXE( mainShape, atoi( argv[i+1] ) ); i++; }		// Import TXE
		
		else if ( !strcmp( argv[i], "debug-Header" ) )		{ debugHeader( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-VtxPos" ) )		{ debugVtxPos( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-VtxNrm" ) )		{ debugVtxNrm( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-TexCoord" ) )	{ debugTexCoord( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-Texture" ) )		{ debugTexture( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-ColPrism" ) )	{ debugColPrism( mainShape ); }							// (1 argument)
		else if ( !strcmp( argv[i], "debug-INI" ) )			{ debugINI( mainShape ); }								// (1 argument)
		else { std::cout << "Undefined errand" << std::endl; }
		
		std::cout << std::endl;
		
	}
	
}

void printHelp() {
	std::cout <<
	"A utility for Shape files (*.mod) found in Pikmin 1."                           << std::endl <<
	""                                                                               << std::endl <<
	"TWEAKMOD errand \"filename\" [ errand \"filename\" ] [ ... ]"                   << std::endl <<
	""                                                                               << std::endl <<
	"  errand            Function to be performed"                                   << std::endl <<
	"                      iMOD  input a Shape file (*.mod)"                         << std::endl <<
	"                      oOBJ  output a Wavefront Object file (*.obj)"             << std::endl <<
	"                      oDMD  output a Dolphin Model file (*.dmd)"                << std::endl <<
	"                      oLOG  output to command window and log file"              << std::endl <<
	""                                                                               << std::endl <<
	"  filename          Name of file to perform errand on."                         << std::endl <<
	""                                                                               << std::endl <<
	"Only one input errand should be given."                                         << std::endl <<
	"Any number of output errands can be given."                                     << std::endl <<
	""                                                                               << std::endl <<
	"To bring up help information, pass /? as the only argument"                     << std::endl <<
	""                                                                               << std::endl <<
	"ERRORLEVELS:"                                                                   << std::endl <<
	"  -1  | Help prompt called"                                                     << std::endl <<
	"  -2  | Malformed arguments"                                                    << std::endl;
}

void printError() {
	std::cout <<
	"Malformed arguments (errand without filename)"                                  << std::endl;
}
