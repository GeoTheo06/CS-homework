#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   Parse a dotted-decimal IP string (e.g. "192.168.1.128")
   into a 32-bit unsigned int.
*/
unsigned int parse_ip(char *ip_str)
{
    unsigned int a, b, c, d;
    sscanf(ip_str, "%u.%u.%u.%u", &a, &b, &c, &d);
    return ((a & 0xFF) << 24) | ((b & 0xFF) << 16) | ((c & 0xFF) << 8) | (d & 0xFF);
}

/*
   Given a prefix length p, compute the corresponding mask.
   e.g. p = 24 => 0xFFFFFF00
*/
unsigned int prefix_to_mask(unsigned int p)
{
    if (p == 0)
    {
        return 0;
    }
    return 0xFFFFFFFF << (32 - p);
}

int main(void)
{
    int M;
    scanf("%d", &M);

    /* Parallel arrays instead of using a struct */
    unsigned int *route_network = (unsigned int *)malloc(M * sizeof(unsigned int));
    unsigned int *route_prefix = (unsigned int *)malloc(M * sizeof(unsigned int));
    unsigned int *route_output = (unsigned int *)malloc(M * sizeof(unsigned int));

    if (!route_network || !route_prefix || !route_output)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    /* Read the M routes */
    for (int i = 0; i < M; i++)
    {
        char route_str[64];
        int output;
        scanf("%s %d", route_str, &output);

        /* Split route_str into "ip" and "prefix" if there's a slash */
        char *slash = strchr(route_str, '/');
        unsigned int prefix = 32; // default to /32 if no slash

        if (slash != NULL)
        {
             // end the IP part
            prefix = (unsigned int)atoi(slash + 1);
        }

        /* Convert IP to 32-bit integer */
        unsigned int ip = parse_ip(route_str);
        /* Convert prefix to mask and compute the network part */
        unsigned int mask = prefix_to_mask(prefix);
        unsigned int network = ip & mask;

        route_network[i] = network;
        route_prefix[i] = prefix;
        route_output[i] = (unsigned int)output;
    }

    /* Read the number of queries */
    int N;
    scanf("%d", &N);

    /* Process each query */
    for (int i = 0; i < N; i++)
    {
        char ip_str[64];
        scanf("%s", ip_str);

        /* Parse query IP into a 32-bit integer */
        unsigned int ip = parse_ip(ip_str);

        int best_output = -1;
        unsigned int best_prefix = 0;

        /* Compare against all routes for the longest prefix match */
        for (int j = 0; j < M; j++)
        {
            unsigned int p = route_prefix[j];
            unsigned int mask = prefix_to_mask(p);

            /* Check if query IP belongs to this route's network */
            if ((ip & mask) == route_network[j])
            {
                /* If this prefix is longer than what we have so far, update */
                if (p > best_prefix)
                {
                    best_prefix = p;
                    best_output = (int)route_output[j];
                }
            }
        }

        /* Print the best match output for this query */
        printf("%d\n", best_output);
    }

    free(route_network);
    free(route_prefix);
    free(route_output);

    return 0;
}
