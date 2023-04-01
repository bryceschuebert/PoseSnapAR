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

import cadex.*;

public class netgen {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExMesh");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load.\n" + e);
            System.exit(1);
        }
    }

    public static void main(String[] args) {
        String aKey = LicenseKey.Value();

        // Activate the license (aKey must be defined in LicenseKey.java)
        if (!LicenseManager.Activate(aKey)) {
            System.out.println("Failed to activate CAD Exchanger license.");
            System.exit(1);
        }

        if (args.length != 1) {
            System.out.println("Usage: " + " <input_file>, where:");
            System.out.println("    <input_file>  is a name of the XML file to be read");
            System.exit(1);
        }

        String aSource = args[0];

        ModelData_Model aModel = new ModelData_Model();

        if (!new ModelData_ModelReader().Read(new Base_UTF16String(aSource), aModel)) {
            System.out.println("Failed to read the file");
            System.exit(1);
        }

        // Set up mesher and parameters
        ModelAlgo_BRepMesherParameters aParam = new ModelAlgo_BRepMesherParameters();

        // Netgen setup
        MeshAlgo_NetgenFactory aNF = new MeshAlgo_NetgenFactory();
        MeshAlgo_NetgenFactory.Parameters aP = new MeshAlgo_NetgenFactory.Parameters();
        aP.SetGranularity(MeshAlgo_NetgenFactory.Parameters.GranularityType.Fine);
        aNF.SetParameters(aP);
        aParam.SetComputationalMeshAlgo(aNF);

        ModelAlgo_BRepMesher aMesher = new ModelAlgo_BRepMesher(aParam);
        aMesher.Compute(aModel, true /*to add a polygonal representation to the model*/);

        // Save the result
        if (!new ModelData_ModelWriter().Write(aModel, new Base_UTF16String("netgen.xml"))) {
            System.out.println("Unable to save the model!");
            System.exit(1);
        }
    }
}
