#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int allocation[10][10], max[10][10];
    int need[10][10], available[10];
    int work[10], finish[10] = {0};
    int safeSequence[10], count = 0, found;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Initialize Work = Available
    for (j = 0; j < m; j++)
        work[j] = available[j];

    // Safety Algorithm
    while (count < n)
    {
        found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;

                if (j == m)
                {
                    for (k = 0; k < m; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    safeSequence[count++] = i;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    if (count == n)
    {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
            printf("P%d ", safeSequence[i]);

        printf("\n");
    }
    else
    {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    return 0;
}