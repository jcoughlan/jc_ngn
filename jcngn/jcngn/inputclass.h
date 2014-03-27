////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	void LButtonDown(unsigned int, unsigned int);
	void LButtonUp(unsigned int, unsigned int);

	void MouseMove(int, int);
	
	inline void GetMouseCoords(int& x,int &y)
	{
		x = mouseX; 
		y = mouseY;		
	}
	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
	int mouseX, mouseY;
};

#endif