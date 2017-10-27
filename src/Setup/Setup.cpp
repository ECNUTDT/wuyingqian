#include "/usr/local/include/pbc/pbc.h"
#include "/usr/local/include/pbc/pbc_test.h"
#include<stdio.h>
#define N 10
#define M 10

int main(int argc, char **argv) {
	pairing_t pairing;
	element_t z,y;
	element_t v,g,g1,g2; //elements from G
	element_t temp;
	
	element_t A;
	
	pbc_demo_pairing_init(pairing,argc,argv); //read a.param file
	
	element_t arrN[N];
	element_t arrM[M];
	
	//init
	element_init_G1(v,pairing);
  element_init_Zr(y,pairing);
  element_init_Zr(z,pairing);
  element_init_G1(g,pairing);
  element_init_G1(g1,pairing);
  element_init_G1(g2,pairing);
  element_init_Zr(temp,pairing);
  element_init_GT(A,pairing);
  
  element_random(y);
  element_random(z);
  element_random(g);
  element_random(g2);
  
  element_pow_zn(g1, g, y);
  element_pow_zn(v, g, z);
  
	FILE *file1;
	file1=fopen("../../data/setup_data/mk","w");
	element_fprintf(file1,"{\"y\":\"%B\"}",y);
	fclose(file1);
  
  FILE *file2;
  file1=fopen("../../data/setup_data/pp","w");
  element_fprintf(file2,"{\n\"g1\":\"%B\",\n",g1);
  element_fprintf(file2,"\"g2\":\"%B\",\n",g2);
  
  for(int i=0;i<N;i++){
  	element_init_G1(arrN[i],pairing);
  	element_random(arrN[i]);
  	element_fprintf(file2,"\"t-%d\":\"%B\",\n",i+1,arrN[i]);
  }
  
  element_fprintf(file2,"\"v\":\"%B\",\n",v);
  for(int i=0;i<M;i++){
  	element_init_G1(arrM[i],pairing);
  	element_random(temp);
  	element_pow_zn(arrM[i],g,temp);
  	element_fprintf(file2,"\"v-%d\":\"%B\",\n",i+1,arrM[i]);
  }
  
  pairing_apply(A,g1,g2,pairing);
  element_fprintf(file2,"\"A\":\"%B\",\n}",A);
  fclose(file2);
  
  element_clear(A);
  element_clear(v);
  element_clear(y);
  element_clear(z);
  element_clear(temp);
  element_clear(g);
  element_clear(g1);
  element_clear(g2);
  //element_clear(pairing);
  return 0;
 
  
  
  
  
  
}
