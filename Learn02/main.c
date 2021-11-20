#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;
char *src, *old_src;
int poolsize;
int line;

// 用于词法分析，获取下一个标记，它将自动忽略空白字符。
void next() {
    token = *src++;
    return;
}

// 用于解析一个表达式
void expression(int level) {

}

// 语法分析的入口，分析整个 C 语言程序。
void program() {
    next(); // get next token
    while (token > 0) {
        printf("token is %c\n", token);
        next();
    }
}

// 虚拟机的入口，用于解释目标代码。
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
    if (i = read(fd, src, poolsize-1) <= 0) {
        printf("read return %d\n", i);
        return -1;
    }
    src[i] = 0; // add EOF character
    close(fd);

    program();
    return eval();
}