////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& other)
{
		
}


InputClass::~InputClass()
{
}


void InputClass::Initialize()
{
	int i;
	mouseX = 0;
	mouseY = 0;

	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}

void InputClass::LButtonDown(unsigned int l, unsigned int r)
{
}
void InputClass::LButtonUp(unsigned int l, unsigned int r)
{
}

void InputClass::MouseMove(int x , int y)
{
	mouseX = (int)x;
	mouseY = (int)y;
}
void InputClass::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}