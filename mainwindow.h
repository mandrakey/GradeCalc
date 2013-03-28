#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#include "programoptions.h"
#include "model/institution.h"
#include "exceptions/uninitializedexception.h"

namespace po = boost::program_options;

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

    void loadData();
    void showCourses(QString& studyCourse);
};

#endif // MAINWINDOW_H
