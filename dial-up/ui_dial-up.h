/********************************************************************************
** Form generated from reading UI file 'dial-up.ui'
**
** Created: Sun Sep 9 17:49:04 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAL_2D_UP_H
#define UI_DIAL_2D_UP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QDialWindow
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QWidget *QImageWidget;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *QUsernameLabel;
    QLabel *QPasswordLabel;
    QLabel *QChannelLabel;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *QUsernamelineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *QPasswordlineEdit;
    QCheckBox *QPasswordcheckBox;
    QComboBox *QChannelcomboBox;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *QConnectpushButton;
    QPushButton *QDisconnectpushButton;
    QPushButton *QSelfServicepushButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *QVersionLabel;

    void setupUi(QWidget *QDialWindow)
    {
        if (QDialWindow->objectName().isEmpty())
            QDialWindow->setObjectName(QString::fromUtf8("QDialWindow"));
        QDialWindow->resize(378, 355);
        verticalLayout_6 = new QVBoxLayout(QDialWindow);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        QImageWidget = new QWidget(QDialWindow);
        QImageWidget->setObjectName(QString::fromUtf8("QImageWidget"));
        QImageWidget->setMinimumSize(QSize(300, 101));
        QImageWidget->setMaximumSize(QSize(400, 101));

        verticalLayout_2->addWidget(QImageWidget);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        QUsernameLabel = new QLabel(QDialWindow);
        QUsernameLabel->setObjectName(QString::fromUtf8("QUsernameLabel"));

        verticalLayout_5->addWidget(QUsernameLabel);

        QPasswordLabel = new QLabel(QDialWindow);
        QPasswordLabel->setObjectName(QString::fromUtf8("QPasswordLabel"));

        verticalLayout_5->addWidget(QPasswordLabel);

        QChannelLabel = new QLabel(QDialWindow);
        QChannelLabel->setObjectName(QString::fromUtf8("QChannelLabel"));

        verticalLayout_5->addWidget(QChannelLabel);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        QUsernamelineEdit = new QLineEdit(QDialWindow);
        QUsernamelineEdit->setObjectName(QString::fromUtf8("QUsernamelineEdit"));

        verticalLayout_3->addWidget(QUsernamelineEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        QPasswordlineEdit = new QLineEdit(QDialWindow);
        QPasswordlineEdit->setObjectName(QString::fromUtf8("QPasswordlineEdit"));

        horizontalLayout_2->addWidget(QPasswordlineEdit);

        QPasswordcheckBox = new QCheckBox(QDialWindow);
        QPasswordcheckBox->setObjectName(QString::fromUtf8("QPasswordcheckBox"));

        horizontalLayout_2->addWidget(QPasswordcheckBox);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        QChannelcomboBox = new QComboBox(QDialWindow);
        QChannelcomboBox->setObjectName(QString::fromUtf8("QChannelcomboBox"));

        verticalLayout_4->addWidget(QChannelcomboBox);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(horizontalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        QConnectpushButton = new QPushButton(QDialWindow);
        QConnectpushButton->setObjectName(QString::fromUtf8("QConnectpushButton"));

        horizontalLayout->addWidget(QConnectpushButton);

        QDisconnectpushButton = new QPushButton(QDialWindow);
        QDisconnectpushButton->setObjectName(QString::fromUtf8("QDisconnectpushButton"));

        horizontalLayout->addWidget(QDisconnectpushButton);

        QSelfServicepushButton = new QPushButton(QDialWindow);
        QSelfServicepushButton->setObjectName(QString::fromUtf8("QSelfServicepushButton"));

        horizontalLayout->addWidget(QSelfServicepushButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        QVersionLabel = new QLabel(QDialWindow);
        QVersionLabel->setObjectName(QString::fromUtf8("QVersionLabel"));

        horizontalLayout_4->addWidget(QVersionLabel);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_6->addLayout(verticalLayout);


        retranslateUi(QDialWindow);

        QMetaObject::connectSlotsByName(QDialWindow);
    } // setupUi

    void retranslateUi(QWidget *QDialWindow)
    {
        QDialWindow->setWindowTitle(QApplication::translate("QDialWindow", "Broadband Dial-up", 0, QApplication::UnicodeUTF8));
        QUsernameLabel->setText(QApplication::translate("QDialWindow", "username", 0, QApplication::UnicodeUTF8));
        QPasswordLabel->setText(QApplication::translate("QDialWindow", "password", 0, QApplication::UnicodeUTF8));
        QChannelLabel->setText(QApplication::translate("QDialWindow", "channel", 0, QApplication::UnicodeUTF8));
        QPasswordcheckBox->setText(QApplication::translate("QDialWindow", "save password", 0, QApplication::UnicodeUTF8));
        QConnectpushButton->setText(QApplication::translate("QDialWindow", "connect", 0, QApplication::UnicodeUTF8));
        QDisconnectpushButton->setText(QApplication::translate("QDialWindow", "disconnect", 0, QApplication::UnicodeUTF8));
        QSelfServicepushButton->setText(QApplication::translate("QDialWindow", "self service", 0, QApplication::UnicodeUTF8));
        QVersionLabel->setText(QApplication::translate("QDialWindow", "version 1.0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QDialWindow: public Ui_QDialWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAL_2D_UP_H
