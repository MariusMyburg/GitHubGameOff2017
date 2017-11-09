#include "stdafx.h"
#include "OverlapCallbackRectangle.h"
#include "OverlapCallbackRectangleManager.h"




OverlapCallbackRectangle::OverlapCallbackRectangle(double x, double y, double w, double h, void(*onOverlap)(OverlapCallbackRectangle* ptrSelf, OverlapCallbackRectangle* ptrOther), void* ptrData)
{
    mRectangle = sf::Rect<double>(x - (w/2.f), y - (h/2.f), w, h);
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

