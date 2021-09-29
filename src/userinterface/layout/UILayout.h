#include <string>
#include <map>
#include "constraints/ConstraintSet.h"
#include "../../math/Color.h"

class UILayout {

private:
    std::string id;
    std::map<std::string, ConstraintSet> itemChanges;

public:
    UILayout(std::string id, std::map<std::string, ConstraintSet> & itemChanges);
    explicit UILayout(std::string id);

    std::string getId();

    void operator+=(const std::pair<std::string, ConstraintSet>& itemChange);

    bool containsConstraintForItem(const std::string & itemId);
    ConstraintSet getConstraint(const std::string & itemId);
};