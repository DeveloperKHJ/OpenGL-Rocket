#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices


static const GLfloat g_axis_vertex_data[] =
{
	0.0f, 0.0f, 0.0f,
	1000.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 
	0.0f, 1000.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1000.0f
};

static const GLfloat g_axis_color_data[] =
{
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f
};

static const GLfloat g_circle_vertex_data[] =
{
	0.0f, 0.0f, 0.0f,
	50.0f, 0.0f, 0.0f,
	40.45f, 0.0f, 29.38f,

	0.0f, 0.0f, 0.0f,
	40.45f, 0.0f, 29.38f,
	15.45f, 0.0f, 47.55f,

	0.0f, 0.0f, 0.0f,
	15.45f, 0.0f, 47.55f,
	-15.45f, 0.0f, 47.55f,

	0.0f, 0.0f, 0.0f,
	-15.45f, 0.0f, 47.55f,
	-40.45, 0.0f, 29.38f,

	0.0f, 0.0f, 0.0f,
	-40.45, 0.0f, 29.38f,
	-50.0f, 0.0f, 0.0f,

	0.0f, 0.0f, 0.0f,
	-50.0f, 0.0f, 0.0f,
	-40.45f, 0.0f, -29.38f,

	0.0f, 0.0f, 0.0f,
	-40.45f, 0.0f, -29.38f,
	-15.45f, 0.0f, -47.55f,
	
	0.0f, 0.0f, 0.0f,
	-15.45f, 0.0f, -47.55f,
	15.45f, 0.0f, -47.55f,

	0.0f, 0.0f, 0.0f,
	15.45f, 0.0f, -47.55f,
	40.45f, 0.0f, -29.38f,

	0.0f, 0.0f, 0.0f,
	40.45f, 0.0f, -29.38f,
	50.0f, 0.0f, 0.0
};

static const GLfloat g_circle_uv_data[] =
{
	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 0.0f,
	0.25f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.25f,
	0.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.75f,
	0.25f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 1.0f,
	0.5f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 1.0f,
	0.75f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.75f,
	1.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.25f,
	0.75f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f
};

float height = 100.0f;
static const GLfloat g_cone_vertex_data[]
{
	0.0f, 350.0f+height, 0.0f,
	50.0f, 350.0f, 0.0f,
	40.45f, 350.0f, 29.38f,

	0.0f, 350.0f + height, 0.0f,
	40.45f, 350.0f, 29.38f,
	15.45f, 350.0f, 47.55f,

	0.0f, 350.0f + height, 0.0f,
	15.45f, 350.0f, 47.55f,
	-15.45f, 350.0f, 47.55f,

	0.0f, 350.0f + height, 0.0f,
	-15.45f, 350.0f, 47.55f,
	-40.45, 350.0f, 29.38f,

	0.0f, 350.0f + height, 0.0f,
	-40.45, 350.0f, 29.38f,
	-50.0f, 350.0f, 0.0f,

	0.0f, 350.0f + height, 0.0f,
	-50.0f, 350.0f, 0.0f,
	-40.45f, 350.0f, -29.38f,

	0.0f, 350.0f + height, 0.0f,
	-40.45f, 350.0f, -29.38f,
	-15.45f, 350.0f, -47.55f,

	0.0f, 350.0f + height, 0.0f,
	-15.45f, 350.0f, -47.55f,
	15.45f, 350.0f, -47.55f,

	0.0f, 350.0f + height, 0.0f,
	15.45f, 350.0f, -47.55f,
	40.45f, 350.0f, -29.38f,

	0.0f, 350.0f + height, 0.0f,
	40.45f, 350.0f, -29.38f,
	50.0f, 350.0f, 0.0
};

static const GLfloat g_cone_uv_data[] =
{
	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 0.0f,
	0.25f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.25f,
	0.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.75f,
	0.25f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 1.0f,
	0.5f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 1.0f,
	0.75f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.75f,
	1.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.25f,
	0.75f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f
};

float cylinderHeight = 350.0f;
static const GLfloat g_cylinder_data[]=
{
	//// plane 0
	50.0f, cylinderHeight, 0.0f,
	50.0f, 0.0f, 0.0f,
	40.45f, 0.0f, 29.38f,

	50.0f, cylinderHeight, 0.0f,
	40.45f, 0.0f, 29.38f,
	40.45f, cylinderHeight, 29.38f,
	//// plane 1
	40.45f, cylinderHeight, 29.38f,
	40.45f, 0.0f, 29.38f,
	15.45f, 0.0f, 47.55f,

	40.45f, cylinderHeight, 29.38f,
	15.45f, 0.0f, 47.55f,
	15.45f, cylinderHeight, 47.55f,
	//// plane 2
	15.45f, cylinderHeight, 47.55f,
	15.45f, 0.0f, 47.55f,
	-15.45f, 0.0f, 47.55f,

	15.45f, cylinderHeight, 47.55f,
	-15.45f, 0.0f, 47.55f,
	-15.45f, cylinderHeight, 47.55f,
	///// plane 3
	-15.45f, cylinderHeight, 47.55f,
	-15.45f, 0.0f, 47.55f,
	-40.45f, 0.0f, 29.38f,

	-15.45f, cylinderHeight, 47.55f,
	-40.45f, 0.0f, 29.38f,
	-40.45f, cylinderHeight, 29.38f,
	///// plane 4
	-40.45f, cylinderHeight, 29.38f,
	-40.45f, 0.0f, 29.38f,
	-50.0f, 0.0f, 0.0f,

	-40.45f, cylinderHeight, 29.38f,
	-50.0f, 0.0f, 0.0f,
	-50.0f, cylinderHeight, 0.0f,
	///// plane 5
	-50.0f, cylinderHeight, 0.0f,
	-50.0f, 0.0f, -0.0f,
	-40.45f, 0.0f, -29.38f,

	-50.0f, cylinderHeight, 0.0f,
	-40.45f, 0.0f, -29.38f,
	-40.45f, cylinderHeight, -29.38f,
	///// plane 6
	-40.45f, cylinderHeight, -29.38f,
	-40.45f, 0.0f, -29.38f,
	-15.45f, 0.0f, -47.55f,

	-40.45f, cylinderHeight, -29.38f,
	-15.45f, 0.0f, -47.55f,
	-15.45f, cylinderHeight, -47.55f,
	///// plane 7
	-15.45f, cylinderHeight, -47.55f,
	-15.45f, 0.0f, -47.55f,
	15.45f, 0.0f, -47.55f,

	-15.45f, cylinderHeight, -47.55f,
	15.45f, 0.0f, -47.55f,
	15.45f, cylinderHeight, -47.55f,
	///// plane 8
	15.45f, cylinderHeight, -47.55f,
	15.45f, 0.0f, -47.55f,
	40.45f, 0.0f, -29.38f,

	15.45f, cylinderHeight, -47.55f,
	40.45f, 0.0f, -29.38f,
	40.45f, cylinderHeight, -29.38f,
	///// plane 9
	40.45f, cylinderHeight, -29.38f,
	40.45f, 0.0f, -29.38f,
	50.0f, 0.0f, 0.0f,

	40.45f, cylinderHeight, -29.38f,
	50.0f, 0.0f, 0.0f,
	50.0f, cylinderHeight, 0.0f,
};

static const GLfloat g_cylinder_uv_data[] =
{
	//// 0
	1.0f, 1.0f-1.0f,
	1.0f, 1.0f - 0.0f,
	0.75f, 1.0f - 0.0f,
	//// 1
	1.0f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.75f, 1.0f - 1.0f,
	//// 2
	0.75f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f,
	//// 3
	0.75f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.0f,
	0.5f, 1.0f - 1.0f,
	//// 4
	0.5f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.0f,
	0.25f, 1.0f - 0.0f,
	//// 5
	0.5f, 1.0f - 1.0f,
	0.25f, 1.0f - 0.0f,
	0.25f, 1.0f - 1.0f,
	//// 6
	0.25f, 1.0f - 1.0f,
	0.25f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.0f,
	//// 7
	0.25f, 1.0f - 1.0f,
	0.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	//// 8
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.75f, 1.0f - 0.0f,
	//// 9
	1.0f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.75f, 1.0f - 1.0f,
	//// 10
	0.75f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f,
	//// 11
	0.75f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.0f,
	0.5f, 1.0f - 1.0f,
	//// 12
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.75f, 1.0f - 0.0f,
	//// 13
	1.0f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.75f, 1.0f - 1.0f,
	//// 14
	0.75f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f,
	//// 15
	0.75f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.0f,
	0.5f, 1.0f - 1.0f,
	//// 16
	1.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.75f, 1.0f - 0.0f,
	//// 17
	1.0f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.75f, 1.0f - 1.0f,
	//// 18
	0.75f, 1.0f - 1.0f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f,
	//// 19
	0.75f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.0f,
	0.5f, 1.0f - 1.0f
};


float wingWidth = 50.0f;
float wingHeight = 100.0f;
static const GLfloat g_wing_vertex_data[]=
{
	// wing right
	50.0f, 0.0f, 0.0f,
	50.0f+ wingWidth, 0.0f, 0.0f,
	50.0f, wingHeight, 0.0f,
	50.0f + wingWidth, 0.0f, 0.0f,
	50.0f, wingHeight, 0.0f,
	50.0f + wingWidth, wingHeight/2, 0.0f,

	// wing left
	-50.0f, 0.0f, 0.0f,
	-(50.0f + wingWidth), 0.0f, 0.0f,
	-50.0f, wingHeight, 0.0f,
	-(50.0f + wingWidth), 0.0f, 0.0f,
	-50.0f, wingHeight, 0.0f,
	-(50.0f + wingWidth), wingHeight / 2, 0.0f,

	// center wing
	0.0f, 0.0f, 50.0f,
	0.0f, 0.0f, 50.0f+70,
	0.0f, wingHeight, 50.0f,
	0.0f, 0.0f, 50.0f + 70,
	0.0f, wingHeight, 50.0f,
	0.0f , wingHeight / 2, 50.0f + 70
};

static const GLfloat g_wing_uv_data[]=
{
	// wing left uv
	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.5f,

	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.5f,

	0.0f, 1.0f - 0.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.0f,
	0.0f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.5f

};

float cubeWidth = 30000.0f;
float cubeHeight = cubeWidth*2;
static const GLfloat g_cubeMap_vertex_data[] = {
		// 0, 1, 2 left
		-cubeWidth, 0.0f,-cubeWidth,
		-cubeWidth, 0.0f, cubeWidth,
		-cubeWidth, cubeHeight, cubeWidth,
		// 3, 4, 5 back
		 cubeWidth, cubeHeight,-cubeWidth,
		-cubeWidth, 0.0f,-cubeWidth,
		-cubeWidth, cubeHeight,-cubeWidth,
		// 6, 7, 8 bottom
		 cubeWidth, 0.0f, cubeWidth,
		-cubeWidth, 0.0f,-cubeWidth,
		 cubeWidth, 0.0f,-cubeWidth,
		 // 9, 10, 11 back
		 cubeWidth, cubeHeight,-cubeWidth,
		 cubeWidth, 0.0f,-cubeWidth,
		-cubeWidth, 0.0f,-cubeWidth,
		// 12, 13, 14 left
		-cubeWidth, 0.0f,-cubeWidth,
		-cubeWidth, cubeHeight, cubeWidth,
		-cubeWidth, cubeHeight,-cubeWidth,
		// 15, 16, 17 bottom
		 cubeWidth, 0.0f, cubeWidth,
		-cubeWidth, 0.0f, cubeWidth,
		-cubeWidth, 0.0f,-cubeWidth,
		// 18, 19, 20 front
		-cubeWidth, cubeHeight, cubeWidth,
		-cubeWidth, 0.0f, cubeWidth,
		 cubeWidth, 0.0f, cubeWidth,
		 // 21, 22, 23 right
		 cubeWidth, cubeHeight, cubeWidth,
		 cubeWidth, 0.0f,-cubeWidth,
		 cubeWidth, cubeHeight,-cubeWidth,
		 // 24, 25, 26 right
		 cubeWidth, 0.0f,-cubeWidth,
		 cubeWidth, cubeHeight, cubeWidth,
		 cubeWidth, 0.0f, cubeWidth,
		 // 27, 28, 29 up 
		 cubeWidth, cubeHeight, cubeWidth,
		 cubeWidth, cubeHeight,-cubeWidth,
		-cubeWidth, cubeHeight,-cubeWidth,
		// 30, 31, 32  up 
		 cubeWidth, cubeHeight, cubeWidth,
		-cubeWidth, cubeHeight,-cubeWidth,
		-cubeWidth, cubeHeight, cubeWidth,
		// 33, 34, 35 front
		 cubeWidth, cubeHeight, cubeWidth,
		-cubeWidth, cubeHeight, cubeWidth,
		 cubeWidth, 0.0f, cubeWidth
};

static const GLfloat g_cubeMap_uv_data[] = 
{
	// 0, 1, 2 left
	0.25f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.75f,
	// 3, 4, 5 back
	0.5f, 1.0f - 0.75f,
	0.25f, 1.0f - 0.5f,
	0.25f, 1.0f - 0.75f,
	// 6, 7, 8 bottom
	0.5f, 1.0f - 0.25f,
	0.25f, 1.0f - 0.5f,
	0.5f, 1.0f - 0.5f,
	// 9, 10, 11 back
	0.5f, 1.0f - 0.75f,
	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 0.5f,
	// 12, 13, 14 left
	0.25f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.75f,
	0.25f, 1.0f - 0.75f,
	// 15, 16, 17 bottom
	0.5f, 1.0f - 0.25f,
	0.25f, 1.0f - 0.25f,
	0.25f, 1.0f - 0.5f,
	// 18, 19, 20 front
	1.0f, 1.0f - 0.75f,
	1.0f, 1.0f - 0.5f,
	0.75f, 1.0f - 0.5f,
	// 21, 22, 23 right
	0.75f, 1.0f - 0.75f,
	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 0.75f,
	// 24, 25, 26 
	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 0.75f,
	0.75f, 1.0f - 0.5f,
	// 27, 28, 29
	0.5f, 1.0f - 1.0f,
	0.5f, 1.0f - 0.75f,
	0.25f, 1.0f -0.75f,
	// 30, 31, 32
	0.5f, 1.0f - 1.0f,
	0.25f, 1.0f - 0.75f,
	0.25f, 1.0f - 1.0f,
	// 33, 34, 35
	0.75f, 1.0f - 0.75f,
	1.0f, 1.0f - 0.75f,
	0.75f, 1.0f - 0.5f

};

float paraHeight = 100.0f;
float paraLineHeight = 300.0f;
float paraWidth = 4.0f;

static const GLfloat g_para_vertex_data[] =
{
	0.0f, paraLineHeight +paraHeight, 0.0f,
	paraWidth * 50.0f, paraLineHeight, 0.0f,
	paraWidth * 40.45f, paraLineHeight, paraWidth * 29.38f,

	0.0f, paraLineHeight + paraHeight,  0.0f,
	paraWidth  * 40.45f, paraLineHeight, paraWidth *29.38f,
	paraWidth * 15.45f, paraLineHeight, paraWidth *47.55f,

	0.0f,  paraLineHeight + paraHeight, 0.0f,
	paraWidth *15.45f, paraLineHeight, paraWidth *47.55f,
	paraWidth *(-15.45f), paraLineHeight, paraWidth *47.55f,

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *(-15.45f), paraLineHeight, paraWidth *47.55f,
	paraWidth *(-40.45), paraLineHeight, paraWidth *29.38f,

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *(-40.45), paraLineHeight, paraWidth *29.38f,
	paraWidth *(-50.0f), paraLineHeight, 0.0f,

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *(-50.0f), paraLineHeight, 0.0f,
	paraWidth *(-40.45f), paraLineHeight, paraWidth *(-29.38f),

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *(-40.45f), paraLineHeight, paraWidth *(-29.38f),
	paraWidth *(-15.45f), paraLineHeight, paraWidth *(-47.55f),

	0.0f,  paraLineHeight + paraHeight, 0.0f,
	paraWidth *(-15.45f), paraLineHeight, paraWidth *(-47.55f),
	paraWidth *15.45f, paraLineHeight, paraWidth *(-47.55f),

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *15.45f, paraLineHeight, paraWidth *(-47.55f),
	paraWidth *40.45f, paraLineHeight, paraWidth *(-29.38f),

	0.0f, paraLineHeight + paraHeight, 0.0f,
	paraWidth *40.45f, paraLineHeight, paraWidth *(-29.38f),
	paraWidth *50.0f, paraLineHeight, 0.0f

		};

static const GLfloat g_para_uv_data[] =
{
	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 0.0f,
	0.25f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 0.0f,
	0.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.25f,
	0.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	0.0f, 1.0f - 0.75f,
	0.25f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.25f, 1.0f - 1.0f,
	0.5f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.5f, 1.0f - 1.0f,
	0.75f, 1.0f - 1.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 1.0f,
	1.0f, 1.0f - 0.75f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.75f,
	1.0f, 1.0f - 0.25f,

	0.5f, 1.0f - 0.5f,
	1.0f, 1.0f - 0.25f,
	0.75f, 1.0f - 0.0f,

	0.5f, 1.0f - 0.5f,
	0.75f, 1.0f - 0.0f,
	0.5f, 1.0f - 0.0f
};

static const GLfloat g_paraLine_vertex_data[] =
{
	0.0f, 0.0f, 0.0f,
	0.0f, paraLineHeight, paraWidth*50.0f,

	0.0f, 0.0f, 0.0f,
	0.0f, paraLineHeight, paraWidth*(-50.0f),

	0.0f, 0.0f, 0.0f,
	paraWidth*50.0f, paraLineHeight, 0.0f,

	0.0f, 0.0f, 0.0f,
	paraWidth*(-50.0f), paraLineHeight, 0.0f
};