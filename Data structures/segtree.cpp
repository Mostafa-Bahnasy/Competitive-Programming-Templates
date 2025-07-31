
struct Node
{
  
}NEUTRAL;

struct SegTree 
{
    int size;
    vector<Node> tree;
    vector<int> lazy;

    SegTree(int n) 
    {
      size = 1;
      while (size < n) size *= 2;
      tree.resize(2*size);
      lazy.assign(2*size, 0);
    }

    Node merage(Node a , Node b)
    {
        Node res; 

        return res;
    }
    void build(vector<int>& a, int x, int lx, int rx) 
    {
      if (rx - lx == 1) 
      {
            if (lx < a.size())
            {
              
            };
            return;
      }
      int m = (lx + rx)/2;
      build(a, 2*x+1, lx, m);
      build(a, 2*x+2, m, rx);
      tree[x] = merage(tree[2*x+1], tree[2*x+2]);
    }

    void push(int x, int lx, int rx) 
    {
      if (lazy[x]) 
      {
        lazy[x] = 0;
      }
    }

    void update(int l, int r, int x, int lx, int rx) 
    {
      push(x, lx, rx);
      if (lx >= r || rx <= l) return;
      if (lx >= l && rx <= r) 
      {
            lazy[x] = 1;
            push(x, lx, rx);
            return;
      }
      int m = (lx + rx)/2;
      update(l, r, 2*x+1, lx, m);
      update(l, r, 2*x+2, m, rx);
      tree[x] = merage(tree[2*x+1], tree[2*x+2]);
    }

    Node query(int l, int r, int x, int lx, int rx) 
    {
        push(x, lx, rx);
        if (lx >= r || rx <= l) return NEUTRAL;
        if (lx >= l && rx <= r) return tree[x];
        int m = (lx + rx)/2;
        return merage(query(l, r, 2*x+1, lx, m),query(l, r, 2*x+2, m, rx));
    }

    void build(vector<int>& a) { build(a, 0, 0, size); }
    void update(int l, int r) { update(l, r, 0, 0, size);}
    Node query(int l, int r) { return query(l, r, 0, 0, size); }
};