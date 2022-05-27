ARCHIVOS.O = comprimir.o hlist.o io.o slist.o main.o 
FLAGS = -Wall -Wextra -std=c99

slist.o: slist.c
	gcc $(FLAGS) -c slist.c

io.o: io.c
	gcc $(FLAGS) -c io.c

hlist.o: hlist.c
	gcc $(FLAGS) -c hlist.c

comprimir.o: comprimir.c
	gcc $(FLAGS) -c comprimir.c

main.o: main.c
	gcc $(FLAGS) -c main.c

programa: $(ARCHIVOS.O) 
	gcc -o programa main.o comprimir.o hlist.o slist.o io.o -g
	./programa

clean:                 #Remueve los archivos .o generados y el archivo ejecutable
	rm *.o
	rm programa

remove:               #Remueve los archivos f.txt.tree y f.txt.hf 
	rm f.txt.*


	