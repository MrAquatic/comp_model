#ifndef DEMO_H
#define DEMO_H

#include <QMainWindow>
#include "picturebox.h" // фрейм, в котором все рисуем

QT_BEGIN_NAMESPACE
namespace Ui { class Demo; }
QT_END_NAMESPACE

class Demo : public QMainWindow
{
    Q_OBJECT
public:
    Demo(QWidget *parent = nullptr);
    ~Demo();
    void hideInputs();

    /** Включить анимацию демки при переключении на демо из главного меню */
    void activateAnimOnShow();

signals:
    void return_to_menu();

private slots:
    void on_tabWidget_currentChanged(int index);        // переключились на другую визуализацию
    //void on_pushButton_changePolarity_clicked();        // изменили полярность подключения
    void on_pushButton_toMenu_clicked();                // возврат в главное меню

private:
    Ui::Demo *ui;
    PictureBox *graphic;                                // наш класс, в котором мы все рисуем
};


#endif // Demo_H
