#pragma once

#ifndef _TCPHANDLER_H
#define _TCPHANDLER_H

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
#include <thread>
#include <vector>

struct request_line;
void print_request_line(request_line rl);

class TcpHandler
{
    public:
        TcpHandler(int fd):
            m_fd(fd){  }
        static void handle(int fd);

        void handle_get();
        void handle_post();
        void switch_on_method(const char * method);

        request_line get_request_line(std::string request);   // returns the request line of the http request

    private:
        int m_fd;
        int m_valread;

        static std::vector<std::string> tokenize(const char *str, char d);
};

#endif // !_TCPHANDLER_H