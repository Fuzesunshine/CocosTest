//
//  FKSprite.h
//  AirfightGame
//
//  Created by Jason on 14-5-8.
//
//

#ifndef __AirfightGame__FKSprite__
#define __AirfightGame__FKSprite__

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
// �Զ��徫����
class FKSprite : public cocos2d::CCSprite
{
private:
    // ����ֵ
    int _lifeValue;
	bool isLastFlag;
    // Ѫ��
    LoadingBar* _HP;
    // Ѫ���ĸ�����
    float _HPInterval;
	int _positionType;
public:

	/*static  FKSprite* createSpritFrameName(const std::string filename){


		FKSprite* sprite= (FKSprite*)FKSprite::create (filename);
		  return  sprite;
	 }
*/


    // ��̬��create����
   static FKSprite* createWithSpriteFrameName(const std::string& filename)
    {
        FKSprite *sprite = new FKSprite();
		
        if (sprite && sprite->initWithFile(filename))
        {
            sprite->autorelease();
            return sprite;
        }
		
        CC_SAFE_DELETE(sprite);
        return nullptr;
		
    }
    // setter��getter
    void setLifeValue(int lifeValue){
        _lifeValue = lifeValue;
    }
    int getLifeValue(){
        return _lifeValue;
    }
	void setPositionType(int positionType){
		_positionType = positionType;
    }
    int getPositionType(){
        return _positionType;
    }
    void setHP(LoadingBar* HP){
        _HP = HP;
    }
    LoadingBar* getHP(){
        return _HP;
    }
    void setHPInterval(float HPInterval){
        _HPInterval = HPInterval;
    }
    float getHPInterval(){
        return _HPInterval;
    }

	void setIsLastFlag(bool LastFlag){
        isLastFlag = LastFlag;
    }
    bool getIsLastFlag(){
        return isLastFlag;
    }
};

#endif /* defined(__AirfightGame__FKSprite__) */
