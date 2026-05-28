#include <bits/stdc++.h>
using namespace std;

class Alumni{
	public:
		Alumni(string, char, unsigned int, unsigned int, string, string, string, string, string, string);
		void display();

		void setName();
		string getName(){return name;}
		
		void setGender();
		char getGender(){return Gender;}
		
		void setAge();
		unsigned getAge(){return age;}
		
		void setBatch();
		unsigned getBatch(){return batch;}
		
		void setDepartment();
		string getDepartment(){return department;}
		
		void setClassName();
		string getClassName(){return classname;}
		
		void setAddr();
		string getAddr(){return addr;}
		
		void setNum();
		string getNum(){return num;}
		
		void setQq();
		string getQq(){return qq;}
		
		void setEmail();
		string getEmail(){return eml;}

	private:
		string name;
		char gender;
		unsigned int age;
		unsigned int batch;
		string department;
		string className;
		string addr;
		string num;
		string qq;
		string eml;
};

Alumni::Alumni(string n, char g, unsigned int a, unsigned int b, string d, string c, string address, string number, string qqNumber, string email):
	name(n), gender(g), age(a), batch(b), department(d), className(c), addr(address), num(number), qq(qqNumber), eml(email) {}
	
void Alumni::display(){
	cout << "name:" << name << endl;
	cout << "gender:" << (gender=='m' ? "male":"female") << endl;
	cout << "age:" << age << endl;
	cout << "batch:" << batch << endl;
	cout << "department:" << department << endl;
	cout << "className:" << className << endl;
	cout << "address:" << addr << endl;
	cout << "phoneNumber:" << num << endl;
	cout << "qq:" << qq << endl;
	cout << "email:" << eml << endl;
} 

void Alumni::setName(){
	string tmp = name;
	cout << "Original name: " << name << ", " << "change to --> ";
	cin >> name;
	cout << "Successfully changed the name from " << tmp << " to " << name << endl; 
}

void Alumni::setGender(){
	char tmp = gender;
	cout << "Original gender: " << (gender=='m' ? "male":"female") << ", " << "change to --> ";
	cin >> gender;
	cout << "Successfully changed the gender from " << tmp << " to " << gender << endl; 
}

void Alumni::setAge(){
	unsigned int tmp = age;
	cout << "Original age: " << age << ", " << "change to --> ";
	cin >> age;
	cout << "Successfully changed the age from " << tmp << " to " << age << endl;
}
	
void Alumni::setBatch(){
	unsigned int tmp = batch;
	cout << "Original batch: " << batch << ", " << "change to --> ";
	cin >> batch;
	cout << "Successfully changed the batch from " << tmp << " to " << batch << endl;
}
void Alumni::setDepartment(){
	string tmp = department;
	cout << "Original department: " << department << ", " << "change to --> ";
	cin >> department;
	cout << "Successfully changed the department from " << tmp << " to " << department << endl;
}
void Alumni::setClassName(){
	string tmp = className;
	cout << "Original classname: " << className << ", " << "change to --> ";
	cin >> className;
	cout << "Successfully changed the className from " << tmp << " to " << className << endl;
}
void Alumni::setAddr(){
	string tmp = addr;
	cout << "Original address: " << addr << ", " << "change to --> ";
	cin >> addr;
	cout << "Successfully changed the address from " << tmp << " to " << addr << endl;
}
void Alumni::setNum(){
	string tmp = num;
	cout << "Original number: " << num << ", " << "change to -> ";
	cin >> num;
	cout << "Successfully changed the age from " << tmp << " to " << num << endl;
}
void Alumni::setQq(){
	string tmp = qq;
	cout << "Original qq: " << qq << ", " << "change to -> ";
	cin >> qq;
	cout << "Successfully changed the age from " << tmp << " to " << qq << endl;
}
void Alumni::setEmail(){
	string tmp = eml;
	cout << "Original email: " << eml << ", " << "change to -> ";
	cin >> eml;
	cout << "Successfully changed the age from " << tmp << " to " << eml << endl;
}
Alumni inputAlumni(){
	string name, department, className, addr, num, qq, email;
    char gender;
    unsigned int age, batch;

    cout << "姓名: "; cin.ignore(); getline(cin, name);
    cout << "性别(m/f): "; cin >> gender;
    cout << "年龄: "; cin >> age;
    cout << "届级: "; cin >> batch;
    cout << "系: "; cin >> department;
    cout << "班级: "; cin >> className;
    cout << "通讯地址: "; cin >> addr;
    cout << "电话: "; cin >> num;
    cout << "QQ: "; cin >> qq;
    cout << "邮箱: "; cin >> email;

    return Alumni(name, gender, age, batch, department, 
                  className, addr, num, qq, email);
}

void sortAlumniList(vector<ALumni>& list){
	sort(list.begin(), list.end(), [](const Alumni& a, const Alumni& b){
		if (a.getBatch()==b.getBatch()){
			return a.getName() < b.getName();
		} else{
			return a.getBatch() < getBatch();
		}
	})
}