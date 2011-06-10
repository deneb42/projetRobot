#|  Makefile for the robot project  |
#|                                  |
#|  by :deneb                       |
#|  last modif : 10/06/11           |
#/__________________________________/


INC_PATH = -I../include
LIB_PATH = 
PGM_PATH = ../
LIBRARY = -lglut -lGLU -lGL -lX11
CFLAGS = -Wall
LDFALGS = $(LIB_PATH) $(LIBRARY)
GCC=gcc

# Name of the files (more .o)
OBJS = bmp.o utils.o bender.o city.o shapes.o collisions.o moteur.o
# Name of the bin
PGM = Futurama


# For the generic utilisation,
# DO NOT TOUCH ANYTHING UNDER THIS LINE !!!
# ___________________________________________

all : $(OBJS)
	$(GCC) -o $(PGM_PATH)$(PGM) $(OBJS) $(LDFALGS)

# generic method for all the .o
%.o : %.c
	$(GCC) $(CFLAGS) $(INC_PATH) -c $<

run :
	$(PGM_PATH)$(PGM)

clean :
	-rm *.o *~ $(PGM_PATH)$(PGM)

