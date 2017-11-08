#include<iostream>
#include<json/json.h>
#include<fstream>
using namespace std;
int main(){
	Json::Value root;
	Json::Reader reader;
	ifstream ifs("MK");
	if(reader.parse(ifs,root)){
		cout<<root["y"].asString()<<endl;
	}
	return 0;
}
