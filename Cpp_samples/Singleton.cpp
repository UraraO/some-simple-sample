

#include <iostream>


using namespace std;

class Singleton {
public:
	Singleton(const Singleton &other) = delete;
	Singleton& operator = (const Singleton &other) = delete;

	static Singleton* get_instance() {
		static Singleton single;
		return &single;
	}

	static int somefunc(int i) {
		return i;
	}

private:
	Singleton() { cout << "constructor" << endl; }
	~Singleton() { cout << "destructor" << endl; }
};



int main(int argc, char **argv) {
	auto s = Singleton::get_instance();
	cout << s->somefunc(42) << endl;

	return 0;
}


// #pragma clang diagnostic pop