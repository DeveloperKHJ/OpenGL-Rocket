#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

class Model {
public:

	Model(int mode = 0)
	{
		drawMode = mode;
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	};
	
	~Model() {
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteTextures(1, &uvbuffer);
	}
	void Render(glm::mat4 projection, glm::mat4 view);
	void SetVertices(const GLfloat *data, int size);
	void SetTextures(const GLfloat *data, int size);
	void animationEvent(float deltaTime, float launchAngle, float launchPower, bool paraEvent);


	GLuint matrixID;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 direction;
	bool isAnimated = false;
	float vY;
private:
	glm::mat4 calcModelMatrix();
	GLuint vertexbuffer;
	GLuint uvbuffer;

	int verticeLength;
	// 0 = triangle, 1 = line
	int drawMode;
	float yGo;
	float animationTime = 0;
	float pendularAngle = 0;
	float lastZero = 0;
};