#include "scenenodelist.h"

SceneNodeList::SceneNodeList()
{
	frustum = 0;
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

void SceneNodeList::DrawAll(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, LightShaderClass* lightShader, LightClass* light, CameraClass* camera)
{
	int numSceneNodes = sceneNodes.size();

	for (int i = 0; i < numSceneNodes; i++)
	{
		if (sceneNodes.at(i)->getRenderSceneNode())
		{
			//draw
			sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, lightShader, light, camera);


		}

	}

}

void SceneNodeList::DrawAll(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, MultiTextureShaderClass* multiTextureShader, LightClass* light, CameraClass* camera)
{
	int numSceneNodes = sceneNodes.size();

	for (int i = 0; i < numSceneNodes; i++)
	{
		if (sceneNodes.at(i)->getRenderSceneNode())
		{
			//draw
			sceneNodes.at(i)->Draw(deviceContext,worldMatrix, viewMatrix, projectionMatrix, multiTextureShader, light, camera);


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