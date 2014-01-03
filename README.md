Conway's Game of Life

usuń:  

    namespace Ui {
    class MainWindow;
    }
    
    #include "ui_mainwindow.h",

    ui(new Ui::MainWindow),
    
    ui->setupUi(this);
    

    MainWindow::~MainWindow()
    {
        delete ui; //to
    }

zamien MainWindow->GUI
