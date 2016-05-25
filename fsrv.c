#include <cargo.h>
#include <stdio.h>

int main(
    int   argc,
    char* argv[])
{

    char* portStr = cargoFlag("port", "9876", argc, argv);
    int   port    = atoi(portStr);

    if (0 == portStr) port = 9876;

    printf("will listen on port %d (UDP)\n", port);

}
