#include<iostream>
#include<json/json.h>
using namespace std;
//compile: g++ test.cpp -o test libjson_linux-gcc-5.4.0_libmt.a
int main(){
	Json::Value root;
	Json::FastWriter fast;
	root["DateTime"]=("23");
	root["name"]=("hello");
	root["class"]=("12");
	cout<<fast.write(root)<<endl;
	return 0;
}

//test the jsoncpp lib
