#ifndef HEX_UTILS_H_
#define HEX_UTILS_H_

#include "SFML/System.hpp"
#include <math.h>

sf::Vector2f Vector3fToVector2f(sf::Vector3f v);

inline float Vector3fDot(sf::Vector3f a, sf::Vector3f b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline sf::Vector3f Vector3fCross(sf::Vector3f a, sf::Vector3f b) {
	return sf::Vector3f(
		a.y*b.z-a.z*b.y,
		a.z*b.x-a.x*b.z,
		a.x*b.y-a.y*b.x
	);
}

inline sf::Vector3f Vector3fNormalized(sf::Vector3f a) {
	return a / sqrt(Vector3fDot(a, a));
}

inline sf::Vector3f Vector3fNormalize(sf::Vector3f& a) {
	a = Vector3fNormalized(a);
	return a;
}

inline float Vector3fLengthSqr(sf::Vector3f v) {
	return Vector3fDot(v, v);
}

inline float Vector3fLength(sf::Vector3f v) {
	return sqrt(Vector3fLengthSqr(v));
}


#endif // HEX_UTILS_H_