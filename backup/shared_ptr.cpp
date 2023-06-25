
#include <iostream>

template <typename T>
class my_shared_ptr {
public:
	explicit my_shared_ptr(T *pt = nullptr) : _pt(pt), _count(new size_t(1)) {}

	~my_shared_ptr() {
		--(*_count);
		if(*_count == 0) {
			delete _pt;
			delete _count;
		}
	}

	my_shared_ptr(const my_shared_ptr<T> &other)
		: _pt(other._pt), _count(other._count) {
		if(_count) ++(*_count);
	}

	my_shared_ptr<T>& operator=(const my_shared_ptr<T> &other) {
		if(&other == this) return *this;
		{   // destructor
			--(*(this->_count));
			if(*(this->_count) == 0) {
				delete this->_pt;
				delete this->_count;
			}
		}
		this->_pt = other._pt;
		this->_count = other._count;
		++(*this->_count);
	}

	T& operator*() { return *_pt; }
	T* operator->() { return _pt; }
	T* get() { return _pt; }
	size_t use_count() { return _count ? *_count : 0; }
private:
	T *_pt;
	size_t *_count;
};