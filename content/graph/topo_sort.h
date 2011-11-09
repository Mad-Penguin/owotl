/**
 * Author:
 * Date: 2010-11-18
 * Source: tinyKACTL
 * Description:
 */
#pragma once

#include <vector>
#include <queue>
using namespace std;

template <class E, class I>
bool topo_sort(const E *edges, I &idx, int n) {
	vector<int> indeg(n);
	rep(i,0,n)
		trav(e, edges[i])
		indeg[*e]++;
	queue<int> q; // use priority queue for lexic. smal lest ans.
	rep(i,0,n) if (indeg[i] == 0) q.push(-i);
	int nr = 0;
	while (q.size() > 0) {
		int i = -q.front(); // top() for priority queue
		idx[i] = ++nr;
		q.pop();
		trav(e, edges[i])
			if (--indeg[*e] == 0) q.push(-*e);
	}
	return nr == n;
}