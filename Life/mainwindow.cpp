#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont f("Helvetica",10);
    this->setFont(f);

    LifeField = 0;
    OptionGroup = 0;
    GroupLayout = 0;
    isSimulationOn = false;
    LifeCount = 0;
    IterationCount = 0;


    WindowLayout= new QHBoxLayout;

    QWidget * mycentralwidget = new QWidget;
    mycentralwidget->setLayout(WindowLayout);

    this->setCentralWidget(mycentralwidget);
    this->setWindowTitle("Gra w Życie");

    connect(this, SIGNAL(CellsChanged(int,int)), &Algorithm, SLOT(NewDimension(int,int)));
    connect(&Algorithm, SIGNAL(CellChanged(int,int,bool)),this, SLOT(FeedCell(int,int,bool)));
    connect(&Algorithm, SIGNAL(ChangeStatus(int,int)), this, SLOT(StatusUpdate(int,int)));
    connect(this, SIGNAL(CellsChanged(int,int,bool)), &Algorithm, SLOT(CellModified(int,int,bool)));
    connect(this, SIGNAL(FeedsChanger(int)), &Algorithm, SLOT(FeedsStatus(int)));
    //connect(&Algorithm, SIGNAL(Clear()),this, SLOT(CleanNow()));

    InitLifeField();
    InitGroupBox();
    RowsChanged();
    ColumnsChanged();


this->setMinimumSize(700, 480);

    connect(ColumnChanger, SIGNAL(valueChanged(int)), this, SLOT(ColumnsChanged()));
    connect(RowChanger, SIGNAL(valueChanged(int)), this, SLOT(RowsChanged()));
    connect(Quiter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(Generator, SIGNAL(clicked()),this, SLOT(GenerateField()) );
    connect(Cleaner, SIGNAL(clicked()),this, SLOT(CleanNow()));
    connect(LifeField, SIGNAL(cellClicked(int, int)), this, SLOT(FeedCell(int, int)));
    connect(Starter,SIGNAL(clicked()),this ,SLOT(SimulationTrigger()));
    connect(OneMove,SIGNAL(clicked()),&Algorithm ,SLOT(SingleStep()));
    connect(comboBox, SIGNAL(activated(QString)), this, SLOT(Prepared(QString)));

    connect(this,SIGNAL(StartSimulation()), &Algorithm, SLOT(SetTimer()));
    connect(this, SIGNAL(StopSimulation()),&Algorithm, SLOT(StopTimer()));


    qsrand(QTime::currentTime().msecsTo(QTime(0,0,0,0)));

}

void MainWindow::InitGroupBox()
{
    if((GroupLayout!= 0)||(OptionGroup != 0)|| (WindowLayout == 0)) return;

    OptionGroup= new QGroupBox;
    OptionGroup->setTitle("Opcje");

    GroupLayout= new QFormLayout(OptionGroup);
    ColumnChanger= new QSpinBox;
    RowChanger= new QSpinBox;
    Starter = new QPushButton("START/STOP ");
    Generator = new QPushButton("Losuj świat");
    Cleaner = new QPushButton("Wyczyść");
    OneMove = new QPushButton("Generuj pojedyncze pokolenie");
    comboBox = new QComboBox;


    LifeFeed = new QLCDNumber;
    Iteration = new QLCDNumber;

    Quiter = new QPushButton("Wyjdź");

    Starter->setEnabled(false);
    OneMove->setEnabled(false);

    GroupLayout->addRow(NewLabel("Kolumn:"),ColumnChanger);
    GroupLayout->addRow(NewLabel("Wierszy:"),RowChanger);
    OptionGroup->setMinimumWidth(120);

    ColumnChanger->setMinimum(10);
    ColumnChanger->setMaximum(300);

    RowChanger->setMinimum(10);
    RowChanger->setMaximum(300);

    RowChanger->setValue(40);
    ColumnChanger->setValue(40);

    Spacers.append(new QSpacerItem(10,15));
    GroupLayout->addItem(Spacers.last());
    LifeFeed->setSegmentStyle(QLCDNumber::Flat);
    Iteration->setSegmentStyle(QLCDNumber::Flat);
    GroupLayout->addRow("Żyje:",LifeFeed);
    GroupLayout->addRow("Kroków:",Iteration);
    LifeFeed->setDigitCount(7);
    Iteration->setDigitCount(7);

    Spacers.append(new QSpacerItem(10,50));
    GroupLayout->addItem(Spacers.last());
    GroupLayout->setWidget(GroupLayout->rowCount(),QFormLayout::SpanningRole, Generator);
    comboBox->addItem(tr("Glider"));
    comboBox->addItem(tr("Gun"));
    comboBox->addItem(tr("Blinker"));
    comboBox->addItem(tr("Star"));
    comboBox->addItem(tr("Cross"));
    comboBox->addItem(tr("Clock"));
    comboBox->addItem(tr("Pinwheel"));
    comboBox->addItem(tr("French Kiss"));
    comboBox->addItem(tr("Fumarole"));
    comboBox->addItem(tr("Fox"));
    comboBox->addItem(tr("Pulsar"));

GroupLayout->addRow("Lub wybierz szablon",comboBox);

    Spacers.append(new QSpacerItem(10,20));
    GroupLayout->addItem(Spacers.last());
    GroupLayout->setWidget(GroupLayout->rowCount(),QFormLayout::SpanningRole, OneMove);

    Spacers.append(new QSpacerItem(10,20));
     GroupLayout->addRow("Symulacja",Starter);
    //GroupLayout->addItem(Spacers.last());
    //GroupLayout->setWidget(GroupLayout->rowCount(),QFormLayout::SpanningRole, Starter);

    Spacers.append(new QSpacerItem(10,50));
    GroupLayout->addItem(Spacers.last());
    GroupLayout->setWidget(GroupLayout->rowCount(),QFormLayout::SpanningRole, Cleaner);

    Spacers.append(new QSpacerItem(10,50));
    GroupLayout->addItem(Spacers.last());
    GroupLayout->setWidget(GroupLayout->rowCount(),QFormLayout::SpanningRole, Quiter);

    WindowLayout->addWidget(OptionGroup);

}

void MainWindow::InitLifeField()
{
    if((LifeField!= 0) || (WindowLayout == 0)) return;
    LifeField = new QTableWidget;

    LifeField->setShowGrid(true);
    LifeField->setSelectionMode(QTableWidget::NoSelection);
    LifeField->horizontalHeader()->hide();
    LifeField->verticalHeader()->hide();


    WindowLayout->addWidget(LifeField);
}

void MainWindow::RowsChanged()
{
    if(LifeField->rowCount() == RowChanger->value()) return;

    int oldRows = LifeField-> rowCount();
    int lifeCropped = 0;
    QTableWidgetItem *item;

    //gdy wierszyjest mniej
    for(int i=RowChanger->value(); i< oldRows; i++)
    {
        for(int j=0; j< LifeField->columnCount();j++)
        {
            item = LifeField->item(i,j);
            if(item == 0) continue;
            if(item->data(Qt::UserRole)== true) ++lifeCropped;
        }
    }
    if(lifeCropped > 0) emit StatusUpdate( (LifeCount - lifeCropped), IterationCount);

    LifeField->setRowCount(RowChanger->value());

    //Gdy wierszy jest więcej
    for( int i = oldRows; i< RowChanger->value();i++)
    {
        LifeField->setRowHeight(i,10);
    }

    emit CellsChanged(LifeField->rowCount(),LifeField->columnCount());
}

void MainWindow::ColumnsChanged()
{
    if(LifeField->columnCount() == ColumnChanger->value()) return;

    int oldColumns = LifeField->columnCount();
    int lifeCropped = 0;
    QTableWidgetItem *item;

    //gdy kolumn jest mniej
    for(int i=ColumnChanger->value(); i< oldColumns; i++)
    {
        for(int j=0; j< LifeField->rowCount();j++)
        {
            item = LifeField->item(j,i);
            if(item == 0) continue;
            if(item->data(Qt::UserRole)== true) ++lifeCropped;
        }
    }
    if(lifeCropped > 0) emit StatusUpdate((LifeCount - lifeCropped), IterationCount);

    LifeField->setColumnCount(ColumnChanger->value());

    //Gdy wierszy jest więcej
    for( int i = oldColumns; i< ColumnChanger->value();i++)
    {
        LifeField->setColumnWidth(i,10);
    }

    emit CellsChanged(LifeField->rowCount(),LifeField->columnCount());

}



void MainWindow::CleanNow()
{
    LifeField->clear();

    Starter->setEnabled(false);
    OneMove->setEnabled(false);
    Generator->setEnabled(true);
    ColumnChanger->setEnabled(true);
    RowChanger->setEnabled(true);

    LifeFeed->display(0);
    Iteration->display(0);
    LifeCount = 0;
    IterationCount = 0;

    Algorithm.Restart();
}

void MainWindow::GenerateField()
{
    bool good = Algorithm.Generate();
    if(good == true)
    {
        Starter->setEnabled(true);
        OneMove->setEnabled(true);
    }

}

void MainWindow::Run()
{

}

void MainWindow::SimulationTrigger()
{
    isSimulationOn= !isSimulationOn;
    isSimulationOn ? SimulationOn() : SimulationOff();
}

void MainWindow::SimulationOn()
{
    OneMove->setEnabled(false);
    Cleaner->setEnabled(false);
    Generator->setEnabled(false);
    ColumnChanger->setEnabled(false);
    comboBox->setEnabled(false);
    RowChanger->setEnabled(false);
    Starter->setEnabled(true);

    emit StartSimulation();
}

void MainWindow::SimulationOff()
{
    OneMove->setEnabled(true);
    Cleaner->setEnabled(true);
    Generator->setEnabled(true);
    ColumnChanger->setEnabled(true);
    comboBox->setEnabled(true);
    RowChanger->setEnabled(true);

    emit StopSimulation();

}

void MainWindow::StatusUpdate(int feeds, int iterations)
{
    LifeFeed->display(feeds);
    Iteration->display(iterations);
    LifeCount = feeds;
    IterationCount=iterations; //cos debil wymyslil

    if(!isSimulationOn) Starter->setEnabled(feeds);
    if(!isSimulationOn) OneMove->setEnabled(feeds);
    emit FeedsChanger(feeds);

}

void MainWindow::FeedCell(int row, int column)
{
    QTableWidgetItem * item = LifeField->item(row, column);
    bool populated;

    if(item == 0)
    {
        item = new QTableWidgetItem;
        LifeField->setItem(row, column, item);
        populated= false;
    }
    else populated= item->data(Qt::UserRole).toBool();

    if(populated == true)
    {
        ItemEmpty(item);
        --LifeCount;
    }
    else
    {
        ItemPopulated(item);        
        ++LifeCount;
    }

    emit StatusUpdate(LifeCount, IterationCount);
    emit CellsChanged(row, column, !populated);

}

void MainWindow::ItemPopulated(QTableWidgetItem *item)
{
    item->setData(Qt::UserRole, QVariant(true));
    item->setBackgroundColor(QColor("red"));
}

void MainWindow::ItemEmpty(QTableWidgetItem *item)
{
    item->setData(Qt::UserRole, QVariant(false));
    item->setBackgroundColor(QColor("white"));
}

void MainWindow::FeedCell(int row, int column, bool life)
{
    QTableWidgetItem * item = LifeField->item(row, column);


    if(item == 0)
    {
        item = new QTableWidgetItem;
        LifeField->setItem(row, column, item);

    }
    if(life == true)
    {
        ItemPopulated(item);
        LifeCount++;
    }
else
    {
        ItemEmpty(item);
        LifeCount--;
    }


    emit StatusUpdate(LifeCount, IterationCount);

}

void MainWindow::Prepared(QString name)
{
    CleanNow();
    if(name=="Glider")
    {
        ColumnChanger->setValue(40);
        RowChanger->setValue(40);
        FeedCell(0,1);
        FeedCell(1,2);
        FeedCell(2,0);
        FeedCell(2,1);
        FeedCell(2,2);
    }
    else
        if(name=="Gun")
        {
            ColumnChanger->setValue(40);
            RowChanger->setValue(40);
            FeedCell(5,1);
            FeedCell(6,1);
            FeedCell(5,2);
            FeedCell(6,2);
            FeedCell(5,11);
            FeedCell(6,11);
            FeedCell(7,11);
            FeedCell(4,12);
            FeedCell(8,12);
            FeedCell(3,13);
            FeedCell(3,14);
            FeedCell(9,13);
            FeedCell(9,14);
            FeedCell(6,15);
            FeedCell(4,16);
            FeedCell(8,16);
            FeedCell(5,17);
            FeedCell(6,17);
            FeedCell(7,17);
            FeedCell(6,18);
            FeedCell(3,21);
            FeedCell(3,22);
            FeedCell(4,21);
            FeedCell(4,22);
            FeedCell(5,21);
            FeedCell(5,22);
            FeedCell(2,23);
            FeedCell(6,23);
            FeedCell(1,25);
            FeedCell(2,25);
            FeedCell(6,25);
            FeedCell(7,25);
            FeedCell(3,35);
            FeedCell(3,36);
            FeedCell(4,35);
            FeedCell(4,36);
        }
    else
            if(name=="Blinker")
            {
                ColumnChanger->setValue(10);
                RowChanger->setValue(10);
                 FeedCell(2,1);
                 FeedCell(2,2);
                 FeedCell(2,3);
            }
    else if(name=="Star")
            {
                ColumnChanger->setValue(13);
                RowChanger->setValue(13);
                FeedCell(5,1);
                FeedCell(6,1);
                FeedCell(7,1);
                FeedCell(3,3);
                FeedCell(5,3);
                FeedCell(7,3);
                FeedCell(9,3);
                FeedCell(1,5);
                FeedCell(1,6);
                FeedCell(1,7);
                FeedCell(3,5);
                FeedCell(3,7);
                FeedCell(3,9);
                FeedCell(5,9);
                FeedCell(7,9);
                FeedCell(9,9);
                FeedCell(9,7);
                FeedCell(9,5);
                FeedCell(5,11);
                FeedCell(6,11);
                FeedCell(7,11);
                FeedCell(11,5);
                FeedCell(11,6);
                FeedCell(11,7);
            }
    else if(name=="Cross")
            {
                ColumnChanger->setValue(10);
                RowChanger->setValue(10);
                FeedCell(1,3);
                FeedCell(1,4);
                FeedCell(1,5);
                FeedCell(1,6);
                FeedCell(2,6);
                FeedCell(3,6);
                FeedCell(3,7);
                FeedCell(3,8);
                FeedCell(4,8);
                FeedCell(5,8);
                FeedCell(6,8);
                FeedCell(6,7);
                FeedCell(6,6);
                FeedCell(7,6);
                FeedCell(8,6);
                FeedCell(8,5);
                FeedCell(8,4);
                FeedCell(8,3);
                FeedCell(7,3);
                FeedCell(6,3);
                FeedCell(6,2);
                FeedCell(6,1);
                FeedCell(5,1);
                FeedCell(4,1);
                FeedCell(3,1);
                FeedCell(3,2);
                FeedCell(3,3);
                FeedCell(2,3);
            }
    else if(name=="French Kiss")
            {
                ColumnChanger->setValue(12);
                RowChanger->setValue(11);
                FeedCell(1,1);
                FeedCell(2,1);
                FeedCell(2,2);
                FeedCell(2,3);
                FeedCell(3,4);
                FeedCell(4,3);
                FeedCell(5,3);
                FeedCell(6,4);
                FeedCell(6,5);
                FeedCell(4,6);
                FeedCell(4,7);
                FeedCell(5,8);
                FeedCell(6,8);
                FeedCell(7,7);
                FeedCell(8,8);
                FeedCell(8,9);
                FeedCell(8,10);
                FeedCell(9,10);
            }
    else if(name=="Clock")
            {
                ColumnChanger->setValue(10);
                RowChanger->setValue(10);
                FeedCell(3,2);
                FeedCell(4,3);
                FeedCell(5,3);
                FeedCell(2,4);
                FeedCell(3,4);
                FeedCell(4,5);
            }
    else if(name=="Pinwheel")
            {
                ColumnChanger->setValue(12);
                RowChanger->setValue(12);
                FeedCell(3,4);
                FeedCell(3,5);
                FeedCell(3,6);
                FeedCell(3,7);
                FeedCell(4,3);
                FeedCell(5,3);
                FeedCell(6,3);
                FeedCell(7,3);
                FeedCell(8,4);
                FeedCell(8,5);
                FeedCell(8,6);
                FeedCell(8,7);
                FeedCell(4,8);
                FeedCell(5,8);
                FeedCell(6,8);
                FeedCell(7,8);
                FeedCell(5,6);
                FeedCell(6,7);
                FeedCell(7,5);
                FeedCell(4,0);
                FeedCell(4,1);
                FeedCell(5,0);
                FeedCell(5,1);
                FeedCell(0,6);
                FeedCell(0,7);
                FeedCell(1,6);
                FeedCell(1,7);
                FeedCell(6,10);
                FeedCell(6,11);
                FeedCell(7,10);
                FeedCell(7,11);
                FeedCell(10,4);
                FeedCell(10,5);
                FeedCell(11,4);
                FeedCell(11,5);

            }
    else if(name=="Fumarole")
            {
                ColumnChanger->setValue(10);
                RowChanger->setValue(10);
                FeedCell(2,4);
                FeedCell(2,5);
                FeedCell(3,2);
                FeedCell(4,2);
                FeedCell(5,2);
                FeedCell(6,3);
                FeedCell(7,3);
                FeedCell(7,1);
                FeedCell(8,1);
                FeedCell(8,2);
                FeedCell(3,7);
                FeedCell(4,7);
                FeedCell(5,7);
                FeedCell(6,6);
                FeedCell(7,6);
                FeedCell(8,7);
                FeedCell(8,8);
                FeedCell(7,8);
            }
    else if(name=="Fox")
            {
                ColumnChanger->setValue(10);
                RowChanger->setValue(10);
                FeedCell(4,1);
                FeedCell(4,2);
                FeedCell(3,3);
                FeedCell(1,5);
                FeedCell(2,5);
                FeedCell(3,6);
                FeedCell(6,3);
                FeedCell(5,5);
                FeedCell(6,5);
                FeedCell(5,7);
                FeedCell(6,7);
                FeedCell(7,7);
            }
    else if(name=="Pulsar")
            {
                ColumnChanger->setValue(15);
                RowChanger->setValue(15);
                FeedCell(1,3);
                FeedCell(1,4);
                FeedCell(1,5);
                FeedCell(1,9);
                FeedCell(1,10);
                FeedCell(1,11);
                FeedCell(13,3);
                FeedCell(13,4);
                FeedCell(13,5);
                FeedCell(13,9);
                FeedCell(13,10);
                FeedCell(13,11);
                FeedCell(6,3);
                FeedCell(6,4);
                FeedCell(6,5);
                FeedCell(6,9);
                FeedCell(6,10);
                FeedCell(6,11);
                FeedCell(8,3);
                FeedCell(8,4);
                FeedCell(8,5);
                FeedCell(8,9);
                FeedCell(8,10);
                FeedCell(8,11);
                FeedCell(3,1);
                FeedCell(4,1);
                FeedCell(5,1);
                FeedCell(9,1);
                FeedCell(10,1);
                FeedCell(11,1);
                FeedCell(3,6);
                FeedCell(4,6);
                FeedCell(5,6);
                FeedCell(9,6);
                FeedCell(10,6);
                FeedCell(11,6);
                FeedCell(3,8);
                FeedCell(4,8);
                FeedCell(5,8);
                FeedCell(9,8);
                FeedCell(10,8);
                FeedCell(11,8);
                FeedCell(3,13);
                FeedCell(4,13);
                FeedCell(5,13);
                FeedCell(9,13);
                FeedCell(10,13);
                FeedCell(11,13);
            }


}

QLabel* MainWindow::NewLabel(QString Text)
{
    QLabel *l = new QLabel;
    QFont font = NewFont();


    l->setFont(font);
    l->setText(Text);

    return l;
}

const QFont MainWindow::NewFont()
{
    QFont *font = new QFont;
    font->setFamily("Times news Roman");
    font->setBold(false);
    font->setPointSize(12);
    return *font;
}

MainWindow::~MainWindow()
{
    delete ui;
}

