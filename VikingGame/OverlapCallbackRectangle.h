#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

class OverlapCallbackRectangle
{
public:
    OverlapCallbackRectangle(double x, double y, double w, double h, void (*onOverlap)(OverlapCallbackRectangle* ptrSelf, OverlapCallbackRectangle* ptrOther), void* ptrData);
    ~OverlapCallbackRectangle();

    sf::Rect<double> getSFMLRectangle()
    {
        return mRectangle;
    }

    void CallOnOverlap(OverlapCallbackRectangle* ptrOther);

private:
    sf::Rect<double> mRectangle;
    std::function<void(OverlapCallbackRectangle* ptrSelf, OverlapCallbackRectangle* ptrOther)> mfnOnOverlap;
    void*            mptrData;
};

