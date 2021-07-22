#ifndef ELECTRON_H
#define ELECTRON_H

#include <QPropertyAnimation>
#include <vector>
#include "particle.h"
#include <QGraphicsItemGroup>
class Electron : public QObject
{
public:
    Electron();
    ~Electron();
    void drawPowerSource();
// поля
    // массивы частиц и анимаций к ним
    std::vector<Particle*> particleArr;
    std::vector<QPropertyAnimation*> animationArr;
    // объявляем группу для элементов элементов
    QGraphicsItemGroup *group = nullptr;
    // константы для рисования
    const double w = 700;
    const double h = 150;
    const double halfH = h/2;
    const double particleSize = 16;
    const double halfParticleSize = particleSize/2;
    // таймер, выпускающий частицы для эффекта потока частиц
    QTimer *animTimer = nullptr;
    // длительность анимации
    int animDuration = 2500;
    // индекс текущей выпускаемой частицы
    int i = 0;
     // активна ли сейчас анимация?
    bool active = false;
    // сформировались ли все элементы сцены и анимации?
    bool readyToShow = false;

};

#endif // ELECTRON_H
