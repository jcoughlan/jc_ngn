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
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include <algorithm> 

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);

	D3DXVECTOR3 GetPosition();


	float GetYaw () const { return cam_yaw ; }
	void SetYaw ( float y ) ;

	float GetPitch () const { return cam_pitch ;}
	void SetPitch ( float p ) ;
	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	float m_positionX, m_positionY, m_positionZ, cam_pitch, cam_yaw;
	D3DXMATRIX m_viewMatrix;
};

#endif