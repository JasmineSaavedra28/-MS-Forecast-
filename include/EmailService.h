#ifndef EMAILSERVICE_H
#define EMAILSERVICE_H

#include <string>
#include <vector>
#include "Alert.h"

/**
 * @brief Clase para manejar el envío de alertas por email
 * 
 * Esta clase se encarga de enviar notificaciones por email
 * cuando se generan alertas en el sistema de control de clima.
 * En esta implementación se simula el envío de emails.
 */
class EmailService {
private:
    std::string smtpServer;         ///< Servidor SMTP
    int smtpPort;                   ///< Puerto SMTP
    std::string senderEmail;        ///< Email del remitente
    std::string senderPassword;     ///< Contraseña del remitente
    std::vector<std::string> recipients; ///< Lista de destinatarios
    
    /**
     * @brief Simula el envío de un email
     * @param to Destinatario
     * @param subject Asunto del email
     * @param body Cuerpo del email
     * @return true si se envió exitosamente, false en caso contrario
     */
    bool sendEmail(const std::string& to, const std::string& subject, const std::string& body);

public:
    /**
     * @brief Constructor
     * @param server Servidor SMTP
     * @param port Puerto SMTP
     * @param email Email del remitente
     * @param password Contraseña del remitente
     */
    EmailService(const std::string& server = "smtp.gmail.com", 
                 int port = 587,
                 const std::string& email = "datacenter@empresa.com",
                 const std::string& password = "password123");
    
    /**
     * @brief Destructor
     */
    ~EmailService();
    
    /**
     * @brief Envía una alerta por email a todos los destinatarios
     * @param alert Alerta a enviar
     * @return true si se envió exitosamente, false en caso contrario
     */
    bool sendAlert(const Alert& alert);
    
    /**
     * @brief Envía una alerta por email a un destinatario específico
     * @param alert Alerta a enviar
     * @param recipientEmail Email del destinatario
     * @return true si se envió exitosamente, false en caso contrario
     */
    bool sendAlert(const Alert& alert, const std::string& recipientEmail);
    
    /**
     * @brief Agrega un destinatario a la lista
     * @param email Email del destinatario
     */
    void addRecipient(const std::string& email);
    
    /**
     * @brief Elimina un destinatario de la lista
     * @param email Email del destinatario
     */
    void removeRecipient(const std::string& email);
    
    /**
     * @brief Obtiene la lista de destinatarios
     * @return Vector con los emails de los destinatarios
     */
    std::vector<std::string> getRecipients() const;
    
    /**
     * @brief Configura la lista de destinatarios
     * @param recipients Vector con los emails de los destinatarios
     */
    void setRecipients(const std::vector<std::string>& recipients);
    
    /**
     * @brief Verifica la configuración del servicio de email
     * @return true si la configuración es válida, false en caso contrario
     */
    bool isValidConfiguration() const;
};

#endif // EMAILSERVICE_H 