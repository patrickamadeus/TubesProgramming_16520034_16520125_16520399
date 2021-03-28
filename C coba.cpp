#include<iostream>
#include<vector>
#include<stdlib.h> 
#include<time.h>
#include<algorithm>
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
	cout<<endl;
	for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
	
	cout<<endl;
	
	do{
		bool invalid = true;
		do{
			invalid = false;
			cout << "maju/mundur/kiri/kanan : ";
			cin >> comm;
			transform(comm.begin(), comm.end(), comm.begin(), ::tolower);
			if ((comm == "mundur" && (pos.y == 0 || field[15-pos.y+1][pos.x]!=0)) || (comm == "kiri" && (pos.x == 0 ||field[15-pos.y][pos.x-1]!=0)) || (comm=="maju" && (pos.y==15 ||field[15-pos.y-1][pos.x]!=0)) || (comm=="kanan" && (pos.x==15 || field[15-pos.y][pos.x+1]!=0) )){
				invalid = true;
				cout << "Invalid\n";
			}
		}
		while (invalid);
		field[15-pos.y][pos.x]=0;
		if (comm == "maju"){
			pos.y += 1;
		}
		else if (comm == "mundur"){
			pos.y -= 1;
		}
		else if (comm == "kiri"){
			pos.x -= 1;
		}
		else if (comm == "kanan"){
			pos.x += 1;
		}
		cout << pos.x << "," << pos.y << endl;
		field[15-pos.y][pos.x]=1;
		
		
		
		cout<<"POSISI SETELAH PERGERAKAN (robot anda adalah angka 1)"<<endl;
		cout<<endl;
		for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
		cout<<endl;
			
		//bagian cockroaches detector --> 4 kiri 4 kanan , 4 atas 4 bawah
		cout<<"COCKROACHES DETECTOR SECTION"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -"<<endl;
		cout<<"angka N menunjukkan jarak sebesar N satuan dari robot ke musuh"<<endl;
		int atas=15-pos.y-1, bawah = 15-pos.y+1, kanan = pos.x+1 ,kiri = pos.x-1 ,distAtas = 1, distBawah = 1 ,distKanan = 1 , distKiri = 1;
		
		//vertikal atas : sensor dapat mendeteksi ke bawah sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (atas>=0){
				if (field[atas][pos.x]!=0){
					break;
				}
				distAtas+=1;
				atas-=1;}
			else{
				distAtas=6;
				break;}
			}
		if (distAtas>4){
			distAtas=0;
		}
		
		
		//vertikal bawah : sensor dapat mendeteksi ke bawah sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (bawah<=15){
				if (field[bawah][pos.x]!=0){
					break;
				}
				distBawah+=1;
				bawah+=1;}
			else{
				distBawah=6;
				break;}
			}
		if (distBawah>4){
			distBawah=0;
		}
		
		//horizontal kanan : sensor dapat mendeteksi ke kanan sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (kanan<=15){
				if (field[15-pos.y][kanan]!=0){
					break;
				}
				distKanan+=1;
				kanan+=1;}
			else{
				distKanan=6;
				break;}
			}
		if (distKanan>4){
			distKanan=0;
		}
		
		//horizontal kiri : sensor dapat mendeteksi ke kiri sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (kiri>=0){
				if (field[15-pos.y][kiri]!=0){
					break;
				}
				distKiri+=1;
				kiri-=1;}
			else{
				distKiri=6;
				break;}
			}
		if (distKiri>4){
			distKiri=0;
		}
		
		//peta detector
		cout<<"       "<<distAtas<<endl;
		cout<<"       .\n       .\n       .\n       .\n";
		cout<<distKiri<<"----"<<"ROBOT"<<"----"<<distKanan<<endl;
		cout<<"       .\n       .\n       .\n       .\n";
		cout<<"       "<<distBawah<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -"<<endl;
		
	}
	
	while (alive);
	
	
	
}
