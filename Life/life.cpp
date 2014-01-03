//life.cpp
#include "Life.h"

using namespace std;

/*----------------------------------------------------*/
life::life() //tworzenie tablicy - swiata
{
    try
            {
                 cell= new bool*[H];
            }
            catch(bad_alloc)
            {
                cout<<"Blad akolacji";
            };

    for(int i=0;i<H;i++)
    {
        try
            {
                cell[i]=new bool[L];
            }
            catch(bad_alloc)
            {
                cout<<"Blad akolacji";
            };

        for(int j=0;j<L;j++) //swiat startowy- wszystko martwe
            cell[i][j]=false;
    }

}

/*----------------------------------------------------*/
life::~life() //destruktor usuwajacy swiat tworzony dynamicznie
{
    for(int i=0;i<H;i++)
        delete [] cell[i];
    delete []cell;
}

/*----------------------------------------------------*/
void life::show() //wyswietlanie swiata
{
    if(flag) //modul przepisujacy swiat do pliku
    {

        fstream file;
        file.open(fname,ios::out | ios::app);
        for(int i=0; i<H; i++)
        {
            for(int j = 0; j<L; j++)
            {
                if(cell[i][j])
                {
                    if(file.good()==true)
                    {
                        file<<"0 ";

                    }

                }

                else
                {
                    if(file.good()==true)
                    {
                        file<<". ";

                    }
                }


            }
            if(file.good()==true)
            {
                file<<endl;
            }

        }
        if(file.good()==true)
            file<<"----------------------------------"<<endl;
       file.close();
    }

//modul wypisujacy na ekran
     for(int i=0; i<H; i++)
     {
         for(int j = 0; j<L; j++)
        {
            if(cell[i][j])
            {
                cout<<"0 ";
            }

            else
            {
                cout<<". ";
            }


        }
        cout<<endl;
     }
     cout<<"----------------------------------"<<endl;

}

/*----------------------------------------------------*/
void life::set()
{
    char line[6];
    int i=0,j=0;

    //stara wersja uzywajaca scanf
    cout<<"czy chcesz wpisac wspolrzedne? (y/n)"<<endl;
    cin>>line;
   /* while(line!='n')
    {
        scanf("%d %d",&i,&j);
        cell[i][j]=true;
        cout<<"kolejne? (y/n)"<<endl;
        cin>>line;
    }
*/

//nowa wersja wczytujaca do napotkania q
    cout<<"czy chcesz wpisac wspolrzedne? (y/n)"<<endl;
    cin>>line;
    if(line[0]=='y')
    {




        cout<<"Podaj wspolrzedne. aby zakonczyc wcisnij q"<<endl;
        cin.getline(line,6);
        while(line[0]!='q')
        {
            int r;
            for(r=0;line[r]!=' ';r++) //wyciagnie pierwszej liczby
            {
                if(line[r+1]!=' ')
                    i+=(line[r]-'0')*10;
                else
                    i+=(line[r]-'0');
            }
            for(r++;line[r]!='\0';r++)  //wyciaganie drugiej liczby
            {
                if(line[r+1]!='\0')
                    j+=(line[r]-'0')*10;
                else
                    j+=(line[r]-'0');
            }
            if(i>=0&&i<H&&j>=0&&j<L) //ustawianie wartosci dla wczytanej komorki
                cell[i][j]=true;
            else
                cout<<"Niepoprawne wspolrzedne. Wpisz ponownie"<<endl;

            cin.getline(line,6);

        }
    }
    else
        prepared();


    //wybor opcji zapisania do pliku
    cout<<"czy chcesz zapisywac do pliku? (y/n)"<<endl;
    cin>>line;
    if(line[0]=='y')
    {
        flag=true;
        cout<<"podaj nazwe pliku"<<endl;
        cin>>fname;

    }
    else
        flag=false;

}


/*----------------------------------------------------*/
//zliczanie liczby sasiadow
int life::count(int i, int j)
{
    int co=0;
    for(int k=i-1;k<i+2;k++)
    {
        for(int w=j-1;w<j+2;w++)
            if(k>=0 && k<H && w>=0 && w<L)
                if(k!=i || w!=j)
                    if(cell[k][w])
                        co++;

    }

    return co;
}

/*----------------------------------------------------*/
//tworzenie nowego pokolenia
void life::generation()
{
    bool** temp; //generacja nowego swiata

    try
            {
                temp=new bool*[H];
            }
            catch(bad_alloc)
            {
                cout<<"Blad akolacji";
            };


    for(int i=0;i<H;i++)
    {
        try
            {
                temp[i]=new bool[L];
            }
            catch(bad_alloc)
            {
                cout<<"Blad akolacji";
            };
    }

    int c; //zmienna opisujaca ilosc sasiadow

    for(int i=0; i<H; i++)
    {
        for(int j=0; j<L; j++)
        {
            c=count(i,j);
            cout<<c;
            if(cell[i][j]) //jesli zywa
            {
                if(c>3 || c<2) //kiedy umiera
                {
                    temp[i][j]=false;
                }
                else
                {
                    temp[i][j]=cell[i][j];
                }
            }
            else //jesli martwa
            {
                if(c==3) //kiedy sie rodzi
                {
                    temp[i][j]=true;
                }
                else
                    temp[i][j]=cell[i][j];
            }

            c=0;
        }
        cout<<endl;
    }

    this->~life(); //jawne wywolanie destruktora
    cell=temp;      //zamiana swiatow. stary -> nowy

}

/*----------------------------------------------------*/
//metoda wywolujaca cala procedure wraz z opoznieniem
void life::proceed()
{

    set();
    while(true)
    {
        show();
        generation();
        usleep(500000);

    }
}

/*----------------------------------------------------*/
void life::prepared()
{
    char a;
    cout<<"Czy chcesz wczytac gotowy schemat? (y/n"<<endl;
    cin>>a;
    if(a=='y')
    {
        cout<<"Wybierz jedna z opcji:"<<endl<<"1. Szybowiec"<<endl<<"..."<<endl;
        cin>>a;
    switch(a)
    {
        case '1':

                cell[2][0]=true;
                cell[2][1]=true;
                cell[2][2]=true;
                cell[1][2]=true;
                cell[0][1]=true;
                break;

        default:

                cout<<"Nic nie wybrano"<<endl;
                break;

    }

    }


}
