#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include "src/TcpConnection.h"

using namespace std;

int main()
{
    TcpConnection tcp("127.0.0.1", 8080);
    if (tcp.init() < 0)
    {
        cerr << "Unable to create tcp connection";
        return 1;
    }

    return tcp.run();
}