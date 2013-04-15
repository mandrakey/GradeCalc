#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QTranslator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void initComponents();

    QMenuBar *mMenu;

    QGridLayout *mTopLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;
};

#endif // MAINWINDOW_H
