#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGroupBox>
#include <QWidget>
#include <QFormLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QHeaderView>
#include <QSpacerItem>
#include <QVector>
#include <QLCDNumber>
#include <QTime>
#include <QComboBox>



#include "gamealg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QHBoxLayout *WindowLayout;
    QTableWidget *LifeField;
    QGroupBox *OptionGroup;
    bool isSimulationOn;
    GameAlg Algorithm;


QLabel * NewLabel(QString Text);
const QFont NewFont();

    //************GrupBox**************//
    QFormLayout * GroupLayout;
    QSpinBox * ColumnChanger;
    QSpinBox * RowChanger;
    QPushButton * Starter;
    QPushButton * OneMove;
    QPushButton * Quiter;

    QPushButton * Generator;
    QPushButton * Cleaner;
    QVector <QSpacerItem *> Spacers;
    QLCDNumber * LifeFeed;
    QLCDNumber * Iteration;
    QComboBox *comboBox;



    void InitGroupBox();
    void Run();//----------------------
    void SimulationOn();
    void SimulationOff();

    //************TableWidget**************//

    int LifeCount;
    int IterationCount;

    void InitLifeField();
    void ItemPopulated(QTableWidgetItem * item);
    void ItemEmpty(QTableWidgetItem* item);
 //   void StatusUpdate(int feeds, int iterations);

private slots:
    //void ChangeTableWidget();

    void StatusUpdate(int feeds, int iterations);
    void GenerateField();
    void CleanNow();
    void FeedCell(int row, int column);
    void RowsChanged();
    void ColumnsChanged();
    void SimulationTrigger();
    void FeedCell(int row, int column, bool life);
    void Prepared(QString name);

signals:
    void CellsChanged(int row, int column);
    void CellsChanged(int row, int column, bool life);
    void StartSimulation();
    void StopSimulation();
    void FeedsChanger(int f);
};

#endif // MAINWINDOW_H
