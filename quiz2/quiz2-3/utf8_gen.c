#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int n = atoi(argv[1]);
    FILE *fp;
    fp = fopen(argv[2],"w+");
    char c1,c2,c3,c4;
    while(n--) {
        double p = (double) rand() / RAND_MAX;
        if(p < 0.25) {
            fprintf(fp,"%c",(char)(rand() & 0x7f));
        }
        else if(p < 0.5) {
            c1 = (char)rand() & 0x1f;
            c1 = c1 | 0xc0;
            c2 = (char)rand() & 0x3f;
            c2 = c2 | 0x80;
            fprintf(fp,"%c%c",c1,c2);
        }
        else if(p < 0.75) {
            c1 = (char)rand() & 0xf;
            c1 = c1 | 0xe0;
            c2 = (char)rand() & 0x3f;
            c2 = c2 | 0x80;
            c3 = (char)rand() & 0x3f;
            c3 = c3 | 0x80;
            fprintf(fp,"%c%c%c",c1,c2,c3);
        }
        else {
            c1 = (char)rand() & 0x7;
            c1 = c1 | 0xf0;
            c2 = (char)rand() & 0x3f;
            c2 = c2 | 0x80;
            c3 = (char)rand() & 0x3f;
            c3 = c3 | 0x80;
            c4 = (char)rand() & 0x3f;
            c4 = c4 | 0x80;
            fprintf(fp,"%c%c%c%c",c1,c2,c3,c4);
        }
    }
}