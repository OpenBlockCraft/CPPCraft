//-----------------------------------------------------------------------------
// MIT License
// 
// Copyright (c) 2017 Jeff Hutchinson
// Copyright (c) 2017 Tim Barnes
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "scene/camera.hpp"

const float MOUSE_SENSITIVITY = 0.1f;

const float CAMERA_SPEED = 0.01f;

Camera::Camera()
{
	mFrontVector = glm::vec3(0.0f, 0.0f, -1.0f);
	mWorldUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	mRightVector = glm::vec3(0.0f, 0.0f, 0.0f);
	mUpVector = glm::vec3(0.0f, 0.0f, 0.0f);

	mLastMousePos = glm::vec2(0.0f, 0.0f);
	mFirstMouseMove = true;

	mYaw = -90.0f;
	mPitch = 0.0f;

	mMoveAxis.horizontal = 0.0f;
	mMoveAxis.vertical = 0.0f;
}

Camera::~Camera()
{

}

void Camera::onKeyPressEvent(const KeyPressEventData &data)
{
	float val = (data.keyState == Input::KeyState::ePRESSED) ? 1.0f : -1.0f;
	switch (data.key)
	{
		case Input::Key::eW:
		case Input::Key::eUP:
			mMoveAxis.horizontal += val;
			break;
		case Input::Key::eS:
		case Input::Key::eDOWN:
			mMoveAxis.horizontal -= val;
			break;
		case Input::Key::eD:
		case Input::Key::eRIGHT:
			mMoveAxis.vertical += val;
			break;
		case Input::Key::eA:
		case Input::Key::eLEFT:
			mMoveAxis.vertical -= val;
			break;
	}
}

void Camera::onMouseMoveEvent(const MousePositionData &data)
{
	// record first movement. Second movent will move it.
	if (mFirstMouseMove)
	{
		mLastMousePos = glm::vec2(data.x, data.y);
		mFirstMouseMove = false;
		return;
	}

	mYaw += (static_cast<float>(data.x) - mLastMousePos.x) * MOUSE_SENSITIVITY;
	mPitch += (mLastMousePos.y - static_cast<float>(data.y)) * MOUSE_SENSITIVITY; // Reversed y

	mLastMousePos = glm::vec2(data.x, data.y);

	// pitch clamping
	mPitch = glm::clamp(mPitch, -90.0f, 90.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mPosition + mFrontVector, mUpVector);
}

void Camera::getYawPitch(float &yaw, float &pitch) const
{
	yaw = mYaw;
	pitch = mPitch;
}

void Camera::update(const double &dt)
{
	float yaw = glm::radians(mYaw);
	float pitch = glm::radians(mPitch);

	// Calculate front vector.
	glm::vec3 front(
		std::cos(yaw) * std::cos(pitch),
		std::sin(pitch),
		std::sin(yaw) * std::cos(pitch)
	);
	mFrontVector = glm::normalize(front);

	// Update right and up vectors
	mRightVector = glm::normalize(glm::cross(mFrontVector, mWorldUpVector));
	mUpVector = glm::normalize(glm::cross(mRightVector, mFrontVector));

	// Update position
	const float SPEED = static_cast<float>(dt) * CAMERA_SPEED;
	mPosition += mFrontVector * SPEED * mMoveAxis.horizontal;
	mPosition += mRightVector * SPEED * mMoveAxis.vertical;
}
