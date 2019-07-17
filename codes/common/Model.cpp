#include "Model.h"
#include <iostream>


void Model::Render(glm::mat4 projection, glm::mat4 view)
{
	glm::mat4 MVP = projection * view * calcModelMatrix();
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


	if (drawMode == 0) // GL_TRIANGLES
		glDrawArrays(GL_TRIANGLES, 0, verticeLength); // 12*3 indices starting at 0 -> 12 triangles
	else if (drawMode == 1) // GL_LINES
		glDrawArrays(GL_LINES, 0, verticeLength);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Model::SetVertices(const GLfloat *data, int size)
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	verticeLength = size / 12;
}


void Model::SetTextures(const GLfloat * data, int size)
{
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


void Model::animationEvent(float time, float launchAngle, float launchPower, bool paraEvent)
{
	// 애니메이션은 기본적인 포물선 운동에 근거하여 근사하였다.

	animationTime += time; // deltaTime을 축적해 애니메이션 시간으로 사용
	float vZero = launchPower; // 초기속도 = 로켓 출력 정도
	float gravity = 9.8 * 80; // 중력
	float vZeroCosine = vZero * cos((90 - launchAngle)*3.14 / 180); 
	float vZeroSine = vZero * sin((90 - launchAngle)*3.14 / 180);
	vY = vZeroSine - gravity * animationTime;
	float airResistance = 350; // 낙하시의 공기 저항, 클수록 천천히 떨어짐

	// 낙하산 안 펴졌을 때
	if (!paraEvent)
	{
		// 물체 위치 = t초후 위치
		position.z = vZeroCosine * animationTime;
		position.y = vZeroSine * animationTime - 0.5 * gravity*pow(animationTime, 2);

		float skyTime = (2 * vZeroSine) / gravity; // 포물선 운동에 의해 정의된 물체가 땅에 닿는 시간.
		rotation.x = (launchAngle + (180 - 2 * launchAngle) * (animationTime / skyTime))*3.14 / 180; // 0 ~ 땅에 닿는 시간에 비례하여 회전한다. launchAngle ~ -lanchAngle까지 달라짐.

		// 낙하산이 펼쳐질 위치를 기억하기 위해 마지막 z값을 저장
		lastZero = position.z;
		
		// 지면과 충돌 검사 y방향 속도가 -이면서 높이가 일정 이하가 되면 멈춤.
		if (vY < 0 && position.y < 330.0f)
			position.y = 330.0f;

		// 애니메이션 시간이 땅에 닿는 시간이 넘어가면 애니메이션을 종료
		if (animationTime > skyTime)
		{
			isAnimated = false;
		}
	}
	else
	{
		
		vY = -gravity / airResistance; // 낙하속도
		// 수직낙하 + 진자운동
		pendularAngle +=  time * 3.14159f;
		position.y -=  gravity/ airResistance; // 중력과 공기저항의 영향을 받음.
		position.z = lastZero  + 10*glm::sin(pendularAngle); // 진자 운동 1
		rotation.x = 3.14 - glm::sin(pendularAngle); // 진자운동 2

		// 지면과 충돌 검사
		if (vY < 0 && position.y < 330.0f)
		{
			position.y = 330.0f;
			isAnimated = false;
		}
	}
}

glm::mat4 Model::calcModelMatrix() {
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), position); // A bit to the left
	glm::mat4 RotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);

	glm::mat4 ScalingMatrix = glm::scale(glm::mat4(), scale);
	glm::mat4 modelMatrix = TranslationMatrix * RotationMatrix*ScalingMatrix;
	return modelMatrix;
}