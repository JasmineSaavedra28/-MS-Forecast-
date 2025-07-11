#ifndef CLIMATEREADING_H
#define CLIMATEREADING_H

#include <string>
#include <ctime>

/**
 * @brief Clase que representa una lectura del clima
 * 
 * Esta clase encapsula los datos de una lectura de temperatura
 * y humedad en un momento específico del tiempo.
 * Aplica el patrón POJO (Plain Old Java Object) adaptado a C++.
 */
class ClimateReading {
private:
    int id;                 ///< Identificador único de la lectura
    float temperature;      ///< Temperatura en grados Celsius
    float humidity;         ///< Humedad en porcentaje
    time_t timestamp;       ///< Timestamp de la lectura

public:
    /**
     * @brief Constructor por defecto
     */
    ClimateReading();
    
    /**
     * @brief Constructor con parámetros
     * @param temp Temperatura en grados Celsius
     * @param hum Humedad en porcentaje
     */
    ClimateReading(float temp, float hum);
    
    /**
     * @brief Constructor completo
     * @param id Identificador único
     * @param temp Temperatura en grados Celsius
     * @param hum Humedad en porcentaje
     * @param ts Timestamp de la lectura
     */
    ClimateReading(int id, float temp, float hum, time_t ts);
    
    // Getters
    int getId() const;
    float getTemperature() const;
    float getHumidity() const;
    time_t getTimestamp() const;
    
    // Setters
    void setId(int id);
    void setTemperature(float temp);
    void setHumidity(float hum);
    void setTimestamp(time_t ts);
    
    /**
     * @brief Convierte la lectura a string para mostrar
     * @return String formateado con los datos de la lectura
     */
    std::string toString() const;
    
    /**
     * @brief Obtiene la fecha y hora como string
     * @return String con la fecha y hora formateada
     */
    std::string getDateTimeString() const;
};

#endif // CLIMATEREADING_H 