/*
This file is part of World Editor.

World Editor is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

World Editor is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with World Editor.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "alltests.h"

allTests::allTests(QObject *parent) : QObject(parent)
{

}

bool allTests::runTests() {
    //! Run Plane tests
    PlaneTests planeTest;
    QTest::qExec(&planeTest);

    //! Run Brush tests
    BrushTests brushTest;
    QTest::qExec(&brushTest);

    //! Run Map tests
    MapTests mapTest;
    QTest::qExec(&mapTest);

    //! Run Polygon tests
    PolygonTests polyTests;
    QTest::qExec(&polyTests);

    //! Run Polygon tests
    ViewPortTests vtests;
    QTest::qExec(&vtests);

    return 0;
}
