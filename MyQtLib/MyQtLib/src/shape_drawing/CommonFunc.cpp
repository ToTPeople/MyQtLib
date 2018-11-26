#include "CommonFunc.h"
#include <QRect>
#include <QPoint>
#include <QDebug>


QRect CalRegionByPos(const QPoint &st, const QPoint &en, RegionType_E eType)
{
    if (eType <= REGION_TYPE_NONE || eType >= REGION_TYPE_MAX)
    {
        return QRect();
    }

    QRect rc;
    if (st == en)
    {
        rc.setTopLeft(st);
        rc.setBottomRight(en);
        return rc;
    }
    bool bEquilateral = false;
    if (REGION_TYPE_SQUARE == eType)
    {
        bEquilateral = true;
    }

    int x = en.x() - st.x();
    int y = en.y() - st.y();
    int width = (x > 0) ? x : -x;
    int height = (y > 0) ? y : -y;
    int nMin = (width > height) ? height : width;
    QPoint newSt = st;
    QPoint newEn = en;


    if (x < 0)
    {
        if (y < 0)
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() + width - nMin);
                newEn.setY(en.y() + height - nMin);
            }
            rc.setTopLeft(newEn);
            rc.setBottomRight(newSt);
        }
        else
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() + width - nMin);
                newEn.setY(en.y() - (height - nMin));
            }
            rc.setTopRight(newSt);
            rc.setBottomLeft(newEn);
        }
    }
    else
    {
        if (y < 0)
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() - (width - nMin));
                newEn.setY(en.y() + height - nMin);
            }
            rc.setBottomLeft(newSt);
            rc.setTopRight(newEn);
        }
        else
        {
            if (bEquilateral)
            {
                newEn.setX(en.x() - (width - nMin));
                newEn.setY(en.y() - (height - nMin));
            }
            rc.setTopLeft(newSt);
            rc.setBottomRight(newEn);
        }
    }

    qDebug() << "################### Cal: rc: " << rc;
    return rc;
}

void ExpandRegionByPos(QRect & rcSrc, const QPoint & pos)
{
    if (rcSrc.contains(pos))
    {
        return;
    }

    QPoint topleft = rcSrc.topLeft();
    QPoint bottomright = rcSrc.bottomRight();

    if (pos.x() < topleft.x())
    {
        topleft.setX(pos.x());
    }
    else if (pos.x() > bottomright.x())
    {
        bottomright.setX(pos.x());
    }

    if (pos.y() < topleft.y())
    {
        topleft.setY(pos.y());
    }
    else if (pos.y() > bottomright.y())
    {
        bottomright.setY(pos.y());
    }

    rcSrc.setTopLeft(topleft);
    rcSrc.setBottomRight(bottomright);
}
