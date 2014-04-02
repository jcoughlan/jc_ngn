////////////////////////////////////////////////////////////////////////////////
// Filename: md5model.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MD5_MODEL_H_
#define _MD5_MODEL_H_

//Include and link appropriate libraries and headers//
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "dxguid.lib")

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




struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
		int StartWeight;
		int WeightCount;
	};

	struct Weight
	{
		int jointID;
		float bias;
		XMFLOAT3 pos;
	};

	struct ModelSubset
	{
	int texArrayIndex;
	int numTriangles;

	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;
	std::vector<Weight> weights;

	std::vector<D3DXVECTOR3> positions;

	ID3D11Buffer* vertBuff; 
	ID3D11Buffer* indexBuff;
	};

	struct Joint
	{
	std::wstring name;
	int parentID;

	D3DXVECTOR3 pos;
	D3DXVECTOR4 orientation;
	};

	struct ModelAnimation;

	struct Model3D
	{
		int numSubsets;
		int numJoints;
		std::vector<ModelAnimation> animations;
		std::vector<Joint> joints;
		std::vector<ModelSubset> subsets;
	};


	struct BoundingBox
	{
		XMFLOAT3 min;
		XMFLOAT3 max;
	};

	struct FrameData
	{
		int frameID;
		std::vector<float> frameData;
	};
	struct AnimJointInfo
	{
		std::wstring name;
		int parentID;

		int flags;
		int startIndex;
	};

	struct ModelAnimation
	{
		int numFrames;
		int numJoints;
		int frameRate;
		int numAnimatedComponents;

		float frameTime;
		float totalAnimTime;
		float currAnimTime;

		std::vector<AnimJointInfo> jointInfo;
		std::vector<BoundingBox> frameBounds;
		std::vector<Joint>	baseFrameJoints;
		std::vector<FrameData>	frameData;
		std::vector<std::vector<Joint>> frameSkeleton;
	};
class MD5Mesh
{
public: MD5Mesh();
		~MD5Mesh();

	
	ID3D11ShaderResourceView* GetTextureAtIndex(int i);

	bool LoadMD5Model(std::wstring filename, ID3D11Device* m_D3D);
	bool Render(ID3D11DeviceContext*, int);
	void RenderBuffers(ID3D11DeviceContext*, int);

	Model3D md5Model;
private:
	
	
	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> texFileNameArray;

};

#endif