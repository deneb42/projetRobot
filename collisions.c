#include <math.h>
#include "collisions.h"


int inCollision(Object* obj1, Object* obj2)
{
	if (obj1->type == TYPE_BOX) {
		if (obj2->type == TYPE_BOX)
			return collisionTYPE_BOXTYPE_BOX(obj1, obj2);
		else if (obj1->type == TYPE_CYLINDER)
			return collisionTYPE_BOXTYPE_CYLINDER(obj1, obj2);
	}
	else if (obj1->type == TYPE_CYLINDER)
	{
		if (obj2->type == TYPE_BOX)
			return collisionTYPE_BOXTYPE_CYLINDER(obj2, obj1);
		else if (obj1->type == TYPE_CYLINDER)
			return collisionTYPE_CYLINDERTYPE_CYLINDER(obj1, obj2);
	}
	return 0;
}

int collisionTYPE_CYLINDERTYPE_CYLINDER(Object* a, Object* b)
{
	if (a->y > b->y + b->h) return 0;
	if (a->y + a->h < b->y) return 0;
	return collisionCircles(a, b);
}

int collisionTYPE_BOXTYPE_BOX(Object* a, Object* b)
{
	if (a->x > b->x + b->w) return 0;
	else if (a->y > b->y + b->h) return 0;
    else if (a->z > b->z + b->d) return 0;
    else if (a->x + a->w < b->x) return 0;
    else if (a->y + a->h < b->y) return 0;
    else if (a->z + a->d < b->z) return 0;
    return 1;
}

int collisionTYPE_BOXTYPE_CYLINDER(Object* b, Object* c)
{
	Object tempTYPE_BOX[2] = {{b->x - c->r, b->y, b->z, b->h, 0, b->w + c->r, b->d},
							  {b->x, b->y - c->r, b->z, b->h + c->r, 0, b->w, b->d}};
	Object tempTYPE_CYLINDER[4] = {{b->x, c->y, b->z, c->h, c->r, 0, 0},
							  {b->x + b->w, c->y, b->z, c->h, c->r, 0, 0},
							  {b->x, c->y, b->z + b->d, c->h, c->r, 0, 0},
							  {b->x + b->w, c->y, b->z + b->d, c->h, c->r, 0, 0}};
	int i, result = 0;
	double distance;
	if (b->y > c->y + c->h) return 0;
	if (b->y + b->h < c->y) return 0;

	for(i=0; i<2 && result == 0; i++)
		result = collisionPointRectangle(c->x, c->z, tempTYPE_BOX+i);
	for(i=0; i<4 && result == 0; i++)
	{
		distance = (c->x - tempTYPE_CYLINDER[i].x)*(c->x - tempTYPE_CYLINDER[i].x);
		distance += (c->z - tempTYPE_CYLINDER[i].z)*(c->z - tempTYPE_CYLINDER[i].z);
		distance = sqrt(distance);
		result = distance <= c->r;
	}
	return result;
}

int collisionPointRectangle(double x, double z, Object* rect)
{
	if (x < rect->x)		   return 0;
	if (x > rect->x + rect->w) return 0;
	if (z < rect->z)		   return 0;
	if (z > rect->z + rect->d) return 0;
	return 1;
}

int collisionCircles(Object* a, Object* b)
{
	double distance = (b->x - a->x)*(b->x - a->x);
	distance += (b->z - a->z)*(b->z - a->z);
	distance = sqrt(distance);
	if (distance <= a->r + b->r)
		return 1;
	return 0;
}

Object* getBender(double position[3]) {
	Object* bender = (Object*) malloc(sizeof(Object));
	bender->type = TYPE_CYLINDER;
	bender->x = position[0];
	bender->y = position[2];
	bender->z = position[1];
	bender->h = 9.16;
	bender->r = 1.5;
	return bender;
}
