#include <string.h>

#include "bmp.h"


void loadTexture(char* path, char* name, int *tex)
{
	char nameWPath[150];

	sprintf(nameWPath, "%stextures/%s", path, name);

	if (!(*tex= loadBMPTexture(nameWPath)) )
	{
		printf("Could not read '%s'\n", nameWPath);
		exit(EXIT_FAILURE);
	}
	else
		printf("loading : %s\n", nameWPath);
}
