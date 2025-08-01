int dist[N][N];
int next[N][N];
void path(int fr, int to)
{
    if (next[fr][to] == -1)
    {
        cout << fr << " "; // beytalla3 kolo ma 3ada a5er node
        return;
    }
    path(fr, next[fr][to]);
    path(next[fr][to], to);
}
void floyd()
{
    // dist[i][j] contains the weight of edge (i, j)
    // or INF (1B) if there is no such edge
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = k;
                }
            }
        }
    }
}