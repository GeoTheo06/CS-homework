#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert the string IP into an integer, knowing that each 0 <= oct <= 255
int parseIp(char *ipStr)
{
    int a, b, c, d;
    sscanf(ipStr, "%u.%u.%u.%u", &a, &b, &c, &d);

    // Each oct goes to its position using bitwise shift
    return (a << 24) | (b << 16) | (c << 8) | d;
}

// Create a mask with prefix # of leading 1's and trailing 0's  
int prefixToMask(int prefix)
{
    return prefix == 0 ? 0 : 0xFFFFFFFF << (32 - prefix);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *networks = (int *)malloc(n * sizeof(int));
    int *prefixes = (int *)malloc(n * sizeof(int));
    int *outputs = (int *)malloc(n * sizeof(int));

    // Create routing table
    for (int i = 0; i < n; i++)
    {
        int prefix;
        int output;
        char subnetIpStr[64];

        scanf("%s %d", subnetIpStr, &output);

        // Split subnetIpStr into "subnetIp" and "prefix" based on the slash
        char *slash = strchr(subnetIpStr, '/');
        prefix = (int)atoi(slash + 1);

        int subnetIp = parseIp(subnetIpStr);
        int mask = prefixToMask(prefix);
        // Keep the network section of the IP address 
        int network = subnetIp & mask;
        networks[i] = network;
        prefixes[i] = prefix;
        outputs[i] = output;
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char ipStr[20];
        int bestOutput = -1;
        int bestPrefix = -1;
        scanf("%s", ipStr);

        int ip = parseIp(ipStr);

        // Compare the address to the entries of the routing table
        for (int j = 0; j < n; j++)
        {
            int mask = prefixToMask(prefixes[j]);
            // Longest prefix is best prefix
            if ((ip & mask) == networks[j] && (int)prefixes[j] > bestPrefix)
            {
                bestPrefix = prefixes[j];
                bestOutput = (int)outputs[j];
            }
        }
        printf("%d \n", bestOutput);
    }
    free(outputs);
    free(prefixes);
    free(networks);
    return 0;
}
