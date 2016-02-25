
#include "elastos/droid/bluetooth/le/ResultStorageDescriptor.h"

namespace Elastos {
namespace Droid {
namespace Bluetooth {
namespace LE {

//=====================================================================
//                       ResultStorageDescriptor
//=====================================================================
CAR_INTERFACE_IMPL_2(ResultStorageDescriptor, Object, IResultStorageDescriptor, IParcelable);

ResultStorageDescriptor::ResultStorageDescriptor()
{
    mType = 0;
    mOffset = 0;
    mLength = 0;
}

ECode ResultStorageDescriptor::constructor(
    /* [in] */ Int32 type,
    /* [in] */ Int32 offset,
    /* [in] */ Int32 length)
{
    mType = type;
    mOffset = offset;
    mLength = length;
    return NOERROR;
}

ECode ResultStorageDescriptor::GetType(
    /* [out] */ Int32* result)
{
    VALIDATE_NOT_NULL(result);
    *result = mType;
    return NOERROR;
}

ECode ResultStorageDescriptor::GetOffset(
    /* [out] */ Int32* result)
{
    VALIDATE_NOT_NULL(result);
    *result = mOffset;
    return NOERROR;
}

ECode ResultStorageDescriptor::GetLength(
    /* [out] */ Int32* result)
{
    VALIDATE_NOT_NULL(result);
    *result = mLength;
    return NOERROR;
}

ECode ResultStorageDescriptor::WriteToParcel(
    /* [in] */ IParcel* dest)
{
    dest->WriteInt32(mType);
    dest->WriteInt32(mOffset);
    dest->WriteInt32(mLength);
    return NOERROR;
}

ECode ResultStorageDescriptor::constructor(
    /* [in] */ IParcel* in)
{
    ReadFromParcel(in);
    return NOERROR;
}

ECode ResultStorageDescriptor::ReadFromParcel(
    /* [in] */ IParcel* in)
{
    in->ReadInt32(&mType);
    in->ReadInt32(&mOffset);
    in->ReadInt32(&mLength);
    return NOERROR;
}

} // namespace LE
} // namespace Bluetooth
} // namespace Droid
} // namespace Elastos
