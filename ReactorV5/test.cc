#include "EchoSrever.h"

int main()
{   
    EchoServer server(4, 10, "127.0.0.1", 10425);
    server.start();

    return 0;
}

