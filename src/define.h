#ifndef DEFINE_H
#define DEFINE_H

#include "ansi_include.h"
	
//	enum class Chunks : u16
//    {
//        Header = 0x0000,
//
//        VertexPosition = 0x0010,
//        VertexNormal = 0x0011,
//        VertexNBT = 0x0012,
//        VertexColor = 0x0013,
//
//        VertexUV0 = 0x0018,
//        VertexUV1 = 0x0019,
//        VertexUV2 = 0x001A,
//        VertexUV3 = 0x001B,
//        VertexUV4 = 0x001C,
//        VertexUV5 = 0x001D,
//        VertexUV6 = 0x001E,
//        VertexUV7 = 0x001F,
//
//        Texture = 0x0020,
//        TextureAttribute = 0x0022,
//        Material = 0x0030,
//
//        VertexMatrix = 0x0040,
//
//        Envelope = 0x0041,
//
//        Mesh = 0x0050,
//
//        Joint = 0x0060,
//        JointName = 0x0061,
//
//        CollisionPrism = 0x0100,
//        CollisionGrid = 0x0110,
//
//        EoF = 0xFFFF
//    };

struct xyz { float X; float Y; float Z; };
struct uv { float U; float V; };
struct rgba { uint8_t R; uint8_t G; uint8_t B; uint8_t A; };
struct colPrism {
	unsigned int unk1;
	struct {
		unsigned int X;
		unsigned int Y;
		unsigned int Z;
	} indice;
	unsigned short unk2;
	unsigned short unk3;
	unsigned short unk4;
	unsigned short unk5;
	unsigned int unk6;
	unsigned int unk7;
	unsigned int unk8;
	float unk9;
};
enum GX_FMT { RGB565, CMPR, RGB5A3, I4, I8, IA4, IA8, RGBA8 };

struct shape {
	
	string filename;
	
	struct {		// 0x0000 Chunk
		unsigned int year;
		unsigned int month;
		unsigned int day;
		unsigned int unk;
	} header;
	
	struct {		// 0x0010, 0x0013 0x0011, 0x0012, 0x0018-0x001F Chunks
		vector<xyz> pos;		// 0x0010
		vector<xyz> nrm;		// 0x0011
		// nbt					// 0x0012
		vector<rgba> color0;	// 0x0013
		vector<uv> texCoord[8];	// 0x0018-0x001F
	} vtx;
	
	struct {		// 0x0020, 0x0022 Chunks
		struct attribute {
			unsigned short index;
			//palette	-1
			//tiling	repeat repeat
				// repeat, clamp or mirror wraps
			//mode	XLU / TEX
			//mipmap	off
			//max_lod	0
			//embossbump	off
		};
		struct image {
			unsigned short xRes;
			unsigned short yRes;
			GX_FMT format;
			unsigned int unk;
			vector<unsigned char> data;
		};
		
		vector<image> img;		// 0x0020
		vector<attribute> attr;	// 0x0022
		//?						// 0x0080
	} tex;
	
	// Mat
	
	struct {
		
		struct envelope { unsigned int num; vector<unsigned int> idx; vector<float> wgt; };
		
		vector<envelope> evl;
		//vector<unsigned short> vtx;
		
	} mtx;
	
	struct {		// 0x0050 Chunk
		
	} mesh;
	
	// Joint
	
	struct {		// 0x0100, 0x0110 Chunks
		unsigned int prismUnk;
		vector<colPrism> prism;
		//vector<tri>
	} col;
	
	vector<char> ini;	// Appended INI file
	
};

#endif	//DEFINE_H
