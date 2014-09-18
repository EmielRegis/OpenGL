#pragma once
#include <boost/signal.hpp>
#include <functional>

class Camera
{
public:
	Camera();
	Camera(float angle, float xPosition, float yPosition, float zPosition, float xLookAtPoint, float yLookAtPoint, float zLookAtPoint);
	~Camera();
	void setAngle(float angle);
	float getAngle();
	
	float getXPosition();
	float getYPosition();
	float getZPosition();	
	float getXLookAtPosition();
	float getYLookAtPosition();
	float getZLookAtPosition();

	void setPosition(float x, float y, float z);
	void setLookAtPoint(float x, float y, float z);
	void addCameraPositionChangeListener(std::function<void(float, float, float)> listener);
	void addCameraLookAtPointChangeListener(std::function<void(float, float, float)> listener);
	float getDistanceToLookAtPoint();
	void moveCamera(float xShift, float yShift, float zShift);
	void rotateCamera(float xAxisRotation, float yAxisRotation, float zAxisRotation);



private:
	float angle, xPosition, yPosition, zPosition, xLookAtPoint, yLookAtPoint, zLookAtPoint, distanceToLookAtPoint;
	boost::signal<void(float, float, float)> positionChangeListeners;
	boost::signal<void(float, float, float)> lookAtPointChangeListeners;
	void countDistanceToLookAtPoint();
};

