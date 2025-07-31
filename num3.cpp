#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

class BigInt {
private:
    vector<int> digits; // µÍÎ»ÔÚÇ°
    bool is_negative;

    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            is_negative = false;
    }

    BigInt add_abs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        int carry = 0;
        size_t max_len = max(digits.size(), other.digits.size());
        for (size_t i = 0; i < max_len || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }
        result.is_negative = false;
        return result;
    }

    BigInt sub_abs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        int borrow = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int sub = digits[i] - borrow;
            borrow = 0;
            if (i < other.digits.size())
                sub -= other.digits[i];
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            }
            result.digits.push_back(sub);
        }
        result.remove_leading_zeros();
        return result;
    }

    int compare_abs(const BigInt& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() > other.digits.size() ? 1 : -1;
        for (int i = digits.size()-1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return digits[i] > other.digits[i] ? 1 : -1;
        }
        return 0;
    }

public:
    BigInt() : digits(1, 0), is_negative(false) {}

    BigInt(long long num) {
        if (num < 0) {
            is_negative = true;
            num = -num;
        } else {
            is_negative = false;
        }
        if (num == 0) {
            digits.push_back(0);
        } else {
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
        }
    }

    BigInt(const string& s) {
        if (s.empty()) throw invalid_argument("Empty string");
        
        size_t start = 0;
        if (s[0] == '-') {
            is_negative = true;
            start = 1;
        } else {
            is_negative = false;
            if (s[0] == '+') start = 1;
        }

        digits.clear();
        for (int i = s.size()-1; i >= (int)start; --i) {
            if (!isdigit(s[i]))
                throw invalid_argument("Invalid character");
            digits.push_back(s[i] - '0');
        }
        remove_leading_zeros();
        if (digits.empty()) {
            digits.push_back(0);
            is_negative = false;
        }
    }

    int compare(const BigInt& other) const {
        if (is_negative != other.is_negative)
            return is_negative ? -1 : 1;
        
        int abs_comp = compare_abs(other);
        return is_negative ? -abs_comp : abs_comp;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        if (a.is_negative == b.is_negative) {
            BigInt res = a.add_abs(b);
            res.is_negative = a.is_negative;
            return res;
        } else {
            int cmp = a.compare_abs(b);
            if (cmp == 0) return BigInt(0);
            
            BigInt res;
            if (cmp > 0) {
                res = a.sub_abs(b);
                res.is_negative = a.is_negative;
            } else {
                res = b.sub_abs(a);
                res.is_negative = b.is_negative;
            }
            res.remove_leading_zeros();
            return res;
        }
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        BigInt neg_b = b;
        neg_b.is_negative = !neg_b.is_negative;
        return a + neg_b;
    }

    friend BigInt operator*(const BigInt& a, int b) {
        if (b == 0) return BigInt(0);
        
        BigInt result;
        result.digits.clear();
        long long abs_b = abs((long long)b);
        bool res_sign = a.is_negative != (b < 0);
        
        long long carry = 0;
        for (size_t i = 0; i < a.digits.size() || carry; ++i) {
            long long product = carry;
            if (i < a.digits.size())
                product += a.digits[i] * abs_b;
            carry = product / 10;
            result.digits.push_back(product % 10);
        }
        
        result.is_negative = res_sign;
        result.remove_leading_zeros();
        return result;
    }

    friend BigInt operator*(int b, const BigInt& a) {
        return a * b;
    }

    friend bool operator==(const BigInt& a, const BigInt& b) { return a.compare(b) == 0; }
    friend bool operator<(const BigInt& a, const BigInt& b)  { return a.compare(b) < 0; }
    friend bool operator>(const BigInt& a, const BigInt& b)  { return a.compare(b) > 0; }
    friend bool operator<=(const BigInt& a, const BigInt& b) { return a.compare(b) <= 0; }
    friend bool operator>=(const BigInt& a, const BigInt& b) { return a.compare(b) >= 0; }

    friend ostream& operator<<(ostream& os, const BigInt& num) {
        if (num.is_negative) os << '-';
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it)
            os << *it;
        return os;
    }
};

int main()
{
	BigInt a = 12345;
	BigInt b("-67890");
	BigInt c = a * 3;
	BigInt d = 5 * b;
	
	cout << a + b << a-b << endl;
	cout << (a > b) << endl;
	

//	cout<<a-b<<endl; 
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
}

