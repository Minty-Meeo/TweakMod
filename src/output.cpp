#include "ansi_include.h"
#include "define.h"
#include "utility.h"

extern string filename;

void toWavefrontObj( shape& mainShape, char* filename ) {
	
	ofstream outFile;
	outFile.open( filename, std::ios_base::binary );
	
	/* Information */ {
		outFile << "# Date: " << mainShape.header.year << "/" << mainShape.header.month << "/" << mainShape.header.day << std::endl;
		outFile << std::endl;
	}
	outFile << "o mesh0" << "r\n";
	/* Vertex Positions */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
		
		if ( mainShape.vtx.pos.size() ) {		// Check if Vertex Positions exist
			
			outFile << "# Vertex Positions" << "\r\n";
			for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ )
				outFile << "v " << mainShape.vtx.pos[i].X << " " << mainShape.vtx.pos[i].Y << " " << mainShape.vtx.pos[i].Z << "\r\n";
			outFile << "\r\n";
			
		}
	}
	/* Vertex Normals */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
		
		if ( mainShape.vtx.nrm.size() ) {		// Check if Vertex Normals exist
			
			outFile << "# Vertex Normals" << "\r\n";
			for ( unsigned int i = 0; i < mainShape.vtx.nrm.size(); i++ )
				outFile << "vn " << mainShape.vtx.nrm[i].X << " " << mainShape.vtx.nrm[i].Y << " " << mainShape.vtx.nrm[i].Z << "\r\n";
			outFile << "\r\n";
			
		}
	}
	/* Prism Collision Faces */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		
		if ( mainShape.col.prism.size() ) {
			
			outFile << "# Collision Prism Faces" << "\r\n";
			for ( unsigned int i = 0; i < mainShape.col.prism.size(); i++ )
				 outFile << "f " << mainShape.col.prism[i].indice.X+1 << " " << mainShape.col.prism[i].indice.Y+1 << " " << mainShape.col.prism[i].indice.Z+1 << "\r\n";
			outFile << "\r\n";
			
		}
	}
	outFile.close();
	
}

void toDolphinModel( shape& mainShape, char* filename ) {
	
	ofstream outFile;
	outFile.open( filename, std::ios_base::binary  );
	
	/* <INFORMATION> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		
		outFile << "<INFORMATION>"																							<< "\r\n"
		        << "{"																										<< "\r\n"
		        << "	toolname	TweakMod"																				<< "\r\n"
				<< "	date	" << mainShape.header.year << "/" << mainShape.header.month << "/" << mainShape.header.day	<< "\r\n"
		        << "}"																										<< "\r\n\r\n";
	}
	/* <TEX_IMG> */ {
		for ( unsigned int index = 0; index < mainShape.tex.img.size(); index++ ) {		// Iterate through all sets of image data
			
			outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
			outFile
			<< "<TEX_IMG>"																				<< "\r\n"
			<< "{"																						<< "\r\n"
			<< "	index	" << index																	<< "\r\n"
			<< "	name	" << "dummy"																<< "\r\n"
			<< "	format	" << lookupGX_FMT( mainShape.tex.img[index].format )						<< "\r\n"
			<< "	size	" << mainShape.tex.img[index].xRes << " " << mainShape.tex.img[index].yRes	<< "\r\n";
			
			outFile.setf( std::ios::hex, std::ios::basefield );
			outFile.setf( std::ios::right, std::ios::adjustfield );
			outFile.setf( std::ios::uppercase );
			outFile.fill( '0' );
			// CMPR	|	word
			// IA4	|	byte
			switch ( mainShape.tex.img[index].format ) {		// Output Image Data
				case CMPR:
					for ( unsigned int i = 0; i < mainShape.tex.img[index].data.size(); i += 16 ) {
						outFile << "	word	";
						for ( unsigned int j = 0; j < 16; j += 4 ) {
							outFile << "0x"
							        << std::setw(2)	<< +mainShape.tex.img[index].data[i + j+0]
							        << std::setw(2) << +mainShape.tex.img[index].data[i + j+1]
							        << std::setw(2)	<< +mainShape.tex.img[index].data[i + j+2]
							        << std::setw(2)	<< +mainShape.tex.img[index].data[i + j+3];
							if ( j < 12 ) { outFile << " "; } else { outFile << "\r\n"; }
						}
					}
					break;
				
				case IA4:
					for ( unsigned int i = 0; i < mainShape.tex.img[index].data.size(); i += 8 ) {
						outFile << "	byte	";
						for ( unsigned int j = 0; j < 8; j++ ) {
							outFile << "0x"
							        << std::setw(2) << +mainShape.tex.img[index].data[i + j];
							if ( j < 7 ) { outFile << " "; } else { outFile << "\r\n"; }
						}
					}
					break;
				
				default:
					outFile << "¯\\_(ツ)_/¯" << "\r\n";
					break;
				
			}
			
			outFile << "}" << "\r\n\r\n";
			
		}
	}
	// <TEX_ATTR>
	/* <ENVELOPE> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
		
		if ( mainShape.mtx.evl.size() ) {
			
			/* Write to file */ {
				outFile << "<ENVELOPE>"									<< "\r\n"
				        << "{"											<< "\r\n"
				        << "	size	" << mainShape.mtx.evl.size()	<< "\r\n";
				
				outFile << "	evl_mtx_num	";
				for ( unsigned int i = 0; i < mainShape.mtx.evl.size(); i++ )
					outFile << mainShape.mtx.evl[i].num << " ";
				outFile << "\r\n";
				
				outFile << "	evl_mtx_idx	";
				for ( unsigned int i = 0; i < mainShape.mtx.evl.size(); i++ ) {
					for ( unsigned int j = 0; j < mainShape.mtx.evl[i].num; j++ )
						outFile << mainShape.mtx.evl[i].idx[j] << " ";
					outFile << "  ";
				}
				outFile << "\r\n";
				
				outFile << "	evl_mtx_wgt	";
				for ( unsigned int i = 0; i < mainShape.mtx.evl.size(); i++ ) {
					for ( unsigned int j = 0; j < mainShape.mtx.evl[i].num; j++ )
						outFile << mainShape.mtx.evl[i].wgt[j] << " ";
					outFile << "  ";
				}
				outFile << "\r\n";
				
				outFile << "}" << "\r\n\r\n";
			}
		
		}
	}
	// <VTX_MATRIX>
	/* <VTX_POS> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
	
		if ( mainShape.vtx.pos.size() ) {
			
			float minX = mainShape.vtx.pos[0].X;
			float minY = mainShape.vtx.pos[0].Y;
			float minZ = mainShape.vtx.pos[0].Z;
			float maxX = mainShape.vtx.pos[0].X;
			float maxY = mainShape.vtx.pos[0].Y;
			float maxZ = mainShape.vtx.pos[0].Z; 
			
			/* Find min and max */ {
				for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ ) {
					if ( minX > mainShape.vtx.pos[i].X ) minX = mainShape.vtx.pos[i].X;
					if ( minY > mainShape.vtx.pos[i].Y ) minY = mainShape.vtx.pos[i].Y;
					if ( minZ > mainShape.vtx.pos[i].Z ) minZ = mainShape.vtx.pos[i].Z;
					if ( maxX < mainShape.vtx.pos[i].X ) maxX = mainShape.vtx.pos[i].X;
					if ( maxY < mainShape.vtx.pos[i].Y ) maxY = mainShape.vtx.pos[i].Y;
					if ( maxZ < mainShape.vtx.pos[i].Z ) maxZ = mainShape.vtx.pos[i].Z;
				}
			}
			
			/* Write to file */ {
				outFile << "<VTX_POS>"										<< "\r\n"
				        << "{"												<< "\r\n"
				        << "	size	" << mainShape.vtx.pos.size()		<< "\r\n"
				        << "	min	" << minX << " " << minY << " " << minZ	<< "\r\n"
				        << "	max	" << maxX << " " << maxY << " " << maxZ	<< "\r\n\r\n";
				
				for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ )
					outFile << "	float	" << mainShape.vtx.pos[i].X << " " << mainShape.vtx.pos[i].Y << " " << mainShape.vtx.pos[i].Z << "\r\n";
				outFile << "}" << "\r\n\r\n";
			}
		
		}
	}
	// <DEFORMED_XYZ>
	// <ENVELOPE_XYZ>
	/* <VTX_NRM> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
		
		if ( mainShape.vtx.nrm.size() ) {
			
			/* Write to file */ {
				outFile << "<VTX_NRM>"										<< "\r\n"
				        << "{"												<< "\r\n"
				        << "	size	" << mainShape.vtx.nrm.size()		<< "\r\n\r\n";
				
				for ( unsigned int i = 0; i < mainShape.vtx.nrm.size(); i++ )
					outFile << "	float	" << mainShape.vtx.nrm[i].X << " " << mainShape.vtx.nrm[i].Y << " " << mainShape.vtx.nrm[i].Z << "\r\n";
				outFile << "}" << "\r\n\r\n";
			}
		
		}
	}
	/* <TEXCOORD0> to <TEXCOORD7> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		outFile.precision(6);									// Always show 6 of them
		
		for ( int index = 0; index < 8; index++ ) {						//
			
			if ( mainShape.vtx.texCoord[index].size() ) {						// Check if Vertex Texture Coordinates exist
				
				/* Write to file */ {
					outFile << "<TEXCOORD" << index << ">"								<< "\r\n"
					        << "{"														<< "\r\n"
					        << "	size	" << mainShape.vtx.texCoord[index].size()	<< "\r\n"
					        << "	min	0.000000 0.000000"								<< "\r\n"
					        << "	max	1.000000 1.000000"								<< "\r\n\r\n";
					
					for ( unsigned int i = 0; i < mainShape.vtx.texCoord[index].size(); i++ )
						outFile << "	float	" << mainShape.vtx.texCoord[index][i].U << " " << mainShape.vtx.texCoord[index][i].V << "\r\n";
					outFile << "}" << "\r\n\r\n";
				}
				
			}
			
		}
	}
	/* <COLOR0> */ {
		outFile.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		outFile.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
		
		if ( mainShape.vtx.color0.size() ) {
			
			/* Write to file */ {
				outFile << "<COLOR0>"										<< "\r\n"
				        << "{"												<< "\r\n"
				        << "	size	" << mainShape.vtx.color0.size()	<< "\r\n\r\n";
				
				for ( unsigned int i = 0; i < mainShape.vtx.color0.size(); i++ )
					outFile << "	byte	" << static_cast<unsigned int>(mainShape.vtx.color0[i].R) << " " << static_cast<unsigned int>(mainShape.vtx.color0[i].G) << " " << static_cast<unsigned int>(mainShape.vtx.color0[i].B) << " " << static_cast<unsigned int>(mainShape.vtx.color0[i].A) << "\r\n";
				outFile << "}" << "\r\n\r\n";
			}
		
		}
	}
	// <MATERIAL>
	// <POLYGON>
	// <JOINT>
	
	outFile.close();
	
}

void toShape( shape& mainShape, char* filename ) {
	
	ofstream outFile;
	outFile.open( filename, std::ios_base::binary );
	
	/* Vertex Positions */ {
		if ( mainShape.vtx.pos.size() ) {		// Check if Vertex Positions exist
			writeU32( outFile, 0x00000010 );				// Chunk Opcode
			writeU32( outFile, 0 );							// Packet Count
			writeU32( outFile, mainShape.vtx.pos.size() );	// Chunk Size
			align( outFile, 0x20 );							// Align for container
			for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ ) {
				writeFloat( outFile, mainShape.vtx.pos[i].X );
				writeFloat( outFile, mainShape.vtx.pos[i].Y );
				writeFloat( outFile, mainShape.vtx.pos[i].Z );
			}
			align( outFile, 0x20 );
			
			
		}
	}
	
	outFile.close();
	
}

void exportINI( shape& mainShape, char* filename ) {
	
	if ( mainShape.ini.size() == 0 ) {
		std::cout << "No INI file found" << std::endl;
		return;
	}
	
	ofstream outFile;
	outFile.open( filename, std::ios_base::binary );
	outFile.write( mainShape.ini.data(), mainShape.ini.size() );
	outFile.close();
	
}

void exportBTI( shape& mainShape, char* filename ) {
	
	ofstream outFile;
	
	for ( unsigned int index = 0; index < mainShape.tex.img.size(); index++ ) {
		string destFile = filename;
		destFile += "-";
		destFile += std::to_string(index);
		destFile += ".bti";
		
		std::cout << destFile << std::endl;
		
		
		outFile.open( destFile.c_str(), std::ios_base::binary );
		
		writeU8( outFile, translateTexFormat( mainShape.tex.img[index].format ) );			// Format
		writeU8( outFile, 0x00 );															// Alpha Flag
		writeU16( outFile, mainShape.tex.img[index].xRes );	// X Res
		writeU16( outFile, mainShape.tex.img[index].yRes );	// Y Res
		skip( outFile, 0x12 );
		writeU8( outFile, 0x01 );
		skip (outFile, 0x03 );
		writeU32( outFile, 0x20 );
		outFile.write( mainShape.tex.img[index].data.data(), mainShape.tex.img[index].data.size() );
		
		outFile.close();
	}
}

/*
<POLYGON>
<VTX_MATRIX>
<ENVELOPE>			###
<TEX_IMG>
<TEX_ATTR>
<JOINT>
<MATERIAL>
<COLOR0>
<TEXCOORD7>			###
...					###
<TEXCOORD0>			###
<VTX_NBT>
<ENVELOPE_TANGENT>
<ENVELOPE_BINORMAL>
<ENVELOPE_NRM>
<ENVELOPE_XYZ>
<INFORMATION>		###
*/
