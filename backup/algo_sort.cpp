#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::swap;

void select_sort(vector<int> &vec);

void insert_sort(vector<int> &vec);

void shell_sort(vector<int> &vec);

void print_vec(const vector<int> &vec);


class quick_sort {
public:
	void operator()(vector<int> &vec);

private:
	void _quick_sort(vector<int> &vec, int low, int high);

	void _insert_sort(vector<int> &vec, int low, int high);

	int getSecond(int a,int b,int c) {
		return a > b ? (b > c ? b : ( a > c ? c : a)) : ( a > c ? a: (b > c ? c : a));
	}
};

void quick_sort::operator()(vector<int> &vec) {
	std::mt19937 g(std::random_device{}());
	std::shuffle(vec.begin(), vec.end(), g);
	_quick_sort(vec, 0, vec.size() - 1);
}

// between less and equal :         less_i
// between equal and unsorted :     i
// between unsorted and greater:    greater_i
// ( <V ) less_i ( ==V ) i ( unsorted ) greater_i ( >V )
// V = part_point

void quick_sort::_quick_sort(vector<int> &vec, int low, int high) {
	if(high - low <= 8) {   // turn to insert
		_insert_sort(vec, low, high);
		return;
	}
	// get the partition_point : median
	int less_i = low, i = low, greater_i = high;
	int mid = low + (high - low) / 2;
	int part_point = getSecond(vec[low], vec[high], vec[mid]);
	// partition
	while(i <= greater_i) { // i > greater_i means no unsorted
		if(vec[i] < part_point) {
			std::swap(vec[less_i++], vec[i++]);
		} else if(vec[i] > part_point) {
			std::swap(vec[greater_i--], vec[i]);
		} else {
			++i;
		}
	}
	_quick_sort(vec, low, less_i - 1);
	_quick_sort(vec, greater_i + 1, high);
}

void quick_sort::_insert_sort(vector<int> &vec, int low, int high) {
	int size = high - low + 1;
	if(size == 0) {
		return;
	}

	for(int i = low + 1; i < size + low; ++i) {
		int inserted_elem = vec[i];
		int j = i;

		for(; j > low && vec[j - 1] > inserted_elem; --j) {
			vec[j] = vec[j - 1];
		}
		vec[j] = inserted_elem;
	}
}


void select_sort(vector<int> &vec) {
	int size = vec.size();
	if(size == 0) {
		return;
	}
	int index_min = size - 1;
	for(int i = 0; i < size; ++i) {
		index_min = i;
		for(int j = i + 1; j < size; ++j) {
			if(vec[j] < vec[index_min]) {
				index_min = j;
			}
		}
		swap(vec[i], vec[index_min]);
	}
}

void insert_sort(vector<int> &vec) {
	int size = vec.size();
	if(size == 0) {
		return;
	}

	for(int i = 1; i < size; ++i) {
		int inserted_elem = vec[i];
		int j = i;
		for(; j > 0 && vec[j - 1] > inserted_elem; --j) {
			vec[j] = vec[j - 1];
		}
		vec[j] = inserted_elem;
	}
}

void shell_sort(vector<int> &vec) {
	int size = vec.size();
	if(size == 0) {
		return;
	}
	int h = 1;
	while(h < size / 3) {
		h = h * 3 + 1;  // 1, 4, 13, 40, 121, 364......
	}
	while(h >= 1) {
		for(int i = h; i < size; ++i) {
			int inserted_elem = vec[i];
			int j = i;
			for(; j >= h && vec[j - h] > inserted_elem; j -= h) {
				vec[j] = vec[j - h];
			}
			vec[j] = inserted_elem;
		}
		h /= 3; // ..., 40, 13, 4, 1
	}
}

void print_vec(const vector<int> &vec) {
	cout << "print_vec : " << endl;
	for(int i: vec) {
		cout << i << " ";
	}
	cout << endl;
}





int main() {
	vector<int> vec{6,5,5,5,5,5,3,2,1};
	quick_sort()(vec);
	print_vec(vec);
	return 0;
}










