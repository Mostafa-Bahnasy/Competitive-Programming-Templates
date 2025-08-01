using row = vector<long long>;
using mat = vector<row>;
const int MOD = 1e9 + 7;
mat operator*(mat a, mat b)
{
    mat ret = mat(a.size(), row(b[0].size()));
    for (int i = 0; i < ret.size(); i++)
        for (int j = 0; j < ret[i].size(); j++)
            for (int k = 0; k < ret[i].size(); k++)
                ret[i][j] = (ret[i][j] + a[i][k] * b[k][j]) % MOD;
    return ret;
}
mat operator^(mat b, int p)
{
    if (p == 1)
        return b;
    if (p & 1)
        return b * (b ^ (p - 1));
    return (b * b) ^ (p / 2);
}