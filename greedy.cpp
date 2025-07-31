#include	<iostream>
#include	<sstream>
#include	<vector>
#include	<cctype>
#include	<algorithm>
#include	<string>
using namespace std;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    	vector<vector<int>>result;
        sort(people.begin(),people.end(),[](const vector<int>&a,const vector<int>&b){
        	if(a[0]!=b[0]){
        		return a[0]>b[0];
			}
			return a[1]<b[1];
		});
        for(auto e:people){
        	result.insert(result.begin()+e[1],e);
		}
        return result;
    }
};


int greedy(vector<vector<int>>&arr){
	if(arr.empty())
		return 0;
	int count=1;
	sort(arr.begin(),arr.end(),[](const vector<int>&a,const vector<int>&b){
		return a[1]<b[1];
	});
	int preEnd=arr[0][1];
	for(int i=1;i<arr.size();i++){
		if(arr[i][0]>=preEnd){
			count++;
			preEnd=arr[i][1];
		}
	};

	return arr.size()-count;
} 
int main()
{
	string input;
	string subinput;
	string cleaninput;
	getline(cin,input);
	
	size_t pos=input.find('=')+1;
	subinput=input.substr(pos);
	
	for(size_t i=0;i<subinput.size();i++){
		if(isdigit(subinput[i])){
			cleaninput.push_back(subinput[i]);
		}
		else{
			cleaninput.push_back(' ');
		}
	}
	
	int num;
	vector<int>nums;
	stringstream ss(cleaninput);
	while(ss>>num){
		nums.push_back(num);
	}
	for(auto nu:nums){
		cout<<nu<<' ';
	}
	cout<<endl;
	vector<vector<int>>last(nums.size()/2,vector<int>(2,0));
	for(int i=0;i<last.size();i++){
		last[i][0]=nums[i*2];
		last[i][1]=nums[i*2+1];
	}
		
	for(auto e:last){
		cout<<'['<<e[0]<<','<<e[1]<<']'<<' '; 
	}
	int res=greedy(last);
	cout<<res;
	return 0;	
}

