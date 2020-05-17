Now moving from CentOS to Ubuntu in mini pc, maybe keep sync with my WSL env.

There are lots of wrong guide on web, some make task more difficult, here record some tips used.

# install
安装的时候选择最小化安装
## "System program problem detected" 
just ignore it via
>sudo rm /var/crash/* 

# daily usage
## 定时关机
```
$ shutdown -h 00:59
Shutdown scheduled for Thu 2020-04-23 00:59:00 CST, use 'shutdown -c' to cancel.
$ 
```
## screen snapshot
使用OS内置功能截屏即可,shortcut key can be configured:

![tbd](images/u_screensnapshot.png)

## change the repo source
不用一些guide 说的手动修改, just changing it in GUI.

![tbd](images/u_repo.png)

## chinese input
* sudo apt install fcitx-bin
* https://pinyin.sogou.com/linux/?r=pinyin

安装好了之后，打开Language Support，将ibus改成fcitx，重启，点击右上角小键盘-设置，调整一下输入法顺序，将搜狗移到第一个。添加完成之后，可用Ctrl+shift进行中英文的切换 


# tools
## install deb package
e.g.
```
 sudo dpkg -i baidunetdisk_linux_3.0.1.2.deb 
```
## torrent tool Deluge
https://deluge.readthedocs.io/en/latest/intro/01-install.html

## paint tool
KolourPaint

## wps office suite
https://linux.wps.com/

装完后打开wps会发现提示缺少字体，这时候我们就需要去安装一下ubuntu系统没有的中文字体，理论上，你只需要下面这些字体就可以解决问题：

WPS Office 所需字体：wingding.ttf、webdings.ttf、symbol.ttf、WINGDNG3.TTF、WINGDNG2.TTF、MTExtra.ttf

但是，既然要使用wps，其他中文字体也是要用到的，还不如去Windows系统下C:\Windows\Fonts把所有用的到的字体全靠过来，也就百来兆大小

然后，在ubuntu中创建 Windows 字体存放路径

sudo mkdir /usr/share/fonts/win-fonts
拷贝字体到wiondow-fonts录下

sudo cp /home/fonts/*  /usr/share/fonts/win-fonts
更新字体缓存

sudo mkfontscale
sudo mkfontdir
sudo fc-cache



## foxit pdf reader
https://www.foxitsoftware.com/pdf-reader/

## tmux
multi-tab

# VS Code
## PlantUML support
* install the PlantUML extension
* sudo apt install default-jre
* sudo apt install graphviz
## C/C++ Suppport
## Python 3 support
## Golang support

## hotkey
   F11
   

