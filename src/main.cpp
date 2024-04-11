#include <Geode/Geode.hpp>
using namespace geode::prelude;
CCLayer* firstEverLayer = nullptr;
#include <Geode/modify/CCLayer.hpp>
class $modify(CCLayerExt, CCLayer) {
    static CCLayer* create(void) {
        auto rtn = CCLayer::create();
        //first layer created catch to add search path
        if (!firstEverLayer) {
            firstEverLayer = rtn;
            CCFileUtils::sharedFileUtils()->addPriorityPath((dirs::getTempDir() / "Resources").string().c_str());
        }
        return rtn;
    }
};