#include "../utils.h"
#include <math.h>


inline float 
u_vector_magnitude(struct Vec2f vf)
{
	return sqrt((vf.x * vf.x) + (vf.y * vf.y));
}

inline struct Vec2f 
u_vector_add(struct Vec2f vf0, struct Vec2f vf1)
{
	vf0.x = vf0.x + vf1.x;
	vf0.y = vf0.y + vf1.y;

	return vf0;
}

inline struct Vec2f 
u_vector_subtract(struct Vec2f vf0, struct Vec2f vf1)
{
	vf0.x = vf0.x - vf1.x;
	vf0.y = vf0.y - vf1.y;

	return vf0;
}

inline struct Vec2f 
u_vector_multiply(struct Vec2f vf, const double m)
{
	vf.x *= m;
	vf.y *= m;
	return vf;
}

inline struct Vec2f 
u_vector_normal(struct Vec2f vf0, struct Vec2f vf1)
{
	struct Vec2f vf;
	vf.x = vf1.y - vf0.y;
	vf.y = vf0.x - vf1.x;

	return vf;
}

inline struct Vec2f 
u_vector_normalise(struct Vec2f vf)
{
	const double magnitude = u_vector_magnitude(vf);
	if (magnitude == 0) return vf;
	vf.x = vf.x / magnitude;
	vf.y = vf.y / magnitude;
	return vf;
}

double 
u_vector_dotproduct(struct Vec2f vf0, struct Vec2f vf1)
{
	double result = 0.0;
	result += vf0.x * vf1.x;
	result += vf0.y * vf1.y;
	return result;
}

double 
u_vector_dotproduct_perpendicular(struct Vec2f vf0, struct Vec2f vf1)
{
	double result;
	result = vf0.x * vf1.y - vf0.y * vf1.x;
	return result;
}

/**
 * Used to sort vectors by z value.
 */
int 
u_vector3f_cmp_z(const void* a, const void* b)
{
	struct Vec3f* vf0 = (struct Vec3f*)a;
	struct Vec3f* vf1 = (struct Vec3f*)b;

	return (vf0->z > vf1->z) ? 1 : ((vf0->z < vf1->z) ? -1 : 0);
}


float 
u_vector_distance(struct Vec2f vf0, struct Vec2f vf1)
{
	return sqrt(((vf0.x - vf1.x) * (vf0.x - vf1.x)) + ((vf0.y - vf1.y) * (vf0.y - vf1.y)));
}

float 
u_vector_angle(struct Vec2f vf0, struct Vec2f vf1)
{
	//return acos((vf0.x * vf1.x + vf0.y * vf1.y) / (sqrt(vf0.x * vf0.x + vf0.y * vf0.y) * sqrt(vf1.x * vf1.x + vf1.y * vf1.y)));
	return atan2(vf1.y, vf1.x) - atan2(vf0.y, vf0.x);
}