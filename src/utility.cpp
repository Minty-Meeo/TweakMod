#include "ansi_include.h"
#include "define.h"


//		BYTE SWAPPING FUNCTIONS / DEFINES

#define _BSWAP_16(v) (((v & 0xff00) >> 8) | \
                      ((v & 0x00ff) << 8))

#define _BSWAP_32(v) (((v & 0xff000000) >> 24) | \
                      ((v & 0x00ff0000) >>  8) | \
                      ((v & 0x0000ff00) <<  8) | \
                      ((v & 0x000000ff) << 24) )

#define MAKE_BE32(x) _BSWAP_32(x)
#define MAKE_LE32(x) x
#define MAKE_BE16(x) _BSWAP_16(x)
#define MAKE_LE16(x) x

unsigned int swap32(unsigned int value) {
    return _BSWAP_32( value );
}
unsigned short swap16(unsigned short value) {
    return _BSWAP_16( value );
}


//	FILE READING FUNCTIONS

unsigned int readU32( ifstream& inFile ) {
	unsigned int value;
	
	inFile.read( reinterpret_cast<char*>(&value), 4 );
	return swap32( value );
}
unsigned short readU16( ifstream& inFile ) {
	unsigned short value;
	
	inFile.read( reinterpret_cast<char*>(&value), 2 );
	return swap16( value );
}
unsigned char readU8( ifstream& inFile ) {
	unsigned char value;
	
	inFile.read( reinterpret_cast<char*>(&value), 1 );
	return value;
}
float readFloat(ifstream& inFile ) {
	unsigned int value;
	
	inFile.read( reinterpret_cast<char*>(&value), 4 );
	value = swap32( value );
	return reinterpret_cast<float&>(value);
}

void writeU32( ofstream& outFile, unsigned int value ) {
	value = swap32( value );
	outFile.write( reinterpret_cast<char*>(&value), 4 );
}
void writeU16( ofstream& outFile, unsigned short value ) {
	value = swap16( value );
	outFile.write( reinterpret_cast<char*>(&value), 2 );
}
void writeU8( ofstream& outFile, unsigned char value ) {
	outFile.write( reinterpret_cast<char*>(&value), 1 );
}

void writeFloat(ofstream& outFile, float value ) {
	unsigned int value2 = reinterpret_cast<unsigned int&>(value);
	value2 = swap32( value2 );
	outFile.write( reinterpret_cast<char*>(&value2), 4 );
}


void skip( ifstream& inFile, int offset ) {
	inFile.seekg( offset, std::ios_base::cur );
}
void skip( ofstream& outFile, int offset ) {
	outFile.seekp( offset, std::ios_base::cur );
}
void align( ifstream& inFile, int value ) {
	int offset = value - ( inFile.tellg() % value );
	
	if ( offset == 0x20 ) return;
	
	inFile.seekg( offset, std::ios_base::cur );
}
void align( ofstream& outFile, int value ) {
	int offset = value - ( outFile.tellp() % value );
	
	if ( offset == 0x20 ) return;
	
	outFile.seekp( offset, std::ios_base::cur );
}

string getUserInput( string prompt ) {
	std::cout << prompt;
	string temp;
	std::cin >> temp;
	return temp;
}

void clearShapeStruct( shape& mainShape ) {
	mainShape.header.day = 0;
	mainShape.header.month = 0;
	mainShape.header.year = 0;
	mainShape.header.unk = 0;
	mainShape.vtx.pos.clear();
	mainShape.vtx.nrm.clear();
	mainShape.vtx.color0.clear();
	mainShape.vtx.texCoord[0].clear();
	mainShape.vtx.texCoord[1].clear();
	mainShape.vtx.texCoord[2].clear();
	mainShape.vtx.texCoord[3].clear();
	mainShape.vtx.texCoord[4].clear();
	mainShape.vtx.texCoord[5].clear();
	mainShape.vtx.texCoord[6].clear();
	mainShape.vtx.texCoord[7].clear();
	mainShape.tex.img.clear();
	mainShape.tex.attr.clear();
	mainShape.mtx.evl.clear();
	mainShape.col.prism.clear();
	mainShape.ini.clear();
}

string lookupGX_FMT( GX_FMT input ) {
	switch ( input ) {	// GX_FMT ID --> GX_FMT descriptor
		case RGB565:	return "RGB565";
		case CMPR:		return "CMPR";
		case RGB5A3:	return "RGB5A3";
		case I4:		return "I4";
		case I8:		return "I8";
		case IA4:		return "IA4";
		case IA8:		return "IA8";
		case RGBA8:		return "RGBA8";
		// Todo: What are type 8 and 9?
		default:		return "unk";
	}
}
unsigned int translateTexFormat( GX_FMT input ) {
	switch ( input ) {	// GX_FMT ID --> BTI Format ID
		case RGB565:	return 0x04;
		case CMPR:		return 0x0E;
		case RGB5A3:	return 0x05;
		case I4:		return 0x00;
		case I8:		return 0x01;
		case IA4:		return 0x02;
		case IA8:		return 0x03;
		case RGBA8:		return 0x06;
		// Todo: What are type 8 and 9?
		default:		return 0xFF;
	}
}
