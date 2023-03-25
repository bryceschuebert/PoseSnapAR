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

public class configurations {
    static {
        try {
            System.loadLibrary("CadExCore");
            System.loadLibrary("CadExSLD");
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
            System.out.println("    <input_file>  is a name of the SLD file to be read");
            System.exit(1);
        }

        String aSource = args[0];
		
		// Open the model
		ModelData_Model aModel = new ModelData_Model();

		//Read all configurations
		SLD_ReaderParameters aParameters = new SLD_ReaderParameters();
		aParameters.SetConfigurationsMode(SLD_ReaderParameters.ConfigurationsModeType.All);

		ModelData_ModelReader aReader = new ModelData_ModelReader();
		aReader.SetReaderParameters(aParameters);
		if (!aReader.Read(new Base_UTF16String(aSource), aModel))
		{
			System.out.println("Failed to read the file " + aSource);
			System.exit(1);
		}

		PartConfigurationVisitor aVisitor = new PartConfigurationVisitor();
		aModel.Accept(aVisitor);
    }
}

// Visits directly each part and calls configuration exploring if a part has one
class PartConfigurationVisitor extends ModelData_Model.VoidElementVisitor {
    @Override
    public void Apply(ModelData_Part thePart) {
            ModelData_ConfigurationManager aManager = thePart.Configurations();
            if (aManager != null)
            {
                ExploreConfigurations(aManager);
            }
    }

	private void ExploreConfigurations(ModelData_ConfigurationManager theManager)
	{
		System.out.println("Number of part configurations: " + theManager.NumberOfConfigurations());

		ModelData_ConfigurationManager.ConfigurationIterator anIterator =
			new ModelData_ConfigurationManager.ConfigurationIterator(theManager);
		while (anIterator.HasNext())
		{
			ModelData_SceneGraphElement anElement = anIterator.Next();
			System.out.println("Part configuration name: " + ModelData_ConfigurationManager.ConfigurationName(anElement));
		}
	}
}
