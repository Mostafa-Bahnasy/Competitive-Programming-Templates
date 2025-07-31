#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
void erase_one(ordered_multiset<T>& ms, const T& val) {
    auto it = ms.lower_bound(val);
    if (it != ms.end() && *it == val) {
        ms.erase(it);
    }
}
