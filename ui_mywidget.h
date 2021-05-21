/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tableWidget;
    QLabel *label;
    QPushButton *importdata;

    void setupUi(QWidget *MyWidget)
    {
        if (MyWidget->objectName().isEmpty())
            MyWidget->setObjectName(QString::fromUtf8("MyWidget"));
        MyWidget->resize(800, 600);
        verticalLayout = new QVBoxLayout(MyWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(MyWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout->addWidget(radioButton_2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(MyWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new QWidget(groupBox_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        tableWidget = new QTableWidget(widget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setHighlightSections(false);

        horizontalLayout_2->addWidget(tableWidget);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label);


        verticalLayout_2->addWidget(widget);

        importdata = new QPushButton(groupBox_2);
        importdata->setObjectName(QString::fromUtf8("importdata"));

        verticalLayout_2->addWidget(importdata);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(MyWidget);

        QMetaObject::connectSlotsByName(MyWidget);
    } // setupUi

    void retranslateUi(QWidget *MyWidget)
    {
        MyWidget->setWindowTitle(QCoreApplication::translate("MyWidget", "MyWidget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MyWidget", "\346\213\237\345\220\210\345\207\275\346\225\260", nullptr));
        radioButton->setText(QCoreApplication::translate("MyWidget", "RadioButton", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyWidget", "RadioButton", nullptr));
        pushButton->setText(QCoreApplication::translate("MyWidget", "\346\213\237\345\220\210", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MyWidget", "\346\225\260\346\215\256", nullptr));
        label->setText(QString());
        importdata->setText(QCoreApplication::translate("MyWidget", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyWidget: public Ui_MyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
