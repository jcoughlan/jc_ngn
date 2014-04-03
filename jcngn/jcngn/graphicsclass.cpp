////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	cubeNode = 0;
	sphereNode = 0;
	planeNode = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Bitmap = 0;
	m_TextureShader = 0;
	m_Text = 0;
	m_sceneNodeList = 0;
	m_Frustum = 0;
	m_MultiTextureShader = 0;
	m_BumpMapShader = 0;
	m_LightMapShader = 0;
	m_AlphaMapShader = 0;
	m_SpecMapShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_sceneNodeList = new SceneNodeList();

	InitializeShaders(screenWidth, screenHeight, hwnd, baseViewMatrix);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.

	m_Camera->SetPosition(0.0f, 3.0f, -10.0f);
	cubeNode = new SceneNode("../Engine/data/cube.obj", m_D3D->GetDevice(),    L"../Engine/data/stone02.dds", 
				     L"../Engine/data/bump02.dds", L"../Engine/data/spec02.dds", SPEC_MAP);

	sphereNode = new SceneNode("../Engine/data/sphere.obj", m_D3D->GetDevice(),  L"../Engine/data/stone01.dds", LIGHT);

	planeNode = new SceneNode( PLANE_MESH, m_D3D->GetDevice(),  L"../Engine/data/stone01.dds", 
				     L"../Engine/data/bump01.dds",BUMP_MAP);
	

	md5Node = new SceneNode("../Engine/data/md5Bob/bob_lamp_update_export.md5mesh", m_D3D->GetDevice(), LIGHT);
	md5Anim = new MD5Anim();

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wfilename = converter.from_bytes("../Engine/data/md5Bob/bob_lamp_update_export.md5anim");
	md5Anim->LoadMD5Anim(wfilename, md5Node->GetMD5Mesh()->md5Model);
	//m_sceneNodeList->AddSceneNode(cubeNode);
	//m_sceneNodeList->AddSceneNode(sphereNode);
	//m_sceneNodeList->AddSceneNode(planeNode);
	m_sceneNodeList->AddSceneNode(md5Node);

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.2f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	//lower = stronger
	m_Light->SetSpecularPower(20.f);

	lastMousePos[0] = 0.0;
	lastMousePos[1] = 0.0;

	//set our light
	m_sceneNodeList->SetLight(m_Light);
	//set all of our shaders
	m_sceneNodeList->SetBumpMapShader(m_BumpMapShader);
	m_sceneNodeList->SetSpecMapShader(m_SpecMapShader);
	m_sceneNodeList->SetTextureShader(m_TextureShader);
	m_sceneNodeList->SetLightMapShader(m_LightMapShader);
	m_sceneNodeList->SetLightShader(m_LightShader);
	m_sceneNodeList->SetMultiTextureShader(m_MultiTextureShader);
	m_sceneNodeList->SetAlphaMapShader(m_AlphaMapShader);
	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light map shader object.
	if(m_LightMapShader)
	{
		m_LightMapShader->Shutdown();
		delete m_LightMapShader;
		m_LightMapShader = 0;
	}

	// Release the specular map shader object.
	if(m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	// Release the bump map shader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the alpha map shader object.
	if(m_AlphaMapShader)
	{
		m_AlphaMapShader->Shutdown();
		delete m_AlphaMapShader;
		m_AlphaMapShader = 0;
	}

	// Release the multitexture shader object.
	if(m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	if(m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	if(m_sceneNodeList)
	{
		m_sceneNodeList->Shutdown();
		delete m_sceneNodeList;
		m_sceneNodeList = 0;
	}
	 

	// Release the bitmap object.
	if(m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(sphereNode)
	{
		//TODO shutdown
		delete sphereNode;
		sphereNode = 0;
	}

	if(cubeNode)
	{
		//TODO shutdown
		delete cubeNode;
		cubeNode = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}



bool GraphicsClass::DrawPerspective()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool  result = false;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);		

	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);
	m_sceneNodeList->SetFrustum(m_Frustum);
	// Draw our meshes	
		
	sphereNode->setTranslation(0,1,2);
	cubeNode->setTranslation(0,-1,0);

	planeNode->setRotationX((float)(90 * DEG_2_RAD));
	planeNode->setScale(2.0,2.0,2.0);
	planeNode->setTranslation(0,-2,0);

	md5Node->setScale(1,1,1);
	m_sceneNodeList->Sort();

	m_sceneNodeList->DrawAll(m_D3D->GetDeviceContext(),worldMatrix, viewMatrix, projectionMatrix,  m_Camera);
	
	
	return true;

}

bool GraphicsClass::DrawOrthographic(int fps, int cpu)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->TurnZBufferOff();
	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	/*result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	if(!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if(!result)
	{
		return false;
	}*/
	
	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	
	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.f, 0.f, 0.f, 1.0f);
	// Render the perspective scene scene.

	result = DrawOrthographic(fps, cpu);
	if(!result)
	{
		return false;
	}
	result = DrawPerspective();
	if(!result)
	{
		return false;
	}


	
	md5Anim->UpdateMD5Model(md5Node->GetMD5Mesh()->md5Model, frameTime/600, 0, m_D3D->GetDeviceContext());
	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::HandleMouseInput(int mouseX, int mouseY)
{	
	float speed = MOUSE_CAMERA_SPEED;
	float yaw, pitch;
	yaw = m_Camera->GetYaw();
	pitch = m_Camera->GetPitch();
	m_Camera->SetPitch(pitch +(mouseY* speed));
	m_Camera->SetYaw(yaw + (mouseX* speed));
	return true;
}

bool GraphicsClass::HandleKeyboardInput(unsigned int keyIndex){

	///To handle all key presses required
	//Codes can be found at http://www.asciitable.com/

	//cout << "HandleInput (DOWN): " << keyIndex << endl


	float camX,camY,camZ = 0.0f;
	camX = m_Camera->GetPosition().x;
	camY = m_Camera->GetPosition().y;
	camZ = m_Camera->GetPosition().z;
	float offset =KEYBOARD_CAMERA_SPEED;

	float pitch = m_Camera->GetPitch();
	float yaw   =m_Camera->GetYaw();

	float pitchRadian =(float)( pitch * (PI / 180)); // X rotation
	float yawRadian   =(float)(yaw   * (PI / 180)); // Y rotation

	float newPosX = offset *  sinf( yawRadian ) * cosf( pitchRadian );
	float newPosY = offset * -sinf( pitchRadian );
	float newPosZ = offset *  cosf( yawRadian ) * cosf( pitchRadian );	

	yawRadian   =(float)((yaw+90)   * (PI / 180));
	float otherPosX = offset *  sinf( yawRadian ) * cosf( pitchRadian );
	float otherPosY = offset * -sinf( pitchRadian );
	float otherPosZ = offset *  cosf( yawRadian ) * cosf( pitchRadian );	


	switch (keyIndex)
	{		
		//movecameraforward
		//"W"
	case(87):  m_Camera->SetPosition(camX + newPosX, camY + newPosY,camZ+newPosZ);break;
			
		//movecameraBack
		//"S"
		case(83): m_Camera->SetPosition(camX-newPosX, camY-newPosY,camZ-newPosZ);break;

		//movecameraLeft
		//"A"
		case(65):m_Camera->SetPosition(camX -otherPosX, camY -otherPosY,camZ -otherPosZ);break;

		//movecameraRight
		//"D"
		case(68): m_Camera->SetPosition(camX +otherPosX, camY +otherPosY,camZ +otherPosZ);break;

		//movecameraup
		case(VK_SPACE): m_Camera->SetPosition(camX, camY+offset,camZ);break;

		//movecameradown
		case(VK_CONTROL): m_Camera->SetPosition(camX, camY-offset, camZ);break;

		default:cout << "HandleInput (Not handled): " << keyIndex << endl; break;
	}
	return true;

}


bool GraphicsClass::InitializeShaders(int screenWidth, int screenHeight,HWND hwnd, D3DMATRIX& baseViewMatrix)
{
	bool result = false;
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if(!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/seafloor.dds", 256, 256);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if(!m_Frustum)
	{
		return false;
	}

	// Create the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShaderClass;
	if(!m_MultiTextureShader)
	{
		return false;
	}

	// Initialize the multitexture shader object.
	result = m_MultiTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}

// Create the light map shader object.
	m_LightMapShader = new LightMapShaderClass;
	if(!m_LightMapShader)
	{
		return false;
	}

	// Initialize the light map shader object.
	result = m_LightMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the alpha map shader object.
	m_AlphaMapShader = new AlphaMapShaderClass;
	if(!m_AlphaMapShader)
	{
		return false;
	}

	// Initialize the alpha map shader object.
	result = m_AlphaMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the alpha map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the bump map shader object.
	result = m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the specular map shader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if(!m_SpecMapShader)
	{
		return false;
	}

	// Initialize the specular map shader object.
	result = m_SpecMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}
}

