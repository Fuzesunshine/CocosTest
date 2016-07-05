#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "FKSprite.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
public:
	// 屏幕宽度、高度的变量
	int _screenWidth , _screenHeight;
	int _count;
	 int _score;                    //实际得分

	//int irret;
	std::string text;      

	int reArg4;     //力度

	// 敌机数组
	Vector<FKSprite*> _enemyVector;

	// 钢琴白键数组
	Vector<Sprite*>_keyboardwhiteVector;

	//钢琴黑键数组
	Vector<Sprite*>_keyboardblackVector;

	void changeText(float delta); //改变label的显示函数

	void createkeyboard();      //创建钢琴键盘（初始钢琴数组）

	 void initlabeltitle();     //文本标题

	 void initlabelspeed();    //文本下落速度（固定）

	 void initlabelscore();    //文本得分（固定）

	void initpicture1();      //右上角欢迎图片场景1（小狗）

	void coverpicture1();     //右上角欢迎图片场景1（小狗）切换后

	void coverpicture2();     //右上角欢迎图片场景2（小猴）切换后

	void changepicture1(float delta);    //更新右上角场景1图片（小狗）

	void changepicture2(float delta);    //更新右上角场景2图片（猴子）

	 void initlabelscores();    //初始得分

	void changescore(float delta);       //更新得分

	void gameOver(float delta);       //退出游戏进程

	void boneMoveRemove(float delta);
	
	bool onTouchLeftBegan(Touch* touch, Event* event);
	void onTouchLeftEnded(Touch* touch, Event* event);
	bool onTouchRightBegan(Touch* touch, Event* event);
	void onTouchRightEnded(Touch* touch, Event* event);

	bool onTouchExitBegan(Touch* touch, Event* event);
	void onTouchExitEnded(Touch* touch, Event* event);

	Label* labelscore;             //得分框

	Sprite* spriteanimal;      //右上角动物表情

	void keycolorchange(float delta);    //钢琴键变色

	void keycolorback(float delta);     //钢琴键颜色还原

	void inittest();

	void changetest(float delta);

	Label* labeltest;

	Sprite* spritewhite1;
	Sprite* spritewhite2;
	Sprite* spritewhite3;
	Sprite* spritewhite4;
	Sprite* spritewhite5;
	Sprite* spritewhite6;
	Sprite* spritewhite7;
	Sprite* spritewhite8;
	Sprite* spritewhite9;
	Sprite* spritewhite10;
	Sprite* spritewhite11;
	Sprite* spritewhite12;
	Sprite* spritewhite13;
	Sprite* spritewhite14;
	Sprite* spritewhite15;
	Sprite* spritewhite16;
	Sprite* spritewhite17;
	Sprite* spritewhite18;
	Sprite* spritewhite19;
	Sprite* spritewhite20;
	Sprite* spritewhite21;
	Sprite* spritewhite22;
	Sprite* spritewhite23;
	Sprite* spritewhite24;
	Sprite* spritewhite25;
	Sprite* spritewhite26;
	Sprite* spritewhite27;
	Sprite* spritewhite28;
	Sprite* spritewhite29;
	Sprite* spritewhite30;
	Sprite* spritewhite31;
	Sprite* spritewhite32;
	Sprite* spritewhite33;
	Sprite* spritewhite34;
	Sprite* spritewhite35;
	Sprite* spritewhite36;
	Sprite* spritewhite37;
	Sprite* spritewhite38;
	Sprite* spritewhite39;
	Sprite* spritewhite40;
	Sprite* spritewhite41;
	Sprite* spritewhite42;
	Sprite* spritewhite43;
	Sprite* spritewhite44;
	Sprite* spritewhite45;
	Sprite* spritewhite46;
	Sprite* spritewhite47;
	Sprite* spritewhite48;
	Sprite* spritewhite49;
	Sprite* spritewhite50;
	Sprite* spritewhite51;
	Sprite* spritewhite52;
	Sprite* spriteblack1;
	Sprite* spriteblack2;
	Sprite* spriteblack3;
	Sprite* spriteblack4;
	Sprite* spriteblack5;
	Sprite* spriteblack6;
	Sprite* spriteblack7;
	Sprite* spriteblack8;
	Sprite* spriteblack9;
	Sprite* spriteblack10;
	Sprite* spriteblack11;
	Sprite* spriteblack12;
	Sprite* spriteblack13;
	Sprite* spriteblack14;
	Sprite* spriteblack15;
	Sprite* spriteblack16;
	Sprite* spriteblack17;
	Sprite* spriteblack18;
	Sprite* spriteblack19;
	Sprite* spriteblack20;
	Sprite* spriteblack21;
	Sprite* spriteblack22;
	Sprite* spriteblack23;
	Sprite* spriteblack24;
	Sprite* spriteblack25;
	Sprite* spriteblack26;
	Sprite* spriteblack27;
	Sprite* spriteblack28;
	Sprite* spriteblack29;
	Sprite* spriteblack30;
	Sprite* spriteblack31;
	Sprite* spriteblack32;
	Sprite* spriteblack33;
	Sprite* spriteblack34;
	Sprite* spriteblack35;
	Sprite* spriteblack36;


	// 回调更新函数，该函数每一帧都会调用
	void update(float delta);

	// 更新骨头函数
	void enemyPlaneDive(float delta);

	// 骨头离开屏幕删除函数
	void removeEnemy(float delta);

	//检测碰撞（检测on及off）
	void detectCollision(float delta);
	//检测碰撞（只检测on）
	void detectCollision1(float delta);

	int collisionwhite[100];         //检测白键碰撞

	int collisionblack[100];         //检测黑键碰撞

	int flagwhite[100];             //在白键变红色期间置为1

	int flagblack[100];             //在黑键变红色期间置为1
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__
