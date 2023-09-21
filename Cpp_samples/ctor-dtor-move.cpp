

#include <iostream>
#include <string>
#include <utility>


using namespace std;

class A {
public:
	A() { cout << "ctor" << endl; }
	explicit A(string n) : name(std::move(n)) { cout << name << " ctor" << endl; }
	~A() { cout << "dtor" << endl; }
	A(const A &other) { cout << "copy" << endl; }
	A& operator = (const A &other) {
		cout << "A::=" << endl;
		this->name = other.name;
		return *this;
	}

	A(A &&other) noexcept : name(std::move(other.name)) {
		//other.name.clear();
		cout << "move copy" << endl;
	}
	A& operator = (A &&other) noexcept {
		if(this == &other) return *this;
		this->name = other.name;
		cout << "A::= move" << endl;
		return *this;
	}

	string get_name() { return name; }
private:
	string name;
};

A get_A_1() {
	A temp("A1");
	return temp;
}

int main(int argc, char **argv) {

	// 1
//	A a = get_A_1();
	// 编译器自动优化，去除拷贝部分，仅执行一次ctor和dtor，在A a上原位构造
	// get_A_1相当于包装一个构造函数的实例，可以内含特定参数

	// 2
//	A b;
//	b = get_A_1();

	// 3
//	A c(get_A_1());

	// 4
//	A a("before move");
//	A d(std::move(a));
//	A e;
//	e = std::move(d);

	return 0;
}


// #pragma clang diagnostic pop