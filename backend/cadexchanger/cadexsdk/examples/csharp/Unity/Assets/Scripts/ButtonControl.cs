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

[RequireComponent(typeof(Button))]
public class ButtonControl : MonoBehaviour
{
    public enum State { Available, LoadingMDM, CreatingGO };
    private State myState = State.Available;

    private Button myButton = null;
    private Text myText = null;

    static ButtonControl instance = null;

    private void Awake() {
        if (instance == null) 
        {
            instance = this;
        }
        else 
        {
            Destroy(this);
            return;
        }

        myButton = GetComponent<Button>();
        myText = GetComponentInChildren<Text>();

        SetState(myState);
    }

    public static void SetState(State theState) 
    {
        instance.myState = theState;
        switch (theState) 
        {
            case State.Available:
                instance.myButton.interactable = true;
                instance.myText.text = "Load model";
                break;
            case State.LoadingMDM:
                instance.myButton.interactable = false;
                instance.myText.text = "Loading model..";
                break;
            case State.CreatingGO:
                instance.myButton.interactable = false;
                instance.myText.text = "Creating GameObject..";
                break;
        }
    }

    public static State GetState() 
    {
        return instance.myState;
    }
}
