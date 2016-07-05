#向iOS工程中添加cocos工程
## 大致思路
我的解决方案的大致思路是这样的：将cocos引擎添加到iOS工程中，在合适的位置进入cocos游戏界面。
## 步骤
### 向iOS工程中加入文件
首先按cocos官网上的方法生成cocos工程，向iOS工程中添加cocos工程中的Classes/、proj.ios_mac/ios/、resources复制到iOS工程的文件夹中。向工程中添加文件：Classes/、ios/、cocos2d/build/cocos2d_libs.xcodeproj。
### 更改工程设置
1.向工程中添加如图所示的库
![Markdown](http://i2.piimg.com/568443/bf0194e50b26bd19.png)
2.向 Building Setting>Header Search Paths 中添加项
![Markdown](http://i2.piimg.com/568443/906b2df33c673389.png)
3.在 Building Setting 中更改工程设置
![Markdown](http://i2.piimg.com/568443/d89b38ff2fa46a2b.png)
![Markdown](http://i4.piimg.com/568443/59b00a328c3dfcc9.png)
4.删除原工程的 main.m、AppDelegate.h/m 文件
### 更改工程入口
具体设置参照[博客](http://blog.csdn.net/crayondeng/article/details/16828555, "我是标题")，大致的思路就是修改cocos工程的入口AppController文件，在需要嵌入游戏的位置初始化RootViewController即可。

