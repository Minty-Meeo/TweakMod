#ifndef UTILITY_H
#define UTILITY_H

#include "ansi_include.h"
#include "define.h"


unsigned int swap32(unsigned int value);
unsigned short swap16(unsigned short value);

unsigned int readU32( ifstream& inFile );
unsigned short readU16( ifstream& inFile );
unsigned char readU8( ifstream& inFile );
float readFloat(ifstream& inFile );

void writeU32( ofstream& outFile, unsigned int value );
void writeU16( ofstream& outFile, unsigned short value );
void writeU8( ofstream& outFile, unsigned char value );
void writeFloat(ofstream& outFile, float value );

void skip( ifstream& inFile, int offset );
void skip( ofstream& outFile, int offset );
void align( ifstream& inFile, int value );
void align( ofstream& outFile, int value );

string getUserInput( string prompt );

void clearShapeStruct( shape& mainShape );

string lookupGX_FMT( GX_FMT input );
unsigned int translateTexFormat( GX_FMT input );

#endif	// UTILITY_H
