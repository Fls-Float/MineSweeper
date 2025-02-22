#pragma once
#include <iostream>
#include <vector>
#include "raylib.hpp"
class F_Font
{
	Font _rayfnt;
	unsigned char* _temp_data;
public:
	F_Font();
	F_Font(const F_Font& font);
	F_Font(const Font& _rfont);
	struct Font to_raylib_font();
	void Load(const char* filename,const char*type,int font_size,int*codepoints, int codepoints_count);
	void Unload();
};
namespace floatapi_font{
	void InitDefaultFont();
	//默认字体
	//读取raylib字体
	Font LoadFontRaylib(const char* filename, const char* type, int font_size, int*
		codepoints, int codepoints_count);
	//从data中读取raylib字体
	Font LoadFontRaylibFromData(const unsigned char* data,
		int data_size, const char* type, int font_size, int*
		codepoints, int codepoints_count);
	//读取默认中文字体
	Font LoadChineseFontDefault();

	//范围常用字符码点
	int* LoadCommonCodepoints(int&count,std::string other = "");
	//根据范围返回码点
	int* LoadCodepointsFromRange(int start, int end, int& count);
	// 返回中文字符集的所有 Unicode 码点
	int* LoadChineseCodepoints(int &count);
	// 返回日文字符集的所有 Unicode 码点
	int* LoadJapaneseCodepoints(int&count);
    // 返回法语字符集的所有 Unicode 码点
	int* LoadFrenchCodepoints(int& count);
    // 返回德语字符集的所有 Unicode 码点
    int* LoadGermanCodepoints(int& count);
    // 返回西班牙语字符集的所有 Unicode 码点
    int* LoadSpanishCodepoints(int& count);
	// 返回 ASCII 字符集的所有 Unicode 码点
	int* LoadAsciiCodepoints(int& count);
    // 返回 Emoji 字符集的所有 Unicode 码点
	int* LoadEmojiCodepoints(int& count);
    // 判断是否是有效的 Unicode 字符
	bool IsValidUnicodeCodepoint(int codepoint);
    // 返回 0 到 0xFFFF 范围内所有有效的 Unicode 码点
	int* LoadUnicodeCodepoints(int& count,bool filter=true);
    // 拼接多个 codepoints 数组
	int* ConcatenateCodepoints(int* codepoints1, int count1, int* codepoints2, int count2, int& count);
}