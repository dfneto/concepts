/*
The sizeof operator in C returns the size in bytes of the type or expression provided to it. 
When you apply sizeof to a pointer, it returns the size of the pointer itself, not the size of the data it points to.

The size of a pointer depends on the architecture of the system:
On a 32-bit system, a pointer typically occupies 4 bytes (32 bits).
On a 64-bit system, a pointer typically occupies 8 bytes (64 bits).
*/

//%zu is used to format an argument of type size_t.

#include <stdio.h>

int main()
{
    typedef struct s_token
    {
        int                 type;
        char                *str;
        struct s_token      *next;
    } token;

	printf("Size of int: %zu Bytes\n", sizeof(int)); //4 Bytes
	printf("Size of char*: %zu Bytes\n", sizeof(char*));// 8 Bytes
	printf("Size of token*: %zu Bytes\n", sizeof(token *)); //8 Bytes
    printf("Size of token: %zu Bytes\n", sizeof(token)); //24 Bytes: sum of the sizes of its members: 4 (int) + 8 (char*) + 8 (token*) + padding
    printf("The size of pointer: On 64-bit systems, a pointer typically occupies 8 bytes (64 bits) as we can see:\n");
	printf("Size of int*: %zu Bytes\n", sizeof(int *)); //8 Bytes
    printf("Size of double*: %zu Bytes\n", sizeof(double *)); //8 Bytes
	printf("Size of char*: %zu Bytes\n", sizeof(char *)); //8 Bytes

    return (0);

}

/*
* What is padding:
The compiler is likely adding padding bytes to the structure for alignment purposes. This padding is often added to ensure that each member of the structure is aligned at an address that is a multiple of its size. This can help improve memory access performance.

In your structure, the int member has a size of 4 bytes, and the char* and token* members have a size of 8 bytes each on a typical 64-bit system. However, some compilers may add padding between the members to ensure proper alignment, which can result in additional bytes being added to the structure.

The padding added by the compiler can vary depending on the specific compiler, compiler flags, and target architecture. The size of the padding is often chosen to ensure that each member is aligned according to the architecture's requirements.

If you want to control the structure's size more precisely, you can use compiler-specific directives or attributes to control the packing and alignment of structure members. For example, in GCC, you can use the __attribute__((packed)) attribute to indicate that you want the structure to be packed without any padding:

typedef struct __attribute__((packed)) s_token
{
    int type;
    char* str;
    struct s_token* next;
} token;
Keep in mind that while using __attribute__((packed)) can reduce padding and control the size of the structure, it may also lead to slower memory access times on some architectures, so use it judiciously based on your specific requirements.
Use essa estrutura com __attribute__((packed)) no token e o mesmo código e terá:
Size of token: 20 Bytes
*/