#include <stdio.h>
#include <stdlib.h>

#define N 10

int main()
{
    int frames, i, j, k, l, flag, count = 0, faults = 0;
    int *queue, *counter, *referenceString;
    int *frame, *next;

    printf("Enter number of frames : ");
    scanf("%d", &frames);

    queue = (int *)malloc(frames * sizeof(int));
    counter = (int *)calloc(N, sizeof(int));
    referenceString = (int *)malloc(N * sizeof(int));
    frame = (int *)malloc(frames * sizeof(int));
    next = (int *)malloc(frames * sizeof(int));

    printf("Enter reference string : ");
    for (i = 0; i < N; i++)
        scanf("%d", &referenceString[i]);

    for (i = 0; i < frames; i++)
    {
        queue[i] = -1;
        frame[i] = -1;
        next[i] = i;
    }

    for (i = 0; i < N; i++)
    {
        flag = 0;
        for (j = 0; j < frames; j++)
        {
            if (queue[j] == referenceString[i])
            {
                flag = 1;
                counter[j] = i;
                break;
            }
        }

        if (flag == 0)
        {
            if (count < frames)
            {
                queue[count] = referenceString[i];
                frame[count] = i;
                counter[count] = i;
                count++;
                faults++;
            }
            else
            {
                l = next[0];
                k = 0;
                for (j = 1; j < frames; j++)
                {
                    if (counter[j] < counter[k])
                    {
                        k = j;
                        l = next[j];
                    }
                }
                queue[l] = referenceString[i];
                frame[l] = i;
                counter[l] = i;
                next[k] = l;
                faults++;
            }
        }
    }

    printf("Page Faults : %d", faults);

    return 0;
}
