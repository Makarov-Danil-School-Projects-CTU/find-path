#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>

using Place = size_t;

struct Map {
    size_t places;
    Place start, end;
    std::vector<std::pair<Place, Place>> connections;
    std::vector<std::vector<Place>> items;
};

template < typename F, typename S >
struct std::hash<std::pair<F, S>> {
    std::size_t operator () (const std::pair<F, S> &p) const noexcept {
        // something like boost::combine would be much better
        return std::hash<F>()(p.first) ^ (std::hash<S>()(p.second) << 1);
    }
};

#endif

using namespace std;

std::list<Place> find_path(const Map &map) {
    unordered_map<int, vector<int>> vertex;
    unordered_map<int, vector<int>> items;

    // node parsing
    for (auto item: map.connections) {
        vertex[item.first].push_back(item.second);
        vertex[item.second].push_back(item.first);
    }

    // items parsing
    set<int> allItems;
    bitset<16> correctCombination;
    for (int item = 0; item < (int) map.items.size(); ++item) {
        for (int node: map.items[item]) {
            items[node].push_back(item);
        }
        allItems.insert(item);
    }
    for (auto x: allItems)
        correctCombination.set(x, true);

    unordered_map<pair<int, unsigned long>, pair<int, unsigned long>> parents(vertex.size());

    // initialize queue
    queue<pair<int, bitset<16>>> q;

    // starting node
    bitset<16> st;
    for (int x: items[map.start])
        st.set(x, true);

    parents[{map.start, st.to_ulong()}] = make_pair(-1, st.to_ulong());
    q.push(make_pair(map.start, st));
    while (!q.empty()) {
        int v = q.front().first;
        auto mask = q.front().second;
        q.pop();

        for (int t: vertex[v]) {
            bitset<16> newMask;
            for (auto x: items[t])
                newMask.set(x, true);

            newMask |= mask;
            if (!parents.count({t, newMask.to_ulong()})) {
                parents[{t, newMask.to_ulong()}] = make_pair(v, mask.to_ulong());
                if (parents.count({map.end, correctCombination.to_ulong()}))
                    break;
                else
                    q.push(make_pair(t, newMask));
            }
        }
    }

    if (!parents.count({map.end, correctCombination.to_ulong()}))
        return list<Place>{};
    else {
        list<Place> path;
        int v = map.end;
        auto mask = correctCombination.to_ulong();
        while (v != -1) {
            path.push_back(v);
            int V = v;
            auto Mask = mask;
            v = parents[{V, Mask}].first;
            mask = parents[{V, Mask}].second;
        }
        reverse(path.begin(), path.end());
        return path;
    }
}

#ifndef __PROGTEST__

using TestCase = std::pair<size_t, Map>;

// Class template argument deduction exists since C++17 :-)
const std::array examples = {
        TestCase{ 1, Map{ 2, 0, 0,
                          { { 0, 1 } },
                          { { 0 } }
        }},
        TestCase{ 3, Map{ 2, 0, 0,
                          { { 0, 1 } },
                          { { 1 } }
        }},
        TestCase{ 3, Map{ 4, 0, 1,
                          { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
                          {}
        }},
        TestCase{ 4, Map{ 4, 0, 1,
                          { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
                          { { 2 } }
        }},
        TestCase{ 0, Map{ 4, 0, 1,
                          { { 0, 2 }, { 2, 3 }, { 0, 3 }, { 3, 1 } },
                          { { 2 }, {} }
        }},
};

int main() {
    int fail = 0;
    for (size_t i = 0; i < examples.size(); i++) {
        auto sol = find_path(examples[i].second);
        if (sol.size() != examples[i].first) {
            std::cout << "Wrong anwer for map " << i << std::endl;
            fail++;
        }
    }

    if (fail) std::cout << "Failed " << fail << " tests" << std::endl;
    else std::cout << "All tests completed" << std::endl;

    return 0;
}

#endif