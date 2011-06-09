#ifndef COLLISIONS_H
#define COLLISIONS_H
#define TYPE_BOX 0
#define TYPE_CYLINDER 1

typedef struct Object Object;
struct Object {
	int type; // Determines the shape of the object.

	double x; // Position on x-axis
	double y; // Position on y-axis
	double z; // Position on z-axis
	double h; // Height

	// For TYPE_CYLINDERs
	double r; // Radius

	// For TYPE_BOXes
	double w; // Width
	double d; // Depth
};

int inCollision(Object* obj1, Object* obj2);
int collisionTYPE_CYLINDERTYPE_CYLINDER(Object* a, Object* b);
int collisionTYPE_BOXTYPE_CYLINDER(Object* b, Object* c);
int collisionTYPE_BOXTYPE_BOX(Object* a, Object* b);
int collisionPointRectangle(double x, double z, Object* rect);
int collisionCircles(Object* a, Object* b);
Object* getBender(double position[3]);

#endif
