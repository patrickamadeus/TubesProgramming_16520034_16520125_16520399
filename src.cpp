#include<iostream>
#include<stdlib.h> 
#include<time.h>
#include<algorithm>
using namespace std;

//class untuk koordinat
typedef struct{
	int x, y;
} Point;

int main(){
	
	// bagian initialitation battle field 
	srand(time(0));
	int n=7,killcount=0;
	int field[n][n];
	int jmlKecoa=1 , hpKecoa = 500, hpRobot = 1000, attKecoa = 50, attRobot = 79;
	for (int i=0;i<n;i++){
		for (int j=0 ; j<16 ; j++){
			field[i][j]=0;
		}
	}
	
	//pengisian kecoak secara random di spot tertentu field
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
		cout<<"			  JARAK ATAS:"<<distAtas<<"\n""\n";	
		cout<<"			     .===.    "<<endl;
		cout<<"			    //O O\\\\    "<<endl;
		cout<<"			    \\\\_#_//    "<<endl;
		cout<<"	 JARAK KIRI:"<<"	    ,=|x|=.    	"<<"    JARAK KANAN:"<<endl;
		cout<<"	     "<<distKiri<<"	 	    'c/_\\ 'c  	    	"<<distKanan<<endl;
		cout<<"			     [] []     "<<endl;
		cout<<"			    /:] [:\\     "<<endl;
		cout <<"\n\n		 	 JARAK BAWAH:"<<distBawah<<"\n";
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -"<<endl;
		
		
		// attack power
		cout << "Attack Power Kecoa : " << attKecoa << "          Attack Power Robot : " << attRobot << endl;
		 
		
		// command user
		bool invalid = true;
		do{
			invalid = false;
			cout <<"Maju/Mundur/Kiri/Kanan/Serang : ";
			cin>>comm;
			transform(comm.begin(), comm.end(), comm.begin(), ::tolower);
			
			//diminta input apabila masukan tidak sesuai dengan command program
			while (comm!="maju" and comm!="mundur" and comm!="kiri" and comm!="kanan" and comm!="serang"){
				cout<<"Masukkan command yang benar (maju/mundur/kiri/kanan/serang)!! : ";	
			   cin>>comm;
			   transform(comm.begin(), comm.end(), comm.begin(), ::tolower);
			   }
			   
			   
			//bagian conditional gerak robot , memastikan tidak ada pergerakan yang invalid
			if ((comm=="mundur" && (pos.y==0 || field[n-1-pos.y+1][pos.x]!=0)) || (comm=="kiri" && (pos.x==0 ||field[n-1-pos.y][pos.x-1]!=0)) || (comm=="maju" && (pos.y==n-1 ||field[n-1-pos.y-1][pos.x]!=0)) || (comm=="kanan" && (pos.x==n-1 || field[n-1-pos.y][pos.x+1]!=0) )){
				invalid = true;
				cout << "Invalid\n";
			}
			if (comm == "serang" && distAtas == 0 && distBawah == 0 && distKanan == 0 && distKiri == 0){
				invalid = true;
				cout << "Kecoak di luar jangkauan\n";
			}
			if (comm == "quit"){
				alive = false;
			}
		}
		while (invalid);
		
		//bagian gerak dinamik
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
		else if (comm == "serang"){
			
			//algoritma attack robot terhadap kecoak
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
		cout << "Koordinat Posisi = (" << pos.x << "," << pos.y << ")" << endl;
		field[n-1-pos.y][pos.x]=1;
		
		
		// Deteksi kecoa pada radius 1 dari robot 
		int kib, ki, kia, a, kaa, ka, kab, b;
		kib = field[n-1-pos.y+1][pos.x-1];  // kiri bawah
		ki  = field[n-1-pos.y  ][pos.x-1];  // kiri
		kia = field[n-1-pos.y-1][pos.x-1];  // kiri atas
		a   = field[n-1-pos.y-1][pos.x  ];  // atas
		kaa = field[n-1-pos.y-1][pos.x+1];  // kanan atas
		ka  = field[n-1-pos.y  ][pos.x+1];  // kanan
		kab = field[n-1-pos.y+1][pos.x+1];  // kanan bawah
		b   = field[n-1-pos.y+1][pos.x  ];  // bawah
		
		
		//algoritma penyerangan kecoak terhadap robot
		if (pos.x == 0 && pos.y == 0 && (a !=0 || kaa !=0 || ka !=0)){
			hpRobot -= attKecoa;  // robot di pojok kiri bawah
		}
		else if (pos.x == 0 && pos.y == n-1 && (ka !=0 || kab !=0 || b !=0)){
			hpRobot -= attKecoa;  // robot di pojok kiri atas
		}
		else if (pos.x == n-1 && pos.y == n-1 && (ki !=0 || kib !=0 || b !=0)){
			hpRobot -= attKecoa;  // robot di pojok kanan atas
		}
		else if (pos.x == n-1 && pos.y == 0 && (ki !=0 || kia !=0 || a !=0)){
			hpRobot -= attKecoa;  // robot di pojok kanan bawah
		} 
		else if (pos.x == 0 && pos.y != 0 && pos.y != n-1 && (a !=0 || kaa !=0 || ka !=0 || kab !=0 || b !=0)){
			hpRobot -= attKecoa;  // robot di sepanjang dinding kiri
		}
		else if (pos.y == 0 && pos.x != 0 && pos.x != n-1 && (ki !=0 || kia !=0 || a !=0 || kaa !=0 || ka !=0)){
			hpRobot -= attKecoa;  // robot di sepanjang dinding bawah
		}
		else if (pos.x == n-1 && pos.y != 0 && pos.y != n-1 && (a !=0 || kia !=0 || ki !=0 || kib !=0 || b !=0)){
			hpRobot -= attKecoa;  // robot di sepanjang dinding kanan
		} 
		else if (pos.y == n-1 && pos.x != 0 && pos.x != n-1 && (ki !=0 || kib !=0 || b !=0 || kab !=0 || ka !=0)){
			hpRobot -= attKecoa;  // robot di sepanjang dinding atas
		}
		else if (pos.x != 0 && pos.x != n-1 && pos.y != 0 && pos.y != n-1 && (kib !=0 || ki !=0 || kia !=0 || a !=0 || kaa !=0 || ka !=0 || kab !=0 || b !=0)){
			hpRobot -= attKecoa;  // robot di tengah
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
		cout << "Health Robot: " << hpRobot << endl;
		if (hpRobot <=0){
			cout<<endl;
			cout<<"!! GAME OVER !!"<<endl;
			cout<<"Jumlah kecoa yang berhasil dibunuh: "<<killcount;
			break;
		}
		
		//spawn baru apabila kecoak mati
		bool kecoaMati=false;
		for (int i=0; i<n ;i++){
			for (int j=0 ; j<n ;j++){
				if (field[i][j]<0){
					field[i][j]=0;
					killcount+=1;
					cout<<"_.~~._.~~._.-~"<<"CONGRATZ, YOU HAVE CLEARED STAGE "<<killcount<<" !"<<"~._.-~~._.-~~._"<<endl;
					jmlKecoa+=1;
					hpKecoa+=100;
					kecoaMati=true;
					break;
				}
			}
		}
		
		//bagian spawn baru
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
