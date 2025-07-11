#ifndef MSFORECASTMOCK_H
#define MSFORECASTMOCK_H

#include "IMSForecast.h"

/**
 * @brief Implementación mock de la API MS-Forecast
 * 
 * Esta clase simula el comportamiento de la API MS-Forecast
 * para propósitos de desarrollo y testing.
 * Implementa la interfaz IMSForecast.
 */
class MSForecastMock : public IMSForecast {
private:
    float currentTemp;      ///< Temperatura actual simulada
    float currentHumidity;  ///< Humedad actual simulada

public:
    /**
     * @brief Constructor por defecto
     * Inicializa la temperatura en 22°C y humedad en 45%
     */
    MSForecastMock();
    
    /**
     * @brief Aumenta la temperatura simulada
     * @param x Cantidad de grados a aumentar
     * @return true siempre (simulación exitosa)
     */
    bool upTemp(int x) override;
    
    /**
     * @brief Disminuye la temperatura simulada
     * @param x Cantidad de grados a disminuir
     * @return true siempre (simulación exitosa)
     */
    bool downTemp(int x) override;
    
    /**
     * @brief Aumenta la humedad simulada
     * @param x Cantidad de porcentaje a aumentar
     * @return true siempre (simulación exitosa)
     */
    bool upHumidity(int x) override;
    
    /**
     * @brief Disminuye la humedad simulada
     * @param x Cantidad de porcentaje a disminuir
     * @return true siempre (simulación exitosa)
     */
    bool downHumidity(int x) override;
    
    /**
     * @brief Lee la temperatura actual simulada
     * @return Temperatura actual en grados Celsius
     */
    float readTemp() const override;
    
    /**
     * @brief Lee la humedad actual simulada
     * @return Humedad actual en porcentaje
     */
    float readHumidity() const override;
};

#endif // MSFORECASTMOCK_H 