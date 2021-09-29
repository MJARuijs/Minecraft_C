#pragma once

#include <functional>

class Animation {

protected:
    std::function<void()> onFinish;
    bool started;

public:
    explicit Animation(std::function<void()> onFinish);

//    virtual void start();
    virtual bool apply(float deltaTime) = 0;

};