/********************************************************************************
** Form generated from reading UI file 'qfilesocket.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFILESOCKET_H
#define UI_QFILESOCKET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QfileSocket
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QTextEdit *pTeLogData;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pPbclear;
    QPushButton *pPbQfileRead;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *QfileSocket)
    {
        if (QfileSocket->objectName().isEmpty())
            QfileSocket->setObjectName(QStringLiteral("QfileSocket"));
        QfileSocket->resize(790, 460);
        gridLayout = new QGridLayout(QfileSocket);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(QfileSocket);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 771, 411));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pTeLogData = new QTextEdit(verticalLayoutWidget);
        pTeLogData->setObjectName(QStringLiteral("pTeLogData"));
        pTeLogData->setMouseTracking(false);
        pTeLogData->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pTeLogData);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pPbclear = new QPushButton(verticalLayoutWidget);
        pPbclear->setObjectName(QStringLiteral("pPbclear"));

        horizontalLayout_2->addWidget(pPbclear);

        pPbQfileRead = new QPushButton(verticalLayoutWidget);
        pPbQfileRead->setObjectName(QStringLiteral("pPbQfileRead"));

        horizontalLayout_2->addWidget(pPbQfileRead);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(QfileSocket);

        QMetaObject::connectSlotsByName(QfileSocket);
    } // setupUi

    void retranslateUi(QWidget *QfileSocket)
    {
        QfileSocket->setWindowTitle(QApplication::translate("QfileSocket", "Form", 0));
        label->setText(QApplication::translate("QfileSocket", "Total Log", 0));
        pPbclear->setText(QApplication::translate("QfileSocket", "clear", 0));
        pPbQfileRead->setText(QApplication::translate("QfileSocket", "Read", 0));
    } // retranslateUi

};

namespace Ui {
    class QfileSocket: public Ui_QfileSocket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFILESOCKET_H
