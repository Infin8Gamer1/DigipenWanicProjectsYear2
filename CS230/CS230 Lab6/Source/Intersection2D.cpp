#include "stdafx.h"
#include "Intersection2D.h"
#include <Vector2D.h>

bool PointCircleIntersection(const Vector2D & point, const Circle & circle)
{
	float distanceSq = point.DistanceSquared(circle.center);
	float radiusSq = circle.radius * circle.radius;

	if (distanceSq <= radiusSq) {
		return true;
	}

	return false;
}

bool PointRectangleIntersection(const Vector2D & point, const BoundingRectangle & rect)
{
	if ((point.x >= rect.left && point.x <= rect.right) && (point.y >= rect.bottom && point.y <= rect.top)) {
		return true;
	}

	return false;
}

bool CircleCircleIntersection(const Circle & circle1, const Circle & circle2)
{
	float distanceSq = circle1.center.DistanceSquared(circle2.center);
	float radiSq = (circle1.radius * circle1.radius) + (circle2.radius * circle2.radius);

	if (distanceSq <= radiSq) {
		return true;
	}

	return false;
}

bool RectangleRectangleIntersection(const BoundingRectangle & rect1, const BoundingRectangle & rect2)
{
	if (rect1.right < rect2.left) {
		return false;
	}
	
	if (rect1.bottom > rect2.top) {
		return false;
	}

	if (rect1.left > rect2.right) {
		return false;
	}

	if (rect1.top < rect2.bottom) {
		return false;
	}

	return true;
}

bool RectangleCircleIntersection(const BoundingRectangle & rect, const Circle & circle)
{
	Vector2D point = Vector2D(0, 0);

	if (circle.center.x <= rect.center.x) {
		point.x = max(rect.left, circle.center.x);
	}

	if (circle.center.x > rect.center.x) {
		point.x = max(rect.right, circle.center.x);
	}

	//WORK IN PROGRESS

	return false;
}
