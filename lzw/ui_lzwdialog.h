/********************************************************************************
** Form generated from reading UI file 'lzwdialog.ui'
**
** Created: Sat Aug 18 20:45:36 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LZWDIALOG_H
#define UI_LZWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *filenameLabel;
    QLineEdit *filenameLineEdit;
    QToolButton *fileButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *locationLabel;
    QComboBox *locationComboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *quitButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *compressButton;
    QPushButton *decompressButton;
    QProgressBar *progressBar;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(373, 156);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        filenameLabel = new QLabel(layoutWidget);
        filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));

        horizontalLayout->addWidget(filenameLabel);

        filenameLineEdit = new QLineEdit(layoutWidget);
        filenameLineEdit->setObjectName(QString::fromUtf8("filenameLineEdit"));

        horizontalLayout->addWidget(filenameLineEdit);

        fileButton = new QToolButton(layoutWidget);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));

        horizontalLayout->addWidget(fileButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        locationLabel = new QLabel(layoutWidget);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        horizontalLayout_2->addWidget(locationLabel);

        locationComboBox = new QComboBox(layoutWidget);
        locationComboBox->setObjectName(QString::fromUtf8("locationComboBox"));
        locationComboBox->setEnabled(true);

        horizontalLayout_2->addWidget(locationComboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        splitter->addWidget(layoutWidget);

        horizontalLayout_3->addWidget(splitter);

        horizontalSpacer_2 = new QSpacerItem(98, 58, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        quitButton = new QPushButton(Dialog);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        horizontalLayout_4->addWidget(quitButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        compressButton = new QPushButton(Dialog);
        compressButton->setObjectName(QString::fromUtf8("compressButton"));

        horizontalLayout_4->addWidget(compressButton);

        decompressButton = new QPushButton(Dialog);
        decompressButton->setObjectName(QString::fromUtf8("decompressButton"));
        decompressButton->setEnabled(true);

        horizontalLayout_4->addWidget(decompressButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        progressBar = new QProgressBar(Dialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setValue(24);
        progressBar->setTextVisible(true);

        verticalLayout_2->addWidget(progressBar);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        filenameLabel->setText(QApplication::translate("Dialog", "Filename", 0, QApplication::UnicodeUTF8));
        fileButton->setText(QApplication::translate("Dialog", "...", 0, QApplication::UnicodeUTF8));
        locationLabel->setText(QApplication::translate("Dialog", "Location", 0, QApplication::UnicodeUTF8));
        quitButton->setText(QApplication::translate("Dialog", "Quit", 0, QApplication::UnicodeUTF8));
        compressButton->setText(QApplication::translate("Dialog", "Compress", 0, QApplication::UnicodeUTF8));
        decompressButton->setText(QApplication::translate("Dialog", "Decompress", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LZWDIALOG_H
