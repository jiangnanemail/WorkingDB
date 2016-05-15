#pragma once

/*
	定义全局宏定义
*/

//方法
#define  FreePtr( Ptr ) if( Ptr != NULL ){ delete Ptr; Ptr = NULL; }





//常量
#define   _PI                                                                                      3.1415926535898
#define   _TOL                                                                                     0.00000000001
#define   STRING_TINY_LEN                                                                          8
#define   STRING_SMALL_LEN                                                                         16
#define   STRING_NORMAL_LEN                                                                        32
#define   STRING_LARGE_LEN                                                                         64
#define   STRING_HUGE_LEN                                                                          128