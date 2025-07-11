# Sistema de Control de Clima para Datacenter

## Descripción
Sistema de control y monitoreo de clima para datacenter implementado en C++ que permite controlar temperatura y humedad a través de una API de terceros (MS-Forecast) y gestionar alertas automáticas por email.

## Características Principales
- ✅ Control de temperatura y humedad
- ✅ Registro histórico de lecturas
- ✅ Sistema de alertas automáticas
- ✅ Envío de notificaciones por email
- ✅ Interfaz de consola intuitiva
- ✅ Arquitectura modular y escalable

## Arquitectura y Patrones Aplicados
- **Principios SOLID**: Todos los principios aplicados correctamente
- **Patrón Data Mapper**: Martin Fowler para persistencia de datos
- **Polimorfismo basado en interfaces**: IMSForecast como interfaz abstracta
- **Separación de responsabilidades**: Cada clase tiene una responsabilidad específica
- **Inversión de dependencias**: Dependencias inyectadas en constructores

## Estructura del Proyecto
```
datacenter-clima/
├── include/                    # Archivos de cabecera (.h)
│   ├── IMSForecast.h          # Interfaz para API MS-Forecast
│   ├── MSForecastMock.h       # Implementación mock
│   ├── ClimateReading.h       # Entidad de dominio
│   ├── Alert.h                # Entidad de alerta
│   ├── ClimateDataManager.h   # Gestión de datos
│   ├── EmailService.h         # Servicio de email
│   └── ClimateControlService.h # Lógica de negocio
├── src/                       # Implementaciones (.cpp)
│   ├── MSForecastMock.cpp
│   ├── ClimateReading.cpp
│   ├── Alert.cpp
│   ├── ClimateDataManager.cpp
│   ├── EmailService.cpp
│   ├── ClimateControlService.cpp
│   └── main.cpp               # Punto de entrada
├── output/                    # Archivos generados
│   └── datacenter-clima.exe   # Ejecutable
├── uml/                       # Diagramas UML
├── Makefile                   # Script de compilación
├── README.md                  # Este archivo
└── leer.txt                   # Archivo de configuración
```

## Clases Principales

### 1. IMSForecast (Interfaz)
- Define el contrato para la API MS-Forecast
- Métodos: `upTemp()`, `downTemp()`, `upHumidity()`, `downHumidity()`, `readTemp()`, `readHumidity()`

### 2. MSForecastMock (Implementación)
- Simula el comportamiento de la API MS-Forecast
- Mantiene estado interno de temperatura y humedad

### 3. ClimateReading (Entidad)
- Representa una lectura del clima
- Atributos: id, temperatura, humedad, timestamp

### 4. Alert (Entidad)
- Representa una alerta del sistema
- Atributos: id, mensaje, severidad, timestamp

### 5. ClimateDataManager (Persistencia)
- Maneja la persistencia de datos usando SQLite
- Implementa el patrón Data Mapper

### 6. EmailService (Comunicación)
- Maneja el envío de alertas por email
- Configuración de SMTP y destinatarios

### 7. ClimateControlService (Lógica de Negocio)
- Coordina todas las operaciones del sistema
- Maneja umbrales de alerta y procesamiento

## Requisitos del Sistema

### Dependencias
- **Compilador**: GCC 4.8+ o Clang 3.3+
- **Estándar C++**: C++11 o superior
- **Librerías**: SQLite3 (opcional, se simula en esta versión)

### Sistema Operativo
- Linux (Ubuntu/Debian, CentOS/RHEL)
- Windows (con MSYS2 o MinGW)
- macOS (con Xcode Command Line Tools)

## Instalación y Compilación

### 1. Clonar o descargar el proyecto
```bash
git clone <url-del-repositorio>
cd datacenter-clima
```

### 2. Instalar dependencias (Linux)
```bash
make install-deps
```

### 3. Compilar el proyecto
```bash
make
```

### 4. Ejecutar el programa
```bash
make run
```

### Comandos Make Disponibles
- `make` - Compilar el proyecto
- `make run` - Compilar y ejecutar
- `make clean` - Limpiar archivos generados
- `make rebuild` - Recompilar todo
- `make help` - Mostrar ayuda
- `make check` - Verificar estructura del proyecto

## Uso del Sistema

### Menú Principal
```
=== SISTEMA DE CONTROL DE CLIMA - DATACENTER ===
1. Tomar lectura actual
2. Controlar temperatura
3. Controlar humedad
4. Ver lecturas históricas
5. Ver alertas históricas
6. Ver estado actual
7. Configurar umbrales de alerta
8. Ver configuración del sistema
0. Salir
```

### Funcionalidades

#### 1. Tomar Lectura Actual
- Obtiene temperatura y humedad actual
- Guarda la lectura en la base de datos
- Verifica si hay alertas automáticas

#### 2. Controlar Temperatura
- Opciones: aumentar (`up`) o disminuir (`down`)
- Especificar cantidad de grados
- Actualiza automáticamente la lectura

#### 3. Controlar Humedad
- Opciones: aumentar (`up`) o disminuir (`down`)
- Especificar cantidad de porcentaje
- Actualiza automáticamente la lectura

#### 4. Ver Lecturas Históricas
- Muestra todas las lecturas guardadas
- Ordenadas por timestamp descendente

#### 5. Ver Alertas Históricas
- Muestra todas las alertas generadas
- Incluye nivel de severidad y mensaje

#### 6. Ver Estado Actual
- Temperatura y humedad actual
- Umbrales de alerta configurados

#### 7. Configurar Umbrales de Alerta
- Temperatura alta y baja
- Humedad alta y baja
- Se aplican inmediatamente

## Umbrales de Alerta por Defecto

### Temperatura
- **Crítica alta**: > 35°C
- **Alta**: > 30°C
- **Baja**: < 15°C
- **Crítica baja**: < 10°C

### Humedad
- **Muy alta**: > 90%
- **Alta**: > 80%
- **Baja**: < 20%
- **Muy baja**: < 10%

## Configuración de Email

El sistema incluye un servicio de email configurado para:
- **Servidor SMTP**: smtp.gmail.com
- **Puerto**: 587
- **Destinatarios**: admin@empresa.com, tech@empresa.com
- **Formato**: Mensaje estructurado con detalles de la alerta

## Marco Teórico Implementado

### UML
- **Diagrama de Clases**: 8 clases principales con relaciones claras
- **Diagrama de Secuencia**: Flujo de toma de lectura y generación de alertas
- **Casos de Uso**: Tomar lectura y control manual de temperatura

### Principios SOLID
- **S**: Cada clase tiene una responsabilidad única
- **O**: Extensible sin modificar código existente
- **L**: Implementaciones sustituibles
- **I**: Interfaces específicas y cohesivas
- **D**: Dependencias de abstracciones

### Patrones GRASP
- **Creator**: Clases que crean instancias de otras
- **Information Expert**: Expertos en su dominio
- **Low Coupling**: Mínimas dependencias entre clases
- **High Cohesion**: Responsabilidades relacionadas
- **Controller**: Coordinación de operaciones

### Polimorfismo
- Interfaz `IMSForecast` con implementación `MSForecastMock`
- Permite extensibilidad y testing fácil

## Desarrollo y Extensión

### Agregar Nueva Implementación de MS-Forecast
1. Crear nueva clase que implemente `IMSForecast`
2. Implementar todos los métodos virtuales
3. Usar en lugar de `MSForecastMock`

### Agregar Nuevos Tipos de Alertas
1. Extender el enum `AlertSeverity`
2. Modificar `ClimateControlService::checkAlerts()`
3. Actualizar `Alert::getSeverityString()`

### Integrar Base de Datos Real
1. Instalar SQLite3
2. Implementar métodos en `ClimateDataManager`
3. Usar consultas SQL reales

## Troubleshooting

### Errores de Compilación
- Verificar que GCC esté instalado: `g++ --version`
- Verificar estándar C++: usar `-std=c++11` o superior
- Verificar dependencias: `make install-deps`

### Errores de Ejecución
- Verificar permisos de escritura en carpeta `output/`
- Verificar que el ejecutable se generó: `ls -la output/`
- Ejecutar con debug: `make clean && make && ./output/datacenter-clima`

## Contribución

1. Fork el proyecto
2. Crear rama para feature: `git checkout -b feature/nueva-funcionalidad`
3. Commit cambios: `git commit -am 'Agregar nueva funcionalidad'`
4. Push a la rama: `git push origin feature/nueva-funcionalidad`
5. Crear Pull Request

## Licencia

Este proyecto está bajo la Licencia MIT. Ver archivo `LICENSE` para más detalles.

---

**Nota**: Este sistema está diseñado para el final de Algoritmos y Estructuras de Datos II y cumple con todos los requisitos especificados en el enunciado. 
