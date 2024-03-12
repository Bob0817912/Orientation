# ROS

##  什么是ROS
机器人操作系统（ROS）是一套软件库和工具，可帮助你构建机器人应用程序。从驱动程序到最先进的算法，再加上强大的开发工具，重要的是ROS全部开源，详情请见[ros.org](https://ros.org/)

## 如何使用ROS

### 安装
+ 如何你使用传统的编译安装会非常麻烦，这里我建议你使用鱼香ROS一键安装，省去你很多的烦恼

  >wget http://fishros.com/install -O fishros && . fishros

+ 进去后，你只需要按照小鱼的步骤一步一步来就好了，值得注意是装的 **ROS2(humble)** 版本，桌面版不要最小化安装

+ ROS 有很多版本，我们使用的是humble

![ros](https://fishros.com/d2lros2/humble/chapt1/get_started/1.ROS2%E5%89%8D%E4%B8%96%E4%BB%8A%E7%94%9F/imgs/image-20220602012621600.png)

### 疑惑
你可能会问，那为什么不使用ROS1，而使用ROS2呢，ROS1和ROS2有什么区别呢？，安装之后我的ROS在哪里呢？
+ 回答一：
> 我们早期其实是ROS1和ROS2一起用的，哨兵使用的ROS1，就像组长现在还再用Ubuntu20.04,而我们自瞄使用的是Ubuntu22.04，后来为了代码统一，方便管理，索性都转为ROS2，因为相对于ROS1,ROS2的更方便，包管理更轻松
+ 回答二：
> 你想问他们两个的区别，我用一张图，你便知晓：

![ros1&&ros2](https://fishros.com/d2lros2/humble/chapt1/get_started/2.ROS%E4%B8%8EROS2%E5%AF%B9%E6%AF%94/imgs/image-20210717153612576.png)

1. 他们两个的中间层发生了很大的变化，首先是系统层面，从原来的只支持linux平台变成了支持windows、mac甚至是嵌入式RTOS平台
2. 
+ 去中心化master，ROS和ROS2中间件不同之处在于，ROS2取消了master节点。
+ 去中心化后，各个节点之间可以通过DDS的节点相互发现，各个节点都是平等的，且可以1对1、1对n、n对n进行互相通信。
+ 不造通信的轮子，通信直接更换为DDS进行实现
+ 采用DDS通信，使得ROS2的实时性、可靠性和连续性上都有了增强
3. 对于应用层来说ROS2也做了很大的改进，上面那张图没有体现出来。
ROS2进行改进有：
+ Python2到Python3的支持
+ 编译系统的改进（catkin到ament）
+ C++标准更新到c++11
+ 可以使用相同 API 的进程间和进程内通信

+ 问题三：
 ROS一般会默认安装在你的 opt目录下，你可以通过： 
  >cd /opt/ros/humble/  
  > ls


### 测试
+ 安装之后，你不确定是否可以使用，那我们不妨测试一下
打开终端 ctrl+alt+T  
输入命令:
  > ros2 run turtlesim turtlesim_node   
   
   就会看到下面的画面:   

![turtlesim](https://fishros.com/d2lros2/humble/chapt1/get_started/4.ROS2%E5%88%9D%E4%BD%93%E9%AA%8C/imgs/image-20210720123734477.png)
!
在新开一个终端：
> ros2 run turtlesim turtle_teleop_key

你就可以操控小海龟了

![](https://fishros.com/d2lros2/humble/chapt1/get_started/4.ROS2%E5%88%9D%E4%BD%93%E9%AA%8C/imgs/image-20210720125026860.png)

### 学习
系统性的学习ROS2，这里有很多文档给你推荐
+ [ros官方文档](https://docs.ros.org/en/humble/)
+ [跟着小鱼学ROS](https://fishros.com/d2lros2/#/)
+ [官方的github仓库](https://github.com/ros2/ros2)
### 注意
+ 请在掌握一定C++的基础上在进行学习








