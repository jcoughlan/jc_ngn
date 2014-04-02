////////////////////////////////////////////////////////////////////////////////
// Filename: scenenode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "scenenode.h"


SceneNode::SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR* textureLoc, SHADER_TYPE sh_type)
{
	scenenode_type = OBJ_MESH;
	shader_type = sh_type;
	model = 0;	
	md5Mesh = 0;
	objImporter = 0;
	objImporter = new OBJImporter();
	objTxtPath =objImporter->ObjToTextFile((char*)obj_path.c_str());
	
	// Create the model object.
	model = new ModelClass;
	if(!model)
	{
		//TODO deal with error
	}
	
	int result = model->InitializeFromTextFile(m_D3D, (char*)objTxtPath.c_str(), textureLoc);
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

SceneNode::SceneNode(string md5_path, ID3D11Device* m_D3D, SHADER_TYPE sh_type)
{
	shader_type = sh_type;
	scenenode_type = MD5_MESH;
	model = 0;	
	md5Mesh = 0;
	objImporter = 0;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wfilename = converter.from_bytes(md5_path.c_str());
	md5Mesh = new MD5Mesh();
	md5Mesh->LoadMD5Model(wfilename, m_D3D);


	D3DXMatrixTranslation(&translationMatrix,0.0f, 0.0f, 0.0f);
	D3DXMatrixRotationX(&rotationMatrixX, 0.f);
	D3DXMatrixRotationY(&rotationMatrixY, 0.f);
	D3DXMatrixRotationZ(&rotationMatrixZ, 0.f);
	D3DXMatrixScaling(&scalingMatrix, 1.0f, 1.0f, 1.0f);
}

SceneNode::SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR* textureLoc1, WCHAR* textureLoc2, SHADER_TYPE sh_type)
{
	shader_type = sh_type;
	scenenode_type = OBJ_MESH;
	model = 0;	
	md5Mesh = 0;
	objImporter = 0;
	objImporter = new OBJImporter();
	objTxtPath =objImporter->ObjToTextFile((char*)obj_path.c_str());
	
	// Create the model object.
	model = new ModelClass;
	if(!model)
	{
		//TODO deal with error
	}
	
	int result = model->InitializeFromTextFile(m_D3D, (char*)objTxtPath.c_str(), textureLoc1, textureLoc2);
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

SceneNode::SceneNode(string obj_path, ID3D11Device* m_D3D, WCHAR* textureLoc1, WCHAR* textureLoc2,WCHAR* textureLoc3, SHADER_TYPE sh_type)
{
	shader_type = sh_type;
	scenenode_type = OBJ_MESH;
	model = 0;	
	md5Mesh = 0;
	objImporter = 0;
	objImporter = new OBJImporter();
	objTxtPath =objImporter->ObjToTextFile((char*)obj_path.c_str());
	
	// Create the model object.
	model = new ModelClass;
	if(!model)
	{
		//TODO deal with error
	}
	
	int result = model->InitializeFromTextFile(m_D3D, (char*)objTxtPath.c_str(), textureLoc1, textureLoc2, textureLoc3);
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
SceneNode::SceneNode(SCENENODE_TYPE type, ID3D11Device* m_D3D , WCHAR* textureLoc1, SHADER_TYPE sh_type)
{
	scenenode_type = type;
	shader_type = sh_type;
	model = 0;	
	md5Mesh = 0;
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
			int result = model->InitializePlane(m_D3D, textureLoc1);
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

SceneNode::SceneNode(SCENENODE_TYPE type, ID3D11Device* m_D3D , WCHAR* textureLoc1, WCHAR* textureLoc2, SHADER_TYPE sh_type)
{
	scenenode_type = type;
	shader_type = sh_type;
	model = 0;	
	md5Mesh = 0;
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
			int result = model->InitializePlane(m_D3D, textureLoc1, textureLoc2);
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



SceneNode::SceneNode(SCENENODE_TYPE type,  ID3D11Device* m_D3D ,WCHAR* textureLoc1, WCHAR* textureLoc2, WCHAR* textureLoc3,SHADER_TYPE sh_type)
{
	scenenode_type = type;
	shader_type = sh_type;
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
			int result = model->InitializePlane(m_D3D, textureLoc1, textureLoc2, textureLoc3);
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

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, MultiTextureShaderClass* multiTextureShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = multiTextureShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		model->GetTextureArray());
	return result;
}

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, LightMapShaderClass* lightMapShaderClass, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = lightMapShaderClass->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		model->GetTextureArray());
	return result;
}

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, TextureShaderClass* textureShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = textureShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		model->GetTexture());
	return result;
}


bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, ColorShaderClass* colorShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = colorShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	return result;
}


bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, AlphaMapShaderClass* alphaMapShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = alphaMapShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTextureArray());
	return result;
}

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, BumpMapShaderClass* bumpMapShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = bumpMapShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTextureArray(), light->GetDirection(), light->GetDiffuseColor());
	return result;
}

bool SceneNode::Draw(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, SpecMapShaderClass* specMapShader, LightClass* light, CameraClass* camera)
{
	model->Render(deviceContext);

	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
	worldMatrix = modelMatrix*worldMatrix;
	// Render the model using the light shader.
	bool result = specMapShader->Render(deviceContext, model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, model->GetTextureArray(),light->GetDirection(), light->GetDiffuseColor(), 
				camera->GetPosition(), light->GetSpecularColor(), light->GetSpecularPower());
	return result;
}

bool SceneNode::DrawMD5(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, LightShaderClass* lightShader, LightClass* light, CameraClass* camera)
{
	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
		worldMatrix = modelMatrix*worldMatrix;
	for (int i = 0; i < md5Mesh->md5Model.numSubsets; i++)
	{
		md5Mesh->Render(deviceContext, i);

		
		// Render the model using the light shader.
		bool result = lightShader->Render(deviceContext, md5Mesh->md5Model.subsets.at(i).indices.size(), worldMatrix, viewMatrix, projectionMatrix, 
			md5Mesh->GetTextureAtIndex(md5Mesh->md5Model.subsets.at(i).texArrayIndex), light->GetDirection(), light->GetAmbientColor(), light->GetDiffuseColor(), 
						   camera->GetPosition(), light->GetSpecularColor(), light->GetSpecularPower());
	
	}
	return true;
}



bool SceneNode::DrawMD5(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,  D3DXMATRIX projectionMatrix, TextureShaderClass* textureShader, LightClass* light, CameraClass* camera)
{
	D3DXMATRIX modelMatrix = ( rotationMatrixX * rotationMatrixY * rotationMatrixZ *translationMatrix* scalingMatrix);
		worldMatrix = modelMatrix*worldMatrix;
	for (int i = 0; i < md5Mesh->md5Model.numSubsets; i++)
	{
		md5Mesh->Render(deviceContext, i);

		
		// Render the model using the light shader.
		bool result = textureShader->Render(deviceContext, md5Mesh->md5Model.subsets.at(i).indices.size(), worldMatrix, viewMatrix, projectionMatrix, 
			md5Mesh->GetTextureAtIndex(md5Mesh->md5Model.subsets.at(i).texArrayIndex));
	
	}
	return true;
}

