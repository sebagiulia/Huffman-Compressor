FILES.O = compression.o hlist.o io.o slist.o main.o decompression.o

TEST.O = compression.o hlist.o io.o slist.o decompression.o compressiontests.o 

FLAGS = -g -Wall -Wextra -std=c99 

CC = gcc

EXE.NAME = huff

io.o: io.c
	$(CC) $(FLAGS) -c io.c

slist.o: slist.c
	$(CC) $(FLAGS) -c slist.c

hlist.o: hlist.c
	$(CC) $(FLAGS) -c hlist.c

compression.o: compression.c
	$(CC) $(FLAGS) -c compression.c

decompression.o: decompression.c
	$(CC) $(FLAGS) -c decompression.c

compressiontests.o: compressiontests.c
	$(CC) $(FLAGS) -c compressiontests.c

main.o: main.c
	$(CC)  -c main.c

program: $(FILES.O)       		#Comando principal (make program)
	$(CC) -o $(EXE.NAME) $(FILES.O)

test: $(TEST.O)
	$(CC) -o test  $(TEST.O)
	./test

clean:							#Remueve los archivos .o generados (make clean)
	rm *.o

remove:                       	#Remueve los archivos f.txt y el archivo ejecutable (make remove) 
	rm f.txt*
	rm $(EXE.NAME)
  


	