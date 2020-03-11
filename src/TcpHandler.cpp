#include "TcpHandler.h"

using namespace std;

typedef struct request_line
{
    const char * method_token;
    const char * request_target;
    const char * protocol_version;
} request_line_t;

void print_request_line(request_line_t rl)
{
    printf("Method: %s\n", rl.method_token);
    printf("Target: %s\n", rl.request_target);
    printf("Version: %s\n", rl.protocol_version);
}

void TcpHandler::handle(int fd)
{
    TcpHandler * handler = new TcpHandler(fd);
    // std::string method = handler->getMethod();

    int valread;
    char buffer[1024] = {0}; 
    valread = read( fd , buffer, 1024); 

    std::string request = buffer;
    request_line_t rt = handler->get_request_line(request);
    print_request_line(rt);
    handler->switch_on_method(rt.method_token);
    
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // send(fd , "Hello there" , strlen("Hello there") , 0);
    shutdown(fd, 1);
}


request_line TcpHandler::get_request_line(std::string request)
{
    std::istringstream str(request);
    std::string line;

    std::getline(str, line);
    
    std::vector<string> tokenized = tokenize(line.c_str(), ' ');
    request_line_t lt;
    if (tokenized.size() == 3)
    {
        lt.method_token = tokenized.at(0).c_str();
        lt.request_target = tokenized.at(1).c_str();
        lt.protocol_version = tokenized.at(2).c_str();
    }

    return lt;
}

void TcpHandler::switch_on_method(const char * method)
{
    if (strncmp(method, "GET", sizeof("GET")) == 0)
    {
        this->handle_get();
    } else if (strncmp(method, "POST", sizeof("POST")) == 0)
    {
        this->handle_post();
    }
}

void TcpHandler::handle_get()
{
    send(m_fd , "You sent a get request" , strlen("You sent a get request") , 0);
}

void TcpHandler::handle_post()
{
    send(m_fd , "You sent a POST request" , strlen("You sent a get request") , 0);
}

std::vector<string> TcpHandler::tokenize(const char *str, char d = ' ')
{
    std::vector<string> result;
    do
    {
        const char *begin = str;
        while (*str != d && *str)
            str++;
        
        result.push_back(string(begin, str));
    } while (0 != *str++);
    return result;
}