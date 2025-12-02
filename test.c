# include <stdio.h>

typedef struct data1
{
    char    *s1;
    char    *s2;
    char    *s3;
}   data1;


typedef struct data2
{
    int     n1;
    int     n2;
    char    *s1;
    char    *s2;
    char    *s3;
}   data2;

void print(void *p)
{
    data1 *d1 = p;
    printf("%s\n", d1->s1);
    printf("%s\n", d1->s2);
    printf("%s\n", d1->s3);
}

int main()
{
    data2 d2;
    d2.n1 = 10;
    d2.n1 = 1111;
    d2.s1 = "name1";
    d2.s2 = "name2";
    d2.s3 = "name3";
    print((void *)&d2);
}