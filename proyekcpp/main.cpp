#include<iostream>
#include "display.h"
using namespace std;
int main(){

		system("color a");
		system("cls");
		H();
		cout<<"Using Option: \n";
		cout<<"Hacking [Option]\n\n\n";
		cout<<"Information\n";
		cout<<"\t-h ,--help \t\t:Bantuan alat alat pengunaan\n";
		cout<<"\t-i ,--ip \t\t:informasi ip\n";
		notfound:
		string penguna;
		cout<<">>";
		getline(cin,penguna);
		if(penguna=="Hacking -h"||penguna=="Hacking --help"){
			return main();
		}
		else{
				system("cls");
				cout<<endl<<"Tidak Ditemukan "<<endl;
				cout<<"Using Option:  \n";
				cout<<"/Hacking [Option]\n\n\n";
				cout<<"\t-h ,--help \t\t:Bantuan alat alat pengunaan\n";
				cout<<"\t-i ,--ip \t\t:informasi ip\n";
				goto notfound;
		}


	
}
