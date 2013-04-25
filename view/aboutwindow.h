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

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDialogButtonBox>

#include "model/application.h"

extern const bool TRYOUT_MODE;

/**
 * A window containing information about the program.
 * @ingroup view
 */
class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    AboutWindow();

private:
    /**
     * Initialize the GUI components.
     */
    void initComponents();

    QVBoxLayout *mMainLayout;
    QLabel *mApplicationName;
    QLabel *mCopyrightNotice;
    QTextEdit *mLicense;

    /** Contains the "close" button. */
    QDialogButtonBox *mButtonBox;
};

#endif // ABOUTWINDOW_H
