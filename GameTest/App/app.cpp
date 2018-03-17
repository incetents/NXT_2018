//---------------------------------------------------------------------------------
// App.cpp
// Implementation of the calls that are exposed via the App namespace.
//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include <string>
#include "main.h"
#include "app.h"
#include "SimpleSound.h"
#include "SimpleController.h"

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Color.h"
#include "../GameObject/CameraManager.h"

//---------------------------------------------------------------------------------
// Utils and externals for system info.
#define APP_VIRTUAL_TO_NATIVE_COORDS(_x_,_y_)			_x_ = ((_x_ / APP_VIRTUAL_WIDTH )*2.0f) - 1.0f; _y_ = ((_y_ / APP_VIRTUAL_HEIGHT)*2.0f) - 1.0f;
#define APP_NATIVE_TO_VIRTUAL_COORDS(_x_,_y_)			_x_ = ((_x_ + 1.0f) * APP_VIRTUAL_WIDTH) / 2.0f; _y_ = ((_y_ + 1.0f) * APP_VIRTUAL_HEIGHT) / 2.0f;

namespace App
{	
	void SetWireframeMode(bool state)
	{
		if (state)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void CullMode(CullType t)
	{
		switch (t)
		{
		case CullType::NONE:
			glDisable(GL_CULL_FACE);
			break;

		case CullType::COUNTER_CLOCKWISE:
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
			break;

		case CullType::CLOCKWISE:
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CW);
			break;
		}
	}

	/* !!! Conflicts with Orthographic Camera !!! //
	// Functions have been written to account for current camera matrix
	#if APP_USE_VIRTUAL_RES
	APP_VIRTUAL_TO_NATIVE_COORDS(sx, sy);
	APP_VIRTUAL_TO_NATIVE_COORDS(ex, ey);
	#endif
	*/

	// Draw Points //
	void DrawPoints(Matrix4x4 Model, Vector3* points, Color3F* colors, u_int length)
	{
		Matrix4x4 MVP = CameraManager.getMain()->getViewProjection() * Model;

		bool HasColor = (colors != nullptr);

		glBegin(GL_POINTS);
		if (HasColor)
		{
			for (u_int i = 0; i < length; i++)
			{
				Vector3 P = MVP * points[i];
				glColor3f(colors[i].r, colors[i].g, colors[i].b);
				glVertex3f(P.x, P.y, P.z);
			}
		}
		else
		{
			for (u_int i = 0; i < length; i++)
			{
				Vector3 P = MVP * points[i];
				glColor3f(1, 1, 1);
				glVertex3f(P.x, P.y, P.z);
			}
		}
		glEnd();
	}

	// Draw Point //
	void DrawPoint(float x, float y, float z, Color3F c)
	{
		glBegin(GL_POINTS);
		glColor3f(c.r, c.g, c.b);
		glVertex3f(x, y, z);
		glEnd();
	}
	void DrawPoint(Vector2 p1, Color3F color)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		DrawPoint(p1.x, p1.y, 0, color);
	}
	void DrawPoint(Vector3 p1, Color3F color)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		DrawPoint(p1.x, p1.y, p1.z, color);
	}
	void DrawPoint(Vector4 p1, Color3F color)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		DrawPoint(p1.x, p1.y, p1.z, color);
	}

	// Draw Lines //
	void DrawLine(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		Color3F c1, Color3F c2)
	{
		glBegin(GL_LINES);
		glColor3f(c1.r, c1.g, c1.b);
		glVertex3f(x1, y1, z1);
		glColor3f(c2.r, c2.g, c2.b);
		glVertex3f(x2, y2, z2);
		glEnd();
	}
	void DrawLine(Vector2 p1, Vector2 p2, Color3F c1, Color3F c2)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		p2 = P * p2;
		DrawLine(p1.x, p1.y, 0, p2.x, p2.y, 0, c1, c2);
	}
	void DrawLine(Vector3 p1, Vector3 p2, Color3F c1, Color3F c2)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		p2 = P * p2;
		DrawLine(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, c1, c2);
	}
	void DrawLine(Vector4 p1, Vector4 p2, Color3F c1, Color3F c2)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		p2 = P * p2;
		DrawLine(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, c1, c2);
	}

	void DrawTriangle(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		Color3F c1, Color3F c2, Color3F c3)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(c1.r, c1.g, c1.b);
		glVertex3f(x1, y1, z1);
		glColor3f(c2.r, c2.g, c2.b);
		glVertex3f(x2, y2, z2);
		glColor3f(c3.r, c3.g, c3.b);
		glVertex3f(x3, y3, z3);
		glEnd();
	}

	void DrawTriangle(
		Vector3 p1, Vector3 p2, Vector3 p3,
		Color3F c1, Color3F c2, Color3F c3)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		p2 = P * p2;
		p3 = P * p3;
		DrawTriangle(
			p1.x, p1.y, p1.z,
			p2.x, p2.y, p2.z,
			p3.x, p3.y, p3.z,
			c1, c2, c3
		);
	}
	void DrawTriangle(
		Vector4 p1, Vector4 p2, Vector4 p3,
		Color3F c1, Color3F c2, Color3F c3)
	{
		Matrix4x4 P = CameraManager.getMain()->getViewProjection();
		p1 = P * p1;
		p2 = P * p2;
		p3 = P * p3;
		DrawTriangle(
			p1.x, p1.y, p1.z,
			p2.x, p2.y, p2.z,
			p3.x, p3.y, p3.z,
			c1, c2, c3
		);
	}

	bool IsKeyPressed(int key)
	{
		return ((GetAsyncKeyState(key) & 0x8000) != 0);
	}

	void GetMousePos(float &x, float &y)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
		ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
		x = (float)mousePos.x;
		y = (float)mousePos.y;
		x = (x * (2.0f / WINDOW_WIDTH) - 1.0f);
		y = -(y * (2.0f / WINDOW_HEIGHT) - 1.0f);

#if APP_USE_VIRTUAL_RES		
		APP_NATIVE_TO_VIRTUAL_COORDS(x, y);
#endif
	}
	void PlaySound(const char *fileName, bool looping)
	{
		DWORD flags = (looping) ? DSBPLAY_LOOPING : 0;
		CSimpleSound::GetInstance().PlaySound(fileName, flags);
	}
	void StopSound(const char *fileName)
	{
		CSimpleSound::GetInstance().StopSound(fileName);
	}
	bool IsSoundPlaying(const char *fileName)
	{
		return CSimpleSound::GetInstance().IsPlaying(fileName);
	}
	// This prints a string to the screen
	void Print(float x, float y, const char *st, float r, float g, float b, void *font)
	{
#if APP_USE_VIRTUAL_RES		
		APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
#endif		
		// Set location to start printing text
		glColor3f(r, g, b); // Yellow
		glRasterPos2f(x, y);
		int l = (int)strlen(st);
		for (int i = 0; i < l; i++)
		{
			glutBitmapCharacter(font, st[i]); // Print a character on the screen
		}
	}
	const CController &GetController( int pad )
	{
		return CSimpleControllers::GetInstance().GetController(pad);
	}
}