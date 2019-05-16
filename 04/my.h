#ifndef _TEST_H
#define _TEST_H

struct operation {
    
    void (*opstype[10])(int,int);
};

struct operation ops;

void init(void (*opstype)(int,int));
void use(void (*opstype)(int,int));

#endif
