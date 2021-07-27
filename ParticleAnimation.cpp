#include "ParticleAnimation.h"

#include <ctime>

#include <random>
#include <vector>

#include <QPropertyAnimation>
#include <QDebug>
#include <QTimer>

#include "Demo.h"
#include "PictureBox.h"

using namespace std;

ParticleAnimation::ParticleAnimation() : particleArr(particleCount), animationArr(particleCount)
{
    group = new QGraphicsItemGroup();
    animTimer = new QTimer();
}

ParticleAnimation::~ParticleAnimation()
{
    delete group;
}

void ParticleAnimation::draw()
{
    QPen penBlack(Qt::black);
    penBlack.setWidth(3);
    // рисуем полупроводник
    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,w,h);
    rect->setRect(0,0,w,h);
    rect->setPen(penBlack);
    rect->setBrush(Qt::white);
    group->addToGroup(rect);
    // рисуем электроны
    drawElectrons();
    drawIons();
    // рисуем зоны, в которую должны уходить атомы (для эффекта исчезания)
    drawBounds();
    // рисуем схему от источника тока
    drawPowerSource();
    // анимации (последовательная группа анимаций)
    prepareAnim();
    readyToShow = true;
    active = true;
}

void ParticleAnimation::drawPowerSource()
{
    // рисуем схему источника тока
    QPainterPath* path = new QPainterPath();
    QPen pen = {Qt::black};
    pen.setWidth(2);
    path->moveTo(-2,halfH);
    path->lineTo(-30,halfH);
    path->lineTo(-30,halfH-140);
    path->lineTo(340,halfH-140);
    path->moveTo(702,halfH);
    path->lineTo(700+30,halfH);
    path->lineTo(700+30,halfH-140);
    path->lineTo(360,halfH-140);
    path->lineTo(360,halfH-170);
    path->lineTo(360,halfH-110);

    QGraphicsPathItem* mainLine = new QGraphicsPathItem(*path);
    mainLine->setPath(*path);
    mainLine->setPen(pen);
    mainLine->setZValue(5);
    group->addToGroup(mainLine);
    // добавляем жирную линию со стороны минуса у источника тока
    QGraphicsLineItem* minusLine = new QGraphicsLineItem();
    minusLine->setLine(340,halfH-155,340,halfH-125);
    pen.setWidth(6);
    minusLine->setPen(pen);
    minusLine->setParentItem(mainLine);
    // знаки + и -
    PictureBox::drawSigns("+",{700+40,halfH-40},group);
    PictureBox::drawSigns("-",{-68,halfH-40},group);
    PictureBox::drawSigns("+",{365,halfH-186},group);
    PictureBox::drawSigns("-",{300,halfH-185},group);
}

void ParticleAnimation::drawIon(const QPointF &coords)
{
    QGraphicsSvgItem *svgProton = new QGraphicsSvgItem(QString(":/proton.svg"), group);
    svgProton->setPos(coords);
}

void ParticleAnimation::drawIons()
{
    time_t seed = time(nullptr);
    mt19937 mt(seed);
    uniform_int_distribution<int> rand_y(4,h-particleSize-halfParticleSize);
    for (int i = 0; i < 19; ++i)
    {
        drawIon({double((i+1)*35),double(rand_y(mt))});
    }
}

void ParticleAnimation::drawElectrons()
{
    for (int i = 0; i < particleCount; ++i)
    {
        particleArr[i] = new Particle();
        particleArr[i]->setZValue(2);
        particleArr[i]->setGeometry({-20,5,particleSize,particleSize});
        group->addToGroup(particleArr[i]);
    }
}

void ParticleAnimation::drawBounds()
{
    QGraphicsRectItem *outRight = new QGraphicsRectItem(w+2,0,30,h);
    QGraphicsRectItem *outLeft = new QGraphicsRectItem(-4-30,0,particleSize*2,h);
    outRight->setBrush(Qt::white);
    outLeft->setBrush(Qt::white);
    outRight->setPen(QPen(Qt::NoPen));
    outLeft->setPen(QPen(Qt::NoPen));
    outRight->setZValue(5);
    outLeft->setZValue(5);
    group->addToGroup(outRight);
    group->addToGroup(outLeft);
}

void ParticleAnimation::prepareAnim()
{
    time_t seed = time(nullptr);
    mt19937 mt(seed);
    uniform_int_distribution<int> rand_y(4,h-particleSize-halfParticleSize); // в пределах проводника
    double prev_y = 0;
    for (int i = 0; i < particleCount; ++i)
    {
        double y = 0;
        do {
            y = rand_y(mt);
        } while (fabs(y - prev_y) < particleSize);
        prev_y = y;
        animationArr[i] = new QPropertyAnimation(particleArr[i],"geometry");
        animationArr[i]->setDuration(animDuration);
        animationArr[i]->setStartValue(QRectF(-20,y,particleSize,particleSize));
        animationArr[i]->setEndValue(QRectF(w+particleSize,y,particleSize,particleSize));
        animationArr[i]->setLoopCount(-1);
    }
    connect(animTimer, &QTimer::timeout, this, &ParticleAnimation::resumeAnim);
    animTimer->start(animGenerationInterval);
}

void ParticleAnimation::pause()
{
    if (active && readyToShow)
    {
        // обрабатываем случай, когда переключились на другую демонстрацию
        // а таймер, подготавливающий анимацию потока электрона ещё не закончился
        // т.е анимация не сформирована до конца, поэтому запустим её в следующий раз заново
        if (animTimer->isActive())
        {
            i=0;
            animTimer->stop();
            for (auto &anim : animationArr)
            {
                anim->stop();
                anim->targetObject()->setProperty(anim->propertyName(),anim->startValue());
            }
        }
        else    // иначе поставим анимацию на паузу
        {
            for (auto &anim : animationArr)
            {
                anim->pause();
            }
        }

        active = false;
    }
}

void ParticleAnimation::unpause()
{
    if (!active && readyToShow)
    {
        if (animationArr[0]->state() == QAbstractAnimation::State::Stopped) // если в прошлый раз остановили
        {
            animTimer->start(animGenerationInterval);
        }
        else    // если поставили на паузу
        {
            for (auto &anim : animationArr)
            {
                anim->resume();
            }
        }
        active = true;
    }
}

void ParticleAnimation::resumeAnim()
{
    animationArr[i]->start();
    ++i;
    if (i == particleCount) animTimer->stop();
}
