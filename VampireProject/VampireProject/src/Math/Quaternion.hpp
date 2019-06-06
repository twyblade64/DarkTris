#ifndef HEX_QUATERNION_H_
#define HEX_QUATERNION_H_

#include <math.h>
#include <iostream>
#include "Utils.hpp"
#include "Constants.hpp"
#include "SFML/System.hpp" 

#define DEG2RAD 0.01745329251f
#define RAD2DEG 57.2957795131f

struct Quaternion {
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(sf::Vector3f v, float s);
public:
	float x;
	float y;
	float z;
	float w;
public:
	sf::Vector3f VectorComponent() const;
	float ScalarComponent() const;

	void Normalize();
	Quaternion Normalized() const;
	Quaternion Conjugate() const;
	Quaternion Inverse() const;
	float Length() const;
	float LengthSqr() const;
	sf::Vector3f Rotate(const sf::Vector3f& v) const;


public:
	sf::Vector3f operator*(const sf::Vector3f& rhs);
public:
	static Quaternion LookRotation(const sf::Vector3f& forward, const sf::Vector3f& dest, const sf::Vector3f& fallbackAxis = sf::Vector3f(0, 0, 0));
	static Quaternion AngleAxis(const float& degrees, const sf::Vector3f& up);
	static float Dot(const Quaternion& p, const Quaternion& q);
	static Quaternion Identity();
	static Quaternion Lerp(const Quaternion& start, const Quaternion& end, const float& value);
	static Quaternion Slerp(const Quaternion& start, const Quaternion& end, const float& value);
};

Quaternion operator*(const Quaternion& lhs, const float& rhs);
Quaternion operator*(const float& lhs, const Quaternion& rhs);
Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs);
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
std::ostream& operator<<(std::ostream& lhs, const Quaternion& rhs);

#endif // HEX_QUATERNION_H_
