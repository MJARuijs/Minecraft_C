#include <GL/gl.h>
#include "Attribute.h"

Attribute::Attribute(int location, int size, Attribute::DataType type) : location(location), size(size), type(type) {}

Attribute::Attribute(int location, int size) : location(location), size(size), type(FLOAT) {}

int Attribute::getTypeCode(Attribute::DataType dataType) {
    switch (dataType) {
        case FLOAT:
            return GL_FLOAT;
        case INT:
            return GL_INT;
    }
    return -1;
}

int Attribute::getTypeSize(Attribute::DataType dataType) {
    switch (dataType) {
        case FLOAT:
            return sizeof(GLfloat);
        case INT:
            return sizeof(GLint);
    }
    return -1;
}

int Attribute::getTypeSize() const {
    return getTypeSize(type);
}

int Attribute::getTypeCode() const {
    return getTypeCode(type);
}

int Attribute::getLocation() const {
    return location;
}

Attribute::DataType Attribute::getType() const {
    return type;
}

int Attribute::getSize() const {
    return size;
}
