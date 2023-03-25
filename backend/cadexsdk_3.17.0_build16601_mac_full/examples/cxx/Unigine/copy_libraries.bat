set sourceDir=..\..\..\win64\vc14.1\bin\
set targetDir=.\bin\
set targetPluginDir=.\bin\cadexplugins\

xcopy "%sourceDir%CadExA3DS.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExACIS.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExAdvGeom.dll"    "%targetDir%" /y
xcopy "%sourceDir%CadExBRep.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExCAT.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExCollada.dll"    "%targetDir%" /y
xcopy "%sourceDir%CadExCore.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExCreo.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExDS3DXML.dll"    "%targetDir%" /y
xcopy "%sourceDir%CadExDWG.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExDXF.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExFBX.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExGLTF.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExIFC.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExIGES.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExINV.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExJT.dll"         "%targetDir%" /y
xcopy "%sourceDir%CadExMesh.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExNX.dll"         "%targetDir%" /y
xcopy "%sourceDir%CadExOBJ.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExPara.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExPLY.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExPRC.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExRhino.dll"      "%targetDir%" /y
xcopy "%sourceDir%CadExSLD.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExSLDE.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExSTEP.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExSTL.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExU3D.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExUnigine.dll"    "%targetDir%" /y
xcopy "%sourceDir%CadExUSD.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExView.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExVRML.dll"       "%targetDir%" /y
xcopy "%sourceDir%CadExX3D.dll"        "%targetDir%" /y
xcopy "%sourceDir%CadExX3DPDF.dll"     "%targetDir%" /y
xcopy "%sourceDir%CadExX3MF.dll"       "%targetDir%" /y
xcopy "%sourceDir%freeimage.dll"       "%targetDir%" /y
xcopy "%sourceDir%freetype.dll"        "%targetDir%" /y
xcopy "%sourceDir%geom.dll"            "%targetDir%" /y
xcopy "%sourceDir%tbb.dll"             "%targetDir%" /y
xcopy "%sourceDir%tbbmalloc.dll"       "%targetDir%" /y
xcopy "%sourceDir%vis.dll"             "%targetDir%" /y

xcopy "%sourceDir%CadExUniginePlugin_x64.dll" "%targetPluginDir%" /y