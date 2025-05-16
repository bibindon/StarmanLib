#include "main.h"

int main(int argc, wchar_t* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    WriteBinary(argv[1]);

    return 0;
}

