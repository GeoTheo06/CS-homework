#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LibQueue.h"
#include "LibStack.h"

int main(int argc, char *argv[])
{
    int n;

    scanf("%d", &n);

    Stack hangar = newStack(10);
    Queue runway = newQueue(10);

    int hangarCounter = 0;
    int runwayCounter = 0;

    char repair[4];
    int airplane;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %s", &airplane, repair);
        if (repair[0] == 'y')
        {
            push(airplane, &hangar);
            hangarCounter++;

            if (hangarCounter == 5)
            {

                // planes leave from runway
                for (int j = 0; j < runwayCounter; j++)
                {
                    printf("%d\n", dequeue(&runway));
                }

                // planes from hangar go to runway to wait
                for (int j = 0; j < hangarCounter; j++)
                {
                    enqueue(pop(&hangar), &runway);
                }

                // now runway has hangar planes and hangar is empty
                runwayCounter = hangarCounter;
                hangarCounter = 0;
            }
        }
        else
        {
            enqueue(airplane, &runway);
            runwayCounter++;

            if (runwayCounter == 7)
            {
                // all planes leave from the runway and it remains empty
                for (int i = 0; i < runwayCounter; i++)
                {
                    printf("%d\n", dequeue(&runway));
                }
                runwayCounter = 0;
            }
        }
    }

    // the remaining planes from the runway leave
    for (int i = 0; i < runwayCounter; i++)
    {
        printf("%d\n", dequeue(&runway));
    }

    // the remaining planes from the hangar leave
    for (int i = 0; i < hangarCounter; i++)
    {
        printf("%d\n", pop(&hangar));
    }

    freeStack(hangar);
    freeQueue(runway);

    return 0;
}
