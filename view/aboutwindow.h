#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QDialogButtonBox>

#include "model/application.h"

extern const bool TRYOUT_MODE;

class AboutWindow : public QDialog
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
    QDialogButtonBox *mButtonBox;
};

#endif // ABOUTWINDOW_H
