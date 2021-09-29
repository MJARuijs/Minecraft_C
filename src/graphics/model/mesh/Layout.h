#pragma once

#include <vector>
#include "Attribute.h"

class Layout {

private:
    std::vector<Attribute> attributes;

public:
    explicit Layout(std::vector<Attribute> attributes);

    int getStride();

    [[nodiscard]] const std::vector<Attribute> & getAttributes() const;

};