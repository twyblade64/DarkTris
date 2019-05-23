#ifndef HEX_UTILS_H_
#define HEX_UTILS_H_

#include "SFML/System.hpp"
#include <math.h>

inline sf::Vector2f Vector3fToVector2f(sf::Vector3f v) {
	return sf::Vector2f(v.x, v.y);
}

inline sf::Vector3f Vector2fToVector3f(sf::Vector2f v) {
	return sf::Vector3f(v.x, v.y, 0);
}

inline float Vector3fDot(sf::Vector3f a, sf::Vector3f b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline float Vector2fDot(sf::Vector2f a, sf::Vector2f b) {
	return a.x*b.x + a.y*b.y;
}

inline sf::Vector2f Vector2fPerp(sf::Vector2f v) {
	return sf::Vector2f(-v.y, v.x);
}

inline sf::Vector3f Vector3fCross(sf::Vector3f a, sf::Vector3f b) {
	return sf::Vector3f(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x
	);
}

inline float Vector3fLengthSqr(sf::Vector3f v) {
	return Vector3fDot(v, v);
}

inline float Vector2fLengthSqr(sf::Vector2f v) {
	return Vector2fDot(v, v);
}

inline float Vector3fLength(sf::Vector3f v) {
	return sqrt(Vector3fLengthSqr(v));
}

inline float Vector2fLength(sf::Vector2f v) {
	return sqrt(Vector2fLengthSqr(v));
}

inline sf::Vector3f Vector3fNormalized(sf::Vector3f a) {
	return a / Vector3fLength(a);
}

inline sf::Vector2f Vector2fNormalized(sf::Vector2f a) {
	return a / Vector2fLength(a);
}

inline sf::Vector3f Vector3fNormalize(sf::Vector3f& a) {
	a = Vector3fNormalized(a);
	return a;
}

inline sf::Vector2f Vector2fNormalize(sf::Vector2f& a) {
	a = Vector2fNormalized(a);
	return a;
}

inline sf::Vector2f Vector2fAbs(sf::Vector2f a) {
	a.x = abs(a.x);
	a.y = abs(a.y);
	return a;
}

inline sf::Vector3f Vector3fAbs(sf::Vector3f a) {
	a.x = abs(a.x);
	a.y = abs(a.y);
	a.z = abs(a.z);
	return a;
}

#endif // HEX_UTILS_H_