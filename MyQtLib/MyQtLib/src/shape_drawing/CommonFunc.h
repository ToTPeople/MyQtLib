#pragma once
#include "CommonDefine.h"

class QRect;
class QPoint;

/**
  功能：根据起点、终点计算矩形区域
*/
QRect CalRegionByPos(const QPoint &st, const QPoint &en, RegionType_E eType);

/**
  功能：根据点扩展矩形区域（把点包含在矩形区域中）
*/
void ExpandRegionByPos(QRect &rcSrc, const QPoint &pos);

