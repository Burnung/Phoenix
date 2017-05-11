#pragma once

#include <stdlib.h>
#include"P3D_util.h"
#include<iostream>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/geometric.hpp>
#include <math.h>

class P3DRandom{

	P3D_DECLARE_SINGLETON(P3DRandom);

public:
	void Init();
	~P3DRandom(){};
	void SetSeed(unsigned short *);

	double GetDouble();
	long GetLong();

	void lcong48(unsigned short p[7]);
private:
	unsigned short m_rand48_seed[3];
	unsigned short m_rand48_mult[3];
	unsigned short m_rand48_add;



private:

	void _dorand48(unsigned short xseed[3]);


	double erand48(unsigned short xseed[3]);
	



	long lrand48(void);

	long nrand48(unsigned short xseed[3]);

	long mrand48(void);

	long jrand48(unsigned short xseed[3]);


	void srand48(long seed);


	unsigned short * seed48(unsigned short xseed[3]);




};





using namespace glm;

const float pif = 3.1415926535898;


class P3DQuaternion
{
public:
	static const float s_quaternionNormalizationTolerance;
	static const float s_quaternionDotTolerance;

	float w, x, y, z;

	P3DQuaternion();
	P3DQuaternion(float W, float X, float Y, float Z);
	P3DQuaternion(const vec3 &axis, float angle);
	P3DQuaternion(const vec3 &eulerAngles);

	float Magnitude() const;
	float MagnitudeSquared() const;
	P3DQuaternion Normalize() const;
	void NormalizeThis();

	vec4 GetVec4f() const;

	float Dot(const P3DQuaternion &other) const;

	P3DQuaternion operator+(const P3DQuaternion &other) const;
	P3DQuaternion operator-(const P3DQuaternion &other) const;
	
	P3DQuaternion operator*(float scalar) const;
	P3DQuaternion operator/(float scalar) const;

	//Quaternion operator*(const Quaternion &other) const;

	const P3DQuaternion &operator+=(const P3DQuaternion &other);
	const P3DQuaternion &operator-=(const P3DQuaternion &other);

	const P3DQuaternion &operator*=(const P3DQuaternion &other);

	const P3DQuaternion &operator*=(float scalar);
	const P3DQuaternion &operator/=(float scalar);

	void Rotate(float angle, const vec3 &axis);

	static P3DQuaternion GetRotated(float angle, const vec3 &axis);

	P3DQuaternion Conjugate() const;
	P3DQuaternion Inverse() const;

	void Reset();

	//Matrix4x4f GetMatrix() const;

	void SetFromEulerAngles(const vec3 &eulerAngles);
	vec3 GetEulerAngles() const;

	void CalculateWFromXYZ();

	void MulMatrix();

	static P3DQuaternion Lerp(const P3DQuaternion &first, const P3DQuaternion &second, float interpolationCoefficient);
	static P3DQuaternion Slerp(const P3DQuaternion &first, const P3DQuaternion &second, float interpolationCoefficient);
};

//Vec3f operator*(const Quaternion &quat, const Vec3f &vec);
//Vec3f operator*(const Vec3f &vec, const Quaternion &quat);

P3DQuaternion operator*(const P3DQuaternion& q, const vec3& v);
P3DQuaternion operator*(const P3DQuaternion& q, const P3DQuaternion& v);
std::ostream &operator<<(std::ostream &output, const P3DQuaternion &quat);
