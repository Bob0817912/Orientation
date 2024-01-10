# Docker学习
![docker](https://bunnyacademy.b-cdn.net/what-is-docker.png)
+ 本文档仅供个人学习使用，涉及的安装docker的过程请自行寻找相关教程
  这里推荐[docker安装教程](https://yeasy.gitbook.io/docker_practice/install/ubuntu)

+ [什么是docker?](https://vuepress.mirror.docker-practice.com/introduction/what/)
+ [为什么使用docker？](https://vuepress.mirror.docker-practice.com/introduction/why/)

## docker的组成
Docker 包括三个基本概念

镜像（Image）
容器（Container）
仓库（Repository）
理解了这三个概念，就理解了 Docker 的整个生命周期。

## 镜像（image）
>+ 我们都知道，操作系统分为 内核 和 用户空间。对于 Linux 而言，内核启动后，会挂载 root 文件系统为其提供用户空间支持。而 Docker 镜像（Image），就相当于是一个 root 文件系统。比如官方镜像 ubuntu:22.04 就包含了完整的一套 Ubuntu 22.04 最小系统的 root 文件系统。
>+ Docker 镜像 是一个特殊的文件系统，除了提供容器运行时所需的程序、库、资源、配置等文件外，还包含了一些为运行时准备的一些配置参数（如匿名卷、环境变量、用户等）。镜像 不包含 任何动态数据，其内容在构建之后也不会被改变。
### 获取镜像
Docker从仓库获取镜像的命令
```shell
 docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
```
具体的命令可以通过 **docker pull --help** 命令看到

**镜像名称的格式**
> + Docker 镜像仓库地址：地址的格式一般是 <域名/IP>[:端口号]。默认地址是 Docker Hub(docker.io)。
>+ 仓库名：如之前所说，这里的仓库名是两段式名称，即 <用户名>/<软件>对于 Docker Hub，如果不给出用户名，则默认为 library，也就是官方镜像。
举例：
```shell
 docker pull ubuntu:22.04
```

### 运行镜像
 有了这个镜像，我们就要以容器的形式启动这个镜像并运行ta,至于什么是容器，下面会具体的讲解,如果我们启动里面的bash进行交互式操作
 ```shell
 $ docker run -it --rm ubuntu:22.04 bash
 ```
```docker run```就是运行容器的命令
+ ```-it```：这是两个参数，一个是 ```-i```：交互式操作，一个是 ```-t ```终端。我们这里打算进入 ```bash``` 执行一些命令并查看返回结果，因此我们需要交互式终端。
+ ```--rm```：这个参数是说容器退出后随之将其删除。默认情况下，为了排障需求，退出的容器并不会立即删除，除非手动 ```docker rm```。我们这里只是随便执行个命令，看看结果，不需要排障和保留结果，因此使用 --rm 可以避免浪费空间。
+ ```ubuntu:22.04```：这是指用```ubuntu:22.04``` 镜像为基础来启动容器。
+ ```bash```：放在镜像名后的是 命令，这里我们希望有个交互式 Shell，因此用的是 bash。
### 列出镜像
如果你想看自己的docker镜像，我们通常采用命令：
<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker image list
REPOSITORY                               TAG                IMAGE ID       CREATED        SIZE
ghcr.io/ros-planning/moveit2_tutorials   rolling-tutorial   f7232e2f9679   5 days ago     5.57GB
hello-world                              latest             9c7a54a9a43c   7 months ago   13.3kB
</pre>
### 镜像体积
如果你想知道自己的镜像占用的体积是多少，我们通常使用命令：

<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          2         1         5.568GB   5.568GB (99%)
Containers      1         0         0B        0B
Local Volumes   0         0         0B        0B
Build Cache     0         0         0B        0B
</pre>

### 中间层镜像
为了加速镜像构建、重复利用资源，Docker 会利用 中间层镜像。所以在使用一段时间后，可能会看到一些依赖的中间层镜像。默认的 ```docker image ls``` 列表中只会显示顶层镜像，如果希望显示包括中间层镜像在内的所有镜像的话，需要加 ```-a``` 参数。
<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker image list -a
REPOSITORY                               TAG                IMAGE ID       CREATED        SIZE
ghcr.io/ros-planning/moveit2_tutorials   rolling-tutorial   f7232e2f9679   5 days ago     5.57GB
hello-world                              latest             9c7a54a9a43c   7 months ago   13.3kB
</pre>
## 容器（container）
>1.镜像（Image）和容器（Container）的关系，就像是面向对象程序设计>中的 类 和 实例 一样，镜像是静态的定义，容器是镜像运行时的实体。容器> 可以被创建、启动、停止、删除、暂停等。
>
>2.容器的实质是进程，但与直接在宿主执行的进程不同，容器进程运行于属于自己的独立的 命名空间 (opens new window)。因此容器可以拥有自己的 root 文件系统、自己的网络配置、自己的进程空间，甚至自己的用户 ID 空间。容器内的进程是运行在一个隔离的环境里，使用起来，就好像是在一个独立于宿主的系统下操作一样。这种特性使得容器封装的应用比直接在宿主运行更加安全。也因为这种隔离的特性，很多人初学 Docker 时常常会混淆容器和虚拟机。
>
> 3.前面讲过镜像使用的是分层存储，容器也是如此。每一个容器运行时，是以镜像为基础层，在其上创建一个当前容器的存储层，我们可以称这个为容器运行时读写而准备的存储层为 容器存储层。
>
>4.容器存储层的生存周期和容器一样，容器消亡时，容器存储层也随之消亡。因此，任何保存于容器存储层的信息都会随容器删除而丢失。
>
>5.按照 Docker 最佳实践的要求，容器不应该向其存储层内写入任何数据，容器存储层要保持无状态化。所有的文件写入操作，都应该使用[数据卷](https://vuepress.mirror.docker-practice.com/data_management/volume/)（Volume）、或者 绑定宿主目录，在这些位置的读写会跳过容器存储层，直接对宿主（或网络存储）发生读写，其性能和稳定性更高。
>
>6.数据卷的生存周期独立于容器，容器消亡，数据卷不会消亡。因此，使用数据卷后，容器删除或者重新运行之后，数据却不会丢失。

### 新建并启动
+ 要运行基于镜像的容器，可以使用 docker run 命令。例如
<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$docker run -it ubuntu:latest /bin/bash
</pre>

### 列出容器
+ 要列出你有哪些容器，可以使用 docker ps -a 命令。例如
<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker ps -a
CONTAINER ID   IMAGE         COMMAND    CREATED      STATUS                  PORTS     NAMES
4b68be7b79f9   hello-world   &quot;/hello&quot;   4 days ago   Exited (0) 4 days ago             romantic_dijkstra
</pre>

### 容器连接
+ 容器中可以运行一些网络应用，要让外部也可以访问这些应用，可以通过 ```-P ```或 ```-p ```参数来指定端口映射。

+ ```-P```是容器内部端口随机映射主机端口
+ ```-p```是容器内部端口指定映射主机端口，支持的格式有 ```ip:hostPort:containerPort | ip::containerPort | hostPort:containerPort```
举例：
<pre><font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker run -d -P f7232e2f9679
975fcacc8e78a9c78c7c38bebc0231849927dca5a9fad9c0bfc571ed223a188d
<font color="#26A269"><b>笔者的小电脑</b></font>:<font color="#12488B"><b>~</b></font>$ sudo docker container list -l
CONTAINER ID   IMAGE          COMMAND                  CREATED          STATUS                      PORTS     NAMES
975fcacc8e78   f7232e2f9679   &quot;/ros_entrypoint.sh …&quot;   55 seconds ago   Exited (0) 55 seconds ago             brave_nightingale
</pre>
这里我推荐[docker从入门到实践](https://github.com/yeasy/docker_practice)
##仓库(Repository)
### docker仓库管理
官方提供了[DockerHub](https://hub.docker.com/)作为仓库来储存你的而镜像，同时提供了各个科技公司的软件和系统的镜像，你也可以通过其他远程仓库来储存你的镜像
### 注册
你可以在在 https://hub.docker.com 免费注册一个 Docker 账号。
### 登陆和退出
你可以通过输入用户名和密码来登陆DockerHub：
```shell
docker login

```
<pre><font color="#26A269"><b>笔者的小破电脑</b></font>:<font color="#12488B"><b>~</b></font>$ docker login
Log in with your Docker ID or email address to push and pull images from Docker Hub. If you don&apos;t have a Docker ID, head over to https://hub.docker.com/ to create one.
You can log in with your password or a Personal Access Token (PAT). Using a limited-scope PAT grants better security and is required for organizations using SSO. Learn more at https://docs.docker.com/go/access-tokens/

Username: conanben77
Password: 
WARNING! Your password will be stored unencrypted in /home/suibian/.docker/config.json.
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store

Login Succeeded
</pre>

退出 docker hub 可以使用以下命令：
```shell
docker logout
```


**TODO:**
1.Dockerfile的编写
2.Docker使用中的其他功能
3.常见的docker指令

参考文档：
[docker教程](https://www.runoob.com/docker/docker-tutorial.html)
[docker官方文档](https://docs.docker.com/?_gl=1*8beuxe*_ga*NTc3ODc5NjE4LjE3MDIyOTMzODY.*_ga_XJWPQMJYHQ*MTcwMjY1MjY0NS40LjEuMTcwMjY1MzM0Ny41Mi4wLjA.)
