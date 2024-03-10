/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Usage: 
 * Same functions as set +
 * find_by_order(k): Returns an iterator to the k-th element (0 indexed)
 * order_of_key(x): Returns how many elements go strictly before x
 * t.join(t1): Assuming T < T2 or T > T2, merge t2 into t
 * Declare as Tree<int>, Tree<pii>, ...
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

