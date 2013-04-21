CC = g++
FLAGS = -Wall
LIBS = -lSDL2 -lGLEW 
FRAMEWORKS = -framework OpenGL
TARGET = Triangle
OBJ = OpenGL.o 

$(TARGET): main.cpp $(OBJ)
	$(CC) -o $(TARGET) main.cpp $(OBJ) $(FLAGS) $(LIBS) $(FRAMEWORKS) 
%.o: %.cpp
	$(CC) -c $<
