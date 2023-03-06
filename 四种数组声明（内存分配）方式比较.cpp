#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
int main()
{
    byte bytes_array[32];
    byte *new_bytes_array = new byte[32];
    byte *malloc_bytes_array = (byte *)malloc(sizeof(byte) * 32);
    byte *calloc_bytes_array = (byte *)calloc(32, 1);
    printf(
        "\nsizeof(bytes_array)    >>>     %-8llu\nsizeof(bytes_array[0])    >>>    %-8llu\nsizeof(&bytes_array)    >>>    %-8llu\nsizeof(bytes_array) / sizeof(bytes_array[0])    >>>    %-8llu\n\n",
        sizeof(bytes_array),
        sizeof(bytes_array[0]),
        sizeof(&bytes_array),
        sizeof(bytes_array) / sizeof(bytes_array[0]));
    printf(
        "\nsizeof(new_bytes_array)    >>>     %-8llu\nsizeof(new_bytes_array[0])    >>>    %-8llu\nsizeof(&new_bytes_array)    >>>    %-8llu\nsizeof(new_bytes_array) / sizeof(new_bytes_array[0])    >>>    %-8llu\n\n",
        sizeof(new_bytes_array),
        sizeof(new_bytes_array[0]),
        sizeof(&new_bytes_array),
        sizeof(new_bytes_array) / sizeof(new_bytes_array[0]));
    printf(
        "\nsizeof(malloc_bytes_array)    >>>     %-8llu\nsizeof(malloc_bytes_array[0])    >>>    %-8llu\nsizeof(&malloc_bytes_array)    >>>    %-8llu\nsizeof(malloc_bytes_array) / sizeof(malloc_bytes_array[0])    >>>    %-8llu\n\n",
        sizeof(malloc_bytes_array),
        sizeof(malloc_bytes_array[0]),
        sizeof(&malloc_bytes_array),
        sizeof(malloc_bytes_array) / sizeof(malloc_bytes_array[0]));
    printf(
        "\nsizeof(calloc_bytes_array)    >>>     %-8llu\nsizeof(calloc_bytes_array[0])    >>>    %-8llu\nsizeof(&calloc_bytes_array)    >>>    %-8llu\nsizeof(calloc_bytes_array) / sizeof(calloc_bytes_array[0])    >>>    %-8llu\n\n",
        sizeof(calloc_bytes_array),
        sizeof(calloc_bytes_array[0]),
        sizeof(&calloc_bytes_array),
        sizeof(calloc_bytes_array) / sizeof(calloc_bytes_array[0]));

    return 0;
}
