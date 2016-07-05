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
	// ��Ļ��ȡ��߶ȵı���
	int _screenWidth , _screenHeight;
	int _count;
	 int _score;                    //ʵ�ʵ÷�

	//int irret;
	std::string text;      

	int reArg4;     //����

	// �л�����
	Vector<FKSprite*> _enemyVector;

	// ���ٰ׼�����
	Vector<Sprite*>_keyboardwhiteVector;

	//���ٺڼ�����
	Vector<Sprite*>_keyboardblackVector;

	void changeText(float delta); //�ı�label����ʾ����

	void createkeyboard();      //�������ټ��̣���ʼ�������飩

	 void initlabeltitle();     //�ı�����

	 void initlabelspeed();    //�ı������ٶȣ��̶���

	 void initlabelscore();    //�ı��÷֣��̶���

	void initpicture1();      //���Ͻǻ�ӭͼƬ����1��С����

	void coverpicture1();     //���Ͻǻ�ӭͼƬ����1��С�����л���

	void coverpicture2();     //���Ͻǻ�ӭͼƬ����2��С��л���

	void changepicture1(float delta);    //�������Ͻǳ���1ͼƬ��С����

	void changepicture2(float delta);    //�������Ͻǳ���2ͼƬ�����ӣ�

	 void initlabelscores();    //��ʼ�÷�

	void changescore(float delta);       //���µ÷�

	void gameOver(float delta);       //�˳���Ϸ����

	void boneMoveRemove(float delta);
	
	bool onTouchLeftBegan(Touch* touch, Event* event);
	void onTouchLeftEnded(Touch* touch, Event* event);
	bool onTouchRightBegan(Touch* touch, Event* event);
	void onTouchRightEnded(Touch* touch, Event* event);

	bool onTouchExitBegan(Touch* touch, Event* event);
	void onTouchExitEnded(Touch* touch, Event* event);

	Label* labelscore;             //�÷ֿ�

	Sprite* spriteanimal;      //���ϽǶ������

	void keycolorchange(float delta);    //���ټ���ɫ

	void keycolorback(float delta);     //���ټ���ɫ��ԭ

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


	// �ص����º������ú���ÿһ֡�������
	void update(float delta);

	// ���¹�ͷ����
	void enemyPlaneDive(float delta);

	// ��ͷ�뿪��Ļɾ������
	void removeEnemy(float delta);

	//�����ײ�����on��off��
	void detectCollision(float delta);
	//�����ײ��ֻ���on��
	void detectCollision1(float delta);

	int collisionwhite[100];         //���׼���ײ

	int collisionblack[100];         //���ڼ���ײ

	int flagwhite[100];             //�ڰ׼����ɫ�ڼ���Ϊ1

	int flagblack[100];             //�ںڼ����ɫ�ڼ���Ϊ1
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);


};

#endif // __HELLOWORLD_SCENE_H__
