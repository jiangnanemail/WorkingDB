#pragma once

/*
	常用宏定义
*/

//方法
#define  TWFreePtr( Ptr ) if( Ptr != NULL ){ delete Ptr; Ptr = NULL; }





//常量
#define   TW_PI                                                                        3.1415926535898
#define   TW_TOL                                                                       0.00000000001

#define   TW_STRING_TINY_LEN                                                           8
#define   TW_STRING_SMALL_LEN                                                          16
#define   TW_STRING_NORMAL_LEN                                                         32
#define   TW_STRING_LARGE_LEN                                                          64
#define   TW_STRING_HUGE_LEN                                                           128



//字符串
//appname
#define     TW_TUNNEL_GROUNDLINE_APPNAME                                                _T("TUNNEL_GROUNDLINE")
#define     TW_TUNNEL_LONGIROUTE_APPNAME                                                _T("TUNNEL_LONGIROUTE")
#define     TW_TUNNEL_TUNNELTOP_APPNAME                                                 _T("TUNNEL_TUNNELTOP")
#define     TW_TUNNEL_TUQIAN_APPNAME                                                    _T("TUNNEL_TUQIAN")  
#define     TW_TUNNEL_ZDOUTFRAME_APPNAME                                                _T("TUNNEL_ZDOUTFRAME")  
#define     TW_TUNNEL_CLBOUTFRAME_APPNAME                                               _T("TUNNEL_CLBOUTFRAME")
#define     TW_TUNNEL_BCMAIN_APPNAME                                                    _T("TUNNEL_BCMAIN")

//扩展纪录名称
#define     TW_TUNNEL_FJCS_EXTDIC_RECORD                                                _T("TUNNEL_FJCS_EXTDIC_RECORD")
#define     TW_TUNNEL_GROUNDLINE_EXTDIC_RECORD                                          _T("TUNNEL_GROUNDLINE_EXTDIC_RECORD")


//dwg模板文件
#define    TW_TUNNEL_EXTDWG_TEMPLATE_FILE                                               _T("TunnelTemplate.dwg")

//配置文件名称
#define    TW_TUNNELCASD_CFGFILENAME                                                    _T("TunnelCASDConfig.xml")

//XML配置文件中的字符资源定义
#define    TW_TUNNEL_XMLCFG_ITEM_TABLEDEF                                                _T("TableDef")
#define    TW_TUNNEL_XMLCFG_ITEM_SUPPORTTBL                                              _T("SupportTbl")
#define    TW_TUNNEL_XMLCFG_ITEM_TITLE                                                   _T("Title")
#define    TW_TUNNEL_XMLCFG_ITEM_ITEM                                                    _T("Item")
#define    TW_TUNNEL_XMLCFG_ITEM_COLUM                                                   _T("Colum")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_ROWNUM                                             _T("RowNum")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_NAME                                               _T("Name")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_ROW                                                _T("Row")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_COLUM                                              _T("Colum")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_COUNT                                              _T("Count")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_WIDTH                                              _T("Width")
#define    TW_TUNNEL_XMLCFG_ATTRIBUTE_ALNTYPE                                            _T("AlnType")



//其他
#define     TW_STRING_SEPARATOR_UNDERLINE                                              _T("_")                         //字符分割符
#define     TW_STRING_SEPARATOR_SHARP                                                  _T( "#")


#define     TW_TYPECODE_XRECORD_NOTE                                                    300
#define     TW_TYPECODE_XRECORD_DOUBLE                                                  40
#define     TW_TYPECODE_XRECORD_POINT3D                                                 10
#define     TW_TYPECODE_XRECORD_INT32                                                   90
#define     TW_TYPECODE_XRECORD_INT16                                                   280

//ISO图纸尺寸
#define     TTMB_PAPERFRAME_SIZE_A0                                                     _T("A0(1189×841)")
#define     TTMB_PAPERFRAME_SIZE_A1                                                     _T("A1(841×594)")
#define     TTMB_PAPERFRAME_SIZE_A2                                                     _T("A2(594×420)")
#define     TTMB_PAPERFRAME_SIZE_A3                                                     _T("A3(420×297)")
#define     TTMB_PAPERFRAME_SIZE_A4                                                     _T("A4(297×210)")

//会签默认内容
#define     TTMB_HQ_DEFAULT_VALUE_1                                                      _T("设  计_复  核_专业负责人")
#define     TTMB_HQ_DEFAULT_VALUE_2                                                      _T("设  计_复  核_专业负责人_院总工程师")                   
#define     TTMB_HQ_DEFAULT_VALUE_3                                                      _T("设  计_复  核_专业负责人_院总工程师_总体负责人_集团总工程师")





//枚举定义
//方向
enum CTwEnumDirection { eTWEnumDir_Left, eTWEnumDir_Righ, eTWEnumDir_Top, eTWEnumDir_Bottom };

//对其方式
enum CTwEnumAlnType { eTWEnumAT_Left, eTWEnumAT_Middle, eTWEnumAT_Right };
