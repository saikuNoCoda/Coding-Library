# Coding Library

## By failed_coder

## https://codeforces.com/profile/failed_coder

## https://www.codechef.com/users/failed_coder

## https://atcoder.jp/users/failed__coder

## https://www.topcoder.com/members/failed_coder


https://math.stackexchange.com/questions/2956889/how-many-number-of-integer-coordinates-exists-between-a-line-segment-including

no of trees with n labeled vertices is n^(n-2) https://en.wikipedia.org/wiki/Cayley%27s_formula


https://proofwiki.org/wiki/Sum_of_r%2Bk_Choose_k_up_to_n

Smallest Enclosing Circle https://codeforces.com/blog/entry/23554

a+b=a⊕b+2×(a and b)=(a or b)+(a and b)

Dilworth's theorem states that, in any finite partially ordered set, the largest antichain has the same size as the smallest chain decomposition

Set bits xor pairsum https://atcoder.jp/contests/abc091/submissions/11263481


Policy Based data structure
OrderedSet

(Use as multiset)
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_updat
using namespace __gnu_pbds;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

order_of_key -> find element less than x
find_order_by -> returns iterator to kth largest element counting from 0.
lower bound works as upper bound

Normal set
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
  
Fast Hash in cpp

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { int operator()(int x) const { return x ^ RANDOM; }};
cc_hash_table<int, int, hash<int>> cnt;

