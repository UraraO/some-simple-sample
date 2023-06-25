#include <iostream>
#include <vector>
#include <type_traits>


#include <thread>
#include <future>


using std::cin;
using std::cout;
using std::endl;
using std::vector;

using std::future;
using std::thread;
using std::packaged_task;
using std::move;

/*
 * spawn_task是一个对future的包装
 * 其将future的任务类型和任务接受的参数类型作为模板参数
 * 可以代替async，packaged_task等异步调用创建器
 * 其内部使用packaged_task实现
 * */
// F is thread_func_type, A is thread_func_arguments_type
//future<typename std::result_of<F(A&&)>::type>
template<typename A = void, typename F>
future<typename std::invoke_result_t<F, A&&>>
spawn_task(F &&f, A &&a) {
	using result_type = std::invoke_result_t<F, A&&>;
	packaged_task<result_type(A&&)> task(std::forward<F>(f));
	future<result_type> result(task.get_future());
	thread t(std::move(task), std::forward<A>(a));
	t.detach();
	return result;
};

int func(int useless) {
	return 1;
}

int func_noarg() {
	return 2;
}


int main(int argc, char **argv) {

	auto res = spawn_task(func, 0);
	cout << res.get() << endl;

	auto res2 = std::async(func_noarg);
	cout << res2.get() << endl;

	return 0;
}