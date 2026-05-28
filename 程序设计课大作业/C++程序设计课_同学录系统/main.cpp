#include <bits/stdc++.h>
#include "Alumni.h"
using namespace std;
 
void sortAlumniList(vector<ALumni>& list);

int main(){
	vector<Alumni> alumniList; // 存储所有校友
	int choice;

	do{
		sortAlumniList(alumniList);
		cout << "\n===校友录管理系统===\n";
		cout << "1.录入校友\n";
		cout << "2.显示所有校友\n";
		cout << "3.修改校友信息\n";
		cout << "4.删除校友\n";
		cout << "5.查询校友\n";
		cout << "0.退出\n";
		cout << "请选择：";
		cin >> choice;

		switch(choice){
			case 1:  // 录入
				alumniList.push_back(inputAlumni());
				cout << "录入成功！\n";
			break;

			case 2:  // 展示全部
				for (size_t i = 0; i < alumniList.size(); i++){
					cout << "--- 校友 " << i+1 << "---\n";
					alumniList[i].display();
				}
			break;

			case 3:  // 修改
				
			break;

			case 4:  // 删除
			break;

			case 5:  // 查询
			break;
		}
	}while(choice!=0);
	cout << "退出系统...\n";
	return 0;
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