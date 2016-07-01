#include "brushtests.h"

///////////////////////////////////////////////////////////////////////////////
/// PLANE TESTS
/// ///////////////////////////////////////////////////////////////////////////
//!
//! \brief PlaneTests::testInitPlane Test init"
//!
void PlaneTests::testInitPlane() {
    QVector3D botLeft(-16, -16, 0);
    QVector3D topLeft(16, -16, 0);
    QVector3D topRight(16, 16, 0);
    Plane p(botLeft,topLeft,topRight);
    QCOMPARE(p.getBotLeft(),botLeft);
    QCOMPARE(p.getTopLeft(),topLeft);
    QCOMPARE(p.getTopRight(),topRight);
}

//!
//! \brief PlaneTests::testGetSet Tests get and set are implemented properly
//!
void PlaneTests::testGetSet() {

    QVector3D botLeft(-32, -32, 0);
    QVector3D topLeft(32, -32, 0);
    QVector3D topRight(32, 32, 0);
    Plane p(botLeft,topLeft,topRight);

    QVector3D botLeft2(-16, -16, 0);
    QVector3D topLeft2(16, -16, 0);
    QVector3D topRight2(16, 16, 0);

    p.setBotLeft(botLeft2);
    p.setTopLeft(topLeft2);
    p.setTopRight(topRight2);

    QCOMPARE(p.getBotLeft(),botLeft2);
    QCOMPARE(p.getTopLeft(),topLeft2);
    QCOMPARE(p.getTopRight(),topRight2);

}
//!
//! \brief PlaneTests::testInvalid tests for values that are the same
//!
void PlaneTests::testInvalid() {

    QVector3D uninit3d;

    // Invalid values 1
    QVector3D botLeft2(16, -16, 0);
    QVector3D topLeft2(16, -16, 0);
    QVector3D topRight2(16, -16, 0);
    Plane x(botLeft2,topLeft2,topRight2);
    QCOMPARE(x.getBotLeft(), uninit3d);
    QCOMPARE(x.getTopLeft(), uninit3d);
    QCOMPARE(x.getTopRight(), uninit3d);

    // Invalid values 2
    QVector3D botLeft3(16, -16, 0);
    QVector3D topLeft3(16, -16, 0);
    QVector3D topRight3(16, 16, 0);
    Plane y(botLeft3,topLeft3,topRight3);
    QCOMPARE(y.getBotLeft(), uninit3d);
    QCOMPARE(y.getTopLeft(), uninit3d);
    QCOMPARE(y.getTopRight(), uninit3d);

    // Invalid values 3
    QVector3D botLeft4(16, -16, 0);
    QVector3D topLeft4(32, -16, 0);
    QVector3D topRight4(32, -16, 0);
    Plane z(botLeft4,topLeft4,topRight4);
    QCOMPARE(z.getBotLeft(), uninit3d);
    QCOMPARE(z.getTopLeft(), uninit3d);
    QCOMPARE(z.getTopRight(), uninit3d);
}

