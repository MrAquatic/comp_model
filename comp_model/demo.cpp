#include "demo.h"
#include "ui_demo.h"
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <random>
#include <QIntValidator>

using namespace std;

Demo::Demo(QWidget *parent) : QMainWindow(parent), ui(new Ui::Demo)
{
    ui->setupUi(this);
    graphic = new PictureBox(); // определяю фрейм, в котором рисую
    ui->graphicLayout_nSemi->addWidget(graphic);
    // добавляем виджет, но не включаем пока отрисовку n-semi
    ui->textBrowser->scrollToAnchor("8");

    hideInputs();
    if (QFile::exists("files\\text.txt"))
    {
        ui->textBrowser->setSource(QUrl("files\\text.txt"));
    }
}

Demo::~Demo()
{
    delete ui;
}

void Demo::hideInputs()
{
    // скрываю кнопку для переключения полярности
    ui->pushButton_changePolarity->hide();
}

/** Включить анимацию демки при переключении на демо из главного меню */
void Demo::activateAnimOnShow()
{
    graphic->show_n_semi();
}

void Demo::on_tabWidget_currentChanged(int)
{
    hideInputs();
    QWidget *p = ui->tabWidget->currentWidget();
    if (p == ui->n_semi)
    {
        ui->graphicLayout_nSemi->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("7");
        graphic->show_n_semi();
    }
}

/*
void Demo::on_pushButton_changePolarity_clicked()
{
    graphic->changePolarity();
}
*/
void Demo::on_pushButton_toMenu_clicked()
{
    // перед выходом в меню, ставим анимацию на паузу
    graphic->pauseAll();
    emit return_to_menu();
}
