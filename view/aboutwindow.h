#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

#include "model/application.h"

extern const bool TRYOUT_MODE;

class AboutWindow : public QWidget
{
    Q_OBJECT

public:
    AboutWindow();

private:
    void initComponents();

    QVBoxLayout *mMainLayout;
    QLabel *mApplicationName;
    QLabel *mCopyrightNotice;
    QTextEdit *mLicense;
};

#endif // ABOUTWINDOW_H
