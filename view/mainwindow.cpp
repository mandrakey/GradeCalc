#include "mainwindow.h"

MainWindow::MainWindow() :
    QWidget(),
    mMenu(0), mMainLayout(0), mTopLayout(0),
    mInstitutionsCombo(0), mStudyCourseCombo(0), mCourseTable(0)
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
    mMainLayout = new QVBoxLayout(this);
    mTopLayout = new QGridLayout();

    mMainLayout->setContentsMargins(10, 30, 10, 10);

    // Top layout
    QLabel *instiLabel = new QLabel(tr("Institution:"));
    QLabel *studycourseLabel = new QLabel(tr("Study course:"));
    mInstitutionsCombo = new QComboBox();
    mStudyCourseCombo = new QComboBox();

    mTopLayout->setSpacing(5);
    mTopLayout->setColumnStretch(1, 1);
    mTopLayout->addWidget(instiLabel, 0, 0);
    mTopLayout->addWidget(mInstitutionsCombo, 0, 1);
    mTopLayout->addWidget(studycourseLabel, 1, 0);
    mTopLayout->addWidget(mStudyCourseCombo, 1, 1);

    mCourseTable = new QTableWidget(this);
    mMainLayout->addLayout(mTopLayout);
    mMainLayout->addWidget(mCourseTable);

    this->show();
}
