#ifndef PLANETESTS_H
#define PLANETESTS_H

#include <QObject>
#include <QtTest>
#include "brush.h"

class PlaneTests : public QObject
{
    Q_OBJECT
    private slots:
        void testInitPlane();
        void testGetSet();
        void testInvalid();
};

class BrushTests : public QObject
{
    Q_OBJECT
    private slots:
        void testInitBrush();
        void testInvalid();

};

#endif // PLANETESTS_H
