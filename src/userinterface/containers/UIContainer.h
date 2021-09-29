//#include <map>
//#include <vector>
//#include "../items/Item.h"
//#include "../../graphics/Quad.h"
//#include "../../devices/input/Mouse.h"
//
//class UIContainer {
//
//private:
//    std::map<Item, std::vector<std::string>> postPonedItems;
//    std::vector<std::string> boundlessChildren;
//
//
//protected:
//    const std::string id;
//    Quad quad;
//    std::vector<Item> children;
//
//public:
//    UIContainer(const std::string & id);
//
//    Vec2 getTranslation();
//    Vec2 scaleVector();
//
//    Item & findById(const std::string & id);
//    void allowChildToIgnoreBounds(const std::string & id);
//    bool isChildBoundless(const std::string & id);
//
//    bool update(Mouse & mouse, float aspectRatio, float deltaTime);
//
//    void apply();
//};