////////////////////////////////////////////////////////////////////////////////
// Filename: md5anim.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MD5_ANIM_H_
#define _MD5_ANIM_H_


#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>
#include <vector>
#include <fstream>
#include <istream>
#include <iostream>

#include "md5model.h"

class MD5Anim
{

public:
	MD5Anim();
	~MD5Anim();
	void UpdateMD5Model(Model3D& MD5Model, float deltaTime, int animation, ID3D11DeviceContext* deviceContext);
	bool LoadMD5Anim(std::wstring filename,	Model3D& MD5Model);
private:
	
};

#endif