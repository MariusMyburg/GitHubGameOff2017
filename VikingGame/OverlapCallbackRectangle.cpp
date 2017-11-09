#include "stdafx.h"
#include "OverlapCallbackRectangle.h"
#include "OverlapCallbackRectangleManager.h"




OverlapCallbackRectangle::OverlapCallbackRectangle(void(*onOverlap)(OverlapCallbackRectangle* ptrSelf, OverlapCallbackRectangle* ptrOther), void* ptrData)
{
    mfnOnOverlap = onOverlap;
    mptrData = ptrData;
    OverlapCallbackRectangleManager::Instance()->RegisterRectangle(this);
}

OverlapCallbackRectangle::~OverlapCallbackRectangle()
{
}

void OverlapCallbackRectangle::CallOnOverlap(OverlapCallbackRectangle* ptrOther)
{
    mfnOnOverlap(this, ptrOther);
}

