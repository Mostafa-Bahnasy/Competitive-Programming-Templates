#include <chrono>
#include <random>

#include <bits/stdc++.h>
using namespace std;

/*
    XOR Hash - randomized hashing using XOR and a random base
    Use case: fast and collision-resistant hash for strings or containers
    rng(): returns a random 64-bit integer for use as a base or hash seed
    Commonly used in: unordered_map custom hash, randomized hash functions for strings
*/

long long rng() {
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<long long>(0, LLONG_MAX)(gen);
}
