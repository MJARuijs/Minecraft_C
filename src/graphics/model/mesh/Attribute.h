#pragma once

class Attribute {

public:
    enum DataType {
        FLOAT,
        INT
    };

    Attribute(int location, int size, DataType type);
    Attribute(int location, int size);

    [[nodiscard]] int getLocation() const;
    [[nodiscard]] DataType getType() const;

    [[nodiscard]] int getTypeSize() const;
    [[nodiscard]] int getTypeCode() const;

    [[nodiscard]] int getSize() const;

    static int getTypeCode(DataType dataType);
    static int getTypeSize(DataType dataType);

private:
    int location;
    int size;
    DataType type;

};