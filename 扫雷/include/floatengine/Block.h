#pragma once
#include "Object.h"

class Block :
    public Object
{
public:
    Block();
    ~Block();
    virtual void onEvent_User(int index) override;
};

