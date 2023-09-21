

#include <iostream>
#include <vector>

using namespace std;

class min_heap {
public:
	min_heap() : heap(), size_(0) {}
	~min_heap() = default;

	void push(int node);
	void pop();
	int& top();
	size_t size() const { return size_; }

private:
	vector<int> heap;
	size_t size_;

	void show_vec();

};

void min_heap::push(int node) {
	++size_;
	heap.push_back(node);
	auto son_index = size_;
	auto father_index = son_index / 2;
	while(son_index > 1) {
		if(heap[son_index-1] < heap[father_index-1]) {
			swap(heap[son_index-1], heap[father_index-1]);
			son_index = father_index;
			father_index = son_index / 2;
		}
		else break;
	}
	show_vec();
}

void min_heap::pop() {
	if(size_ <= 0) return;
	--size_;
	swap(heap[0], heap[size_]);
	heap.pop_back();
	size_t father_index = 1;
	auto left_index = father_index*2, right_index = left_index+1;
	while(left_index <= size_) {
		auto min_index = father_index;
		if(right_index <= size_) {
			min_index = heap[left_index-1] < heap[right_index-1] ? left_index : right_index;
		}
		else min_index = left_index;
		if(heap[father_index-1] > heap[min_index-1]) {
			swap(heap[father_index-1], heap[min_index-1]);
		}
		else break;

		father_index = min_index;
		left_index = father_index*2;
		right_index = left_index+1;
	}
	show_vec();
}

int &min_heap::top() {
	try {
		if(size_ <= 0) throw "heap is empty!";
	}
	catch(const char * str) {
		cout << "heap is empty!" << endl;
	}
	return heap[0];
}

void min_heap::show_vec() {
	for(auto const &i : heap) {
		cout << i << " ";
	}
	cout << endl;
}


int main(int argc, char **argv) {
	min_heap heap;
	for(int i = 10; i > 0; --i) heap.push(i);
	int sz = heap.size();
	for(int i = 0; i < sz; ++i) heap.pop();
	heap.top();
	
	return 0;
}


// #pragma clang diagnostic pop