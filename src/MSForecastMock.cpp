#include "../include/MSForecastMock.h"
#include <iostream>
#include <algorithm>

MSForecastMock::MSForecastMock() : currentTemp(22.0), currentHumidity(45.0) {
    std::cout << "MSForecastMock inicializado - Temperatura: " << currentTemp 
              << "°C, Humedad: " << currentHumidity << "%" << std::endl;
}

bool MSForecastMock::upTemp(int x) {
    currentTemp += x;
    std::cout << "MSForecastMock: Temperatura aumentada en " << x 
              << "°C. Nueva temperatura: " << currentTemp << "°C" << std::endl;
    return true;
}

bool MSForecastMock::downTemp(int x) {
    currentTemp -= x;
    std::cout << "MSForecastMock: Temperatura disminuida en " << x 
              << "°C. Nueva temperatura: " << currentTemp << "°C" << std::endl;
    return true;
}

bool MSForecastMock::upHumidity(int x) {
    currentHumidity = std::min(100.0f, currentHumidity + x);
    std::cout << "MSForecastMock: Humedad aumentada en " << x 
              << "%. Nueva humedad: " << currentHumidity << "%" << std::endl;
    return true;
}

bool MSForecastMock::downHumidity(int x) {
    currentHumidity = std::max(0.0f, currentHumidity - x);
    std::cout << "MSForecastMock: Humedad disminuida en " << x 
              << "%. Nueva humedad: " << currentHumidity << "%" << std::endl;
    return true;
}

float MSForecastMock::readTemp() const {
    std::cout << "MSForecastMock: Leyendo temperatura actual: " 
              << currentTemp << "°C" << std::endl;
    return currentTemp;
}

float MSForecastMock::readHumidity() const {
    std::cout << "MSForecastMock: Leyendo humedad actual: " 
              << currentHumidity << "%" << std::endl;
    return currentHumidity;
} 