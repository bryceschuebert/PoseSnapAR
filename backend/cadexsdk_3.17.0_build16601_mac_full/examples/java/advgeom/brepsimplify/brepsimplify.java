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

public class brepsimplify {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExAdvGeom");
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

        if (args.length != 2) {
            System.err.println("Usage: " + " <input_file> <output_file>, where:");
            System.err.println("    <input_file>  is a name of the ACIS file to be read        ");
            System.err.println("    <output_file> is a name of the XML file to Save() the model");
            System.exit(1);
        }

        String aSource = args[0];
        String aDest = args[1];

        ModelData_Model aModel = new ModelData_Model();

        ModelData_ModelReader aReader = new ModelData_ModelReader();

        // Open and convert the file
        if (!aReader.Read(new Base_UTF16String(aSource), aModel)) {
            System.err.println("Failed to open and convert the file " + aSource);
            System.exit(1);
        }

        // Basic info about model
        FaceCounter aBeforeCounter = new FaceCounter();
        aModel.Accept(aBeforeCounter);
        System.out.println("Model name: " + aModel.Name());
        System.out.println("# of faces before: " + String.valueOf(aBeforeCounter.NumberOfFaces()));

        // Running the simplifier
        ModelSimplifier_SimplifierBuilder aBuilder = new ModelSimplifier_SimplifierBuilder();
        aBuilder.SetLevel(ModelSimplifier_SimplifierBuilder.SimplificationLevel.High);
        aBuilder.SetFeatureSize(ModelSimplifier_SimplifierBuilder.SimplifiedFeatureSize.Large);
        ModelSimplifier_Simplifier aSimplifier = aBuilder.CreatePipeline();

        ModelData_Model aNewModel = aSimplifier.Perform(aModel);

         // How many shapes does simplified model contain?
        FaceCounter anAfterCounter = new FaceCounter();
        aNewModel.Accept(anAfterCounter);
        System.out.println("# of faces after: " + String.valueOf(anAfterCounter.NumberOfFaces()));

        // Saving the simplified model
        if (!new ModelData_ModelWriter().Write(aNewModel, new Base_UTF16String(aDest))) {
            System.err.println("Failed to write the file " + aDest);
            System.exit(1);
        }
    }
}

class FaceCounter extends ModelData_Model.VoidElementVisitor {


    private int myNumberOfFaces = 0;

    @Override
    public void Apply(ModelData_Part thePart) {
        ModelData_BRepRepresentation aBRep = thePart.BRepRepresentation();
        final ModelData_BodyList aBodyList = aBRep.Get();
        for (int i = 0; i < aBodyList.Size(); ++i) {
            ModelData_Body aBody = aBodyList.Element(i);
            ModelData_Shape.Iterator aFaceIt = new ModelData_Shape.Iterator(aBody, ModelData_ShapeType.ModelData_ST_Face);
            while (aFaceIt.HasNext()) {
                aFaceIt.Next();
                ++myNumberOfFaces;
            }
        }
    }

    public int NumberOfFaces() {
        return myNumberOfFaces;
    }

}
