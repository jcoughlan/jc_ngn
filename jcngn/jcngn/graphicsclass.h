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
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "bitmapclass.h"
#include "scenenodelist.h"
#include "d3dclass.h"
#include "textureshaderclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "OBJImporter.h"
#include "md5anim.h"
#include "scenenode.h"
#include "inputclass.h"
#include "textclass.h"
#include "colorshaderclass.h"
#include "multitextureshaderclass.h"
#include "frustumclass.h"
#include "lightmapshaderclass.h"
#include "alphamapshaderclass.h"
#include "bumpmapshaderclass.h"
#include "specmapshaderclass.h"
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

#define DEG_2_RAD 0.0174532925 
#define PI 3.14159265359
/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float KEYBOARD_CAMERA_SPEED = 0.1f;
const float MOUSE_CAMERA_SPEED = 0.1f;
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
	bool DrawOrthographic(int fps, int cpu);
	bool DrawPerspective();
	bool Frame(int fps, int cpu, float frameTime);
	bool HandleKeyboardInput(unsigned int keyIndex);
	bool HandleMouseInput(int mouseX, int mouseY);
	bool InitializeShaders(int, int, HWND, D3DMATRIX&);

private:
	float lastMousePos[2];
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	SceneNode* cubeNode;
	SceneNode* planeNode;
	SceneNode* sphereNode;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	TextureShaderClass* m_TextureShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	TextClass* m_Text;	
	FrustumClass* m_Frustum;
	SceneNodeList* m_sceneNodeList;
	LightMapShaderClass* m_LightMapShader;
	BumpMapShaderClass* m_BumpMapShader;
	AlphaMapShaderClass* m_AlphaMapShader;
	SpecMapShaderClass* m_SpecMapShader;

	SceneNode* md5Node;
	MD5Anim* md5Anim;
};

#endif