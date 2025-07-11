#include "../include/ClimateDataManager.h"
#include <iostream>
#include <fstream>

// Simulación de SQLite para este ejemplo
// En un proyecto real, incluirías #include <sqlite3.h>

ClimateDataManager::ClimateDataManager(const std::string& databasePath) 
    : db(nullptr), dbPath(databasePath) {
    std::cout << "ClimateDataManager: Inicializando conexión a " << dbPath << std::endl;
    
    // Simular conexión a base de datos
    if (createTables()) {
        std::cout << "ClimateDataManager: Base de datos inicializada correctamente" << std::endl;
    } else {
        std::cout << "ClimateDataManager: Error al inicializar la base de datos" << std::endl;
    }
}

ClimateDataManager::~ClimateDataManager() {
    closeConnection();
}

bool ClimateDataManager::createTables() {
    // Simular creación de tablas
    std::cout << "ClimateDataManager: Creando tablas..." << std::endl;
    
    // En un proyecto real, aquí ejecutarías las consultas SQL
    // CREATE TABLE IF NOT EXISTS climate_readings (...)
    // CREATE TABLE IF NOT EXISTS alerts (...)
    
    return true;
}

bool ClimateDataManager::executeQuery(const std::string& sql) {
    // Simular ejecución de consulta
    std::cout << "ClimateDataManager: Ejecutando consulta: " << sql << std::endl;
    return true;
}

bool ClimateDataManager::insertReading(const ClimateReading& reading) {
    std::cout << "ClimateDataManager: Insertando lectura - " << reading.toString() << std::endl;
    
    // Simular inserción en base de datos
    // En un proyecto real, aquí ejecutarías INSERT INTO climate_readings (...)
    
    return true;
}

bool ClimateDataManager::insertAlert(const Alert& alert) {
    std::cout << "ClimateDataManager: Insertando alerta - " << alert.toString() << std::endl;
    
    // Simular inserción en base de datos
    // En un proyecto real, aquí ejecutarías INSERT INTO alerts (...)
    
    return true;
}

std::vector<ClimateReading> ClimateDataManager::getAllReadings() {
    std::cout << "ClimateDataManager: Obteniendo todas las lecturas" << std::endl;
    
    // Simular consulta de base de datos
    // En un proyecto real, aquí ejecutarías SELECT * FROM climate_readings ORDER BY timestamp DESC
    
    std::vector<ClimateReading> readings;
    // Agregar algunas lecturas de ejemplo
    readings.push_back(ClimateReading(1, 22.5, 45.0, time(nullptr) - 3600));
    readings.push_back(ClimateReading(2, 23.1, 46.2, time(nullptr) - 1800));
    readings.push_back(ClimateReading(3, 22.8, 44.8, time(nullptr)));
    
    return readings;
}

std::vector<Alert> ClimateDataManager::getAllAlerts() {
    std::cout << "ClimateDataManager: Obteniendo todas las alertas" << std::endl;
    
    // Simular consulta de base de datos
    // En un proyecto real, aquí ejecutarías SELECT * FROM alerts ORDER BY timestamp DESC
    
    std::vector<Alert> alerts;
    // Agregar algunas alertas de ejemplo
    alerts.push_back(Alert(1, "Temperatura alta detectada", AlertSeverity::HIGH, time(nullptr) - 7200));
    alerts.push_back(Alert(2, "Humedad normal", AlertSeverity::LOW, time(nullptr) - 3600));
    
    return alerts;
}

std::vector<ClimateReading> ClimateDataManager::getReadingsByDateRange(time_t startTime, time_t endTime) {
    std::cout << "ClimateDataManager: Obteniendo lecturas por rango de fechas" << std::endl;
    
    // Simular consulta con filtro de fechas
    // En un proyecto real, aquí ejecutarías SELECT * FROM climate_readings WHERE timestamp BETWEEN ? AND ?
    
    return getAllReadings(); // Por simplicidad, retornamos todas las lecturas
}

std::vector<Alert> ClimateDataManager::getAlertsBySeverity(AlertSeverity severity) {
    std::cout << "ClimateDataManager: Obteniendo alertas por severidad" << std::endl;
    
    // Simular consulta con filtro de severidad
    // En un proyecto real, aquí ejecutarías SELECT * FROM alerts WHERE severity = ?
    
    std::vector<Alert> allAlerts = getAllAlerts();
    std::vector<Alert> filteredAlerts;
    
    for (const auto& alert : allAlerts) {
        if (alert.getSeverity() == severity) {
            filteredAlerts.push_back(alert);
        }
    }
    
    return filteredAlerts;
}

void ClimateDataManager::closeConnection() {
    if (db) {
        std::cout << "ClimateDataManager: Cerrando conexión a la base de datos" << std::endl;
        // En un proyecto real, aquí ejecutarías sqlite3_close(db)
        db = nullptr;
    }
}

bool ClimateDataManager::isConnected() const {
    return db != nullptr;
} 