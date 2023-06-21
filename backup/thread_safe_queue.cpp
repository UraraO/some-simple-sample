

#include "thread_safe_queue.h"



void generate(std::shared_ptr<thread_safe_queue<int>> que) {
	int i = 0;
	while(i < 1000) {
		que->push(i);
		printf("Generator: push %d\n", i);
		++i;
	}
}

void consume(std::shared_ptr<thread_safe_queue<int>> que) {
	while(1) {
		auto sp = que->wait_and_pop();
		printf("Consumer: pop %d\n", *sp);
		if(*sp == 999) break;
	}
}



int main(int argc, char **argv) {


	std::shared_ptr<thread_safe_queue<int>> sp(std::make_shared<thread_safe_queue<int>>());

	std::thread consumer(consume, sp);
	std::thread generator(generate, sp);

	generator.join();
	consumer.join();

	return 0;
}








