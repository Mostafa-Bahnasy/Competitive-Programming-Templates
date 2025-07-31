// ask plus for template

//The sparse table is optimized for idempotent operations like GCD, min, max (not sum)

struct Sparse 
{
    vector<int> lg;                    // Stores precomputed floor(log2(i)) values
    vector<vector<int>> table;        // Sparse table for range GCD queries

    // Constructor to initialize the sparse table for array 'a' of size 'n'
    Sparse(int n, vector<int>& a) 
    {
        lg.resize(n + 5);
        lg[1] = 0;

        // Precompute floor(log2(i)) for i in [2, n]
        for (int i = 2; i <= n; i++) 
            lg[i] = lg[i / 2] + 1;
        

        // Initialize the sparse table with dimensions [n][log2(n)]
        table = vector<vector<int>>(n + 5, vector<int>(lg[n] + 5, 0));

        // Base case: the 0-th level stores the original array values
        for (int i = 0; i < n; i++) 
            table[i][0] = a[i];
        

        // Build the sparse table using dynamic programming
        // table[i][j] holds GCD of the subarray starting at i with length 2^j
        for (int j = 1; j <= lg[n]; j++) 
        {
            for (int k = 0; k + (1 << j) - 1 < n; k++) 
            {
                table[k][j] = __gcd(
                    table[k][j - 1],                       // First half
                    table[k + (1 << (j - 1))][j - 1]       // Second half
                );
            }
        }
    }

    // Query the GCD of the subarray [l, r] (0-based indexing)
    int query(int l, int r) 
    {
        int len = r - l + 1;
        int x = lg[len];  // log2 of the segment length
        return __gcd(
            table[l][x],                                // GCD of first segment
            table[r - (1 << x) + 1][x]                  // GCD of second segment
        );
    }
};
