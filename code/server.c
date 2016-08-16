#include <cargo.h>
#include <stdio.h>

#define DEFAULT_PORT 9876

int
main(
    int   argc,
    char* argv[])
{
    char* portStr = cargoFlag("port", "0", argc, argv);
    int   port    = atoi(portStr);

    if (0 == portStr) port = DEFAULT_PORT;

    printf("will listen on port %d (UDP)\n", port);

    return 0;
}
