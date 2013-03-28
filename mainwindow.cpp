#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mInstitutions(QList<Institution*>()),
    mCurrentInstitution(0)
{
    ui->setupUi(this);
    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;

    foreach (Institution* i, mInstitutions)
        delete i;
}

void MainWindow::loadData()
{
    const ProgramOptions options;
    po::variables_map vm;
    try {
        vm = options.getVariables();
    } catch (UninitializedException e) {
        QMessageBox msg;
        msg.setText(QString("Die Kommandozeilenoptionen konnten nicht geladen "
                            "werden:\n%1").arg(e.getMessage()));
        msg.exec();
        close();
    }

    //====
    // Load data from datafile

    QDomDocument d("data");
    QFile f("./data.xml");

    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox msg;
        msg.setText(QString("Failed to open file '%1' for reading data.").
                    arg(f.fileName()));
        msg.exec();
        return;
    }

    if (!d.setContent(&f)) {
        QMessageBox msg;
        msg.setText(QString("Failed to load XML content."));
        msg.exec();
        f.close();
        return;
    }

    // Load everything from the file
    QDomElement root = d.documentElement();
    QDomNodeList l = root.elementsByTagName("Institution");

    for (int i = 0; i < l.size(); ++i) {
        Institution *insti = new Institution(l.at(i));
        mInstitutions.push_back(insti);
        this->ui->mInstitutionCombo->addItem(insti->getName());

        if (i == 0)
            mCurrentInstitution = insti;
    }

    // Load study courses for current institution
    foreach (StudyCourse s, mCurrentInstitution->getStudyCourses())
        this->ui->mStudyCourseCombo->addItem(s.getName());
}
