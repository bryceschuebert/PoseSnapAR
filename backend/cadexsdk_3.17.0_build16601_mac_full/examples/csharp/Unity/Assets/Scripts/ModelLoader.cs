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

using System.Threading;
using UnityEngine;
using cadex;

public class ModelLoader : MonoBehaviour
{
    public Shader CustomShader;
    public float ScaleFactor = 1f;
    public bool ImportPMI = false;

    private ModelData_Model myModel;
    private GameObject myResultGameObject;
    private Thread myMDMLoadingThread;

    private void Awake() 
    {
        ProgressBar.SetActive(false);
    }

    private void Start() 
    {
        Screen.SetResolution(1280, 800, false);
        // Put your license file in the Scripts folder
        string aKey = LicenseKey.Value();
        // Activate the license (aKey must be defined in cadex_license.cs)
        if (!LicenseManager.Activate(aKey))
        {
            Debug.LogError("Failed to activate CAD Exchanger license.");
            QuitApplication();
        }
        // Update PATH environment variable to resolve model reader's dependencies of format libraries
        UniversalConverterHelper.UpdateSystemEnvironment();
    }

    private void Update() 
    {
        if (myMDMLoadingThread != null) 
        {
            if (myMDMLoadingThread.ThreadState == ThreadState.Stopped) 
            {
                myMDMLoadingThread = null;
                if (myModel != null) 
                {
                    ButtonControl.SetState(ButtonControl.State.CreatingGO);
                    OnModelDataModelLoaded();
                }
                else 
                {
                    ButtonControl.SetState(ButtonControl.State.Available);
                    ProgressBar.SetActive(false);
                }
            }
        }
    }

    public void AsyncImportModel(string thePath) 
    {
        ButtonControl.SetState(ButtonControl.State.LoadingMDM);
        var anObserver = new ProgressBar.Observer();
        myMDMLoadingThread = new Thread(() => {
            myModel = ModelImporter.ImportModel(thePath, ImportPMI, anObserver);
        });
        myMDMLoadingThread.Start();
    }

    public void OnCancel() 
    {
        
    }

    public void OpenFileDialog() 
    {
        if (myResultGameObject != null) 
        {
            Destroy(myResultGameObject);
        }
        SimpleFileBrowser.FileBrowser.ShowLoadDialog(AsyncImportModel, OnCancel);
    }

    void OnModelDataModelLoaded() 
    {
        Unity_ObjectFactory aFactory = new Unity_ObjectFactory();
        if (CustomShader) 
        {
            aFactory.Parameters().SetShader(CustomShader);
        }

        aFactory.Parameters().SetScaleFactor(ScaleFactor);
        aFactory.Parameters().SetImportPMI(ImportPMI);

        var anObserver = new ProgressBar.Observer();
        aFactory.SetProgressStatusObserver(anObserver);
        string aModelName = myModel.Name().ToString();
        aFactory.CreateAsync(myModel, aModelName, OnGameObjectCreated);
    }

    void OnGameObjectCreated(GameObject theGameObject) 
    {
        if (theGameObject != null) 
        {
            myResultGameObject = theGameObject;
            GetComponent<CameraControl>().SetTarget(myResultGameObject.transform);
        }
        ProgressBar.SetActive(false);
        ButtonControl.SetState(ButtonControl.State.Available);
    }

    void QuitApplication() 
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
    }
}