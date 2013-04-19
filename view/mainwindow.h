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

private slots:
    /**
     * Handle selection of another StudyCourse in the combo box.
     * @param int index The new selected index (same as index in courses list)
     * @todo Really display the courses attached to StudyCourse
     */
    void on_StudyCourseCombo_currentIndexChanged(int);

private:
    void initComponents();

    static QStringList TABLE_HEADERS_H;

    QMenuBar *mMenu;

    QVBoxLayout *mMainLayout;
    QGridLayout *mTopLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;

    QTableWidget *mCourseTable;

    Institution *mCurrentInstitution;
    StudyCourse *mCurrentStudyCourse;
};

#endif // MAINWINDOW_H
