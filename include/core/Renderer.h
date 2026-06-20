#pragma once
#include "graphics/Opengl.h"

class Renderer
{
private:
	OpenGL* m_opengl{};
public:
	Renderer(OpenGL* opengl)
		: m_opengl(opengl) {};

	~Renderer() = default;
	void onResize(int width, int height); 
	void Render();
	void Update(float dt);
};
