#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class plik {  
    protected:
        ifstream fileIn;      
               
    public:    
        plik();
        ~plik();
        virtual void loop() = 0;
};

plik::plik() {
    fileIn.open("dane_obrazki.txt");
}

plik::~plik() {
    fileIn.close();
}
class ex64:public plik {
    bool rewers(string obrazek[20][20]);
    int yPos;
    int xPos;
    int paa();
    int licznikRev = 0;
    int maxCzarny = 0;
    string obraz[20][20];
    string yParzy;
    string xParzy;
    int maxBledow;
    public:virtual void loop();
};
    
void ex64::loop() {
	int dobry = 0;
	int naprawialny = 0;
	int zly = 0;
    string line;
    string buf;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 20; j++) {
            fileIn >> line;
            for(int l = 0; l < 20; l++) {
                obraz[j][l] = line[l];
            }
            yParzy += line[20];
        }
        fileIn >> xParzy;
        int dada = paa();
        yParzy = "";
        if(dada == 0) {
        	dobry++;
		} else if(dada == 1) {
			cout << "W obrazku nr " << i << " zmienic bit poziomy: " << xPos << " i pionowy: " << yPos << "\n";
			naprawialny++;
		} else if(dada > 1) {
			zly++;
		}
    }
    cout << "Ilosc dobrych obrazkow: " << dobry << "\n";
    cout << "ilosc naprawialnych obrazkow: " << naprawialny << "\n";
    cout << "ilosc zlych obrazkow: " << zly << "\n";
}
    bool ex64::rewers(string obrazek[20][20]) {
        int czarny = 0;
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 20; j++){
                if(obrazek[i][j] == "1") {
                    czarny++;
                }
            }
            if(czarny > maxCzarny) {
                maxCzarny = czarny;
            }
        }
        if(czarny > (20 * 20 / 2)) {
            return true;
        } else {
            return false;
        }
    }
	int ex64::paa() {
		int xBlad = 0;
		int yBlad = 0;
		int yPa = 0;
		int xPa = 0;
		for(int i = 0; i < 20; i++) {
			yPa=0;
			xPa=0;
            for(int j = 0; j < 20; j++) {
                if(obraz [i] [j] == "1") yPa++;
                if(obraz [j] [i] == "1") xPa++;
            }
            if((( xPa % 2 ) == 1 && xParzy [i] == '0') || (( xPa % 2 ) == 0 && xParzy [i] == '1')) {
        		xPos = i;
				xBlad++;
			}
            if((( yPa % 2 ) == 1 && yParzy [i]=='0')||(( yPa % 2 )== 0 && yParzy [i] == '1')){
            	yPos = i;
				yBlad++;
			}
        }
        if( xBlad + yBlad == 0 ) return 0;
        if( xBlad <= 1 && yBlad <= 1 ) return 1;
    	return xBlad + yBlad;
}

int main() {
    ex64 wynikKoncowy;
    wynikKoncowy.loop();
    return 0;
}
