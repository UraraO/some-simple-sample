
set(SRC_FILE_BACKUP

	algo_sort.cpp
	mutex_lock.h
	stock_factory.h
	union_find.cpp
	prim.cpp
	virtual_table_exp.cpp
	thread_safe_queue.h
	thread_safe_queue.cpp
	shared_ptr.cpp
	my_thread_test.cpp
	chrono_test.cpp
	spawn_task.cpp
	LRU_Cache.cpp


)

add_custom_target(test_target1 SOURCES ${SRC_FILE_BACKUP})

#add_executable(thread_test my_thread_test.cpp)
#add_executable(queue thread_safe_queue.cpp)
#add_executable(virtual virtual_table_exp.cpp)
#add_library(test_target1 ${SRC_FILE_BACKUP})
#add_executable(spawn_task spawn_task.cpp)