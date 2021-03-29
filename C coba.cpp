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
	//ide awal, field n x n , robot bisa nembak
	
	// bagian initialitation battle field 
	srand(time(0));
	int n=7,killcount=0;
	int field[n][n];
	int jmlKecoa=1 , hpKecoa = 500, hpRobot = 1000, attKecoa = 50, attRobot = 25;
	for (int i=0;i<n;i++){
		for (int j=0 ; j<16 ; j++){
			field[i][j]=0;
		}
	}
	
	
	//random spawn awal kecoak
	while (jmlKecoa >0){
		int s1 = rand() % n , s2 = rand() % n;
		if (s1!=n-1 and s2!=0){ // kondisi dimana di titik awal jangan langsung muncul kecoak
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
	field[n-1-pos.y][pos.x]=1;
	string comm;
	bool alive = true;
	
	
	//peta awal
	cout<<"!!  POSISI AWAL  !!"<<endl;
	cout<<endl;
	for(int i=0; i<n ;i++){
			for(int j=0;j<n ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
	
	cout<<endl;
	
	// Health awal robot
	cout << "Health Robot : " << hpRobot << endl;
	
	do{
		//bagian cockroaches detector --> 4 kiri 4 kanan , 4 atas 4 bawah
		cout<<"COCKROACHES DETECTOR SECTION"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -"<<endl;
		cout<<"angka N menunjukkan jarak sebesar N satuan dari robot ke musuh"<<endl;
		int atas=n-1-pos.y-1, bawah = n-1-pos.y+1, kanan = pos.x+1 ,kiri = pos.x-1 ,distAtas = 1, distBawah = 1 ,distKanan = 1 , distKiri = 1;
		
		//vertikal atas : sensor dapat mendeteksi ke bawah sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (atas>=0){
				if (field[atas][pos.x]!=0){
					break;
				}
				distAtas+=1;
				atas-=1;}
			else{
				distAtas=9999;
				break;}
			}
		if (distAtas>4){
			distAtas=0;
		}
		
		//vertikal bawah : sensor dapat mendeteksi ke bawah sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (bawah<=n-1){
				if (field[bawah][pos.x]!=0){
					break;
				}
				distBawah+=1;
				bawah+=1;}
			else{
				distBawah=9999;
				break;}
			}
		if (distBawah>4){
			distBawah=0;
		}
		
		//horizontal kanan : sensor dapat mendeteksi ke kanan sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (kanan<=n-1){
				if (field[n-1-pos.y][kanan]!=0){
					break;
				}
				distKanan+=1;
				kanan+=1;}
			else{
				distKanan=9999;
				break;}
			}
		if (distKanan>4){
			distKanan=0;
		}
		
		//horizontal kiri : sensor dapat mendeteksi ke kiri sejauh 4 blocks dari titik robot berada
		for (int i=0;i<4;i++){
			if (kiri>=0){
				if (field[n-1-pos.y][kiri]!=0){
					break;
				}
				distKiri+=1;
				kiri-=1;}
			else{
				distKiri=9999;
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
		
		
		// attack power
		cout << "Attack Power Kecoa : " << attKecoa << "          Attack Power Robot : " << attRobot << endl;
		 
		
		// command user
		bool invalid = true;
		do{
			invalid = false;
			cout << "maju/mundur/kiri/kanan/serang : ";
			cin >> comm;
			transform(comm.begin(), comm.end(), comm.begin(), ::tolower);
			if ((comm == "mundur" && (pos.y == 0 || field[n-1-pos.y+1][pos.x]!=0)) || (comm == "kiri" && (pos.x == 0 ||field[n-1-pos.y][pos.x-1]!=0)) || (comm=="maju" && (pos.y==n-1 ||field[n-1-pos.y-1][pos.x]!=0)) || (comm=="kanan" && (pos.x==n-1 || field[n-1-pos.y][pos.x+1]!=0) )){
				invalid = true;
				cout << "Invalid\n";
			}
			if (comm == "serang" && distAtas == 0 && distBawah == 0 && distKanan == 0 && distKiri == 0){
				invalid = true;
				cout << "Kecoa di luar jangkauan\n";
			}
		}
		while (invalid);
		
		
		//movement robot 
		field[n-1-pos.y][pos.x]=0;
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
		else{ //attack robot
			if (distAtas != 0){
				if (distAtas == 1){
					field[n-1-pos.y-distAtas][pos.x] -= attRobot;
				}
				else{
					field[n-1-pos.y-distAtas+1][pos.x] = field[n-1-pos.y-distAtas][pos.x] - attRobot;
					field[n-1-pos.y-distAtas][pos.x] = 0;
				}
			} 
			else if (distBawah != 0){
				if (distBawah == 1){
					field[n-1-pos.y+distBawah][pos.x] -= attRobot;
				}
				else{
					field[n-1-pos.y+distBawah-1][pos.x] = field[n-1-pos.y+distBawah][pos.x] - attRobot;
					field[n-1-pos.y+distBawah][pos.x] = 0;
				}
			}
			else if (distKiri != 0){
				if (distKiri == 1){
					field[n-1-pos.y][pos.x-distKiri] -= attRobot;
				}
				else{
					field[n-1-pos.y][pos.x-distKiri+1] = field[n-1-pos.y][pos.x-distKiri] - attRobot;
					field[n-1-pos.y][pos.x-distKiri] = 0;
				}
			}
			else if (distKanan != 0){
				if (distKanan == 1){
					field[n-1-pos.y][pos.x+distKanan] -= attRobot;
				}
				else{
					field[n-1-pos.y][pos.x+distKanan-1] = field[n-1-pos.y][pos.x+distKanan] - attRobot;
					field[n-1-pos.y][pos.x+distKanan] = 0;
				}
			}
		}
		cout << pos.x << "," << pos.y << endl;
		field[n-1-pos.y][pos.x]=1;
		
		
		// Deteksi kecoa pada radius 1 dari robot + attack kecoak
		if (pos.x == 0 && pos.y == 0 && (field[15-pos.y-1][pos.x] >1 || field[n-1-pos.y-1][pos.x+1] >1 || field[n-1-pos.y][pos.x+1] >1)){
			hpRobot -= attKecoa;
		}
		else if (pos.x == 0 && pos.y != 0 && (field[n-1-pos.y-1][pos.x] >1 || field[n-1-pos.y-1][pos.x+1] >1 || field[n-1-pos.y][pos.x+1] >1 || field[n-1-pos.y+1][pos.x+1] >1 || field[n-1-pos.y+1][pos.x] >1)){
			hpRobot -= attKecoa;	
		}
		else if (pos.y == 0 && pos.x != 0 && (field[n-1-pos.y-1][pos.x] >1 || field[n-1-pos.y-1][pos.x+1] >1 || field[n-1-pos.y][pos.x+1] >1 || field[n-1-pos.y-1][pos.x-1] >1 || field[n-1-pos.y][pos.x-1] >1)){
			hpRobot -= attKecoa;
		}
		else if (field[n-1-pos.y-1][pos.x] >1 || field[n-1-pos.y-1][pos.x+1] >1 || field[n-1-pos.y][pos.x+1] >1 || field[n-1-pos.y+1][pos.x+1] >1 || field[n-1-pos.y+1][pos.x] >1 || field[n-1-pos.y-1][pos.x-1] >1 || field[n-1-pos.y][pos.x-1] >1){
			hpRobot -= attKecoa;
		}
		
		
		// Peta setelah pergerakan
		cout<<"POSISI SETELAH PERGERAKAN (robot anda adalah angka 1)"<<endl;
		cout<<endl;
		for(int i=0; i<n ;i++){
			for(int j=0;j<n ;j++){
				cout<< field[i][j]<<" ";
			}
			cout<<endl;}
		cout<<endl;
			
			
		// Status Robot
		cout << "Health : " << hpRobot << endl;
		if (hpRobot <=0){
			cout<<endl;
			cout<<"!! GAME OVER !!"<<endl;
			cout<<"Jumlah kecoa yang berhasil dibunuh: "<<killcount;
			break;
		}
		
		//spawn baru
		bool kecoaMati=false;
		for (int i=0; i<n ;i++){
			for (int j=0 ; j<n ;j++){
				if (field[i][j]<0){
					field[i][j]=0;
					killcount+=1;
					jmlKecoa+=1;
					hpKecoa+=100;
					kecoaMati=true;
					break;
				}
			}
		}
		if (kecoaMati){
			while (jmlKecoa >0){
				int s1 = rand() % n , s2 = rand() % n;
				if (s1!=pos.y and s2!=pos.x){ // kondisi dimana di titik robot jangan muncul kecoak
					if (field[s1][s2]==0){
						field[s1][s2]=hpKecoa;
						jmlKecoa-=1;
					}
				}		
			}
		}
	}
	while (alive);
}
