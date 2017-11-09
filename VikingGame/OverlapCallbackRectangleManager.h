#pragma once
#include "OverlapCallbackRectangle.h"
#include <vector>

class OverlapCallbackRectangleManager
{
    friend class OverlapCallbackRectangle;
public:    
    ~OverlapCallbackRectangleManager();

    static OverlapCallbackRectangleManager* Instance();

    void RegisterRectangle(OverlapCallbackRectangle* rect);
    std::vector<OverlapCallbackRectangle*> getRegisteredRectangles() const;

    // Be sure to call this from your game loop.
    void Update();

private:
    OverlapCallbackRectangleManager();

    // Does the checking and inf there is an overlap, calls the handler.
    // You do not need to call this manuallt, OverlapCallbackRectangle will call it 
    // from its Update() method.
    void CheckForOverlaps();

    std::vector<OverlapCallbackRectangle*> mvecRegisteredRectangels;
};

