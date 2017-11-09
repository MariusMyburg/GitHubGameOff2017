#include "stdafx.h"
#include "OverlapCallbackRectangleManager.h"

OverlapCallbackRectangleManager::OverlapCallbackRectangleManager()
{
}

OverlapCallbackRectangleManager::~OverlapCallbackRectangleManager()
{
}

OverlapCallbackRectangleManager* OverlapCallbackRectangleManager::Instance()
{
    static OverlapCallbackRectangleManager * ptrInstance = new OverlapCallbackRectangleManager();
    return ptrInstance;
}

void OverlapCallbackRectangleManager::RegisterRectangle(OverlapCallbackRectangle * rect)
{
    mvecRegisteredRectangels.push_back(rect);
}

std::vector<OverlapCallbackRectangle*> OverlapCallbackRectangleManager::getRegisteredRectangles() const
{
    return mvecRegisteredRectangels;
}

void OverlapCallbackRectangleManager::Update()
{
    CheckForOverlaps();
}

void OverlapCallbackRectangleManager::CheckForOverlaps()
{
    for (auto firstRectangle: mvecRegisteredRectangels)
    {
        for (auto secondRectangle: mvecRegisteredRectangels)
        {
            if (firstRectangle != secondRectangle)
            {
                if (firstRectangle->getSFMLRectangle().intersects(secondRectangle->getSFMLRectangle()))
                {
                    //overlappers.push_back(firstRectangle);
                    //overlappers.push_back(secondRectangle);

                    firstRectangle->CallOnOverlap(secondRectangle);
                    secondRectangle->CallOnOverlap(firstRectangle);
                }
            }
        }
    }    
}
