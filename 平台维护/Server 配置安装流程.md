# Server 配置安装流程

(一)安装Ubuntu系统

由于数据库不兼容，建议安装Ubuntu15.10



(二)配置镜像源



(三)安装svn，下载Laptop代码

安装svn

$sudo apt-get install subversion



下载Server 运行所需代码

$sudo svn checkout --username jiuxiaxixi [http://code.taobao.org/svn/neteye](http://code.taobao.org/svn/laotop)server



放在 /var/www/html/ 文件夹下



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



要求： 配置远程可以访问



（6）安装PHP Apache webserver

​     PHP 版本为5.6 高版本无法使用



​     $sudo apt-get install apache2 php5 php5-mysql sudo apt-get install apache2 php5 php5-mysql



（7）安装FTP服务 

​     

​     sudo apt-get install vsftpd

​     配置FTP：

​          配置 可以用户密码登录 并且在 /var/www/ 和 /var/log/ 下有读写权限 

1. 修改执行权限



$sudo chmod 777 –R /var/ /tmp/



1. 创建Server上的local数据库——osenses

   

$mysql –uroot –p



mysql>show databases;



mysql>create database osense; (注：不要将数据库名称写错，也不要用其他名称)



mysql>use osenser;



mysql > source SERVER.sql

注：具体配置按照 

(9)安装NTP 用来同步时间

​     sudo apt-get install ntp ntpdate

​     配置 /etc/ntp.conf 使得Laptop 可以同步Server 的时间



(9)运行server



​     运行 /neteye/cron 下的所有pl 文件