#include "Layout.h"

#include <utility>

Layout::Layout(std::vector<Attribute> attributes) : attributes(std::move(attributes)) {}

int Layout::getStride() {
    int stride = 0;
    for (auto & attribute : attributes) {
        stride += attribute.getTypeSize() * attribute.getSize();
    }
    return stride;
}

const std::vector<Attribute> &Layout::getAttributes() const {
    return attributes;
}
