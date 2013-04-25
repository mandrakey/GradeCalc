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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QTranslator>
#include <QStringList>
#include <QDebug>

#include <iostream>
using std::cerr;
using std::endl;

#include "programoptions.h"
#include "model/application.h"
#include "model/institution.h"
#include "model/studycourse.h"
#include "model/course.h"
#include "model/worksheet.h"
#include "view/aboutwindow.h"

/**
 * Tryout mode.
 * @see main.cpp
 */
extern const bool TRYOUT_MODE;

/**
 * The main application window.
 * @ingroup view
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * Construct a MainWindow instance.
     * Initializes all widget pointers with 0, calls initComponents().
     * @see MainWindow::initComponents()
     */
    MainWindow();

public slots:
    /**
     * Override default behavior when displaying the main window.
     * Loads institution database and prepares data objects and table.
     */
    void show();

    /**
     * Called when the window is closed.
     * @return Always true
     * @see Application::cleanup()
     */
    bool close();

    /**
     * Method for a test menu option normally invisible.
     * Shall be used to try-out new features before really integrating with
     * the GUI.
     */
    void on_testAction_triggered();

    /**
     * Recalculate the result average grade using currently set data.
     */
    void recalculateResult();

private slots:
    /**
     * Handle selection of another StudyCourse in the combo box.
     * @param int index The new selected index (same as index in courses list)
     */
    void on_StudyCourseCombo_currentIndexChanged(int);

    /**
     * Handle change in the grade table by the user.
     * @param row Index of the changed row
     * @param column Index of the changed column
     */
    void on_mGradeTable_cellChanged(int row, int column);

    /**
     * Handle click on "save worksheet" menu option.
     * Saves the current worksheet data into a file.
     */
    void on_saveSheetAction_triggered();

    /**
     * Handle click on "load worksheet" menu option.
     * Allows to load a worksheet from file, replacing all set data with
     * information contained in selected file.
     */
    void on_loadSheetAction_triggered();

    /**
     * Discards all current user input.
     */
    void on_newSheetAction_triggered();

    /**
     * Display the AboutWindow.
     */
    void on_aboutAction_triggered();

private:
    /**
     * Initialize the GUI widgets.
     */
    void initComponents();

    /**
     * Clear the course table, only resetting the column headers.
     */
    void clearCourseTable();

    /** List containing all column headers for mCourseTable. */
    static QStringList TABLE_HEADERS_H;

    /** Value for "disable editing" Qt flag. */
    static const Qt::ItemFlag DISABLE_EDIT_FLAG;

    /** Text for the select file dialog filter. */
    static const char *FILEDIALOG_FILTER;

    /** The main menu bar widget. */
    QMenuBar *mMenu;

    /** The main virtual box layout for the main window. */
    QVBoxLayout *mMainLayout;

    /** Grid with institution, study course selection and course table. */
    QGridLayout *mTopLayout;

    /** Grid containing labels for ects and grade results. */
    QGridLayout *mResultLayout;

    QComboBox *mInstitutionsCombo;
    QComboBox *mStudyCourseCombo;

    QLabel *mResultEctsLabel;
    QLabel *mResultGradeLabel;

    QTableWidget *mCourseTable;

    /** Points to the currently selected institution. */
    Institution *mCurrentInstitution;

    /** Points to the currently selected study course. */
    StudyCourse *mCurrentStudyCourse;

    AboutWindow *mAboutWindow;
};

#endif // MAINWINDOW_H
