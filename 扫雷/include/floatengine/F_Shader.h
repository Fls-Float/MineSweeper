#pragma once
#include "raylib.hpp"
class F_Shader
{
	Shader m_shader;
public:
	F_Shader();
	F_Shader(const Shader& shader);
	void LoadFromFile(const char* vs,const char*fs);
	void LoadFromCode(const char* vs, const char* fs);
	void SetValue(const char*name,const void*value,int type);
	void SetValueTexture(const char* name, Texture texture);
	void SetrValueMatrix(const char*name,Matrix mat);
	int GetLoc(const char* name);
	void Unload();
	void Begin();
	void End();
};

