#include <bits/stdc++.h>
using namespace std;

class DataInfo{
	private:
		int yy;
		int mm;
		int dd;
	public:
		DataInfo();  //无参数构造函数
		DataInfo(int, int, int);  //有参构造函数
		DataInfo(const DataInfo&);  //复制构造函数
		~DataInfo();  //析构函数
		void set();  //实现日期设置
		void get();  //实现日期获取
		
};