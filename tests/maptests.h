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

#ifndef MAPTESTS_H
#define MAPTESTS_H

#include <QObject>
#include <QTest>
#include "map.h"

class MapTests : public QObject
{
    Q_OBJECT

private slots:
  void init();
  void testInsertBrush();
  void testReturnBrush();
  void testReadVMF();

};

#endif // MAPTESTS_H
