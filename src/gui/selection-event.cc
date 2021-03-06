// Copyright (c) 2017, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of gepetto-viewer-corba.
// gepetto-viewer-corba is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// gepetto-viewer-corba is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// gepetto-viewer-corba. If not, see <http://www.gnu.org/licenses/>.

#include "gepetto/gui/selection-event.hh"

#include <QDebug>

#include <osgUtil/LineSegmentIntersector>


namespace gepetto {
  namespace gui {
    namespace {
      void toQVector3(const osg::Vec3f& in, QVector3D& out) {
        out.setX(in[0]);
        out.setY(in[1]);
        out.setZ(in[2]);
      }
      void toQVector3(const osg::Vec3d& in, QVector3D& out) {
        out.setX((float)in[0]);
        out.setY((float)in[1]);
        out.setZ((float)in[2]);
      }
    }

    void SelectionEvent::setupIntersection(const osgUtil::LineSegmentIntersector::Intersection& it)
    {
      hasIntersection_ = true;
      toQVector3(it.getLocalIntersectPoint(),  localPoint_);
      toQVector3(it.getWorldIntersectPoint(),  worldPoint_);
      toQVector3(it.getLocalIntersectNormal(), localNormal_);
      toQVector3(it.getWorldIntersectNormal(), worldNormal_);
    }

    void SelectionEvent::done()
    {
      c_.fetchAndAddAcquire(-1);
      if (c_.testAndSetAcquire(0,0)) {
        deleteLater();
      }
    }
  }
}
