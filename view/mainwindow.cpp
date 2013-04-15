#include "mainwindow.h"

MainWindow::MainWindow() :
    QMainWindow(),
    mMenu(0)
{
    initComponents();
}

void MainWindow::initComponents()
{
    // Init main application menu
    mMenu = new QMenuBar(this);
    QMenu *fileMenu = mMenu->addMenu(tr("&File"));

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    //====
    // Main layout: VBox
    mTopLayout = new QGridLayout(this);
    this->setLayout(mTopLayout);

    // Top layout
    QLabel *instiLabel = new QLabel(tr("Institution:"));
    QLabel *studycourseLabel = new QLabel(tr("Study course:"));
    mInstitutionsCombo = new QComboBox();
    mStudyCourseCombo = new QComboBox();

    mTopLayout->setSpacing(5);
    mTopLayout->addWidget(instiLabel, 0, 0);
    mTopLayout->addWidget(mInstitutionsCombo, 0, 1);
    mTopLayout->addWidget(studycourseLabel, 1, 0);
    mTopLayout->addWidget(mStudyCourseCombo, 1, 1);

    this->show();
}
