/*
 * Copyright (C) 2013  Maurice Bleuel (mandrakey@lavabit.com)
 *
 * This file is part of GradeCalc.
 *
 * GradeCalc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GradeCalc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GradeCalc.  If not, see <http://www.gnu.org/licenses/>.
 */

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
