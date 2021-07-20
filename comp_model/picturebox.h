#ifndef PICTUREBOX_H
#define PICTUREBOX_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "n_semiconductor.h"

class PictureBox : public QGraphicsView
{
    Q_OBJECT
public:
    explicit PictureBox(QWidget *parent = nullptr);
    ~PictureBox();

private:
    QGraphicsScene *scene;          // Объявляем сцену для отрисовки

    // для визуализации n-полупроводника
    N_semiconductor *n_semi = nullptr;
    // позволяем увеличивать размеры окна с масштабированием содержимого
    void resizeEvent(QResizeEvent *event);

public:
    // включить анимацию n-semi
    void show_n_semi();
    // остановить все на паузу и скрыть все визуализации со сцены
    void pauseAll();
    // рисуем знак + или -, или любой другой символ 'c' по коордианте coords и помещаем элемент в указанную группу group
    static QGraphicsTextItem *drawSigns(const std::string &c, const QPointF &coords, QGraphicsItemGroup *group, int FontSize = 28);
    // переадресовываем для p-n перехода, что необходимо изменить полярность
    void changePolarity();
};
#endif // PICTUREBOX_H
