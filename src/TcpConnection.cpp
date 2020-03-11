#include "TcpConnection.h"
#include "TcpHandler.h"
#include "ThreadQueue.h"

#include <iostream>
#include <thread>
#include <vector>


int TcpConnection::init()
{

	m_serverMsg = "hello there";

	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cerr << "Unable to create socket" << std::endl;
		return -1;
	}

	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(m_port);
	if (bind(m_socket, (sockaddr*)&m_address, sizeof(m_address)) < 0)
	{
		std::cerr << "Unable to bind on the server" << std::endl;
		return -1;
	}

	if (listen(m_socket, 3) < 0)
	{
		std::cerr << "Unable to listen on socket" << std::endl;
		return -1;
	}

	FD_ZERO(&m_master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(m_socket, &m_master);

    return 0;
}

class Task
{
	public:
		static void test(int m_fd)
		{
			int valread;
			char buffer[1024] = {0}; 
			valread = read( m_fd , buffer, 1024); 
			printf("%s\n",buffer ); 
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			send(m_fd , "Hello there" , strlen("Hello there") , 0);
			shutdown(m_fd, 1);
		}
};

int TcpConnection::run()
{
	int newfd;
	int addrlen = sizeof(m_address); 

	std::thread appthreads[2];
	std::cout << "Listening on " << m_ipAddress << ":" << m_port << std::endl;

	while (true)
	{
		newfd = accept(m_socket, (struct sockaddr *)&m_address, (socklen_t*)&addrlen);
		if (newfd < 0)
		{
			return 1;
		}

		std::thread t(&TcpHandler::handle, newfd);
		t.detach();
	}

}
