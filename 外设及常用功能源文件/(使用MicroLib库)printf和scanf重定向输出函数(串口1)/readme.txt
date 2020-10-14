PA9——TX，PA10——RX       复用为USART1

注意：因为我们是软件方面重定向的scanf数据流
           所以我们不需要开启硬件的接收中断，如果
           开启将会影响到scanf的数据流重定向。

记得勾选Target——>Usb MicroLIB缺省C库的备选库

Usb MicroLIB缺省C库的备选库作用在下面的网址：
https://blog.csdn.net/u014717398/article/details/55251859