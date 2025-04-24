# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17

# Nombre del ejecutable
TARGET = crear_proyecto

# Archivos objeto
OBJFILES = main.o gestor_de_proyectos.o proyecto.o usuario.o

# Compila el ejecutable
all: $(TARGET)

# Generar el ejecutable
$(TARGET): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES)

# Compilar cada archivo fuente en objeto
main.o: main.cc usuario.h proyecto.h gestor_de_proyectos.h
	$(CXX) $(CXXFLAGS) -c main.cc

usuario.o: usuario.cc usuario.h proyecto.h gestor_de_proyectos.h
	$(CXX) $(CXXFLAGS) -c usuario.cc

proyecto.o: proyecto.cc usuario.h proyecto.h gestor_de_proyectos.h
	$(CXX) $(CXXFLAGS) -c proyecto.cc

gestor_de_proyectos.o: gestor_de_proyectos.cc usuario.h proyecto.h gestor_de_proyectos.h
	$(CXX) $(CXXFLAGS) -c gestor_de_proyectos.cc

# Limpiar archivos objeto y ejecutable
clean:
	rm -f *.o $(TARGET)
