
/*
 * 对std::thread的封装测试，保存一个thread_func，并通过my_thread.start()
 * 和my_thread.stop()反复使用线程thread_func
 *
 * */

#include <iostream>
#include <utility>
#include <vector>

#include <thread>
#include <functional>
#include <unistd.h>



using std::cin;
using std::cout;
using std::endl;
using std::vector;

class my_thread {
public:
	using thread_func = std::function<void()>;

	explicit my_thread(thread_func func) : m_func(std::move(func)) {
		cout << "my_thread() constructor" << endl;
	}

	~my_thread() {
		cout << "~my_thread() destructor" << endl;
	}

	void start() {
		cout << "my_thread start" << endl;
		std::thread t(m_func);
		t.swap(m_thread);
		cout << "start: thread swap" << endl;
		if(t.joinable()) {
			t.detach();
		}
	}

	void stop() {
		cout << "my_thread stop" << endl;
		std::thread t;
		m_thread.swap(t);
		if(t.joinable()) {
			cout << "my_thread join" << endl;
			t.detach();
		}
	}

private:
	std::thread m_thread;
	thread_func m_func;
};


int main(int argc, char **argv) {
	auto func = []{
		int i = 0;
		while(i++ < 20) {
			cout << "func" << i << endl;
			sleep(1);
		}
	};
	my_thread mt(func);
	cout << "mt initialized" << endl;
	mt.start();
	sleep(5);
	mt.stop();
	sleep(5);
	mt.start();
	sleep(5);
	mt.stop();
}