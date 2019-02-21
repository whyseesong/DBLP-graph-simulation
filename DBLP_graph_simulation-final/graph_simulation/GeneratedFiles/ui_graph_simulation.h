/********************************************************************************
** Form generated from reading UI file 'graph_simulation.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_SIMULATION_H
#define UI_GRAPH_SIMULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_graph_simulationClass
{
public:
    QAction *actionLoad_Data_File;
    QAction *actionTop_10_Authors_colored_graph;
    QAction *actionAuthor_filtering_animation;
    QAction *actionSearch_one_Author;
    QAction *actionSearch_two_Authors;
    QAction *actionRecommend;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioBtn_streamOn;
    QRadioButton *radioBtn_streamOff;
    QPushButton *pushBtn_streamConfirm;
    QGroupBox *groupBox_2;
    QTextBrowser *label_dataStatus;
    QWidget *tabbox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuFunctions;
    QMenu *menuSearch_Author;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *graph_simulationClass)
    {
        if (graph_simulationClass->objectName().isEmpty())
            graph_simulationClass->setObjectName(QStringLiteral("graph_simulationClass"));
        graph_simulationClass->resize(1200, 800);
        actionLoad_Data_File = new QAction(graph_simulationClass);
        actionLoad_Data_File->setObjectName(QStringLiteral("actionLoad_Data_File"));
        actionTop_10_Authors_colored_graph = new QAction(graph_simulationClass);
        actionTop_10_Authors_colored_graph->setObjectName(QStringLiteral("actionTop_10_Authors_colored_graph"));
        actionAuthor_filtering_animation = new QAction(graph_simulationClass);
        actionAuthor_filtering_animation->setObjectName(QStringLiteral("actionAuthor_filtering_animation"));
        actionSearch_one_Author = new QAction(graph_simulationClass);
        actionSearch_one_Author->setObjectName(QStringLiteral("actionSearch_one_Author"));
        actionSearch_two_Authors = new QAction(graph_simulationClass);
        actionSearch_two_Authors->setObjectName(QStringLiteral("actionSearch_two_Authors"));
        actionRecommend = new QAction(graph_simulationClass);
        actionRecommend->setObjectName(QStringLiteral("actionRecommend"));
        centralWidget = new QWidget(graph_simulationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(910, 10, 281, 61));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 203, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioBtn_streamOn = new QRadioButton(layoutWidget);
        radioBtn_streamOn->setObjectName(QStringLiteral("radioBtn_streamOn"));

        horizontalLayout->addWidget(radioBtn_streamOn);

        radioBtn_streamOff = new QRadioButton(layoutWidget);
        radioBtn_streamOff->setObjectName(QStringLiteral("radioBtn_streamOff"));
        radioBtn_streamOff->setChecked(true);

        horizontalLayout->addWidget(radioBtn_streamOff);

        pushBtn_streamConfirm = new QPushButton(layoutWidget);
        pushBtn_streamConfirm->setObjectName(QStringLiteral("pushBtn_streamConfirm"));

        horizontalLayout->addWidget(pushBtn_streamConfirm);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(910, 80, 281, 661));
        label_dataStatus = new QTextBrowser(groupBox_2);
        label_dataStatus->setObjectName(QStringLiteral("label_dataStatus"));
        label_dataStatus->setGeometry(QRect(10, 20, 261, 631));
        tabbox = new QWidget(centralWidget);
        tabbox->setObjectName(QStringLiteral("tabbox"));
        tabbox->setGeometry(QRect(0, 0, 901, 741));
        graph_simulationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(graph_simulationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFunctions = new QMenu(menuBar);
        menuFunctions->setObjectName(QStringLiteral("menuFunctions"));
        menuSearch_Author = new QMenu(menuFunctions);
        menuSearch_Author->setObjectName(QStringLiteral("menuSearch_Author"));
        graph_simulationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(graph_simulationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        graph_simulationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(graph_simulationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        graph_simulationClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuFunctions->menuAction());
        menuFile->addAction(actionLoad_Data_File);
        menuFunctions->addAction(actionTop_10_Authors_colored_graph);
        menuFunctions->addAction(actionAuthor_filtering_animation);
        menuFunctions->addAction(actionRecommend);
        menuFunctions->addAction(menuSearch_Author->menuAction());
        menuSearch_Author->addAction(actionSearch_one_Author);
        menuSearch_Author->addAction(actionSearch_two_Authors);

        retranslateUi(graph_simulationClass);

        QMetaObject::connectSlotsByName(graph_simulationClass);
    } // setupUi

    void retranslateUi(QMainWindow *graph_simulationClass)
    {
        graph_simulationClass->setWindowTitle(QApplication::translate("graph_simulationClass", "graph_simulation", Q_NULLPTR));
        actionLoad_Data_File->setText(QApplication::translate("graph_simulationClass", "Load Data File", Q_NULLPTR));
        actionTop_10_Authors_colored_graph->setText(QApplication::translate("graph_simulationClass", "Top-10 Authors colored graph", Q_NULLPTR));
        actionAuthor_filtering_animation->setText(QApplication::translate("graph_simulationClass", "Author filtering animation", Q_NULLPTR));
        actionSearch_one_Author->setText(QApplication::translate("graph_simulationClass", "Search one Author", Q_NULLPTR));
        actionSearch_two_Authors->setText(QApplication::translate("graph_simulationClass", "Search two Authors", Q_NULLPTR));
        actionRecommend->setText(QApplication::translate("graph_simulationClass", "Recommend", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("graph_simulationClass", "Stream Data Load Setting", Q_NULLPTR));
        radioBtn_streamOn->setText(QApplication::translate("graph_simulationClass", "On", Q_NULLPTR));
        radioBtn_streamOff->setText(QApplication::translate("graph_simulationClass", "Off", Q_NULLPTR));
        pushBtn_streamConfirm->setText(QApplication::translate("graph_simulationClass", "Confirm", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("graph_simulationClass", "Data Loading Status", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("graph_simulationClass", "File", Q_NULLPTR));
        menuFunctions->setTitle(QApplication::translate("graph_simulationClass", "Functions", Q_NULLPTR));
        menuSearch_Author->setTitle(QApplication::translate("graph_simulationClass", "Search Author", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class graph_simulationClass: public Ui_graph_simulationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_SIMULATION_H
