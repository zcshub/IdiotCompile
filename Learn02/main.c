#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int token;
char *src, *old_src;
int poolsize;
int line;

void next() {
    token = *src++;
    return;
}


void expression(int level) {

}


void program() {
    next(); // get next token
    while (token > 0) {
        printf("%c", token);
        next();
    }
}

int eval() {
    return 0;
}


int main(int argc, char **argv) {
    int i, fd;
    
    argc --;
    argv ++;

    poolsize = 256 * 1024;
    line = 1;

    if ((fd = open(*argv, 0)) < 0) {
        printf("couldn't open %s\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("couldn't malloc %d size for source area\n", poolsize);
        return -1;
    }

    //read the source file
    if ((i = read(fd, src, poolsize-1)) <= 0) {
        printf("read return %d\n", i);
        return -1;
    }
    src[i] = 0; // add EOF character
    close(fd);

    program();
    return eval();
}