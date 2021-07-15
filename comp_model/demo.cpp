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
    ui->graphicLayout_pSemi->addWidget(graphic);
    graphic->show_n_semi(); // изначально показываю анимацию n-полупроводника
    ui->textBrowser->scrollToAnchor("8");
    // запрещаю вводить символы отличные от цифр в поля для ввода
    ui->input1->setValidator(new QIntValidator(0, 20, this));
    ui->input2->setValidator(new QIntValidator(0, 20, this));
    // скрываю эти поля, так как они только для сумматоров
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
    // скрываю поля для ввода, так как они только для сумматоров
    ui->input1->hide();
    ui->input2->hide();
    // скрываю кнопку для переключения полярности
    ui->pushButton_changePolarity->hide();
}

void Demo::on_tabWidget_currentChanged(int)
{
    hideInputs();
    QWidget *p = ui->tabWidget->currentWidget();
    if (p == ui->p_semi)
    {
        ui->graphicLayout_pSemi->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("8");
        //graphic->show_p_semi();
    } else if (p == ui->n_semi)
    {
        ui->graphicLayout_nSemi->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("7");
        graphic->show_n_semi();
    } else if (p == ui->diod)
    {
        ui->graphicLayoutDiod->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("9");
        //graphic->show_diod();
        ui->pushButton_changePolarity->show();
    } else if (p == ui->transistor)
    {
        ui->graphicLayout_transistor->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("10");
        //graphic->show_transistor();
    } else if (p == ui->halfbitsum)
    {
        ui->graphicLayout_halfbitsum->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("16");
        //graphic->show_halfbitsum();
        ui->input1->show();
        ui->input2->show();
        ui->input1->clear();
        ui->input2->clear();
        ui->input1->setMaxLength(1);
        ui->input2->setMaxLength(1);
    } else if (p == ui->twobitsum)
    {
        ui->graphicLayout_twobitsum->addWidget(graphic);
        ui->textBrowser->scrollToAnchor("17");
        //graphic->show_twobitsum();
        ui->input1->show();
        ui->input2->show();
        ui->input1->clear();
        ui->input2->clear();
        ui->input1->setMaxLength(2);
        ui->input2->setMaxLength(2);
    }
}

/*void Demo::on_pushButton_changePolarity_clicked()
{
    graphic->changePolarity();
}*/

void Demo::on_pushButton_toMenu_clicked()
{
    emit return_to_menu();
}

void Demo::on_input1_textEdited(const QString &arg1)
{
    if (arg1 != "0" && arg1 != "1" && arg1 != "01" && arg1 != "11" && arg1 != "10" && arg1 != "00")
    {
        ui->input1->backspace();
    }
    else
    {
        QWidget *p = ui->tabWidget->currentWidget();
        if (p == ui->halfbitsum)
        {
            bool x = arg1.toInt();
            bool y = ui->input2->text().toInt();
            //graphic->callHalfBitSum(x,y);
        }
        else if (p == ui->twobitsum)
        {
            int in1 = arg1.toInt();
            int in2 = ui->input2->text().toInt();
            bool a = in1 / 10;
            bool b = in1 % 10;
            bool c = in2 / 10;
            bool d = in2 % 10;
            //graphic->callTwoBitSum(a,b,c,d);
        }
    }
}

void Demo::on_input2_textEdited(const QString &arg1)
{
    if (arg1 != "0" && arg1 != "1" && arg1 != "01" && arg1 != "11" && arg1 != "10" && arg1 != "00")
    {
        ui->input2->backspace();
    }
    else
    {
        QWidget *p = ui->tabWidget->currentWidget();
        if (p == ui->halfbitsum)
        {
            bool x = arg1.toInt();
            bool y = ui->input1->text().toInt();
            //graphic->callHalfBitSum(x,y);
        }
        else if (p == ui->twobitsum)
        {
            int in1 = ui->input1->text().toInt();
            int in2 = arg1.toInt();
            bool a = in1 / 10;
            bool b = in1 % 10;
            bool c = in2 / 10;
            bool d = in2 % 10;
            //graphic->callTwoBitSum(a,b,c,d);
        }
    }
}
