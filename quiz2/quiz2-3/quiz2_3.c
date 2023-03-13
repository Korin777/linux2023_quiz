#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


size_t count_utf8(const char *buf, size_t len);
size_t swar_count_utf8(const char *buf, size_t len);


int main(int argc, char *argv[]) {
    if(argc < 2)
        printf("missing input file\n"), exit(1);

    FILE *fp = fopen(argv[1],"r");
    long lSize;
    char *buffer;

    if( !fp ) 
        perror("file not found"),exit(1);

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    // printf("%ld\n",lSize);
    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) 
        fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( fread( buffer , lSize, 1 , fp) != 1 )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    clock_gettime(CLOCK_REALTIME, &start);
    #ifdef SWAR
    swar_count_utf8(buffer,lSize);
    // printf("%ld\n",swar_count_utf8(buffer,lSize));
    #else
    count_utf8(buffer,lSize);
    // printf("%ld\n",count_utf8(buffer,lSize));
    #endif
    clock_gettime(CLOCK_REALTIME, &end);
    // printf("time passed is: %ld ms\n",(end.tv_sec - start.tv_sec)*1000 + (end.tv_nsec - start.tv_nsec)/1000000);
    printf("%ld",(end.tv_sec - start.tv_sec)*1000 + (end.tv_nsec - start.tv_nsec)/1000000);
    fclose(fp);
    free(buffer);
}


size_t count_utf8(const char *buf, size_t len)
{
    const int8_t *p = (const int8_t *) buf;
    size_t counter = 0;
    for (size_t i = 0; i < len; i++) {
        /* -65 is 0b10111111, anything larger in two-complement's should start
         * new code point.
         */
        if (p[i] > -65)
            counter++;
    }
    return counter;
}

size_t swar_count_utf8(const char *buf, size_t len)
{
    const uint64_t *qword = (const uint64_t *) buf;
    const uint64_t *end = qword + (len >> 3);

    size_t count = 0;
    for (; qword != end; qword++) {
        const uint64_t t0 = *qword;
        const uint64_t t1 = ~t0;
        const uint64_t t2 = t1 & 0x04040404040404040llu;
        const uint64_t t3 = t2 + t2;
        const uint64_t t4 = t0 & t3;
        count += __builtin_popcountll(t4);
    }

    count = ((len >> 3) << 3) - count;
    count += (len & 7) ? count_utf8((const char *) end, len & 7) : 0;

    return count;
}

