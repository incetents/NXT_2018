#pragma once

#include "../Utility/Singleton.h"

class VertexArray;

static class SimpleShapes : public Singleton<class SimpleShapes>
{
protected:
	bool isInit = false;

	void createCube();
	void createBox();
	void createBoxLeft(); // offset anchor to left
	void createBoxRight(); // offset anchor to right
	void createTriangle();
	void createCircle();
public:
	VertexArray* v_cube;
	VertexArray* v_box;
	VertexArray* v_box_left;
	VertexArray* v_box_right;
	VertexArray* v_tri;
	VertexArray* v_circle;

	void Init();
	SimpleShapes();


} &SimpleShapes = Singleton<class SimpleShapes>::instanceRef;
