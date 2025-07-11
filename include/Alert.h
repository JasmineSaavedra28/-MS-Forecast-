#ifndef ALERT_H
#define ALERT_H

#include <string>
#include <ctime>

/**
 * @brief Enum para los niveles de severidad de las alertas
 */
enum class AlertSeverity {
    LOW,        ///< Baja severidad
    MEDIUM,     ///< Severidad media
    HIGH,       ///< Alta severidad
    CRITICAL    ///< Severidad crítica
};

/**
 * @brief Clase que representa una alerta del sistema
 * 
 * Esta clase encapsula los datos de una alerta generada
 * por el sistema de control de clima del datacenter.
 */
class Alert {
private:
    int id;                     ///< Identificador único de la alerta
    std::string message;        ///< Mensaje descriptivo de la alerta
    AlertSeverity severity;     ///< Nivel de severidad de la alerta
    time_t timestamp;           ///< Timestamp de la alerta

public:
    /**
     * @brief Constructor por defecto
     */
    Alert();
    
    /**
     * @brief Constructor con parámetros
     * @param msg Mensaje de la alerta
     * @param sev Nivel de severidad
     */
    Alert(const std::string& msg, AlertSeverity sev);
    
    /**
     * @brief Constructor completo
     * @param id Identificador único
     * @param msg Mensaje de la alerta
     * @param sev Nivel de severidad
     * @param ts Timestamp de la alerta
     */
    Alert(int id, const std::string& msg, AlertSeverity sev, time_t ts);
    
    // Getters
    int getId() const;
    std::string getMessage() const;
    AlertSeverity getSeverity() const;
    time_t getTimestamp() const;
    
    // Setters
    void setId(int id);
    void setMessage(const std::string& msg);
    void setSeverity(AlertSeverity sev);
    void setTimestamp(time_t ts);
    
    /**
     * @brief Convierte la severidad a string
     * @return String representando el nivel de severidad
     */
    std::string getSeverityString() const;
    
    /**
     * @brief Convierte la alerta a string para mostrar
     * @return String formateado con los datos de la alerta
     */
    std::string toString() const;
    
    /**
     * @brief Obtiene la fecha y hora como string
     * @return String con la fecha y hora formateada
     */
    std::string getDateTimeString() const;
};

#endif // ALERT_H 