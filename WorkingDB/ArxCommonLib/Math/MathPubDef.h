#pragma once

/*
	定义数学计算相关的宏，常数定义
*/

extern const double INF           = 1e10;     													   // 无穷大 
extern const double EPS           = 1e-15;    													   // 计算精度 
extern const int    LEFT          = 0;        													   // 点在直线左边 
extern const int    RIGHT         = 1;        													   // 点在直线右边 
extern const int    ONLINE        = 2;        													   // 点在直线上 
extern const int    CROSS         = 0;        													   // 两直线相交 
extern const int    COLINE        = 1;        													   // 两直线共线 
extern const int    PARALLEL      = 2;        													   // 两直线平行 
extern const int    NOTCOPLANAR   = 3;        													   // 两直线不共面 
extern const int    INSIDE        = 1;        													   // 点在图形内部 
extern const int    OUTSIDE       = 2;        													   // 点在图形外部 
extern const int    BORDER        = 3;        													   // 点在图形边界 
extern const int    BAOHAN        = 1;        													   // 大圆包含小圆
extern const int    NEIQIE        = 2;        													   // 内切
extern const int    XIANJIAO      = 3;                                                             // 相交
extern const int    WAIQIE        = 4;                                                             // 外切
extern const int    XIANLI        = 5;                                                             // 相离
extern const double PI            = 3.1415926535898;
