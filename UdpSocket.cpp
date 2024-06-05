#include "UdpSocket.h"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

UdpSocket::UdpSocket() : sockfd(-1), isConnected(false) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create socket: " + std::string(strerror(errno)));
    }
}

UdpSocket::~UdpSocket() {
    if (isConnected) {
        disconnectFromHost();
    }
    close(sockfd);
}

bool UdpSocket::bindPort(int port) {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        return false;
    }
    return true;
}

bool UdpSocket::connectToHost(const std::string& host, int port) {
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr) <= 0) {
        return false;
    }

    isConnected = true;
    return true;
}

void UdpSocket::disconnectFromHost() {
    isConnected = false;
}

bool UdpSocket::writeData(const std::string& data) {
    if (sendto(sockfd, data.c_str(), data.size(), 0,
               (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        return false;
    }
    return true;
}

std::string UdpSocket::readData() {
    char buffer[1024];
    socklen_t len = sizeof(serverAddr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&serverAddr, &len);
    if (n > 0) {
        buffer[n] = '\0'; // Ensure null-terminated string
        return std::string(buffer);
    }
    return "";
}

std::string UdpSocket::error() {
    return strerror(errno);
}
