#include "/usr/local/include/pbc/pbc.h"
#include "/usr/local/include/pbc/pbc_test.h"
#include<stdio.h>
#include<malloc.h>


// x=e (P,Q)^ab  y=e (aP,bQ)   x==y?
/*
G1: P temp1
G2: Q temp2
Zr: a,b,c
GT: x y
in x=e (P,Q)^ab   c=ab:element_mul(c,a,b)  X'=e(P,Q):pairing(x,P,Q,pairing)  x=X'^ab:  element_pow_zn(x,X',c)
in y=e (aP,bQ)   temp1=aP:  element_pow_zn(temp1,P,a)	 temp2=bQ  y=pairing_apply(y,temp1,temp2,pairing);
*/


/*
compile   gcc -o a a.c -L. -lpbc -lgmp
execute   ./a < ../../data/param/a.paaram
*/

int main(int argc,char **argv){
	pairing_t pairing; //
	//G1  P temp1   
	//G2  Q temp2
	//Z_r a b c
	//GT  x y
	element_t P,Q,a,b,c,x,y,temp1,temp2;
	
	pbc_demo_pairing_init(pairing,argc,argv);
	
	element_init_G1(P,pairing);
	element_init_G1(temp1,pairing);
	
	element_init_G2(Q,pairing);
	element_init_G2(temp2,pairing);
	
	element_init_GT(x,pairing);
	element_init_GT(y,pairing);
	
	element_init_Zr(a,pairing);
	element_init_Zr(b,pairing);
	element_init_Zr(c,pairing);
	
	element_random(P);
	element_random(Q);
	element_random(a);
	element_random(b);
	
	element_mul(c,b,a);
	
	pairing_apply(x,P,Q,pairing);
	element_pow_zn(x,x,c);
	
	element_pow_zn(temp1,P,a);
	element_pow_zn(temp2,Q,b);
	pairing_apply(y,temp1,temp2,pairing);
	
	if(!element_cmp(x,y))
		printf("x is equal to y\n");
	else
		printf("x is not equal to y\n");
	
	element_clear(P);
	element_clear(Q);
	element_clear(a);
	element_clear(b);
	element_clear(c);
	element_clear(temp1);
	element_clear(temp2);
	pairing_clear(pairing);
	return 0;
}
