#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include <iostream>

#include "programoptions.h"
#include "model/institution.h"
#include "model/gradetablemodel.h"
#include "exceptions/uninitializedexception.h"

namespace po = boost::program_options;

using std::cout;
using std::endl;

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
    QList<Institution*> mInstitutions;
    Institution *mCurrentInstitution;
    StudyCourse *mCurrentStudyCourse;
    GradeTableModel *mGradeTableModel;

    void loadData();
};

#endif // MAINWINDOW_H
