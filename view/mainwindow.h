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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private:
    void initComponents();

    QMenuBar *mMenu;

    QVBoxLayout *mMainLayout;
    QGridLayout *mTopLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;

    QTableWidget *mCourseTable;
};

#endif // MAINWINDOW_H
