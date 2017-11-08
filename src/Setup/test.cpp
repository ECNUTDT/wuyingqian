#include<iostream>
#include<json/json.h>
using namespace std;
int main(){
	Json::Value root;
	Json::FastWriter fast;
	root["DateTime"]=("23");
	root["name"]=("hello");
	root["class"]=("12");
	cout<<fast.write(root)<<endl;
	return 0;
}
