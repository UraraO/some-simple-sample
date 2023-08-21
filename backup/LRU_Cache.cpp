

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <chrono>

using namespace std;


// 使用自己设计的链表实现，普通LRU
class LRUCache {
public:
	LRUCache(int capacity) : cap(capacity), m_umap(), m_list() {}

	void m_push(int key, int val) {
		node* pnode = new node(key, val);
		m_umap[key] = pnode;
		m_list.push(pnode);
	}

	void m_delete() {
		int del = m_list.vfront.back->key;
		m_list.pop();
		m_umap.erase(del);
	}

	int get(int key) {
		if (m_umap.count(key)) {
			m_list.change(m_umap[key]);
			return m_umap[key]->val;
		}
		return -1;
	}

	void put(int key, int value) {
		if (m_umap.find(key) != m_umap.end()) {
			m_umap[key]->val = value;
			m_list.change(m_umap[key]);
			return;
		}
		m_push(key, value);
		if (m_umap.size() > cap) {
			m_delete();
		}
	}

	class node {
	public:
		node() : key(0), val(0), front(nullptr), back(nullptr) {}
		node(int k, int v) : key(k), val(v), front(nullptr), back(nullptr) {}
		int key;
		int val;
		node* front;
		node* back;
	};

	class my_list {
	public:
		my_list() : vfront(), vback() {
			vfront.back = &vback;
			vback.front = &vfront;
		}
		node vfront;
		node vback;
		void push(node* pnode) {
			node* next = vback.front;
			next->back = pnode;
			vback.front = pnode;
			pnode->front = next;
			pnode->back = &vback;
		}

		void pop() {
			node* del = vfront.back;
			if (del != &vback) {
				node* b = del->back;
				vfront.back = b;
				b->front = &vfront;
				delete del;
			}
		}

		void change(node* pnode) {
			node* f1 = pnode->front;
			node* b1 = pnode->back;
			f1->back = b1;
			b1->front = f1;
			node* vb_f = vback.front;
			pnode->front = vb_f;
			pnode->back = &vback;
			vb_f->back = pnode;
			vback.front = pnode;
		}
	};

private:
	unordered_map<int, node*> m_umap;
	my_list m_list;
	int cap;
};


class LRUCache_std {
public:
	LRUCache_std(int capacity) : cap(capacity), m_umap(), m_list() {}

	// 插入函数主要实现
	void m_push(int key, int node) {
		m_list.push_front({ key, node });
		m_umap[key] = m_list.begin();
		if (m_list.size() > cap) {
			m_delete();
		}
	}

	// 删除函数主要实现
	void m_delete() {
		m_umap.erase(m_list.back().first);
		m_list.pop_back();
	}

	// 调整缓存，将被修改的缓存项提到链表首部
	void m_change(list<pair<int, int>>::iterator iter) {
		auto node = *iter;
		m_list.erase(iter);
		m_list.push_front(node);
		m_umap[node.first] = m_list.begin();
	}

	int get(int key) {
		if (m_umap.count(key)) {
			auto result = m_umap[key]->second;
			m_change(m_umap[key]);
			return result;
		}
		return -1;
	}

	void put(int key, int node) {
		if (m_umap.find(key) != m_umap.end()) {
			m_umap[key]->second = node;
			m_change(m_umap[key]);
			return;
		}
		m_push(key, node);
	}

private:
	list<pair<int, int>> m_list;
	unordered_map<int, list<pair<int, int>>::iterator> m_umap;
	int cap;
};


// template<typename K = int, typename V = int>
class LRUCache_withTTL {
public:
	using dure_type = chrono::system_clock::duration;
	using point_type = chrono::system_clock::time_point;
	using K = int;
	using V = int;
	LRUCache_withTTL(int capacity) : cap(capacity), m_umap(), m_list() {}
	class node {
	public:
		node(K k, V v, dure_type dur = 60s) : key(k), val(v), expire_point(chrono::system_clock::now() + dur) {}
		bool is_expired() {
			return chrono::system_clock::now() > expire_point;
		}

		void flush_time(dure_type dur = 60s) {
			expire_point = chrono::system_clock::now() + dur;
		}

		K key;
		V val;
		point_type expire_point;
	};

	// 插入函数主要实现
	void m_push(int key, int val, dure_type dur = 60s) {
		m_list.push_front(node(key, val, dur));
		m_umap[key] = m_list.begin();
		if (m_list.size() > cap) {
			m_delete();
		}
	}

	// 删除函数主要实现
	void m_delete() {
		m_umap.erase(m_list.back().key);
		m_list.pop_back();
	}

	void m_delete_one(list<node>::iterator iter) {
		m_umap.erase(iter->key);
		m_list.erase(iter);
	}

	// 调整缓存，将被修改的缓存项提到链表首部
	void m_change(list<node>::iterator iter) {
		auto node = *iter;
		m_list.erase(iter);
		node.flush_time();
		m_list.push_front(node);
		m_umap[node.key] = m_list.begin();
	}

	int get(int key) {
		if (m_umap.count(key)) {
			if (m_umap[key]->is_expired()) {
				m_delete_one(m_umap[key]);
				return -1;
			}
			auto result = m_umap[key]->val;
			m_change(m_umap[key]);
			return result;
		}
		return -1;
	}

	void put(int key, int val, dure_type dur = 60s) {
		if (m_umap.find(key) != m_umap.end()) {
			m_umap[key]->val = val;
			m_change(m_umap[key]);
			return;
		}
		m_push(key, val, dur);
	}

private:
	list<node> m_list;
	unordered_map<K, list<node>::iterator> m_umap;
	int cap;
};


// #pragma clang diagnostic pop