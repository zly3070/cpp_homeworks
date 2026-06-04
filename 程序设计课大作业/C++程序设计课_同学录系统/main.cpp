#include <bits/stdc++.h>
#include "Alumni.h"
using namespace std;
 
void sortAlumniList(vector<Alumni>& list);
void loadTestData(vector<Alumni>& list); // 批量生成测试数据（调试用）
void setAlumni(vector<Alumni>& list); // 修改
void deleteAlumni(vector<Alumni>& list); // 删除
void queryAlumni(vector<Alumni>& list); // 查询

int main(){
	vector<Alumni> alumniList; // 存储所有校友
	int choice = -1;

	loadTestData(alumniList); // 载入测试数据 

	loadFromFile(alumniList, "alumni_data.txt"); // 从文件读取校友类列表
	
	do{
		sortAlumniList(alumniList);
		cout << "\n===校友录管理系统===\n";
		cout << "1.录入校友\n";
		cout << "2.显示所有校友\n";
		cout << "3.修改校友信息\n";
		cout << "4.删除校友\n";
		cout << "5.查询校友\n";
		cout << "0.退出系统\n";
		cout << "请选择：";
		
		if (!(cin >> choice)) {
    		cout << "检测到无效字符！\n";
    		cin.clear();                 // 清除错误标志
    		cin.ignore(1024, '\n');     // 丢掉错误的输入
    		choice = -1;
			continue;                   // 直接跳回循环开头，不进入下面的 switch
		}

		switch(choice){
			case 1:  // 录入
				alumniList.push_back(inputAlumni());
				cout << "录入成功！\n";
			break;

			case 2:  // 展示全部
				if (alumniList.empty()){ // 先检查
					cout << "暂无校友数据，请先录入！\n";
					break;
				}
				for (size_t i = 0; i < alumniList.size(); i++){
					cout << "--- 校友 " << i+1 << "---\n";
					alumniList[i].display();
					cout << endl;
				}
			break;

			case 3:  // 修改
				if (alumniList.empty()){ // 先检查
					cout << "暂无校友数据，请先录入！\n";
					break;
				}
				setAlumni(alumniList);
			break;

			case 4:  // 删除
				if (alumniList.empty()){ // 先检查
					cout << "暂无校友数据，请先录入！\n";
					break;
				}
				deleteAlumni(alumniList);
			break;

			case 5:  // 查询
				if (alumniList.empty()){ // 先检查
					cout << "暂无校友数据，请先录入！\n";
					break;
				}
				queryAlumni(alumniList);
			break;
		}
	}while(choice != 0);
	cout << "退出系统...\n";
	saveToFile(alumniList, "alumni_data.txt");
	return 0;‘
	
/*
	Alumni alumni1("Zhang", 'm', 25, 2026, "化工", "化工1班", "Hangzhou", "18258193070", "2049990576", "2049990576@qq.com");
	alumni1.display();
	alumni1.setName();
	alumni1.setGender();
	alumni1.setAge();
	alumni1.setBatch();
	alumni1.setDepartment();
	alumni1.setClassName();
	alumni1.setAddr();
	alumni1.setNum();
	alumni1.setQq();
	alumni1.setEmail();
	cout << "set end." << endl;
	alumni1.display();
	return 0;
*/
}