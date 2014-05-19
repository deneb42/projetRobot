#include "global.h"
#include "collisions.h"
#define TAILLEBORD 150

// Indicates whether the first Object parameter is colliding with the second one.
// Returns 1 if it is, or if it is out of the bounds of the map (=colliding with the external walls), 0 otherwise.
// Both objects are supposed to have the same type (box or cylinder), otherwise 0 may be returned.
int inCollision(Object* obj1, Object* obj2)
{
	// Checks whether the object is out of bounds or not.
	if (obj1->x < -TAILLEBORD || obj1->x > TAILLEBORD) return 1;
	if (obj1->z < -TAILLEBORD || obj1->z > TAILLEBORD) return 1;

	// Call the appropriate collision test function
	if (obj1->type == TYPE_BOX && obj2->type == TYPE_BOX)
		return collisionBox(obj1, obj2);
	else if (obj1->type == TYPE_CYLINDER && obj2->type == TYPE_CYLINDER)
		return collisionCylinder(obj1, obj2);
	return 0;
}

// Checks whether the two given cylinder objects are colliding.
// Returns 1 it hey do, 0 otherwise.
int collisionCylinder(Object* a, Object* b)
{
	double distance;
	if (a->y > b->y + b->h) return 0;
	if (a->y + a->h < b->y) return 0;
	distance = (b->x - a->x)*(b->x - a->x);
	distance += (b->z - a->z)*(b->z - a->z);
	distance = sqrt(distance);
	if (distance <= a->r + b->r)
		return 1;
	return 0;
}

// Checks whether the two given box objects are colliding.
// Returns 1 it hey do, 0 otherwise.
int collisionBox(Object* a, Object* b)
{
	if (a->x > b->x + b->w) return 0;
	else if (a->y > b->y + b->h) return 0;
    else if (a->z > b->z + b->d) return 0;
    else if (a->x + a->w < b->x) return 0;
    else if (a->y + a->h < b->y) return 0;
    else if (a->z + a->d < b->z) return 0;
    return 1;
}

// Returns the axis-oriented bounding cylinder and box for Bender.
// Warning : Both of the returned objects and the array itself will need to be freed.
Object** getBender(double position[3]) {
	// Allocation of the array
	Object** bender = (Object**) malloc(2*sizeof(Object*));

	// Bounding box
	bender[TYPE_BOX] = (Object*) malloc(sizeof(Object));
	bender[TYPE_BOX]->type = TYPE_BOX;
	bender[TYPE_BOX]->x = position[0] - 1.5;
	bender[TYPE_BOX]->y = position[2];
	bender[TYPE_BOX]->z = position[1] - 1.5;
	bender[TYPE_BOX]->h = 9.16;
	bender[TYPE_BOX]->w = 3.0;
	bender[TYPE_BOX]->d = 3.0;

	// Bounding cylinder
	bender[TYPE_CYLINDER] = (Object*) malloc(sizeof(Object));
	bender[TYPE_CYLINDER]->type = TYPE_CYLINDER;
	bender[TYPE_CYLINDER]->x = position[0];
	bender[TYPE_CYLINDER]->y = position[2];
	bender[TYPE_CYLINDER]->z = position[1];
	bender[TYPE_CYLINDER]->h = 9.16;
	bender[TYPE_CYLINDER]->r = 1.5;

	return bender;
}

// Returns the axis-oriented bounding shape of a building.
// Warning : The returned object will need to be freed.
Object* getBuilding(double position[3], int buildingType) {
	Object* building = (Object*) malloc(sizeof(Object));
	building->x = position[0];
	building->y = position[1];
	building->z = position[2];

	// The bounding box is relative to each building, depending on buildingType.
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
