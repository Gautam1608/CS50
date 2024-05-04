#include<stdio.h>

typedef struct{
    int a;
    int b;
} test;

int main(){
    test ab = malloc(2*sizeof(test));
    ab[0].a=5;
    ab[0].b=6;
    ab[1].a=15;
    ab[1].b=16;
    printf("%d %d\n",ab[0].a,ab[0].b);

    test cd = malloc(2*sizeof(test));

    printf("%d %d\n",ab.a,ab.b);
    printf("%d %d\n",cd.a,cd.b);

    ab.a=1000;
        printf("%d %d\n",ab.a,ab.b);
    printf("%d %d\n",cd.a,cd.b);
}
