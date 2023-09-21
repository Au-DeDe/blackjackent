CC = g++ 
CPPFLAGS = -Wall -g -Iinclude/ 
OPT = -O3
SRC = card.cpp deck.cpp player.cpp #liste des .cpp des modules. 
OBJ = obj/main.o obj/card.o obj/deck.o obj/player.o

main : $(OBJ)
	$(CC) $(OPT) $^ -o $@

obj/main.o : main.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

obj/%.o : src/%.cpp include/%.hpp
	$(CC) -c $(CPPFLAGS) $< -o $@

.PHONY : clean

clean : 
	rm -f *.o main