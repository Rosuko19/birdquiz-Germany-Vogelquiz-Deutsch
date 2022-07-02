#include <iostream>
#include <windows.h>//für die Methode PlaySound()
#include <MMSystem.h>//für die Methode PlaySound()
#include <random>//für rand() und srand()
#include <ctime>//für ziehungszufallsZahl()
#include <algorithm>//für Methode find()
#include <vector>//fürs speichern der bereits gezogenen Zahlen
#include <cmath>
#include <cstdlib>

/*
https://docs.microsoft.com/en-us/previous-versions/dd743680(v=vs.85 //Methode PlaySound Parameter erklärt
https://www.tierstimmenarchiv.de //hier habe ich die wav dateien her
https://www.avi-fauna.info/start/haeufige-brutvoegel/ //häufigsten Brutvögel Deutschlands

Insgesamt 84 verschiedene Vögel, von manchen habe ich sowohl Rufe als auch Gesang genommen(siehe Amsel,Rotkehlchen,Buchfink und Mönchsgrasmücke)
*/

using namespace std;

//globale Variablen
string eingVogel,gespielterVogel; //eingVogel= der Vogelname, welcher über das Terminal übergeben wird | gespielterVogel= der letzte Vogel, welcher abgespielt wurde
int richtigeVoegel=0, falscheVoegel=0;//zähler variable, für das Endergebnis
bool versuch=NULL;//bei jedem case wird hierdrin das Ergebnis der Funktion verarbeitungSwitchCase() gespeichert
string nChancegewuenscht="false";//Variable, in welcher gespeichert wird, ob nach einer falschen Eingabe eine neue Chance gewünscht ist
int zufallsZahl;//hier wird die Zahl für die switch-case-Variable gespeichert, siehe Methode ziehungsZufallszahl() und mainone()
int speicherzufallsZahl;
std::vector<int> zahlen_vector;//speichert alle bereits gezogene Zufallszahlen, damit kein Vogel doppelt vorkommt
int counter=1;//beim wievielten Vogel ist das Programm gerade
int speichercounter;//speichert die letzte zufallszahl, wird in Methode ziehungsZufallszahl() gebraucht als backup
bool abbruch;//soll weitergespielt werden nach jeden 10. gespielten Vogel
string sabbruch;//die gleiche Information als string gespeichert, damit war es einfacher zu vergleichen gewesen in einem if statement


bool verarbeitungSwitchCase()//hier wird die Eingabe nach Abspielen des Vogels über das Terminal verarbeitet
{
 try
 {
    cout <<"Eingabe des Vogels: "<<endl;
    cin >> eingVogel;

    if(eingVogel==gespielterVogel)
    {
        cout <<"Richtig!"<<endl;
        richtigeVoegel++;
        return true;

    }

    else{
            cout <<"Falsch"<<endl;
            falscheVoegel++;
            return false;
    }

 }
 catch(...)
 {
     cout <<"Fehler bei verarbeitungSwitchCase()"<<endl;
 }

}

int ziehungZufallszahl()//hier wird eine Zufallszahl gezogen, jede Zahl ist für einen Vogel da
{
 try
 {
        if(nChancegewuenscht=="false")//ziehung der zufallszahl
    {

    srand(time(NULL));
    zufallsZahl = rand()%90+1;
    speicherzufallsZahl=zufallsZahl;
    }

    if(find(zahlen_vector.begin(),zahlen_vector.end(),zufallsZahl) != zahlen_vector.end()&& nChancegewuenscht == "false")//überprüfen,
                                                                                                                        //ob die Zahl schonmal gezogen wurde
    {

        return speicherzufallsZahl;//wenn sie bereits gezogen wurde,gebe gespeicherte Zahl zurück
    }

    else//wenn sie zum ersten mal gezogen wird
    {
    zahlen_vector.push_back(zufallsZahl);//füge sie den bereits gezogenen Zahlen hinzu
    return zufallsZahl;//gebe die neue Zufallszahl zurück

    }
 }
 catch(...)
 {
     cout <<"Fehler bei ziehungZufallszahl() "<<endl;
 }


}


void hauptprogramm()//hier befindet sich der Haupteil des Programms, zb. Abspielen der Sounddateien, was soll passieren, wenn falsche Eingabe
{

    while(abbruch==false)
    {//Ende der while schleife ungefähr in Zeile 1105

        try
        {
              if(counter > 1)//beim ersten mal soll keine freie Zeile da sein
        {
           cout <<"\n"<<endl;//eine freie Zeile einfügen zwischen den Vögeln
        }
        if(counter % 10 !=0)//bei jedem 10. Vogel wird zuerst gefragt, ob der Benutzer weiterspielen möchte, ansonsten wird nicht gefragt
        {
        cout <<counter<<". Vogelstimme "<<endl;//gibt aus, bei der wievielten Vogelstimme das Programm gerade ist

        }

        ziehungZufallszahl();//ziehung eines neuen vogels

        //alle zehn umlaufe nachfragen, ob der Spieler weitermachen will
        if(counter % 10 == 0)
        {

        cout <<"weiterspielen?true/false "<<endl;
        cin >> sabbruch;

        if(sabbruch=="false")//wenn der Benutzer nicht mehr weiterspielen will und false eingibt,
            {
            abbruch=true;//wird abbruch auf true gesetzt
            break;//springe aus while schleife raus
            }
            cout <<counter<<". Vogelstimme "<<endl;//damit erst gefragt wird, ob der Spieler weiterspielen möchte und dann erst der neue Vogel angezeigt wird

        }

        }//Ende des try blocks

                catch(...)
        {
            cout <<"Fehler oberhalb des Einstiegspunkts der goto-Anweisung in hauptprogramm()"<<endl;
        }

    neueChance://Einstiegspunkt für den Befehl goto in ca Zeile 1089
    nChancegewuenscht="false";//zurücksetzung auf false


  try
  {
       switch(zufallsZahl)
{//Anfang des switchs


//ein Case erklärt:
case(1)://wenn die zufallsZahl 1 ist, mache diesen Code
    {
    gespielterVogel="amsel";//setze gespielterVogel auf den gleich abzuspielenden Vogel, hier die Amsel
    PlaySound(TEXT("amsel.wav"),NULL,SND_ASYNC);//diese Methode spielt eine wav datei ab, um diese Methode benutzen zu können muss man unter Windows <windows.h> und <MMSystem.h> hinzufügen
    //PlaySound(TEXT(name der datei, wo die Vogelstimme drin gespeichert wird(sie muss sich nicht im gleichen Ordner wie die c++ datei befinden, dann muss man aber den Pfad hinschreiben), NULL,
    //soll man schon während die Sounddatei abgespielt wird den Vogelname eingeben können?SND_ASYNC erlaubt die Eingabe schon während des Abspielens),
    //die Methode gibt einen bool Wert zurück, ob die Datei abgespielt werden konnte
    versuch=verarbeitungSwitchCase();//rufe Funktion switch case auf, welche einen bool Wert zurückgibt, abhängig davon, ob richtig geraten wurde oder nicht (richtig geraten, dann versuch=true)
    counter++;//erhöhe Anzahl der abgespielten Vögel um eins
    speichercounter=counter;
    break;//springe aus dem Switch-case heraus
    }

case(2):
    {
    gespielterVogel="buchfink";
    PlaySound(TEXT("buchfink.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(3):
    {
    gespielterVogel="kohlmeise";
    PlaySound(TEXT("kohlmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(4):
    {
    gespielterVogel="moenchsgrasmuecke";
    PlaySound(TEXT("moenchsgrasmuecke.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(5):
    {
    gespielterVogel="haussperling";
    PlaySound(TEXT("haussperling.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(6):
    {
    gespielterVogel="blaumeise";
    PlaySound(TEXT("blaumeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(7):
    {
    gespielterVogel="zilpzalp";
    PlaySound(TEXT("zilpzalp.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(8):
    {
    gespielterVogel="rotkehlchen";
    PlaySound(TEXT("rotkehlchen.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(9):
    {
    gespielterVogel="star";
    PlaySound(TEXT("star.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(10):
    {
    gespielterVogel="zaunkoenig";
    PlaySound(TEXT("zaunkoenig.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(11):
    {
    gespielterVogel="singdrossel";
    PlaySound(TEXT("singdrossel.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(12):
    {
    gespielterVogel="gruenfink";
    PlaySound(TEXT("gruenfink.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(13):
    {
    gespielterVogel="sommergoldhaehnchen";
    PlaySound(TEXT("sommergoldhaehnchen.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(14):
    {
    gespielterVogel="feldlerche";
    PlaySound(TEXT("feldlerche.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(15):
    {
    gespielterVogel="heckenbraunelle";
    PlaySound(TEXT("heckenbraunelle.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(16):
    {
    gespielterVogel="kleiber";
    PlaySound(TEXT("kleiber.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(17):
    {
    gespielterVogel="goldammer";
    PlaySound(TEXT("goldammer.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(18):
    {
    gespielterVogel="tannenmeise";
    PlaySound(TEXT("tannenmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(19):
    {
    gespielterVogel="wintergoldhaehnchen";
    PlaySound(TEXT("wintergoldhaehnchen.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(20):
    {
    gespielterVogel="feldsperling";
    PlaySound(TEXT("feldsperling.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(21):
    {
    gespielterVogel="fitis";
    PlaySound(TEXT("fitis.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(22):
    {
    gespielterVogel="buntspecht";
    PlaySound(TEXT("buntspecht.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(23):
    {
    gespielterVogel="hausrotschwanz";
    PlaySound(TEXT("hausrotschwanz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(24):
    {
    gespielterVogel="gartengrasmuecke";
    PlaySound(TEXT("gartengrasmuecke.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(25):
    {
    gespielterVogel="rabenkraehe";
    PlaySound(TEXT("rabenkraehe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(26):
    {
    gespielterVogel="dorngrasmuecke";
    PlaySound(TEXT("dorngrasmuecke.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(27):
    {
    gespielterVogel="mehlschwalbe";
    PlaySound(TEXT("mehlschwalbe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(28):
    {
    gespielterVogel="rauchschwalbe";
    PlaySound(TEXT("rauchschwalbe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(29):
    {
    gespielterVogel="eichelhaeher";
    PlaySound(TEXT("eichelhaeher.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(30):
    {
    gespielterVogel="bachstelze";
    PlaySound(TEXT("bachstelze.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(31):
    {
    gespielterVogel="gartenbaumlaeufer";
    PlaySound(TEXT("gartenbaumlaeufer.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(32):
    {
    gespielterVogel="haubenmeise";
    PlaySound(TEXT("haubenmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(33):
    {
    gespielterVogel="waldbaumlaeufer";
    PlaySound(TEXT("waldbaumlaeufer.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(34):
    {
    gespielterVogel="sumpfmeise";
    PlaySound(TEXT("sumpfmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(35):
    {
    gespielterVogel="elster";
    PlaySound(TEXT("elster.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(36):
    {
    gespielterVogel="sumpfrohrsaenger";
    PlaySound(TEXT("sumpfrohrsaenger.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(37):
    {
    gespielterVogel="baumpieper";
    PlaySound(TEXT("baumpieper.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(38):
    {
    gespielterVogel="stieglitz";
    PlaySound(TEXT("stieglitz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(39):
    {
    gespielterVogel="kernbeisser";
    PlaySound(TEXT("kernbeisser.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(40):
    {
    gespielterVogel="gimpel";
    PlaySound(TEXT("gimpel.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(41):
    {
    gespielterVogel="stockente";
    PlaySound(TEXT("stockente.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(42):
    {
    gespielterVogel="misteldrossel";
    PlaySound(TEXT("misteldrossel.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(43):
    {
    gespielterVogel="drosselrohrsaenger";
    PlaySound(TEXT("drosselrohrsaenger.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(44):
    {
    gespielterVogel="klappergrasmuecke";
    PlaySound(TEXT("klappergrasmuecke.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(45):
    {
    gespielterVogel="waldlaubsaenger";
    PlaySound(TEXT("waldlaubsaenger.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(46):
    {
    gespielterVogel="fasan";
    PlaySound(TEXT("fasan.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(47):
    {
    gespielterVogel="grauschnaepper";
    PlaySound(TEXT("grauschnaepper.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(48):
    {
    gespielterVogel="wacholderdrossel";
    PlaySound(TEXT("wacholderdrossel.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(49):
    {
    gespielterVogel="bluthaenfling";
    PlaySound(TEXT("bluthaenfling.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(50):
    {
    gespielterVogel="rohrammer";
    PlaySound(TEXT("rohrammer.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(51):
    {
    gespielterVogel="teichrohrsaenger";
    PlaySound(TEXT("teichrohrsaenger.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(52):
    {
    gespielterVogel="lachmoewe";
    PlaySound(TEXT("lachmoewe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(53):
    {
    gespielterVogel="schwanzmeise";
    PlaySound(TEXT("schwanzmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(54):
    {
    gespielterVogel="gelbspoetter";
    PlaySound(TEXT("gelbspoetter.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(55):
    {
    gespielterVogel="gartenrotschwanz";
    PlaySound(TEXT("gartenrotschwanz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(56):
    {
    gespielterVogel="nachtigall";
    PlaySound(TEXT("nachtigall.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

 case(57):
    {
    gespielterVogel="wiesenschafstelze";
    PlaySound(TEXT("schafstelze.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(58):
    {
    gespielterVogel="neuntoeter";
    PlaySound(TEXT("neuntoeter.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(59):
    {
    gespielterVogel="dohle";
    PlaySound(TEXT("dohle.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(60):
    {
    gespielterVogel="uferschwalbe";
    PlaySound(TEXT("uferschwalbe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(61):
    {
    gespielterVogel="saatkraehe";
    PlaySound(TEXT("saatkraehe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(62):
    {
    gespielterVogel="schwarzkehlchen";
    PlaySound(TEXT("schwarzkehlchen.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(63):
    {
    gespielterVogel="trauerschnaepper";
    PlaySound(TEXT("trauerschnaepper.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(64):
    {
    gespielterVogel="girlitz";
    PlaySound(TEXT("girlitz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(65):
    {
    gespielterVogel="weidenmeise";
    PlaySound(TEXT("weidenmeise.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(66):
    {
    gespielterVogel="maeussebussard";
    PlaySound(TEXT("maeussebussard.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(67):
    {
    gespielterVogel="gruenspecht";
    PlaySound(TEXT("gruenspecht.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(68):
    {
    gespielterVogel="nebelkraehe";
    PlaySound(TEXT("nebelkraehe.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(69):
    {
    gespielterVogel="waldkauz";
    PlaySound(TEXT("waldkauz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(70):
    {
    gespielterVogel="turmfalke";
    PlaySound(TEXT("turmfalke.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(71):
    {
    gespielterVogel="fichtenkreuzschnabel";
    PlaySound(TEXT("fichtenkreuzschnabel.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(72):
    {
    gespielterVogel="kiebitz";
    PlaySound(TEXT("kiebitz.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(73):
    {
    gespielterVogel="graugans";
    PlaySound(TEXT("graugans.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(74):
    {
    gespielterVogel="mittelspecht";
    PlaySound(TEXT("mittelspecht.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(75):
    {
    gespielterVogel="wiesenpieper";
    PlaySound(TEXT("wiesenpieper.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(76):
    {
    gespielterVogel="gebirgsstelze";
    PlaySound(TEXT("gebirgsstelze.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(77):
    {
    gespielterVogel="pirol";
    PlaySound(TEXT("pirol.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(78):
    {
    gespielterVogel="schwarzspecht";
    PlaySound(TEXT("schwarzspecht.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(79):
    {
    gespielterVogel="heidelerche";
    PlaySound(TEXT("heidelerche.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(80):
    {
    gespielterVogel="erlenzeisig";
    PlaySound(TEXT("erlenzeisig.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(81):
    {
    gespielterVogel="turteltaube";
    PlaySound(TEXT("turteltaube.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

    //weitere nicht singvögel
case(82):
    {
    gespielterVogel="mauersegler";
    PlaySound(TEXT("mauersegler.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }


case(83):
    {
    gespielterVogel="alpensegler";
    PlaySound(TEXT("alpensegler.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(84):
    {
    gespielterVogel="rotmilan";
    PlaySound(TEXT("rotmilan.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(85):
    {
    gespielterVogel="wendehals";
    PlaySound(TEXT("wendehals.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
   //ein paar Rufe von Singvögeln

   case(86):
    {
    gespielterVogel="amsel";
    PlaySound(TEXT("amsel_ruf.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(87):
    {
    gespielterVogel="rotkehlchen";
    PlaySound(TEXT("rotkehlchen_ruf.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
}
case(88):
    {
    gespielterVogel="buchfink";
    PlaySound(TEXT("buchfink_ruf.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }

case(89):
    {
    gespielterVogel="buchfink";
    PlaySound(TEXT("buchfink_regenruf.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }
case(90):
    {
    gespielterVogel="moenchsgrasmuecke";
    PlaySound(TEXT("moenchsgrasmuecke_ruf.wav"),NULL,SND_ASYNC);
    versuch=verarbeitungSwitchCase();
    counter++;
    speichercounter=counter;
    break;
    }




    }//Ende der Switch-case

  }//Ende des try blocks

  catch(...)
  {
      cout <<"Fehler innerhalb der cases in hauptprogramm()"<<endl;
  }


    try
    {
            if(versuch==false && counter > 1)//bei einem falsch eingegebenen Vogel wird gefragt, ob ein neuer Versuch gewünscht ist
    {
        cout <<"Neue Chance? true/false" <<endl;
        cin >>nChancegewuenscht;
        if(nChancegewuenscht=="false")//keine neue Chance gewünscht, also löse auf, welcher Vogel das war
        {
            cout <<"Der richtige Vogel waere "<<gespielterVogel<<" gewesen"<<endl;

        }
        if (nChancegewuenscht=="true")//neue Chance
        {
            cout <<"neuer Versuch"<<endl;
            zufallsZahl=speicherzufallsZahl;
            if(counter == speichercounter)//damit nicht bei jedem neuem Versuch counter -- gemacht wird, sondern nur beim ersten Versuch
            {
            counter --;//damit der neue Versuch nicht als neuer Vogel gilt im Vorhinein bereits um eins vermindert

            }
            goto neueChance;//springe zum Punkt neueChance (ca. Zeile 142)
        }



    }
    }

    catch(...)
    {
        cout <<"Fehler unterhalb der switch-cases in hauptprogramm()"<<endl;
    }




} //Ende der while-schleife

}//ende der funktion hauptprogramm()

void endergebnis() //Methode zur Ausgabe des Endergebnisses
{

        cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        cout <<"Endergebnis:"<<endl;
        cout <<"Richtig erratene Voegel: "<<richtigeVoegel<<endl;
        cout <<"Falsch geratene Voegel: " <<falscheVoegel<<endl;

}


int main()
{
        hauptprogramm();//um den Befehl goto zu Verwenden, welcher nur innerhalb einer Funktion, welche nicht die main methode ist,
                        // funktioniert, habe ich große Teile des Programms in diese Funktion geschrieben
        endergebnis();//gebe Endergebnis aus

}
