#include <stdio.h>

int main(){
       asm ("tbegin.  \n\t");
       asm goto ("beq %l[failure] \n\t" : : : : failure);
       asm ("treclaim. 0\n\t");
       asm ("tend.\n\t");

       printf("Failure\n");
       return 1;

failure:
       return 0;
}

