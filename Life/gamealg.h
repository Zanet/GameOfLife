#ifndef GAMEALG_H
#define GAMEALG_H

#include <QVector>
#include <QInputDialog>
#include <QObject>
#include <QTimer>

class GameAlg : public QObject

{
    Q_OBJECT
public:

    GameAlg();
    void Restart();
    bool Generate();
    int Feeds;

private:

    int Rows;
    int Columns;

    int Iterations;

    bool isRunning;
    QVector< QVector< bool > > Field;

    void setCellLive(int row, int column);
    void setCellDead(int row, int column);
    int count(int i, int j, QVector< QVector< bool > > * temp);

    QTimer Timer;


signals:
    void ChangeStatus(int feeds, int iteration);
    void CellChanged(int row, int column, bool life);


private slots:
    void NewDimension(int row, int column);
    void CellModified(int row, int column, bool life);
    void SetTimer();
    void StopTimer();
    void Step();
    void SingleStep();
    void FeedsStatus(int f);

};



#endif // GAMEALG_H
