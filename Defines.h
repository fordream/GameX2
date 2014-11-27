#pragma once

#define _CRT_SECURE_NO_WARNINGS

//Sleep函数所需头文件
#ifdef _MSC_VER
#include <windows.h>
#else
//#include <syswait.h>
#include <unistd.h>
#endif

// 标准模板库引用
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <fstream>
//#include <hash_map>
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <cstdlib>
using namespace std;

//直接渲染到屏幕
//GameX当不使用FBO时使用GLFW以实现跨平台
#define FBO_MODE_FOR_WINDOWS 0

//GLFW
//#if !FBO_MODE_FOR_WINDOWS
#include <GLFW/glfw3.h>
/*
#else
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
*/

/*隐藏窗口*///
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
//typedef float GLfloat;

// 一些宏
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define safe_release(p)      { if(p) { (p)->release(); (p)=NULL; } }
#define SAFE_RELEASE_ARRAY(p) { if(p) { delete[] (p); (p)=NULL; }}

//检测内存是否泄漏
#define _CRTDBG_MAP_ALLOC 
#ifdef _DEBUG
//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
 //_CrtSetBreakAlloc(5351);
#endif

//定义
const double PI = 3.1415926;

void ErrorExit(string msg);

struct RGBAData{
	unsigned char r,g,b,a;
	RGBAData(){r = g = b =a = 255;}
	RGBAData(unsigned char _a):r(255),g(255),b(255),a(_a){};
	RGBAData(unsigned char _r,unsigned char _g,unsigned char _b):r(_r),g(_g),b(_b),a(255){};
	RGBAData(unsigned char _r,unsigned char _g,unsigned char _b,unsigned char _a):r(_r),g(_g),b(_b),a(_a){};
	void Set(unsigned char _r,unsigned char _g,unsigned char _b){r=_r;g=_g;b=_b;};
	void Set(unsigned char _r,unsigned char _g,unsigned char _b,unsigned char _a){r=_r;g=_g;b=_b;a=_a;};
	//RGBAData(RGBAData const& d):r(d.r),g(d.g),b(d.b),a(d.a){};
};

template <typename T>struct Vector2X{
	T x, y;
	Vector2X() :x(0), y(0){};
	Vector2X(T _x, T _y) :x(_x), y(_y){};
};
typedef Vector2X<int> Vector2;

template <typename T>struct Vector3X{
	T x, y ,z;
	Vector3X() :x(0), y(0),z(0){};
	Vector3X(T _x, T _y,T _z) :x(_x), y(_y),z(_z){};
};
typedef Vector3X<int> Vector3;

typedef struct {
	int	width,height;
	GLuint id;
}Texture;

template<typename T>class RectX{
public:
	T left,top,right,bottom;
	T width,height;
public:
	RectX(T _x,T _y,T w,T h){
		Set(_x,_y,w,h);
	};
	void Set(T _x,T _y,T w,T h){
		left = _x;
		top = _y;
		width = w;
		height = h;
		right = _x+w;
		bottom = _y+h;
	};
};
typedef RectX<int> Rect;

//字符串处理
string ws2s(const wstring& ws);
wstring s2ws(const string& s);
