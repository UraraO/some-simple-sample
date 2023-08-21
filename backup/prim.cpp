/*
 * Prim最小生成树算法
 * */

#pragma once

#include <vector>
#include <queue>
#include <functional>

using std::vector;
using std::priority_queue;
using std::greater;

class Prim {
private:
	// 核心数据结构，存储「横切边」的优先级队列
	// 三元组 {from, to, weight} 表示一条边
	priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > pq;
	// 类似 visited 数组的作用，记录哪些节点已经成为最小生成树的一部分
	vector<bool> inMST;
	// 记录最小生成树的权重和
	int weightSum = 0;
	// graph 是用邻接表表示的一幅图，
	// graph[s] 记录节点 s 所有相邻的边
	vector<vector<int> > m_graph;

public:
	Prim(vector<vector<int> > graph) {
		m_graph = std::move(graph);
		// 图中有 n 个节点
		auto n = m_graph.size();
		this->inMST.resize(n);

		// 随便从一个点开始切分都可以，我们不妨从节点 0 开始
		inMST[0] = true;
		cut(0);
		// 不断进行切分，向最小生成树中添加边
		while(!pq.empty()) {
			vector<int> edge = pq.top();
			pq.pop();
			int to = edge[1];
			int weight = edge[2];
			if (inMST[to]) {
				// 节点 to 已经在最小生成树中，跳过
				// 否则这条边会产生环
				continue;
			}
			// 将边 edge 加入最小生成树
			weightSum += weight;
			inMST[to] = true;
			// 节点 to 加入后，进行新一轮切分，会产生更多横切边
			cut(to);
		}
	}

	// 将 s 的横切边加入优先队列
	void cut(int s) {
		// 遍历 s 的邻边
		for (auto edge : m_graph) {
			int to = edge[1];
			if (inMST[to]) {
				// 相邻接点 to 已经在最小生成树中，跳过
				// 否则这条边会产生环
				continue;
			}
			// 加入横切边队列
			pq.push(edge);
		}
	}

	// 最小生成树的权重和
	int weight_sum() {
		return weightSum;
	}

	// 判断最小生成树是否包含图中的所有节点
	bool allConnected() {
		for (bool connected : inMST) {
			if (!connected) {
				return false;
			}
		}
		return true;
	}
};