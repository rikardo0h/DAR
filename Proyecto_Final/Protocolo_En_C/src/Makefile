#    Makefile - Desarrollo de Aplicaciones en Red Servidor, Cliente UDP
#    all	- Compilar todo
#    clean	- Limpiar archivos compilados


BIN = ../bin
LIB = libs
EXECUTABLES = atk clientatk
# Agregar cabeceras .h
INCLUDES = 
#Usar gcc
GCC = gcc
#Bibliotecas
LIBS = -lm -lpthread libscan.o
#FLAGS =  -std=c99
CFLAGS = -I.

#'make all' creará todos los ejecutables
all: $(EXECUTABLES)

#'make clean' eleminar archivos objetos
clean:
	rm -f $(BIN)/atk $(BIN)/clientatk *.o

# Compilar los archivos .c
lib:$(LIB)/*.c $(INCLUDES) 
	$(GCC) $(FLAGS) $(CFLAGS) -c $<


# Compilar los archivos .c
%.o:%.c $(INCLUDES) 
	$(GCC) $(FLAGS) $(CFLAGS) -c $<

# Generar ejecutables individuales
atk: atk.o
	$(GCC) $(FLAGS) $(CFLAGS) -o $(BIN)/atk atk.o $(LIBS)

clientatk: clientatk.o
	$(GCC) $(FLAGS) $(CFLAGS) -o $(BIN)/clientatk clientatk.o $(LIBS)	