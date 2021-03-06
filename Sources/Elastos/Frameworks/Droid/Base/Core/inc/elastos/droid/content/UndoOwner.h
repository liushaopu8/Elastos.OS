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

#ifndef __ELASTOS_DROID_CONTENT_UNDOOWNER_H__
#define __ELASTOS_DROID_CONTENT_UNDOOWNER_H__

#include "Elastos.Droid.Content.h"
#include <elastos/core/Object.h>

namespace Elastos {
namespace Droid {
namespace Content {

/**
 * Representation of an owner of {@link UndoOperation} objects in an {@link UndoManager}.
 *
 * @hide
 */
class UndoOwner
    : public Object
    , public IUndoOwner
{
public:
    CAR_INTERFACE_DECL()

    UndoOwner();

    virtual ~UndoOwner();

    CARAPI constructor(
        /* [in] */ const String& tag);

    CARAPI GetTag(
        /* [out] */ String* tag);

    CARAPI GetData(
        /* [out] */ IInterface** data);

private:
    String mTag;

    AutoPtr<IUndoManager> mManager;
    AutoPtr<IInterface> mData;
    Int32 mOpCount;

    // For saving/restoring state.
    Int32 mStateSeq;
    Int32 mSavedIdx;
};

}
}
}

#endif // __ELASTOS_DROID_CONTENT_UNDOOWNER_H__
