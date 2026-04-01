#include <iostream>
#include <cstring>

class Client
{
    char* nume;
    int id_client;
    double buget;
    char* telefon;
    char* ora_sosire;

    bool lungime_telefon() const
    {
        if(telefon==nullptr)
            return false;
        if(strlen(telefon)!=10)
            return false;
        return true;
    }

    bool ora_sosire_valida(const char* ora)const
    {
        if(ora==nullptr)
            return false;
        if(strlen(ora)!=5)
            return false;
        if(ora[2]!=':')
            return false;
        int lg=strlen(ora);
        for(int i=0; i<lg; i++)
        {
            if(i!=2)
            {
                if(ora[i]<'0' || ora[i]>'9')
                    return false;
            }
        }
        int hh=(ora[0]-'0')*10+(ora[1]-'0');
        int mm=(ora[3]-'0')*10+(ora[4]-'0');
        if(hh<0 || hh>23)
            return false;
        if(mm<0 || mm>59)
            return false;
        return true;
    }

public:
    Client():id_client(0),buget(0)
    {
        nume=new char[strlen("Neidentificat")+1];
        strcpy(nume,"Neidentificat");

        telefon=new char[strlen("Necunoscut")+1];
        strcpy(telefon,"Necunoscut");

        ora_sosire=new char[strlen("Necunoscuta")+1];
        strcpy(ora_sosire,"Necunoscuta");

    }
    Client(const char* nume,const int id_client,const double buget,const char* telefon,const char* ora_sosire):id_client(id_client),buget(buget)
    {
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

        this->telefon=new char[strlen(telefon)+1];
        strcpy(this->telefon,telefon);

        if(ora_sosire_valida(ora_sosire))
        {
            this->ora_sosire=new char[strlen(ora_sosire)+1];
            strcpy(this->ora_sosire,ora_sosire);
        }
        else
        {
            this->ora_sosire=new char[strlen("Necunoscuta")+1];
            strcpy(this->ora_sosire,"Necunoscuta");
        }
    }
    Client(const Client& c):id_client(c.id_client),buget(c.buget)
    {
        this->nume=new char[strlen(c.nume)+1];
        strcpy(this->nume,c.nume);

        this->telefon=new char[strlen(c.telefon)+1];
        strcpy(this->telefon,c.telefon);

        this->ora_sosire=new char[strlen(c.ora_sosire)+1];
        strcpy(this->ora_sosire,c.ora_sosire);
    }
    Client& operator=(const Client &cl)
    {
        if(this!=&cl)
        {
            delete[] nume;
            delete[] telefon;
            delete[] ora_sosire;

            this->nume=new char[strlen(cl.nume)+1];
            strcpy(this->nume,cl.nume);

            id_client=cl.id_client;
            buget=cl.buget;

            this->telefon=new char[strlen(cl.telefon)+1];
            strcpy(this->telefon,cl.telefon);

            this->ora_sosire=new char[strlen(cl.ora_sosire)+1];
            strcpy(this->ora_sosire,cl.ora_sosire);
        }
        return *this;
    }
    ~Client()
    {
        delete[] nume;
        delete[] telefon;
        delete[] ora_sosire;
    }
    void set_nume(const char* nume)
    {
        delete[] this->nume;
        this->nume=new char[strlen(nume)+1];
        strcpy(this->nume,nume);

    }
    void set_id_client(const int id_client)
    {
        this->id_client=id_client;
    }
    void set_buget(const double buget)
    {
        if(buget>0)
            this->buget=buget;
        else
            std::cout<<"Fonduri insuficiente"<<'\n';
    }
    void set_telefon(const char* telefon)
    {
        delete[] this->telefon;
        this->telefon=new char[strlen(telefon)+1];
        strcpy(this->telefon,telefon);
    }
    void set_ora_sosire(const char* ora_sosire)
    {
        if(ora_sosire_valida(ora_sosire))
        {
            delete[] this->ora_sosire;
            this->ora_sosire=new char[strlen(ora_sosire)+1];
            strcpy(this->ora_sosire,ora_sosire);
        }
        else
            std::cout<<"Ora sosire invalida!"<<'\n';
    }
    const char* get_nume()const
    {
        return nume;
    }
    int get_id_client() const
    {
        return id_client;
    }
    double get_buget() const
    {
        return buget;
    }
    const char* get_telefon()const
    {
        return telefon;
    }
    const char* get_ora_sosire() const
    {
        return ora_sosire;
    }
    void marire_buget(const int procent)
    {
        buget=buget+(procent/100.0)*buget;
    }

    bool telefon_valid()const
    {
        if(!lungime_telefon())
            return false;
        int n=strlen(telefon);
        for(int i=0; i<n; i++)
            if(telefon[i]<'0' || telefon[i]>'9')
                return false;
        return true;
    }

};

///supraincarcarea operatorului de scriere cu ajutorul getterilor din clasa Client

std::ostream& operator <<(std::ostream& out,const Client& c)
{
    out<<"Numele clientului este:"<<c.get_nume()<<'\n';
    out<<"Are id-ul:"<<c.get_id_client()<<'\n';
    out<<"Clientul are bugetul:"<<c.get_buget()<<"$"<<'\n';
    out<<"Rezervarea a fost facuta cu numarul de telefon:"<<c.get_telefon()<<'\n';
    out<<"Clientul ajunge la ora:"<<c.get_ora_sosire()<<'\n';
    return out;
}

class Masa
{
    int nr_locuri;
    int numar_masa;
    double consum_minim;
    char* pozitie;

    bool este_pe_terasa()const
    {
        if(strcmp(pozitie,"terasa")!=0)
            return false;
        return true;
    }

public:
    Masa():nr_locuri(0),numar_masa(0),consum_minim(0)
    {
        pozitie=new char[strlen("Necunoscuta")+1];
        strcpy(pozitie,"Necunoscuta");
    }
    Masa(const int nr_locuri,const int numar_masa,const double consum_minim,const char* pozitie):nr_locuri(nr_locuri),numar_masa(numar_masa),consum_minim(consum_minim)
    {
        this->pozitie=new char[strlen(pozitie)+1];
        strcpy(this->pozitie,pozitie);
    }
    Masa(const Masa& m):nr_locuri(m.nr_locuri),numar_masa(m.numar_masa),consum_minim(m.consum_minim)
    {
        pozitie=new char[strlen(m.pozitie)+1];
        strcpy(pozitie,m.pozitie);
    }
    Masa& operator=(const Masa& m)
    {
        if(this!=&m)
        {
            delete[] pozitie;
            nr_locuri=m.nr_locuri;
            numar_masa=m.numar_masa;
            consum_minim=m.consum_minim;
            pozitie=new char[strlen(m.pozitie)+1];
            strcpy(pozitie,m.pozitie);
        }
        return *this;
    }
    ~Masa()
    {
        delete[] pozitie;
    }

    void set_nr_locuri(const int nr_locuri)
    {
        this->nr_locuri=nr_locuri;
    }

    void set_numar_masa(const int numar_masa)
    {
        this->numar_masa=numar_masa;
    }
    void set_consum_minim(const double consum_minim)
    {
        this->consum_minim=consum_minim;
    }
    void set_pozitie(const char* pozitie)
    {
        delete[] this->pozitie;
        this->pozitie=new char[strlen(pozitie)+1];
        strcpy(this->pozitie,pozitie);
    }
    int get_nr_locuri()const
    {
        return nr_locuri;
    }
    int get_numar_masa()const
    {
        return numar_masa;
    }
    double get_consum_minim()const
    {
        return consum_minim;
    }
    const char* get_pozitie() const
    {
        return pozitie;
    }
    bool masa_premium() const
    {
        if(este_pe_terasa() && consum_minim>=200)
            return true;
        else
            return false;

    }
    double consum_persoana()const
    {
        if(nr_locuri==0)
            return 0;
        return consum_minim/nr_locuri;
    }
};

///supraincarcarea operatorului de scriere cu ajutorul getterilor din clasa Masa

std::ostream& operator <<(std::ostream& output,const Masa& m)
{
    output<<"Numar de locuri al acestei mese este:"<<m.get_nr_locuri()<<'\n';
    output<<"Numarul mesei este:"<<m.get_numar_masa()<<'\n';
    output<<"Consumul minim necesar este:"<<m.get_consum_minim()<<'\n';
    output<<"Pozitia mesei:"<<m.get_pozitie()<<'\n';
    output<<'\n';
    return output;

}

class Rezervare

{
    Client* clienti;
    Masa masa;
    char* ora_rezervare;
    int numar_clienti;
    int id_rezervare;///va fi incrementat doar pentru constructori de initializare si cu parametrii(folosit pentru a identifica rezervarile cu care vom lucra in programul main pentru a le putea identifica)In constr copiere si op atribuire doar il vom copia
    static int generat_id;
    static int numar_rezervari;///numarul de obiecte de tip rezervare create

    bool clienti_generos()const
    {
        for(int i=0; i<numar_clienti; i++)
            if(clienti[i].get_buget()<800)
                return false;
        return true;
    }
    bool ora_valida(const char* ora)const
    {
        if(ora==nullptr)
            return false;
        if(strlen(ora)!=5)
            return false;
        if(ora[2]!=':')
            return false;
        int lg=strlen(ora);
        for(int i=0; i<lg; i++)
        {
            if(i!=2)
            {
                if(ora[i]<'0' || ora[i]>'9')
                    return false;
            }
        }
        int hh=(ora[0]-'0')*10+(ora[1]-'0');
        int mm=(ora[3]-'0')*10+(ora[4]-'0');
        if(hh<0 || hh>23)
            return false;
        if(mm<0 || mm>59)
            return false;
        return true;
    }

    int proprietar_rezervare()const
    {
        int poz=-1,nr=0;
        for(int i=0; i<numar_clienti; i++)
            if(clienti[i].telefon_valid())
            {
                nr++;
                if(nr==1)
                {
                    poz=i;
                }
            }
        if(nr==1)
            return poz;
        return -1;

    }

    double buget_total()const
    {
        double sum=0;
        for(int i=0; i<numar_clienti; i++)
        {
            sum+=clienti[i].get_buget();
        }
        return sum;
    }

    void sortare_clienti_buget(Client* v,int n)const
    {
        for(int i=0; i<n-1; i++)
            for(int j=i+1; j<n; j++)
                if(v[i].get_buget()<v[j].get_buget())
                {
                    Client aux=v[i];
                    v[i]=v[j];
                    v[j]=aux;
                }
    }

public:
    Rezervare():numar_clienti(0)
    {
        clienti=nullptr;
        ora_rezervare=new char[strlen("Necunoscuta")+1];
        strcpy(ora_rezervare,"Necunoscuta");
        numar_rezervari++;
        id_rezervare=++generat_id;


    }
    Rezervare(const Client* clienti,const int numar_clienti,const Masa& masa,const char* ora_rezervare):numar_clienti(numar_clienti),masa(masa)
    {
        this->clienti=new Client[numar_clienti];
        for(int i=0; i<numar_clienti; i++)
            this->clienti[i]=clienti[i];
        if(ora_valida(ora_rezervare))
        {
            this->ora_rezervare=new char[strlen(ora_rezervare)+1];
            strcpy(this->ora_rezervare,ora_rezervare);
        }
        else
        {
            this->ora_rezervare=new char[strlen("Necunoscuta")+1];
            strcpy(this->ora_rezervare,"Necunoscuta");
        }
        numar_rezervari++;
        id_rezervare=++generat_id;

    }
    Rezervare(const Rezervare& r):numar_clienti(r.numar_clienti),masa(r.masa),id_rezervare(r.id_rezervare)
    {
        clienti=new Client[r.numar_clienti];
        for(int i=0; i<r.numar_clienti; i++)
            clienti[i]=r.clienti[i];
        ora_rezervare=new char[strlen(r.ora_rezervare)+1];
        strcpy(ora_rezervare,r.ora_rezervare);
        numar_rezervari++;

    }
    Rezervare& operator=(const Rezervare& r)
    {
        if(this!=&r)
        {
            delete[] clienti;
            delete[] ora_rezervare;
            numar_clienti=r.numar_clienti;
            clienti=new Client[r.numar_clienti];
            for(int i=0; i<r.numar_clienti; i++)
                clienti[i]=r.clienti[i];
            masa=r.masa;
            ora_rezervare=new char[strlen(r.ora_rezervare)+1];
            strcpy(ora_rezervare,r.ora_rezervare);
            id_rezervare=r.id_rezervare;
        }
        return *this;
    }
    ~Rezervare()
    {
        delete[] clienti;
        delete[] ora_rezervare;

    }
    void set_ora_rezervare(const char* ora_rezervare)
    {
        if(ora_valida(ora_rezervare))
        {
            delete[]this->ora_rezervare;
            this->ora_rezervare=new char[strlen(ora_rezervare)+1];
            strcpy(this->ora_rezervare,ora_rezervare);
        }
        else
            std::cout<<"Ora invalida!"<<'\n';
    }
    const char* get_ora_rezervare() const
    {
        return ora_rezervare;
    }
    int get_id_rezervare()const
    {
        return id_rezervare;
    }
    static int get_numar_rezervari()
    {
        return numar_rezervari;
    }
    void afisare_clienti_sortati_buget()const
    {
        Client* copie=new Client[numar_clienti];
        for(int i=0; i<numar_clienti; i++)
            copie[i]=clienti[i];
        sortare_clienti_buget(copie,numar_clienti);
        std::cout<<"Clientii sortati descrescator dupa buget pentru rezervarea cu id-ul "<<id_rezervare<<"!"<<'\n';
        std::cout<<'\n';
        for(int i=0; i<numar_clienti; i++)
            std::cout<<copie[i]<<std::endl;
        delete[] copie;

    }

    bool rezervare_valida()const
    {
        if(numar_clienti==0 || masa.get_nr_locuri()==0)
            return false;
        if(numar_clienti>masa.get_nr_locuri())
            return false;
        if(buget_total()<masa.get_consum_minim())
            return false;
        if(proprietar_rezervare()==-1)
            return false;
        int poz=proprietar_rezervare();
        if(strcmp(clienti[poz].get_ora_sosire(),ora_rezervare)>0)
            return false;
        return true;
    }

    void rezerv_bugetmare()const
    {
        if(clienti_generos() && numar_clienti>=4 && masa.masa_premium())
            std::cout<<"Rezervare VIP!"<<'\n';
        else
            std::cout<<"Rezervare normala."<<'\n';

    }
    const char* client_buget_maxim()const
    {
        int poz=-1;
        double mx=-1;
        for(int i=0; i<numar_clienti; i++)
            if(clienti[i].get_buget()>mx)
            {
                poz=i;
                mx=clienti[i].get_buget();
            }
        if(poz!=-1)
            return clienti[poz].get_nume();
        return "Nu exista clienti!";
    }

    bool beneficiaza_reducere() const
    {
        if(!rezervare_valida())
            return false;
        if(numar_clienti < 3)
            return false;
        if(buget_total() < 1500)
            return false;
        if(strcmp(ora_rezervare, "20:00") > 0)
            return false;

        return true;
    }

    friend std::ostream& operator <<(std::ostream& out,const Rezervare& r);

};
int Rezervare::numar_rezervari=0;
int Rezervare::generat_id=0;

///supraincarcarea operatorului de scriere cu ajutorul unei functii friend

std::ostream& operator<<(std::ostream& out,const Rezervare& r)
{
    out<<"Rezervarea cu numarul "<<r.id_rezervare<<"!"<<'\n';
    out<<'\n';
    out<<"Rezervarea a fost facuta la ora:"<<r.ora_rezervare<<"!"<<'\n';
    out<<'\n';
    out<<"Clientii sunt in numar de:"<<r.numar_clienti<<"!"<<'\n';
    out<<'\n';
    for(int i=0; i<r.numar_clienti; i++)
    {
        out<<r.clienti[i];
        out<<'\n';
    }
    out<<"Masa acestei rezervari:"<<'\n';
    out<<r.masa;
    out<<'\n';
    return out;
}

int main()
{
    ///Creare rezervare 1

    Client c1("Ion Popescu",7,1000.87,"Necunoscut","20:30");
    Client c2("Maria Ionescu",3,499.99,"Necunoscut","19:45");
    Client c3("Eduard Ungureanu",8,285,"0771170533","19:30");
    c1.marire_buget(50);
    Client lista1_clienti[3] = {c1, c2, c3};
    Masa m1(4,10,200,"terasa");
    Rezervare r1(lista1_clienti, 3, m1, "19:30");
    std::cout<<r1;
    std::cout<<"---------------------\n";

///Creare rezervare 2

    Client c4("Popescu Mihai",1,121,"0744561232","19:59");
    c4.marire_buget(89);
    Client c5("Stan Ana",6,2000,"0711223453","20:30");
    Client lista2_clienti[2]= {c4,c5};
    Masa m2(2,3,541,"interior");
    Rezervare r2(lista2_clienti,2,m2,"20:00");
    std::cout<<r2;
    std::cout<<"---------------------\n";

///Creare o a treia rezervare care insa va fi stearsa de destructor dupa terminarea setului de instructiuni dintre acolade

    {
        Client c6,c7;
        c6.set_nume("Corina Ioana");
        c6.set_id_client(27);
        c6.set_buget(456);
        c6.set_telefon("0744362315");
        c6.set_ora_sosire("22:00");
        c7.set_nume("Matei Patru");
        c7.set_id_client(16);
        c7.set_buget(444);
        c7.set_telefon("Necunoscut");
        c7.set_ora_sosire("22:04");
        Client lista3_clienti[2]= {c6,c7};
        Masa m3;
        m3.set_nr_locuri(2);
        m3.set_numar_masa(13);
        m3.set_consum_minim(120.43);
        m3.set_pozitie("interior");
        Rezervare r3(lista3_clienti,2,m3,"Necunoscuta");
        r3.set_ora_rezervare("22:00");
        std::cout<<r3;
        std::cout<<"---------------------\n";
    }

///Creare rezervare 4

    Client c8("Matei Ioana",10,800.01,"0773451977","21:30");
    Client c9("Stefania Adelina",22,821,"Necunoscut","21:15");
    Client c10("Badea Ionut",12,911,"Necunoscut","22:00");
    Client c11("Negut Ovidiu",9,975.50,"Necunoscut","21:30");
    Client lista4_clienti[4]= {c8,c9,c10,c11};
    Masa m4(4,1,231,"terasa");
    Rezervare r4(lista4_clienti,4,m4,"21:30");
    std::cout<<r4;

    std::cout<<"---------------------\n";

///Creare rezervare 5 cu constructorul default

    Rezervare r5;
    std::cout<<r5;

    std::cout<<"---------------------\n";

///Testare persoane cu telefon valid din rezervarea cu numarul 1

    std::cout<<"Persoanele cu telefon valid din Rezervarea 1:"<<'\n';
    for(int i=0; i<3; i++)
    {
        if(lista1_clienti[i].telefon_valid())
        {
            std::cout<<"Nume: " <<lista1_clienti[i].get_nume()<<'\n';
            std::cout<<"ID: " <<lista1_clienti[i].get_id_client()<<'\n';
            std::cout<<"Buget: " <<lista1_clienti[i].get_buget()<<'\n';
            std::cout<<"Telefon: " <<lista1_clienti[i].get_telefon()<<'\n';
            std::cout<<"\n";
        }
    }
    std::cout<<"---------------------\n";

///Afisare clientii sortati descrescator dupa buget din rezervarea 4

    r4.afisare_clienti_sortati_buget();

    std::cout<<"---------------------\n";

///Afisare mese premium

    std::cout<<"Mesele premium sunt:"<<'\n';
    std::cout<<'\n';
    Masa mese[3]= {m1,m2,m4};
    int nr=0,n=sizeof(mese)/sizeof(mese[0]);
    for(int i=0; i<n; i++)
        if(mese[i].masa_premium())
        {
            nr++;
            std::cout<<"Numarul de locuri: "<<mese[i].get_nr_locuri()<<'\n';
            std::cout<<"Numarul mesei: "<<mese[i].get_numar_masa()<<'\n';
            std::cout<<"Consumul minim: "<<mese[i].get_consum_minim()<<'\n';
            std::cout<<"Pozitia: "<<mese[i].get_pozitie()<<'\n';
            std::cout<<'\n';
        }

    std::cout<<"Numarul de mese premium rezervate este:"<<nr<<'\n';
    std::cout<<'\n';

    std::cout<<"---------------------\n";

///Afisare consum pentru fiecare persoana de la fiecare masa in medie

    std::cout<<"Consum persoana pentru fiecare masa!"<<'\n';
    std::cout<<'\n';
    for(int i=0; i<n; i++)
        std::cout<<"Masa cu numarul "<<mese[i].get_numar_masa()<<": "<<mese[i].consum_persoana()<<'\n';
    std::cout<<'\n';

    std::cout<<"---------------------\n";

///Pastrarea rezervarilor valide(in principiu cele care nu sunt realizate cu constructorul de initializare)

    std::cout<<"Rezervarile valide cu care vom lucra! "<<'\n';
    std::cout<<'\n';
    Rezervare rezervari[4]= {r1,r2,r4,r5};
    Rezervare rezervari_valide[4];
    int n1=sizeof(rezervari)/sizeof(rezervari[0]),numar_rez_valide=0,poz=0;
    for(int i=0; i<n1; i++)
    {
        if(rezervari[i].rezervare_valida())
        {
            rezervari_valide[poz++]=rezervari[i];
            numar_rez_valide++;
        }
    }
    for(int i=0; i<numar_rez_valide; i++)
        std::cout<<"Rezervarea cu id-ul "<<rezervari_valide[i].get_id_rezervare()<<'\n';
    std::cout<<'\n';

    std::cout<<"----------------------\n";

///Clientul cu cel mai mare buget din fiecare rezervare

    std::cout<<"Clientul cu bugetul cel mai mare din fiecare rezervare:"<<'\n';
    std::cout<<'\n';
    for(int i=0; i<numar_rez_valide; i++)
        std::cout<<"Din rezervarea "<<rezervari_valide[i].get_id_rezervare()<<" care are loc la ora "<<rezervari_valide[i].get_ora_rezervare()<<": "<<rezervari_valide[i].client_buget_maxim()<<'\n';

    std::cout<<'\n';

    std::cout<<"---------------------\n";

///Tipul rezervarii(vip/normala)

    std::cout<<"Tipul rezervarii:"<<'\n';
    std::cout<<'\n';
    for(int i=0; i<numar_rez_valide; i++)
    {
        std::cout<<"Rezervarea cu id-ul "<<rezervari_valide[i].get_id_rezervare()<<":";
        rezervari_valide[i].rezerv_bugetmare();
        std::cout<<'\n';
    }

    std::cout<<"---------------------\n";

///Rezervarile care beneficiaza de reducere
    std::cout<<'\n';
    std::cout<<"Rezervarile care beneficiaza de reducere:"<<'\n';
    std::cout<<'\n';
    for(int i=0;i<numar_rez_valide;i++)
    {
        if(rezervari_valide[i].beneficiaza_reducere())
            std::cout<<"Rezervarea cu id-ul "<<rezervari_valide[i].get_id_rezervare()<<" beneficiaza de reducere!"<<'\n';
    }
    std::cout<<'\n';
    std::cout<<"---------------------\n";

///Numarul de obiecte de tip rezervare create(constructor default,copiere,cu parametrii)

    std::cout<<"Numarul de obiecte de tip rezervari create pe parcursul programului este de:"<<Rezervare::get_numar_rezervari();

    return 0;
}
