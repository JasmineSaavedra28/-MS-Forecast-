#ifndef CLIMATEDATAMANAGER_H
#define CLIMATEDATAMANAGER_H

#include <vector>
#include <string>
#include "ClimateReading.h"
#include "Alert.h"

// Forward declaration para evitar incluir sqlite3.h aquí
struct sqlite3;

/**
 * @brief Clase para manejar la persistencia de datos del clima
 * 
 * Esta clase implementa el patrón Data Mapper de Martin Fowler.
 * Se encarga de mapear los objetos de dominio (ClimateReading, Alert)
 * a la base de datos SQLite.
 */
class ClimateDataManager {
private:
    sqlite3* db;                    ///< Conexión a la base de datos SQLite
    std::string dbPath;             ///< Ruta al archivo de base de datos
    
    /**
     * @brief Crea las tablas necesarias en la base de datos
     * @return true si se crearon exitosamente, false en caso contrario
     */
    bool createTables();
    
    /**
     * @brief Ejecuta una consulta SQL
     * @param sql Consulta SQL a ejecutar
     * @return true si se ejecutó exitosamente, false en caso contrario
     */
    bool executeQuery(const std::string& sql);

public:
    /**
     * @brief Constructor
     * @param databasePath Ruta al archivo de base de datos
     */
    ClimateDataManager(const std::string& databasePath = "output/datacenter_climate.db");
    
    /**
     * @brief Destructor
     */
    ~ClimateDataManager();
    
    /**
     * @brief Inserta una lectura en la base de datos
     * @param reading Lectura a insertar
     * @return true si se insertó exitosamente, false en caso contrario
     */
    bool insertReading(const ClimateReading& reading);
    
    /**
     * @brief Inserta una alerta en la base de datos
     * @param alert Alerta a insertar
     * @return true si se insertó exitosamente, false en caso contrario
     */
    bool insertAlert(const Alert& alert);
    
    /**
     * @brief Obtiene todas las lecturas de la base de datos
     * @return Vector con todas las lecturas ordenadas por timestamp descendente
     */
    std::vector<ClimateReading> getAllReadings();
    
    /**
     * @brief Obtiene todas las alertas de la base de datos
     * @return Vector con todas las alertas ordenadas por timestamp descendente
     */
    std::vector<Alert> getAllAlerts();
    
    /**
     * @brief Obtiene las lecturas de un rango de fechas
     * @param startTime Timestamp de inicio
     * @param endTime Timestamp de fin
     * @return Vector con las lecturas del rango especificado
     */
    std::vector<ClimateReading> getReadingsByDateRange(time_t startTime, time_t endTime);
    
    /**
     * @brief Obtiene las alertas por nivel de severidad
     * @param severity Nivel de severidad a filtrar
     * @return Vector con las alertas del nivel especificado
     */
    std::vector<Alert> getAlertsBySeverity(AlertSeverity severity);
    
    /**
     * @brief Cierra la conexión a la base de datos
     */
    void closeConnection();
    
    /**
     * @brief Verifica si la conexión a la base de datos está activa
     * @return true si está conectado, false en caso contrario
     */
    bool isConnected() const;
};

#endif // CLIMATEDATAMANAGER_H 