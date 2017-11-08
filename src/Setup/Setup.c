#include "/usr/local/include/pbc/pbc.h"
#include "/usr/local/include/pbc/pbc_test.h"
#include<stdio.h>
#define N 20
#define M 20

/*
compile   gcc -o setup Setup.c -L. -lpbc -lgmp
execute   ./setup < ../../data/param/a.param
*/

int main(int argc,char **argv){
	pairing_t pairing;
	int i;
	//G1
	element_t g,g1,g2,vl,t[N+1],v[M];
	//Zr
	element_t zl,z[M],y;
	//GT
	element_t A;
	
	//init pairing
	pbc_demo_pairing_init(pairing,argc,argv);
	
	//init variables of G1
	element_init_G1(g,pairing);
	element_init_G1(g1,pairing);
	element_init_G1(g2,pairing);
	element_init_G1(vl,pairing);
	for(i=0;i<=N;i++){
		element_init_G1(t[i],pairing);
	}
	for(i=0;i<M;i++){
		element_init_G1(v[i],pairing);
	}
	
	//init variables of Zr
	element_init_Zr(zl,pairing);
	element_init_Zr(y,pairing);
	for(i=0;i<M;i++){
		element_init_Zr(z[i],pairing);
	}
	
	//init variables of GT
	element_init_GT(A,pairing);
	
	//set random value for g2,t[N+1],g,zl,z[M],y
	element_random(g2);
	for(i=0;i<=N;i++)
		element_random(t[i]);
	element_random(vl);
	element_random(g);
	element_random(zl);
	for(i=0;i<M;i++)
		element_random(z[i]);
	element_random(y);
	
	//calculate g1  vl  v[M]  A
	element_pow_zn(g1,g,y);
	element_pow_zn(vl,g,zl);
	for(i=0;i<M;i++)
		element_pow_zn(v[i],g,z[i]);
	pairing_apply(A,g1,g2,pairing);
	
	// write y to MK file
	FILE *mk;
	mk=fopen("../../data/setup_data/MK","w+");
	element_fprintf(mk,"{\"y\":\"%B\"}",y);
	fclose(mk);
	
	// write values to PP file
	FILE *pp;
	pp=fopen("../../data/setup_data/PP","w+");
	element_fprintf(pp,"{\n\"g1\":\"%B\",\n",g1);
	element_fprintf(pp,"\"g2\":\"%B\",\n",g2);
	for(i=0;i<=N;i++)
		element_fprintf(pp,"\"t-%d\":\"%B\",\n",i+1,t[i]);
	element_fprintf(pp,"\"v'\":\"%B\",\n",vl);
	for(i=0;i<M;i++)
		element_fprintf(pp,"\"v-%d\":\"%B\",\n",i+1,v[i]);
	element_fprintf(pp,"\"A\":\"%B\"\n}",A);
	fclose(pp);
	
	
	element_clear(g1);
	element_clear(g2);
	for(i=0;i<=N;i++)
		element_clear(t[i]);
	element_clear(vl);
	element_clear(g);
	for(i=0;i>M;i++){
		element_clear(v[i]);
		element_clear(z[i]);
	}
	element_clear(zl);
	element_clear(y);
	pairing_clear(pairing);
	
	
	return 0;
}
