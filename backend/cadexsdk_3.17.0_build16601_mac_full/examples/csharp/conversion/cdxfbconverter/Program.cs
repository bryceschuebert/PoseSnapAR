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
using System;
using System.Runtime.InteropServices;

namespace cdxfbconverter
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

            if (args.Length != 2)
            {
                Console.WriteLine("Usage: " + System.Reflection.Assembly.GetExecutingAssembly().Location
                + " <input_file> <output_file>, where:");
                Console.WriteLine("    <input_file>  is a name of the JT file to be read");
                Console.WriteLine("    <output_file> is a name of the CDXFB file to Save() the model");
                return 1;
            }

            string aSource = args[0];
            string aDest = args[1];

            ModelData_ModelReader aReader = new ModelData_ModelReader();

            ModelData_Model aModel = new ModelData_Model();

            // Opening and converting the file
            if (!aReader.Read(new Base_UTF16String(aSource), aModel))
            {
                Console.WriteLine("Failed to open and convert the file " + aSource);
                return 1;
            }

            // Now we can get some model data
            Console.WriteLine("Model name: " + aModel.Name());
            Console.WriteLine("Number of roots: " + aModel.NumberOfRoots());

            // Saving the xml file
            ModelData_ModelWriter aWriter = new ModelData_ModelWriter();
            ModelData_WriterParameters aParams = new ModelData_WriterParameters();
            aParams.SetFileFormat(ModelData_WriterParameters.FileFormatType.Cdxfb);
            aParams.SetWriteBRepRepresentation(true);
            aParams.SetWritePolyRepresentation(true);
            aParams.SetPreferredLOD(ModelData_RepresentationMask.ModelData_RM_MediumLOD);
            aParams.SetWriteTextures(false);
            aParams.SetWritePMI(false);

            aWriter.SetWriterParameters (aParams);

            if (!aWriter.Write(aModel, new Base_UTF16String(aDest)))
            {
                Console.WriteLine("Failed to save the .cdxfb file");
                return 1;
            }

            return 0;
        }
    }
}
