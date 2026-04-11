#include <bits/stdc++.h>
using namespace std;

class Matrix{
	private:
		array<array<int, 3>, 2> data = {};
	public:
		Matrix(){
			for (int i = 0; i < 2; i ++){
				for (int j = 0; j < 3; j++){
					data[i][j] = 0;
				}
			}
		}
		Matrix(initializer_list<initializer_list<int>> list){
			int i = 0;
			for (const auto& row : list){
				int j = 0;
				for (const auto& val : row){
					data[i][j] = val;
					j ++;
				}
				i ++;
			}
		}
		friend Matrix operator+(const Matrix& juzhen1, const Matrix& juzhen2);
		void getMatrix() const;
		friend istream& operator>>(istream&, Matrix&);
		friend ostream& operator<<(ostream&, const Matrix&);
};

Matrix operator+(const Matrix& juzhen1, const Matrix& juzhen2){
	Matrix tmp;
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			tmp.data[i][j] = juzhen1.data[i][j] + juzhen2.data[i][j];
		}
	}
	return tmp;
}

void Matrix::getMatrix() const {
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++){
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

istream& operator>>(istream& input, Matrix& m){
    cout << "请输入6个整数（2行3列）：" << endl;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            input >> m.data[i][j];
        }
    }
    return input;
}

ostream& operator<<(ostream& output, const Matrix& m){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 3; j++){
            output << m.data[i][j] << " ";
        }
        output << endl;
    }
    return output;
}

int main(){
	Matrix a = {
		{2, 3, 0},
		{1, 4, 5}
	}; 
	Matrix b = {
		{1, 2, 3},
		{-1, 2, 4}
	}; 
	Matrix c = a + b;
	cout << c << endl;
	Matrix d;
	cin >> d; 
	cout << d;
	return 0;
}
