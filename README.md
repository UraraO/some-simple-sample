# some-simple-sample
some simple code sample, only for reference
this repo will cotinuously update, if there's any sample of interest to you, just copy it and read~

学习编程过程中写的一些值得记录的代码片段，会保持更新，只要有任何新的代码示例，都会添加到这个仓库
main.cpp中不保存任何代码，已有的代码片段保存在backup文件夹中
可以拷贝仓库之后参考backup/CMakeLists.txt中的示例，添加add_executable，即可运行单个cpp文件
其中部分文件使用到linux的库文件，推荐使用gcc编译，windows下使用MinGW  

具体内容如下:
- algo_sort   多种排序算法源码示例
- chrono_test   C++11新的时间库chrono的常用用法示例
- mutex_lock   使用RAII手法简单包装pthread库的mutex  
    C++标准并发支持库已有良好实现，仅供参考，实际编写代码过程中应使用lock_guard和unique_lock模板配合std::mutex使用
- my_thread_test    一个简单的可手动启停线程的实现
- prim    prim最小生成树的实现，图算法
- shared_ptr    shared_ptr的简单实现
- spawn_task    对异步任务类型的简单封装，内部使用packaged_task实现，可以用作带参数的异步任务，代替std::async和packaged_task
- stock_factory   源于陈硕先生的《linux多线程服务端编程》，一个简单的线程安全的股票仓库，可以线程安全的添加和访问股票信息
- thread_safe_queue   一个简单的线程安全的队列实现，可以配合spawn_task成为线程安全的任务队列
- union_find    查找一幅图中连通分量个数的算法
- **virtual_table_exp**   虚函数表实验，探究C++虚函数机制的内存结构，backup中附有此实验的结果图和解析图，便于配合理解
- LRU_Cache    LRU缓存，其中包含简单的版本和带有过期时间的版本
