#include "ansi_include.h"
#include "define.h"
#include "utility.h"

extern string filename;

void fromShape( shape& mainShape, char* filename ) {
	
	clearShapeStruct( mainShape );
	mainShape.filename = filename;
	
	ifstream inFile;
	inFile.open( filename, std::ios::binary );							// Open Shape
	if ( !( inFile.is_open() ) ) {
		std::cout << "Could not open file!!" << std::endl;
		return;
	}
	
	bool eofFlag = false;								// EOF Flag to be tripped by 0xFFFF chunk
	
	while ( eofFlag == false ) {						// ==========Read Shape==========
	
		unsigned int opcode = readU32( inFile );		// Read Opcode
		
		/* [DEBUG] Report Opcode */ {
			std::cout << "  Opcode: ";
			std::cout.setf( std::ios::right, std::ios::adjustfield );
			std::cout.setf( std::ios::hex,   std::ios::basefield   );
			std::cout.width( 4 );
			std::cout.fill( '0' );
			std::cout << opcode;
		}
		
		switch ( opcode ) {								// Operate based on Opcode
			case 0x0000:
				/* Header */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					align( inFile, 0x20 );
					
					mainShape.header.year = readU16( inFile );
					mainShape.header.month = readU8( inFile );
					mainShape.header.day = readU8( inFile );
					mainShape.header.unk = readU32( inFile );
				}
				break;
			case 0x0010:
				/* Vertex Positions */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					mainShape.vtx.pos.resize( readU32( inFile ) );		// Allocate vertexes from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ ) {
						mainShape.vtx.pos[i].X = readFloat( inFile );
						mainShape.vtx.pos[i].Y = readFloat( inFile );
						mainShape.vtx.pos[i].Z = readFloat( inFile );
					}
				}
				break;
			case 0x0013:
				/* Vertex Colors */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					mainShape.vtx.color0.resize( readU32( inFile ) );	// Allocate colors from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.vtx.color0.size(); i++ ) {
						mainShape.vtx.color0[i].R = readU8( inFile );
						mainShape.vtx.color0[i].G = readU8( inFile ); 
						mainShape.vtx.color0[i].B = readU8( inFile );
						mainShape.vtx.color0[i].A = readU8( inFile );
					}
				}
				break;
			case 0x0011:
				/* Vertex Normals */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					mainShape.vtx.nrm.resize( readU32( inFile ) );		// Allocate normals from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.vtx.nrm.size(); i++ ) {
						mainShape.vtx.nrm[i].X = readFloat( inFile );
						mainShape.vtx.nrm[i].Y = readFloat( inFile );
						mainShape.vtx.nrm[i].Z = readFloat( inFile );
					}
				}
				break;
//			case 0x0012:
//				/* Vertex NBT(?) */ {}		// Unimplemented
//				break;
			case 0x0018 ... 0x001F:
				/* Vertex Texture Coordinates 0-7 */ {
					unsigned int index = opcode - 0x0018;						// Calculate index from opcode
					
					unsigned int containerSize = readU32( inFile );				// Read Container Size in case we need it
					mainShape.vtx.texCoord[index].resize( readU32( inFile ) );	// Allocate texture coordinates from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.vtx.texCoord[index].size(); i++ ) {
						mainShape.vtx.texCoord[index][i].U = readFloat( inFile );
						mainShape.vtx.texCoord[index][i].V = readFloat( inFile );
					}
				}
				break;
			
			case 0x0020:
				/* TXE Files */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					mainShape.tex.img.resize( readU32( inFile ) );		// Allocate textures from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.tex.img.size(); i++ ) {		// Read one mTXE at a time
						
						unsigned int dataSize;
						
						/* Read mTXE header */ {
							mainShape.tex.img[i].xRes = readU16( inFile );
							mainShape.tex.img[i].yRes = readU16( inFile );
							mainShape.tex.img[i].format = static_cast<GX_FMT>( readU32( inFile ) );
							mainShape.tex.img[i].unk = readU32( inFile );
							skip( inFile, 0x10 );
							dataSize = readU32( inFile );
						
						}
						/* Read mTXE data */ {
// Manual					dataSize = mainShape.tex.img[i].xRes * mainShape.tex.img[i].yRes;
// Calculation				
// Backup					switch ( mainShape.tex.img[i].format ) {				// Adjust format weights
//								case RGB565:	dataSize *= 2;		break;
//								case CMPR:		dataSize *= 0.5;	break;
//								case RGB5A3:	dataSize *= 2;		break;
//								case I4:		dataSize *= 0.5;	break;
//								case I8:							break;
//								case IA4:							break;
//								case IA8:		dataSize *= 2;		break;
//								case RGBA8:		dataSize *= 4;		break;
//								// Todo: What are type 8 and 9?
//							}
							
							mainShape.tex.img[i].data.resize( dataSize );			// Allocate space for image data
							
							for ( unsigned int j = 0; j < dataSize; j++ )			// Read image data
								mainShape.tex.img[i].data[j] = readU8( inFile );	// One byte at a time
						}
					
					}
					
				}
				break;
//			case 0x0022:
//				/* Tex Attributes */ {}		// Unimplemented
//			case 0x0030:
//				/* Material */ {}			// Unimplemented

//			case 0x0040:
//				/* Vertex Matrix */ {}		// Unimplemented
			case 0x0041:
				/* Matrix Envelope */ {
					unsigned int containerSize = readU32( inFile );		// Read Container Size in case we need it
					mainShape.mtx.evl.resize( readU32( inFile ) );		// Allocate envelope from Packet Count
					align( inFile, 0x20 );
					
					for ( unsigned int i = 0; i < mainShape.mtx.evl.size(); i++ ) {
						mainShape.mtx.evl[i].num = readU16( inFile );
						
						mainShape.mtx.evl[i].idx.resize( mainShape.mtx.evl[i].num );
						mainShape.mtx.evl[i].wgt.resize( mainShape.mtx.evl[i].num );
						
						for ( unsigned int j = 0; j < mainShape.mtx.evl[i].num; j++ ) {
							mainShape.mtx.evl[i].idx[j] = readU16( inFile );
							mainShape.mtx.evl[i].wgt[j] = readFloat( inFile );
						}
					}
				}
				break;
			
//			case 0x0050:
//				/* Mesh */ {}				// Unimplemented

//			case 0x0060:
//				/* Joint */ {}				// Unimplemented
//			case 0x0061:
//				/* Joint Name */ {}			// Unimplemented
			case 0x0100:
				/* Collision Prism */ {
					unsigned int containerSize = readU32( inFile );			// Read Container Size in case we need it
					mainShape.col.prism.resize( readU32( inFile ) );		// Allocate texture coordinates from Packet Count
					mainShape.col.prismUnk = readU32( inFile );				// Unknown value in Chunk Header
					align( inFile, 0x20 );
					skip ( inFile, 0x20 );		// There is a buncha padding for some reason??
					
					for ( unsigned int i = 0; i < mainShape.col.prism.size(); i++ ) {
						mainShape.col.prism[i].unk1 = readU32( inFile );
						mainShape.col.prism[i].indice.X = readU32( inFile );
						mainShape.col.prism[i].indice.Y = readU32( inFile );
						mainShape.col.prism[i].indice.Z = readU32( inFile );
						mainShape.col.prism[i].unk2 = readU16( inFile );
						mainShape.col.prism[i].unk3 = readU16( inFile );
						mainShape.col.prism[i].unk4 = readU16( inFile );
						mainShape.col.prism[i].unk5 = readU16( inFile );
						mainShape.col.prism[i].unk6 = readU32( inFile );
						mainShape.col.prism[i].unk7 = readU32( inFile );
						mainShape.col.prism[i].unk8 = readU32( inFile );
						mainShape.col.prism[i].unk9 = readFloat( inFile );
					}
				}
				break;
//			case 0x0110:
//				/* Collision Grid */ {}		// Unimplemented
			
			case 0xFFFF:
				/* End of File */ {
					eofFlag = true;
				}
				break;
				
			default:
				/* Unimplemented opcode failsafe */ {
					unsigned int containerSize = readU32( inFile );
					
					inFile.seekg( containerSize, std::ios_base::cur );
					
					std::cout << "	Unimplemented";
				}
				break;
		}
		
		std::cout << std::endl;							// [DEBUG] print newline
		
		align( inFile, 0x20 );							// Realign on 0x20 multiple
		
//		system( "pause" );								// [DEBUG] Pause after each chunk
		
		inFile.peek();									// Check for EOF.  Important if there is no INI file appended.
		
	}
	
	if ( !( inFile.eof() ) ) {							// Check for Appended INI
		
		std::cout << "  INI file found" << std::endl;	// [DEBUG] Report INI file
		
		while ( !( inFile.eof() ) ) {					// ==========Read INI==========
			mainShape.ini.push_back( inFile.get() );	// Get character
			inFile.peek();								// Check for EOF
		}
	
	}
	
	inFile.close();										// Close Shape
	
}

void fromWavefrontObj( shape& mainShape, char* filename ) {
	
	clearShapeStruct( mainShape );
	
	ifstream inFile;
	inFile.open( filename, std::ios::binary );							// Open Wavefront OBJ
	if ( !( inFile.is_open() ) ) { std::cout << "Could not open file!!" << std::endl;	return;	}
	
	inFile.peek();		// Check for 0 byte file

	while ( !( inFile.eof() ) ) {
		string opcode;
		getline( inFile, opcode, ' ' );
		/**/ if ( !strcmp( opcode.c_str(), "v" ) ) {
			xyz newVtxPos;
			inFile >> newVtxPos.X >> newVtxPos.Y >> newVtxPos.Z;
			inFile.ignore( 256, '\n' );		// Discard newline
			mainShape.vtx.pos.push_back( newVtxPos );
		}
		else if ( !strcmp( opcode.c_str(), "vn" ) ) {
			xyz newVtxNrm;
			inFile >> newVtxNrm.X >> newVtxNrm.Y >> newVtxNrm.Z;
			mainShape.vtx.nrm.push_back( newVtxNrm );
			inFile.ignore( 256, '\n' );		// Discard newline
		}
		else { getline( inFile, opcode ); }
	}
	
	inFile.close();
	
}

