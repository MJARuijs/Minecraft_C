#include "Animation.h"

#include <utility>

Animation::Animation(std::function<void()> onFinish) : started(false), onFinish(std::move(onFinish)) {}

