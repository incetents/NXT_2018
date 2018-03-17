#pragma once

#include <vector>
#include "Camera.h"

#include "../Utility/Singleton.h"
#include "../App/AppSettings.h"

static class CameraManager : Singleton<class CameraManager>
{
private:
	std::vector<Camera*> m_cameras;
	Camera* main; // Camera in use
public:
	CameraManager()
	{
		main = Camera::createOrthographic(
			-APP_VIRTUAL_WIDTH*0.5f, +APP_VIRTUAL_WIDTH*0.5f,
			-APP_VIRTUAL_HEIGHT*0.5f, +APP_VIRTUAL_HEIGHT*0.5f,
			-1000.0f, 1000.0f);

		m_cameras.push_back(main);
	}

	inline void		setMain(Camera* cam)
	{
		main = cam;
	}
	inline Camera*	getMain() const
	{
		return main;
	}


} &CameraManager = Singleton<class CameraManager>::instanceRef;