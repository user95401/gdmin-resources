#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		auto rtn = MenuLayer::init();
		GameManager::get()->fadeInMusic("Owady nocy.mp3"_spr);
		//menu
		auto menu = this->getChildByIDRecursive("bottom-menu");
		//myButton
		{
			auto myButton = CCMenuItemSpriteExtra::create(
				CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
				this,
				menu_selector(MyMenuLayer::onMyButton)
			);
			myButton->setID("myButton"_spr);
			//updateLayout is shit or idk
			//myButton->setScale(1.01f);
			//myButton->m_baseScale = myButton->getScale();//unselect scale fix
			menu->addChild(myButton);
		};
		menu->updateLayout();
		//tulip
		{
			this->addChild(CCSprite::create("GD_icon_round.png"_spr), 10, 194);
			this->getChildByTag(194)->setPosition(CCMenu::create()->getPosition());//centerpoint
			this->getChildByTag(194)->setScale(0.55f);
		};
		//794576380968697896.png
		{
			this->addChild(CCSprite::createWithSpriteFrameName("794576380968697896.png"_spr), 10, 549);
			this->getChildByTag(549)->setPosition(CCMenu::create()->getPosition());//centerpoint
		}
		return rtn;
	}
	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
	}
};

void myAddSpriteFramesWithFile(CCSpriteFrameCache* pClass, const char* pszPlist) {
	// Call the original
	pClass->addSpriteFramesWithFile(pszPlist);
	log::debug("loading the {}", pszPlist);
}

$execute{
	Mod::get()->hook(
		reinterpret_cast<void*>(
			// All of this is to get the address of ccDrawCircle
			geode::addresser::getNonVirtual(
				// This is used because this function is overloaded,
				// otherwise just a regular function pointer would suffice (&foobar)
				geode::modifier::Resolve<const char*>::func(&cocos2d::CCSpriteFrameCache::addSpriteFramesWithFile)
			)
		),
		&myAddSpriteFramesWithFile, // Our detour
		"cocos2d::CCSpriteFrameCache::addSpriteFramesWithFile", // Display name, shows up on the console
		tulip::hook::TulipConvention::Thiscall // Static free-standing cocos2d functions are cdecl
	);
}
