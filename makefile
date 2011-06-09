#|  Makefile for the robot project  |
#|                                  |
#|  by :deneb                       |
#|  last modif : 23/05/11           |
#/__________________________________/


LIBPATH =
LIBRARY = -lglut -lGLU -lGL -lX11
CFLAGS = -Wall
LDFALGS = $(LIBPATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = mainBender.o bender.o bmp.o
#OBJS = moteur.o shapes.o collisions.o bender.o bmp.o
# Path where the bin will be
PATH_PGM = ./
# Name of the bin
PGM = TestBender


# For the generic utilisation,
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

all : $(OBJS)
	$(GCC) -o $(PATH_PGM)$(PGM) $(OBJS) $(LDFALGS)

# generic method for all the .o
%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $<

run :
	$(PATH_PGM)$(PGM)

clean :
	-rm *.o *~ $(PATH_PGM)$(PGM)

