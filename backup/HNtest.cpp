

#include <iostream>
#include <vector>



using std::cin;
using std::cout;
using std::endl;
using std::vector;

using namespace std;

union HNtest {
	int a;
	char b;
};

int main(int argc, char **argv) {

	HNtest u1{0x12345678};
	if(u1.b == 0x78) cout << "N" << endl;       // 小端，高位在高地址
	else if(u1.b == 0x12) cout << "H" << endl;  // 大端，高位在低地址

	return 0;
}


// #pragma clang diagnostic pop