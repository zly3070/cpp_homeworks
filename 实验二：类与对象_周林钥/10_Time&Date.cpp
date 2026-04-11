#include <bits/stdc++.h>
using namespace std;

class Date;

class Time{
	public:
		Time(int h, int m, int s) : hour(h), minute(m), sec(s){};
		friend void display(Date&, Time&);
	private:
		int hour;
		int minute;
		int sec;
};

class Date{
	public:
		Date(int y, int m, int d) : year(y), month(m), day(d){};
		friend void display(Date&, Time&);
	private:
		int year;
		int month;
		int day;
};

void display(Date& D, Time& T){
	cout << D.year << "Äê" << D.month << "ÔÂ" << D.day<< "ÈÕ" << endl;
	cout << T.hour << ":" << T.minute << ":" << T.sec << endl;
}

int main(){
	Time t1{10, 36, 56};
	Date d1{12, 25, 2024};
	display(d1, t1);
	return 0;
}
