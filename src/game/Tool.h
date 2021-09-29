#pragma once

class Tool {

public:
    enum ToolMaterial {
        DEFAULT,
        WOOD,
        STONE,
        IRON,
        GOLD,
        DIAMOND
    };

    enum ToolType {
        PICK_AXE,
        AXE,
        SHOVEL,
        SWORD,
        SHEARS,
        BUCKET,
        HOE,
        ANY,
        NONE
    };
};