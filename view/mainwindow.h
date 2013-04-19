#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTableWidget>
#include <QTranslator>
#include <QStringList>

#include <QDebug>

#include "model/application.h"
#include "model/institution.h"
#include "model/studycourse.h"
#include "model/course.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void show();
    bool close();

private:
    void initComponents();

    static QStringList TABLE_HEADERS_H;

    QMenuBar *mMenu;

    QVBoxLayout *mMainLayout;
    QGridLayout *mTopLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;

    QTableWidget *mCourseTable;
};

#endif // MAINWINDOW_H
