#include "UdpSocket.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

int main()
{
    UdpSocket udpSocket;
    if (udpSocket.bindPort(9080))
    {
        std::cout << "Server bound to port 9080" << std::endl;
        while (true)
        {
            std::string receivedData = udpSocket.readData();
            if (!receivedData.empty())
            {
                std::cout << "Received: " << receivedData << std::endl;

                // 去除字符串前后的空白字符
                receivedData.erase(std::remove_if(receivedData.begin(), receivedData.end(), [](unsigned char c){ return std::isspace(c); }), receivedData.end());

                if (receivedData == "quit()")
                {
                    break;
                }
            }
        }
    }
    else
    {
        std::cerr << "Failed to bind port: " << udpSocket.error() << std::endl;
    }
    return 0;
}
