#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<inttypes.h>
#include <sys/mman.h>
#include <unistd.h>

/* Michael Neuling 4/12/2013
 *
 * See if the altivec state is leaked out of an aborted transaction due to
 * kernel vmx copy loops.
 *
 *   gcc -m64 htm_vmxcopy.c -o htm_vmxcopy
 *
 */

/* We don't use all of these, but for reference: */

#define TBEGIN	 "tbegin.	;\n"
#define TSUSPEND "tsr.	  0	;\n"
#define TABORT	 "tabort. 0	;\n"
#define TRESUME	 "tresume.	;\n"
#define TEND	 "tend.		;\n"

int main(int argc, char *argv[])
{
        long double vecin = 1.3;
        long double vecout;
        unsigned long pgsize = getpagesize();
        int i;
        int fd;
        int size = pgsize*16;
        char tmpfile[] = "/tmp/page_faultXXXXXX";
        char buf[pgsize];
        char *a;
        uint64_t aborted = 0;

        fd = mkstemp(tmpfile);
        assert(fd >= 0);

        memset(buf, 0, pgsize);
        for (i = 0; i < size; i += pgsize)
                assert(write(fd, buf, pgsize) == pgsize);

        unlink(tmpfile);

        a = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
        assert(a != MAP_FAILED);

        asm __volatile__(
                "lxvd2x 40,0,%[vecinptr] ; " // set 40 to initial value
                TBEGIN
                "beq    3f ;"
                TSUSPEND
                "xxlxor 40,40,40 ; " // set 40 to 0
                "std    5, 0(%[map]) ;" // cause kernel vmx copy page
                TABORT
                TRESUME
                TEND
                "li     %[res], 0 ;"
                "b      5f ;"
                "3: ;" // Abort handler
                "li     %[res], 1 ;"
                "5: ;"
                "stxvd2x 40,0,%[vecoutptr] ; "
                : [res]"=r"(aborted)
                : [vecinptr]"r"(&vecin),
                  [vecoutptr]"r"(&vecout),
                  [map]"r"(a)
                : "memory", "r0", "r3", "r4", "r5", "r6", "r7");

        if (aborted && (vecin != vecout)){
                printf("FAILED: vector state leaked on abort %f != %f\n",
                       (double)vecin, (double)vecout);
                exit(1);
        }

        munmap(a, size);

        close(fd);

        printf("PASSED!\n");
        return 0;
}

