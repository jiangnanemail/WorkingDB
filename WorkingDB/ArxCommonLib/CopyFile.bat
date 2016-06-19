ECHO "ÎÄ¼þ¸´ÖÆ......"
set arxdesc="..\..\..\inc\CadLib\"
set arxpubfun="..\..\..\inc\CadLib\Publib\PubFun\"

xcopy /r /y 	.\Publib\PubFun\TWArxCommonFun.h			%arxpubfun%
xcopy /r /y 	.\Publib\PubFun\TWArxEntityParam.h			%arxpubfun%
xcopy /r /y 	.\Publib\PubFun\TWArxGeCommonFun.h			%arxpubfun%
xcopy /r /y 	.\Publib\PubFun\TWArxTool.h			        %arxpubfun%
xcopy /r /y 	.\Publib\PubFun\TWExcelWidget.h			    %arxpubfun%
xcopy /r /y 	.\Publib\PubFun\TWWorkingDatabase.h			%arxpubfun%