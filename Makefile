CC       := g++
OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -std=c++17 -lm -g -lGL -lGLU -lglut -Wall -pedantic -Wextra -Wno-unused-parameter
EXE 	 := trabalhocg
PROJETO  := main


all: clean $(OBJ)/gunshot.o $(OBJ)/$(PROJETO).o $(OBJ)/game.o $(OBJ)/character.o $(OBJ)/terrain.o $(OBJ)/svg_reader.o $(OBJ)/utils.o $(OBJ)/player.o $(OBJ)/enemy.o $(OBJ)/tinyxml2.o ## Create objects from all source code files from scratch and link them in the final program
	$(CC) $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/$(PROJETO).o: $(PROJETO).cpp
	$(CC) -c $(CFLAGS) $(PROJETO).cpp -o "$(OBJ)/$(PROJETO).o"

$(OBJ)/game.o: $(SRC)/game.cpp $(INC)/game.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/game.cpp" -o "$(OBJ)/game.o"

$(OBJ)/gunshot.o: $(SRC)/gunshot.cpp $(INC)/gunshot.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/gunshot.cpp" -o "$(OBJ)/gunshot.o"

$(OBJ)/character.o: $(SRC)/character.cpp $(INC)/character.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/character.cpp" -o "$(OBJ)/character.o"

$(OBJ)/terrain.o: $(SRC)/terrain.cpp $(INC)/terrain.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/terrain.cpp" -o "$(OBJ)/terrain.o"

$(OBJ)/svg_reader.o: $(SRC)/svg_reader.cpp $(INC)/svg_reader.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/svg_reader.cpp" -o "$(OBJ)/svg_reader.o"

$(OBJ)/utils.o: $(SRC)/utils.cpp $(INC)/utils.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/utils.cpp" -o "$(OBJ)/utils.o"

$(OBJ)/player.o: $(SRC)/player.cpp $(INC)/player.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/player.cpp" -o "$(OBJ)/player.o"

$(OBJ)/enemy.o: $(SRC)/enemy.cpp $(INC)/enemy.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/enemy.cpp" -o "$(OBJ)/enemy.o"

$(OBJ)/tinyxml2.o: $(SRC)/tinyxml2.cpp $(INC)/tinyxml2.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/tinyxml2.cpp" -o "$(OBJ)/tinyxml2.o"

run: all  ## Compile and run executable with input/arena_teste.svg
	./$(EXE) input/arena_teste.svg

debug: all ## Compile and run executable with input/arena_teste.svg in debug mode
	./$(EXE) input/arena_teste.svg -d

exe: ## Run executable with input/arena_teste.svg
	./$(EXE) input/arena_teste.svg

release: clean ## Compress code in a .zip file for distribution
	-tar -cvf AtilioAntonioDadalto.zip include/* input/arena_teste.svg obj/ src/* LICENSE main.cpp Makefile README.md

help:  ## Display help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-10s\033[0m %s\n", $$1, $$2}'

clean: ## Clean objects and executables
	-rm -f $(OBJ)/*.o
	-rm -f $(EXE)
