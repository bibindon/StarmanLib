#include "main.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    WriteCsv(argv[1]);

    return 0;
}
