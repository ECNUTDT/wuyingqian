#include <iostream>
#include <json/json.h>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include "../mn.h"
#include "/usr/local/include/pbc/pbc.h"
#include "/usr/local/include/pbc/pbc_test.h"
using namespace std;

/**
compile : 
			g++ -o extract Extract.cpp -L. -lpbc -lgmp -ljson
execute   ./extract < ../../data/param/a.param
*/
	pairing_t pairing;
	//G1
	element_t g1,g2,vl,t[N+1],v[M];
	//GT
	element_t A;
	//Zr
	element_t y;

void restoreVariables();
string readFile(string path);
unsigned char* stringToChar(string str);
void initVariables();
void clearVariables();

// 

int main(int argc,char **argv){
	//init pairing

	pbc_demo_pairing_init(pairing,argc,argv);

	initVariables();
	restoreVariables();
	clearVariables();

	pairing_clear(pairing);
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
	//ifstream ifs("../../data/setup_data/PP");
	ifstream ifs;
	string PP=readFile("../../data/setup_data/PP");
	if(reader.parse(PP,root)){
		g1s=root["g1"].asString();
		g2s=root["g2"].asString();
		element_from_bytes_compressed(g1,stringToChar(g1s));
		element_from_bytes_compressed(g2,stringToChar(g2s));
		//element_printf("%B\n",g1);

		
		s1="t-";
		for(i=1;i<=N+1;i++){
			oss<<s1<<i;
			s2=oss.str();
			oss.str("");
			ts[i-1]=root[s2].asString();
			element_from_bytes_compressed(t[i-1],stringToChar(ts[i-1]));
		}

		vls=root["v'"].asString();
		element_from_bytes_compressed(vl,stringToChar(vls));

		s1="v-";
		for(i=1;i<=M;i++){
			oss<<s1<<i;
			s2=oss.str();
			oss.str("");
			vs[i-1]=root[s2].asString();
			element_from_bytes_compressed(v[i-1],stringToChar(vs[i-1]));
		}

		As=root["A"].asString();
		element_from_bytes(A,stringToChar(As));
		element_printf("%B\n",A);
	}
	//ifs.close();

	// restore v from MK
	ifs.open("../../data/setup_data/MK");
	if(reader.parse(ifs,root)){
		ys=root["y"].asString();

		mpz_t gmp_y;
		const char* chargmp_y = ys.c_str();
		mpz_init_set_str(gmp_y,chargmp_y,10);
		element_set_mpz(y,gmp_y);
	}
	ifs.close();

	
}



string readFile(string path){
	stringstream ss;
	fstream file(path.c_str());
	ss<<file.rdbuf();
	string data=ss.str();
	ss.clear();
	ss.str("");
	file.close();
	return data;
}

unsigned char* stringToChar(string str){
	char *p;
	int length=str.length();
	p=new char[length+1];
	strcpy(p,str.c_str());
	unsigned char* uc=(unsigned char*)p;
	return uc;
}

void initVariables(){
	int i;
	//init variables of G1
	element_init_G1(g1,pairing);
	element_init_G1(g2,pairing);
	element_init_G1(vl,pairing);
	for(i=0;i<=N;i++){
		element_init_G1(t[i],pairing);
	}
	for(i=0;i<M;i++){
		element_init_G1(v[i],pairing);
	}
	//init variables of GT
	element_init_GT(A,pairing);
	//init variables of Zr
	element_init_Zr(y,pairing);
}

void clearVariables(){
	int i;

	element_clear(g1);
	element_clear(g2);
	for(i=0;i<=N;i++)
		element_clear(t[i]);
	element_clear(vl);
	for(i=0;i>M;i++){
		element_clear(v[i]);
	}
	element_clear(y);
}