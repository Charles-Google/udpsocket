#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class UdpSocket {
public:
    UdpSocket() {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            std::cerr << "Error creating socket" << std::endl;
        }
    }

    bool connectToHost(const std::string& ip, int port) {
        this->port = port;
        this->ip = ip;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        if (inet_pton(AF_INET, ip.c_str(), &servaddr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported" << std::endl;
            return false;
        }
        return true;
    }

    void writeData(const std::string& msg) {
        sendto(sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    }

    bool error() {
        int err = errno;
        if (err != 0) {
            std::cerr << "Socket error: " << strerror(err) << std::endl;
            return true;
        }
        return false;
    }

private:
    int sockfd;
    struct sockaddr_in servaddr;
    std::string ip;
    int port;
};

void testClient(UdpSocket &clientsocket) {
    if (clientsocket.connectToHost("127.0.0.1", 9080)) {
        std::cout << "--------发送quit()取消连接--------" << std::endl;
        std::cout << "套接字建立成功，输入以发送消息到服务器端..." << std::endl;
        while (true) {
            std::string msg;
            std::cin >> msg;
            if (msg == "quit") {
                std::cout << "退出连接" << std::endl;
                break;
            }
            clientsocket.writeData(msg);
            if (clientsocket.error()) {
                std::cout << "Socket error!" << std::endl;
                break;
            }
        }
    } else {
        std::cerr << "无法连接到服务器" << std::endl;
    }
}

int main() {
    UdpSocket clientsocket;
    testClient(clientsocket);
    return 0;
}
