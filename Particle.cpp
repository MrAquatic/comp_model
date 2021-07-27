#include "Particle.h"
#include <QPainter>
#include <QDebug>
#include <QSvgRenderer>

Particle::Particle() : QGraphicsObject(), svgElectron(std::make_unique<QSvgRenderer>(QString(":/electron.svg")))
{
    // по умолчанию - электрон
    type = ParticleType::electron;
}

QRectF Particle::boundingRect() const
{
    return rect;
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // рисуем частицу
    painter->setRenderHint(QPainter::Antialiasing);
    svgElectron->render(painter, rect);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

const QRectF Particle::geometry() const
{
    return rect;
}

void Particle::setGeometry(const QRectF &value)
{
    rect = value;
    update(); // вызываем метод перерисовки
}

