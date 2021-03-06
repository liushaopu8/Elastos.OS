//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#include "elastos/droid/inputmethod/pinyin/SoftKeyToggle.h"
#include "elastos/droid/inputmethod/pinyin/SkbTemplate.h"

namespace Elastos {
namespace Droid {
namespace InputMethod {
namespace Pinyin {

//====================================================
//  SoftKeyToggle::ToggleState
//====================================================
SoftKeyToggle::ToggleState::ToggleState()
    : mKeyCode(0)
    , mIdAndFlags(0)
{}

void SoftKeyToggle::ToggleState::SetStateId(
    /* [in] */ Int32 stateId)
{
    mIdAndFlags |= (stateId & KEYMASK_TOGGLE_STATE);
}

void SoftKeyToggle::ToggleState::SetStateFlags(
    /* [in] */ Boolean repeat,
    /* [in] */ Boolean balloon)
{
    if (repeat) {
        mIdAndFlags |= KEYMASK_REPEAT;
    }
    else {
        mIdAndFlags &= (~KEYMASK_REPEAT);
    }

    if (balloon) {
        mIdAndFlags |= KEYMASK_BALLOON;
    }
    else {
        mIdAndFlags &= (~KEYMASK_BALLOON);
    }
}


//====================================================
//  SoftKeyToggle
//====================================================
const Int32 SoftKeyToggle::KEYMASK_TOGGLE_STATE = 0x000000ff;

CAR_INTERFACE_IMPL(SoftKeyToggle, SoftKey, ISoftKeyToggle);

Int32 SoftKeyToggle::GetToggleStateId()
{
    return (mKeyMask & KEYMASK_TOGGLE_STATE);
}

Boolean SoftKeyToggle::EnableToggleState(
    /* [in] */ Int32 stateId,
    /* [in] */ Boolean resetIfNotFound)
{
    Int32 oldStateId = (mKeyMask & KEYMASK_TOGGLE_STATE);
    if (oldStateId == stateId) return FALSE;

    mKeyMask &= (~KEYMASK_TOGGLE_STATE);
    if (stateId > 0) {
        mKeyMask |= (KEYMASK_TOGGLE_STATE & stateId);
        if (GetToggleState() == NULL) {
            mKeyMask &= (~KEYMASK_TOGGLE_STATE);
            if (!resetIfNotFound && oldStateId > 0) {
                mKeyMask |= (KEYMASK_TOGGLE_STATE & oldStateId);
            }
            return resetIfNotFound;
        }
        else {
            return TRUE;
        }
    }
    else {
        return TRUE;
    }
}

Boolean SoftKeyToggle::DisableToggleState(
    /* [in] */ Int32 stateId,
    /* [in] */ Boolean resetIfNotFound)
{
    Int32 oldStateId = (mKeyMask & KEYMASK_TOGGLE_STATE);
    if (oldStateId == stateId) {
        mKeyMask &= (~KEYMASK_TOGGLE_STATE);
        return stateId != 0;
    }

    if (resetIfNotFound) {
        mKeyMask &= (~KEYMASK_TOGGLE_STATE);
        return oldStateId != 0;
    }
    return FALSE;
}

Boolean SoftKeyToggle::DisableAllToggleStates()
{
    Int32 oldStateId = (mKeyMask & KEYMASK_TOGGLE_STATE);
    mKeyMask &= (~KEYMASK_TOGGLE_STATE);
    return oldStateId != 0;
}

AutoPtr<IDrawable> SoftKeyToggle::GetKeyIcon()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) return state->mKeyIcon;
    return SoftKey::GetKeyIcon();
}

AutoPtr<IDrawable> SoftKeyToggle::GetKeyIconPopup()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        if (NULL != state->mKeyIconPopup) {
            return state->mKeyIconPopup;
        }
        else {
            return state->mKeyIcon;
        }
    }
    return SoftKey::GetKeyIconPopup();
}

Int32 SoftKeyToggle::GetKeyCode()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) return state->mKeyCode;
    return mKeyCode;
}

String SoftKeyToggle::GetKeyLabel()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) return state->mKeyLabel;
    return mKeyLabel;
}

AutoPtr<IDrawable> SoftKeyToggle::GetKeyBg()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyType) {
        return state->mKeyType->mKeyBg;
    }
    return mKeyType->mKeyBg;
}

AutoPtr<IDrawable> SoftKeyToggle::GetKeyHlBg()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyType) {
        return state->mKeyType->mKeyHlBg;
    }
    return mKeyType->mKeyHlBg;
}

Int32 SoftKeyToggle::GetColor()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyType) {
        return state->mKeyType->mColor;
    }
    return mKeyType->mColor;
}

Int32 SoftKeyToggle::GetColorHl()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyType) {
        return state->mKeyType->mColorHl;
    }
    return mKeyType->mColorHl;
}

Int32 SoftKeyToggle::GetColorBalloon()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyType) {
        return state->mKeyType->mColorBalloon;
    }
    return mKeyType->mColorBalloon;
}

Boolean SoftKeyToggle::IsKeyCodeKey()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        if (state->mKeyCode > 0) return TRUE;
        return FALSE;
    }
    return SoftKey::IsKeyCodeKey();
}

Boolean SoftKeyToggle::IsUserDefKey()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        if (state->mKeyCode < 0) return TRUE;
        return FALSE;
    }
    return SoftKey::IsUserDefKey();
}

Boolean SoftKeyToggle::IsUniStrKey()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        if (NULL != state->mKeyLabel && state->mKeyCode == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return SoftKey::IsUniStrKey();
}

Boolean SoftKeyToggle::NeedBalloon()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        return (state->mIdAndFlags & KEYMASK_BALLOON) != 0;
    }
    return SoftKey::NeedBalloon();
}

Boolean SoftKeyToggle::Repeatable()
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state) {
        return (state->mIdAndFlags & KEYMASK_REPEAT) != 0;
    }
    return SoftKey::Repeatable();
}

void SoftKeyToggle::ChangeCase(
    /* [in] */ Boolean lowerCase)
{
    AutoPtr<ToggleState> state = GetToggleState();
    if (NULL != state && NULL != state->mKeyLabel) {
        if (lowerCase) {
            state->mKeyLabel = state->mKeyLabel.ToLowerCase();
        }
        else {
            state->mKeyLabel = state->mKeyLabel.ToUpperCase();
        }
    }
}

AutoPtr<SoftKeyToggle::ToggleState> SoftKeyToggle::CreateToggleState()
{
    return new ToggleState();
}

Boolean SoftKeyToggle::SetToggleStates(
    /* [in] */ ToggleState* rootState)
{
    if (NULL == rootState) return FALSE;
    mToggleState = rootState;
    return TRUE;
}

AutoPtr<SoftKeyToggle::ToggleState> SoftKeyToggle::GetToggleState()
{
    Int32 stateId = (mKeyMask & KEYMASK_TOGGLE_STATE);
    if (0 == stateId) return NULL;

    AutoPtr<ToggleState> state = mToggleState;
    while ((NULL != state)
            && (state->mIdAndFlags & KEYMASK_TOGGLE_STATE) != stateId) {
        state = state->mNextState;
    }
    return state;
}

} // namespace Pinyin
} // namespace InputMethod
} // namespace Droid
} // namespace Elastos
