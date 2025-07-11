#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "../include/MSForecastMock.h"
#include "../include/ClimateDataManager.h"
#include "../include/EmailService.h"
#include "../include/ClimateControlService.h"

void mostrarMenu() {
    std::cout << "\n=== SISTEMA DE CONTROL DE CLIMA - DATACENTER ===" << std::endl;
    std::cout << "1. Tomar lectura actual" << std::endl;
    std::cout << "2. Controlar temperatura" << std::endl;
    std::cout << "3. Controlar humedad" << std::endl;
    std::cout << "4. Ver lecturas históricas" << std::endl;
    std::cout << "5. Ver alertas históricas" << std::endl;
    std::cout << "6. Ver estado actual" << std::endl;
    std::cout << "7. Configurar umbrales de alerta" << std::endl;
    std::cout << "8. Ver configuración del sistema" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

void mostrarEstadoActual(ClimateControlService& service) {
    std::cout << "\n=== ESTADO ACTUAL DEL SISTEMA ===" << std::endl;
    std::cout << "Temperatura actual: " << service.getCurrentTemperature() << "°C" << std::endl;
    std::cout << "Humedad actual: " << service.getCurrentHumidity() << "%" << std::endl;
    
    float tempHigh, tempLow, humidityHigh, humidityLow;
    service.getAlertThresholds(tempHigh, tempLow, humidityHigh, humidityLow);
    
    std::cout << "\nUmbrales de alerta:" << std::endl;
    std::cout << "  Temperatura: " << tempLow << "°C - " << tempHigh << "°C" << std::endl;
    std::cout << "  Humedad: " << humidityLow << "% - " << humidityHigh << "%" << std::endl;
}

void controlarTemperatura(ClimateControlService& service) {
    std::cout << "\n=== CONTROL DE TEMPERATURA ===" << std::endl;
    std::cout << "Temperatura actual: " << service.getCurrentTemperature() << "°C" << std::endl;
    
    std::string accion;
    std::cout << "Acción (up/down): ";
    std::cin >> accion;
    
    if (accion != "up" && accion != "down") {
        std::cout << "Acción inválida. Use 'up' o 'down'" << std::endl;
        return;
    }
    
    int cantidad;
    std::cout << "Cantidad de grados: ";
    std::cin >> cantidad;
    
    if (std::cin.fail()) {
        std::cout << "Cantidad inválida" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    bool exito = service.controlTemperature(accion, cantidad);
    if (exito) {
        std::cout << "Control de temperatura exitoso" << std::endl;
    } else {
        std::cout << "Error en el control de temperatura" << std::endl;
    }
}

void controlarHumedad(ClimateControlService& service) {
    std::cout << "\n=== CONTROL DE HUMEDAD ===" << std::endl;
    std::cout << "Humedad actual: " << service.getCurrentHumidity() << "%" << std::endl;
    
    std::string accion;
    std::cout << "Acción (up/down): ";
    std::cin >> accion;
    
    if (accion != "up" && accion != "down") {
        std::cout << "Acción inválida. Use 'up' o 'down'" << std::endl;
        return;
    }
    
    int cantidad;
    std::cout << "Cantidad de porcentaje: ";
    std::cin >> cantidad;
    
    if (std::cin.fail()) {
        std::cout << "Cantidad inválida" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    bool exito = service.controlHumidity(accion, cantidad);
    if (exito) {
        std::cout << "Control de humedad exitoso" << std::endl;
    } else {
        std::cout << "Error en el control de humedad" << std::endl;
    }
}

void verLecturasHistoricas(ClimateControlService& service) {
    std::cout << "\n=== LECTURAS HISTÓRICAS ===" << std::endl;
    
    std::vector<ClimateReading> lecturas = service.getAllReadings();
    
    if (lecturas.empty()) {
        std::cout << "No hay lecturas registradas" << std::endl;
        return;
    }
    
    std::cout << "Total de lecturas: " << lecturas.size() << std::endl;
    std::cout << "\nÚltimas lecturas:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& lectura : lecturas) {
        std::cout << lectura.toString() << std::endl;
    }
}

void verAlertasHistoricas(ClimateControlService& service) {
    std::cout << "\n=== ALERTAS HISTÓRICAS ===" << std::endl;
    
    std::vector<Alert> alertas = service.getAllAlerts();
    
    if (alertas.empty()) {
        std::cout << "No hay alertas registradas" << std::endl;
        return;
    }
    
    std::cout << "Total de alertas: " << alertas.size() << std::endl;
    std::cout << "\nÚltimas alertas:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& alerta : alertas) {
        std::cout << alerta.toString() << std::endl;
    }
}

void configurarUmbrales(ClimateControlService& service) {
    std::cout << "\n=== CONFIGURAR UMBRALES DE ALERTA ===" << std::endl;
    
    float tempHigh, tempLow, humidityHigh, humidityLow;
    service.getAlertThresholds(tempHigh, tempLow, humidityHigh, humidityLow);
    
    std::cout << "Umbrales actuales:" << std::endl;
    std::cout << "  Temperatura alta: " << tempHigh << "°C" << std::endl;
    std::cout << "  Temperatura baja: " << tempLow << "°C" << std::endl;
    std::cout << "  Humedad alta: " << humidityHigh << "%" << std::endl;
    std::cout << "  Humedad baja: " << humidityLow << "%" << std::endl;
    
    std::cout << "\nNuevos umbrales:" << std::endl;
    
    std::cout << "Temperatura alta (°C): ";
    std::cin >> tempHigh;
    
    std::cout << "Temperatura baja (°C): ";
    std::cin >> tempLow;
    
    std::cout << "Humedad alta (%): ";
    std::cin >> humidityHigh;
    
    std::cout << "Humedad baja (%): ";
    std::cin >> humidityLow;
    
    if (std::cin.fail()) {
        std::cout << "Valores inválidos" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    service.setAlertThresholds(tempHigh, tempLow, humidityHigh, humidityLow);
    std::cout << "Umbrales configurados exitosamente" << std::endl;
}

void verConfiguracionSistema(ClimateControlService& service) {
    std::cout << "\n=== CONFIGURACIÓN DEL SISTEMA ===" << std::endl;
    
    std::cout << "Estado del sistema: " << (service.isSystemHealthy() ? "SALUDABLE" : "ERROR") << std::endl;
    
    float tempHigh, tempLow, humidityHigh, humidityLow;
    service.getAlertThresholds(tempHigh, tempLow, humidityHigh, humidityLow);
    
    std::cout << "\nConfiguración actual:" << std::endl;
    std::cout << "  API MS-Forecast: Mock (simulado)" << std::endl;
    std::cout << "  Base de datos: SQLite (simulado)" << std::endl;
    std::cout << "  Servicio de email: Configurado (simulado)" << std::endl;
    std::cout << "  Umbrales de temperatura: " << tempLow << "°C - " << tempHigh << "°C" << std::endl;
    std::cout << "  Umbrales de humedad: " << humidityLow << "% - " << humidityHigh << "%" << std::endl;
}

int main() {
    std::cout << "=== SISTEMA DE CONTROL DE CLIMA PARA DATACENTER ===" << std::endl;
    std::cout << "Inicializando componentes..." << std::endl;
    
    // Crear instancias de los componentes
    MSForecastMock* forecast = new MSForecastMock();
    ClimateDataManager* dataManager = new ClimateDataManager();
    EmailService* emailService = new EmailService();
    
    // Crear el servicio principal
    ClimateControlService service(forecast, dataManager, emailService);
    
    std::cout << "Sistema inicializado correctamente" << std::endl;
    
    int opcion;
    bool continuar = true;
    
    while (continuar) {
        mostrarMenu();
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cout << "Opción inválida" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch (opcion) {
            case 0:
                continuar = false;
                std::cout << "Cerrando sistema..." << std::endl;
                break;
                
            case 1:
                {
                    ClimateReading lectura = service.takeReading();
                    std::cout << "Lectura tomada: " << lectura.toString() << std::endl;
                }
                break;
                
            case 2:
                controlarTemperatura(service);
                break;
                
            case 3:
                controlarHumedad(service);
                break;
                
            case 4:
                verLecturasHistoricas(service);
                break;
                
            case 5:
                verAlertasHistoricas(service);
                break;
                
            case 6:
                mostrarEstadoActual(service);
                break;
                
            case 7:
                configurarUmbrales(service);
                break;
                
            case 8:
                verConfiguracionSistema(service);
                break;
                
            default:
                std::cout << "Opción inválida" << std::endl;
                break;
        }
    }
    
    // Limpieza de memoria
    delete forecast;
    delete dataManager;
    delete emailService;
    
    std::cout << "Sistema cerrado correctamente" << std::endl;
    return 0;
} 