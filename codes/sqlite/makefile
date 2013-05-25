objects = main.o sqlite3.o

edit : $(objects)
	g++ -o edit $(objects) -lpthread -ldl
main.o : main.cc
	g++ -c main.cc
sqlite3.o : sqlite3.c sqlite3.h
	gcc -c sqlite3.c
clean :
	rm edit $(objects)
