
set(SRC_FILE_CPP

	chrono_test.cpp
	Singleton.cpp
	ctor-dtor-move.cpp

	)

add_custom_target(CPP_Sample_target SOURCES ${SRC_FILE_CPP})

#add_executable(thread_test my_thread_test.cpp)
#add_executable(queue thread_safe_queue.cpp)
#add_executable(virtual virtual_table_exp.cpp)
#add_library(test_target1 ${SRC_FILE_BACKUP})
#add_executable(spawn_task spawn_task.cpp)
#add_executable(spawn_task spawn_task.cpp)



