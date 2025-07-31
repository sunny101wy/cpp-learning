#include	<vector>
#include	<iostream>
using namespace std;
class BigInt{
private:
	vector<int>_num;
	int _sign;
	BigInt _add(const BigInt&other)const
	{
		BigInt result;
		int size=max(other._num.size(),_num.size());
		int carry=0;
		int pos=min(other._num.size(),_num.size());
		for(int i=0;i<size;i++)
		{
			int temp=0;
			if(i>=pos&&_num.size()>other._num.size())
			{
				temp=_num[i]+carry;
			}else if(i>=pos&&_num.size()<other._num.size())
			{
				temp=other._num[i]+carry;
			}
			else
			{
				temp=_num[i]+other._num[i]+carry;
			}
			result._num.push_back(temp%10);
			carry=temp/10;
		}
		while(carry>0)
		{
			result._num.push_back(carry%10);
			carry=carry/10;
		}
		return result;
	}
	BigInt _sub(const BigInt&other)const
	{
		BigInt result;
		int carry=0;
		int size=_num.size();
		int pos=other._num.size();
		for(int i=0;i<size;i++)
		{	
			int temp=0;
			if(i>=pos)
			{
				temp=_num[i]+carry;
			}else
			{
				temp=_num[i]-other._num[i]+carry;
			}
			if(temp>=0)
			{	
				carry=0;
				result._num.push_back(temp);
			}else{
				result._num.push_back(10+temp);
				carry=-1;
			}
		}
		return result;
	}
public:
	BigInt();
	BigInt(int num);
	BigInt operator*(int p)const;
	bool operator<(const BigInt&other)const;
	bool operator>(const BigInt&other)const;
	bool operator==(const BigInt&other)const;
	bool operator>=(const BigInt&other)const;
	bool operator<=(const BigInt&other)const;
	BigInt operator-(const BigInt&other)const;
	BigInt operator+(const BigInt&other)const;
	void print();
};
BigInt::BigInt(){
	
}
BigInt::BigInt(int num){
	if(num<0){
		num=-num;
		_sign=-1;
	}
	else if(num==0){
		_num.push_back(0);
		_sign=0;
	}
	else{
		_sign=1;
	}
	while(num>0){
		_num.push_back(num%10);
		num=num/10;
	}
	
}
BigInt BigInt::operator*(int p)const{
	BigInt result;
	if(p==0||_sign==0){
		result._num.push_back(0);
		return result;
	}
	if(p<0&&this->_sign<0){
		result._sign=1;
		p=-p;
	}else if(p<0&&_sign>0){
		result._sign=-1;
		p=-p;
	}else{
		result._sign=_sign;
	}
	int carry=0;
	for(int i=0;i<this->_num.size();i++){
		result._num.push_back(_num[i]*p+carry);
		carry=(_num[i]*p+carry)/10;
	}
	while(carry>0){
		result._num.push_back(carry%10);
		carry/10; 
	}
	return result;
	
}
bool BigInt::operator<(const BigInt&other)const{
	if(_sign<other._sign){
		return true;
		
	}
	else if(_sign>other._sign){
		return false;
	}
	else if(_sign==other._sign){
		if(other==*this){
			return false;
		}
		else if(_num.size()==other._num.size()){
			for(int i=_num.size()-1;i>=0;i--){
				int temp=_num[i]-other._num[i];
				if(_num[i]<other._num[i]&&_sign>0){
					return true;
				}
				if(_num[i]>other._num[i]&&_sign>0){
					return false;
				}
				if(_num[i]<other._num[i]&&_sign<0){
					return false;
				}
				if(_num[i]>other._num[i]&&_sign<0){
					return true;
				}
			}
		}
		else if(_num.size()>other._num.size()&&_sign>0){
			return false;
		}
		else if(_num.size()<other._num.size()&&_sign<0){
			return false;
		}
		return true;
	}
}
bool BigInt::operator==(const BigInt&other)const{
	if(other._sign!=_sign){
		return false;
	}
	else if(_sign==0){
		return true;
	}
	else if(_num.size()!=other._num.size()){
		return false;
	}
	for(int i=0;i<_num.size();i++){
		if(_num[i]!=other._num[i]){
			return false;
		}
	}
	return true;
}
bool BigInt::operator>(const BigInt&other)const{
	if(*this<other||other==*this){
		return false;
	}
	return true;
}
bool BigInt::operator<=(const BigInt&other)const{
	if(other>*this||other==*this){
		return true;
	}
	return false;
}
bool BigInt::operator>=(const BigInt&other)const{
	if(other<*this||other==*this){
		return true;
	}
	return false;
} 

BigInt BigInt::operator-(const BigInt&other)const{
	BigInt result;
	if(_sign>0&&other._sign<0)
	{
		result=_add(other);
		result._sign=1;
	}
	else if(_sign>0&&other._sign>0)
	{
		if(*this<other)
		{
			result=other._sub(*this);
			result._sign=-1;
		}
		else if(*this==other)
		{
			result._sign=0;
			result._num.push_back(0);
		}
		else
		{
			result=_sub(other);
			result._sign=1;
		}
	}
	else if(_sign<0&&other._sign>0)
	{
		result=_add(other);
		result._sign=-1;
	}
	else if(_sign<0&&other._sign<0)
	{
		if(*this>other)
		{
			result=other._sub(*this);
			result._sign=1;
		}
		else if(*this==other)
		{
			result._sign=0;
			result._num.push_back(0);
		}
		else
		{
			result=_sub(other);
			result._sign=-1;
		}
	}
	else if(_sign==0&&other._sign>0)
	{
		result=other;
		result._sign=-1;
	}
	else if(_sign==0&&other._sign<0)
	{
		result=other;
		result._sign=1;
	}
	else if(_sign>0&&other._sign==0)
	{
		result=*this;
		result._sign=1;
	}
	else if(_sign<0&&other._sign==0)
	{
		result=*this;
		result._sign=-1;
	}
	else if(_sign==0&&other._sign==0){
		result._num.push_back(0);
		result._sign=0;
	}
	return result;
}
BigInt BigInt::operator+(const BigInt&other)const{
	BigInt result;
	if(_sign>0&&other._sign<0)
	{	if(*this>other*-1)
		{
			result=_sub(other);
			result._sign=1;
		}
		else if(*this==other*-1)
		{
			result._sign=0;
			result._num.push_back(0);
		}
		else
		{
			result=other._sub(*this);
			result._sign=-1;
		}
	}
	else if(_sign>0&&other._sign>0)
	{
		result=_add(other);
		result._sign=1;
	}
	else if(_sign<0&&other._sign>0)
	{
		if(*this>other*-1)
		{
			result=_sub(other);
			result._sign=-1;
		}
		else if(*this==other*-1)
		{
			result._sign=0;
			result._num.push_back(0);
		}
		else
		{
			result=other._sub(*this);
			result._sign=1;
		}
	}
	else if(_sign<0&&other._sign<0)
	{
		result=_add(other);
		result._sign=-1;
	}
	else if(_sign==0&&other._sign>0)
	{
		result=other;
		result._sign=1;
	}
	else if(_sign==0&&other._sign<0)
	{
		result=other;
		result._sign=-1;
	}
	else if(_sign>0&&other._sign==0)
	{
		result=*this;
		result._sign=1;
	}
	else if(_sign<0&&other._sign==0)
	{
		result=*this;
		result._sign=-1;
	}
	else if(_sign==0&&other._sign==0){
		result._num.push_back(0);
		result._sign=0;
	}
	return result;
}
void BigInt::print(){
	if(_sign<0){
		cout<<'-';
	}
//	if(_sign==0){
//		cout<<'0';
//		return;
//	}

	for(int i=_num.size()-1;i>=0;i--){
		cout<<_num[i];
	}
	cout<<' ';
}
int main(){
//	BigInt result;
//	int p;
//	cin>>p;
//	for(int i=0;i<p;i++){
//		result=result * 2;
//		result = result.operator*(2);
//	}
	int a,b;
//	cin>>a>>b;
	BigInt n(-372);
	BigInt m(-9696);
	BigInt r1 = m+n;
	BigInt r2 = m-n;
	r1.print();
	r2.print();
	cout<<2;
//	cout<<n;
	return 0; 
}



