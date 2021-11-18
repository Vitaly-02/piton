# piton
да, я написал питон на си. вопросы??

## установка
### сначала нужно установить библиотеку ncurses
Debian/Ubuntu Linux:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older:
```
sudo yum install ncurses-devel
```
Fedora Linux 22.x+:
```
sudo dnf install ncurses-devel
```
### когда библиотека уже установлена пишем:
```
git clone https://github.com/Vitaly-02/piton.git
cd piton
make
cd bin
./piton
```
## управление
движение на wasd, пауза на esc
