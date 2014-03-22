////////////////////////////////////////////////////////////////////////////////
// Filename: OBJImporter.h
////////////////////////////////////////////////////////////////////////////////

#ifndef _OBJ_IMPORTER_H_
#define _OBJ_IMPORTER_H_
//////////////
// INCLUDES //
//////////////
#include <iostream>
#include <fstream>
using namespace std;


//////////////
// TYPEDEFS //
//////////////
typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
class OBJImporter
{
public: 
	OBJImporter();
	~OBJImporter();

	char* ObjToTextFile (char filename[256]);
private:
	void GetModelFile(char*);
	bool ReadFileCounts(char*, int&, int&, int&, int&);
	char* LoadDataStructures(char*, int, int, int, int);

};

#endif