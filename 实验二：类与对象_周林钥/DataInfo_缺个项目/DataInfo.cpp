#include "DataInfo.h"
using namespace std;

DataInfo::DataInfo(){
	yy = 2026;
	mm = 3;
	dd = 23;
	cout << "无参构造函数被调用" << endl;
}

DataInfo::DataInfo(int yy, int mm, int dd):yy(yy), mm(mm), dd(dd){
	cout << "有参构造函数被调用" << endl;
}

DataInfo::DataInfo(const DataInfo& tmp){
	yy = tmp.yy;
	mm = tmp.mm;
	dd = tmp.dd;
	cout << "复制构造函数被调用" << endl;
}

DataInfo::~DataInfo(){
	yy = 0;
	mm = 0;
	dd = 0;
	cout << "析构函数被调用" << endl;
}

void DataInfo:: set(){
	int y;
	int m;
	int d;
	cout << "请依次输入年、月、日（空格隔开）" << endl;
	cin >> y >> m >> d;
	yy = y;
	mm = m;
	dd = d;
}

void DataInfo:: get(){
	cout << "日期：" << yy << "年" << mm << "月" << dd << "日" << endl;
}
