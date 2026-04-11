#include <bits/stdc++.h>
using namespace std;

class Sale{
	private:
		int num;
		int quantity;
		double price;
		
		static double discount;
		static double sum;  //总销售额 
		static int n;  //总销售件数 
	
	public:
		Sale(int n, int q, double p) : num(n), quantity(q), price(p) {} 
		
		static void setDiscount(){
			cout << "请输入discount：" << endl;
			cin >> discount;
		}
		
		void calculate(){
			double salePrice = price;
			if (quantity > 10){
				salePrice *= 0.98;
			}
			salePrice *= discount;
			double saleMoney = salePrice * quantity;
			sum += saleMoney;
			n += quantity;
		}
		
		static double average(){
			if (n == 0) return 0;
			return sum / n;
		}
		
		static void display(){
			cout << fixed << setprecision(2);
			cout << "sum:"  << sum << endl;
			cout << "average:" << average() << endl;
		}
};

//类外初始化静态数据成员 
double Sale::discount = 0.95;  //此处为随便给的初始值 
double Sale::sum = 0;
int Sale::n = 0; 

int main(){
	Sale sales[3] = {
		{101, 5, 23.5},
        {102, 12, 24.56},
        {103, 100, 21.5}
	};
	Sale::setDiscount();
	for (int i = 0; i < 3; i++){
		sales[i].calculate();
	}
	Sale::average();
	Sale::display();
	return 0;
} 


