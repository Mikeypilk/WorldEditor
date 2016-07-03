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

#include "brush.h"
#define PI 3.14159265
//!
//! \brief Plane::Plane Contruct a plane with 3 vertex
//! \param bot_left - Defines the bottom left vertex
//! \param top_left - Defines the top left vertex
//! \param top_right - Defines the top right vertex
//!
Plane::Plane(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
    if(!checkValid(bot_left, top_left, top_right)) {
        m_bot_left = bot_left;
        m_top_left = top_left;
        m_top_right = top_right;
    }
}
//!
//! \brief Plane::setBotLeft
//! \param bot_left
//!
void Plane::setBotLeft(QVector3D bot_left) {
    if(!checkValid(bot_left, m_top_left, m_top_right)) {
        m_bot_left = bot_left;
    }
}
//!
//! \brief Plane::setTopRight
//! \param top_right
//!
void Plane::setTopRight(QVector3D top_right) {
    if(!checkValid(m_bot_left, m_top_left, top_right)) {
        m_top_right = top_right;
    }
}
//!
//! \brief Plane::setTopLeft
//! \param top_left
//!
void Plane::setTopLeft(QVector3D top_left) {
    if(!checkValid(m_bot_left, top_left, m_top_right)) {
        m_top_left = top_left;
    }
}
//!
//! \brief Plane::getBotLeft
//! \return
//!
QVector3D Plane::getBotLeft() {
    return m_bot_left;
}
//!
//! \brief Plane::getTopRight
//! \return
//!
QVector3D Plane::getTopRight() {
    return m_top_right;
}
//!
//! \brief Plane::getTopLeft
//! \return
//!
QVector3D Plane::getTopLeft() {
    return m_top_left;
}

//!
//! \brief Plane::checkValid check that each vertex is unique
//! \param bot_left
//! \param top_left
//! \param top_right
//! \return
//!
bool Plane::checkValid(QVector3D bot_left, QVector3D top_left, QVector3D top_right) {
    if (bot_left == top_left ||
            bot_left == top_right ||
            top_left == top_right) {
        qWarning("registered an invalid plane");
        return 1;
    }
    else
        return 0;
}
//!
//! \brief getVertexes returns pointers to vertexes for editing
//! Remember to validate the vertexes when using this!
//! \return
//!
QList<QVector3D*> Plane::getVertexes() {
    QList<QVector3D*> list;
    list.append(&m_bot_left);
    list.append(&m_top_left);
    list.append(&m_top_right);
    return list;
};
//!
//! \brief Brush::Brush
//! \param planes
//!
Brush::Brush(QList<Plane *> planes) {
    if(!checkValid(planes))
        m_planes = planes;
}
//!
//! \brief checkValid
//! The whole system relies on the fact that you cant have more than one face
//! on the same plane, this iterates the entire list of planes to check this.
//! \param planes
//! \return
//!
bool Brush::checkValid(QList<Plane*> planes) {
    Plane *plane;
    Plane *plane2;
    foreach (plane, planes) {
        foreach (plane2, planes) {
            if(plane != plane2) {
                if(plane->getBotLeft().distanceToPlane(plane2->getBotLeft(),
                                                       plane2->getTopLeft(),
                                                       plane2->getTopRight()) == 0)
                    if(plane->getTopLeft().distanceToPlane(plane2->getBotLeft(),
                                                           plane2->getTopLeft(),
                                                           plane2->getTopRight()) == 0)
                        if(plane->getTopRight().distanceToPlane(plane2->getBotLeft(),
                                                                plane2->getTopLeft(),
                                                                plane2->getTopRight()) == 0 ) {
                            qWarning("registered an invalid block");
                            return 1;
                        }
            }
        }
    }
    return 0;
}
//!
//! \brief Brush::getNumOfSides
//! \return
//!
int Brush::getNumOfSides() {
    return m_planes.size();
}
//!
//! \brief Brush::setXMinMax
//!
void Brush::setXMinMax() {
    QPointF result;
    qreal f=DBL_MIN;
    Plane *plane;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().x() > f)
            f = plane->getBotLeft().x();
        if(plane->getTopLeft().x() > f)
            f = plane->getTopLeft().x();
        if(plane->getTopRight().x() > f )
            f = plane->getTopRight().x();
    }
    result.setX(f);
    f=DBL_MAX;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().x() < f)
            f = plane->getBotLeft().x();
        if(plane->getTopLeft().x() < f)
            f = plane->getTopLeft().x();
        if(plane->getTopRight().x() < f )
            f = plane->getTopRight().x();
    }
    result.setY(f);
    m_x_max_min = result;
}
//!
//! \brief Brush::setYMinMax
//!
void Brush::setYMinMax() {
    QPointF result;
    qreal f=DBL_MIN;
    Plane *plane;
    //! Maximum
    foreach (plane, m_planes) {
        if(plane->getBotLeft().y() > f)
            f = plane->getBotLeft().y();
        if(plane->getTopLeft().y() > f)
            f = plane->getTopLeft().y();
        if(plane->getTopRight().y() > f )
            f = plane->getTopRight().y();
    }
    result.setX(f);
    f=DBL_MAX;
    //! Minimum
    foreach (plane, m_planes) {
        if(plane->getBotLeft().y() < f)
            f = plane->getBotLeft().y();
        if(plane->getTopLeft().y() < f)
            f = plane->getTopLeft().y();
        if(plane->getTopRight().y() < f )
            f = plane->getTopRight().y();
    }
    result.setY(f);
    m_y_max_min = result;
}
//!
//! \brief Brush::setZMinMax
//!
void Brush::setZMinMax() {
    QPointF result;
    qreal f=DBL_MIN;
    Plane *plane;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().z() > f)
            f = plane->getBotLeft().z();
        if(plane->getTopLeft().z() > f)
            f = plane->getTopLeft().z();
        if(plane->getTopRight().z() > f )
            f = plane->getTopRight().z();
    }
    result.setX(f);
    f=DBL_MAX;
    foreach (plane, m_planes) {
        if(plane->getBotLeft().z() < f)
            f = plane->getBotLeft().z();
        if(plane->getTopLeft().z() < f)
            f = plane->getTopLeft().z();
        if(plane->getTopRight().z() < f )
            f = plane->getTopRight().z();
    }
    result.setY(f);
    m_z_max_min = result;
}
//!
//! \brief Brush::getBoundingBox
//! \return
//!
bool Brush::getBoundingBox() {
    setXMinMax();
    setYMinMax();
    setZMinMax();
    return 0;
}
//!
//! \brief Brush::getTopLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTopLeft(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.y());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.x());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getTopRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTopRight(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.x());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.x());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getBottomLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottomLeft(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.y());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.y());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getBottomRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottomRight(axis primary, axis secondary) {
    QVector2D vec;
    if(primary == secondary) {
        qWarning("primary=secondary");
        return vec;
    }
    if(!getBoundingBox()) {
        switch (primary) {
        case X_AXIS:
            vec.setX(m_x_max_min.x());
            break;
        case Y_AXIS:
            vec.setX(m_y_max_min.x());
            break;
        case Z_AXIS:
            vec.setX(m_z_max_min.x());
            break;
        default:
            break;
        }
        switch (secondary) {
        case X_AXIS:
            vec.setY(m_x_max_min.y());
            break;
        case Y_AXIS:
            vec.setY(m_y_max_min.y());
            break;
        case Z_AXIS:
            vec.setY(m_z_max_min.y());
            break;
        default:
            break;
        }
    }
    return vec;
}
//!
//! \brief Brush::getBottom i.e. the center between bottom left and right
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getBottom(axis primary, axis secondary) {
    QVector2D bottomRight = getBottomRight(primary,secondary);
    QVector2D bottomLeft = getBottomLeft(primary,secondary);
    return (bottomRight + bottomLeft) / 2;
}
//!
//! \brief Brush::getTop
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getTop(axis primary, axis secondary) {
    QVector2D topRight = getTopRight(primary,secondary);
    QVector2D topLeft = getTopLeft(primary,secondary);
    return (topRight + topLeft) / 2;
}
//!
//! \brief Brush::getLeft
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getLeft(axis primary, axis secondary) {
    QVector2D topLeft = getTopLeft(primary,secondary);
    QVector2D bottomLeft = getBottomLeft(primary,secondary);
    return (bottomLeft + topLeft) / 2;
}
//!
//! \brief Brush::getRight
//! \param primary
//! \param secondary
//! \return
//!
QVector2D Brush::getRight(axis primary, axis secondary) {
    QVector2D topRight = getTopRight(primary,secondary);
    QVector2D bottomRight = getBottomRight(primary,secondary);
    return (bottomRight + topRight) / 2;
}
//!
//! \brief Brush::translate
//! \param box
//! \param primary
//! \param secondary
//! \param transform

QVector2D Brush::getCenter(axis primary, axis secondary) {
    return ((getBottom(primary,secondary) + getTop(primary,secondary)) / 2);
}

void Brush::translate(axis primary, axis secondary, QVector2D transform) {
    QMatrix4x4 matrix;
    switch (primary) {
    case X_AXIS:
        matrix.translate(transform.x(), 0, 0);
        break;
    case Y_AXIS:
        matrix.translate(0, transform.x(), 0);
        break;
    case Z_AXIS:
        matrix.translate(0, 0, transform.x());
        break;
    default:
        break;
    }
    switch (secondary) {
    case X_AXIS:
        matrix.translate(transform.y(), 0, 0);
        break;
    case Y_AXIS:
        matrix.translate(0, transform.y(), 0);
        break;
    case Z_AXIS:
        matrix.translate(0, 0, transform.y());
        break;
    default:
        break;
    }
    Plane *pla;
    foreach(pla, m_planes) {
        pla->setBotLeft(matrix.map(pla->getBotLeft()));
        pla->setTopLeft(matrix.map(pla->getTopLeft()));
        pla->setTopRight(matrix.map(pla->getTopRight()));
    }
}
//!
//! \brief Brush::rotate
//! \param primary
//! \param secondary
//! \param rotation
//!
void Brush::rotate(axis primary, axis secondary, float angle) {

    angle = angle * PI/180;
    // Move the object to the center of the grid!
    QVector2D center = getCenter(primary, secondary);
    translate(primary,secondary,-center);

    bool rotateX = true;
    bool rotateY = true;
    bool rotateZ = true;
    // Remember if your editing the X against Z axis, you do the
    // bounding box and start to rotate your going to be wanting
    // to rotate around the Z axis...
    if((primary == X_AXIS) || (secondary == X_AXIS))
        rotateX = false;
    if((primary == Y_AXIS) || (secondary == Y_AXIS))
        rotateY = false;
    if((primary == Z_AXIS) || (secondary == Z_AXIS))
        rotateZ = false;

    // for some reason i couldnt understand the matrix.rotate wouldnt work..?
    // Goto link for more info:
    // http://inside.mines.edu/fs_home/gmurray/ArbitraryAxisRotation/
    QMatrix4x4 matrix;
    if(rotateZ) {
        matrix.setRow(0, QVector4D(cos(angle), -sin(angle),0,0));
        matrix.setRow(1, QVector4D(sin(angle), cos(angle) ,0,0));
        matrix.setRow(2, QVector4D(0,0          ,1,0));
        matrix.setRow(3, QVector4D(0,0          ,0,1));
    }
    if(rotateY) {
        matrix.setRow(0, QVector4D(cos(angle),0,sin(angle),0));
        matrix.setRow(1, QVector4D(0, 1,0,0));
        matrix.setRow(2, QVector4D(-sin(angle),0,cos(angle),0));
        matrix.setRow(3, QVector4D(0,0,0,1));
    }
    if(rotateX) {
        matrix.setRow(0, QVector4D(cos(angle),-sin(angle),0,0));
        matrix.setRow(1, QVector4D(sin(angle),cos(angle),0,0));
        matrix.setRow(2, QVector4D(0,0,1,0));
        matrix.setRow(3, QVector4D(0,0,0,1));
    }
    Plane *pla;
    foreach(pla, m_planes) {
        pla->setBotLeft(matrix.map(pla->getBotLeft()));
        pla->setTopLeft(matrix.map(pla->getTopLeft()));
        pla->setTopRight(matrix.map(pla->getTopRight()));
    }
    // Move the object back to where it came from!
    translate(primary,secondary,center);
}
//!
//! \brief Brush::scale
//! \param primary
//! \param secondary
//! \param travector
//!
void Brush::scale(axis primary, axis secondary, QVector2D travector) {
    QMatrix4x4 matrix;
    switch (primary) {
    case X_AXIS:
        matrix.scale(travector.x(),1,1);
        break;
    case Y_AXIS:
        matrix.scale(1, travector.x(), 1);
        break;
    case Z_AXIS:
        matrix.scale(1, 1, travector.x());
        break;
    default:
        break;
    }
    switch (secondary) {
    case X_AXIS:
        matrix.scale(travector.y(), 1, 1);
        break;
    case Y_AXIS:
        matrix.scale(1, travector.y(), 1);
        break;
    case Z_AXIS:
        matrix.scale(1, 1, travector.y());
        break;
    default:
        break;
    }
    Plane *pla;
    foreach(pla, m_planes) {
        pla->setBotLeft(matrix.map(pla->getBotLeft()));
        pla->setTopLeft(matrix.map(pla->getTopLeft()));
        pla->setTopRight(matrix.map(pla->getTopRight()));
    }
}
//!
//! \brief Brush::transform
//! \param corner
//! \param primary
//! \param secondary
//! \param newpos
//!
void Brush::transform(boundingBox box, axis primary, axis secondary, QVector2D transform) {

    QVector2D coords;
    switch (box) {
    case  BOUND_BOX__TOP_LEFT:
        coords = getBottomRight(primary, secondary);
        break;
    case  BOUND_BOX__TOP_RIGHT:
        coords = getBottomLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_RIGHT:
        coords = getTopLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_LEFT:
        coords = getTopRight(primary, secondary);
        break;
    case  BOUND_BOX__TOP:
        coords = getBottom(primary, secondary);
        break;
    case  BOUND_BOX__RIGHT:
        coords = getLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM:
        coords = getTop(primary, secondary);
        break;
    case  BOUND_BOX__LEFT:
        coords = getRight(primary, secondary);
        break;
    default  :
        break;
    }

    translate(primary,secondary,-coords);
    QVector2D size = getTopLeft(primary,secondary) - getBottomRight(primary,secondary);
    QVector2D newSize = size + transform;
    scale(primary,secondary,newSize/size);

    QVector2D newCoords;
    switch (box) {
    case  BOUND_BOX__TOP_LEFT:
        newCoords = getBottomRight(primary, secondary);
        break;
    case  BOUND_BOX__TOP_RIGHT:
        newCoords = getBottomLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_RIGHT:
        newCoords = getTopLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM_LEFT:
        newCoords = getTopRight(primary, secondary);
        break;
    case  BOUND_BOX__TOP:
        newCoords = getBottom(primary, secondary);
        break;
    case  BOUND_BOX__RIGHT:
        newCoords = getLeft(primary, secondary);
        break;
    case  BOUND_BOX__BOTTOM:
        newCoords = getTop(primary, secondary);
        break;
    case  BOUND_BOX__LEFT:
        newCoords = getRight(primary, secondary);
        break;
    default  :
        break;
    }
    translate(primary,secondary,coords);

}


