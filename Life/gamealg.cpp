#include <gamealg.h>

GameAlg::GameAlg()
{
    Rows=0;
    Columns = 0;
    Feeds = 0;
    Iterations = 0;

    isRunning = false;

    connect(&Timer, SIGNAL(timeout()),this, SLOT(Step()));

}

void GameAlg::Restart()
{
    isRunning = false;
    Feeds = 0;
    Iterations = 0;

    Field.clear();
    NewDimension(Rows,Columns); // dodane bo po wyczyszczeniu sie kraszowal

}

bool GameAlg::Generate()
{

    bool done = false;
    int percent = 15;
    //QInputDialog ask;
    percent = QInputDialog::getInt(0,"Generowanie Życia", "Prawdopodobieństwo populacji/komorki w procentach:", percent, 10, 70, 1, &done, Qt::WindowCloseButtonHint);

    if(done == false) return done;

    Feeds = 0;

    for(int i=0; i< Field.size(); i++)
    {
        for(int j=0; j< Field.at(i).size(); j++)
        {

            (((qrand() % 100) + 1 <= percent) == true ) ? this->setCellLive(i,j) : this->setCellDead(i,j);
        }
    }

    //emit ChangeStatus(Feeds, Iterations);
    return done;
}

void GameAlg::NewDimension(int row, int column)
{
    Rows= row;
    Columns= column;
    Field.resize(Rows);
    for(int i=0; i<Rows; i++)
    {
        this->Field[i].resize(Columns);
    }
}

void GameAlg::CellModified(int row, int column, bool life)
{
    if(row > Rows) return;
    if(column > Columns) return;
    Field[row][column] = life;
}

void GameAlg::SetTimer()
{
    isRunning = true;
    Timer.setInterval(100);
    Timer.setSingleShot(true);
    Timer.start();

}

void GameAlg::StopTimer()
{
    Timer.stop();
    isRunning = false;
    Iterations=0;

}

void GameAlg::SingleStep()
{

    QVector< QVector< bool > > temp; //generacja nowego swiata

    temp.resize(Rows);


        for(int i=0;i<Rows;i++)
        {
            temp[i].resize(Columns);
        }

        for(int i=0; i<Rows; i++)
        {
            for(int j=0; j<Columns; j++)
            {
                temp[i][j]=Field[i][j];
            }
        }

        int c; //zmienna opisujaca ilosc sasiadow

        for(int i=0; i<Rows; i++)
        {
            for(int j=0; j<Columns; j++)
            {

                c=count(i,j, &temp);
                //cout<<c;
                if(Field[i][j]) //jesli zywa
                {
                    if(c>3 || c<2) //kiedy umiera
                    {
                        setCellDead(i,j);
                    }
                    else
                    {
                        setCellLive(i,j);
                    }
                }
                else //jesli martwa
                {
                    if(c==3) //kiedy sie rodzi
                    {
                        setCellLive(i,j);
                    }
                    else
                        setCellDead(i,j);

                }

                c=0;
            }
            //cout<<endl;
        }

        for(int i=0;i<Rows;i++)
        {
            temp[i].clear();
        }
        temp.clear(); //jawne wywolanie destruktora
              //zamiana swiatow. stary -> nowy



}

void GameAlg::Step()
{
    if(isRunning == false) return;
    SingleStep();
    if((Feeds >0 )) Iterations++;
    emit ChangeStatus(Feeds,Iterations);
    if((isRunning == true))
        SetTimer();


}

void GameAlg::setCellLive(int row, int column)
{
    if(Field[row][column] == true) return;
    Field[row][column] = true;
    ++Feeds;

    emit CellChanged(row, column, true);
    //emit ChangeStatus(this->Feeds,this->Iterations);
}

void GameAlg::setCellDead(int row, int column)
{
    if(Field[row][column] == false) return;
    Field[row][column] = false;
    Feeds--;

    emit CellChanged(row, column, false);
    //emit ChangeStatus(this->Feeds,this->Iterations);

}

int GameAlg::count(int i, int j, QVector< QVector< bool > > * temp)
{
    int co=0;
    for(int k=i-1;k<i+2;k++)
    {
        for(int w=j-1;w<j+2;w++)
            if(k>=0 && k<(*temp).size() && w>=0 && w<(*temp).at(i).size()) //Field.size() == H
                if(k!=i || w!=j)
                    if((*temp)[k][w])
                        co++;

    }
    return co;
}

void GameAlg::FeedsStatus(int f)
{
    Feeds=f;
}
