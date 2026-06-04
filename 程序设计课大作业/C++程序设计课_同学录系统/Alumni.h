#include <bits/stdc++.h>
using namespace std;

class Alumni{
	public:
		Alumni(string, char, unsigned int, unsigned int, string, string, string, string, string, string);
		void display();

		void setName();
		string getName() const {return name;}
		
		void setGender();
		char getGender() const {return gender;}
		
		void setAge();
		unsigned getAge() const {return age;}
		
		void setBatch();
		unsigned getBatch() const {return batch;}
		
		void setDepartment();
		string getDepartment() const {return department;}
		
		void setClassName();
		string getClassName() const {return className;}
		
		void setAddr();
		string getAddr() const {return addr;}
		
		void setNum();
		string getNum() const {return num;}
		
		void setQq();
		string getQq() const {return qq;}
		
		void setEmail();
		string getEmail() const {return eml;}

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
	cout << "Original gender: " << (gender=='m' ? "male":"female") << ", " << "change to(m/f) --> ";
	cin >> gender;
	cout << "Successfully changed the gender from " << (tmp=='m' ? "male":"female") << " to " << (gender=='m' ? "male":"female") << endl; 
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

void sortAlumniList(vector<Alumni>& list){
	sort(list.begin(), list.end(), [](const Alumni& a, const Alumni& b){
		if (a.getBatch()==b.getBatch()){
			return a.getName() < b.getName();
		} else{
			return a.getBatch() < b.getBatch();
		}
	});
}

void loadTestData(vector<Alumni> &list){  // 加载测试数据脚本
	list.push_back(Alumni("张三", 'm', 22, 2024, "计算机系", "计科1班", "杭州", "13800000001", "10001", "zhangsan@test.com"));
    list.push_back(Alumni("李四", 'f', 21, 2025, "计算机系", "计科2班", "宁波", "13800000002", "10002", "lisi@test.com"));
    list.push_back(Alumni("王五", 'm', 23, 2023, "计算机系", "计科1班", "温州", "13800000003", "10003", "wangwu@test.com"));
    list.push_back(Alumni("赵六", 'm', 22, 2024, "软件学院", "软工1班", "绍兴", "13800000004", "10004", "zhaoliu@test.com"));
    list.push_back(Alumni("孙七", 'f', 24, 2022, "软件学院", "软工2班", "嘉兴", "13800000005", "10005", "sunqi@test.com"));

    cout << "【调试模式】已加载 " << list.size() << " 条测试数据\n";
}

void setAlumni(vector<Alumni>& list){
	int index;
	cout << "请输入要修改的校友编号：";
	cin >> index;
	if (index < 1 || index > list.size()){ // 检测编号有效性
		cout << "编号无效！\n";
		return;
	}
	Alumni* p2Alumni = &list[index-1];
	int field;
    cout << "\n选择要修改的字段:\n";
    cout << "1. 姓名\n";
    cout << "2. 性别\n";
    cout << "3. 年龄\n";
    cout << "4. 届级\n";
    cout << "5. 系\n";
    cout << "6. 班级\n";
    cout << "7. 通讯地址\n";
    cout << "8. 电话\n";
    cout << "9. QQ\n";
    cout << "10. 邮箱\n";
    cout << "请输入选择: ";
    cin >> field;
	switch(field){
		case 1: p2Alumni->setName(); break;
		case 2: p2Alumni->setGender(); break;
		case 3: p2Alumni->setAge(); break;
		case 4: p2Alumni->setBatch(); break;
		case 5: p2Alumni->setDepartment(); break;
		case 6: p2Alumni->setClassName(); break;
		case 7: p2Alumni->setAddr(); break;
		case 8: p2Alumni->setNum(); break;
		case 9: p2Alumni->setQq(); break;
		case 10: p2Alumni->setEmail(); break;
		default: cout << "无效输入！\n"; break;
	}
}

void deleteAlumni(vector<Alumni>& list){
	int index;
	cout << "请输入要删除的校友编号：\n";
	cin >> index;

	if (index < 1 || index > list.size()){
		cout << "编号无效！\n";
		return;
	}
	cout << "\n即将删除以下校友信息：" << endl;
    list[index - 1].display();
    
    char confirm;
    cout << "\n确认删除？(y/n): ";
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        list.erase(list.begin() + (index - 1));
        cout << "删除成功！" << endl;
    } else {
        cout << "已取消删除。" << endl;
	}
}

void queryAlumni(vector<Alumni>& list){
	cin.ignore();
    cout << "输入关键词，空格分隔多个关键词\n";
    cout << "请输入: ";
	string input;
	getline(cin, input);

	vector<string> keywords;
	stringstream ss(input);
	string word;
	while(ss >> word){
		keywords.push_back(word);	
	}
	// cout << "当前keywords.size()=" << keywords.size() << endl;
	if (keywords.empty()){
		cout << "未检测到有效关键词！\n";
		return;
	}

	vector<pair<int, Alumni>> results;  // pair<match, Alumni>
	for (const auto& a : list){
		int match = 0;
		for (const auto& kw : keywords){ // kw 关键词  find(something)!=string::npos 有匹配到该关键词 
			if ((a.getName().find(kw)) != string::npos) match += 1;
			if (a.getGender() == kw[0]) match += 1;
			if (to_string(a.getAge()) == kw) match += 1;
			if (to_string(a.getBatch()) == kw) match += 1;
			if ((a.getDepartment().find(kw)) != string::npos) match += 1;
			if ((a.getClassName().find(kw)) != string::npos) match += 1;
			if ((a.getAddr().find(kw)) != string::npos) match += 1;
			if ((a.getNum().find(kw)) != string::npos) match += 1;
			if ((a.getQq().find(kw)) != string::npos) match += 1;
			if ((a.getEmail().find(kw)) != string::npos) match += 1;
		}
		if (!match) continue; // 若一个关键词都匹配不上，则跳过当前循环，尝试匹配下一位校友
		// cout << "当前" << a.getName() << "校友的match：" << match << endl;
		if (match > (int)keywords.size()-2){ // .size()返回的是size_t类型的，负数会溢出，变为很大的正数
			results.push_back(make_pair(match, a));
		}
	}
	
	stable_sort(results.begin(), results.end(), // 使用stable_sort保留原始排序特性
		[](const pair<int, Alumni>& x, const pair<int, Alumni>& y){
			return x.first > y.first;
		});

	if (results.empty()){
			cout << "未找到匹配的校友！\n";
			return;
		} else {
			cout << "找到" << results.size() << "位匹配的校友：\n\n";
			for (size_t i = 0; i < results.size(); i++){
				cout << "--- 结果" << i + 1 << "---\n";
				results[i].second.display();
				cout << endl;
			}
		}
}

void saveToFile(const vector<Alumni>& list, const string& filename){  // 向文件中写入队列
	ofstream out(filename);
	if (!out){
		cerr << "警告：无法打开文件" << filename << "进行保存\n";
		return;
	}
	
	for (const auto& a : list){
		// 写入时用"|"作为分隔符
		out << a.getName() << "|"
            << a.getGender() << "|"
            << a.getAge() << "|"
            << a.getBatch() << "|"
            << a.getDepartment() << "|"
            << a.getClassName() << "|"
            << a.getAddr() << "|"
            << a.getNum() << "|"
            << a.getQq() << "|"
            << a.getEmail() << "\n";

	}
}

void loadFromFile(vector<Alumni>& list, const string& filename){  // main起初时，从文件中读取数据
	ifstream in(filename);
	if (!in){
		return;  //初次运行时没有文件，故直接退出无妨
	}
	list.clear();
	string line;
	
}

/*
cout << "\n选择要修改的字段:\n";
    cout << "1. 姓名\n";
    cout << "2. 性别\n";
    cout << "3. 年龄\n";
    cout << "4. 届级\n";
    cout << "5. 系\n";
    cout << "6. 班级\n";
    cout << "7. 通讯地址\n";
    cout << "8. 电话\n";
    cout << "9. QQ\n";
    cout << "10. 邮箱\n";
    cout << "请输入选择: ";
*/