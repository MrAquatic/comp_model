#include <QFile>
#include "Theory.h"
#include "TextLoader.h"
#include <QMessageBox>
#include "ui_Theory.h"

Theory::Theory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Theory)
{
    ui->setupUi(this);
    // -- если файлов нет, то выдаем месседжбокс, иначе читаем файл и грузим в textBrowser -- //
    if (!QFile::exists("text.txt"))
    {
        QMessageBox::warning(this,"Ошибка","Не удалось открыть файл text.txt");
    } else ui->textBrowser->setSource(QUrl("text.txt"));

    if (!QFile::exists("dictionary.txt"))
    {
        QMessageBox::warning(this,"Ошибка","Не удалось открыть файл dictionary.txt");
    } else ui->dictionary->setSource(QUrl("dictionary.txt"));
    ui->textBrowser->setAlignment(Qt::AlignJustify); // -- выравнивание текста по ширине -- //
    ui->textBrowser->setOpenLinks(false); // -- запретить изменения окна с теории при нажатии на ссылки -- //


}

void Theory::on_textBrowser_anchorClicked(const QUrl &arg1)
{
    if (arg1.fileName() == "dictionary")
    {
        ui->dictionary->scrollToAnchor(arg1.fragment());    // -- переход к якорю в словаре, при нажатии на ссылку в тексте теории -- //
    }
}

Theory::~Theory()
{
    delete ui;
}

void Theory::on_pushButton_clicked()
{
    emit return_to_menu();
}
