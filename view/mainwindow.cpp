#include "mainwindow.h"

QStringList MainWindow::TABLE_HEADERS_H;

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

    QAction *newSheetAction = fileMenu->addAction(tr("&New worksheet"));
    //connect(newSheetAction, SIGNAL(triggered()), this, SLOT(on_newSheetAction_click()));

    QAction *loadSheetAction = fileMenu->addAction(tr("&Load worksheet"));
    //connect(saveSheetAction, SIGNAL(triggered()), this, SLOT(on_loadSheetAction_click()));

    QAction *saveSheetAction = fileMenu->addAction(tr("&Save worksheet"));
    //connect(saveSheetAction, SIGNAL(triggered()), this, SLOT(on_saveSheetAction_click()));

    fileMenu->addSeparator();

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Init help menu
    QMenu *helpMenu = mMenu->addMenu(tr("Help"));

    QAction *helpAction = helpMenu->addAction(tr("Help"), 0, 0, QKeySequence::HelpContents);
    helpMenu->addSeparator();
    QAction *aboutAction = helpMenu->addAction(tr("About GradeCalc..."));

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

    this->setMinimumSize(500, 470);
    this->adjustSize();
}

void MainWindow::show()
{
    Application app;
    app.loadDatabase();

    // Fill institutions list
    QList<Institution*> institutions = app.institutions();
    QList<StudyCourse*> &studyCourses = institutions.first()->getStudyCourses();

    foreach (Institution *i, institutions) {
        //qDebug() << i.toString();
        mInstitutionsCombo->addItem(
                    QString("%1 (%2)").arg(i->getName(), i->getCity()));
    }

    foreach (StudyCourse *sc, studyCourses) {
        mStudyCourseCombo->addItem(sc->getName());
    }

    mCourseTable->setColumnCount(4);
    mCourseTable->setRowCount(0);

    TABLE_HEADERS_H << "Semester" << "Name" << "ECTS" << "Note";
    mCourseTable->setHorizontalHeaderLabels(TABLE_HEADERS_H);
    mCourseTable->setVerticalHeaderLabels(QStringList());

    QWidget::show();
}

bool MainWindow::close()
{
    Application().cleanup();
    return QWidget::close();
}
