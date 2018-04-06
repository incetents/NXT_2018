#pragma once

#include "../Utility/Singleton.h"

class VertexArray;

static class SimpleShapes : public Singleton<class SimpleShapes>
{
protected:
	bool isInit = false;

	void createBox();
	void createTriangle();
	void createCircle();
public:
	VertexArray* v_box;
	VertexArray* v_tri;
	VertexArray* v_circle;

	void Init();
	SimpleShapes();


} &SimpleShapes = Singleton<class SimpleShapes>::instanceRef;
