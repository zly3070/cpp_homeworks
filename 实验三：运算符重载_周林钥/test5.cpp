#include <bits/stdc++.h>
using namespace std;

class Student {
private:
    int num;
    string name;
    bool sex;
public:
    Student(int n, string na, bool s) : num(n), name(na), sex(s) {}
	friend class Teacher;
    friend void getInfo(const Student&);
};

class Teacher {
private:
    int num;
    string name;
    bool sex;
public:
    Teacher(const Student& stu) : num(stu.num), name(stu.name), sex(stu.sex) {}
    
    friend void getInfo(const Teacher&);
};

void getInfo(const Teacher& obj) {
    cout << "学号/工号：" << obj.num << endl;
    cout << "姓名：" << obj.name << endl;
    cout << "性别：" << (obj.sex ? "男" : "女") << endl;
}

void getInfo(const Student& obj) {
    cout << "学号/工号：" << obj.num << endl;
    cout << "姓名：" << obj.name << endl;
    cout << "性别：" << (obj.sex ? "男" : "女") << endl;
}

int main() {
    Student stu(123, "张三", true);
    Teacher tea(stu);
    
    getInfo(stu);
    getInfo(tea);
    
    return 0;
}
