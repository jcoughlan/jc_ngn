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
// Filename: scenenode.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SCENENODE_H_
#define _SCENENODE_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "OBJImporter.h"
#include "modelclass.h"
#include "lightclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightmapshaderclass.h"
#include "multitextureshaderclass.h"
#include "alphamapshaderclass.h"
#include "bumpmapshaderclass.h"
#include "specmapshaderclass.h"
#include <d3d11.h>
#include <d3dx10math.h>
/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////

enum SCENENODE_TYPE
{
	TRIANGLE_MESH,
	PLANE_MESH,
	OBJ_MESH,
	UNKNOWN
}; 


enum SHADER_TYPE
{
	COLOR,
	TEXTURE,
	MULTI_TEXTURE,
	LIGHT,
	LIGHT_MAP,
	ALPHA_MAP,
	BUMP_MAP,
	SPEC_MAP,
	SHADER_UNKNOWN
};

class SceneNode
{
public: 
		SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR*, SHADER_TYPE );
		SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR* ,  WCHAR*,SHADER_TYPE );
		SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR* ,  WCHAR*, WCHAR*, SHADER_TYPE );
		SceneNode(SCENENODE_TYPE, ID3D11Device* m_D3D, WCHAR*,SHADER_TYPE);
		SceneNode(SCENENODE_TYPE, ID3D11Device* m_D3D, WCHAR*,WCHAR*,SHADER_TYPE);
		SceneNode(SCENENODE_TYPE, ID3D11Device* m_D3D,WCHAR*,WCHAR*,WCHAR*, SHADER_TYPE);
		~SceneNode();

		ModelClass* GetModel(){ return model;}
		bool Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, MultiTextureShaderClass* multiTextureShader, LightClass* light, CameraClass* camera);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, LightShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, LightMapShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, TextureShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, ColorShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, AlphaMapShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, BumpMapShaderClass*, LightClass*, CameraClass*);
		bool Draw(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX,  D3DXMATRIX, SpecMapShaderClass*, LightClass*, CameraClass*);
		
		void setTranslation(float x, float y, float z);
		void setRotationX(float angle);
		void setRotationY(float angle);
		void setRotationZ(float angle);
		void setRenderSceneNode(bool render){renderSceneNode = render;}
		void setScale(float x, float y, float z);
		void getTranslation(float &x, float &y, float&z); 		
		void getScale(float &x, float &y, float&z);
		bool getRenderSceneNode() { return renderSceneNode;}
		SHADER_TYPE getShaderType() {return shader_type;}
	
private:
	string objTxtPath;
	ModelClass* model;
	OBJImporter* objImporter;
	SCENENODE_TYPE scenenode_type;
	bool renderSceneNode;
	D3DXMATRIX translationMatrix;
	D3DXMATRIX rotationMatrixX;
	D3DXMATRIX rotationMatrixY;
	D3DXMATRIX rotationMatrixZ;
	D3DXMATRIX scalingMatrix;
	SHADER_TYPE shader_type;
};

#endif