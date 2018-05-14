#pragma once
#include "Entity.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SPRINT_SPEED = 2.0f;
const float JUMP_SPEED = 5.0f;
const float CROUCH_SPEED = 0.0002f;
const float STANDUP_SPEED = 3.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float JUMP_LIMIT = 2.5f;
const float GROUND = 0.0f;
const float CROUCH_GROUND = -0.3f;
const float GRAVITY = 9.8f;

class Camera : public Entity
{
private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	glm::vec3 velocity;
	// Euler Angles
	float yaw;
	float pitch;
	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	bool direction[4]{false};
	float accerationJump = 0.0f;
	float accerationCrouch= 0.0f;
	float accerationStandUp = 0.0f;

	bool fly;
	bool jump = false;
	float jumpSpeed;

	bool crouch = false;
	bool standUp = false;
	bool sprint = false;
	float sprintSpeed = SPRINT_SPEED;

	void updateCameraVectors();

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),bool fly = true ,glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	void Init();
	void Update(double delta);
	void ProcessKeyboard(int key, int action);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	glm::mat4 GetViewMatrix();
	inline float GetZoom() { return zoom; };
	inline float GetAcceration() {
		return accerationJump;
	}
	inline glm::vec3 GetVelocity() {
		return velocity;
	}
	inline void SetMovementSpeed(float movementSpeed) {
		this->movementSpeed = movementSpeed;
	}
};

