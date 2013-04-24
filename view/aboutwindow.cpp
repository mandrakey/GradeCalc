#include "aboutwindow.h"

AboutWindow::AboutWindow() :
    mMainLayout(0), mApplicationName(0), mCopyrightNotice(0), mLicense(0)
{
    initComponents();
}

void AboutWindow::initComponents()
{
    mMainLayout = new QVBoxLayout(this);
    mMainLayout->setContentsMargins(10, 30, 10, 10);

    Application app;
    mApplicationName = new QLabel(QString("%1 %2").arg(app.appName()).arg(app.version()));
    mCopyrightNotice = new QLabel(app.copyright());
    mLicense = new QTextEdit(app.license());

    mLicense->setMinimumHeight(200);

    mMainLayout->addWidget(mApplicationName);
    mMainLayout->addWidget(mCopyrightNotice);
    mMainLayout->addWidget(mLicense);

    this->setLayout(mMainLayout);

}
