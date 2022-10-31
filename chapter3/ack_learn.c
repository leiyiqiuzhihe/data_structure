#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100

int ackerman(int m, int n);


int main(int argc, char * argv[])
{
    int m = 0;
    int n = 0;
    int result = 0;

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    result = ackerman(m, n);
    printf("result is: %d",result);

    return 0;
}


int ackerman(int m, int n)
{
    int ack[N][N];
    int i = 0;
    int j = 0;

    memset(ack,0,sizeof(ack));
    for (j = 0; j < N; j++)
         ack[0][j] = j + 1;
    for (i = 1; i < N; i++)
    {
        ack[i][0] = ack[i-1][1];
        for (j = 1; j < N; j++)
            ack[i][j] = ack[i-1][ack[i][j-1]];
    }

    return ack[m][n];

}
