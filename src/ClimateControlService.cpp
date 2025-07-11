#include "../include/ClimateControlService.h"
#include <iostream>
#include <sstream>

ClimateControlService::ClimateControlService(IMSForecast* forecast, 
                                           ClimateDataManager* dataMgr, 
                                           EmailService* emailSvc)
    : msForecast(forecast), dataManager(dataMgr), emailService(emailSvc),
      tempHighThreshold(30.0), tempLowThreshold(15.0),
      humidityHighThreshold(80.0), humidityLowThreshold(20.0) {
    
    std::cout << "ClimateControlService: Inicializando servicio de control de clima" << std::endl;
    std::cout << "  Umbrales de temperatura: " << tempLowThreshold << "°C - " << tempHighThreshold << "°C" << std::endl;
    std::cout << "  Umbrales de humedad: " << humidityLowThreshold << "% - " << humidityHighThreshold << "%" << std::endl;
}

ClimateControlService::~ClimateControlService() {
    std::cout << "ClimateControlService: Destruyendo servicio de control de clima" << std::endl;
}

ClimateReading ClimateControlService::takeReading() {
    std::cout << "ClimateControlService: Tomando lectura del clima..." << std::endl;
    
    // Obtener lecturas actuales
    float temperature = msForecast->readTemp();
    float humidity = msForecast->readHumidity();
    
    // Crear objeto de lectura
    ClimateReading reading(temperature, humidity);
    
    // Guardar en base de datos
    if (dataManager->insertReading(reading)) {
        std::cout << "ClimateControlService: Lectura guardada exitosamente" << std::endl;
    } else {
        std::cout << "ClimateControlService: Error al guardar la lectura" << std::endl;
    }
    
    // Verificar alertas
    std::vector<Alert> alerts = checkAlerts(temperature, humidity);
    processAlerts(alerts);
    
    return reading;
}

bool ClimateControlService::controlTemperature(const std::string& action, int amount) {
    std::cout << "ClimateControlService: Controlando temperatura - " << action << " " << amount << "°C" << std::endl;
    
    bool success = false;
    if (action == "up") {
        success = msForecast->upTemp(amount);
    } else if (action == "down") {
        success = msForecast->downTemp(amount);
    } else {
        std::cout << "ClimateControlService: Acción de temperatura inválida: " << action << std::endl;
        return false;
    }
    
    if (success) {
        // Tomar nueva lectura después del control
        takeReading();
        std::cout << "ClimateControlService: Control de temperatura exitoso" << std::endl;
    } else {
        std::cout << "ClimateControlService: Error en el control de temperatura" << std::endl;
    }
    
    return success;
}

bool ClimateControlService::controlHumidity(const std::string& action, int amount) {
    std::cout << "ClimateControlService: Controlando humedad - " << action << " " << amount << "%" << std::endl;
    
    bool success = false;
    if (action == "up") {
        success = msForecast->upHumidity(amount);
    } else if (action == "down") {
        success = msForecast->downHumidity(amount);
    } else {
        std::cout << "ClimateControlService: Acción de humedad inválida: " << action << std::endl;
        return false;
    }
    
    if (success) {
        // Tomar nueva lectura después del control
        takeReading();
        std::cout << "ClimateControlService: Control de humedad exitoso" << std::endl;
    } else {
        std::cout << "ClimateControlService: Error en el control de humedad" << std::endl;
    }
    
    return success;
}

float ClimateControlService::getCurrentTemperature() const {
    return msForecast->readTemp();
}

float ClimateControlService::getCurrentHumidity() const {
    return msForecast->readHumidity();
}

std::vector<ClimateReading> ClimateControlService::getAllReadings() {
    return dataManager->getAllReadings();
}

std::vector<Alert> ClimateControlService::getAllAlerts() {
    return dataManager->getAllAlerts();
}

void ClimateControlService::setAlertThresholds(float tempHigh, float tempLow, 
                                              float humidityHigh, float humidityLow) {
    tempHighThreshold = tempHigh;
    tempLowThreshold = tempLow;
    humidityHighThreshold = humidityHigh;
    humidityLowThreshold = humidityLow;
    
    std::cout << "ClimateControlService: Umbrales actualizados" << std::endl;
    std::cout << "  Temperatura: " << tempLow << "°C - " << tempHigh << "°C" << std::endl;
    std::cout << "  Humedad: " << humidityLow << "% - " << humidityHigh << "%" << std::endl;
}

void ClimateControlService::getAlertThresholds(float& tempHigh, float& tempLow, 
                                              float& humidityHigh, float& humidityLow) const {
    tempHigh = tempHighThreshold;
    tempLow = tempLowThreshold;
    humidityHigh = humidityHighThreshold;
    humidityLow = humidityLowThreshold;
}

bool ClimateControlService::isSystemHealthy() const {
    return msForecast != nullptr && dataManager != nullptr && emailService != nullptr;
}

std::vector<Alert> ClimateControlService::checkAlerts(float temperature, float humidity) {
    std::vector<Alert> alerts;
    
    // Verificar temperatura
    if (temperature > tempHighThreshold) {
        AlertSeverity severity = (temperature > 35.0) ? AlertSeverity::CRITICAL : AlertSeverity::HIGH;
        std::ostringstream msg;
        msg << "Temperatura crítica: " << temperature << "°C";
        alerts.push_back(Alert(msg.str(), severity));
    } else if (temperature < tempLowThreshold) {
        AlertSeverity severity = (temperature < 10.0) ? AlertSeverity::CRITICAL : AlertSeverity::HIGH;
        std::ostringstream msg;
        msg << "Temperatura muy baja: " << temperature << "°C";
        alerts.push_back(Alert(msg.str(), severity));
    }
    
    // Verificar humedad
    if (humidity > humidityHighThreshold) {
        AlertSeverity severity = (humidity > 90.0) ? AlertSeverity::HIGH : AlertSeverity::MEDIUM;
        std::ostringstream msg;
        msg << "Humedad muy alta: " << humidity << "%";
        alerts.push_back(Alert(msg.str(), severity));
    } else if (humidity < humidityLowThreshold) {
        AlertSeverity severity = (humidity < 10.0) ? AlertSeverity::HIGH : AlertSeverity::MEDIUM;
        std::ostringstream msg;
        msg << "Humedad muy baja: " << humidity << "%";
        alerts.push_back(Alert(msg.str(), severity));
    }
    
    return alerts;
}

void ClimateControlService::processAlerts(const std::vector<Alert>& alerts) {
    for (const auto& alert : alerts) {
        std::cout << "ClimateControlService: Procesando alerta - " << alert.toString() << std::endl;
        
        // Guardar alerta en base de datos
        dataManager->insertAlert(alert);
        
        // Enviar alerta por email
        emailService->sendAlert(alert);
    }
} 