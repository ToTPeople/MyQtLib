#pragma once
#include "CommonDefine.h"

class QRect;
class QPoint;

/**
  ���ܣ�������㡢�յ�����������
*/
QRect CalRegionByPos(const QPoint &st, const QPoint &en, RegionType_E eType);

/**
  ���ܣ����ݵ���չ�������򣨰ѵ�����ھ��������У�
*/
void ExpandRegionByPos(QRect &rcSrc, const QPoint &pos);

