////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "OBJImporter.h"
#include "scenenode.h"
#include "inputclass.h"
#include "colorshaderclass.h"
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

#define DEG_2_RAD 0.0174532925 
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool HandleInput(unsigned int keyIndex);

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	SceneNode* cubeNode;
	SceneNode* planeNode;
	SceneNode* sphereNode;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
};

#endif