#include	<iostream> 
#include	<vector>
#include	<algorithm>
using namespace std;

//struct Carpet{
//	int x,y;
//	int w,h;
//};

int main(){
	vector<int>apple;
	int th=0;
	for(int i=0;i<10;i++){
		int h=0;
		cin>>h;
		apple.push_back(h);
	}
	cin>>th;
	int count=0;
	for(auto e:apple){
		if(th+30>=e){
			count++;
		}
	}
	cout<<count;
//	int n;
//	vector<int>nums;
//	cin>>n;
//	for(int i=0;i<n;i++){
//		int num;
//		cin>>num;
//		nums.push_back(num);
//	}
//	sort(nums.begin(),nums.end());
//	auto last=unique(nums.begin(),nums.end());
//	nums.erase(last,nums.end());
//	
//	cout<<nums.size()<<endl;
//	for(auto e:nums){
//		cout<<e<<' ';
//	}
//	int n;
//	int tx,ty;
//	cin>>n;
//	vector<Carpet>cpts;
//	for (int i=0;i<n;i++){
//		int x,y,w,h;
//		cin>>x>>y>>w>>h;
//		cpts.push_back({x,y,w,h});
//	}
//	cin>>tx>>ty;
//	int res = -1;
//	for(int i=n-1;i>=0;i--){
//		Carpet ct=cpts[i];
//		int x=ct.x;
//		int y=ct.y;
//		int w=ct.w;
//		int h=ct.h;
//		if(tx>=x&&tx<=x+w&&ty>=y&&ty<=y+h){
//			res = i+1;
//			break;
//		}
//	}
//	cout<<res;
	
	return 0;
}
