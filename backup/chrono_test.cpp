#include <iostream>
#include <vector>

#include <chrono>
#include <thread>
#include <string>
#include <iomanip>

using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using namespace std::chrono;

void do_something() {
	cout << "do something" << endl;
	std::this_thread::sleep_for(1s);
}

// 日期格式化
string current_time(string format)
{
	stringstream ss;
	auto now = system_clock::now();
	time_t t1 = system_clock::to_time_t(now);
	ss << std::put_time(localtime(&t1), format.c_str());
	string time = ss.str();
	return time;
}

int main(int argc, char **argv) {

	// 时间字面值常量的使用，y，d，h,min,s,ms,us,ns,紧跟在数字后即可作为时间段
	auto one_seconds = 1s;
	std::this_thread::sleep_for(one_seconds);

	// 时间段类型转换，duration_cast
	auto day = 24h;
	auto my_second = seconds(day);
	day = duration_cast<hours>(my_second);
	cout << my_second.count() << endl;

	// 记录一个时间点，时间点相减可得时间段，时间点与时间段相加减仍是时间点
	auto now_point = system_clock::now();
	cout << duration_cast<days>(now_point.time_since_epoch()).count() << endl;

	// 程序计时的常用手段，在需要计时的代码段前记录当前时间点old，代码段结束后再记录一个新时间点now，dur = now - old，即可得出一段代码的执行时间
	auto old = steady_clock::now();
	do_something();
	auto dur = steady_clock::now() - old;
	cout << dur.count() << " " << duration_cast<milliseconds>(dur).count() << endl;

	// 自定义格式，将日期和时间格式化为字符串
	string format = "%Y/%m/%d  %H:%M:%S";
	cout << current_time(format) << endl;

}