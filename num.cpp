#include	<vector>
#include	<iostream>
using namespace std;
class BigInt{
private:
	vector<int>_digits;
public:
	BigInt();
	BigInt(int num);
	BigInt operator+(const BigInt&other)const;
	BigInt operator*(int num)const;
//	BigInt factorial(int num)const;
	void print()const;
	int getDigit(int pos)const; 
};
BigInt::BigInt(){
	
}
BigInt::BigInt(int num){
	while(num>0){
		_digits.push_back(num%10);
		num/=10;
	}
}
int BigInt::getDigit(int pos)const{
	if(pos>=_digits.size()){
		return 0;
	}
	return _digits[pos];
}
BigInt BigInt::operator+(const BigInt&other)const{
	int carry=0;
	BigInt result;
	int size=max(_digits.size(),other._digits.size());
	for(int i=0;i<size;i++){
		int temp=getDigit(i)+other.getDigit(i)+carry;
		result._digits.push_back(temp%10);
		carry=temp/10;
	}
	if(carry!=0)
		result._digits.push_back(carry);
	
	return result;
}
BigInt BigInt::operator*(int num)const{
	int carry=0;
	BigInt result;
	int size=_digits.size();
	for(int i=0;i<size;i++){
		int temp=getDigit(i)*num+carry;
		result._digits.push_back(temp%10);
		carry=temp/10;
	}
	while(carry>0){
		result._digits.push_back(carry%10);
		carry/=10;
	}
		
	return result;
}
//BigInt BigInt::factorial(int num)const{
//	BigInt result(1);
//	for(int i=2;i<=num;i++){
//		result=result*i;
//	}
//	return result;
//}
void BigInt::print()const{
	for(int i=_digits.size()-1;i>=0;i--){
		cout<<_digits[i];
	}
}
int main(){
	int num=0;
	cin>>num;
	BigInt result(1);
	BigInt factorial(1);
	for(int i=2;i<=num;i++){
		factorial = factorial*i;
		result = result + factorial;
	}
	result.print();
}













