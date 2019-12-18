# Laptop配置安装流程

(一)安装Ubuntu系统

由于数据库不兼容，建议安装Ubuntu15.10



(二)配置镜像源



(三)安装svn，下载Laptop代码

安装svn

$sudo apt-get install subversion

下载Laotop文件

$sudo svn checkout --username jiuxiaxixi http://code.taobao.org/svn/laotop





(四)使用cpanm安装Perl模块

1.概述

cpanm是所用过的安装Perl模块最简便的方法。

关于cpanm:

http://search.cpan.org/~miyagawa/App-cpanminus-1.0015/lib/App/cpanminus.pm



2.安装cpanm

Cpanm其实是一个可执行文件，所以将它下载到bin目录下，然后添加执行权限就可以使用了。

在终端输入：

$ sudo wget http://xrl.us/cpanm -O /usr/bin/cpanm

  $sudo chmod +x /usr/bin/cpanm

3.使用cpanm安装Laptop中perl所需模块

——DateTime::Locale，DateTime，DateTime::Format::MySQL，DBI，DBD::mysql，threads，threads::shared

在终端输入：

​       $sudo cpanm DateTime::Locale DateTime DateTime::Format::MySQL DBI DBD::mysql threads threads::shared

(五)安装mysql 5.6

由于PHP和Perl中的一些语句在mysql 5.7中无法执行，所以建议安装5.6。在终端输入：

$sudo apt-get install mysql-server-5.6

(六)安装jpnevulator

在Linux操作系统下由于监视和监听串行端口:http://www.cyberciti.biz/faq/howto-monitor-data-on-a-serial-port-in-linux





$sudo apt-get install jpnevulator





1. 修改执行权限

​      $sudo chmod 777 -R /var/ /tmp/ /opt/ /dev/ttyUSB*



获取USB的永久权限     $*sudo usermod -aG dialout [username]         #username为当前账户的用户名*

将Laotop文件夹放入opt文件夹中：每台Laptop的地址不同，数据库的地址也不相同，所以要根据每台laptop修改源地址比较麻烦。为了便于laotop中的代码在任何一台laptop上都可运行，程序中已将地址写为/opt/laotop/,所以必须将Laotop文件夹放入opt文件夹中。



tmp：日志



var







1. 创建Laptop上的local数据库——osensestar

$mysql –uroot –p



mysql>show databases;

mysql>create database osensestar; (注：不要将数据库名称写错，也不要用其他名称)

mysql>use osensestar;

mysql > source (Laotop/osense/cron/SERVER&LAPTOP_SQL中已有对应的sql脚本，如LAPTOP-A，选择对应的添加到此处，也可根据自己的需要添加和修改);



修改处：‘INSERT INT0 ‘currentstate’ VALUES’中的node-id和port-no



（七）具体修改的配置

​     /laptop/osense/cron2:

​     --ftp-getmotefile.sh 修改账户密码

​     --ftp-to-server.sh 修改账户密码

​     --neteye-config 按照实际情况修改



(9)安装NTP 用来同步时间

​     sudo apt-get install ntp ntpdate

​     server ntp stop

(八)运行laotop 和关闭

​     $ /opt/laptop/osense/cron2/

​     $ /opt/laptop/osense/cron2/