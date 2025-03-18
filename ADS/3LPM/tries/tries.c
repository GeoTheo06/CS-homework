#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie
{
    int output;
    struct trie *children[2];
} trie;

trie *insertBit()
{
    trie *bit = malloc(sizeof(trie));
    bit->children[0] = NULL;
    bit->children[1] = NULL;
    bit->output = -1;
    return bit;
}

void freeTrie(trie *root)
{
    if (root == NULL)
        return;

    freeTrie(root->children[0]);
    freeTrie(root->children[1]);

    free(root);
}

// Convert the string IP into an integer, knowing that each 0 <= oct <= 255
unsigned int parseIp(char *ipStr)
{
    unsigned int a, b, c, d;
    sscanf(ipStr, "%u.%u.%u.%u", &a, &b, &c, &d);

    // Each oct goes to its position using bitwise shift
    return ((a & 0xFF) << 24) | ((b & 0xFF) << 16) | ((c & 0xFF) << 8) | (d & 0xFF);
}

// Create a mask with prefix # of leading 1's and trailing 0's
unsigned int prefixToMask(unsigned int prefix)
{
    return prefix == 0 ? 0 : 0xFFFFFFFF << (32 - prefix);
}

int main()
{
    int n, bit = 0, output = 0;
    scanf("%d", &n);
    trie *root = insertBit();

    // Create routing table
    for (int i = 0; i < n; i++)
    {
        unsigned int prefix = 0U;
        char subnetIpStr[64];

        scanf("%s %d", subnetIpStr, &output);

        // Split subnetIpStr into "subnetIp" and "prefix" based on the slash
        char *slash = strchr(subnetIpStr, '/');
        prefix = (unsigned int)atoi(slash + 1);

        unsigned int subnetIp = parseIp(subnetIpStr);
        unsigned int mask = prefixToMask(prefix);
        // Keep the network section of the IP address
        unsigned int network = subnetIp & mask;
        trie *subnet = root;
        // extract the bit
        for (int j = 31; j >= 32 - prefix; j--)
        {
            bit = (network >> j) & 1;

            if (subnet->children[bit] == NULL)
            {
                subnet->children[bit] = insertBit();
            }
            subnet = subnet->children[bit];
        }
        subnet->output = output;
    }

    int bestMatch = -1;
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char ipStr[20];
        scanf("%s", ipStr);

        unsigned int ip = parseIp(ipStr);

        trie *address = root;
        // Compare the address to the entries of the routing table
        for (int j = 31; j >= 0; j--)
        {
            bit = (ip >> j) & 1;

            if (address->output != -1)
            {
                bestMatch = address->output;
            }

            if (address->children[bit] == NULL)
            {
                break;
            }

            address = address->children[bit];
        }
        printf("%d\n", bestMatch);
    }
    freeTrie(root);
    return 0;
}
