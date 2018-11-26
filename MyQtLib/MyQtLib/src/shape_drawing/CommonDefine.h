#pragma once

typedef enum
{
    REGION_TYPE_NONE = 0x00,
    REGION_TYPE_RECT,           // 矩形区域
    REGION_TYPE_SQUARE,         // 方形区域
    REGION_TYPE_MAX
} RegionType_E;

/// 绘制图形类型
typedef enum
{
    DRAWING_TYPE_NONE = 0x00,
    DRAWING_TYPE_RECT,          // 矩形
    DRAWING_TYPE_SQUARE,        // 方形
    DRAWING_TYPE_CIRCLE,        // 圆
    DRAWING_TYPE_ELLIPE,        // 椭圆
    DRAWING_TYPE_ARROW,         // 箭头
    DRAWING_TYPE_PEN,           // 钢笔（随鼠标绘制）
    DRAWING_TYPE_MAX
} DrawingType;
