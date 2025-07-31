#include	<vector>
#include	<iostream>
#include	<algorithm>
using namespace std;
class BigInt{
private:
	vector<int> _digits;
	bool is_negative;
public:
	BigInt():_digits(1,0),is_negative(false)
	{
	}
	BigInt(int num){
		if(num<0){
			num=-num;
			is_negative=true;
		}
		else if(num==0){
			_digits.push_back(0);
			is_negative=false;
		}
		else{
			is_negative=false;
		}
		while(num>0){
			_digits.push_back(num%10);
			num=num/10;
	}
}
	void remove_leading_zeros(){
		while(_digits.size()>1&&_digits.back()==0){
			_digits.pop_back();
		}

	}
	BigInt product_abs(int num)const{
		BigInt result;
		if (num==0)
		{
			return result;
		}
		result._digits.clear();
		int carry=0;
		num=::abs(num);
		for (size_t i = 0; i < _digits.size(); i++)
		{
			int temp = _digits[i]*num+carry;
			result._digits.push_back(temp%10);
			carry = temp/10;
		}

		while (carry>0)
		{
			result._digits.push_back(carry%10);
			carry = carry/10;
		}
		return result;
	}
	BigInt add_abs(const BigInt &other)const{
		BigInt result;
		result._digits.clear();
		size_t size=max(_digits.size(),other._digits.size());
		int pos=min(_digits.size(),other._digits.size());
		int carry=0;
		for(int i=0;i<size;i++){
			int temp=carry;
			if(i<_digits.size()) 
				temp+=_digits[i];
			if(i<other._digits.size())
				temp+=other._digits[i];
			result._digits.push_back(temp%10);
			carry=temp/10;
		}
		while(carry>0){
			result._digits.push_back(carry%10);
			carry=carry/10;
		}
		return result;
	}
	BigInt sub_abs(const BigInt &other)const{
		BigInt result;
		result._digits.clear();
		int carry=0;
		int size=_digits.size();
		int pos=other._digits.size();
		for(int i=0;i<size;i++){	
			int temp=carry;
			if(i<pos) 
				temp+=(_digits[i]-other._digits[i]);
			else
				temp+=_digits[i];
				
			if(temp>=0){
				result._digits.push_back(temp);
				carry=0;
			}
			if(temp<0){
				result._digits.push_back(10+temp);
				carry=-1;
			}
		}
		result.remove_leading_zeros();
		return result;
	}
	int compare_abs(const BigInt &other)const{
		if(_digits.size()!=other._digits.size()){
			return _digits.size()>other._digits.size() ? 1 : -1;
		}
		for(int i=_digits.size()-1;i>=0;i--){
			if(_digits[i]!=other._digits[i]){
				return _digits[i]>other._digits[i] ? 1 : -1; 
			}
		}
		return 0;
	}
	friend BigInt operator+(const BigInt&a,const BigInt&b)
	{
		BigInt result(0);
		if(a.is_negative!=b.is_negative)
		{
			int comp_abs=a.compare_abs(b);
			if(comp_abs>0)
			{
				result=a.sub_abs(b);
				result.is_negative=a.is_negative;
			}else if(comp_abs<0)
			{
				result=b.sub_abs(a);
				result.is_negative=b.is_negative;
			}else
			{
			}
		}else{
			result=a.add_abs(b);
			result.is_negative=a.is_negative;
		}
		return result;
	}
	friend BigInt operator-(const BigInt&a,const BigInt&b){
		BigInt neg_b=b;
		neg_b.is_negative= (b==0)?false:!b.is_negative;
		return a+neg_b;
	}
	friend BigInt operator*(const BigInt&a,int num){
		BigInt result;
		result=a.product_abs(num);
		if(num==0 || a==0)
		{
		}
		else if( num<0 )
		{
			result.is_negative = !a.is_negative;
		}
		else
		{
			result.is_negative = a.is_negative;
		}

		return result;
	}
//	friend BigInt operator-(const BigInt&a,const BigInt&b){
//		BigInt result(0);
//		if(a.is_negative!=b.is_negative){
//			result=a.add_abs(b);
//			result.is_negative=a.is_negative;
//		}else{
//			int comp_abs=a.compare_abs(b);
//			if(comp_abs>0){
//				result=a.sub_abs(b);
//				result.is_negative=a.is_negative;
//			}else if(comp_abs<0){
//				result=b.sub_abs(a);
//				if(b.is_negative){
//					result.is_negative=false;
//				}else{
//					result.is_negative=true;
//				}
//			}else{
//				
//			}
//		}
//		return result;
//	}
	friend bool operator!=(const BigInt& a,const BigInt&b){
		return a.compare_abs(b)!=0;
	}

	friend bool operator>(const BigInt&a,const BigInt&b){
		return a.compare_abs(b)==1;
	}
	friend bool operator==(const BigInt&a,const BigInt&b){
		return a.compare_abs(b)==0;
	}
	friend bool operator<(const BigInt&a,const BigInt&b){
		return a.compare_abs(b)==-1;
	}
	friend bool operator>=(const BigInt&a,const BigInt&b){
		return a.compare_abs(b)>=0;
	}
	friend bool operator<=(const BigInt&a,const BigInt&b){
		return a.compare_abs(b)<=0;
	}
	friend ostream& operator<<(ostream&os,const BigInt&a){
		if(a.is_negative){
			os<<'-';
		}
		for(auto it=a._digits.rbegin();it!=a._digits.rend();it++){
			os<<*it;
		}
		return os;
	}
};
int main(){
	BigInt a(1234);
	BigInt b(-396);
	cout<<a-b<<endl; 
	cout<<a+b<<endl;
	cout<<BigInt(23)-BigInt(23)+BigInt(-434)<<endl;
	cout<<BigInt(23)-5890<<endl;
	cout<<250+BigInt(-64)<<endl;
	cout<<BigInt(-214)+BigInt(-787)<<endl;
	cout<<-2723-BigInt(-1310)<<endl;
	cout<<BigInt(1287)-399<<endl;
	cout<<BigInt(27896)-27839<<endl;
	cout<<BigInt(212394)-212394<<endl;
	cout<<BigInt(212394)+BigInt(-212)<<endl;
	cout<<BigInt(-214)+BigInt(9212)<<endl;
	cout<<BigInt(-214)+BigInt(-927)<<endl;
	cout<<BigInt(0)-BigInt(-1259)<<endl;
	cout<<BigInt(298)+18<<endl;
	
	system("pause");
	return 0;
}
