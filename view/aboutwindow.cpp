#include "aboutwindow.h"

AboutWindow::AboutWindow() :
    mMainLayout(0), mApplicationName(0), mCopyrightNotice(0), mLicense(0),
    mButtonBox(0)
{
    initComponents();
}

void AboutWindow::initComponents()
{
    mMainLayout = new QVBoxLayout(this);
    //mMainLayout->setContentsMargins(10, 10, 10, 10);

    Application app;
    mApplicationName = new QLabel(QString("<h1>%1 v.%2</h1>").arg(app.appName()).arg(app.version()));
    mCopyrightNotice = new QLabel(QString("<i>%1</i>").arg(app.copyright()));

    mLicense = new QTextEdit();
    mLicense->setMinimumHeight(200);
    mLicense->setMinimumWidth(300);
    mLicense->setReadOnly(true);
    mLicense->setText(app.license());

    mButtonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(mButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(close()));

    mMainLayout->addWidget(mApplicationName);
    mMainLayout->addWidget(mCopyrightNotice);
    mMainLayout->addWidget(mLicense);
    mMainLayout->addWidget(mButtonBox);

    this->setLayout(mMainLayout);

}
