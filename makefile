OBJ = main.o
INC = -I "./"

renderer: $(OBJ)
	g++  $(OBJ) -o renderer.exe
	

main.o:func.h
	g++ -c main.cpp $(INC)

clean:
	rm -f $(OBJ) renderer