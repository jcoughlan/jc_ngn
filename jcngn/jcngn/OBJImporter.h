/*
                 __________________ _______  _______          
                 \__    _/\__   __/(       )(       )|\     /|                       									******WEBSITE*******               
                    )  (     ) (   | () () || () () |( \   / )															https://www.jamescoughlan.com
                    |  |     | |   | || || || || || | \ (_) / 															*******GITHUB*******
                    |  |     | |   | |(_)| || |(_)| |  \   /  															https://github.com/jcoughlan/
                    |  |     | |   | |   | || |   | |   ) (   															********EMAIL*******
                 |\_)  )  ___) (___| )   ( || )   ( |   | |   															coughlan.james@outlook.com
                 (____/   \_______/|/     \||/     \|   \_/   
                                                              
     _______  _______  _______  _        _______  _______  _______  _______ 
    (  ____ \(  ___  )(  ____ )( \      (  ___  )(  ___  )(  ____ )(  ____ \
    | (    \/| (   ) || (    )|| (      | (   ) || (   ) || (    )|| (    \/
    | (__    | |   | || (____)|| |      | |   | || |   | || (____)|| (_____ 
    |  __)   | |   | ||     __)| |      | |   | || |   | ||  _____)(_____  )
    | (      | |   | || (\ (   | |      | |   | || |   | || (            ) |
    | )      | (___) || ) \ \__| (____/\| (___) || (___) || )      /\____) |
    |/       (_______)|/   \__/(_______/(_______)(_______)|/       \_______)											********DATE********
                                                                            
 */
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
#include <stdio.h>
#include <string.h>
#include <cstring>
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

	string ObjToTextFile (char filename[256]);
private:
	void GetModelFile(char*);
	bool ReadFileCounts(char*, int&, int&, int&, int&);
	string LoadDataStructures(char*, int, int, int, int, char*);
	bool fexists(const char *filename)
	{
	 ifstream ifile(filename);
		return ifile;
	}
};

#endif