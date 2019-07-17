// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/text2D.hpp>
#include <common/Model.h>
#include <common/buffers.h>


namespace control
{
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void computeMatricesFromInputs(glm::vec3 objectPosition, bool isAnimation);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	constexpr auto ZOOMOUT = -1;
	constexpr auto ZOOMIN = 1;

	float r = 1500; // ����ǥ�� ������
	float initialFoV = 45.0f;
	glm::vec3 position = glm::vec3(1500.0f); // ī�޶� ��ġ
	float wheelSpeed = 50.0f; // ����, �ܾƿ� ���ǵ�
	float mouseSpeed = 0.0025f; // �þ� ȸ�� �ӵ�
	float launchAngle = 0; // ���� �߻� ����
	int angleChangeSpeed = 20; // ���� ���� �ӵ�
	float launchPower = 1.0f; // �߻� ���
	int powerChangeSpeed = 70; // ��� ���� �ӵ�
	float deltaTime = 0;
	float theta = 3.14 / 4, phi = 3.14 / 4; // ����ǥ�� 
	float lastR = r;
	float lastX = position.x;
	float lastZ = position.z;

	// ���� ����
	bool isZpress = false;
	bool isZevent = false;
	bool isUp = false;
	bool isDown = false;
	bool paraEventState = false;

	// get, set �Լ�
	bool getEventState();
	bool getUpState();
	bool getDownState();
	float getLaunchAngle();
	float getLaunchPower();
	float getDeltaTime();
	void setEventEnd();
}

namespace object
{
	// �ﰢ��
	Model cone(0);

	// ����	
	Model cylinder(0);

	// ��
	Model circle(0);

	// ���� 
	Model wing(0);

	// ���
	Model cubeMap(0);

	// ���ϻ�
	Model parachute(0);

	// ���ϻ� ��
	Model paraLine(1);
	// �ʱ�ȭ
	void initBufferData(GLuint MatrixID);
}

namespace text
{
	char wheelButton[] = "Mouse Wheel : Zoom";
	
	char upButton[] = "Up & Down Arrow: adjust launch angle";
	
	char zButton[] = "Hold the Z key : adjust launch power";
	
	char xButton[] = "Press X key : Parachute!";

	char qButton[] = "Q: camera 1";
	char eButton[] = "E: camera 2";

	char angleText[12];
	
	char powerText[12];

	char velocityText[16];
}

int main(int argc, char** argv)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize glew
	glewExperimental = true; // needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// background
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	// text texture
	initText2D("Holstein.DDS");

	// Load the texture
	GLuint coneTexture = loadDDS("coneTexture.dds");
	GLuint cylinderTexture = loadDDS("cylinderTextureZ.dds");
	GLuint circleTexture = loadDDS("circleTexture.dds");
	GLuint wingTexture = loadDDS("wingTexture.dds");
	GLuint cubeMapTexture = loadDDS("cubeMapTexture2.dds");
	GLuint paraTexture = loadDDS("paraTexture.dds");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");


	// ������Ʈ�� ���� �����͸� ����
	object::initBufferData(MatrixID);

	// ������ ��ġ�� �����ϴ� ����, ī�޶�� �� ��ġ�� �Ĵٺ���.
	glm::vec3 objectPosition(0.0f, 0.0f, 0.0f);


	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		control::computeMatricesFromInputs(objectPosition, object::cylinder.isAnimated);
		glm::mat4 ProjectionMatrix = control::getProjectionMatrix();
		glm::mat4 ViewMatrix = control::getViewMatrix();
		glm::mat4 ProjectionViewMatrix = ProjectionMatrix * ViewMatrix;

		// z�� �������� ��� �ִϸ��̼� ���¸� TRUE�� �ٲ�.
		if (control::getEventState())
		{
			object::cylinder.isAnimated = true;
			control::setEventEnd();
		}

		// �ִϸ��̼� ������ �� �ൿ, �� ��ü�� �ִϸ��̼� �̺�Ʈ �Լ����� ȣ��
		if (object::cylinder.isAnimated)
		{
			object::cylinder.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);
			object::cone.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);
			object::circle.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);
			object::wing.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);
			object::parachute.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);
			object::paraLine.animationEvent(control::getDeltaTime(), control::getLaunchAngle(), control::getLaunchPower(), control::paraEventState);

			// ���ϻ� �̺�Ʈ �˻�
			if (control::paraEventState)
			{
				// ���ϻ��� ȸ������ �ʾƾ� �ǹǷ� �ݴ�� �ٽ� ȸ��
				object::parachute.rotation.x = 1*3.14/180;

				// ���ϻ� ������
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, paraTexture);
				glUniform1i(TextureID, 0);
				object::parachute.Render(ProjectionMatrix, ViewMatrix);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, 0);

				// ���ϻ� �� ������
				object::paraLine.rotation.x = 3.14 / 180;
				object::paraLine.Render(ProjectionMatrix, ViewMatrix);
			}
		}

		// Up, Down �ַο�� ��ü�� �ޱ��� ���Ѵ�.
		if (control::getUpState() || control::getDownState())
		{
			// launch angle rotation
			object::cone.rotation = glm::vec3((control::getLaunchAngle())*3.14 / 180, 0.0f, 0.0f);
			object::cylinder.rotation = glm::vec3((control::getLaunchAngle())*3.14 / 180, 0.0f, 0.0f);
			object::circle.rotation = glm::vec3((control::getLaunchAngle())*3.14 / 180, 0.0f, 0.0f);
			object::wing.rotation = glm::vec3((control::getLaunchAngle())*3.14 / 180, 0.0f, 0.0f);
		}


		// ��ü ������ Part
		// Bind -> Render -> Unbind
		// ���� �� �� �κ�
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, coneTexture);
		glUniform1i(TextureID, 0);
		object::cone.Render(ProjectionMatrix, ViewMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// ���� ����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cylinderTexture);
		glUniform1i(TextureID, 0);
		object::cylinder.Render(ProjectionMatrix, ViewMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// ���� ���� �����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, circleTexture);
		glUniform1i(TextureID, 0);
		object::circle.Render(ProjectionMatrix, ViewMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);


		// ���� ����
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, wingTexture);
		glUniform1i(TextureID, 0);
		object::wing.Render(ProjectionMatrix, ViewMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// ���
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeMapTexture);
		glUniform1i(TextureID, 0);
		object::cubeMap.Render(ProjectionMatrix, ViewMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// lookAt �Լ����� ī�޶� �Ĵٺ� ��ǥ�� ����
		objectPosition = object::cylinder.position;


		// texture Rendering
		printText2D(text::wheelButton, 10, 70, 20);
		printText2D(text::upButton, 10, 50, 20);
		printText2D(text::zButton, 10, 30, 20);
		printText2D(text::xButton, 10, 10, 20);

		printText2D(text::qButton, 480, 540, 30);
		printText2D(text::eButton, 480, 490, 30);

		snprintf(text::angleText, sizeof(text::angleText), "Angle:%f", (90- control::launchAngle));
		printText2D(text::angleText, 10, 540, 30);

		snprintf(text::powerText, sizeof(text::powerText), "Power:%f", control::launchPower);
		printText2D(text::powerText, 10, 490, 30);

		snprintf(text::velocityText, sizeof(text::velocityText), "Velocity:%f", object::cone.vY*0.1);
		printText2D(text::velocityText, 10, 440, 30);

		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	cleanupText2D();
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}





void object::initBufferData(GLuint MatrixID)
{

	object::cone.matrixID = MatrixID;
	object::cone.SetVertices(g_cone_vertex_data, sizeof(g_cone_vertex_data));
	object::cone.SetTextures(g_cone_uv_data, sizeof(g_cone_uv_data));


	object::cylinder.matrixID = MatrixID;
	object::cylinder.SetVertices(g_cylinder_data, sizeof(g_cylinder_data));
	object::cylinder.SetTextures(g_cylinder_uv_data, sizeof(g_cylinder_uv_data));

	object::circle.matrixID = MatrixID;
	object::circle.SetVertices(g_circle_vertex_data, sizeof(g_circle_vertex_data));
	object::circle.SetTextures(g_circle_uv_data, sizeof(g_circle_uv_data));


	object::wing.matrixID = MatrixID;
	object::wing.SetVertices(g_wing_vertex_data, sizeof(g_wing_vertex_data));
	object::wing.SetTextures(g_wing_uv_data, sizeof(g_wing_uv_data));

	object::cubeMap.matrixID = MatrixID;
	object::cubeMap.SetVertices(g_cubeMap_vertex_data, sizeof(g_cubeMap_vertex_data));
	object::cubeMap.SetTextures(g_cubeMap_uv_data, sizeof(g_cubeMap_uv_data));

	object::parachute.matrixID = MatrixID;
	object::parachute.SetVertices(g_para_vertex_data, sizeof(g_para_vertex_data));
	object::parachute.SetTextures(g_para_uv_data, sizeof(g_para_uv_data));

	object::paraLine.matrixID;
	object::paraLine.SetVertices(g_paraLine_vertex_data, sizeof(g_paraLine_vertex_data));
}

void control::computeMatricesFromInputs(glm::vec3 objectPosition, bool isAnimation)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	control::deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// ���콺 ���������� phi�� theta���� ����
	control::phi += control::mouseSpeed * float(1024 / 2 - xpos);
	control::theta += control::mouseSpeed * float(768 / 2 - ypos);


	// ����ǥ�踦 �̿��� ī�޶� ������ ���
	r = sqrt(position.x*position.x + position.y * position.y + position.z * position.z);
	position.x = r * sin(theta) * sin(phi);
	position.z = r * sin(theta) * cos(phi);
	position.y = r * cos(theta);

	glfwSetScrollCallback(window, scroll_callback);

	// Up arrow = �߻� ������ ������Ų��.
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (launchAngle >= 0 && !isAnimation)
		{
			isUp = true;
			launchAngle -= (deltaTime * angleChangeSpeed);
		}
		else if (launchAngle < 0)
			launchAngle = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		isUp = false;
	}
	// Down arrow = �߻� ������ ���ҽ�Ų��.
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (launchAngle <= 90 && !isAnimation)
		{
			isDown = true;
			launchAngle += (deltaTime * angleChangeSpeed);
		}
		else if (launchAngle > 90)
			launchAngle = 90;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		isDown = false;
	}
	// Z = �߻� ��� ���� ����
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {

		if (launchPower < 100)
			launchPower += deltaTime * powerChangeSpeed;
		else if (launchPower >= 100)
			launchPower = 100;
		isZpress = true;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE)
	{
		if (isZpress)
		{
			isZevent = true;	
		}
		isZpress = false;
	}
	// X = ���ϻ� KEY
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		paraEventState = true;
	}
	// Q = 1�� ī�޶�
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) // ī�޶�ȯ
	{
		ViewMatrix = glm::lookAt(
			 vec3(3000.0f, 1000.0f, 1000.0f),           // Camera is here
			objectPosition,												// and looks here 
			vec3(0.0f, 1.0f, 0.0f)              
		);
	}
	// E = 2�� ī�޶�
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		ViewMatrix = glm::lookAt(
			objectPosition + vec3(200.0f, 400.0f, 600.0f),           // Camera is here
			objectPosition + vec3(0.0f, 150.0f, 0.0f),					// and looks here 
			vec3(0.0f, 1.0f, 0.0f)              
		);
	}
	// ���� ����
	else
	{
		ViewMatrix = glm::lookAt(
			objectPosition + position,           // Camera is here
			objectPosition,							 // and looks here : at the same position
			vec3(0.0f, 1.0f, 0.0f)             
		);
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45?Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100000.0f);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

// ��ũ�ѽ� ȣ��Ǵ� �Լ�, ����, �ܾƿ�
void control::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset == ZOOMIN)
	{
		if (position.x > 0 && position.y > 0 && position.z > 0) // posx posy posz
		{
			position.x -= wheelSpeed;
			position.y -= wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x < 0 && position.y > 0 && position.z > 0) // negx posy posz
		{
			position.x += wheelSpeed;
			position.y -= wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x < 0 && position.y > 0 && position.z < 0) // negx posy negz
		{
			position.x += wheelSpeed;
			position.y -= wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x > 0 && position.y > 0 && position.z < 0) // posx posy negz
		{
			position.x -= wheelSpeed;
			position.y -= wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x > 0 && position.y < 0 && position.z > 0) // posx negy posz
		{
			position.x -= wheelSpeed;
			position.y += wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x < 0 && position.y < 0 && position.z > 0) // negx negy posz
		{
			position.x += wheelSpeed;
			position.y += wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x < 0 && position.y < 0 && position.z < 0) // negx negy negz
		{
			position.x += wheelSpeed;
			position.y += wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x > 0 && position.y < 0 && position.z < 0) // posx negy negz
		{
			position.x -= wheelSpeed;
			position.y += wheelSpeed;
			position.z += wheelSpeed;
		}

	}
	if (yoffset == ZOOMOUT)
	{
		if (position.x > 0 && position.y > 0 && position.z > 0) // posx posy posz
		{
			position.x += wheelSpeed;
			position.y += wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x < 0 && position.y > 0 && position.z > 0) // negx posy posz
		{
			position.x -= wheelSpeed;
			position.y += wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x < 0 && position.y > 0 && position.z < 0) // negx posy negz
		{
			position.x -= wheelSpeed;
			position.y += wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x > 0 && position.y > 0 && position.z < 0) // posx posy negz
		{
			position.x += wheelSpeed;
			position.y += wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x > 0 && position.y < 0 && position.z > 0) // posx negy posz
		{
			position.x += wheelSpeed;
			position.y -= wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x < 0 && position.y < 0 && position.z > 0) // negx negy posz
		{
			position.x -= wheelSpeed;
			position.y -= wheelSpeed;
			position.z += wheelSpeed;
		}
		if (position.x < 0 && position.y < 0 && position.z < 0) // negx negy negz
		{
			position.x -= wheelSpeed;
			position.y -= wheelSpeed;
			position.z -= wheelSpeed;
		}
		if (position.x > 0 && position.y < 0 && position.z < 0) // posx negy negz
		{
			position.x += wheelSpeed;
			position.y -= wheelSpeed;
			position.z -= wheelSpeed;
		}
	}

}

glm::mat4 control::getViewMatrix() {
	return ViewMatrix;
}

glm::mat4 control::getProjectionMatrix() {
	return ProjectionMatrix;
}


bool control::getEventState()
{
	return isZevent;
}

bool control::getUpState()
{
	return isUp;
}

bool control::getDownState()
{
	return isDown;
}


float control::getLaunchAngle()
{
	return launchAngle;
}

float control::getLaunchPower()
{
	return launchPower * 40;
}

float control::getDeltaTime()
{
	return deltaTime;
}

void control::setEventEnd()
{
	isZevent = false;
}