#include <stdio.h>

int n,p[10000],a[100][100];

void afis()
{
    int i, j;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

int bun(int i, int j)
{
    if(i > 1) if(a[i-1][j] % 2 == a[i][j] % 2) return 0;
    if(j > 1) if(a[i][j-1] % 2 == a[i][j] % 2) return 0;
    return 1;
}

void back(int i, int j)
{
    for(int v = 1; v <= n * n; v++)
        if(!p[v])
        {
            a[i][j] = v;
            p[v] = 1;
            if(bun(i,j))
            {
                if(i == n && j == n)
                {
                    afis();
                }
                else if(j < n)
                {
                    back(i, j + 1);
                }
                else
                {
                    back(i + 1, 1);
                }
            }
            p[v] = 0;
        }
}

int main()
{
    printf("Introduceti numarul: ");
    scanf("%d", &n);
    back(1, 1);
    return 0;
}

