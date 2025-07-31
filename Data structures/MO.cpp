// =========================== Mo's Algorithm ===========================
// ➤ Purpose: Efficiently answer multiple offline range queries on a static array.
// ➤ Time Complexity: O((N + Q) * sqrt(N)) ≈ O(N * sqrt(N))
// ➤ Best for: Sum/frequency problems on subarrays (e.g., distinct count, frequency, XOR).
// ➤ Restrictions: 
//     - No updates allowed (only queries).
//     - Queries must be known in advance (offline).
// =====================================================================

const int BLOCK_SIZE = 316; // ≈ sqrt(N), can be tuned

// Comparator for optimal query ordering (Hilbert Curve / Mo Order)
// Z-ordering: minimize pointer movement by adjusting r direction per block
bool cmp(pair<int, int> p, pair<int, int> q) {
    if (p.first / BLOCK_SIZE != q.first / BLOCK_SIZE)
        return p < q;
    return ((p.first / BLOCK_SIZE) & 1) ? (p.second < q.second) : (p.second > q.second);
}

// Structure for queries
struct Query {
    int l, r, idx;
};

// You must define this according to your problem
void add(int idx);            // Add element at idx to your data structure
void remove(int idx);         // Remove element at idx
int get_answer();             // Return current answer from your structure

vector<int> mos_algorithm(vector<Query>& queries) {
    vector<int> answers(queries.size());

    // Sort queries using improved Mo's comparator
    sort(queries.begin(), queries.end(), [&](const Query& a, const Query& b) {
        return cmp({a.l, a.r}, {b.l, b.r});
    });

    int cur_l = 0, cur_r = -1;
    // Maintain [cur_l, cur_r] as the current active segment
    for (auto q : queries) {
        while (cur_l > q.l) add(--cur_l);
        while (cur_r < q.r) add(++cur_r);
        while (cur_l < q.l) remove(cur_l++);
        while (cur_r > q.r) remove(cur_r--);
        answers[q.idx] = get_answer(); // Answer for current query
    }

    return answers;
}
