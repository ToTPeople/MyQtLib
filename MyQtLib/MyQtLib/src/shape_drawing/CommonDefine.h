#pragma once

typedef enum
{
    REGION_TYPE_NONE = 0x00,
    REGION_TYPE_RECT,           // ��������
    REGION_TYPE_SQUARE,         // ��������
    REGION_TYPE_MAX
} RegionType_E;

/// ����ͼ������
typedef enum
{
    DRAWING_TYPE_NONE = 0x00,
    DRAWING_TYPE_RECT,          // ����
    DRAWING_TYPE_SQUARE,        // ����
    DRAWING_TYPE_CIRCLE,        // Բ
    DRAWING_TYPE_ELLIPE,        // ��Բ
    DRAWING_TYPE_ARROW,         // ��ͷ
    DRAWING_TYPE_PEN,           // �ֱʣ��������ƣ�
    DRAWING_TYPE_MAX
} DrawingType;
