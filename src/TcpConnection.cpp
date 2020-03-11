#include "TcpConnection.h"
#include "TcpHandler.h"
#include "ThreadQueue.h"

#include <iostream>
#include <thread>
#include <vector>


int TcpConnection::init()
{

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
	FD_SET(m_socket, &m_master);

    return 0;
}

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
