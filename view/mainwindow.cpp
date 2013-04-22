#include "mainwindow.h"

QStringList MainWindow::TABLE_HEADERS_H;

MainWindow::MainWindow() :
    QWidget(),
    mMenu(0), mMainLayout(0), mTopLayout(0),
    mInstitutionsCombo(0), mStudyCourseCombo(0), mCourseTable(0),
    mCurrentInstitution(0), mCurrentStudyCourse(0)
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
    //connect(saveSheetAction, SIGNAL(triggered()), this, SLOT(on_saveSheetActionint_click()));

    fileMenu->addSeparator();

    QAction *quitAction = fileMenu->addAction(tr("&Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Init help menu
    QMenu *helpMenu = mMenu->addMenu(tr("Help"));

    QAction *helpAction = helpMenu->addAction(tr("Help"), 0, 0, QKeySequence::HelpContents);
    helpMenu->addSeparator();
    QAction *aboutAction = helpMenu->addAction(tr("About GradeCalc..."));

    QAction *testAction = helpMenu->addAction(tr("Test it!"));
    connect(testAction, SIGNAL(triggered()), this, SLOT(on_testAction_triggered()));

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

    connect(mStudyCourseCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(on_StudyCourseCombo_currentIndexChanged(int)));

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

void MainWindow::clearCourseTable()
{
    mCourseTable->clear();
    mCourseTable->setHorizontalHeaderLabels(TABLE_HEADERS_H);
}

void MainWindow::show()
{
    Application app;
    app.loadDatabase();

    // Fill institutions list
    QList<Institution*> institutions = app.institutions();
    mCurrentInstitution = institutions.first();
    QList<StudyCourse*> studyCourses = mCurrentInstitution->getStudyCourses();
    mCurrentStudyCourse = studyCourses.first();

    foreach (Institution *i, institutions) {
        mInstitutionsCombo->addItem(
                    QString("%1 (%2)").arg(i->getName(), i->getCity()));
    }

    foreach (StudyCourse *sc, studyCourses) {
        mStudyCourseCombo->addItem(sc->getName());
    }

    mCourseTable->setColumnCount(4);
    mCourseTable->setRowCount(0);

    TABLE_HEADERS_H << "Semester" << "Name" << "ECTS" << "Note";
    this->clearCourseTable();
    on_StudyCourseCombo_currentIndexChanged(0);

    QWidget::show();
}

bool MainWindow::close()
{
    Application().cleanup();
    return QWidget::close();
}

void MainWindow::on_testAction_triggered() {
    QMessageBox::StandardButton s = QMessageBox::question(this, "Testen", "Laden?",
                                                          QMessageBox::Yes|QMessageBox::No);

    try {
        if (s == QMessageBox::Yes) {
            Worksheet ws("/tmp/test.gcw");

            qDebug() << "Institution:" << ws.institutionId();
            qDebug() << "StudyCourse:" << ws.studyCourseId();
            qDebug() << "Grades:";

            QHash<int,double> grades = ws.grades();
            foreach (int key, grades.keys()) {
                qDebug() << "Course" << key << ":" << grades.value(key);
            }
        } else {
            Worksheet ws;
            ws.setInstitutionId(1);
            ws.setStudyCourseId(5);
            ws.setGrade(0, 2.3);
            ws.setGrade(1, 1.7);
            ws.toFile("/tmp/test.gcw");
        }
    } catch (IllegalArgumentException e) {
        QMessageBox::warning(this, "Fehler", QString("Die gewünschte Aktion "
                                                     "konnte nicht durchgeführt "
                                                     "werden: %1").arg(e.getMessage()));
    }
}

void MainWindow::on_StudyCourseCombo_currentIndexChanged(int index) {
    StudyCourse *sc = mCurrentInstitution->getStudyCourses().at(index);
    QList<Course *> courses = sc->getCourses();

    clearCourseTable();
    mCourseTable->setRowCount(courses.size());
    for (int i = 0; i < courses.size(); ++i) {
        Course *c = courses.at(i);
        QTableWidgetItem *semester =
                new QTableWidgetItem(QString("%1").arg(c->getSemester()));
        QTableWidgetItem *name =
                new QTableWidgetItem(QString("%1").arg(c->getName()));
        QTableWidgetItem *ects =
                new QTableWidgetItem(QString("%1").arg(c->getEcts()));
        QTableWidgetItem *grade =
                new QTableWidgetItem(QString("%1").arg(c->getGrade()));

        mCourseTable->setItem(i, 0, semester);
        mCourseTable->setItem(i, 1, name);
        mCourseTable->setItem(i, 2, ects);
        mCourseTable->setItem(i, 3, grade);
    }
}
