#include "ansi_include.h"
#include "define.h"
#include "utility.h"

void debugHeader( shape& mainShape ) {
	
	std::cout.setf( std::ios::dec, std::ios::basefield );		// Base-10
	
	std::cout << "Date: " << mainShape.header.year << "/" << mainShape.header.month << "/" << mainShape.header.day << std::endl;
	std::cout << "Scaling Mode: " << mainShape.header.unk << std::endl;
	
}


void debugVtxPos( shape& mainShape ) {

	std::cout.setf( std::ios::dec, std::ios::basefield );		// Base-10
	std::cout.setf( std::ios::fixed, std::ios::floatfield );	// Show decimal places
	std::cout.precision(6);										// Show 6 of them
	std::cout.setf( std::ios::right, std::ios::adjustfield );	// Right aligned
	std::cout.fill( ' ' );										// Fill gaps with spaces
	
	std::cout << "Vertex Position Debug" << std::endl;
	std::cout << "Count: " << mainShape.vtx.pos.size() << std::endl;
	
	for ( unsigned int i = 0; i < mainShape.vtx.pos.size(); i++ ) {
		std::cout
		<< std::setw(5) << i
		<< std::setw(14) << mainShape.vtx.pos[i].X
		<< std::setw(14) << mainShape.vtx.pos[i].Y
		<< std::setw(14) << mainShape.vtx.pos[i].Z
		<< std::endl;
	}
		
}


void debugVtxNrm( shape& mainShape ) {
	
	std::cout.setf( std::ios::dec, std::ios::basefield );		// Base-10
	std::cout.setf( std::ios::fixed, std::ios::floatfield );	// Show decimal places
	std::cout.precision(6);										// Show 6 of them
	std::cout.setf( std::ios::right, std::ios::adjustfield );	// Right aligned
	std::cout.fill( ' ' );										// Fill gaps with spaces
	
	std::cout << "Vertex Normal Debug" << std::endl;
	std::cout << "Count: " << mainShape.vtx.nrm.size() << std::endl;
	
	for ( unsigned int i = 0; i < mainShape.vtx.nrm.size(); i++ ) {
		std::cout
		<< std::setw(5) << i
		<< std::setw(11) << mainShape.vtx.nrm[i].X
		<< std::setw(11) << mainShape.vtx.nrm[i].Y
		<< std::setw(11) << mainShape.vtx.nrm[i].Z
		<< std::endl;
	}
	
}


void debugTexCoord( shape& mainShape ) {
	
	std::cout.setf( std::ios::dec, std::ios::basefield );		// Base-10
	std::cout.setf( std::ios::fixed, std::ios::floatfield );	// Show decimal places
	std::cout.precision(6);										// Show 6 of them
	std::cout.setf( std::ios::right, std::ios::adjustfield );	// Right aligned
	std::cout.fill( ' ' );										// Fill gaps with spaces
	
	std::cout << "Texture Coordinate Debug" << std::endl;
	for ( int index = 0; index < 8; index++ ) {
		
		std::cout << "TEXCOORD" << index << " count: " << mainShape.vtx.texCoord[index].size() << std::endl;
		
		if ( mainShape.vtx.texCoord[index].size()) {		// Check if Vertex Texture Coordinates exist
			
			for ( unsigned int i = 0; i < mainShape.vtx.texCoord[index].size(); i++ ) {
				std::cout
				<< std::setw(5) << i
				<< std::setw(11) << mainShape.vtx.texCoord[index][i].U
				<< std::setw(11) << mainShape.vtx.texCoord[index][i].V
				<< std::endl;
			}
			
		}
		
	}
	
}


void debugTexture( shape& mainShape ) {
	
	std::cout.setf( std::ios::right, std::ios::adjustfield );	// Right aligned
	
	std::cout << "count: " << mainShape.tex.img.size() << std::endl;
	
	for ( unsigned int index = 0; index < mainShape.tex.img.size(); index++ ) {		// Iterate through all sets of image data
		
		std::cout.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
		std::cout.fill( ' ' );										// Fill gaps with spaces
		std::cout
		<< "(#" << index << ")" << "  "
		<< "xRes: " << mainShape.tex.img[index].xRes << "  "
		<< "yRes: " << mainShape.tex.img[index].yRes << "  "
		<< "GX_FMT: " << lookupGX_FMT( mainShape.tex.img[index].format ) << std::endl;
		
//		std::cout.setf( std::ios::hex, std::ios::basefield );		// The second part likes hexadecimal
//		std::cout.fill( '0' );										// Fill gaps with zeros
//		for ( unsigned int i = 0; i < mainShape.tex.img[index].data.size(); i += 16 ) {
//			for ( unsigned int j = 0; j < 16; j += 4 ) {
//				std::cout
//				<< std::setw(2)	<< +mainShape.tex.img[index].data[i + j+0]
//				<< std::setw(2) << +mainShape.tex.img[index].data[i + j+1]
//				<< std::setw(2)	<< +mainShape.tex.img[index].data[i + j+2]
//				<< std::setw(2)	<< +mainShape.tex.img[index].data[i + j+3];
//				if ( j < 12 ) { std::cout << " "; } else { std::cout << "\r\n"; }
//			}
//		}
		
	}
	
}


void debugColPrism( shape& mainShape ) {
	std::cout.setf( std::ios::dec, std::ios::basefield );		// The first part likes decimal
	std::cout.setf( std::ios::fixed, std::ios::floatfield );	// Always show decimal places
	std::cout.precision(6);										// Always show 6 of them
	
	for ( unsigned int i = 0; i < mainShape.col.prism.size(); i++ ) {
		std::cout <<
		mainShape.col.prism[i].unk1                                                                                             << "\r\n" <<
		mainShape.col.prism[i].indice.X << "\t" << mainShape.col.prism[i].indice.Y   << "\t" << mainShape.col.prism[i].indice.Z << "\r\n" << 
		mainShape.col.prism[i].unk2 << "\t" << mainShape.col.prism[i].unk3 << "\t" << mainShape.col.prism[i].unk4 << "\t" << mainShape.col.prism[i].unk5 << "\r\n" << 
		mainShape.col.prism[i].unk6       << "\r\n" << 
		mainShape.col.prism[i].unk7       << "\r\n" << 
		mainShape.col.prism[i].unk8       << "\r\n" << 
		mainShape.col.prism[i].unk9       << "\r\n\r\n";
	}
		
}


void debugINI( shape& mainShape ) {
	std::cout << mainShape.ini.data() << std::endl;
}
