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
    DRAWING_TYPE_TEXT,          // �ı�����
    DRAWING_TYPE_MAX
} DrawingType;

/// �߽ǿ�
typedef enum
{
    EDGE_CORNER_NONE = 0x00, // �޸�ʽ
    EDGE_CORNER_TOP_LEFT = 0x01, // ���Ͻ�
    EDGE_CORNER_TOP = 0x02, // ���Ϸ�
    EDGE_CORNER_TOP_RIGHT = 0x04, // ���Ͻ�
    EDGE_CORNER_LEFT = 0x08, // ���
    EDGE_CORNER_RIGHT = 0x10, // �ұ�
    EDGE_CORNER_BOTTOM_LEFT = 0x20, // ���½�
    EDGE_CORNER_BOTTOM = 0x40, // �±�
    EDGE_CORNER_BOTTOM_RIGHT = 0x80, // ���½�
    EDGE_CORNER_TOP_BAR = EDGE_CORNER_TOP_LEFT | EDGE_CORNER_TOP | EDGE_CORNER_TOP_RIGHT,           // �ϱ���
    EDGE_CORNER_BOTTOM_BAR = EDGE_CORNER_BOTTOM_LEFT | EDGE_CORNER_BOTTOM | EDGE_CORNER_BOTTOM_RIGHT,  // �±���
    EDGE_CORNER_LEFT_BAR = EDGE_CORNER_TOP_LEFT | EDGE_CORNER_LEFT | EDGE_CORNER_BOTTOM_LEFT,        // �����
    EDGE_CORNER_RIGHT_BAR = EDGE_CORNER_TOP_RIGHT | EDGE_CORNER_RIGHT | EDGE_CORNER_BOTTOM_RIGHT,     // �ұ���
    EDGE_CORNER_BOTTOMRIGHT_BLOCK = EDGE_CORNER_BOTTOM | EDGE_CORNER_RIGHT | EDGE_CORNER_BOTTOM_RIGHT,// ���½ǿ�
} EdgeCornerType_E;
