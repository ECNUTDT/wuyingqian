#include<iostream>
#include<json/json.h>
#include<fstream>
#include<string>
#include<sstream>
#define N 20
#define M 20
using namespace std;
//compile : g++ Extract.cpp -o extract libjson_linux-gcc-5.4.0_libmt.a

void restoreVariables();

int main(){
	restoreVariables();
	return 0;
}

// MK PP path: ../../data/setup_data/MK
void restoreVariables(){
	int i;
	string g1s,g2s,vls,ys;
	string ts[N+1];
	string vs[M];
	string As;
	Json::Value root;
	Json::Reader reader;
	string s1,s2;
	ostringstream oss;
	// restore v from PP 
	ifstream ifs("../../data/setup_data/PP");
	if(reader.parse(ifs,root)){
		g1s=root["g1"].asString();
		g2s=root["g2"].asString();
		//cout<<"g1:"<<g1s<<endl;
		//cout<<"g2:"<<g2s<<endl;
		
		s1="t-";
		for(i=1;i<=N+1;i++){
			oss<<s1<<i;
			s2=oss.str();
			oss.str("");
			ts[i-1]=root[s2].asString();
			//cout<<s2<<":"<<ts[i-1]<<endl;
		}

		vls=root["v'"].asString();
		//cout<<"v':"<<vls<<endl;

		s1="v-";
		for(i=1;i<=M;i++){
			oss<<s1<<i;
			s2=oss.str();
			oss.str("");
			vs[i-1]=root[s2].asString();
			//cout<<s2<<":"<<vs[i-1]<<endl;
		}

		As=root["A"].asString();
		//cout<<"A:"<<As<<endl;
	}
	ifs.close();

	// restore v from MK
	ifs.open("../../data/setup_data/MK");
	if(reader.parse(ifs,root)){
		ys=root["y"].asString();
		//cout<<"y:"<<ys<<endl;
	}
	ifs.close();

	

}