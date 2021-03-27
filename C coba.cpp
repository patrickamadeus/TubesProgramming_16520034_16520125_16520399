#include<iostream>
#include<vector>
#include <stdlib.h> 
#include<time.h>
using namespace std;

int main(){
	//ide awal, field 16 x 16
	srand(time(0));
	int field[16][16];
	int jmlKecoa=20;
	for (int i=0;i<16;i++){
		for (int j=0 ; j<16 ; j++){
			field[i][j]=0;
		}
	}

	while (jmlKecoa >0){
		int s1 = rand() % 16 , s2 = rand() % 16;
		if (field[s1][s2]==0){
			field[s1][s2]=500;
			jmlKecoa-=1;
		}
	}
	for(int i=0; i<16 ;i++){
		for(int j=0;j<16 ;j++){
			cout<< field[i][j]<<" ";
		}
		cout<<endl;
	}
}
