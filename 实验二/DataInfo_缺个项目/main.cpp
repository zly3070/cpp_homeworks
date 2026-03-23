#include "DataInfo.h"
#include <windows.h>
using namespace std;

int main(){
	SetConsoleOutputCP(CP_UTF8);  //让控制台用 UTF-8 显示
	DataInfo DataInfo1;  //无参构造函数
	DataInfo DataInfo2 (6666, 66, 66);  //有参构造函数
	DataInfo DataInfo3(DataInfo1);  //复制构造函数
	DataInfo1.set();  //日期设置
	DataInfo1.get();
	system("pause");
	return 0;
}