#include "Camera.h"
#include <GLFW\glfw3.h>
#include <iostream>
Camera::Camera(glm::vec3 position, bool fly, glm::vec3 up, float yaw, float pitch) : Entity(position), worldUp(up), yaw(yaw), pitch(pitch),
front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM), fly(fly), jumpSpeed(JUMP_SPEED)
{
	updateCameraVectors();
}

void Camera::Init()
{
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}
void Camera::Update(double delta)
{
	if (!fly) {
		if (jump) {
			accerationJump -= GRAVITY * delta;
			velocity.y += accerationJump * delta;
			if (velocity.y <= GROUND && !standUp) {
				jump = false;
				velocity.y = GROUND;
			}
		}
		if (crouch) {
			accerationCrouch += GRAVITY * delta;
			if (velocity.y > CROUCH_GROUND)
				velocity.y -= accerationCrouch * delta;
			else
				velocity.y = CROUCH_GROUND;
		}
		if (standUp) {
			accerationStandUp -= GRAVITY * delta;
			velocity.y += accerationStandUp * delta;
			if (velocity.y >= GROUND) {
				velocity.y = GROUND;
				standUp = false;
			}
		}
		position.y = velocity.y;
	}
	if (sprint) {
		velocity.x = movementSpeed * sprintSpeed * delta;
		velocity.z = movementSpeed * sprintSpeed * delta;
	}
	else
	{
		velocity.x = movementSpeed * delta;
		velocity.z = movementSpeed * delta;
	}
	if (direction[0])
		if (fly)
			position += front * velocity.z;
		else
			position += glm::normalize(glm::cross(worldUp, right)) * velocity.z;
	if (direction[1])
		if (fly)
			position -= front * velocity.z;
		else
			position -= glm::normalize(glm::cross(worldUp, right)) * velocity.z;

	if (direction[2])
		position -= right * velocity.x;
	if (direction[3])
		position += right * velocity.x;
	
}

void Camera::ProcessKeyboard(int key, int action)
{
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
			direction[0] = true;
		else if (action == GLFW_RELEASE)
			direction[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS)
			direction[1] = true;
		else if (action == GLFW_RELEASE)
			direction[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
			direction[2] = true;
		else if (action == GLFW_RELEASE)
			direction[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
			direction[3] = true;
		else if (action == GLFW_RELEASE)
			direction[3] = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS)
			sprint = true;
		else if (action == GLFW_RELEASE)
			sprint = false;
	}
	if (!fly) {
		if (key == GLFW_KEY_SPACE && !jump && !crouch) {
			if (action == GLFW_PRESS) {
				jump = true;
				accerationJump = jumpSpeed;
			}
		}
		if (key == GLFW_KEY_C) {
			if (action == GLFW_PRESS) {
				crouch = true;
				standUp = false;
				accerationCrouch = CROUCH_SPEED;
			}
			else if (action == GLFW_RELEASE) {
				crouch = false;
				standUp = true;
				accerationStandUp = STANDUP_SPEED;
			}
		}
	}
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}
void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 tempFront;
	tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tempFront.y = sin(glm::radians(pitch));
	tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(tempFront);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}
