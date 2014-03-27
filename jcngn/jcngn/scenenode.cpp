////////////////////////////////////////////////////////////////////////////////
// Filename: scenenode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "scenenode.h"


SceneNode::SceneNode(string obj_path, ID3D11Device* m_D3D)
{
	scenenode_type = OBJ_MESH;
	model = 0;	
	objImporter = 0;
	objImporter = new OBJImporter();
	objTxtPath =objImporter->ObjToTextFile((char*)obj_path.c_str());
	
	// Create the model object.
	model = new ModelClass;
	if(!model)
	{
		//TODO deal with error
	}
	
	int result = model->InitializeFromTextFile(m_D3D, (char*)objTxtPath.c_str(), L"../Engine/data/seafloor.dds");
	if(!result)
	{
		//MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		//TODO deal with error
	}

	D3DXMatrixTranslation(&translationMatrix,0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationX(&rotationMatrixX, 0.f);
	D3DXMatrixRotationY(&rotationMatrixY, 0.f);
	D3DXMatrixRotationZ(&rotationMatrixZ, 0.f);
	D3DXMatrixScaling(&scalingMatrix, 1.0f, 1.0f, 1.0f);

		renderSceneNode = true;
}

SceneNode::SceneNode(SCENENODE_TYPE type, ID3D11Device* m_D3D)
{
	scenenode_type = type;
	model = 0;	
	objImporter = 0;

	model = new ModelClass;
	if(!model)
	{
		//TODO deal with error
	}

	switch(scenenode_type)

	{
		case TRIANGLE_MESH: break;
		case PLANE_MESH:
		{
			int result = model->InitializePlane(m_D3D, L"../Engine/data/seafloor.dds");
			if(!result)
			{
				//MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
				//TODO deal with error
			}
		}; break;
	}

	D3DXMatrixTranslation(&translationMatrix,0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationX(&rotationMatrixX, 0.f);
	D3DXMatrixRotationY(&rotationMatrixY, 0.f);
	D3DXMatrixRotationZ(&rotationMatrixZ, 0.f);
	D3DXMatrixScaling(&scalingMatrix, 1.0f, 1.0f, 1.0f);
	

}


SceneNode::~SceneNode()
{
	model->Shutdown();
	delete objImporter;
}

void SceneNode::setTranslation(float x, float y, float z)
{
	D3DXMatrixTranslation(&translationMatrix,x, y, z);
}
void SceneNode::setRotationX(float angle)
{
	D3DXMatrixRotationX(&rotationMatrixX,angle);
}

void SceneNode::setRotationY(float angle)
{
	D3DXMatrixRotationY(&rotationMatrixY,angle);
}

void SceneNode::setRotationZ(float angle)
{
	D3DXMatrixRotationZ(&rotationMatrixZ,angle);
}
void SceneNode::setScale(float x, float y, float z)
{
	D3DXMatrixScaling(&scalingMatrix,x,y,z);
}

void SceneNode::getTranslation(float &x, float &y, float&z) 
{
	x = translationMatrix._41;
	y = translationMatrix._42;
	z = translationMatrix._43;
}
void SceneNode::getScale(float &x, float &y, float&z) {
	x = scalingMatrix._11;
	y = scalingMatrix._22;
	z = scalingMatrix._33;
}

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, LightShaderClass* lightShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = lightShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				       model->GetTexture(), light->GetDirection(), light->GetAmbientColor(), light->GetDiffuseColor(), 
				       camera->GetPosition(), light->GetSpecularColor(), light->GetSpecularPower());
	return result;
}