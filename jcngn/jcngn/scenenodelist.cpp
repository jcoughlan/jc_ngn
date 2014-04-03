#include "scenenodelist.h"

SceneNodeList::SceneNodeList()
{
	frustum = 0;
	light =  0;
	lightMapShader = 0;
	colorShader = 0;
	textureShader = 0;
	lightShader = 0;
	multiTextureShader = 0;
	alphaMapShader = 0;
}
SceneNodeList::~SceneNodeList()
{

}
void SceneNodeList::AddSceneNode(SceneNode* sceneNode)
{
	sceneNodes.push_back(sceneNode);
}

void SceneNodeList::Shutdown()
{
	sceneNodes.clear();
	frustum = 0;
}
void SceneNodeList::Sort()
{
	//test if they are in the frustum
	int numSceneNodes = sceneNodes.size();
	for (int i = 0; i < numSceneNodes; i++)
	{
		if (TestAgainstFrustum(sceneNodes.at(i)))		
			sceneNodes.at(i)->setRenderSceneNode(true);
		else
			sceneNodes.at(i)->setRenderSceneNode(false);
	}


	//sort according to distance from camera
}

void SceneNodeList::DrawAll(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix,  CameraClass* camera)
{
	int numSceneNodes = sceneNodes.size();

	for (int i = 0; i < numSceneNodes; i++)
	{


		if (sceneNodes.at(i)->getRenderSceneNode())
		{
			//draw
			if (sceneNodes.at(i)->getSceneNodeType() == MD5_MESH)
			{			
				
				switch (sceneNodes.at(i)->getShaderType())
				{
					case TEXTURE:if (textureShader)sceneNodes.at(i)->DrawMD5(deviceContext,worldMatrix, viewMatrix, projectionMatrix, textureShader, light, camera); break;
					case LIGHT: if (lightShader&&light)sceneNodes.at(i)->DrawMD5(deviceContext,worldMatrix, viewMatrix, projectionMatrix, lightShader, light, camera); break	;				
				}
			}
			else
			{

				switch (sceneNodes.at(i)->getShaderType())
				{
					case SHADER_UNKNOWN: break;
					case COLOR: break;
					case TEXTURE: if (textureShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, textureShader, light, camera);break;
					case LIGHT: if (lightShader && light)sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, lightShader, light, camera); break;
					case MULTI_TEXTURE: if (multiTextureShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, multiTextureShader, light, camera); break;
					case LIGHT_MAP: if (lightMapShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, lightMapShader, light, camera); break;
					case ALPHA_MAP: if (alphaMapShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, alphaMapShader, light, camera); break;
					case BUMP_MAP: if (bumpMapShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, bumpMapShader, light, camera); break;
					case SPEC_MAP: if (specMapShader) sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, specMapShader, light, camera); break;
				}
			}
		}
			

	}
}


bool SceneNodeList::TestAgainstFrustum(SceneNode* sceneNode)
{
	if (frustum)
	{
		bool renderModel = true;
		float posX,posY,posZ,scaleX, scaleY, scaleZ, radius = 0;
		sceneNode->getTranslation(posX, posY, posZ);
	sceneNode->getScale(scaleX, scaleY, scaleZ);

	radius = max(scaleX,scaleY);
	radius = max(scaleZ, radius);

	renderModel = frustum->CheckSphere(posX, posY, posZ, radius);
		if (!renderModel)
			return false;
	}

	return true;
}

void SceneNodeList::SetLightShader(LightShaderClass* lightSh)
{
	lightShader = lightSh;
}
void SceneNodeList::SetLightMapShader(LightMapShaderClass* lightMapSh)
{
	lightMapShader = lightMapSh;
}
void SceneNodeList::SetColorShader(ColorShaderClass* colorSh)
{
	colorShader = colorSh;
}
void SceneNodeList::SetTextureShader(TextureShaderClass* texSh)
{
		textureShader = texSh;
}
void SceneNodeList::SetMultiTextureShader(MultiTextureShaderClass* multiTexSh)
{
	multiTextureShader = multiTexSh;
}
void  SceneNodeList::SetAlphaMapShader(AlphaMapShaderClass* alphaMapSh)
{
	alphaMapShader = alphaMapSh;
}

void  SceneNodeList::SetBumpMapShader(BumpMapShaderClass* bumpMapSh)
{
	bumpMapShader = bumpMapSh;
}

void  SceneNodeList::SetSpecMapShader(SpecMapShaderClass* specMapSh)
{
	specMapShader = specMapSh;
}
void SceneNodeList::SetLight(LightClass* l)
{
	light = l;
}