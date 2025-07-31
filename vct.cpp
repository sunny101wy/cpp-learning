//#include<fstream>
//#include<vector>
//#include<algorithm>
//#include<iostream>
//int main(){
//	std::ifstream inf("input2.txt");
//	if(!inf){
//		std::cout<<"failed to open file"<<std::endl;
//		return -1;
//	}
//	std::vector<int>data;
//	
//	int num;
//	while(inf>>num){
//		data.push_back(num);
//	}
//	
//	std::sort(data.begin(),data.end());
//	auto last=std::unique(data.begin(),data.end());
//	data.erase(last,data.end());
//	
//	for(auto&temp:data){
//		temp*=2;
//	}
//	
//	std::reverse(data.begin(),data.end());
//	std::ofstream outf("output.txt");
//	if(!outf){
//		std::cout<<"failed to open file"<<std::endl;
//		return -1;
//	}
//	for(const auto&number:data){
//		std::cout<<number<<" ";
//		outf<<number<<" ";
//	}
//	return 0;
//}
//#include<fstream>
//#include<string>
//#include<algorithm>
//#include<iostream>
//#include<cctype> 
//int main(){
//	std::ifstream inf("input2.txt");
//	if(!inf){
//		std::cout<<"error!!"<<std::endl;
//		return -1;
//	}
//	std::string line;
//	std::getline(inf,line);
//	inf.close();
//	
//	size_t length = line.length();
//	size_t word_counts=std::count_if(line.begin(),line.end(),[](char c){ return ::isspace(c);})+1;
//	std::cout<<word_counts<<std::endl; 
//	
//	std::transform(line.begin(),line.end(),line.begin(),::toupper);
//	std::cout<<line<<std::endl;
//
//	auto last=std::remove_if(line.begin(),line.end(),[](char c){return ::isdigit(c);});
//	line.erase(last,line.end());
//	std::cout<<line<<std::endl;
//	
//	size_t pos=line.find("ERROR");
//	if(pos!=std::string::npos){
//		line.replace(pos,5,"WARNNING");
//	}
//	
//	std::ofstream outf("output.txt");
//	if(!outf){
//		std::cout<<"error!!"<<std::endl;
//		return -1;
//	}
//	outf<<line<<std::endl;
//	outf.close();
//}
//
#include	<iostream>
#include	<fstream>
#include	<map>
#include	<set>
#include	<deque>
#include	<list>
#include	<vector>
#include	<string>
#include	<algorithm>
#include	<numeric>
#include	<iomanip>

struct Student{
	std::string name;
	std::list<int>	score;
};
int calculate(const std::list<int>&score){
	return std::accumulate(score.begin(),score.end(),0);
}
double calculateAverage(const std::list<int>&score){
	return static_cast<double>(calculate(score)/score.size());
}
int main(){
	std::ifstream inf("input2.txt");
	if(!inf){
		std::cout<<"failed to open file"<<std::endl;
		return -1;
	}
	std::map<int,Student>	studentData;
	std::deque<int>	recent;
	std::set<double>	average;
	
	int id,chinese,math,english;
	std::string name;
	while(inf>>id>>name>>chinese>>math>>english){
		Student student;
		student.name=name;
		student.score={chinese,math,english};
		studentData[id]=student;
	}
	inf.close();
	
	int queryId = 1;
	if(studentData.find(queryId)!=studentData.end()){
		const Student& student=studentData[queryId];
		std::cout<<"ID"<<queryId<<"was found"<<std::endl;
		std::cout<<"Name:"<<student.name<<std::endl;
		std::cout<<"Score:"<<std::endl;
		for(int score:student.score){
			std::cout<<score<<" ";
		}
		std::cout<<std::endl;
		recent.push_back(queryId);
		if(recent.size()>5){
			recent.pop_front();
		}
	}
	else{
		std::cout<<"The ID"<<queryId<<"does not exist"<<std::endl;
	}
	std::vector<int>subjectTotal(3,0.0);
	for(const auto& pair :studentData)
	{
		auto it = pair.second.score.begin();  
		for(int i=0;i<3&&it!=pair.second.score.end();i++,it++){
			subjectTotal[i] += *it;
		}
	}
	std::cout<<subjectTotal[0]<<subjectTotal[1]<<subjectTotal[2];
	for(int i=0;i<3;i++){
		average.insert(static_cast<double>(subjectTotal[i])/3);
	}
	int index=0;
	for(double avg:average){
		std::cout<<"Subject "<<index++<<"average:"<<avg<<std::endl;
	}
	std::ofstream outf("output2.txt");
	if(!outf){
		std::cout<<"failed to open file"<<std::endl;
		return -1;
	}
	for(const auto & pair :studentData){
        outf << pair.first << " " << pair.second.name << " ";
        for (int score : pair.second.score) {
            outf << score << " ";
        }
        outf<< "Total: " << calculate(pair.second.score) << "\n";	
	}
	outf.close(); 
} 
