#include "Quaternion.hpp"

// Constructors
Quaternion::Quaternion() :
	x(0), y(0), z(0), w(1) {
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w) {
}

Quaternion::Quaternion(sf::Vector3f v, float s) :
	x(v.x), y(v.y), z(v.z), w(s) {
}

// Public Methods

sf::Vector3f Quaternion::VectorComponent() const {
	return sf::Vector3f(x, y, z);
}

float Quaternion::ScalarComponent() const {
	return w;
}

void Quaternion::Normalize() {
	float im = 1.f / Length();
	x *= im;
	y *= im;
	z *= im;
	w *= im;
}

Quaternion Quaternion::Normalized() const {
	return (*this) * (1.f / Length());
}

Quaternion Quaternion::Conjugate() const {
	return Quaternion(-this->VectorComponent(), this->ScalarComponent());
}

Quaternion Quaternion::Inverse() const {
	return Conjugate() * (1.f / LengthSqr());
}

float Quaternion::Length() const {
	return sqrtf(LengthSqr());
}

float Quaternion::LengthSqr() const {
	return Quaternion::Dot(*this, *this);
}

sf::Vector3f Quaternion::Rotate(const sf::Vector3f& v) const {
	return ((*this) * Quaternion(v,0) * (*this).Conjugate()).VectorComponent();
}



sf::Vector3f Quaternion::operator*(const sf::Vector3f& rhs) {
	return Rotate(rhs);
}

// Static methods

// Source: Ogre3d (https://bitbucket.org/sinbad/ogre/src/9db75e3ba05c/OgreMain/include/OgreVector3.h#cl-651)
/** Gets the shortest arc quaternion to rotate this vector to the destination
	vector.
@remarks
	If you call this with a dest vector that is close to the inverse
	of this vector, we will rotate 180 degrees around the 'fallbackAxis'
	(if specified, or a generated axis if not) since in this case
	ANY axis of rotation is valid.
*/
Quaternion Quaternion::LookRotation(const sf::Vector3f& forward, const sf::Vector3f& dest, const sf::Vector3f& fallbackAxis) {
	// Based on Stan Melax's article in Game Programming Gems
	Quaternion q;
	// Copy, since cannot modify local
	sf::Vector3f v0 = forward;
	sf::Vector3f v1 = dest;
	Vector3fNormalize(v0);
	Vector3fNormalize(v1);

	float d = Vector3fDot(v0, v1);
	// If dot == 1, vectors are the same
	if (d >= 1.0f)
	{
		return Quaternion::Identity();
	}
	if (d < (1e-6f - 1.0f))
	{
		if (fallbackAxis != sf::Vector3f(0, 0, 0))
		{
			// rotate 180 degrees about the fallback axis
			Quaternion::AngleAxis(180.f, fallbackAxis);
		}
		else
		{
			// Generate an axis
			sf::Vector3f axis = Vector3fCross(sf::Vector3f(1, 0, 0), forward);
			if (Vector3fLengthSqr(axis) == 0) // pick another if colinear
				axis = Vector3fCross(sf::Vector3f(0, 1, 0), forward);
			Vector3fNormalize(axis);
			q = Quaternion::AngleAxis(180.f, axis);
		}
	}
	else
	{
		float s = sqrt((1 + d) * 2);
		float invs = 1 / s;

		sf::Vector3f c = Vector3fCross(v0, v1);

		q.x = c.x * invs;
		q.y = c.y * invs;
		q.z = c.z * invs;
		q.w = s * 0.5f;
		q.Normalize();
	}
	return q;
}


Quaternion Quaternion::AngleAxis(const float& degrees, const sf::Vector3f& up) {
	float rad = degrees * DEG2RAD;
	float sin = sinf(rad*.5f);
	float cos = cosf(rad*.5f);
	return Quaternion(
		sin*up.x,
		sin*up.y,
		sin*up.z,
		cos
	);
}

float Quaternion::Dot(const Quaternion& p, const Quaternion& q) {
	return p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w;
}

Quaternion Quaternion::Identity() {
	return Quaternion(0, 0, 0, 1);
}

Quaternion Quaternion::Lerp(const Quaternion& start, const Quaternion& end, const float& value) {
	return Quaternion(start*(1 - value) + end * value).Normalized();
}

Quaternion Quaternion::Slerp(const Quaternion& start, const Quaternion& end, const float& value) {
	float theta = acosf(Quaternion::Dot(start, end));
	float ws = sin((1 - value) * theta) / sin(theta);
	float we = sin(value * theta) / sin(theta);
	return start * ws + end * we;
}

// Operators

Quaternion operator*(const Quaternion& lhs, const float& rhs) {
	return Quaternion(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
}

Quaternion operator*(const float& lhs, const Quaternion& rhs) {
	return Quaternion(lhs*rhs.x, lhs*rhs.y, lhs*rhs.z, lhs*rhs.w);
}

Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs) {
	return Quaternion(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) {
	sf::Vector3f pv = lhs.VectorComponent();
	float        ps = lhs.ScalarComponent();
	sf::Vector3f qv = rhs.VectorComponent();
	float        qs = rhs.ScalarComponent();
	return Quaternion(ps*qv + qs * pv + Vector3fCross(pv, qv), ps*qs - Vector3fDot(pv, qv));
}

std::ostream& operator<<(std::ostream& lhs, const Quaternion& rhs) {
	return lhs << "(" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << ")";
}
