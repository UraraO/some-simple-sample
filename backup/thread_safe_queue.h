#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <stdio.h>
#include <thread>



using std::queue;
using std::mutex;
using std::condition_variable;

template <typename T>
class thread_safe_queue {
private:
	queue<T> m_queue;
	mutable mutex m_mut;
	condition_variable m_data_cond;
public:
	thread_safe_queue() = default;

	thread_safe_queue(const thread_safe_queue &other) {
		std::lock_guard guard(other.m_mut);
		m_queue = other.m_queue;
	}

	~thread_safe_queue() = default;

	void push(const T &data) {
		std::lock_guard guard(m_mut);
		m_queue.push(data);
		m_data_cond.notify_one();
	}

	void wait_and_pop(T &data) {
		std::unique_lock lock(m_mut);
		m_data_cond.wait(lock, [this]{ return !m_queue.empty(); });
		data = std::move(m_queue.front());
		m_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock lock(m_mut);
		m_data_cond.wait(lock, [this]{ return !m_queue.empty(); });
		auto sp = std::make_shared<T>(std::move(m_queue.front()));
		m_queue.pop();
		return sp;
	}

	bool try_pop(T &data) {
		std::lock_guard lock(m_mut);
		if(m_queue.empty()) return false;
		data = m_queue.front();
		m_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop() {
		std::lock_guard lock(m_mut);
		if(m_queue.empty()) return std::shared_ptr<T>();
		auto sp = std::make_shared<T>(m_queue.front());
		m_queue.pop();
		return sp;
	}

	bool empty() const {
		std::lock_guard lock(m_mut);
		return m_queue.empty();
	}

	T front() const {
		std::lock_guard lock(m_mut);
		return m_queue.front();
	}

	T back() const {
		std::lock_guard lock(m_mut);
		return m_queue.back();
	}
};

/*
template <typename T>
class thread_safe_queue {
private:
	queue<shared_ptr<T>> m_queue;
	mutable mutex m_mut;
	condition_variable m_data_cond;
public:
	thread_safe_queue() = default;

	thread_safe_queue(const thread_safe_queue &other) {
		std::lock_guard guard(other.m_mut);
		m_queue = other.m_queue;
	}

	~thread_safe_queue() = default;

	void push(const T &data) {
		shared_ptr<T> sp_data(std::make_shared<T>(std::move(data)));
		std::lock_guard guard(m_mut);
		m_queue.push(sp_data);
		m_data_cond.notify_one();
	}

	void wait_and_pop(T &data) {
		std::unique_lock lock(m_mut);
		m_data_cond.wait(lock, [this]{ return !m_queue.empty(); });
		data = std::move(*m_queue.front());
		m_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock lock(m_mut);
		m_data_cond.wait(lock, [this]{ return !m_queue.empty(); });
		auto sp = m_queue.front();
		m_queue.pop();
		return sp;
	}

	bool try_pop(T &data) {
		std::lock_guard lock(m_mut);
		if(m_queue.empty()) return false;
		data = std::move(*m_queue.front());
		m_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop() {
		std::lock_guard lock(m_mut);
		if(m_queue.empty()) return std::shared_ptr<T>();
		auto sp = m_queue.front();
		m_queue.pop();
		return sp;
	}

	bool empty() const {
		std::lock_guard lock(m_mut);
		return m_queue.empty();
	}

	T front() const {
		std::lock_guard lock(m_mut);
		return m_queue.front();
	}

	T back() const {
		std::lock_guard lock(m_mut);
		return m_queue.back();
	}
};
*/