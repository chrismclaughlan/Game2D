#include "headers/g_collisions.h"
#include "headers/g_scene.h"
#include "headers/g_entities.h"
#include <math.h>

/**
 * Adapted from:
 * https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
 * 
 * If intersection found, v_intersection contains intersection
 */
static bool get_line_intersection(const struct Vec2f* v0, const struct Vec2f* v1,
	const struct Vec2f* v2, const struct Vec2f* v3, struct Vec2f* v_intersection)
{
	float s1_x, s1_y, s2_x, s2_y;
	s1_x = v1->x - v0->x; s1_y = v1->y - v0->y;
	s2_x = v3->x - v2->x; s2_y = v3->y - v2->y;

	float s, t;
	s = (-s1_y * (v0->x - v2->x) + s1_x * (v0->y - v2->y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (v0->y - v2->y) - s2_y * (v0->x - v2->x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		/* Collision */
		v_intersection->x = v0->x + (t * s1_x);
		v_intersection->y = v0->y + (t * s1_y);
		return true;
	}

	return false;
}

static inline collision_lines_using_angle(const struct Vec2f* vf_origin, const double angle,
	const struct Object* starting_object, struct Vec2f* vf_intersect)
{
	/* calculate ray vector */
	struct Vec2f vf_ray;
	vf_ray.y = cos(angle) * 10.0f;
	vf_ray.x = sin(angle) * 10.0f;
	vf_ray = u_vector_add(vf_ray, *vf_origin);

	return game_collision_lines(vf_origin, &vf_ray, starting_object, vf_intersect);
}

static void collision_with_scene(const struct Vec2f* vf_origin, const struct Vec2f* vf_target,
	const struct Object* starting_object, struct Vec3f* vf_intersection_queue,
	uint* vf_intersection_queue_index)
{
	struct Vec2f vf_collision;
	struct Vec2f vf = u_vector_subtract(*vf_target, *vf_origin);
	double radians = atan2(vf.x, vf.y) - atan2(0.0f, 1.0f);

	/* Test exact corner */
	if (collision_lines_using_angle(vf_origin, radians,
		starting_object, &vf_collision))
	{
		vf_intersection_queue[*vf_intersection_queue_index].x = vf_collision.x;
		vf_intersection_queue[*vf_intersection_queue_index].y = vf_collision.y;
		vf_intersection_queue[*vf_intersection_queue_index].z = radians;
		(*vf_intersection_queue_index)++;

		//r_draw_line_f(0xff0000, *vf_origin, vf_collision, false);
	}

	/* Test either side of corner to get area behind */
	const double radians_offset = 0.0001f;

	if (collision_lines_using_angle(vf_origin, radians + radians_offset,
		starting_object, &vf_collision))
	{
		vf_intersection_queue[*vf_intersection_queue_index].x = vf_collision.x;
		vf_intersection_queue[*vf_intersection_queue_index].y = vf_collision.y;
		vf_intersection_queue[*vf_intersection_queue_index].z = radians + radians_offset;
		(*vf_intersection_queue_index)++;
		//r_draw_line_f(0x00ff00, *vf_origin, vf_collision, false);
	}

	if (collision_lines_using_angle(vf_origin, radians - radians_offset,
		starting_object, &vf_collision))
	{
		vf_intersection_queue[*vf_intersection_queue_index].x = vf_collision.x;
		vf_intersection_queue[*vf_intersection_queue_index].y = vf_collision.y;
		vf_intersection_queue[*vf_intersection_queue_index].z = radians - radians_offset;
		(*vf_intersection_queue_index)++;
		//r_draw_line_f(0x0000ff, *vf_origin, vf_collision, false);
	}
}

int game_collision_lines(const struct Vec2f* vf_origin, const struct Vec2f* vf_ray,
	const struct Object* starting_object, struct Vec2f* vf_intersect)
{
	int num_intersections = 0;
	float distance_to_intersect = 100.0f;  /* infinity */

	struct Object* object_next = starting_object;
	while (object_next != NULL)
	{
		for (struct Line* line = object_next->lines_start; line != NULL; line = line->next)
		{
			struct Vec2f this_intersect;
			bool this_did_intersect = get_line_intersection(
				vf_origin, vf_ray,
				&line->start,
				&line->end,
				&this_intersect
			);

			if (this_did_intersect)
			{
				num_intersections++;

				float distance = u_vector_distance(*vf_origin, this_intersect);
				if (distance < distance_to_intersect)
				{
					distance_to_intersect = distance;
					*vf_intersect = this_intersect;
				}
			}
		}

		object_next = object_next->next;
	}

	return num_intersections;
}

/**
 * \brief Check all scene object corners for intersections with vf_origin.
 * 
 * Will append intersections with all other scene objects to global queue
 */
void game_collision_update_los(const struct Vec2f* vf_origin, 
	const struct Object const* starting_object)
{


	struct Object* next_object = starting_object;
	while (next_object != NULL)  /* iterate over all collidable objects */
	{
		for (struct Line* line = next_object->lines_start; line != NULL; line = line->next)
		{
			//struct Vec2f vf0 = u_vector_subtract(next_object->lines[i].points[0], gp_player->sprite->pos);
			//struct Vec2f vf1 = gp_player->aim;
			//double radians = atan2(vf0.x, vf0.y) - atan2(vf1.x, vf1.y);

			//if (radians > 0.5f || radians < -0.5f) continue;

			//LOG_DEBUG("%f %f -> %f %f = %f\n", vf0.x, vf0.y, vf1.x, vf1.y, radians);


			collision_with_scene(vf_origin, &line->start,
				starting_object, g_scene_objects_intersected_queue,
				&g_scene_objects_intersected_queue_index);
		}

		next_object = next_object->next;
	}

	//struct Vec2f fov_1, fov_2;
	//double rad = gp_player->sprite->angle + gp_player->sprite->angle_offset;
	//fov_1.x = cos(rad - 0.5f);
	//fov_1.y = sin(rad - 0.5f);
	//fov_2.x = cos(rad + 0.5f);
	//fov_2.y = sin(rad + 0.5f);
	//fov_1 = u_vector_add(gp_player->sprite->pos, fov_1);
	//fov_2 = u_vector_add(gp_player->sprite->pos, fov_2);

	//collision_with_scene(vf_origin, &fov_1,
	//	starting_object, g_scene_objects_intersected_queue,
	//	&g_scene_objects_intersected_queue_index);
	//collision_with_scene(vf_origin, &fov_2,
	//	starting_object, g_scene_objects_intersected_queue,
	//	&g_scene_objects_intersected_queue_index);

}

bool game_collision_is_in_circle(struct Vec2f vf_origin, struct Vec2f vf_target, float radius)
{
	return (
		(vf_origin.x - vf_target.x) * 
		(vf_origin.x - vf_target.x) + 
		(vf_origin.y - vf_target.y) * 
		(vf_origin.y - vf_target.y)) < radius * radius;
}



/**
 * https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm.
 */
bool game_collision_circle_and_line(struct Circle C, struct Vec2f A,
	struct Vec2f B, double* distance, struct Vec2f* F, struct Vec2f* G)
{
	double distance_AB = u_vector_distance(A, B);
	struct Vec2f D, E;
	D.x = (B.x - A.x) / distance_AB;
	D.y = (B.y - A.y) / distance_AB;

	// the equation of the line AB is x = Dx*t + Ax, y = Dy*t + Ay with 0 <= t <= LAB.

	// compute the distance between the points A and E, where
	// E is the point of AB closest the circle center (Cx, Cy)
	double t = D.x * (C.pos.x - A.x) + D.y * (C.pos.y - A.y);

	// compute the coordinates of the point E
	E.x = t * D.x + A.x;
	E.y = t * D.y + A.y;

	// compute the euclidean distance between E and C
	double distance_EC = u_vector_distance(E, C.pos);

	// test if the line intersects the circle
	if (distance_EC < C.radius)
	{
		// compute distance from t to circle intersection point
		*distance = sqrt((C.radius * C.radius) - (distance_EC * distance_EC));

		if (F)
		{
			// compute first intersection point
			F->x = (t - *distance) * D.x + A.x;
			F->y = (t - *distance) * D.y + A.y;
		}
		if (G)
		{
			// compute second intersection point
			G->x = (t + *distance) * D.x + A.x;
			G->y = (t + *distance) * D.y + A.y;
		}

		return true;
	}

	// else test if the line is tangent to circle
	else if (distance_EC == C.radius)
		return false;  /* TODO true or false? */
	else
		return false;
}

bool game_collision_is_inside_polygon(struct Vec2f point, const struct Object* object)
{
	bool c = false;
	
	for (struct Line *prev = object->lines_end, *line = object->lines_start; line != NULL; prev = line, line = line->next)
	{
		if (((line->start.y > point.y) != (prev->start.y > point.y)) && (point.x < (prev->start.x - line->start.x) * (point.y - line->start.y) / (prev->start.y - line->start.y) + line->start.x))
		{
			c = !c;
		}
	}

	/* interesting format */
	//for (int i = 0, j = object.lines_size - 1; i < object.lines_size; j = i++)

	return c;
}