#ifndef FRACTION_H
#define FRACTION_H
#include "Defines.h"
template<class T>
T gcd(T a, T b){
	T c;
	if (a < 0)a = -a;
	if (b < 0)b = -b;
	//取消递归算法，提升性能
	if (a < b){
		c = a;
		a = b;
		b = c;
	}
	if (b == 0)return 1;
	while (1){
		a = a % b;
		if (a == 0)return b;
		b = b % a;
		if (b == 0)return a;
	}
}
int str2int(string s){
	//有缺陷
	int q = 0;
	bool minus = false;
	if (s[0] == '-')minus = true;
	for (int i = minus; i < s.length(); i++){
		q *= 10;
		q += s[i] - '0';
	}
	return minus ? -q : q;
}
//将来支持高精度
//template<class T>
class Fraction{
private:
	int up, down;
public:
	Fraction(){
		up = 0;
		down = 1;
	}
	Fraction(int a){
		up = a;
		down = 1;
	}
	Fraction(string str){
		string temp;
		int i = 0;
		down = 1;
		for (; i < str.length(); i++){
			if (str[i] == '/'){
				string t2;
				for (++i; i < str.length(); i++){
					t2 += str[i];
				}
				down = str2int(t2);
				break;
			}
			temp += str[i];
		}
		up = str2int(temp);
		Simplify();
	}

	Fraction(const char  ch[]){
		string temp;
		temp += ch;
		*this = Fraction(temp);
	}

	void Simplify(){
		if (down == 0)down = 1;
		if (up == 0)return;
		bool minus = false;
		if (up < 0){
			minus = true;
			up = -up;
		}
		if (down < 0){
			minus = !minus;
			down = -down;
		}
		int c = gcd(up, down);
		if (c != 0){
			up /= c;
			down /= c;
		}
		if (minus)up = -up;
	}
	friend ostream & operator << (ostream &r, Fraction &s){
		r << "\t" << s.up;
		if (s.down != 1 && s.up != 0)r << "/" << s.down;
		return r;
	}
	Fraction operator+(const Fraction &right){
		Fraction temp;
		temp.up = up * right.down + right.up * down;
		temp.down = down * right.down;
		Simplify();
		return temp;
	}
	Fraction operator+(const int &i){
		Fraction temp;
		temp.up = up + down * i;
		Simplify();
		return temp;
	}

	Fraction operator-(const Fraction &right){
		Fraction temp;
		temp.up = up * right.down - right.up * down;
		temp.down = down * right.down;
		Simplify();
		return temp;
	}
	Fraction operator-(const int &i){
		Fraction temp;
		temp.up = up - down * i;
		Simplify();
		return temp;
	}

	Fraction operator*(const Fraction &right){
		Fraction temp;
		temp.up = up * right.up;
		temp.down = down * right.down;
		Simplify();
		return temp;
	}
	Fraction operator*(const int &i){
		Fraction temp;
		temp.up = up * i;
		Simplify();
		return temp;
	}

	Fraction operator/(const Fraction &right){
		Fraction temp;
		temp.up = up * right.down;
		temp.down = down * right.up;
		Simplify();
		return temp;
	}
	Fraction operator/(const int &i){
		Fraction temp;
		temp.down *= i;
		Simplify();
		return temp;
	}

	Fraction operator-(){
		Fraction temp = (*this);
		temp.up = -temp.up;
		Simplify();
		return temp;
	}

	Fraction& operator+=(const Fraction& right){
		up = up * right.down + right.up * down;
		down *= right.down;
		Simplify();
		return *this;
	}

	Fraction& operator-=(const Fraction& right){
		up = up * right.down - right.up * down;
		down *= right.down;
		Simplify();
		return *this;
	}

	Fraction& operator*=(const Fraction& right){
		up = up * right.up;
		down *= right.down;
		Simplify();
		return *this;
	}

	Fraction& operator/=(const Fraction& right){
		up = up * right.down;
		down = down * right.up;
		Simplify();
		return *this;
	}

	bool operator<(const Fraction& right){
		return (up*right.down < right.up*down);
	}
	bool operator<=(const Fraction& right){
		return (up*right.down <= right.up*down);
	}
	bool operator==(const Fraction& right){
		return (up*right.down == right.up*down);
	}
	bool operator==(const int &num){
		return (up == down*num);
	}
	bool operator!=(const Fraction& right){
		return (up*right.down != right.up*down);
	}

	Fraction(int u, int d){
		up = u;
		down = d;
		Simplify();
	}
	void Set(int u, int d){
		up = u;
		down = d;
	}
	void Set(string str){
		Fraction temp(str);
		*this = temp;
	}

	int GetInt(){
		return up / down;
	}
	double GetDouble(){
		return up*1.0 / down;
	}
};
#endif
