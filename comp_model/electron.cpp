#include "electron.h"

Electron::Electron() : particleArr(40), animationArr(40)
{
    group = new QGraphicsItemGroup();
    animTimer = new QTimer();
}

Electron::~Electron()
{
    delete group;
}

