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

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	cubeNode = new SceneNode("../Engine/data/cube.obj", m_D3D->GetDevice() );
	sphereNode = new SceneNode("../Engine/data/sphere.obj", m_D3D->GetDevice() );
	planeNode = new SceneNode( SCENENODE_TYPE::PLANE_MESH, m_D3D->GetDevice());
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

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	//lower = stronger
	m_Light->SetSpecularPower(1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
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

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleInput(unsigned int keyIndex){

	///To handle all key presses required
	//Codes can be found at http://www.asciitable.com/

	//cout << "HandleInput (DOWN): " << keyIndex << endl

	float camX,camY,camZ = 0.0f;
	camX = m_Camera->GetPosition().x;
	camY = m_Camera->GetPosition().y;
	camZ = m_Camera->GetPosition().z;

	float speed = 0.1f;
	switch (keyIndex)
	{		
		//movecameraforward
		//"W"
		case(87):  m_Camera->SetPosition(camX, camY,camZ+speed);break;
			
		//movecameraBack
		//"S"
		case(83): m_Camera->SetPosition(camX, camY,camZ-speed);break;

		//movecameraLeft
		//"A"
		case(65):m_Camera->SetPosition(camX-speed, camY,camZ);break;

		//movecameraRight
		//"D"
		case(68): m_Camera->SetPosition(camX+speed, camY,camZ);break;

		//movecameraup
		case(VK_SPACE): m_Camera->SetPosition(camX, camY+speed,camZ);break;

		//movecameradown
		case(VK_CONTROL): m_Camera->SetPosition(camX, camY-speed,camZ);break;

		default:cout << "HandleInput (Not handled): " << keyIndex << endl; break;
	}
	return true;

}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);		

	// Draw our meshes	
	cubeNode->setTranslation(0,-1,0);
	cubeNode->setRotationY(rotation);
	sphereNode->setTranslation(0,1,2);
	sphereNode->setRotationX(-rotation);
	result =sphereNode->Draw(m_D3D->GetDeviceContext(),worldMatrix, viewMatrix, projectionMatrix, m_LightShader, m_Light, m_Camera);
	result = cubeNode->Draw(m_D3D->GetDeviceContext(),worldMatrix, viewMatrix, projectionMatrix, m_LightShader, m_Light, m_Camera);
	
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}