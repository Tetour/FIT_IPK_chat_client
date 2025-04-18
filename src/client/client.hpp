#pragma once

#include <string>
#include <cstdint>

class Client {
public:
    Client(std::string serverAddress, uint16_t serverPort);
    virtual ~Client();

    virtual void run() = 0;

    std::string getUserId  () const { return userId;  }
    std::string getDname   () const { return dname;   }
    std::string getSecret  () const { return secret;  }

    bool setUserId (const std::string & userId );
    bool setDname  (const std::string & dname  );
    bool setSecret (const std::string & secret );

protected:
    std::string serverAddress;
    uint16_t    serverPort;

    std::string userId = "xvrskaa00";           // User ID
    std::string dname  = "Marcus Porcius Cato"; // Display name
    std::string secret = "fooo";                // Secret

    bool isIdValid      (const std::string & id             ) const;
    bool isSecretValid  (const std::string & secret         ) const;
    bool isContentValid (const std::string & messageContent ) const;
    bool isDnameValid   (const std::string & dname          ) const;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool sendMessage(const std::string & message) = 0;
    virtual bool recvMessage(      std::string & message) = 0;

    virtual std::string createMessageMsg  (std::string messageContent) const = 0;
    virtual std::string createMessageErr  (std::string messageContent) const = 0;
    virtual std::string createMessageJoin (std::string channelID    ) const = 0;
    virtual std::string createMessageAuth (                         ) const = 0;
    virtual std::string createMessageBye  (                         ) const = 0;
};
