# Makefile para Sistema de Control de Clima - Datacenter
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -Iinclude
LIBS = -lsqlite3

# Directorios
SRCDIR = src
OBJDIR = obj
OUTDIR = output
INCDIR = include

# Archivos fuente
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Nombre del ejecutable
TARGET = $(OUTDIR)/datacenter-clima

# Regla principal
all: $(TARGET)

# Crear directorios si no existen
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Compilar el ejecutable
$(TARGET): $(OBJECTS) | $(OUTDIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Compilación exitosa: $(TARGET)"

# Compilar archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Reglas específicas para archivos que dependen de headers
$(OBJDIR)/MSForecastMock.o: $(SRCDIR)/MSForecastMock.cpp $(INCDIR)/MSForecastMock.h $(INCDIR)/IMSForecast.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/ClimateReading.o: $(SRCDIR)/ClimateReading.cpp $(INCDIR)/ClimateReading.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/Alert.o: $(SRCDIR)/Alert.cpp $(INCDIR)/Alert.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/ClimateDataManager.o: $(SRCDIR)/ClimateDataManager.cpp $(INCDIR)/ClimateDataManager.h $(INCDIR)/ClimateReading.h $(INCDIR)/Alert.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/EmailService.o: $(SRCDIR)/EmailService.cpp $(INCDIR)/EmailService.h $(INCDIR)/Alert.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/ClimateControlService.o: $(SRCDIR)/ClimateControlService.cpp $(INCDIR)/ClimateControlService.h $(INCDIR)/IMSForecast.h $(INCDIR)/ClimateDataManager.h $(INCDIR)/EmailService.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp $(INCDIR)/MSForecastMock.h $(INCDIR)/ClimateDataManager.h $(INCDIR)/EmailService.h $(INCDIR)/ClimateControlService.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Limpiar archivos generados
clean:
	rm -rf $(OBJDIR) $(OUTDIR)
	@echo "Archivos de compilación eliminados"

# Limpiar solo archivos objeto
clean-obj:
	rm -rf $(OBJDIR)
	@echo "Archivos objeto eliminados"

# Recompilar todo
rebuild: clean all

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make        - Compilar el proyecto"
	@echo "  make run    - Compilar y ejecutar"
	@echo "  make clean  - Limpiar archivos generados"
	@echo "  make rebuild- Recompilar todo"
	@echo "  make help   - Mostrar esta ayuda"

# Verificar estructura del proyecto
check:
	@echo "Verificando estructura del proyecto..."
	@echo "Headers encontrados:"
	@ls -la $(INCDIR)/*.h 2>/dev/null || echo "  No se encontraron headers"
	@echo "Fuentes encontradas:"
	@ls -la $(SRCDIR)/*.cpp 2>/dev/null || echo "  No se encontraron fuentes"

# Instalar dependencias (para Ubuntu/Debian)
install-deps:
	@echo "Instalando dependencias..."
	sudo apt-get update
	sudo apt-get install -y g++ make libsqlite3-dev

# Instalar dependencias (para Windows con MSYS2)
install-deps-windows:
	@echo "Instalando dependencias para Windows..."
	pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-sqlite3

.PHONY: all run clean clean-obj rebuild help check install-deps install-deps-windows 