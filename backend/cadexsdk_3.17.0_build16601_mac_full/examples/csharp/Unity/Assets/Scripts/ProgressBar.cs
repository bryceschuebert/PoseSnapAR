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

using UnityEngine;
using UnityEngine.UI;
using cadex;

[RequireComponent(typeof(Slider))]
public class ProgressBar : MonoBehaviour
{
    static float myValue = 0;
    static Slider mySlider = null;

    static ProgressBar instance = null;

    void Awake() 
    {
        if (instance == null) 
        {
            instance = this;
        }
        else 
        {
            Destroy(this);
            return;
        }
        
        mySlider = GetComponent<Slider>();
    }

    void Update() 
    {
        mySlider.value = myValue;
    }

    public static void SetValue(float theValue) 
    {
        myValue = theValue;
    }

    public static void SetActive(bool theOption) 
    {
        instance.gameObject.SetActive(theOption);
    }

    public class Observer : Base_ProgressStatus.Observer 
    {
        private bool myWasCanceled = false;

        public Observer() 
        {
            SetValue(0);
            SetActive(true);
        }

        public override void ChangedValue(Base_ProgressStatus theStatus) 
        {
            SetValue(theStatus.Value() / 100f);
        }

        public override void Completed(Base_ProgressStatus theStatus) 
        {
            if (!myWasCanceled) 
            {
                Debug.Log("Import completed!");
            }
        }

        public override void Canceled(Base_ProgressStatus theStatus) 
        {
            myWasCanceled = true;
            Debug.Log("Import canceled.");
        }
    }
}


