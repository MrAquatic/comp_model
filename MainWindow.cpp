#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Theory.h"
#include "Test.h"
#include <QDebug>

void MainWindow::setFixedSizeAndDisableFullscreen()
{
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    setMaximumWidth(800);
    setMaximumHeight(600);
    show();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // -- для возврата в главное меню из подсистем теории, демонстрации и теста -- //
    connect(ui->teoria, &Theory::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->test, &Test::return_to_menu, this, &MainWindow::return_to_menu);
    connect(ui->demo, &Demo::return_to_menu, this, &MainWindow::return_to_menu);
    setFixedSizeAndDisableFullscreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_teoria_clicked()
{
    unSetFixedSizeAndEnableFullscren();
    ui->stackedWidget->setCurrentWidget(ui->teoria);
}

void MainWindow::on_pushButton_test_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->test);
}

void MainWindow::return_to_menu()
{
    ui->stackedWidget->setCurrentWidget(ui->mainmenu);
    setFixedSizeAndDisableFullscreen();
}


void MainWindow::unSetFixedSizeAndEnableFullscren()
{
    setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    setMaximumWidth(QWIDGETSIZE_MAX);
    setMaximumHeight(QWIDGETSIZE_MAX);
    show();
}

void MainWindow::on_pushButton_demo_clicked()
{
    unSetFixedSizeAndEnableFullscren();

    ui->stackedWidget->setCurrentWidget(ui->demo);
    // включаем отрисовку n-semi
    ui->demo->activateAnimOnShow(); // включаю анимацию n-полупроводника
}
