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
	// �ִϸ��̼��� �⺻���� ������ ��� �ٰ��Ͽ� �ٻ��Ͽ���.

	animationTime += time; // deltaTime�� ������ �ִϸ��̼� �ð����� ���
	float vZero = launchPower; // �ʱ�ӵ� = ���� ��� ����
	float gravity = 9.8 * 80; // �߷�
	float vZeroCosine = vZero * cos((90 - launchAngle)*3.14 / 180); 
	float vZeroSine = vZero * sin((90 - launchAngle)*3.14 / 180);
	vY = vZeroSine - gravity * animationTime;
	float airResistance = 350; // ���Ͻ��� ���� ����, Ŭ���� õõ�� ������

	// ���ϻ� �� ������ ��
	if (!paraEvent)
	{
		// ��ü ��ġ = t���� ��ġ
		position.z = vZeroCosine * animationTime;
		position.y = vZeroSine * animationTime - 0.5 * gravity*pow(animationTime, 2);

		float skyTime = (2 * vZeroSine) / gravity; // ������ ��� ���� ���ǵ� ��ü�� ���� ��� �ð�.
		rotation.x = (launchAngle + (180 - 2 * launchAngle) * (animationTime / skyTime))*3.14 / 180; // 0 ~ ���� ��� �ð��� ����Ͽ� ȸ���Ѵ�. launchAngle ~ -lanchAngle���� �޶���.

		// ���ϻ��� ������ ��ġ�� ����ϱ� ���� ������ z���� ����
		lastZero = position.z;
		
		// ����� �浹 �˻� y���� �ӵ��� -�̸鼭 ���̰� ���� ���ϰ� �Ǹ� ����.
		if (vY < 0 && position.y < 330.0f)
			position.y = 330.0f;

		// �ִϸ��̼� �ð��� ���� ��� �ð��� �Ѿ�� �ִϸ��̼��� ����
		if (animationTime > skyTime)
		{
			isAnimated = false;
		}
	}
	else
	{
		
		vY = -gravity / airResistance; // ���ϼӵ�
		// �������� + ���ڿ
		pendularAngle +=  time * 3.14159f;
		position.y -=  gravity/ airResistance; // �߷°� ���������� ������ ����.
		position.z = lastZero  + 10*glm::sin(pendularAngle); // ���� � 1
		rotation.x = 3.14 - glm::sin(pendularAngle); // ���ڿ 2

		// ����� �浹 �˻�
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