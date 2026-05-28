#ifndef DATE_HEADER
#define DATE_HEADER
#include <iostream>
using namespace std;
//-------------------------------------
class Date
{
  int _absDay;
  void _ymd2i(int y, int m, int d);
  bool _isLeapYear(int y) const { return y % 4 == 0 && y % 100 || y % 400 == 0; }
  void _i2ymd(int &y, int &m, int &d) const;
  static const int tians[];
  static const char *week[];

public:
  enum
  {
    YYMD, // "YYYY-MM-DD"
    MDYY, // "MM-DD-YYYY"
    YMD,  // "YY-MM-DD"
    MDY   // "MM-DD-YY"
  };
  Date(const string &s);
  Date(int n = 1) : _absDay(n) {}
  Date(int y, int m, int d) { _ymd2i(y, m, d); }
  Date operator+(int n) const { return Date(_absDay + n); }
  Date &operator+=(int n)
  {
    _absDay += n;
    return *this;
  }
  Date &operator++()
  {
    _absDay++;
    return *this;
  }
  Date &operator--()
  {
    _absDay--;
    return *this;
  }
  bool operator==(const Date &d) const { return _absDay == d._absDay; }
  bool operator!=(const Date &d) const { return _absDay != d._absDay; }
  bool operator<(const Date &d) const { return _absDay < d._absDay; }
  void print(ostream &out, int type) const;
  int operator-(Date &d) const { return _absDay - d._absDay; }
  Date operator-(int n) const { return Date(_absDay - n); }
  Date &operator-=(int n)
  {
    _absDay -= n;
    return *this;
  }
  bool isLeapYear() const;
  const char *getWeekDay() const { return week[_absDay % 7]; }
  int getAbsDay() const { return _absDay; }
  friend istream &operator>>(istream &i, Date &d);
  friend ostream &operator<<(ostream &o, const Date &d);
}; //-----------------------------------
#endif // DATE_HEADER
