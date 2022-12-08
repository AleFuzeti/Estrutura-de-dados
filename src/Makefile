PROJ_NAME=ted

ALUNO= ale_fb
LIBS= -lm
OBJETOS= main.o circ.o line.o rect.o system.o text.o lista.o path.o svg.o qry.o cpt.o

# compilador
CC=gcc

# Flags
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -Wall
LDFLAGS=-O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: lista.h circ.h rect.h line.h text.h system.h path.h svg.h qry.h cpt.h main.c 

lista.o: lista.h lista.c

system.o: lista.h system.h circ.h rect.h text.h line.h path.h qry.h cpt.h system.c

circ.o: circ.h circ.c

rect.o: rect.h rect.c

line.o: line.h line.c

text.o: text.h text.c

path.o: path.h path.c

svg.o: svg.h svg.c

cpt.o: cpt.h cpt.c

qry.o: lista.h system.h circ.h rect.h text.h line.h path.h qry.h cpt.h qry.c

pack: $(PROJ_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega
