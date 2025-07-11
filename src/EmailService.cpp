#include "../include/EmailService.h"
#include <iostream>
#include <sstream>

EmailService::EmailService(const std::string& server, int port, 
                          const std::string& email, const std::string& password)
    : smtpServer(server), smtpPort(port), senderEmail(email), 
      senderPassword(password) {
    
    // Agregar destinatarios por defecto
    recipients.push_back("admin@empresa.com");
    recipients.push_back("tech@empresa.com");
    
    std::cout << "EmailService: Inicializado con servidor " << smtpServer 
              << ":" << smtpPort << std::endl;
}

EmailService::~EmailService() {
    std::cout << "EmailService: Destruyendo servicio de email" << std::endl;
}

bool EmailService::sendEmail(const std::string& to, const std::string& subject, const std::string& body) {
    // Simular envío de email
    std::cout << "EmailService: Enviando email..." << std::endl;
    std::cout << "  De: " << senderEmail << std::endl;
    std::cout << "  Para: " << to << std::endl;
    std::cout << "  Asunto: " << subject << std::endl;
    std::cout << "  Cuerpo: " << body << std::endl;
    std::cout << "EmailService: Email enviado exitosamente (simulado)" << std::endl;
    
    return true;
}

bool EmailService::sendAlert(const Alert& alert) {
    std::cout << "EmailService: Enviando alerta a todos los destinatarios" << std::endl;
    
    bool allSent = true;
    for (const auto& recipient : recipients) {
        if (!sendAlert(alert, recipient)) {
            allSent = false;
        }
    }
    
    return allSent;
}

bool EmailService::sendAlert(const Alert& alert, const std::string& recipientEmail) {
    std::string subject = "ALERTA DATACENTER - " + alert.getSeverityString();
    
    std::ostringstream body;
    body << "ALERTA DEL SISTEMA DE CLIMA DEL DATACENTER\n\n";
    body << "Severidad: " << alert.getSeverityString() << "\n";
    body << "Mensaje: " << alert.getMessage() << "\n";
    body << "Timestamp: " << alert.getDateTimeString() << "\n\n";
    body << "Este es un mensaje automático del sistema de control de clima.\n";
    
    return sendEmail(recipientEmail, subject, body.str());
}

void EmailService::addRecipient(const std::string& email) {
    // Verificar si el email ya existe
    for (const auto& recipient : recipients) {
        if (recipient == email) {
            std::cout << "EmailService: El email " << email << " ya está en la lista" << std::endl;
            return;
        }
    }
    
    recipients.push_back(email);
    std::cout << "EmailService: Agregado destinatario " << email << std::endl;
}

void EmailService::removeRecipient(const std::string& email) {
    for (auto it = recipients.begin(); it != recipients.end(); ++it) {
        if (*it == email) {
            recipients.erase(it);
            std::cout << "EmailService: Eliminado destinatario " << email << std::endl;
            return;
        }
    }
    
    std::cout << "EmailService: El email " << email << " no se encontró en la lista" << std::endl;
}

std::vector<std::string> EmailService::getRecipients() const {
    return recipients;
}

void EmailService::setRecipients(const std::vector<std::string>& newRecipients) {
    recipients = newRecipients;
    std::cout << "EmailService: Lista de destinatarios actualizada" << std::endl;
}

bool EmailService::isValidConfiguration() const {
    return !smtpServer.empty() && smtpPort > 0 && 
           !senderEmail.empty() && !senderPassword.empty() && 
           !recipients.empty();
} 