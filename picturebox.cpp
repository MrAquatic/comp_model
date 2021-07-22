#include "picturebox.h"
#include "QDebug"
#include <QResizeEvent>
#include <vector>
#include <numeric>
#include <cmath>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "particle.h"
#include "demo.h"

using namespace std;

PictureBox::PictureBox(QWidget *parent) : QGraphicsView(parent), n_semi(new N_semiconductor())

{
    // настроим отображение виджета и содержимого
    // отключим скролл бары
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // сглаживание
    setRenderHint(QPainter::Antialiasing);
    setAlignment(Qt::AlignCenter);
    // инициализируем сцену
    scene = new QGraphicsScene();
    setScene(scene);
    // и добавляем на сцену все наши визуализации
    scene->addItem(n_semi->group);
    // сразу их скрываем
    n_semi->group->hide();
    // устанавливаем флаг полной перерисовки при необходимости
    // (поскольку анимации с быстродвижущимися мелкими объектами - электронами)
    setViewportUpdateMode(FullViewportUpdate);
    scene->setSceneRect(-68,-111,838,305);
    // связываем сигнал таймера в анимации p_semi, что при окончании одной итерации анимации
    // поместить электроны на исходное положение
    // чтобы при повторной итерации анимация корректно отображалась
}

PictureBox::~PictureBox()
{
    delete scene;
}

void PictureBox::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::fitInView(-70,0,840,500,Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}

void PictureBox::pauseAll()
{
    qDebug() << "anim pause";
    n_semi->pause();
    n_semi->group->hide();
}
/*
void PictureBox::show_p_semi()
{
    if (p_semi->group->childItems().empty())
    {
        qDebug() << "p draw";
        p_semi->draw();
    }
    pauseAll();
    p_semi->group->show();
    p_semi->unpause();
}
*/
void PictureBox::show_n_semi()
{
    // Если в первый раз запускаем эту функцию,
    // то инициализируем анимацию через n_semi->draw
    if (n_semi->group->childItems().empty())
    {
        qDebug() << "n draw";
        n_semi->draw();
    }
    // снимаем с паузы
    n_semi->group->show();
    n_semi->unpause();
}
/*
void PictureBox::show_diod()
{
    if (perehod->group->childItems().empty())
    {
        qDebug() << "perehod draw";
        perehod->draw();
    }
    pauseAll();
    perehod->group->show();
    perehod->unpause();
}

void PictureBox::show_transistor()
{
    if (trans->group->childItems().empty())
    {
        qDebug() << "trans draw";
        trans->draw();
    }
    pauseAll();
    trans->group->show();
    trans->unpause();
}

void PictureBox::show_halfbitsum()
{
    if (halfbit->group->childItems().empty())
    {
        qDebug() << "halfbit draw";
        halfbit->draw();
    }
    pauseAll();
    halfbit->group->show();
}

void PictureBox::show_twobitsum()
{
    if (twobit->group->childItems().empty())
    {
        qDebug() << "twobit draw";
        twobit->draw();
    }
    pauseAll();
    twobit->group->show();
}

void PictureBox::callHalfBitSum(bool x, bool y)
{
    halfbit->calculateAndDraw(x,y);
}

void PictureBox::callTwoBitSum(bool a, bool b, bool c, bool d)
{
    twobit->calculateAndDraw(a,b,c,d);
}

void PictureBox::reset_Animations_for_p_semi()
{
    p_semi->resetAnimations();
}
*/
QGraphicsTextItem* PictureBox::drawSigns(const string &c, const QPointF &coords, QGraphicsItemGroup* group, int FontSize)
{
    QGraphicsTextItem *sign = new QGraphicsTextItem(c.c_str());
    sign->setFont(QFont("Arial",FontSize));
    sign->setPos(coords.x(),coords.y());
    sign->setZValue(6);
    group->addToGroup(sign);
    return sign;
}

/*
void PictureBox::changePolarity()
{
    qDebug() << scene->sceneRect();
    perehod->changePolarity();
}
*/
