# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../include

# Nombre del ejecutable
TARGET = main

# Archivos fuente y objeto
SRC = main.cc CrearCuenta.cc gestor_de_proyectos.cc IniciarSesion.cc proyecto.cc tarea.cc Uid.cc Usuario.cc
OBJ = $(SRC:.cc=.o)

# Regla principal
all: $(TARGET)

# Generar el ejecutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Regla general para compilar .cc -> .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJ) $(TARGET)
