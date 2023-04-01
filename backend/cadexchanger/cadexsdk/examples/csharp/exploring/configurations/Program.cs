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


using cadex;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace configurations
{
    class Program
    {
        // For more information see https://stackoverflow.com/questions/8836093/how-can-i-specify-a-dllimport-path-at-runtime
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool SetDllDirectory(string lpPathName);

        static int Main(string[] args)
        {
            // Add runtime path to CAD Exchanger libraries (e.g. compiled with Visual Studio 2015)
            SetDllDirectory("../../../../../../win64/vc14.1/bin");

            string aKey = LicenseKey.Value();

            // Activate the license (aKey must be defined in cadex_license.cs)
            if (!LicenseManager.Activate(aKey))
            {
                Console.WriteLine("Failed to activate CAD Exchanger license.");
                return 1;
            }

            if (args.Length != 1)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the SLD file to be read");
                return 1;
            }

            string aSource = args[0];

            // Open the model
            ModelData_Model aModel = new ModelData_Model();

            //Read all configurations
            SLD_ReaderParameters aParameters = new SLD_ReaderParameters();
            aParameters.SetConfigurationsMode(SLD_ReaderParameters.ConfigurationsModeType.All);

            ModelData_ModelReader aReader = new ModelData_ModelReader();
            aReader.SetReaderParameters(aParameters);
            if (!aReader.Read(new Base_UTF16String(aSource), aModel))
            {
                Console.WriteLine("Failed to read the file " + aSource);
                return 1;
            }

            PartConfigurationVisitor aVisitor = new PartConfigurationVisitor();
            aModel.Accept(aVisitor);

            return 0;
        }
    }

    // Visits directly each part and calls configuration exploring if a part has one
    class PartConfigurationVisitor : ModelData_Model.VoidElementVisitor
    {
        public override void Apply(ModelData_Part thePart)
        {
            ModelData_ConfigurationManager aManager = thePart.Configurations();
            if (aManager != null)
            {
                ExploreConfigurations(aManager);
            }
        }

        private void ExploreConfigurations(ModelData_ConfigurationManager theManager)
        {
            Console.WriteLine("Number of part configurations: " + theManager.NumberOfConfigurations());

            ModelData_ConfigurationManager.ConfigurationIterator anIterator =
                new ModelData_ConfigurationManager.ConfigurationIterator(theManager);
            while (anIterator.HasNext())
            {
                ModelData_SceneGraphElement anElement = anIterator.Next();
                Console.WriteLine("Part configuration name: " + ModelData_ConfigurationManager.ConfigurationName(anElement));
            }
        }
    };
}
