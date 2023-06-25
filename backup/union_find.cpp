#include <iostream>
#include <vector>


using std::cin;
using std::cout;
using std::endl;
using std::vector;


class union_find {
public:
	// 连通分量个数
	int m_count;
	// 存储每个节点的父节点
	vector<int> parent;

public:
	// n 为图中节点的个数
	union_find(int n) : m_count(n), parent(n) {
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}

	// 将节点 p 和节点 q 连通
	void connect(int p, int q) {
		int rootP = find(p);
		int rootQ = find(q);

		if (rootP == rootQ)
			return;

		parent[rootQ] = rootP;
		// 两个连通分量合并成一个连通分量
		--m_count;
	}

	// 判断节点 p 和节点 q 是否连通
	bool connected(int p, int q) {
		int rootP = find(p);
		int rootQ = find(q);
		return rootP == rootQ;
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	// 返回图中的连通分量个数
	inline int count() const {
		return m_count;
	}
};