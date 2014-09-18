#include "Camera.h"



Camera::Camera()
{
	angle = 45.0f, xPosition = 10.0f, yPosition = 0.0f, zPosition = 2.0f, xLookAtPoint = -8.0f, yLookAtPoint = -18.0f, zLookAtPoint = 2.0f;
	countDistanceToLookAtPoint();
}

Camera::Camera(float angle, float xPosition, float yPosition, float zPosition, float xLookAtPoint, float yLookAtPoint, float zLookAtPoint)
{
	this->angle = angle, this->xPosition = xPosition, this->yPosition = yPosition, this->zPosition = zPosition, this->xLookAtPoint = xLookAtPoint, this->yLookAtPoint = yLookAtPoint, this->zLookAtPoint = zLookAtPoint;
	countDistanceToLookAtPoint();
}


Camera::~Camera()
{
}

void Camera::setAngle(float angle)
{
	this->angle = angle;
}

float Camera::getAngle()
{
	return angle;
}

void Camera::setPosition(float x, float y, float z)
{
	this->xPosition = x;
	this->yPosition = y;
	this->zPosition = z;

	try
	{
		this->positionChangeListeners(xPosition, yPosition, zPosition);
	}
	catch (...)
	{

	}
}

float Camera::getXPosition()
{
	return xPosition;
}

float Camera::getYPosition()
{
	return yPosition;
}

float Camera::getZPosition()
{
	return zPosition;
}

void Camera::setLookAtPoint(float x, float y, float z)
{
	this->xLookAtPoint = x;
	this->yLookAtPoint = y;
	this->zLookAtPoint = z;

	try
	{
		this->lookAtPointChangeListeners(xPosition, yPosition, zPosition);
	}
	catch (...)
	{

	}
}

float Camera::getXLookAtPosition()
{
	return xLookAtPoint;
}

float Camera::getYLookAtPosition()
{
	return yLookAtPoint;
}

float Camera::getZLookAtPosition()
{
	return zLookAtPoint;
}

void Camera::addCameraPositionChangeListener(std::function<void(float, float, float)> listener)
{
	positionChangeListeners.connect(listener);
}

void Camera::addCameraLookAtPointChangeListener(std::function<void(float, float, float)> listener)
{
	lookAtPointChangeListeners.connect(listener);
}

void Camera::countDistanceToLookAtPoint()
{
	distanceToLookAtPoint = abs(xLookAtPoint - xPosition);
}

float Camera::getDistanceToLookAtPoint()
{
	return distanceToLookAtPoint;
}

void Camera::moveCamera(float xShift, float yShift, float zShift)
{
	xPosition += xShift, yPosition += yShift, zPosition += zShift,
		xLookAtPoint += xShift, yLookAtPoint += yShift, zLookAtPoint += zShift;
}

void Camera::rotateCamera(float xAxisRotation, float yAxisRotation, float zAxisRotation)
{
	float xAx = (xAxisRotation != 0.0) ? xPosition + distanceToLookAtPoint * cos(6.28318 * xAxisRotation / 360.0) : xLookAtPoint;
	float yAx = (yAxisRotation != 0.0) ? yPosition + distanceToLookAtPoint * sin(6.28318 * yAxisRotation / 360.0) : yLookAtPoint;
	float zAx = (zAxisRotation != 0.0) ? zPosition + distanceToLookAtPoint * cos(6.28318 * zAxisRotation / 360.0) : zLookAtPoint;

	setLookAtPoint(xAx, yAx, zAx);
}
