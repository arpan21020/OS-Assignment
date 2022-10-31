run:file
	./file
file:file.o
	gcc -m64 -no-pie file.o -o file
file.o:file.asm
	yasm -f elf64 -o file.o file.asm
clean:
	rm -rf*.o*file
