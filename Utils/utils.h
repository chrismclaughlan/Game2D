#ifndef G2D_UTILS_H
#define G2D_UTILS_H

#include <stdint.h>

struct Vec2
{
	int x; int y;
};

struct Vec2f
{
	double x; double y;
};

struct Vec3f
{
	double x; double y; double z;
};

/* signed */
typedef int8_t int8;
typedef int32_t bool;
typedef int32_t int32;

/* unsigned */
typedef uint8_t uint8;
typedef uint32_t uint;
typedef uint32_t uint32;

#define true 1
#define false 0

#define swapi(a, b) {int swapi_tmp = a; a = b; b = swapi_tmp;}

#define clamp(val, min, max) ((val < min) ? min : ((val > max) ? max : val))
#define clampv(vec, min, max) vec.x = clamp(vec.x, min, max); vec.y = clamp(vec.y, min, max);
//
//#define max(a,b) (a > b ? a : b)
//
//#define min(a,b) (a < b ? a : b)

#define PI 3.14159f

extern inline float vector_magnitude(struct Vec2f vf);
extern inline struct Vec2f vector_add(struct Vec2f vf0, struct Vec2f vf1);
extern inline struct Vec2f vector_subtract(struct Vec2f vf0, struct Vec2f vf1);
extern inline struct Vec2f vector_multiply(struct Vec2f vf, const double m);
extern inline struct Vec2f vector_normalise(struct Vec2f vf);
extern inline struct Vec2f vector_normal(struct Vec2f vf0, struct Vec2f vf1);
extern double vector_dotproduct(struct Vec2f vf0, struct Vec2f vf1);
extern double vector_dotproduct_perpendicular(struct Vec2f vf0, struct Vec2f vf1);
extern int vector3f_cmp_z(const void* a, const void* b);
extern inline float vector_distance(struct Vec2f vf0, struct Vec2f vf1);
extern inline float vector_angle(struct Vec2f vf0, struct Vec2f vf1);

extern bool char_in_string(char c, char* string);

#endif