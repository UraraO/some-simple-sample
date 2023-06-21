#pragma once

#include <pthread.h>
#include <sys/types.h>
#include <cassert>
#include <memory>
#include <string>
#include <map>
#include <utility>
#include <functional>

#include "mutex_lock.h"

using std::shared_ptr;
using std::weak_ptr;
using std::string;
using std::map;

class stock {
public:
	explicit stock(string key) : stock_name(std::move(key)), price(0) {}

	string stock_name;
	double price;
};

class stock_factory : public noncopyable,
						std::enable_shared_from_this<stock_factory> {
public:
	shared_ptr<stock> get(const string &key) {
		shared_ptr<stock> pstock;
		mutex_lock_guard lock(m_mutex);
		weak_ptr<stock> &wk_stock = m_stocks[key];
		pstock = wk_stock.lock();
		if(!pstock) {
			pstock.reset(new stock(key),
			             std::bind(stock_factory::weak_delete_callback, weak_ptr<stock_factory> (shared_from_this()), std::placeholders::_1));
			wk_stock = pstock;
		}
		return pstock;
	}
private:
	static void weak_delete_callback(const weak_ptr<stock_factory> & wk_factory, stock *p_stock) {
		shared_ptr<stock_factory> s_factory(wk_factory.lock());
		if(s_factory) {
			s_factory->remove_stock(p_stock);
		}
		delete p_stock;
	}

	void remove_stock(stock * pstock) {
		if(pstock) {
			mutex_lock_guard lock(m_mutex);
			m_stocks.erase(pstock->stock_name);
		}
	}

private:
	mutable mutex_lock m_mutex;
	map<string, weak_ptr<stock>> m_stocks;
};















