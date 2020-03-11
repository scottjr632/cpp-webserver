#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <sys/types.h> 
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class TcpConnection
{
    public:
        TcpConnection(const char* ipAddress, int port):
            m_ipAddress(ipAddress), m_port(port) { }

        int  init();
        int  run();
        void handleConnection(int fd);
        // void startAccepting(ThreadQueue * tq);

    private:
        const char*     m_ipAddress;    // IP address the server will run on
        int             m_port;         // Port # for the web service
        int             m_socket;       // Internal FD for the listening socket
        fd_set          m_master;       // Master file descriptor set
        sockaddr_in     m_address;      // The address of the server
};