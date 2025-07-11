#ifndef CLIMATECONTROLSERVICE_H
#define CLIMATECONTROLSERVICE_H

#include <vector>
#include "IMSForecast.h"
#include "ClimateDataManager.h"
#include "EmailService.h"
#include "ClimateReading.h"
#include "Alert.h"

/**
 * @brief Clase principal que maneja la lógica de negocio del sistema
 * 
 * Esta clase coordina todas las operaciones del sistema de control
 * de clima del datacenter. Aplica el principio de responsabilidad única
 * y actúa como controlador principal del sistema.
 */
class ClimateControlService {
private:
    IMSForecast* msForecast;        ///< Interfaz para la API MS-Forecast
    ClimateDataManager* dataManager; ///< Gestor de datos
    EmailService* emailService;     ///< Servicio de email
    
    // Umbrales de alerta
    float tempHighThreshold;        ///< Umbral alto de temperatura
    float tempLowThreshold;         ///< Umbral bajo de temperatura
    float humidityHighThreshold;    ///< Umbral alto de humedad
    float humidityLowThreshold;     ///< Umbral bajo de humedad
    
    /**
     * @brief Verifica si se deben generar alertas basadas en las lecturas
     * @param temperature Temperatura actual
     * @param humidity Humedad actual
     * @return Vector con las alertas generadas
     */
    std::vector<Alert> checkAlerts(float temperature, float humidity);
    
    /**
     * @brief Procesa las alertas generadas
     * @param alerts Vector de alertas a procesar
     */
    void processAlerts(const std::vector<Alert>& alerts);

public:
    /**
     * @brief Constructor
     * @param forecast Interfaz para la API MS-Forecast
     * @param dataMgr Gestor de datos
     * @param emailSvc Servicio de email
     */
    ClimateControlService(IMSForecast* forecast, 
                         ClimateDataManager* dataMgr, 
                         EmailService* emailSvc);
    
    /**
     * @brief Destructor
     */
    ~ClimateControlService();
    
    /**
     * @brief Toma una lectura actual del clima y la guarda
     * @return Lectura tomada
     */
    ClimateReading takeReading();
    
    /**
     * @brief Controla la temperatura
     * @param action Acción a realizar ("up" o "down")
     * @param amount Cantidad de grados
     * @return true si se ejecutó exitosamente, false en caso contrario
     */
    bool controlTemperature(const std::string& action, int amount);
    
    /**
     * @brief Controla la humedad
     * @param action Acción a realizar ("up" o "down")
     * @param amount Cantidad de porcentaje
     * @return true si se ejecutó exitosamente, false en caso contrario
     */
    bool controlHumidity(const std::string& action, int amount);
    
    /**
     * @brief Obtiene la temperatura actual
     * @return Temperatura actual en grados Celsius
     */
    float getCurrentTemperature() const;
    
    /**
     * @brief Obtiene la humedad actual
     * @return Humedad actual en porcentaje
     */
    float getCurrentHumidity() const;
    
    /**
     * @brief Obtiene todas las lecturas históricas
     * @return Vector con todas las lecturas
     */
    std::vector<ClimateReading> getAllReadings();
    
    /**
     * @brief Obtiene todas las alertas históricas
     * @return Vector con todas las alertas
     */
    std::vector<Alert> getAllAlerts();
    
    /**
     * @brief Configura los umbrales de alerta
     * @param tempHigh Umbral alto de temperatura
     * @param tempLow Umbral bajo de temperatura
     * @param humidityHigh Umbral alto de humedad
     * @param humidityLow Umbral bajo de humedad
     */
    void setAlertThresholds(float tempHigh, float tempLow, 
                           float humidityHigh, float humidityLow);
    
    /**
     * @brief Obtiene los umbrales de alerta actuales
     * @param tempHigh Referencia para el umbral alto de temperatura
     * @param tempLow Referencia para el umbral bajo de temperatura
     * @param humidityHigh Referencia para el umbral alto de humedad
     * @param humidityLow Referencia para el umbral bajo de humedad
     */
    void getAlertThresholds(float& tempHigh, float& tempLow, 
                           float& humidityHigh, float& humidityLow) const;
    
    /**
     * @brief Verifica el estado del sistema
     * @return true si el sistema está funcionando correctamente, false en caso contrario
     */
    bool isSystemHealthy() const;
};

#endif // CLIMATECONTROLSERVICE_H 