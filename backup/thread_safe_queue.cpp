

#include "thread_safe_queue.h"

using std::shared_ptr;
using std::thread;

void generate(const shared_ptr<thread_safe_queue<int>> que) {
	int i = 0;
	while(i < 1000) {
		que->push(i);
		printf("Generator: push %d\n", i);
		++i;
	}
}

void consume(const shared_ptr<thread_safe_queue<int>> que) {
	while(true) {
		auto sp = que->wait_and_pop();
		printf("Consumer: pop %d\n", *sp);
		if(*sp == 999) break;
	}
}



int main(int argc, char **argv) {


	shared_ptr<thread_safe_queue<int>> sp(std::make_shared<thread_safe_queue<int>>());

	thread consumer(consume, sp);
	thread generator(generate, sp);

	generator.join();
	consumer.join();

	return 0;
}
