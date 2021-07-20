#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <qfile.h>
#include <qtextstream.h>
#include <QFile>
#include <QTextStream>

namespace Ui {
class theory;
}

class Theory : public QWidget
{
    Q_OBJECT

public:
    explicit Theory(QWidget *parent = nullptr);
    ~Theory();

signals:
    void return_to_menu();
private slots:
    void on_textBrowser_anchorClicked(const QUrl &arg1); // -- перехват и обработка нажатия на гиперссылку в теории -- //
    void on_pushButton_clicked();
private:
    Ui::theory *ui;

};

#endif // THEORY_H
