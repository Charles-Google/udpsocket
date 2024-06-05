#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket {
private:
    int sockfd;
    struct sockaddr_in serverAddr;
    bool isConnected;

public:
    UdpSocket();
    ~UdpSocket();

    bool bindPort(int port);
    bool connectToHost(const std::string& host, int port);
    void disconnectFromHost();
    bool writeData(const std::string& data);
    std::string readData();
    std::string error();
};

#endif
