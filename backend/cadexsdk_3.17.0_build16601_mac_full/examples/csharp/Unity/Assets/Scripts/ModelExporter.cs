﻿// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2023, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// You may use this file under the terms of the BSD license as follows:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// ****************************************************************************


using cadex;

public static class ModelExporter 
{
    public static bool ExportModel(ModelData_Model theModel, string thePath) 
    {
        // Update PATH environment variable to resolve ModelData_ModelWriter dependencies of format libraries
        UniversalConverterHelper.UpdateSystemEnvironment();

        ModelData_ModelWriter aModelWriter = new ModelData_ModelWriter();

        aModelWriter.SetWriterParameters(CreateX3DPDFWriterParameters());
        aModelWriter.SetWriterParameters(CreateACISWriterParameters());
        aModelWriter.SetWriterParameters(CreateBRepWriterParameters());
        aModelWriter.SetWriterParameters(CreateColladaWriterParameters());
        aModelWriter.SetWriterParameters(CreateDXFWriterParameters());
        aModelWriter.SetWriterParameters(CreateFBXWriterParameters());
        aModelWriter.SetWriterParameters(CreateGLTFWriterParameters());
        aModelWriter.SetWriterParameters(CreateIFCWriterParameters());
        aModelWriter.SetWriterParameters(CreateIGESWriterParameters());
        aModelWriter.SetWriterParameters(CreateJTWriterParameters());
        aModelWriter.SetWriterParameters(CreateOBJWriterParameters());
        aModelWriter.SetWriterParameters(CreateParaWriterParameters());
        aModelWriter.SetWriterParameters(CreateRhinoWriterParameters());
        aModelWriter.SetWriterParameters(CreateSTEPWriterParameters());
        aModelWriter.SetWriterParameters(CreateSTLWriterParameters());
        aModelWriter.SetWriterParameters(CreateU3DWriterParameters());
        aModelWriter.SetWriterParameters(CreateUSDWriterParameters());
        aModelWriter.SetWriterParameters(CreateVRMLWriterParameters());
        aModelWriter.SetWriterParameters(CreateX3DWriterParameters());

        return aModelWriter.Write(theModel, new Base_UTF16String(thePath));
    }
    static X3DPDF_WriterParameters CreateX3DPDFWriterParameters() 
    {
        X3DPDF_WriterParameters aParam = new X3DPDF_WriterParameters();
        return aParam;
    }
    static ACIS_WriterParameters CreateACISWriterParameters() 
    {
        ACIS_WriterParameters aParam = new ACIS_WriterParameters();
        return aParam;
    }
    static BRep_WriterParameters CreateBRepWriterParameters() 
    {
        BRep_WriterParameters aParam = new BRep_WriterParameters();
        return aParam;
    }
    static Collada_WriterParameters CreateColladaWriterParameters() 
    {
        Collada_WriterParameters aParam = new Collada_WriterParameters();
        return aParam;
    }
    static DXF_WriterParameters CreateDXFWriterParameters() 
    {
        DXF_WriterParameters aParam = new DXF_WriterParameters();
        return aParam;
    }
    static FBX_WriterParameters CreateFBXWriterParameters() 
    {
        FBX_WriterParameters aParam = new FBX_WriterParameters();
        return aParam;
    }
    static GLTF_WriterParameters CreateGLTFWriterParameters() 
    {
        GLTF_WriterParameters aParam = new GLTF_WriterParameters();
        return aParam;
    }
    static IFC_WriterParameters CreateIFCWriterParameters()
    {
        IFC_WriterParameters aParam = new IFC_WriterParameters();
        return aParam;
    }
    static IGES_WriterParameters CreateIGESWriterParameters() 
    {
        IGES_WriterParameters aParam = new IGES_WriterParameters();
        return aParam;
    }
    static JT_WriterParameters CreateJTWriterParameters() 
    {
        JT_WriterParameters aParam = new JT_WriterParameters();
        return aParam;
    }
    static OBJ_WriterParameters CreateOBJWriterParameters() 
    {
        OBJ_WriterParameters aParam = new OBJ_WriterParameters();
        return aParam;
    }
    static Para_WriterParameters CreateParaWriterParameters() 
    {
        Para_WriterParameters aParam = new Para_WriterParameters();
        return aParam;
    }
    static Rhino_WriterParameters CreateRhinoWriterParameters() 
    {
        Rhino_WriterParameters aParam = new Rhino_WriterParameters();
        return aParam;
    }
    static STEP_WriterParameters CreateSTEPWriterParameters() 
    {
        STEP_WriterParameters aParam = new STEP_WriterParameters();
        return aParam;
    }
    static STL_WriterParameters CreateSTLWriterParameters() 
    {
        STL_WriterParameters aParam = new STL_WriterParameters();
        return aParam;
    }
    static U3D_WriterParameters CreateU3DWriterParameters() 
    {
        U3D_WriterParameters aParam = new U3D_WriterParameters();
        return aParam;
    }
    static USD_WriterParameters CreateUSDWriterParameters() 
    {
        USD_WriterParameters aParam = new USD_WriterParameters();
        return aParam;
    }
    static VRML_WriterParameters CreateVRMLWriterParameters() 
    {
        VRML_WriterParameters aParam = new VRML_WriterParameters();
        return aParam;
    }
    static X3D_WriterParameters CreateX3DWriterParameters() 
    {
        X3D_WriterParameters aParam = new X3D_WriterParameters();
        return aParam;
    }
}
