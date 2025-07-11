#ifndef IMSFORECAST_H
#define IMSFORECAST_H

/**
 * @brief Interfaz para la API MS-Forecast
 * 
 * Esta interfaz define los métodos necesarios para controlar
 * la temperatura y humedad del datacenter a través de la API MS-Forecast.
 * Aplica el principio de inversión de dependencias (SOLID).
 */
class IMSForecast {
public:
    /**
     * @brief Aumenta la temperatura en X grados
     * @param x Cantidad de grados a aumentar
     * @return true si la operación fue exitosa, false en caso contrario
     */
    virtual bool upTemp(int x) = 0;
    
    /**
     * @brief Disminuye la temperatura en X grados
     * @param x Cantidad de grados a disminuir
     * @return true si la operación fue exitosa, false en caso contrario
     */
    virtual bool downTemp(int x) = 0;
    
    /**
     * @brief Aumenta la humedad en X porcentaje
     * @param x Cantidad de porcentaje a aumentar
     * @return true si la operación fue exitosa, false en caso contrario
     */
    virtual bool upHumidity(int x) = 0;
    
    /**
     * @brief Disminuye la humedad en X porcentaje
     * @param x Cantidad de porcentaje a disminuir
     * @return true si la operación fue exitosa, false en caso contrario
     */
    virtual bool downHumidity(int x) = 0;
    
    /**
     * @brief Lee la temperatura actual
     * @return Temperatura actual en grados Celsius
     */
    virtual float readTemp() const = 0;
    
    /**
     * @brief Lee la humedad actual
     * @return Humedad actual en porcentaje
     */
    virtual float readHumidity() const = 0;
    
    /**
     * @brief Destructor virtual
     */
    virtual ~IMSForecast() {}
};

#endif // IMSFORECAST_H 