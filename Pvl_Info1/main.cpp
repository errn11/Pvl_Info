//Name: Aaron Gabert, Matrikelnummer: 554631

//darstellung in Matrixform funktioniert leider nicht für alle Werte korrekt.
// darstellung mit vertauschen x und y werten für fliese fehlt


//Jacobs
/* Bemerkungen:
 + Werte in der Matrix sind nicht korrekt
 + Ausgabe der Matrix ist nicht korrekt formatiert.
 + Drehung der Fliese um 90° fehlt
 + Berechnung ermittelt nicht den günstigsten Preis    // sollte nun funktionieren teste nochmal mit versch. werten
 + Keine Verwendung globaler Variablen               //  gelöst indem fliese raum, kachel, und **matrix in die main gerutscht sind ?
 */

#include <iostream>
using namespace std;


struct fliese {
    float x;
    float y;
};


int main() {
    
    fliese raum, kachel, **matrix;
    
    
    //initialisiere raum
    cout << "Breite des Raumens Eingeben (M): ";
    cin >> raum.x;
    while(raum.x>8){
        cout << "Raum darf nicht groesser sein als 8m, erneute Eingabe: " << endl;
        cin >> raum.x;
    }
    raum.x*=100;
    
    cout << "Laenge des Raumes Eingeben(M): ";
    cin >> raum.y;
    while(raum.y>8){
        cout <<"Raum darf nicht laenger sein als 8m, erneute Eingabe: " << endl;
        cin >> raum.y;
    }
    raum.y*=100;
    
    //initialisiere kachel
    cout << "Breite der fliese Eingeben(Cm): ";
    cin >> kachel.x;
    while(kachel.x<10){
        cout <<" Breite muss mindestens 10cm sein, eingabe wiederholen: " << endl;
        cin >> kachel.x;
    }
    
    cout << "Laenge der Fliese Eingeben (Cm): ";
    cin >> kachel.y;
    while(kachel.y<10){
        cout <<"Laenge muss mindestens 10cm sein, eingabe wiederholen: "  << endl;
        cin >> kachel.y;
    }
    
    //Berechnungen raum  und kachel
    float qcmR = raum.x*raum.y;
    float qcmK = kachel.x*kachel.y;
    float countF = (qcmR/qcmK);                                // anzahl fliesen
    countF+=0.005;                                             // fuer korrektes runden
    countF=(int)(countF*100);                                 // cast auf int, alle komma fallen weg
    countF/=100;                                              // +2 nachkommastellen
    
    int HilfsCountF = (int)(countF);                         //cast anzahl fliesen auf int
    if(countF>HilfsCountF) {
        HilfsCountF+=1;                                      // +1 fliese falls durch cast auf int wert verloren ging
    }
    
    
    cout << "Der Raum hat eine Groesse von: " << qcmR/10000 << "Qm" << endl;
    cout << "Eine Fliese hat eine Groesse von: " << qcmK << " Qcm" << endl;
    cout << "Zu verlegende Fliesen fuer angegebenen Raum: " << countF << endl;
    if(countF!=HilfsCountF)
        cout << "Benoetigte Anzahl Fliesen fuer angegebenen Raum: " << HilfsCountF << endl;
    
    
    //Variablen fuer guenstigster Gesamtpreis
    float preis=0;
    float einzelkauf=0;
    float preisF = 0.01*qcmK;
    float PreisFguenstig=preisF*0.75;
    float rest;
    float pakete;
    
    
    //Berechnungen fuer guenstigsten gesamtpreis
    // falls anzahl Fliesen <10
    if(HilfsCountF<10)
    {
        preis=preisF*HilfsCountF;
        preis+=0.005;
        preis=(int)(preis*100);
        preis/=100;
        cout << "Guenstigster Gesamtpreis: " << preis << "Eur" <<  endl;
    }
    //falls anzahl Fliese >10
    else
    {
        pakete=HilfsCountF/10;
        rest=HilfsCountF-(int)pakete*10;
        if(rest>=7.5)
            pakete++;
        else
            einzelkauf=rest;                         //rest aufrunden?
        cout << einzelkauf << endl;                  //delete
        
        preis=(((pakete*10)*PreisFguenstig)+(einzelkauf*preisF));
        preis+=0.005;
        preis=(int)(preis*100);
        preis/=100;
        cout << "Guenstigster Gesamtpreis: " << preis << "Eur" << endl;
    }
    
    
    
    
    //Matrix
    int spalten = ((raum.x)/kachel.x);
    int zeilen = ((raum.y)/kachel.y);
    
    //korrektur falls fehler bei int = (float/float)
    float zeilenTemp = ((raum.y)/kachel.y);
    zeilenTemp+=0.005;
    zeilenTemp=(int)(zeilenTemp*100);
    zeilenTemp/=100;
    if(zeilenTemp>zeilen){
        zeilen+=1;
    }
    //korrektur falls fehler bei int = (float/float)
    float spaltenTemp = ((raum.x)/kachel.x);
    spaltenTemp+=0.005;
    spaltenTemp=(int)(spaltenTemp*100);
    spaltenTemp/=100;
    if(spaltenTemp>spalten){
        spalten+=1;
    }
    
    
    // Matrix
    matrix = new fliese*[zeilen];
    for(int i = 0;i<zeilen;i++) {
        matrix[i] = new fliese[spalten];
    }
    
    if(kachel.x==kachel.y){                                              //wenn kachel quadratisch &&
        float countY=raum.y;                                             // zaehler für raum.y
        for(int i=0;i<zeilen;i++)
        {
            float countX=raum.x;                                            //zaehler für raum.x
            for(int j=0;j<spalten;j++)
            {
                if(countX>=kachel.x){                                       // wenn zahler.X>=kachel.x
                    matrix[i][j].x=1;                                       // kachel kachel.x = 1
                    countX=countX-kachel.x;
                }else
                {
                    matrix[i][j].x=countX/kachel.x;                         // ansonsten teile restlichen/kachel.x
                    countX=countX-kachel.x;                                 // reduzieren um kachel.x
                }
                if(countY>=kachel.y) {                                       // wenn countY>= kachel.y dann kachel.y=1
                    matrix[i][j].y=1;
                }else
                {
                    matrix[i][j].y=countY/kachel.y;                         // ansonsten CountY/kachel.y
                }
            }
            countY=countY-kachel.y;                                         // reduziere Count für Y um kachel.y
        }
        
        // print Matrix
        for(int i=0;i<zeilen;i++){
            for(int j=0;j<spalten;j++)
            {
                if(matrix[i][j].x!=0 && matrix[i][j].y!=0){
                    //  matrix[i][j].x+=0.05;
                    //matrix[i][j].x=(int)(matrix[i][j].x*10);
                    //matrix[i][j].x/=10;                                     //rundet
                    
                    //matrix[i][j].y+=0.05;
                    //matrix[i][j].y=(int)(matrix[i][j].y*10);
                    //matrix[i][j].y/=10;                                     // rundet
                    cout.precision(2);
                    cout << matrix[i][j].x << "\t\t" << matrix[i][j].y << "     | ";
                }
            }
            cout << endl;
        }
        
    }
    else{
        float countY=raum.y;
        for(int i=0;i<zeilen;i++)
        {
            float countX=raum.x;                                              // wird mit jeder verlegten kachel richtung x dekrementiert
            for(int j=0;j<spalten;j++)
            {
                if((countX>=kachel.x)&&(i%2==0)) {                            //wenn   zaehlerX> kachel.x  && zeile 0 + jede zweite zeile = x=1
                    matrix[i][j].x=1;
                    countX=countX-kachel.x;                                   // zaehler wird um kachel.x reduziert
                }
                else if((countX>=kachel.x) && (i%2==1) && (j!=0)) {           //wenn zaehlerX>=kachel.x  && i%2==1 && spalte nicht 0 = ganze kachel
                    matrix[i][j].x=1;
                    countX=countX-kachel.x;                                   //zaehler wird um kachel.x reduziert
                }
                else if((countX>=kachel.x) && (i%2==1) && (j==0)) {           //wenn zaehlerX>=kachel.x && zeile ungerade spalte =0 dann x=0.5 halbekachel.x
                    matrix[i][j].x=0.5;
                    countX=countX-((1/2)*kachel.x);                           //zaehler wird um halbe kackel.x reduziert
                }
                else if (countX < kachel.x) {
                    matrix[i][j].x=countX/kachel.x;                             //sonst gilt für alle kachel.x = restlicher platz richtungx/kachel.x
                    countX=countX-(kachel.x * matrix[i][j].x);                  //zaehler wird um kachel.x reduziert
                }
                if(countY>=kachel.y) {                                         //wenn der zaehler fuer yRichtung>=kachel.y dann ganze kachel.y
                    matrix[i][j].y=1;
                }
                else {
                    matrix[i][j].y=countY/kachel.y;                         // wenn in Y zaehler < als kachel.y  gilt für alle kachel.y = countY/kachel.y
                }
            }
            countY=countY-kachel.y;                                         // reduziere zaehlerY um kachel.y
        }
        // print
        for(int i=0;i<zeilen;i++){
            for(int j=0;j<spalten;j++)
            {
                if(matrix[i][j].x!=0 && matrix[i][j].y!=0){
                    matrix[i][j].x+=0.05;
                    matrix[i][j].x=(int)(matrix[i][j].x*10);
                    matrix[i][j].x/=10;                                        //rundet Matrixwerte.x
                    
                    matrix[i][j].y+=0.05;
                    matrix[i][j].y=(int)(matrix[i][j].y*10);
                    matrix[i][j].y/=10;                                        //rundet Matrixwerte.y
                    cout << matrix[i][j].x << "\t\t" << matrix[i][j].y << "  |  ";
                }
            }
            cout << endl;
            cout << endl;
        }
    }
    return 0;
}


