#include "HelloWorldScene.h"
//#include "cocostudio/CocoStudio.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string.h>                    //string类型
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

USING_NS_CC;
using namespace ui;
using namespace std;                      //命名空间
using namespace cocostudio::timeline;
using namespace cocos2d;
int i=1; //开始暂停按钮技计数
int j=1;  //场景计数
int exitFlag=0;                         //退出游戏进程标志
int jiShu=0;
int fenshu=0;
int dingWei=0;
int color_score=0;
int color_score1=0;
int  number[10];
int  number1[10];
float durationScale = 1;                //下落倍数
int reArg3=0;                           //按键开始键值
int offArg3=0;                          //按键结束键值
float tick;
int tempo=120;                          //xjc3.3 默认节拍为120每分钟
bool firstEnterFlag = true;
bool restartFlag = false;
bool nanduFlag = true;
int detectFlag = 1;
bool isEasyMode_temp = true;              //kty1.25 用于模式选择面板存储中间变量
bool isShowScore = false;                 //   标记是否已弹出结束框容器
bool isShowScoreTemp = false;                 //   标记是否已弹出结束框容器
bool isShowSlider = false;                //    标记是否弹已出速度选择容器
bool isShowSliderTemp = false;                //    标记是否弹已出速度选择容器
bool isModeSelect =  false;               //   标记是否已弹出模式选择容器
bool isModeSelectTemp =  false;               //   标记是否已弹出模式选择容器
int tempoPercent_temp = 38;

 //int HelloWorld::_score =0;
//kty1.19 左右移屏过程中骨头和键盘平移的速度/是否正在平移
float moveSpeed = 100;
int moveDir = 0; //1:正在按左键；2：正在按右键；0:按键松开

     int division;                        //    一个1/4 音符对应的tick数
     std::string title;                    //  标题
     int dhour=0;                 // 记录小时
     int dminute=0;               //记录分钟
	 int mark=0;
     std::vector<int> noteNumber;    //音符指数组
     std::vector<int> startTime;      //开始时间数组
     std::vector<int> duraTime;       //持续时间数组( tick 数)

//     int noteNumber[]={60,62,64,60,60,62,64,60,64,65,67,64,65,67,67,69,67,65,64,60,67,69,67,65,64,60,64,57,60,64,57,60};    //音符指数组
//     int startTime[]={0,2,4,6,8,10,12,14,16,18,20,24,26,28,32,33,34,35,36,38,40,41,42,43,44,46,48,50,52,56,58,60};      //开始时间数组
  
 //    int duraTime[]={4,4,4,4,4,4,4,4,4,4,2,4,4,2,8,8,8,8,4,4,8,8,8,8,4,4,4,4,2,4,4,2};       //持续时间数组


Label*  labela;
LabelTTF * pLabel;
LabelTTF * pLabel2;
LabelTTF * pLabel3;
LabelTTF * pLabel4;
LabelTTF * pLabel5;

Slider* slider;
Button* button;
Button* buttonStop;
Button* button_speed;
Button* button_mode;

Layout* showScore;          //结束框容器
Layout* showSlider;           //速度选择容器
Layout* modeSelect;            //模式选择容器
Sprite*  bgSprite;          //背景图片精灵
Sprite* buttonLeft;             //左键
Sprite* buttonRight;             //右键

int getRandX(int randX);

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//kty1.12
	noteNumber.clear();    //音符指数组
	startTime.clear();      //开始时间数组
	duraTime.clear();       //持续时间数组( tick 数)


//	slider->setPercent(50);
//	slider->setTouchEnabled(true);
//	slider->setOpacity(255);
//	pLabel2->setOpacity(255);

	button_mode->setTouchEnabled(true);
	button_mode->loadTextures("M.png","M.png","M.png");

	button_speed->setTouchEnabled(true);
	button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");

	bool nanduFlag = true;
	int detectFlag = 1;

	

	#  if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 

	log("android platform!");

	JniMethodInfo minfo;

	/**********************************************静态函数func1()********************************/
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"org/cocos2dx/cpp/AppActivity",
		"setRate",
		"()V");
	if(isHave){
		log("call void func1() succeed"); 
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
		//log("call void func2() succeed AGAIN");
		log("call void func1() succeed AGAIN");
	}
	else{
		log("call void func1() failed");
	}
	//log("call void func2() succeed AGAIN   and  again");

	/**********************************************静态函数func2() 返回division 一个1/4音符对应的tick数 ********************************/

	bool bet = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","setRate1","()I");
	if(bet)
	{
		log("call int func2() succeed");
		//返回的int值，用jint类型来接收
		 division = minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID);
		log("func2的返回值是%d",division);
		//irret = iret;
	}else
	{ log("call void func2() failed");
	return 0;}

	/**********************************************静态函数func2补()********************************/
	/*
	bool het = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","setRate2","()I");
	if(het)
	{
	log("call int func3() succeed");
	//返回的int值，用jint类型来接收
	jint itret = minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID);
	log("func3的返回值是%d",itret);
	}else
	{ log("call void func3() failed");
	return 0;}
	*/

	/**********************************************静态函数func4() 返回曲子标题********************************/

	//调用的函数有参数有返回值，这里有坑，注意Ljava/lang/String;后边的;
	bool ret = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","setRate2","()Ljava/lang/String;");
	if(ret)
	{
		log("call int func4() succeed");
		//java层的类类型对应的是jobject，把需要传递的参数写到调用函数的后边
		jstring jstr = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID);
		title = JniHelper::jstring2string(jstr);
		log("%s",title.c_str());

		pLabel4->setString(title); 
   log("call void func3()77777777 succeed AGAIN   and  again");

	}else
	{
		log("call void func3() failed");
		return 0;
	}
	// log("call void func3() succeed AGAIN   and  again");


	//Size  visibleSize=Director::getInstance()->getVisibleSize();

		/**********************************************静态函数func8() 返回值为int型数组，输出音符值********************************/
	
   isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity","setRate4", "()[Ljava/lang/String;");
    if ( isHave)
	{
  
    jobjectArray jResult = static_cast<jobjectArray>(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));//获得中间数组变量（jobjectArray）
  
    jsize resultSize = minfo.env->GetArrayLength(jResult);    //获得数组长度
     
    jsize index = 0;  
    while(index < resultSize)  
      {
        jstring eachElement = (jstring)minfo.env->GetObjectArrayElement(jResult, index);  //获得数组的第index个值
        std::string stdString = JniHelper::jstring2string(eachElement);    //将数组的第index个值从 jstring变为string型
		int n =atoi(stdString.c_str());      //将数组的第index个值从string 变为int型
		 log("每个元素的返回值是%d", n);
		
	    noteNumber.push_back(n);              //将数组的第index个值(int型)压入容器数组中
	   log("call int func8(int) succeed");
        ++index;
	    minfo.env->DeleteLocalRef(eachElement);

      }
           
	}else {
        CCLOG("FAIL: CbCCBLECentralManager - getAllPeripherals");
        return 0;
    }

	
	/**********************************************静态函数func9() 返回值为开始时间---int型数组********************************/
	
         isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity","setRate5", "()[Ljava/lang/String;");
    if ( isHave)
	{
  
    jobjectArray jResult = static_cast<jobjectArray>(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
  
    jsize resultSize = minfo.env->GetArrayLength(jResult);
     
    jsize index = 0;
    while(index < resultSize)
      {
        jstring eachElement = (jstring)minfo.env->GetObjectArrayElement(jResult, index);
        std::string stdString = JniHelper::jstring2string(eachElement);
		int n =atoi(stdString.c_str());
		 log("每个元素的返回值是%d", n);
		
	   startTime.push_back(n);
	   log("call int func9(int) succeed");
        ++index;
		 minfo.env->DeleteLocalRef(eachElement);
      }
        
	}else {
        CCLOG("FAIL: CbCCBLECentralManager - getAllPeripherals");
        return 0;
    }

	
	/**********************************************静态函数func10() 返回值为音符持续时间--int型数组********************************/
	
       isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity","setRate6", "()[Ljava/lang/String;");
    if ( isHave)
	{
  
    jobjectArray jResult = static_cast<jobjectArray>(minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID));
  
    jsize resultSize = minfo.env->GetArrayLength(jResult);
     
    jsize index = 0;
    while(index < resultSize)
      {
        jstring eachElement = (jstring)minfo.env->GetObjectArrayElement(jResult, index);
        std::string stdString = JniHelper::jstring2string(eachElement);
		int n =atoi(stdString.c_str());
		 log("每个元素的返回值是%d", n);
		
	   duraTime.push_back(n);
	   log("call int func10(int) succeed");
        ++index;
		 minfo.env->DeleteLocalRef(eachElement);
      }
	     
	}else {
        CCLOG("FAIL: CbCCBLECentralManager - getAllPeripherals");
        return 0;
    }


# endif 
	//kty1.12
	jiShu = 0;
	i=1;
    tempo=120; 
	 tick=  60/float(tempo*division);                         //xjc3.3   根据给定的tempo计算出tick数     
	tempoPercent_temp = 38;

	reArg3=0;                         //按键开始键值
    offArg3=0;                        //按键结束键值
	//jiShu=0;
	dingWei=0;
	firstEnterFlag = true;
	//slider->setPercent(50);
	//initlabeltitle();
	//initlabelspeed();
	//initlabelscore();
	//initlabelscores();
	// HelloWorld::_score =0;


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	// 获得设备可见视图大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// 获取屏幕宽度和高度
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	
	HelloWorld::_count =0;
	HelloWorld::_score =0;

	/*for(int i=0;i<=99;i++)
	    collisionwhite[i]=0;
	for(int i=0;i<=99;i++)
		collisionblack[i]=0;*/
	for(int i=0;i<=9;i++)
		number[i]=0;
	for(int i=0;i<=9;i++)
		number1[i]=0;
	for(int i=0;i<=99;i++)
	    flagwhite[i]=0;
	for(int i=0;i<=99;i++)
	    flagblack[i]=0;
	this->scheduleUpdate();




	auto rootNode = CSLoader::createNode("MainScene.csb");
	this->addChild(rootNode);

	createkeyboard();                                                                   //钢琴键盘
	initpicture1();
	//initlabeltitle();
	//initlabelspeed();
	//initlabelscore();
	//initlabelscores();
	//inittest();

	//Button* buttonchange = Button::create();                           //切换场景按钮

	button = Button::create();                                //开始暂停按钮
	buttonStop = Button::create();                            //终止，重新开始按钮 
	button_speed = Button::create();                          //速度按钮
	button_mode = Button::create();
	slider = Slider::create();                                  //滑动条      

	    bgSprite = Sprite::create("background.png");                    //背景图片 
	    bgSprite->setAnchorPoint(Vec2(0,0)); 
	    bgSprite->setPosition(Vec2(0,170));
	       this->addChild( bgSprite,2);

	//Button* close_button = Button::create();
	
	

	///////////////////////kty:左右移屏按钮/////////////////////////////////////////////

	 buttonLeft = Sprite::create("left.png");			//左键
    buttonLeft->setPosition(Point(55, visibleSize.height/2));  
    this->addChild(buttonLeft, 5);

	 buttonRight = Sprite::create("right.png");			//右键
    buttonRight->setPosition(Point(visibleSize.width-55, visibleSize.height/2));  
    this->addChild(buttonRight, 5);

	//创建左箭头单点触摸监听
	EventListenerTouchOneByOne* listenerLeft = EventListenerTouchOneByOne::create();
	listenerLeft->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerLeft->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchLeftBegan, this);
	listenerLeft->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchLeftEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerLeft, buttonLeft);
	//创建右箭头单点触摸监听
	EventListenerTouchOneByOne* listenerRight= EventListenerTouchOneByOne::create();
	listenerRight->setSwallowTouches(true);
	//开始触摸时回调onTouchBegan方法
	listenerRight->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchRightBegan, this);
	listenerRight->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchRightEnded, this);
	//添加到监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerRight, buttonRight);

	////////////////////////////////////监听容器退出///////////////////////////////////////////////////

	 // ①创建一个单点触摸事件监听器，处理触摸事件逻辑
    auto listener1 = EventListenerTouchOneByOne::create();
    // 设置是否向下传递触摸
      listener1->setSwallowTouches(true);

	  listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchExitBegan, this);
	  listener1->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchExitEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, bgSprite);




	////////////////////////////////////开始暂停按钮///////////////////////////////////////////////////



	button->setTouchEnabled(true);  
	button->loadTextures("buttonstart.png", "buttonstart.png", "");  
	button->setPosition(Point(55, 750));  

	button->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
		switch(type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			if(firstEnterFlag==true){
				button->loadTextures("buttonstop.png", "buttonstop.png", "");

	            time_t tt = time(0);                                         //获取系统初始时间
                tm* t= localtime(&tt);
				 
                 dhour= t->tm_hour;
                dminute = t->tm_min;
		        
                //log("每个元素的cscscsccs返回值是%d", t->tm_hour);

               // log("每个元素的cscscsccs返回值是%d", t->tm_min);
				//log("%s", dminute.c_str());
              //  log("call int func8888(int) 成功  succeed");

				//开始一次弹奏之后，速度、难度都要禁用
				//slider->setTouchEnabled(false);
			//	slider->setOpacity(125);
				//pLabel2->setOpacity(125);

				button_mode->setTouchEnabled(false);
				button_mode->loadTextures("M_disable.png","M_disable.png","M_disable.png");

				button_speed->setTouchEnabled(false);
				button_speed->loadTextures("speedButton_disable.png","speedButton_disable.png","speedButton_disable.png");


				firstEnterFlag = false;
			}

				if(i==2){
					i=1;
					button->loadTextures("buttonstart.png", "buttonstart.png", "");
					//Director* director =Director::getInstance();
					//director->pause();
					for (int j =0; j < _enemyVector.size();j++) 
					{
						Sprite* enemy = _enemyVector.at(j);
						//enemy->onExit();
						//enemy->pause();
					//	enemy->stopActionByTag(1);
						((Speed*)(enemy->getActionByTag(3)))->setSpeed(0);                       //xjc3.2  当暂停时，运动速度设为0  
					}
					
				}else{
					restartFlag = false;
					button->loadTextures("buttonstop.png", "buttonstop.png", ""); 
					//Director* director =Director::getInstance();
					//director->resume();
					for (int j =0; j < _enemyVector.size();j++) 
					{
						Sprite* enemy = _enemyVector.at(j);
						//enemy->onEnter();
						//enemy->resume();
					//	auto moveBy = MoveBy::create(20*division*tick, Vec2(0,-2640));          //设置Vec2表示横纵坐标的偏移量，也即是骨头运动路程
					//	moveBy->setTag(1);
					//	enemy->runAction(moveBy);
						((Speed*)(enemy->getActionByTag(3)))->setSpeed(1);                   //xjc3.2  当运动时，运动速度比例设为1
					}
					i=2;
				}	
			break;
		}
	});    

	this->addChild(button,5);
	/*
	////////////////////////////////////////////滑动条/////////////////////////////////////////////////////////////

	slider->loadBarTexture("sliderTrack.png");                                 //滑动条具体设置
	slider->loadSlidBallTextures("sliderThumb.png","sliderThumb.png","");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(Vec2(1050,750));
	slider->setPercent(50);
	            //改变滑动条事件响应，只有当游戏开始前，也即i==1（不是i=1）时，改变滑动条有效，游戏开始后无效
	slider->addEventListener([=](Ref* pSender,Slider::EventType type){
		if(type==Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			if (i==1){                                                      
			   int percent = slider->getPercent();
			  //  tick= (float)(percent/100);
                tick= (1-(float(percent)/100))+0.03;                              //注意此处要先将percent 变为float型，再除以100，否则tick结果为0
			//durationScale=(float)(sqrt(slider->getPercent()+1)/5);
			//Director* director =Director::getInstance();              //得到全部动作
			//director->getScheduler()->setTimeScale(durationScale);      //改变下落速度
			}	
		}
	});

	this->addChild(slider,5);

	*/

	//buttonchange->setTouchEnabled(true);                                           //切换场景按钮具体设置
	//buttonchange->loadTextures("buttonchange.png", "buttonchangepush.png", "buttonchangeban.png");    
	//buttonchange->setPosition(Point(55, 680));  

	//buttonchange->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
	//	switch(type){
	//	case Widget::TouchEventType::BEGAN:

	//		break;
	//	case Widget::TouchEventType::MOVED:
	//		break;
	//	case Widget::TouchEventType::ENDED:
	//		j++;
	//		if((j%2==0)&&(i==1)){
	//			auto rootNode1 = CSLoader::createNode("MainScene2.csb");
	//			this->addChild(rootNode1);
	//			coverpicture2();


	//		}
	//		else if((j%2!=0)&&(i==1)){
	//			auto rootNode2 = CSLoader::createNode("MainScene.csb");
	//			this->addChild(rootNode2);
	//			coverpicture1();


	//		}

	//		break;

	//	}
	//});    

	//this->addChild(buttonchange,5);

	//////////////////////////////////重新开始按钮//////////////////////////////////////////////
	
	buttonStop->setTouchEnabled(true);                                           //终止，重新开始按钮具体设置
	buttonStop->loadTextures("restart.png", "restart.png", "");    
	buttonStop->setPosition(Point(55, 680));  

	buttonStop->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
		switch(type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
		//	slider->setTouchEnabled(true);
		//	slider->setOpacity(255);
		//	pLabel2->setOpacity(255);
			button_mode->setTouchEnabled(true);
			button_mode->loadTextures("M.png","M.png","M.png");

			button_speed->setTouchEnabled(true);
			button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");

			i=1;
			mark=1;
			button->loadTextures("buttonstart.png", "buttonstart.png", "");  
		    color_score=0;
            color_score1=0;
			reArg3=0;                         //按键开始键值
            offArg3=0;                        //按键结束键值
			 jiShu=0;
			  dingWei=0;
			  _score=0;
			
			  firstEnterFlag = true;
			 // slider->setPercent(50);
	/*for(int i=0;i<=99;i++)
	    collisionwhite[i]=0;
	for(int i=0;i<=99;i++)
		collisionblack[i]=0;*/
	for(int i=0;i<=9;i++)
		number[i]=0;
	for(int i=0;i<=9;i++)
		number1[i]=0;
	for(int i=0;i<=99;i++)
	    flagwhite[i]=0;
	for(int i=0;i<=99;i++)
	    flagblack[i]=0;
	restartFlag = true;

	
			break;

		}
	});    

	this->addChild(buttonStop,5);

	/////////////////////速度按钮////////////////////////////////////////
	//button_speed->setTouchEnabled(true);  
	button_speed->loadTextures("speedButton.png", "speedButton.png", "");  
	button_speed->setPosition(Point(55, 610));  

	button_speed->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
		switch(type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			//弹出速度对话框后禁用其他按钮
			buttonStop->setTouchEnabled(false);
			button->setTouchEnabled(false); 
			button_mode->setTouchEnabled(false);  
			button_mode->loadTextures("M_disable.png","M_disable.png","M_disable.png");


			buttonLeft->pause();
			buttonRight->pause();

			 showSlider = Layout::create();
			showSlider->setLayoutType(LayoutType::ABSOLUTE);
			showSlider->setAnchorPoint(Vec2(0.5,0.5));
			showSlider->setContentSize(Size(640,400));
			showSlider->setBackGroundImage("mod_bg.png");
			showSlider->setPosition(Vec2(640,400));
			isShowSlider = true;
			button_speed->setTouchEnabled(false);
			button_speed->loadTextures("speedButton_disable.png","speedButton_disable.png","speedButton_disable.png");

			   pLabel2 = LabelTTF::create("下落速度","font.ttf",36);
	           pLabel2->setPosition(Vec2(275,300));
	           pLabel2->setColor(Color3B::WHITE);
	            showSlider->addChild(pLabel2);

			   pLabel5 = LabelTTF::create("","font.ttf",36);
	           pLabel5->setPosition(Vec2(400,300));
	           pLabel5->setColor(Color3B::WHITE);
	            showSlider->addChild(pLabel5);
				stringstream ss;               //int转string
			        string str;
			         ss<<tempo;
			         ss>>str;
					pLabel5->setString(str);

				
				slider = Slider::create();
				slider->loadBarTexture("sliderTrack.png");                                 //滑动条具体设置
	            slider->loadSlidBallTextures("sliderThumb.png","sliderThumb.png","");
	            slider->loadProgressBarTexture("sliderProgress.png");
	            slider->setPosition(Vec2(300,230));
	            slider->setPercent(tempoPercent_temp);
	            //改变滑动条事件响应，只有当游戏开始前，也即i==1（不是i=1）时，改变滑动条有效，游戏开始后无效
	            slider->addEventListener([=](Ref* pSender,Slider::EventType type){
		             if(type==Slider::EventType::ON_PERCENTAGE_CHANGED)
                  {
			      if (i==1){                                                      
			       int percent = slider->getPercent();
				   tempoPercent_temp = percent;
			    //  tick= (float)(percent/100);
				    tempo = 40+(int((float(percent)/100)*210));
					stringstream ss;               //int转string
			        string str;
			         ss<<tempo;
			         ss>>str;
					pLabel5->setString(str);
				   tick=  60/float(tempo*division);
                 //  tick= (1-(float(percent)/100))+0.03;                              //注意此处要先将percent 变为float型，再除以100，否则tick结果为0
		 
			               }	
	            	}
	        });
	             showSlider->addChild(slider);

          Button* buttonYes =Button::create("sure.png", "sure.png");
			      buttonYes->setTouchEnabled(true);  
			      buttonYes->setPosition(Vec2(300,130));

			      buttonYes->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
			     	switch(type){
			     	case Widget::TouchEventType::BEGAN:
				     	break;
			    	case Widget::TouchEventType::MOVED:
				    	break;
			    	case Widget::TouchEventType::ENDED:
						buttonStop->setTouchEnabled(true);
						button->setTouchEnabled(true); 
						button_mode->setTouchEnabled(true);
						button_mode->loadTextures("M.png","M.png","M.png");
						button_speed->setTouchEnabled(true);
				        button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
						buttonLeft->resume();
						buttonRight->resume();
					
				    	this->removeChild(showSlider);
						 isShowSlider = false;
					    break;
			    	}	
		    	}); 
			            showSlider->addChild(buttonYes);

	              
	             this->addChild(showSlider,9);

			break;
		}
	});    
	this->addChild(button_speed,5);

	///////////////////////////////难度选择按钮//////////////////////
	button_mode->setTouchEnabled(true);                         
	button_mode->loadTextures("M.png", "M.png", "");    
	button_mode->setPosition(Point(55, 540));  

	button_mode->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
		switch(type){
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			// 模式界面先禁用其他按钮点击
			buttonStop->setTouchEnabled(false);
			button->setTouchEnabled(false); 
			button_speed->setTouchEnabled(false);
			button_speed->loadTextures("speedButton_disable.png","speedButton_disable.png","speedButton_disable.png");
			//slider->setTouchEnabled(false);      
			buttonLeft->pause();
			buttonRight->pause();

			 modeSelect = Layout::create();
			Button* modeHard = Button::create();
			Button* modeEasy = Button::create();;
			modeSelect->setLayoutType(LayoutType::ABSOLUTE);
			modeSelect->setAnchorPoint(Vec2(0.5,0.5));
			modeSelect->setContentSize(Size(640,400));
			modeSelect->setBackGroundImage("mod_bg.png");
			modeSelect->setPosition(Vec2(640,400));
			isModeSelect =  true;
			button_mode->setTouchEnabled(false);  
			button_mode->loadTextures("M_disable.png","M_disable.png","M_disable.png");

			if(nanduFlag==true){
					modeEasy->loadTextures("mod_easy_white.png", "mod_easy_white.png", "mod_easy_white.png");
					modeHard->loadTextures("mod_hard_yellow.png", "mod_hard_yellow.png", "mod_hard_yellow.png");
					isEasyMode_temp = false;
			}else{
					modeEasy->loadTextures("mod_easy_yellow.png", "mod_easy_yellow.png", "mod_easy_yellow.png");
					modeHard->loadTextures("mod_hard_white.png", "mod_hard_white.png", "mod_hard_white.png");
					isEasyMode_temp = true;
			}
			modeEasy->setAnchorPoint(Vec2(0.5,0.5));
			modeEasy->setTouchEnabled(true);  
			modeEasy->setPosition(Vec2(180,255));
			modeEasy->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
				switch(type){
				case Widget::TouchEventType::BEGAN:
					break;
				case Widget::TouchEventType::MOVED:
					break;
				case Widget::TouchEventType::ENDED:
					modeEasy->loadTextures("mod_easy_yellow.png", "mod_easy_yellow.png", "mod_easy_yellow.png");
					modeHard->loadTextures("mod_hard_white.png", "mod_hard_white.png", "mod_hard_white.png");
					isEasyMode_temp = true;
					break;
				}
			
			});   

			modeHard->setAnchorPoint(Vec2(0.5,0.5));
			modeHard->setTouchEnabled(true);  
			modeHard->setPosition(Vec2(475,200));
			modeHard->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
				switch(type){
				case Widget::TouchEventType::BEGAN:
					break;
				case Widget::TouchEventType::MOVED:
					break;
				case Widget::TouchEventType::ENDED:
					modeEasy->loadTextures("mod_easy_white.png", "mod_easy_white.png", "mod_easy_white.png");
					modeHard->loadTextures("mod_hard_yellow.png", "mod_hard_yellow.png", "mod_hard_yellow.png");
					isEasyMode_temp = false;
					break;
				}
			
			});  

			Button* modeSure =Button::create("ok.png", "ok.png");
			modeSure->setAnchorPoint(Vec2(0.5,0.5));
			modeSure->setTouchEnabled(true);  
			modeSure->setPosition(Vec2(325,125));
			modeSure->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
				switch(type){
				case Widget::TouchEventType::BEGAN:
					break;
				case Widget::TouchEventType::MOVED:
					break;
				case Widget::TouchEventType::ENDED:
					if(isEasyMode_temp){
						detectFlag = 2;
						nanduFlag = false;
					}else{
						detectFlag = 1;
						nanduFlag = true;
					}
				buttonStop->setTouchEnabled(true);
				button->setTouchEnabled(true); 
				button_speed->setTouchEnabled(true);
				button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
				button_mode->setTouchEnabled(true);
				button_mode->loadTextures("M.png","M.png","M.png");
				//slider->setTouchEnabled(true);  
				buttonLeft->resume();
				buttonRight->resume();

					this->removeChild(modeSelect);
					isModeSelect =  false;
					break;
				}
			
			});   

			modeSelect->addChild(modeEasy);
			modeSelect->addChild(modeHard);
			modeSelect->addChild(modeSure);
			this->addChild(modeSelect,9);

	
			break;

		}
	});    

	this->addChild(button_mode,5);


	//////////////////////////////////////////////////////////////////////
	
	

	pLabel = LabelTTF::create("0","font.ttf",32);                     //显示分数
	addChild(pLabel,5);
	pLabel->setPosition(Vec2(1040,755));
	pLabel->setColor(Color3B::RED);
	
	

	pLabel3 = LabelTTF::create("当前弹对:","font.ttf",36);            //显示当前弹对
	pLabel3->setPosition(Vec2(930,755));
	pLabel3->setColor(Color3B::RED);
	addChild(pLabel3,5);
	
	pLabel4 = LabelTTF::create("","font.ttf",36);                     //显示当前曲名
	pLabel4->setPosition(Vec2(420,755));
	pLabel4->setColor(Color3B::ORANGE);
	//pLabel4->setString(title);  
	addChild(pLabel4,5);
	// log("call int func999999(int) 成功  succeed");

	 tick=  60/float(tempo*division);                         //xjc3.3   根据给定的tempo计算出tick数                 
   return true;
}

/**********************************************java方法的本地实现********************************/     

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT jstring JNICALL Java_org_cocos2dx_cpp_jniHelper_getStr    //示例：Java调用c++获得字符串

		(JNIEnv * env, jobject thiz){
			log("call void funccpp1() failed");
			return env->NewStringUTF("hello java");


	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniHelper_getNoteOn   //钢琴键按下调用

		(JNIEnv * env, jobject thiz ,jint a3 ,jint a4){
			log("call void funccpp33() failed");
			reArg3= a3;
			if (reArg3!=0){
				number[color_score]=reArg3;
				color_score++;
			}
			
			//   reArg4= a4;


	}

	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniHelper_getNoteOff         //钢琴键松开调用

		(JNIEnv * env, jobject thiz ,jint a3 ,jint a4){
			log("call void funccpp44() failed");
			offArg3= a3;
			if (offArg3!=0){
				number1[color_score1]=offArg3;
				color_score1++;
			}
			
			//   offArg4= a4;


	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniHelper_getExitFlag       //  接收退出游戏进程标志

		(JNIEnv * env, jobject thiz ,jint a3 ){
			exitFlag= a3;
			
	}

	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_jniHelper_getNum     //示例：Java调用c++获得int值（static方法）

		(JNIEnv *, jclass  clazz){
			log("call void funccpp2() failed");
			return 12345678;

	}
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_jniHelper_getScore     //Java调用c++获得分数值（static方法）

		(JNIEnv *, jclass  clazz){
			log("call void funccpp6() failed");
			return fenshu;
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	}
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_jniHelper_getHour    //Java调用c++获得时刻值（static方法）

		(JNIEnv *, jclass  clazz){
			log("call void funccpp7() failed");
			return dhour;
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	}
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_jniHelper_getMinute     //Java调用c++获得分钟值（static方法）

		(JNIEnv *, jclass  clazz){
			log("call void funccpp8() failed");
			return dminute;
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	}
	JNIEXPORT jint JNICALL Java_org_cocos2dx_cpp_jniHelper_getMark     //Java调用c++获得是否重置的标志值（static方法）

		(JNIEnv *, jclass  clazz){
			log("call void funccpp9() failed");
			return mark;
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
	}

#ifdef __cplusplus
}
#endif


# endif 

/**********************************************java方法的本地实现********************************/

void HelloWorld::createkeyboard(){
	int init_deltaX = 581;
	int creatkeyboard_Y = 85;
	int creatkeyboard_bk = 112;
	spritewhite1 = Sprite::create("white.png");
	spritewhite1->setPosition(Vec2(40-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite1);
	this->addChild(spritewhite1,10);

	spritewhite2 = Sprite::create("white.png");
	spritewhite2->setPosition(Vec2(87-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite2);
	this->addChild(spritewhite2,10);

	spritewhite3 = Sprite::create("white1.png");
	spritewhite3->setPosition(Vec2(134-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite3);
	this->addChild(spritewhite3,10);

	spritewhite4 = Sprite::create("white.png");
	spritewhite4->setPosition(Vec2(181-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite4);
	this->addChild(spritewhite4,10);

	spritewhite5 = Sprite::create("white.png");
	spritewhite5->setPosition(Vec2(228-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite5);
	this->addChild(spritewhite5,10);

	spritewhite6 = Sprite::create("white.png");
	spritewhite6->setPosition(Vec2(275-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite6);
	this->addChild(spritewhite6,10);

	spritewhite7 = Sprite::create("white.png");
	spritewhite7->setPosition(Vec2(322-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite7);
	this->addChild(spritewhite7,10);

	spritewhite8 = Sprite::create("white.png");
	spritewhite8->setPosition(Vec2(369-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite8);
	this->addChild(spritewhite8,10);

	spritewhite9 = Sprite::create("white.png");
	spritewhite9->setPosition(Vec2(416-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite9);
	this->addChild(spritewhite9,10);

	spritewhite10 = Sprite::create("white2.png");
	spritewhite10->setPosition(Vec2(463-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite10);
	this->addChild(spritewhite10,10);

	spritewhite11 = Sprite::create("white.png");
	spritewhite11->setPosition(Vec2(510-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite11);
	this->addChild(spritewhite11,10);

	spritewhite12 = Sprite::create("white.png");
	spritewhite12->setPosition(Vec2(557-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite12);
	this->addChild(spritewhite12,10);

	spritewhite13 = Sprite::create("white.png");
	spritewhite13->setPosition(Vec2(604-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite13);
	this->addChild(spritewhite13,10);

	spritewhite14 = Sprite::create("white.png");
	spritewhite14->setPosition(Vec2(651-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite14);
	this->addChild(spritewhite14,10);

	spritewhite15 = Sprite::create("white.png");
	spritewhite15->setPosition(Vec2(698-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite15);
	this->addChild(spritewhite15,10);

	spritewhite16 = Sprite::create("white.png");
	spritewhite16->setPosition(Vec2(745-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite16);
	this->addChild(spritewhite16,10);

	spritewhite17 = Sprite::create("white3.png");
	spritewhite17->setPosition(Vec2(792-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite17);
	this->addChild(spritewhite17,10);

	spritewhite18 = Sprite::create("white.png");
	spritewhite18->setPosition(Vec2(839-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite18);
	this->addChild(spritewhite18,10);

	spritewhite19 = Sprite::create("white.png");
	spritewhite19->setPosition(Vec2(886-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite19);
	this->addChild(spritewhite19,10);

	spritewhite20 = Sprite::create("white.png");
	spritewhite20->setPosition(Vec2(933-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite20);
	this->addChild(spritewhite20,10);

	spritewhite21 = Sprite::create("white.png");
	spritewhite21->setPosition(Vec2(980-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite21);
	this->addChild(spritewhite21,10);

	spritewhite22 = Sprite::create("white.png");
	spritewhite22->setPosition(Vec2(1027-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite22);
	this->addChild(spritewhite22,10);

	spritewhite23 = Sprite::create("white.png");
	spritewhite23->setPosition(Vec2(1074-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite23);
	this->addChild(spritewhite23,10);

	spritewhite24 = Sprite::create("white4.png");
	spritewhite24->setPosition(Vec2(1121-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite24);
	this->addChild(spritewhite24,10);

	spritewhite25 = Sprite::create("white.png");
	spritewhite25->setPosition(Vec2(1168-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite25);
	this->addChild(spritewhite25,10);

	spritewhite26 = Sprite::create("white.png");
	spritewhite26->setPosition(Vec2(1215-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite26);
	this->addChild(spritewhite26,10);

	spritewhite27 = Sprite::create("white.png");
	spritewhite27->setPosition(Vec2(1262-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite27);
	this->addChild(spritewhite27,10);

	spritewhite28 = Sprite::create("white.png");
	spritewhite28->setPosition(Vec2(1309-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite28);
	this->addChild(spritewhite28,10);

	spritewhite29 = Sprite::create("white.png");
	spritewhite29->setPosition(Vec2(1356-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite29);
	this->addChild(spritewhite29,10);

	spritewhite30 = Sprite::create("white.png");
	spritewhite30->setPosition(Vec2(1403-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite30);
	this->addChild(spritewhite30,10);

	spritewhite31 = Sprite::create("white5.png");
	spritewhite31->setPosition(Vec2(1450-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite31);
	this->addChild(spritewhite31,10);

	spritewhite32 = Sprite::create("white.png");
	spritewhite32->setPosition(Vec2(1497-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite32);
	this->addChild(spritewhite32,10);

	spritewhite33 = Sprite::create("white.png");
	spritewhite33->setPosition(Vec2(1544-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite33);
	this->addChild(spritewhite33,10);

	spritewhite34 = Sprite::create("white.png");
	spritewhite34->setPosition(Vec2(1591-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite34);
	this->addChild(spritewhite34,10);

	spritewhite35 = Sprite::create("white.png");
	spritewhite35->setPosition(Vec2(1638-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite35);
	this->addChild(spritewhite35,10);

	spritewhite36 = Sprite::create("white.png");
	spritewhite36->setPosition(Vec2(1685-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite36);
	this->addChild(spritewhite36,10);

	spritewhite37 = Sprite::create("white.png");
	spritewhite37->setPosition(Vec2(1732-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite37);
	this->addChild(spritewhite37,10);

	spritewhite38 = Sprite::create("white6.png");
	spritewhite38->setPosition(Vec2(1779-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite38);
	this->addChild(spritewhite38,10);

	spritewhite39 = Sprite::create("white.png");
	spritewhite39->setPosition(Vec2(1826-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite39);
	this->addChild(spritewhite39,10);

	spritewhite40 = Sprite::create("white.png");
	spritewhite40->setPosition(Vec2(1873-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite40);
	this->addChild(spritewhite40,10);

	spritewhite41 = Sprite::create("white.png");
	spritewhite41->setPosition(Vec2(1920-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite41);
	this->addChild(spritewhite41,10);

	spritewhite42 = Sprite::create("white.png");
	spritewhite42->setPosition(Vec2(1967-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite42);
	this->addChild(spritewhite42,10);

	spritewhite43 = Sprite::create("white.png");
	spritewhite43->setPosition(Vec2(2014-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite43);
	this->addChild(spritewhite43,10);

	spritewhite44 = Sprite::create("white.png");
	spritewhite44->setPosition(Vec2(2061-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite44);
	this->addChild(spritewhite44,10);

	spritewhite45 = Sprite::create("white7.png");
	spritewhite45->setPosition(Vec2(2108-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite45);
	this->addChild(spritewhite45,10);

	spritewhite46 = Sprite::create("white.png");
	spritewhite46->setPosition(Vec2(2155-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite46);
	this->addChild(spritewhite46,10);

	spritewhite47 = Sprite::create("white.png");
	spritewhite47->setPosition(Vec2(2202-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite47);
	this->addChild(spritewhite47,10);

	spritewhite48 = Sprite::create("white.png");
	spritewhite48->setPosition(Vec2(2249-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite48);
	this->addChild(spritewhite48,10);

	spritewhite49 = Sprite::create("white.png");
	spritewhite49->setPosition(Vec2(2296-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite49);
	this->addChild(spritewhite49,10);

	spritewhite50 = Sprite::create("white.png");
	spritewhite50->setPosition(Vec2(2343-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite50);
	this->addChild(spritewhite50,10);

	spritewhite51 = Sprite::create("white.png");
	spritewhite51->setPosition(Vec2(2390-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite51);
	this->addChild(spritewhite51,10);

	spritewhite52 = Sprite::create("white8.png");
	spritewhite52->setPosition(Vec2(2437-init_deltaX,creatkeyboard_Y));
	_keyboardwhiteVector.pushBack(spritewhite52);
	this->addChild(spritewhite52,10);

	spriteblack1 = Sprite::create("black.png");
	spriteblack1->setPosition(Vec2(64-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack1);
	this->addChild(spriteblack1,10);

	spriteblack2 = Sprite::create("black.png");
	spriteblack2->setPosition(Vec2(158-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack2);
	this->addChild(spriteblack2,10);

	spriteblack3 = Sprite::create("black.png");
	spriteblack3->setPosition(Vec2(205-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack3);
	this->addChild(spriteblack3,10);

	spriteblack4 = Sprite::create("black.png");
	spriteblack4->setPosition(Vec2(299-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack4);
	this->addChild(spriteblack4,10);

	spriteblack5 = Sprite::create("black.png");
	spriteblack5->setPosition(Vec2(346-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack5);
	this->addChild(spriteblack5,10);

	spriteblack6 = Sprite::create("black.png");
	spriteblack6->setPosition(Vec2(393-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack6);
	this->addChild(spriteblack6,10);

	spriteblack7 = Sprite::create("black.png");
	spriteblack7->setPosition(Vec2(487-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack7);
	this->addChild(spriteblack7,10);

	spriteblack8 = Sprite::create("black.png");
	spriteblack8->setPosition(Vec2(534-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack8);
	this->addChild(spriteblack8,10);

	spriteblack9 = Sprite::create("black.png");
	spriteblack9->setPosition(Vec2(628-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack9);
	this->addChild(spriteblack9,10);

	spriteblack10 = Sprite::create("black.png");
	spriteblack10->setPosition(Vec2(675-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack10);
	this->addChild(spriteblack10,10);

	spriteblack11 = Sprite::create("black.png");
	spriteblack11->setPosition(Vec2(722-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack11);
	this->addChild(spriteblack11,10);

	spriteblack12 = Sprite::create("black.png");
	spriteblack12->setPosition(Vec2(816-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack12);
	this->addChild(spriteblack12,10);

	spriteblack13 = Sprite::create("black.png");
	spriteblack13->setPosition(Vec2(863-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack13);
	this->addChild(spriteblack13,10);

	spriteblack14 = Sprite::create("black.png");
	spriteblack14->setPosition(Vec2(957-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack14);
	this->addChild(spriteblack14,10);

	spriteblack15 = Sprite::create("black.png");
	spriteblack15->setPosition(Vec2(1004-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack15);
	this->addChild(spriteblack15,10);

	spriteblack16 = Sprite::create("black.png");
	spriteblack16->setPosition(Vec2(1051-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack16);
	this->addChild(spriteblack16,10);

	spriteblack17 = Sprite::create("black.png");
	spriteblack17->setPosition(Vec2(1145-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack17);
	this->addChild(spriteblack17,10);

	spriteblack18 = Sprite::create("black.png");
	spriteblack18->setPosition(Vec2(1192-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack18);
	this->addChild(spriteblack18,10);

	spriteblack19 = Sprite::create("black.png");
	spriteblack19->setPosition(Vec2(1286-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack19);
	this->addChild(spriteblack19,10);

	spriteblack20 = Sprite::create("black.png");
	spriteblack20->setPosition(Vec2(1333-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack20);
	this->addChild(spriteblack20,10);

	spriteblack21 = Sprite::create("black.png");
	spriteblack21->setPosition(Vec2(1380-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack21);
	this->addChild(spriteblack21,10);

	spriteblack22 = Sprite::create("black.png");
	spriteblack22->setPosition(Vec2(1474-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack22);
	this->addChild(spriteblack22,10);

	spriteblack23 = Sprite::create("black.png");
	spriteblack23->setPosition(Vec2(1521-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack23);
	this->addChild(spriteblack23,10);

	spriteblack24 = Sprite::create("black.png");
	spriteblack24->setPosition(Vec2(1615-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack24);
	this->addChild(spriteblack24,10);
	

	spriteblack25 = Sprite::create("black.png");
	spriteblack25->setPosition(Vec2(1662-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack25);
	this->addChild(spriteblack25,10);

	spriteblack26 = Sprite::create("black.png");
	spriteblack26->setPosition(Vec2(1709-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack26);
	this->addChild(spriteblack26,10);

	spriteblack27 = Sprite::create("black.png");
	spriteblack27->setPosition(Vec2(1803-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack27);
	this->addChild(spriteblack27,10);

	spriteblack28 = Sprite::create("black.png");
	spriteblack28->setPosition(Vec2(1850-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack28);
	this->addChild(spriteblack28,10);

	spriteblack29 = Sprite::create("black.png");
	spriteblack29->setPosition(Vec2(1944-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack29);
	this->addChild(spriteblack29,10);

	spriteblack30 = Sprite::create("black.png");
	spriteblack30->setPosition(Vec2(1991-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack30);
	this->addChild(spriteblack30,10);

	spriteblack31 = Sprite::create("black.png");
	spriteblack31->setPosition(Vec2(2038-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack31);
	this->addChild(spriteblack31,10);

	spriteblack32 = Sprite::create("black.png");
	spriteblack32->setPosition(Vec2(2132-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack32);
	this->addChild(spriteblack32,10);

	spriteblack33 = Sprite::create("black.png");
	spriteblack33->setPosition(Vec2(2179-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack33);
	this->addChild(spriteblack33,10);

	spriteblack34 = Sprite::create("black.png");
	spriteblack34->setPosition(Vec2(2273-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack34);
	this->addChild(spriteblack34,10);

	spriteblack35 = Sprite::create("black.png");
	spriteblack35->setPosition(Vec2(2320-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack35);
	this->addChild(spriteblack35,10);

	spriteblack36 = Sprite::create("black.png");
	spriteblack36->setPosition(Vec2(2367-init_deltaX,creatkeyboard_bk));
	_keyboardblackVector.pushBack(spriteblack36);
	this->addChild(spriteblack36,10);
}

void HelloWorld::initlabeltitle(){

	TTFConfig ttfconfig("font.ttf",36);
	auto label1= Label::createWithTTF(ttfconfig,"当前曲目：abcdefghijk-qwerdf");               //中文冒号
	label1->setPosition(Vec2(420,755));
	label1->setColor(Color3B::GREEN);
	label1->setString(title);                                                            //  改变标题
	this->addChild(label1,5);
}

void HelloWorld::initlabelspeed(){
	TTFConfig ttfconfig1("font.ttf",36);
	auto label2= Label::createWithTTF(ttfconfig1,"下落速度:");               //中文冒号
	label2->setPosition(Vec2(840,755));
	label2->setColor(Color3B::YELLOW);
	this->addChild(label2,5);
}

void HelloWorld::initlabelscore(){
	TTFConfig ttfconfig2("font.ttf",36);
	auto label3= Label::createWithTTF(ttfconfig2,"当前弹对:");               //中文冒号
	label3->setPosition(Vec2(930,700));
	label3->setColor(Color3B::RED);
	this->addChild(label3,5);
}

void HelloWorld::initlabelscores(){
	stringstream ss;               //int转string
	string str;
	ss<<_score;
	ss>>str;

	labelscore = Label::create("score","Courier",32);
	addChild(labelscore);
	labelscore->setPosition(Vec2(1040,700));


	//TTFConfig ttfconfig("font.ttf",36);
	// labelscore= Label::createWithTTF(ttfconfig,"");               //中文冒号
	//labelscore->setPosition(Vec2(1040,700));
	labelscore->setColor(Color3B::RED);
	labelscore->setString(str);
	this->addChild(labelscore,5);
}

void HelloWorld::changescore(float delta){



	fenshu=_score;                                            //将此时的分数赋给全局变量fenshu
	stringstream ss;               //int转string
	//std::string changeStr="score:";
	string str;
	ss<<_score;
	ss>>str;
	//changeStr=changeStr + str;
	pLabel->setString(str);
}


void HelloWorld::initpicture1(){

	spriteanimal = Sprite::create("dogwelcome.png");
	spriteanimal->setPosition(Vec2(1210,735));
	this->addChild(spriteanimal,5);

}

void HelloWorld::coverpicture1(){

	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("dogwelcome.png");
	spriteanimal->setTexture(texture);                                           //替换精灵纹理

}

void HelloWorld::coverpicture2(){

	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("monkeywelcome.png");
	spriteanimal->setTexture(texture);                                           //替换精灵纹理

}

void HelloWorld::changepicture1(float delta){
	if((_score>=10)&&(_score<20)){
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("dogsad.png");
		spriteanimal->setTexture(texture);                                           //替换精灵纹理
	}
	if((_score>=20)&&(_score<30)){
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("doggogo.png");
		spriteanimal->setTexture(texture);                                           //替换精灵纹理
	}
	if(_score>=30){
		Texture2D* texture = TextureCache::sharedTextureCache()->addImage("doghappy.png");
		spriteanimal->setTexture(texture);                                           //替换精灵纹理
	}
}



void HelloWorld::keycolorchange(float delta){
	for(int i =0;i<=9;i++){
		if (number[i]!=0)
	{
		int ireArg3=number[i]-20;
		int V[88]={36,0,37,38,1,39,2,40,41,3,42,4,43,5,44,45,6,46,7,47,48,8,49,9,50,10,51,52,11,53,12,54,55,13,56,14,57,15,58,59
		,16,60,17,61,62,18,63,19,64,20,65,66,21,67,22,68,69,23,70,24,71,25,72,73,26,74,27,75,76,28,77,29,78,30,79,80,31,81,32,82,83,33,84,34,85,35,86,87};
		if(V[ireArg3-1]<=35){
			int a=V[ireArg3-1];
			auto keyboardblack = _keyboardblackVector.at(a);
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("blackred.png");
			keyboardblack->setTexture(texture);                                           //替换精灵纹理
			flagblack[a]=1;
		
		}
		else{
			int b=V[ireArg3-1]-36;
			auto keyboardwhite = _keyboardwhiteVector.at(b);
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("whitered.png");
			keyboardwhite->setTexture(texture);                                           //替换精灵纹理
			flagwhite[b]=1;
		}
	}
	}
	for(int i=0;i<=9;i++)
		number[i]=0;
	    color_score=0;
}

void HelloWorld::keycolorback(float delta){
	for(int i =0;i<=9;i++){
		if (number1[i]!=0)
	    {
		int ioffArg3=number1[i]-20;
		int V[88]={36,0,37,38,1,39,2,40,41,3,42,4,43,5,44,45,6,46,7,47,48,8,49,9,50,10,51,52,11,53,12,54,55,13,56,14,57,15,58,59
		,16,60,17,61,62,18,63,19,64,20,65,66,21,67,22,68,69,23,70,24,71,25,72,73,26,74,27,75,76,28,77,29,78,30,79,80,31,81,32,82,83,33,84,34,85,35,86,87};
		if(V[ioffArg3-1]<=35){
			int a=V[ioffArg3-1];
			auto keyboardblack = _keyboardblackVector.at(a);
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("black.png");
			keyboardblack->setTexture(texture);                                           //替换精灵纹理
			flagblack[a]=0;
			
		}
		else{
			int b=V[ioffArg3-1]-36;
			auto keyboardwhite = _keyboardwhiteVector.at(b);
			if(b==2){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white1.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==9){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white2.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==16){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white3.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==23){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white4.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==30){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white5.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==37){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white6.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==44){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white7.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else if(b==51){
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white8.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			else {
			Texture2D* texture = TextureCache::sharedTextureCache()->addImage("white.png");
			keyboardwhite->setTexture(texture);                                            //替换精灵纹理
			}
			flagwhite[b]=0;
			
		}
	}
	}
	for(int i=0;i<=9;i++)
		number1[i]=0;
	    color_score1=0;
}

//回调更新函数，该函数每一帧都会调用    
void HelloWorld::update(float delta){
	/*for(int i=0;i<=99;i++)
		collisionwhite[i]=0;
	for(int i=0;i<=99;i++)
		collisionblack[i]=0;*/
	enemyPlaneDive(delta); // 敌机俯冲
	//_count++;
	 if(i==2){
			jiShu++;
	}
	//enemyPlaneDive(delta);
	//changeText( delta);    //改变label的显示
	//gameOver( delta);       //退出游戏进程
	removeEnemy(delta); // 删除离开屏幕的敌机
	changescore(delta);
	//if(j%2!=0)
	changepicture1(delta);
	/*if(j%2==0)
		changepicture2(delta);*/
	if(detectFlag==1)
		detectCollision(delta);
	if(detectFlag==2)
		detectCollision1(delta);

	//changetest(delta);
	keycolorchange(delta);
	keycolorback(delta);

	//kty1.19骨头左右平移
	boneMoveRemove(delta);
}

/*************************骨头左右平移**********************************/
void HelloWorld::boneMoveRemove(float delta)
	 {
		 if(moveDir == 0)// || _keyboardwhiteVector.at(0)->getActionByTag(0)->isDone())
		 {
			 for(int i =0; i < _enemyVector.size(); i++)
			 {
				Sprite* enemy = _enemyVector.at(i);
				
				enemy->stopActionByTag(0);
			 }
		 }
}



/*************************退出游戏进程**********************************/

void HelloWorld::gameOver(float delta)
	 {
		if(exitFlag==1)
		{
			Director::getInstance()->end();
			#  if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
			  exit(0);
			# endif 
			exitFlag=0;
		}
	 }



/*************************改变label的显示内容**********************************/
//void HelloWorld::changeText(float delta)//添加一个方法来改变label的显示内容
//{
//	if (reArg3!=0)
//	{   
//		std::string str;
//		std::stringstream ss;
//		std::string changeStr="get value";
//		ss<<reArg3;
//		ss>>str;
//		changeStr=changeStr + str;
//		//log("call void func111() failed");
//		pLabel ->setString(changeStr);
//
//		//log("call void func222() failed");
//		// changeStr ="get value ";
//	}
//
//	if ( offArg3!=0)
//	{
//		std::string str;
//		std::stringstream ss;
//		std::string changeStr="get value";
//		ss<< offArg3;
//		ss>>str;
//		changeStr=changeStr + str;
//		//log("call void func333() failed");
//		labela ->setString(changeStr);
//
//		//log("call void func444() failed");
//		// changeStr ="get value ";
//	}
//
//}

/*************************敌机相关函数*****************************************/
  //骨头下落函数
void HelloWorld::enemyPlaneDive(float delta){
	bool flag = false;
	int lifeValue;
	// 自定义精灵类FKSprite
	FKSprite* enemyPlane;
	
	  if(i==2){                                                              //当开始键按下后才开始掉骨头
		 
       for(int i=dingWei;i<startTime.size();i++)                                          //shiyan32  本是startTime.size()
		{
            int randX = noteNumber[i]-20;                                      // 根据不同音符确定其位置（横坐标）
			int posX = randX-1;
			int positionX=getRandX(randX);                               
		//	if (jiShu== (startTime[i]*100)){
			if (jiShu== int(startTime[i]*60*tick)){                              // 根据每个音符开始时间生成骨头精灵       
				//log("call void JISHUXXXXXXXXXXX successed");
				if (j%2!=0){
             
					int picture = float(duraTime[i]*8)/division;                                        // 根据不同时长tick 数生成不同的骨头
					switch (picture)
					{
					case  48:
               enemyPlane= FKSprite::createWithSpriteFrameName("e24.png");
			   enemyPlane->setTag(24);
			   enemyPlane->setPositionType(posX);
			            break;
					case  32:
               enemyPlane= FKSprite::createWithSpriteFrameName("e16.png");
			   enemyPlane->setTag(16);
			   enemyPlane->setPositionType(posX);
			            break;
					case  24:
               enemyPlane= FKSprite::createWithSpriteFrameName("e12.png");
			   enemyPlane->setTag(12);
			   enemyPlane->setPositionType(posX);
			            break;
					case  16:
               enemyPlane= FKSprite::createWithSpriteFrameName("e8.png");
			   enemyPlane->setTag(8);
			   enemyPlane->setPositionType(posX);
			            break;
					case  12:
               enemyPlane= FKSprite::createWithSpriteFrameName("e6.png");
			   enemyPlane->setTag(6);
			   enemyPlane->setPositionType(posX);
			            break;
					case  8:
               enemyPlane= FKSprite::createWithSpriteFrameName("e4.png");
			   enemyPlane->setTag(4);
			   enemyPlane->setPositionType(posX);
			            break;
					case  6:
               enemyPlane= FKSprite::createWithSpriteFrameName("e3.png");
			   enemyPlane->setTag(3);
			   enemyPlane->setPositionType(posX);
			            break;
					case  4:
               enemyPlane= FKSprite::createWithSpriteFrameName("e2.png");
			   enemyPlane->setTag(2);
			   enemyPlane->setPositionType(posX);
			            break;
					case  3:
               enemyPlane= FKSprite::createWithSpriteFrameName("e1.png");
			   enemyPlane->setTag(9);
			   enemyPlane->setPositionType(posX);
			            break;
					case  2:
               enemyPlane= FKSprite::createWithSpriteFrameName("e0.png");
			   enemyPlane->setTag(1);
			   enemyPlane->setPositionType(posX);
			            break;
					case  1:
               enemyPlane= FKSprite::createWithSpriteFrameName("a.png");
			   enemyPlane->setTag(0);
			   enemyPlane->setPositionType(posX);
			            break;
					default:
			   enemyPlane= FKSprite::createWithSpriteFrameName("b.png");
			   enemyPlane->setTag(5);
			   enemyPlane->setPositionType(posX);
						break;
					}
					if(i==(startTime.size()-1))
					{
						enemyPlane->setIsLastFlag(true);
					}else{
						enemyPlane->setIsLastFlag(false);
					}

			   flag = true;
			   dingWei=i+1;                                                               // 便于下次遍历时，不用从头开始  
			    //log("每个元素的返回值是%d", i);
				}
			    else if(j%2==0){
               enemyPlane= FKSprite::createWithSpriteFrameName("e1.png");                         // 根据场景生成香蕉         
			   enemyPlane->setTag(1);
			   enemyPlane->setPositionType(posX);
			   flag = true;
			   dingWei=i+1;
				}
         //    }else if  (jiShu< (startTime[i]*100)){
			}else if(jiShu< int(startTime[i]*60*tick)) {                         // 若计数器值小于骨头该下落的时间，则后面不遍历 for循环 
				// dingWei=i;
				break;
			}

			

		if (flag) {
			//log("call void countXXXXXXXXXXX failed");
			enemyPlane->setLifeValue(4);
			//enemyPlane->setPosition(positionX, _screenHeight+enemyPlane->getContentSize().height);
			enemyPlane->setAnchorPoint(Vec2(0.5,0));                             //设置锚点为精灵的横中纵下位置
		//	enemyPlane->setPosition(positionX, _screenHeight);                   // 设置高度为屏幕高度     
			//kty1.20实现新下落的骨头以琴键当前位置为参照选取下落X坐标
			enemyPlane->setPosition(positionX-40+_keyboardwhiteVector.at(0)->getPositionX(), _screenHeight);                   // 设置高度为屏幕高度  
			// MoveBy动作，高度为屏幕高度
		//	auto moveBy = MoveBy::create(10,
		//		Vec2(0, -enemyPlane->getPosition().y-enemyPlane->getContentSize().height));
			auto moveBy = MoveBy::create(20*division*tick,               //该10*division*tick  是因为一个1/4音符对应division个tick，根据运动量和1/4音符精灵的比值得出
				Vec2(0,-2640));          //设置Vec2表示横纵坐标的偏移量，也即是骨头运动路程
			// 骨头落下
			//moveBy->setTag(1);
			//enemyPlane->runAction(moveBy);
			auto action3 = Speed::create(moveBy,1.0f);          // xjc3.2 增加对速度的控制，方便开始和暂停
			 action3->setTag(3);
			enemyPlane->runAction(action3);

			//kty1.20实现新下落的骨头以100的速度平移
			if(moveDir == 1)
			{
				float deltaX = 40 - _keyboardwhiteVector.at(0)->getPositionX();
				auto moveBy = MoveBy::create(deltaX/moveSpeed, Vec2(deltaX,0)); 
				moveBy->setTag(0);
				enemyPlane->runAction(moveBy);
			}else if(moveDir == 2){
				float deltaX = _keyboardwhiteVector.at(51)->getPositionX() - 1240;
				auto moveBy = MoveBy::create(deltaX/moveSpeed, Vec2(-deltaX,0));  
				moveBy->setTag(0);
				enemyPlane->runAction(moveBy);
			}
			// 将骨头精灵添加到敌机数组
			_enemyVector.pushBack(enemyPlane);
			// 将骨头添加到当前层
			this->addChild(enemyPlane,5);
			     flag = false;

		          }

		}

	  }

}

// 骨头离开屏幕删除函数
void HelloWorld::removeEnemy(float delta){
	// 遍历所有的骨头精灵
	for (unsigned int k =0; k < _enemyVector.size(); k++) {
		auto enemy = _enemyVector.at(k);
		if(restartFlag == true){
             this->removeChild(enemy,true);
			// 从_enemyVector集合中删除骨头精灵
			_enemyVector.eraseObject(enemy);
	      
		}
		// 如果骨头尾端下落至琴键上沿，删除骨头精灵
		else 
		if (enemy->getPosition().y <= -(enemy->getContentSize().height)+170)   
		{     
			if((detectFlag==1)&&(enemy->getLifeValue()==0)){
				_score++;
			}
			if((detectFlag==2)&&(enemy->getLifeValue()==2)){
				_score++;
			}
			// 从当前层删除该骨头精灵
			this->removeChild(enemy,true);
			// 从_enemyVector集合中删除骨头精灵
			_enemyVector.eraseObject(enemy);

			//kty1.23实现最后一个骨头出屏幕时弹出对话框
			if(enemy->getIsLastFlag())
		{
			 showScore = Layout::create();
			showScore->setLayoutType(LayoutType::ABSOLUTE);
			showScore->setAnchorPoint(Vec2(0.5,0.5));
			showScore->setContentSize(Size(640,400));
			showScore->setBackGroundImage("mod_bg.png");
			showScore->setPosition(Vec2(640,400));
			isShowScore = true;
			buttonStop->setTouchEnabled(false);
			button->setTouchEnabled(false); 

			Button* buttonSure =Button::create("ok.png", "ok.png");
			buttonSure->setTouchEnabled(true);  
			buttonSure->setPosition(Vec2(325,150));

			buttonSure->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type){
				switch(type){
				case Widget::TouchEventType::BEGAN:
					break;
				case Widget::TouchEventType::MOVED:
					break;
				case Widget::TouchEventType::ENDED:
					//slider->setTouchEnabled(true);
					//slider->setOpacity(255);
					//pLabel2->setOpacity(255);
					button_mode->setTouchEnabled(true);
					button_mode->loadTextures("M.png","M.png","M.png");

					buttonStop->setTouchEnabled(true);
		        	button->setTouchEnabled(true); 

					button_speed->setTouchEnabled(true);
					button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
					i=1;
					mark=1;
					button->loadTextures("buttonstart.png", "buttonstart.png", "");  
					color_score=0;
					color_score1=0;
					reArg3=0;                         //按键开始键值
					offArg3=0;                        //按键结束键值
					jiShu=0;
					dingWei=0;
					_score=0;
				//	tick=0.5;
					firstEnterFlag = true;
					//slider->setPercent(50);
					for(int i=0;i<=9;i++)
						number[i]=0;
					for(int i=0;i<=9;i++)
						number1[i]=0;
					for(int i=0;i<=99;i++)
						flagwhite[i]=0;
					for(int i=0;i<=99;i++)
						flagblack[i]=0;
					restartFlag = true;
					
		
					this->removeChild(showScore);
					isShowScore = false;

					break;
				}
			
			});   
			stringstream ss;               //int转string
			string str;
			ss<<_score;
			ss>>str;
			//changeStr=changeStr + str;
			//pLabel->setString(str);
			auto scoreLable = LabelTTF::create("","font.ttf",36);
			scoreLable->setPosition(Vec2(325,275));
			scoreLable->setColor(Color3B::WHITE);
			scoreLable->setString("弹完啦！您的分数是： "+ str); 
			showScore->addChild(scoreLable);



			showScore->addChild(buttonSure);

			this->addChild(showScore,9);
			}
		}
		


	}
}

void HelloWorld::detectCollision(float delta){
	int Y[88]={36,0,37,38,1,39,2,40,41,3,42,4,43,5,44,45,6,46,7,47,48,8,49,9,50,10,51,52,11,53,12,54,55,13,56,14,57,15,58,59
		,16,60,17,61,62,18,63,19,64,20,65,66,21,67,22,68,69,23,70,24,71,25,72,73,26,74,27,75,76,28,77,29,78,30,79,80,31,81,32,82,83,33,84,34,85,35,86,87};
	for (unsigned int i =0; i < _enemyVector.size(); i++) {
		auto enemy = _enemyVector.at(i);
		int posF = enemy->getPositionType();
		if(Y[posF]<=35){                           
			int a=Y[posF];
			switch(enemy->getTag())
			{
			case 0:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>130)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>130)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<135)&&(enemy->getPosition().y>95)){
					enemy->setLifeValue(1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<135)&&(enemy->getPosition().y>95)){
					enemy->setLifeValue(0);
				}
				break;
			case 1:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>110)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>110)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<137)&&(enemy->getPosition().y>77)){
					enemy->setLifeValue(1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<137)&&(enemy->getPosition().y>77)){
					enemy->setLifeValue(0);
				}
				break;
			case 9:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>100)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>100)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<130)&&(enemy->getPosition().y>60)){
					enemy->setLifeValue(1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<130)&&(enemy->getPosition().y>60)){
					enemy->setLifeValue(0);
				}
				break;
			case 2:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<124)&&(enemy->getPosition().y>44)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<124)&&(enemy->getPosition().y>44)){
					enemy->setLifeValue(0);
				}
				break;
			case 3:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>70)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>70)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<111)&&(enemy->getPosition().y>11)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<111)&&(enemy->getPosition().y>11)){
					enemy->setLifeValue(0);
				}
				break;
			case 4:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>50)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>50)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<98)&&(enemy->getPosition().y>-22)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<98)&&(enemy->getPosition().y>-22)){
					enemy->setLifeValue(0);
				}
				break;
			case 6:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>30)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>30)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<52)&&(enemy->getPosition().y>-88)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<52)&&(enemy->getPosition().y>-88)){
					enemy->setLifeValue(0);
				}
				break;
			case 8:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>10)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>10)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<6)&&(enemy->getPosition().y>-154)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<6)&&(enemy->getPosition().y>-154)){
					enemy->setLifeValue(0);
				}
				break;
			case 12:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-60)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-60)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-56)&&(enemy->getPosition().y>-286)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-56)&&(enemy->getPosition().y>-286)){
					enemy->setLifeValue(0);
				}
				break;
			case 16:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-120)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-120)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-128)&&(enemy->getPosition().y>-418)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-128)&&(enemy->getPosition().y>-418)){
					enemy->setLifeValue(0);
				}
				break;
			case 24:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-250)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-250)){
					enemy->setLifeValue(2);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-262)&&(enemy->getPosition().y>-682)){
					enemy->setLifeValue(1);
				}
				if((flagblack[a]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-262)&&(enemy->getPosition().y>-682)){
					enemy->setLifeValue(0);
				}
				break;
			default:
				break;
			
			}
			
		}
		else{                                

			int b = Y[posF]-36;
			switch(enemy->getTag())
			{
			case 0:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>130)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>130)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<135)&&(enemy->getPosition().y>95)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<135)&&(enemy->getPosition().y>95)){
					enemy->setLifeValue(0);
				}
				break;
			case 1:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>110)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>110)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<137)&&(enemy->getPosition().y>77)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<137)&&(enemy->getPosition().y>77)){
					enemy->setLifeValue(0);
				}
				break;
			case 9:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>100)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>100)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<130)&&(enemy->getPosition().y>60)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<130)&&(enemy->getPosition().y>60)){
					enemy->setLifeValue(0);
				}
				break;
			case 2:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<124)&&(enemy->getPosition().y>44)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<124)&&(enemy->getPosition().y>44)){
					enemy->setLifeValue(0);
				}
				break;
			case 3:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>70)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>70)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<111)&&(enemy->getPosition().y>11)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<111)&&(enemy->getPosition().y>11)){
					enemy->setLifeValue(0);
				}
				break;
			case 4:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>50)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>50)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<98)&&(enemy->getPosition().y>-22)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<98)&&(enemy->getPosition().y>-22)){
					enemy->setLifeValue(0);
				}
				break;
			case 6:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>30)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>30)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<52)&&(enemy->getPosition().y>-88)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<52)&&(enemy->getPosition().y>-88)){
					enemy->setLifeValue(0);
				}
				break;
			case 8:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>10)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>10)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<6)&&(enemy->getPosition().y>-154)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<6)&&(enemy->getPosition().y>-154)){
					enemy->setLifeValue(0);
				}
				break;
			case 12:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-60)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-60)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-56)&&(enemy->getPosition().y>-286)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-56)&&(enemy->getPosition().y>-286)){
					enemy->setLifeValue(0);
				}
				break;
			case 16:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-120)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-120)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-128)&&(enemy->getPosition().y>-418)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-128)&&(enemy->getPosition().y>-418)){
					enemy->setLifeValue(0);
				}
				break;
			case 24:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-250)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-250)){
					enemy->setLifeValue(2);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==2)&&(enemy->getPosition().y<-262)&&(enemy->getPosition().y>-682)){
					enemy->setLifeValue(1);
				}
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==1)&&(enemy->getPosition().y<-262)&&(enemy->getPosition().y>-682)){                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
					enemy->setLifeValue(0);
				}
				break;
			default:
				break;
			

				

			}
		}

	}
}
void HelloWorld::detectCollision1(float delta){
	int Y[88]={36,0,37,38,1,39,2,40,41,3,42,4,43,5,44,45,6,46,7,47,48,8,49,9,50,10,51,52,11,53,12,54,55,13,56,14,57,15,58,59
		,16,60,17,61,62,18,63,19,64,20,65,66,21,67,22,68,69,23,70,24,71,25,72,73,26,74,27,75,76,28,77,29,78,30,79,80,31,81,32,82,83,33,84,34,85,35,86,87};
	for (unsigned int i =0; i < _enemyVector.size(); i++) {
		auto enemy = _enemyVector.at(i);
		int posF = enemy->getPositionType();
		if(Y[posF]<=35){                           
			int a=Y[posF];
			switch(enemy->getTag())
			{
			case 0:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>125)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>125)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 1:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>107)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>107)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 9:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 2:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>74)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>74)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 3:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>41)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>41)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 4:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>8)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>8)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 6:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-58)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-58)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 8:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-124)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-124)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 12:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-256)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-256)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 16:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-388)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-388)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 24:
				if((flagblack[a]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-652)){
					enemy->setLifeValue(3);
				}
				if((flagblack[a]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-652)){
					enemy->setLifeValue(2);
				}
				
				break;
			default:
				break;
			
			}
			
		}
		else{                                

			int b = Y[posF]-36;
			switch(enemy->getTag())
			{
			case 0:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>125)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>125)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 1:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>107)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>107)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 9:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>90)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 2:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>74)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>74)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 3:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>41)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>41)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 4:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>8)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>8)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 6:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-58)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-58)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 8:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-124)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-124)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 12:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-256)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-256)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 16:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-388)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-388)){
					enemy->setLifeValue(2);
				}
				
				break;
			case 24:
				if((flagwhite[b]==0)&&(enemy->getLifeValue()==4)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-652)){
					enemy->setLifeValue(3);
				}
				if((flagwhite[b]==1)&&(enemy->getLifeValue()==3)&&(enemy->getPosition().y<170)&&(enemy->getPosition().y>-652)){
					enemy->setLifeValue(2);
				}
				
				break;
			default:
				break;
			

				

			}
		}

	}
}
int   getRandX(int randX){
		  int positionX;
	switch (randX)
		{
		case 1:
		return	positionX=32;
			break;
		case 2:
		return  positionX=64;
			break;
		case 3:
		return	positionX=95;
			break;
		case 4:
		return	positionX=126;
			break;
		case 5:
		return	positionX=158;
			break;
		case 6:
		return	positionX=181;
			break;
		case 7:
		return	positionX=205;
			break;
		case 8:
		return	positionX=236;
			break;
		case 9:
		return	positionX=267;
			break;
		case 10:
		return	positionX=299;
			break;
		case 11:
		return	positionX=322;
			break;
		case 12:
		return	positionX=346;
			break;
		case 13:
		return	positionX=369;
			break;
		case 14:
		return	positionX=393;
			break;
		case 15:
		return	positionX=424;
			break;
		case 16:
		return	positionX=455;
			break;
		case 17:
		return	positionX=487;
			break;
		case 18:
		return	positionX=510;
			break;
		case 19:
		return	positionX=534;
			break;
		case 20:
		return	positionX=565;
			break;
		case 21:
		return	positionX=596;
			break;
		case 22:
		return	positionX=628;
			break;
		case 23:
		return	positionX=651;
			break;
		case 24:
		return	positionX=675;
			break;
		case 25:
		return	positionX=698;
			break;
		case 26:
		return	positionX=722;
			break;
		case 27:
		return	positionX=753;
			break;
		case 28:
		return	positionX=784;
			break;
		case 29:
		return	positionX=816;
			break;
		case 30:
		return	positionX=839;
			break;
		case 31:
		return	positionX=863;
			break;
		case 32:
		return	positionX=894;
			break;
		case 33:
		return	positionX=925;
			break;
		case 34:
		return	positionX=957;
			break;
		case 35:
		return	positionX=980;
			break;
		case 36:
		return	positionX=1004;
			break;
		case 37:
		return	positionX=1027;
			break;
		case 38:
		return	positionX=1051;
			break;
		case 39:
		return	positionX=1082;
			break;
		case 40:
		return	positionX=1113;
			break;
		case 41:
		return	positionX=1145;
			break;
		case 42:
		return	positionX=1168;
			break;
		case 43:
		return	positionX=1192;
			break;
		case 44:
		return	positionX=1223;
			break;
		case 45:
		return	positionX=1254;
			break;
		case 46:
		return	positionX=1286;
			break;
		case 47:
		return	positionX=1309;
			break;
		case 48:
		return	positionX=1333;
			break;
		case 49:
		return	positionX=1356;
			break;
		case 50:
		return	positionX=1380;
			break;
		case 51:
		return	positionX=1411;
			break;
		case 52:
		return	positionX=1442;
			break;
		case 53:
		return	positionX=1474;
			break;
		case 54:
		return	positionX=1497;
			break;
		case 55:
		return	positionX=1521;
			break;
		case 56:
		return	positionX=1552;
			break;
		case 57:
		return	positionX=1583;
			break;
		case 58:
		return	positionX=1615;
			break;
		case 59:
		return	positionX=1638;
			break;
		case 60:
		return	positionX=1662;
			break;
		case 61:
		return	positionX=1685;
			break;
		case 62:
		return	positionX=1709;
			break;
		case 63:
		return	positionX=1740;
			break;
		case 64:
		return	positionX=1771;
			break;
		case 65:
		return	positionX=1803;
			break;
		case 66:
		return	positionX=1826;
			break;
		case 67:
		return	positionX=1850;
			break;
		case 68:
		return	positionX=1881;
			break;
		case 69:
		return	positionX=1912;
			break;
		case 70:
		return	positionX=1944;
			break;
		case 71:
		return	positionX=1967;
			break;
		case 72:
		return	positionX=1991;
			break;
		case 73:
		return	positionX=2014;
			break;
		case 74:
		return	positionX=2038;
			break;
		case 75:
		return	positionX=2069;
			break;
		case 76:
		return	positionX=2100;
			break;
		case 77:
		return	positionX=2132;
			break;
		case 78:
		return	positionX=2155;
			break;
		case 79:
		return	positionX=2179;
			break;
		case 80:
		return	positionX=2210;
			break;
		case 81:
		return	positionX=2241;
			break;
		case 82:
		return	positionX=2273;
			break;
		case 83:
		return	positionX=2296;
			break;
		case 84:
		return	positionX=2320;
			break;
		case 85:
		return	positionX=2343;   
			break;
		case 86:
		return	positionX=2367;
			break;
		case 87:
		return	positionX=2398;
			break;
		case 88:
		return	positionX=2437;
			break;
		default:
		return	positionX=2437;
			break;
		  }
 		}


bool HelloWorld::onTouchLeftBegan(Touch* touch, Event* event){	
	Sprite* firstWhite =_keyboardwhiteVector.at(0);
	float firstX = firstWhite->getPositionX();
	float deltaX = 40 - firstX;
	float timeL = deltaX/moveSpeed;

	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
			moveDir = 1;
			for(int i=0;i<52;i++)
			{
				Sprite* keyboardwhite =_keyboardwhiteVector.at(i);
				float whiteX = keyboardwhite->getPositionX();
				float whiteY = keyboardwhite->getPositionY();
				keyboardwhite->runAction(MoveTo::create(timeL, Point(whiteX+deltaX, whiteY)));
			}
			for(int i=0;i<36;i++)
			{
				Sprite* keyboardblack =_keyboardblackVector.at(i);
				float blackX = keyboardblack->getPositionX();
				float blackY = keyboardblack->getPositionY();
				keyboardblack->runAction(MoveTo::create(timeL, Point(blackX+deltaX, blackY)));

			}
			for (int i =0; i < _enemyVector.size();i++) 
			{
				Sprite* enemy = _enemyVector.at(i);
				float enemyX = enemy->getPositionX();
				float enemyY = enemy->getPositionY();
				cocos2d::MoveBy* mbAction = MoveTo::create(timeL, Point(enemyX+deltaX, enemyY));
				mbAction->setTag(0);
				enemy->runAction(mbAction);

			}		
		return true;
	}
	else
	{
		return false;
	}
	
}
void HelloWorld::onTouchLeftEnded(Touch* touch, Event* event){
			
	moveDir = 0;
	for(int i=0;i<52;i++)
	{
		Sprite* keyboardwhite =_keyboardwhiteVector.at(i);
		keyboardwhite->stopAllActions();

	}
	for(int i=0;i<36;i++)
	{
		Sprite* keyboardblack =_keyboardblackVector.at(i);
		keyboardblack->stopAllActions();
	}
	for (int i =0; i < _enemyVector.size();i++) 
	{
		Sprite* enemy = _enemyVector.at(i);
		enemy->stopActionByTag(0);
	}
	
}
bool HelloWorld::onTouchRightBegan(Touch* touch, Event* event){
	Sprite* lastWhite =_keyboardwhiteVector.at(51);
	float lastX = lastWhite->getPositionX();
	float deltaX = lastX - 1240;
	float timeR = deltaX/moveSpeed;

	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
			moveDir = 2;
			for(int i=0;i<52;i++)
			{
				Sprite* keyboardwhite =_keyboardwhiteVector.at(i);
				float whiteX = keyboardwhite->getPositionX();
				float whiteY = keyboardwhite->getPositionY();
				keyboardwhite->runAction(MoveTo::create(timeR, Point(whiteX-deltaX, whiteY)));

			}
			for(int i=0;i<36;i++)
			{
				Sprite* keyboardblack =_keyboardblackVector.at(i);
				float blackX = keyboardblack->getPositionX();
				float blackY = keyboardblack->getPositionY();
				keyboardblack->runAction(MoveTo::create(timeR, Point(blackX-deltaX, blackY)));

			}
			for (int i =0; i < _enemyVector.size();i++) 
			{
				Sprite* enemy = _enemyVector.at(i);
				float enemyX = enemy->getPositionX();
				float enemyY = enemy->getPositionY();
				cocos2d::MoveBy* mbAction = MoveTo::create(timeR, Point(enemyX-deltaX, enemyY));
				mbAction->setTag(0);
				enemy->runAction(mbAction);
				
			}
		return true;
	}
	else
	{
		return false;
	}
	
}
void HelloWorld::onTouchRightEnded(Touch* touch, Event* event){
	moveDir = 0;
	for(int i=0;i<52;i++)
	{
		Sprite* keyboardwhite =_keyboardwhiteVector.at(i);
		keyboardwhite->stopAllActions();

	}
	for(int i=0;i<36;i++)
	{
		Sprite* keyboardblack =_keyboardblackVector.at(i);
		keyboardblack->stopAllActions();
	}
	for (int i =0; i < _enemyVector.size();i++) 
	{
		Sprite* enemy = _enemyVector.at(i);
		enemy->stopActionByTag(0);
	}
	
}

bool HelloWorld::onTouchExitBegan(Touch* touch, Event* event){
	

	//获取可见区域尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取的当前触摸的对象，并转化为精灵类型
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//获取当前坐标
	auto location = target->convertToNodeSpace(touch->getLocation());
	//获取精灵的大小
	auto size = target->getContentSize();
	//创建一个矩形对象，其大小与精灵相同
	auto rect = Rect(0, 0, size.width, size.height);
	//判断触摸点是否在目标的范围内
	if( rect.containsPoint(location) )
	{
		if(isShowScore == true)
		{
			  auto size1 = showScore->getContentSize();         //获取容器的大小
			  auto rect1 = Rect(showScore->getPositionX()-size1.width/2, showScore->getPositionY()-size1.height/2-170, size1.width, size1.height);   //创建一个矩形对象，其大小与容器相同
				if(!rect1.containsPoint(location))
				{
				    button_mode->setTouchEnabled(true);
					button_mode->loadTextures("M.png","M.png","M.png");

					buttonStop->setTouchEnabled(true);
		        	button->setTouchEnabled(true); 

					button_speed->setTouchEnabled(true);
					button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
					i=1;
					mark=1;
					button->loadTextures("buttonstart.png", "buttonstart.png", "");  
					color_score=0;
					color_score1=0;
					reArg3=0;                         //按键开始键值
					offArg3=0;                        //按键结束键值
					jiShu=0;
					dingWei=0;
					_score=0;
				//	tick=0.5;
					firstEnterFlag = true;
					//slider->setPercent(50);
					for(int i=0;i<=9;i++)
						number[i]=0;
					for(int i=0;i<=9;i++)
						number1[i]=0;
					for(int i=0;i<=99;i++)
						flagwhite[i]=0;
					for(int i=0;i<=99;i++)
						flagblack[i]=0;
					restartFlag = true;
		            this->removeChild(showScore);
					isShowScoreTemp=true;
			      //  isShowScore = false;
				}

		}
		
		else if(isShowSlider == true)
		{
			  auto size1 = showSlider->getContentSize();         //获取容器的大小
			  auto rect1 = Rect(showSlider->getPositionX()-size1.width/2,showSlider->getPositionY()-size1.height/2-170, size1.width, size1.height);   //创建一个矩形对象，其大小与容器相同
				if(!rect1.containsPoint(location))
				{
			            buttonStop->setTouchEnabled(true);
						button->setTouchEnabled(true); 
						button_mode->setTouchEnabled(true);
						button_mode->loadTextures("M.png","M.png","M.png");
						button_speed->setTouchEnabled(true);
			      	    button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
						buttonLeft->resume();
						buttonRight->resume();
					
				    	this->removeChild(showSlider);
						isShowSliderTemp = true;
					//	 isShowSlider = false;
				}
		         
		}
		
		else if(isModeSelect == true)
		{
			  auto size1 = modeSelect->getContentSize();         //获取容器的大小
			  auto rect1 = Rect(modeSelect->getPositionX()-size1.width/2, modeSelect->getPositionY()-size1.height/2-170, size1.width, size1.height);   //创建一个矩形对象，其大小与容器相同
				if(!rect1.containsPoint(location))
				{
			        if(isEasyMode_temp){
						detectFlag = 2;
						nanduFlag = false;
					}else{
						detectFlag = 1;
						nanduFlag = true;
					}
				buttonStop->setTouchEnabled(true);
				button->setTouchEnabled(true); 
				button_speed->setTouchEnabled(true);
				button_speed->loadTextures("speedButton.png","speedButton.png","speedButton.png");
				button_mode->setTouchEnabled(true);
				button_mode->loadTextures("M.png","M.png","M.png");
				//slider->setTouchEnabled(true);  
				buttonLeft->resume();
				buttonRight->resume();

					this->removeChild(modeSelect);
					isModeSelectTemp =  true;
				//	isModeSelect =  false;
				}
		}
		

		return true;
	}
	else
	{
		return false;
	}
	
}

void HelloWorld::onTouchExitEnded(Touch* touch, Event* event){
	  
	 if((isShowScore == false)&&(isShowSlider == false)&&(isModeSelect == false))
	{
         if(firstEnterFlag==true){
				button->loadTextures("buttonstop.png", "buttonstop.png", "");

	            time_t tt = time(0);                                         //获取系统初始时间
                tm* t= localtime(&tt);
				 
                 dhour= t->tm_hour;
                dminute = t->tm_min;

				//开始一次弹奏之后，速度、难度都要禁用
				//slider->setTouchEnabled(false);
			//	slider->setOpacity(125);
				//pLabel2->setOpacity(125);

				button_mode->setTouchEnabled(false);
				button_mode->loadTextures("M_disable.png","M_disable.png","M_disable.png");

				button_speed->setTouchEnabled(false);
				button_speed->loadTextures("speedButton_disable.png","speedButton_disable.png","speedButton_disable.png");


				firstEnterFlag = false;
			}

				if(i==2){
					i=1;
					button->loadTextures("buttonstart.png", "buttonstart.png", "");
					//Director* director =Director::getInstance();
					//director->pause();
					for (int j =0; j < _enemyVector.size();j++) 
					{
						Sprite* enemy = _enemyVector.at(j);
						//enemy->onExit();
						//enemy->pause();
						//enemy->stopActionByTag(1);
						((Speed*)(enemy->getActionByTag(3)))->setSpeed(0);                       //xjc3.2  当暂停时，运动速度设为0  
					}
					
				}else{
					restartFlag = false;
					button->loadTextures("buttonstop.png", "buttonstop.png", ""); 
					//Director* director =Director::getInstance();
					//director->resume();
					for (int j =0; j < _enemyVector.size();j++) 
					{
						Sprite* enemy = _enemyVector.at(j);
						//enemy->onEnter();
						//enemy->resume();
					//	auto moveBy = MoveBy::create(20*division*tick, Vec2(0,-2640));          //设置Vec2表示横纵坐标的偏移量，也即是骨头运动路程
					//	moveBy->setTag(1);
					//	enemy->runAction(moveBy);
						((Speed*)(enemy->getActionByTag(3)))->setSpeed(1);                       //xjc3.2  当运动时，运动速度比例设为1  
					}
					i=2;
				}
				
	}
	     if(isShowScoreTemp == true)
	   {
          isShowScore = false;
		  isShowScoreTemp = false;
	   }
	     if( isShowSliderTemp  == true)
	   {
           isShowSlider = false;
		    isShowSliderTemp  = false;
	   }
		 if(isModeSelectTemp == true)
	   {
          isModeSelect =  false;
		   isModeSelectTemp  = false;
	   }
}
