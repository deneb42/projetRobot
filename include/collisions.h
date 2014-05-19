#ifndef COLLISIONS_H
#define COLLISIONS_H

	#define TYPE_BOX 0	// Axis-oriented bounding box
	#define TYPE_CYLINDER 1	// Axis-oriented bounding cylinder

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
	int collisionCylinder(Object* a, Object* b);
	int collisionBox(Object* a, Object* b);
	Object** getBender(double position[3]);
	Object* getBuilding(double position[3], int buildingType);

#endif
