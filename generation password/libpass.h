
using namespace std;

void PasswordMake(int start = 1,int end = 9,string nama_file="",string modenya="",string nama_PD ="example",string nama_PB ="",string nama_PB_And_PD ="",string dari_tahun ="2023",string sampai_tahun = "2024",string tbh_tgl=""){
	 ofstream outfile;

   if (!nama_file.empty()) {
        if (!modenya.empty()) {
            if (modenya == "app")
                outfile.open(nama_file, ios::app);
            else if (modenya == "ate")
                outfile.open(nama_file, ios::ate);
            else if (modenya == "binary")
                outfile.open(nama_file, ios::binary);
            else if (modenya == "in")
                outfile.open(nama_file, ios::in);
            else if (modenya == "out")
                outfile.open(nama_file, ios::out);
            else
                outfile.open(nama_file); // default mode if invalid modenya
        } else {
            outfile.open(nama_file); // default mode
        }
    } else {
        if (!modenya.empty()) {
            if (modenya == "app")
                outfile.open("pass.txt", ios::app);
            else if (modenya == "ate")
                outfile.open("pass.txt", ios::ate);
            else if (modenya == "binary")
                outfile.open("pass.txt", ios::binary);
            else if (modenya == "in")
                outfile.open("pass.txt", ios::in);
            else if (modenya == "out")
                outfile.open("pass.txt", ios::out);
            else
                outfile.open("pass.txt"); // default mode if invalid modenya
        } else {
            outfile.open("pass.txt"); // default mode
        }
    }
	
    if (outfile.is_open()) {
    	 
    	 cout << nama_PD<<" "<< nama_PB <<endl;
         outfile << nama_PD<<" "<< nama_PB <<endl;
         cout << nama_PB <<" "<< nama_PD<<endl;
         outfile  << nama_PB<<" "<< nama_PD<<endl;
         
         cout << nama_PD<< nama_PB <<endl;
         outfile << nama_PD<< nama_PB <<endl;
         cout << nama_PB << nama_PD<<endl;
         outfile  << nama_PB<< nama_PD<<endl;
        // posisi nama di depan
        if (!nama_PD.empty()) {
        	 cout << nama_PD<<endl;
             outfile << nama_PD<<endl;
            for (int i = start; i <= end; ++i) {
                cout << nama_PD;
                outfile << nama_PD;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
        }

        // posisi nama di belakang
        if (!nama_PB.empty()) {
        	 cout << nama_PB<<endl;
          	 outfile << nama_PB<<endl;
            for (int i = start; i <= end; ++i) {
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << nama_PD << endl;
                outfile << nama_PD << endl;
            }
        }

        // kalau nama ada posisi belakang MODE posisi nama di depan dan di belakang
        if (nama_PB_And_PD == "ya") {
        	//psosisi angka tengah
            for (int i = start; i <= end; ++i) {
                cout << nama_PD;
                outfile << nama_PD;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << nama_PB << endl;
                outfile << nama_PB << endl;
            }
            
            //posisi angka depan
            for (int i = start; i <= end; ++i) {
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout <<nama_PD<<nama_PB << endl;
                outfile <<nama_PD<<nama_PB << endl;
            }
            //posisi angka belakang
             for (int i = start; i <= end; ++i) {
                cout << nama_PD<<nama_PB;
                outfile << nama_PD<<nama_PB;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
            
            
            
        }
		//upper
 		 string nama_PD_upper = nama_PD;
        string nama_PB_upper = nama_PB;
        transform(nama_PD_upper.begin(), nama_PD_upper.end(), nama_PD_upper.begin(), ::toupper);
        transform(nama_PB_upper.begin(), nama_PB_upper.end(), nama_PB_upper.begin(), ::toupper);

        if (!nama_PD_upper.empty()) {
            cout << nama_PD_upper << endl;
            outfile << nama_PD_upper << endl;
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_upper;
                outfile << nama_PD_upper;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
        }

        if (!nama_PB_upper.empty()) {
            cout << nama_PB_upper << endl;
            outfile << nama_PB_upper << endl;
            for (int i = start; i <= end; ++i) {
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << nama_PD_upper << endl;
                outfile << nama_PD_upper << endl;
            }
        }
		//huruf kapital depan
		// capitalize first letter
        string nama_PD_capitalized = nama_PD;
        string nama_PB_capitalized = nama_PB;
        if (!nama_PD.empty()) {
            nama_PD_capitalized[0] = toupper(nama_PD_capitalized[0]);
        }
        if (!nama_PB.empty()) {
            nama_PB_capitalized[0] = toupper(nama_PB_capitalized[0]);
        }

        if (!nama_PD_capitalized.empty()) {
            cout << nama_PD_capitalized << endl;
            outfile << nama_PD_capitalized << endl;
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_capitalized;
                outfile << nama_PD_capitalized;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
        }
        //kapital angkaHuruf
        if (!nama_PD_capitalized.empty()) {
            cout << nama_PD_capitalized << endl;
            outfile << nama_PD_capitalized << endl;
            for (int i = start; i <= end; ++i) {
                
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << nama_PD_capitalized << endl;
                outfile << nama_PD_capitalized<< endl;
            }
        }
		//kapital angkaHurufangka
  		if (!nama_PD_capitalized.empty()) {
            cout << nama_PD_capitalized << endl;
            outfile << nama_PD_capitalized << endl;
            for (int i = start; i <= end; ++i) {
                
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << nama_PD_capitalized;
                outfile << nama_PD_capitalized;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout<< endl;
                outfile<< endl;
            }
        }
        
        // kombinasi simbol di depan, tengah, dan belakang
        char symbols[] = {'$','@', '#', '*', '!', '&', '-', '_', '?'};
        for (char symbol : symbols) {
            // simbol di depan
            for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD;
                outfile << symbol << nama_PD;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
            
            // simbol di belakang
            for (int i = start; i <= end; ++i) {
                cout << nama_PD;
                outfile << nama_PD;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }
            
            // simbol di depan dan belakang
            for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD;
                outfile << symbol << nama_PD;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }
            
            // simbol di tengah
            for (int i = start; i <= end; ++i) {
                cout << nama_PD;
                outfile << nama_PD;
                for (int j = 0; j < i / 2; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol;
                outfile << symbol;
                for (int j = i / 2; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
    	}
        	//uppper dan simbol-simbol
	    for (char symbol : symbols) {

            // simbol di depan
            for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD_upper;
                outfile << symbol << nama_PD_upper;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }

            // simbol di belakang
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_upper;
                outfile << nama_PD_upper;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }

            // simbol di depan dan belakang
            for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD_upper;
                outfile << symbol << nama_PD_upper;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }

            // simbol di tengah
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_upper << symbol;
                outfile << nama_PD_upper << symbol;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }
		}
		//kapital dan simbol-simbol
		for (char symbol : symbols) {

			for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD_capitalized;
                outfile << symbol << nama_PD_capitalized;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }

            // symbol in back
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_capitalized;
                outfile << nama_PD_capitalized;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }

            // symbol in front and back
            for (int i = start; i <= end; ++i) {
                cout << symbol << nama_PD_capitalized;
                outfile << symbol << nama_PD_capitalized;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << symbol << endl;
                outfile << symbol << endl;
            }

            // symbol in middle
            for (int i = start; i <= end; ++i) {
                cout << nama_PD_capitalized << symbol;
                outfile <<nama_PD_capitalized << symbol;
                for (int j = start; j <= i; ++j) {
                    cout << j;
                    outfile << j;
                }
                cout << endl;
                outfile << endl;
            }			
        }



        // kombinasi tanggal, bulan, tahun
        // contoh aditiya010202
        string days[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"};
        string months[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
        for (const string& day : days) {
            for (const string& month : months) {
                for (int year = stoi(dari_tahun); year <= stoi(sampai_tahun); ++year) {
                    string year_str = to_string(year);
                    // format: nama + ddmmyy
                    cout << nama_PD << day << month << year_str.substr(2, 2) << endl;
                    outfile << nama_PD << day << month << year_str.substr(2, 2) << endl;
                    cout << nama_PD<<nama_PB << day << month << year_str.substr(2, 2) << endl;
                    outfile << nama_PD<<nama_PB << day << month << year_str.substr(2, 2) << endl;
                    
                    // format: nama + ddmmyyyy
                    cout << nama_PD << day << month << year_str << endl;
                    outfile << nama_PD << day << month << year_str << endl;
                    cout << nama_PD<<nama_PB<< day << month << year_str << endl;
                    outfile << nama_PD<<nama_PB<< day << month << year_str << endl;
                    
                    // format: nama + mmddyy
                    cout << nama_PD << month << day << year_str.substr(2, 2) << endl;
                    outfile << nama_PD << month << day << year_str.substr(2, 2) << endl;
                    cout << nama_PD<<nama_PB << month << day << year_str.substr(2, 2) << endl;
                    outfile << nama_PD<<nama_PB << month << day << year_str.substr(2, 2) << endl;
                    
                    // format: nama + yymmdd
                    cout << nama_PD << year_str.substr(2, 2) << month << day << endl;
                    outfile << nama_PD << year_str.substr(2, 2) << month << day << endl;
                    cout << nama_PD<<nama_PB<< year_str.substr(2, 2) << month << day << endl;
                    outfile << nama_PD<<nama_PB << year_str.substr(2, 2) << month << day << endl;
                    
                    // format: nama + yyyymmdd
                    cout << nama_PD << year_str << month << day << endl;
                    outfile << nama_PD << year_str << month << day << endl;
                    cout << nama_PD<<nama_PB << year_str << month << day << endl;
                    outfile << nama_PD<<nama_PB << year_str << month << day << endl;
                    
                    //dibalik
                     // format: nama + ddmmyy
                    cout << day << month << year_str.substr(2, 2) << nama_PD << endl;
                    outfile << day << month << year_str.substr(2, 2) << nama_PD << endl;
                    cout << day << month << year_str.substr(2, 2) << nama_PD<<nama_PB << endl;
                    outfile << day << month << year_str.substr(2, 2)  << nama_PD<<nama_PB<< endl;
                    
                    // format: nama + ddmmyyyy
                    cout  << day << month << year_str << nama_PD<< endl;
                    outfile  << day << month << year_str << nama_PD << endl;
                     cout  << day << month << year_str << nama_PD<<nama_PB<< endl;
                    outfile  << day << month << year_str << nama_PD<<nama_PB<< endl;
                    
                    // format: nama + mmddyy
                    cout << month << day << year_str.substr(2, 2) << nama_PD << endl;
                    outfile  << month << day << year_str.substr(2, 2) << nama_PD<< endl;
                    cout << month << day << year_str.substr(2, 2) << nama_PD<<nama_PB<< endl;
                    outfile  << month << day << year_str.substr(2, 2) << nama_PD<<nama_PB<< endl;
                    
                    // format: nama + yymmdd
                    cout  << year_str.substr(2, 2) << month << day << nama_PD<< endl;
                    outfile  << year_str.substr(2, 2) << month << day << nama_PD<< endl;
                    cout  << year_str.substr(2, 2) << month << day << nama_PD<<nama_PB<< endl;
                    outfile  << year_str.substr(2, 2) << month << day << nama_PD<<nama_PB<< endl;
                    
                    // format: nama + yyyymmdd
                    cout  << year_str << month << day << nama_PD<< endl;
                    outfile  << year_str << month << day << nama_PD<< endl;
                    cout  << year_str << month << day << nama_PD<<nama_PB<< endl;
                    outfile  << year_str << month << day << nama_PD<<nama_PB<< endl;
                    
                    //tanggal lahir aja
                    
                    if(tbh_tgl=="ya"){
                    	 // format: nama + ddmmyy
                    cout << day << month << year_str.substr(2, 2) << endl;
                    outfile << day << month << year_str.substr(2, 2) << endl;
                    // format: nama + ddmmyyyy
                    cout << day << month << year_str << endl;
                    outfile << day << month << year_str << endl;
                    // format: nama + mmddyy
                    cout << month << day << year_str.substr(2, 2) << endl;
                    outfile << month << day << year_str.substr(2, 2) << endl;
                    // format: nama + yymmdd
                    cout << year_str.substr(2, 2) << month << day << endl;
                    outfile  << year_str.substr(2, 2) << month << day << endl;
                    // format: nama + yyyymmdd
                    cout << year_str << month << day << endl;
                    outfile  << year_str << month << day << endl;
                    	
                    	
					}
					else{
						
						break;
					}
                    
                    
                }
            }
        }

        outfile.close();
        cout << "\nGenerate password berhasil dibuat" << endl;
    } else {
        cerr << "File tidak dapat dibuka!" << endl;
    }
}
