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
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QTranslator>
#include <QStringList>
#include <QDebug>

#include <iostream>
using std::cerr;
using std::endl;

#include "programoptions.h"
#include "model/application.h"
#include "model/institution.h"
#include "model/studycourse.h"
#include "model/course.h"
#include "model/worksheet.h"

/**
 * Tryout mode.
 * @see main.cpp
 */
extern const bool TRYOUT_MODE;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void show();
    bool close();
    void on_testAction_triggered();
    void recalculateResult();

private slots:
    /**
     * Handle selection of another StudyCourse in the combo box.
     * @param int index The new selected index (same as index in courses list)
     * @todo Really display the courses attached to StudyCourse
     */
    void on_StudyCourseCombo_currentIndexChanged(int);

    void on_mGradeTable_cellChanged(int row, int column);

    void on_saveSheetAction_triggered();

private:
    void initComponents();
    void clearCourseTable();

    static QStringList TABLE_HEADERS_H;
    static const Qt::ItemFlag DISABLE_EDIT_FLAG;

    QMenuBar *mMenu;

    QVBoxLayout *mMainLayout;
    QGridLayout *mTopLayout;
    QGridLayout *mResultLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;

    QLabel *mResultEctsLabel;
    QLabel *mResultGradeLabel;

    QTableWidget *mCourseTable;

    Institution *mCurrentInstitution;
    StudyCourse *mCurrentStudyCourse;
};

#endif // MAINWINDOW_H
