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
																															 27/03/2014
 */

////////////////////////////////////////////////////////////////////////////////
// Filename: scenenode.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SCENENODELIST_H_
#define _SCENENODELIST_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "scenenode.h"
#include "frustumclass.h"
#include <vector>

using namespace std;
/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////

class SceneNodeList
{
public: SceneNodeList();
		~SceneNodeList();
		void Shutdown();
		void AddSceneNode(SceneNode* sceneNode);
		void Sort();
		void SetFrustum(FrustumClass* f){ frustum = f;}
		
		void DrawAll(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, CameraClass* camera);
		
		void SetLight(LightClass* l);
		void SetLightShader(LightShaderClass* lightSh);
		void SetLightMapShader(LightMapShaderClass* lightMapSh);
		void SetColorShader(ColorShaderClass* colorSh);
		void SetTextureShader(TextureShaderClass* texSh);
		void SetMultiTextureShader(MultiTextureShaderClass* multiTexSh);
private:
	bool TestAgainstFrustum(SceneNode* sceneNode);
	vector<SceneNode*> sceneNodes;
	FrustumClass* frustum;

	LightClass* light;
	LightMapShaderClass* lightMapShader;
	ColorShaderClass* colorShader;
	TextureShaderClass* textureShader;
	LightShaderClass* lightShader;
	MultiTextureShaderClass* multiTextureShader;
};
#endif