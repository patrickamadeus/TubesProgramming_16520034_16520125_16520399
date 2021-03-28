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
	for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
	
	
	
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
		for(int i=0; i<16 ;i++){
			for(int j=0;j<16 ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
			
		//bagian cockroaches detector --> 4 kiri 4 kanan , 4 atas 4 bawah
		//atas
		int atas=15-pos.y-1 ,distAtas = 1;
		for (int i=0;i<4;i++){
			if (atas>=0){
				if (field[atas][pos.x]!=0){
					cout<<"Terdeteksi Kecoak pada jarak vertikal ke atas "<<distAtas <<" satuan dari robot!"<<endl;
					distAtas=0;
					break;
				}
				distAtas+=1;
				atas-=1;}
			else{
				distAtas=6;
				break;}
			}
		if (distAtas>4){
			cout<<"Tidak terdeteksi Kecoak di jarak 4 vertikal ke atas dari posisi robot"<< endl;;
		}
	}
	
	while (alive);
	
	
	
}
