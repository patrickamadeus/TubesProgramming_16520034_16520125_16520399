#include<iostream>
#include<vector>
#include<stdlib.h> 
#include<time.h>
using namespace std;

typedef struct{
	int x, y;
} Point;

int main(){
	//ide awal, field 16 x 16 , robot bisa nembak
	
	// bagian initialitation battle field 
	srand(time(0));
	int field[16][16];
	int jmlKecoa=20 , hpKecoa = 500;
	for (int i=0;i<16;i++){
		for (int j=0 ; j<16 ; j++){
			field[i][j]=0;
		}
	}

	while (jmlKecoa >0){
		int s1 = rand() % 16 , s2 = rand() % 16;
		if (s1!=15 and s2!=0){ // kondisi dimana di titik awal jangan langsung muncul kecoak
			if (field[s1][s2]==0){
				field[s1][s2]=hpKecoa;
				jmlKecoa-=1;
				}
		}
	}
	
	//bagian pergerakan 
	Point pos;
	pos.x = 0;
	pos.y = 0;
	field[15-pos.y][pos.x]=1;
	string comm;
	bool alive = true;
	
	
	//peta awal
	cout<<"!!  POSISI AWAL  !!"<<endl;
	for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
	
	
	//program utama
	do{
		bool invalid = true;
		do{
			invalid = false;
			cout << "Maju/Mundur/Kiri/Kanan: ";
			cin >> comm;
			if ((comm == "Mundur" && pos.y == 0) || (comm == "Kiri" && pos.x == 0)){
				invalid = true;
				cout << "Invalid\n";
			}
		}
		while (invalid);
		field[15-pos.y][pos.x]=0;
		if (comm == "Maju"){
			pos.y += 1;
		}
		else if (comm == "Mundur"){
			pos.y -= 1;
		}
		else if (comm == "Kiri"){
			pos.x -= 1;
		}
		else if (comm == "Kanan"){
			pos.x += 1;
		}
		cout << pos.x << "," << pos.y << endl;
		field[15-pos.y][pos.x]=1;
		
		cout<<"POSISI SETELAH PERGERAKAN (robot anda adalah angka 1)"<<endl;
		for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
	}
	while (alive);
	
	
	
}
