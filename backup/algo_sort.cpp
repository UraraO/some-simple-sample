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

// 三切分快速排序
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
	std::mt19937 eng(std::random_device{}());
	std::shuffle(vec.begin(), vec.end(), eng);
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

	for(int i = low + 1; i < size + low; ++i) { // 从第2个元素到最后一个
		int inserted_elem = vec[i];
		int j = i;
		for(; j > low && vec[j - 1] > inserted_elem; --j) {
			vec[j] = vec[j - 1];    // 将前面大于要插入的元素都后移1位
		}
		vec[j] = inserted_elem;     // 插入
	}
}

// 获取中位数
int getSecond(int a,int b,int c) {
	return a > b ? (b > c ? b : ( a > c ? c : a)) : ( a > c ? a: (b > c ? c : a));
}

// 快速选择算法实现
template <typename T = int>
T quick_select_(vector<T> &vec, int k, int low, int high) {
	if(low == high) return vec[low];
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
	if(k <= greater_i && k >= less_i) return vec[k];
	else if(k < less_i) return quick_select_(vec, k, low, less_i-1);
	else return quick_select_(vec, k, greater_i+1, high);
}

template <typename T>
T quick_select(vector<T> vec, int k) {
	return quick_select_(vec, vec.size() - k, 0, vec.size()-1);
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

void merge_sort_recursive_(vector<int> &vec, vector<int> &reg, unsigned long long l, unsigned long long r) {
	if(l >= r) return;
	auto mid = (r-l)/2 + l;
	merge_sort_recursive_(vec, reg, l, mid);
	merge_sort_recursive_(vec, reg, mid+1, r);
	auto liter = l, riter = mid+1;
	auto iter = l;
	while(liter <= mid && riter <= r) {
		reg[iter++] = (vec[liter] < vec[riter]) ? vec[liter++] : vec[riter++];
	}
	while(liter <= mid) {
		reg[iter++] = vec[liter++];
	}
	while(riter <= r) {
		reg[iter++] = vec[riter++];
	}
	for(iter = l; iter <= r; ++iter) vec[iter] = reg[iter];
}

void merge_sort_recursive(vector<int> &vec) {
	vector<int> reg(vec);
	merge_sort_recursive_(vec, reg, 0, vec.size()-1);
}

size_t min(const size_t &lhs, const size_t &rhs) {
	return lhs < rhs ? lhs : rhs;
}

void merge_sort_unrecursive(vector<int> &vec) {
	vector<int> reg(vec);
	auto size = vec.size();
	for(size_t seg = 1; seg < size; seg += seg) {
		for(size_t l = 0; l < size; l += (seg + seg)) {
			auto r = min(size, l + seg + seg), mid = min(l + seg, size);
			auto iter = l, beg1 = l, end1 = mid, beg2 = mid, end2 = r;
			while(beg1 < end1 && beg2 < end2) {
				reg[iter++] = vec[beg1] < vec[beg2] ? vec[beg1++] : vec[beg2++];
			}
			while(beg1 < end1) {
				reg[iter++] = vec[beg1++];
			}
			while(beg2 < end2) {
				reg[iter++] = vec[beg2++];
			}
			//for(iter = l; iter < r; ++iter) vec[iter] = reg[iter];
			copy(reg.begin()+l, reg.begin()+r, vec.begin()+l);
		}
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
	vector<int> vec{9,8,8,7,6,5,4,3,2,1};

	//quick_sort()(vec);
	//merge_sort_recursive(vec);
	merge_sort_unrecursive(vec);
	//cout << quick_select(vec, 9) << endl;

	print_vec(vec);
	return 0;
}
