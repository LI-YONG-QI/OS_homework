#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int n = atoi(argv[1]); 
    int pageNumber = n / 4096;
    int offset = n - pageNumber*4096;

    printf("The address %d contains\n", n);
    printf("page number = %d\n", pageNumber);
    printf("offset = %d\n", offset);
    return 0;
}
