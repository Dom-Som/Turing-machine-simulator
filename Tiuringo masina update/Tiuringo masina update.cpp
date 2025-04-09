#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <map>

using namespace std;

struct Komandos
{
    string EsBus;
    char EsSimb;
    char EsSimb2;
    char NaujSimb;
    char NaujSimb2;
    char kryptis;
    char kryptis2;
    string NaujBus;
};

map <string, int> begalinis;
vector <Komandos> nurodymai;
vector <char> galvute;
vector <char> galvute2;
vector <char> juosta;
vector <char> juosta2;
int juostuKiek, GalvutesPoz, GalvutesPoz2;
const int greitis = 1;//galvutes judejimo greitis milisekundemis

void skaityk();//nuskaito duomenis is tekstinio failo
void daryk();//atlieka operacijas nurodytas faile
void spausdink();//spausdina juosta ir galvute. Naudojamas, kai Tiuringo masina turi 2 juostas
void spausdinkfull();//spausdina, kaip keiciasi juosta atliekant operacijas. Naudojamas, kai Tiuringo masina turi 1 juosta

int main()
{
    skaityk();
    if (juostuKiek > 2 || juostuKiek < 0)
        return 0;
    daryk();
    return 0;
}

void daryk()
{
    string DbBusena = "0", DbBusena2 = "0";
    char DbSimbolis = juosta[GalvutesPoz];
    char DbSimbolis2 = juosta2[GalvutesPoz2];
    int tikrink = 0;
    if (juostuKiek == 1)//Spausdinama pradine juostos padetis
        spausdinkfull();
    else
        spausdink();

    while (true)//Pradedamas ciklas operacijoms vykdyti
    {
        int TikrinkCikla = 0;
        string dublis(juosta.begin(), juosta.end());
        begalinis[dublis]++;
        if (begalinis[dublis] > 100)//Tikrinama ar juosta kartojasi nurodyta kartu kieki, jei taip ciklas greiciausiai bus begalinis ir progama nutraukiama
        {
            cout << "Tiuringo masina greiciausiai vykdo begalini cikla";
            break;
        }
        for (int i = 0; i < nurodymai.size(); i++)//Ieskoma tinkamos busenos 
        {
            if (DbBusena == nurodymai[i].EsBus) //Tikrinama dabartine busena atitinka viena is nurodytu
            {
                if (DbSimbolis == nurodymai[i].EsSimb)//Tikrinama ar esama busena gali atlikti operacija su nurodytu simboliu
                {
                    juosta[GalvutesPoz] = nurodymai[i].NaujSimb;//Simbolis keiciamas juostoje

                    if (nurodymai[i].kryptis == 'R') //Tikrinama kuria kryptinimi turi judeti galvute
                    {
                        if ((GalvutesPoz+1) >= juosta.size())//!!cia pakeistas galvutes pozicijos indekso tikrinimas!!//
                        {
                            juosta.push_back(' '); //pridedamas tarpas kaip paskutinis vektoriaus elementas, kai uzeinama uz juostos ribos is desines
                            tikrink++;
                        }
                        galvute.insert(galvute.begin(), ' ');
                        GalvutesPoz++;
                        DbSimbolis = juosta[GalvutesPoz];
                    }
                    else if (nurodymai[i].kryptis == 'L')//Tikrinam, kuria kryptimi turi judeti galvute
                    {
                        if ((GalvutesPoz - 1) < 0)//!!cia pakeistas galvutes pozicijos indekso tikrinimas!!//
                        {
                            juosta.insert(juosta.begin(), ' ');//pridedamas tarpas kaip pirmas vektoriaus elementas, kai uzeinama uz juostos ribos is kaires
                            tikrink++;
                        }
                        galvute.erase(galvute.begin());
                        //!!!3.txt ir 7.txt failo pataisymas!!!
                        if(tikrink == 0)
                         GalvutesPoz--;
                        DbSimbolis = juosta[GalvutesPoz];
                    }
                    DbBusena = nurodymai[i].NaujBus;//keiciama dabartine busena
                    TikrinkCikla++;
                    //!!!Spausdinimo funkcija pataisyta, kad spausdintu juosta tik tada kai ivyksta pokytis!!!
                    if (juostuKiek == 1 && nurodymai[i].EsSimb != nurodymai[i].NaujSimb)//Spausdinama juosta po kiekvieno pokycio
                        spausdinkfull();
                    else if(juostuKiek == 2)
                        spausdink();
                }
            }
        }

        if (juostuKiek == 2) // Atliekamos tos pacios operacijos su antraja juosta, jeigu tokia yra
        {
            for (int i = 0; i < nurodymai.size(); i++)
            {
                if (DbBusena2 == nurodymai[i].EsBus)
                {
                    if (DbSimbolis2 == nurodymai[i].EsSimb2)
                    {
                        juosta2[GalvutesPoz2] = nurodymai[i].NaujSimb2;

                        if (nurodymai[i].kryptis2 == 'R')
                        {
                            if ((GalvutesPoz2+1) >= juosta2.size())
                            {
                                juosta2.push_back(' ');
                                tikrink++;
                            }
                            galvute2.insert(galvute2.begin(), ' ');
                            GalvutesPoz2++;
                            DbSimbolis2 = juosta2[GalvutesPoz2];
                        }
                        else if (nurodymai[i].kryptis2 == 'L')
                        {
                            if ((GalvutesPoz2 - 1) < 0)
                            {
                                juosta2.insert(juosta2.begin(), ' ');
                                tikrink++;
                            }
                            galvute2.erase(galvute2.begin());
                            if(tikrink == 0)
                                GalvutesPoz2--;
                            DbSimbolis2 = juosta2[GalvutesPoz2];
                        }
                        DbBusena2 = nurodymai[i].NaujBus;
                        TikrinkCikla++;
                        spausdink();
                    }
                }
            }
        }
        if (TikrinkCikla == 0) //Tikrinama ar Tiuringo masina atliko operacija, jeigu ne masina stabdoma
        {
            if (tikrink != 0) {
                cout << "Tiuringo masinos galvute uzejo uz juostos ribu, nerasta daugiau busenu";
            }
            else {
                cout << "Nerasta nurodymu busenai: " << DbBusena;
            }
            break;
        }
    }
}

void spausdink()
{
    this_thread::sleep_for(chrono::milliseconds(greitis));
    system("cls");
    for (char simbolis : juosta)
    {
        cout << simbolis;
    }
    cout << endl;
    for (char simbolis : galvute)
    {
        cout << simbolis;
    }
    cout << endl;
    for (char simbolis : juosta2)
    {
        cout << simbolis;
    }
    cout << endl;
    for (char simbolis : galvute2)
    {
        cout << simbolis;
    }
    cout << endl;
}

void skaityk()
{
    Komandos komanda;
    string Laikjuosta, pav;
    string laikinas;
    cout << "Iveskite tekstinio failo pavadinima, kuriame yra jusu norimos tiuringo masinos kodas." << endl;
    cout << "Reikia ivesti tik failo pavadinima, be prieraso '.txt'" << endl;
    cin >> pav;
    ifstream df;
    df.open("../" + pav + ".txt");//Tekstinio failo pavadinimas paimamas kaip argumentas
    df >> juostuKiek;
    if (juostuKiek == 1)
    {
        getline(df >> ws, Laikjuosta);
        juosta.assign(Laikjuosta.begin(), Laikjuosta.end());//Ivedama Tiuringo masinos juosta
        juosta2.assign(Laikjuosta.begin(), Laikjuosta.end());
        df >> GalvutesPoz;
        GalvutesPoz--;//Galvutes pozicija sumazinama vienetu kadangi naudojami vektoriaus indeksai prasideda nuo 0
        GalvutesPoz2 = GalvutesPoz;
        for (int i = 0; i < juosta.size(); i++) //ivedamas vektorius, kuris atvaizduos galvute pozicija ekrane
        {
            if (GalvutesPoz == i)
                galvute.push_back('^');
            else
                galvute.push_back(' ');
        }
        while (!df.eof())//ivedami nurodymai i struktura
        {
            df >> komanda.EsBus;
            df >> komanda.EsSimb;
            df >> komanda.NaujSimb;
            df >> komanda.kryptis;
            df >> komanda.NaujBus;
            nurodymai.push_back(komanda);
        }
    }
    else if (juostuKiek == 2)//Ivedimas, kai Tiuringo masina turi 2 juostas
    {
        getline(df >> ws, Laikjuosta);
        juosta.assign(Laikjuosta.begin(), Laikjuosta.end());
        getline(df >> ws, Laikjuosta);
        juosta2.assign(Laikjuosta.begin(), Laikjuosta.end());
        df >> GalvutesPoz;
        df >> GalvutesPoz2;
        GalvutesPoz--;
        GalvutesPoz2--;
        for (int i = 0; i < juosta.size(); i++)
        {
            if (GalvutesPoz == i)
                galvute.push_back('^');
            else
                galvute.push_back(' ');

            if (GalvutesPoz2 == i)
                galvute2.push_back('^');
            else
                galvute2.push_back(' ');
        }
        while (!df.eof())//ivedami nurodymai i struktura
        {
            df >> komanda.EsBus;
            df >> komanda.EsSimb;
            df >> komanda.EsSimb2;
            df >> komanda.NaujSimb;
            df >> komanda.NaujSimb2;
            df >> komanda.kryptis;
            df >> komanda.kryptis2;
            df >> komanda.NaujBus;
            nurodymai.push_back(komanda);
        }
    }
    else
    {
        cout << "Netinkamas nurodytas juostu kiekis. Si masina gali vykdyti tik 2 arba 1 juostos Tiuringo masinas";
        return;
    }
    df.close();
}

void spausdinkfull()
{
    for (char simbolis : juosta)
    {
        cout << simbolis;
    }
    cout << endl;
}