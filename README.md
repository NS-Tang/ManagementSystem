# ManagementSystem

 
## 目    录
1. 绪论
    1. 课题背景及意义
    2. 国内外现状
    3. 本课题的主要内容
2. 系统的需求分析
3. 系统的设计思想
4. 系统的实现方法
5. 系统测试及效果分析
6. 总结
7. 参考文献
 
## 1．绪论
### 1.1 课题背景及意义
大学以来我们设计了各种各样的管理系统，例如图书管理系统、学籍管理系统等等、捐款管理系统。我发现这些系统都有一些公共的特点，基本上都可以抽象成一个表。其中提供对元组的增加、删除、修改、排序等功能。于是我就想要做一个能够足够通用、能够方便地修改成各种管理系统的管理系统。
### 1.2 国内外现状
### 1.3 本课题的主要内容
实现一个可以自定义关系模式的管理系统，并有登录注册的功能。
## 2．系统的需求分析
面向人群：操作公共数据（例如图书信息、捐款信息等）时面向系统管理员；
操作私人信息（例如通讯录、时间表等）时面向个人用户。
需要能进行登录与注册功能。
需要提供对管理系统的基本操作，如增加元组、删除元组、修改元组、元组排序的功能。
需要能进行管理系统关系模式的自定义，如增加属性、删除属性、更改属性。
需要能对管理系统数据的长期保存，包括元组和关系模式在内。
提供美观易操作的界面。必须是图形界面，有美观的背景，且操作便捷，可提供鼠标和键盘操作。
在Windows系统下运行。
综上需要有两个模块，一个登录模块一个管理系统模块
 
## 3．系统的设计思想
登录模块就以一般的登录注册功能为模板，管理系统模块则参考了数据模型中的关系模型。
 
## 4．系统的实现方法
采用微软提供的基础类库MFC实现，用不同的类实现各个窗口的功能。

登录与注册功能的实现流程：
 ![图4.1](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.1.png) 登录与注册功能的实现流程
如图4.1，以将登录系统分为三部分，登录模块，注册模块以及进入管理系统之后的账户操作功能。
 
![图4.2](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.2.png) 登录窗口
 
![图4.3](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.3.png) 注册窗口
进入管理系统之后按指定按键则有如下窗口：
 
![图4.4](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.4.png) 注销账号窗口
 
![图4.5](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.5.png)更改密码窗口
注册功能、注销账号功能、更改密码功能都提供了文件操作，可以进行永久更改。

管理系统的功能都集成在管理系统窗口，如图4.6所示
 
![图4.6](https://github.com/NS-Tang/ManagementSystem/blob/master/img/4.6.png) 管理系统窗口
如图4.6所示，管理系统中有如按键所示的功能，功能分别为全选行、反选行、删除所选行、保存全部行、保存所选行、打开文件、注销账号（打开窗口如图4.4）、更改密码的功能（打开窗口如图4.5）。除按钮外可提供的操作有：单击列标题排序（再次单击反向排序）、双击单元格修改分量、双击单元格空白处增加新行、右键单击单元格修改列（修改该列名、删除该列）、右键单击单元格无列空白处增加列的操作。
	 以上窗口都可使用Tab键轮询按键和文本框，并已按通用使用习惯排好序。
另外可见图4.2 与图4.6中的窗口增加了背景，增强了美观感。
支持打开从Excel复制出来的文本文档。

 

## 5．系统测试及效果分析
本系统经过多次测试与修改，已经可以支持4．系统的实现方法中所示的全部功能和流程。并且运行稳定。
 
## 6．总结
通过做本次课题实验，我掌握了微软基础类库（MFC）以及集成开发环境Visual Studio 2017的基础使用，并且掌握了如何实现图形界面系统的基本思路。
 
## 参考文献
[1]	王珊 萨师煊.数据库系统概论（第5版）.北京：高等教育出版社，2014.9
[2]	明日科技 刘锐宁 梁水 李伟明 等.Visual C++项目开发案例全程实录（第2版）.北京：清华大学出版社，2011.1

