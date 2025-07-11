#include "../include/ClimateReading.h"
#include <sstream>
#include <iomanip>
#include <ctime>

ClimateReading::ClimateReading() : id(0), temperature(0.0), humidity(0.0), timestamp(time(nullptr)) {}

ClimateReading::ClimateReading(float temp, float hum) 
    : id(0), temperature(temp), humidity(hum), timestamp(time(nullptr)) {}

ClimateReading::ClimateReading(int id, float temp, float hum, time_t ts) 
    : id(id), temperature(temp), humidity(hum), timestamp(ts) {}

// Getters
int ClimateReading::getId() const { return id; }
float ClimateReading::getTemperature() const { return temperature; }
float ClimateReading::getHumidity() const { return humidity; }
time_t ClimateReading::getTimestamp() const { return timestamp; }

// Setters
void ClimateReading::setId(int id) { this->id = id; }
void ClimateReading::setTemperature(float temp) { temperature = temp; }
void ClimateReading::setHumidity(float hum) { humidity = hum; }
void ClimateReading::setTimestamp(time_t ts) { timestamp = ts; }

std::string ClimateReading::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id 
        << " | Temperatura: " << std::fixed << std::setprecision(1) << temperature << "°C"
        << " | Humedad: " << std::fixed << std::setprecision(1) << humidity << "%"
        << " | Fecha: " << getDateTimeString();
    return oss.str();
}

std::string ClimateReading::getDateTimeString() const {
    std::ostringstream oss;
    struct tm* timeinfo = localtime(&timestamp);
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
} 