#include "global.h"
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

Object** getBender(double position[3]) {
	Object** bender = (Object**) malloc(2*sizeof(Object*));
	bender[TYPE_BOX] = (Object*) malloc(sizeof(Object));
	bender[TYPE_BOX]->type = TYPE_BOX;
	bender[TYPE_BOX]->x = position[0] - 1.5;
	bender[TYPE_BOX]->y = position[2];
	bender[TYPE_BOX]->z = position[1] - 1.5;
	bender[TYPE_BOX]->h = 9.16;
	bender[TYPE_BOX]->w = 3.0;
	bender[TYPE_BOX]->d = 3.0;

	bender[TYPE_CYLINDER] = (Object*) malloc(sizeof(Object));
	bender[TYPE_CYLINDER]->type = TYPE_CYLINDER;
	bender[TYPE_CYLINDER]->x = position[0];
	bender[TYPE_CYLINDER]->y = position[2];
	bender[TYPE_CYLINDER]->z = position[1];
	bender[TYPE_CYLINDER]->h = 9.16;
	bender[TYPE_CYLINDER]->r = 1.5;

	return bender;
}


Object* getBuilding(double position[3], int buildingType) {
	Object* building = (Object*) malloc(sizeof(Object));
	building->x = position[0];
	building->y = position[1];
	building->z = position[2];

	switch (buildingType)
	{
		case 11 :
			building->type = TYPE_BOX;
			building->w = 10;
			building->h = 60;
			building->d = 10;
			break;
		case 12 :
			building->type = TYPE_BOX;
			building->w = 15;
			building->h = 90;
			building->d = 15;
			break;
		case 13 :
			building->type = TYPE_BOX;
			building->w = 30;
			building->h = 10;
			building->d = 30;
			break;
		case 14 :
			building->type = TYPE_CYLINDER;
			building->h = 100;
			building->r = 5;
			break;
		case 15 :
			building->type = TYPE_CYLINDER;
			building->h = 20;
			building->r = 5;
			break;
		case 16 :
			building->type = TYPE_BOX;
			building->w = 20;
			building->h = 70;
			building->d = 20;
			break;
		case 17 :
			building->type = TYPE_BOX;
			building->w = 25;
			building->h = 5;
			building->d = 25;
			break;
		case 18 :
			building->type = TYPE_CYLINDER;
			building->h = 90;
			building->r = 10;
			break;
		case 19 :
			building->type = TYPE_BOX;
			building->w = 18;
			building->h = 20;
			building->d = 18;
			break;
		case 20 :
			building->type = TYPE_CYLINDER;
			building->h = 10;
			building->r = 30;
			break;
		case 21 :
			building->type = TYPE_CYLINDER;
			building->h = 95;
			building->r = 10;
			break;
		case 22 :
			building->type = TYPE_CYLINDER;
			building->h = 40;
			building->d = 20;
			break;
		default:
			break;
	}

	return building;
}
