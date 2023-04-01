// ****************************************************************************
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

using System;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using cadex;

public static class ModelImporter
{
    public static ModelData_Model ImportModel(string thePath, bool theImportPMI = false, Base_ProgressStatus.Observer theObserver = null)
    {
        if (!File.Exists(thePath)) 
        {
            Debug.LogWarning("File not found: \"" + thePath + "\".");
            return null;
        }

        ModelData_ModelReader aModelReader = new ModelData_ModelReader();

        aModelReader.SetReaderParameters(CreateX3DPDFReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateA3DSReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateDS3DXMLReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateX3MFReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateACISReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateINVReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateBRepReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateCATReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateColladaReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateDWGReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateDXFReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateFBXReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateGLTFReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateIFCReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateIGESReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateJTReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateNXReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateOBJReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreatePLYReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreatePRCReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateParaReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateRhinoReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateSTEPReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateSTLReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateSLDEReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateSLDReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateU3DReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateVRMLReaderParameters(theImportPMI));
        aModelReader.SetReaderParameters(CreateX3DReaderParameters(theImportPMI));

        ModelData_Model aModel = new ModelData_Model();
        
        using (var aStatus = new Base_ProgressStatus()) 
        {
            if (theObserver != null) 
            {
                theObserver.SetNotifyingThread();
                aStatus.Register(theObserver);
            }
            aModelReader.SetProgressStatus(aStatus);

            if (!aModelReader.Read(new Base_UTF16String(thePath), aModel)) 
            {
                Debug.LogError("Failed to read the file " + Path.GetFileName(thePath));
                aStatus.Cancel();
                return null;
            }
            
            if (theObserver != null) 
            {
                aStatus.Unregister(theObserver);
            }
        }
        
        return aModel;
    }
    static X3DPDF_ReaderParameters CreateX3DPDFReaderParameters(bool theImportPMI) 
    {
        X3DPDF_ReaderParameters aParam = new X3DPDF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    } 
    static A3DS_ReaderParameters CreateA3DSReaderParameters(bool theImportPMI) 
    {
        A3DS_ReaderParameters aParam = new A3DS_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static DS3DXML_ReaderParameters CreateDS3DXMLReaderParameters(bool theImportPMI) 
    {
        DS3DXML_ReaderParameters aParam = new DS3DXML_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static ACIS_ReaderParameters CreateACISReaderParameters(bool theImportPMI) 
    {
        ACIS_ReaderParameters aParam = new ACIS_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static INV_ReaderParameters CreateINVReaderParameters(bool theImportPMI) 
    {
        INV_ReaderParameters aParam = new INV_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static BRep_ReaderParameters CreateBRepReaderParameters(bool theImportPMI) 
    {
        BRep_ReaderParameters aParam = new BRep_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static CAT_ReaderParameters CreateCATReaderParameters(bool theImportPMI) 
    {
        CAT_ReaderParameters aParam = new CAT_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static Collada_ReaderParameters CreateColladaReaderParameters(bool theImportPMI) 
    {
        Collada_ReaderParameters aParam = new Collada_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static Creo_ReaderParameters CreateCreoReaderParameters(bool theImportPMI) 
    {
        Creo_ReaderParameters aParam = new Creo_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static DWG_ReaderParameters CreateDWGReaderParameters(bool theImportPMI) 
    {
        DWG_ReaderParameters aParam = new DWG_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static DXF_ReaderParameters CreateDXFReaderParameters(bool theImportPMI) 
    {
        DXF_ReaderParameters aParam = new DXF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static FBX_ReaderParameters CreateFBXReaderParameters(bool theImportPMI) 
    {
        FBX_ReaderParameters aParam = new FBX_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static GLTF_ReaderParameters CreateGLTFReaderParameters(bool theImportPMI) 
    {
        GLTF_ReaderParameters aParam = new GLTF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static IFC_ReaderParameters CreateIFCReaderParameters(bool theImportPMI) 
    {
        IFC_ReaderParameters aParam = new IFC_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static IGES_ReaderParameters CreateIGESReaderParameters(bool theImportPMI)
    {
        IGES_ReaderParameters aParam = new IGES_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static JT_ReaderParameters CreateJTReaderParameters(bool theImportPMI) 
    {
        JT_ReaderParameters aParam = new JT_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static NX_ReaderParameters CreateNXReaderParameters(bool theImportPMI) 
    {
        NX_ReaderParameters aParam = new NX_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static OBJ_ReaderParameters CreateOBJReaderParameters(bool theImportPMI) 
    {
        OBJ_ReaderParameters aParam = new OBJ_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static PLY_ReaderParameters CreatePLYReaderParameters(bool theImportPMI) 
    {
        PLY_ReaderParameters aParam = new PLY_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static PRC_ReaderParameters CreatePRCReaderParameters(bool theImportPMI) 
    {
        PRC_ReaderParameters aParam = new PRC_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static Para_ReaderParameters CreateParaReaderParameters(bool theImportPMI) 
    {
        Para_ReaderParameters aParam = new Para_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static Rhino_ReaderParameters CreateRhinoReaderParameters(bool theImportPMI) 
    {
        Rhino_ReaderParameters aParam = new Rhino_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static SLDE_ReaderParameters CreateSLDEReaderParameters(bool theImportPMI) 
    {
        SLDE_ReaderParameters aParam = new SLDE_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static SLD_ReaderParameters CreateSLDReaderParameters(bool theImportPMI) 
    {
        SLD_ReaderParameters aParam = new SLD_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static STEP_ReaderParameters CreateSTEPReaderParameters(bool theImportPMI) 
    {
        STEP_ReaderParameters aParam = new STEP_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static STL_ReaderParameters CreateSTLReaderParameters(bool theImportPMI) 
    {
        STL_ReaderParameters aParam = new STL_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static U3D_ReaderParameters CreateU3DReaderParameters(bool theImportPMI) 
    {
        U3D_ReaderParameters aParam = new U3D_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static VRML_ReaderParameters CreateVRMLReaderParameters(bool theImportPMI) 
    {
        VRML_ReaderParameters aParam = new VRML_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static X3D_ReaderParameters CreateX3DReaderParameters(bool theImportPMI) 
    {
        X3D_ReaderParameters aParam = new X3D_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
    static X3MF_ReaderParameters CreateX3MFReaderParameters(bool theImportPMI) 
    {
        X3MF_ReaderParameters aParam = new X3MF_ReaderParameters();
        aParam.SetReadPMI(theImportPMI);
        aParam.SetDelayedConversion(true);
        return aParam;
    }
}
