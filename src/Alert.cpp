#include "../include/Alert.h"
#include <sstream>
#include <iomanip>
#include <ctime>

Alert::Alert() : id(0), message(""), severity(AlertSeverity::LOW), timestamp(time(nullptr)) {}

Alert::Alert(const std::string& msg, AlertSeverity sev) 
    : id(0), message(msg), severity(sev), timestamp(time(nullptr)) {}

Alert::Alert(int id, const std::string& msg, AlertSeverity sev, time_t ts) 
    : id(id), message(msg), severity(sev), timestamp(ts) {}

// Getters
int Alert::getId() const { return id; }
std::string Alert::getMessage() const { return message; }
AlertSeverity Alert::getSeverity() const { return severity; }
time_t Alert::getTimestamp() const { return timestamp; }

// Setters
void Alert::setId(int id) { this->id = id; }
void Alert::setMessage(const std::string& msg) { message = msg; }
void Alert::setSeverity(AlertSeverity sev) { severity = sev; }
void Alert::setTimestamp(time_t ts) { timestamp = ts; }

std::string Alert::getSeverityString() const {
    switch (severity) {
        case AlertSeverity::LOW: return "BAJA";
        case AlertSeverity::MEDIUM: return "MEDIA";
        case AlertSeverity::HIGH: return "ALTA";
        case AlertSeverity::CRITICAL: return "CRÍTICA";
        default: return "DESCONOCIDA";
    }
}

std::string Alert::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id 
        << " | Severidad: " << getSeverityString()
        << " | Mensaje: " << message
        << " | Fecha: " << getDateTimeString();
    return oss.str();
}

std::string Alert::getDateTimeString() const {
    std::ostringstream oss;
    struct tm* timeinfo = localtime(&timestamp);
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
} 