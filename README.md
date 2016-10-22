# php_extention_encode
一个简单的php 扩展实现的字符加密、解密<br>
下载源码，安装此扩展
进入目录muyi
/usr/local/php-5.5.38/bin/phpize 
./configure --with-php-config=/usr/local/php-5.5.38/bin/php-config 
make 
make install

测试文件test.php
<?php
$str = encodeStr("wangxianjiao");
echo $str;
echo "\n************\n";
$str1 = decodeStr($str);
echo $str1;
echo "\n";


/usr/local/php-5.5.38/bin/php test.php 

输出：
dlxnZXRgYGljZ11m
************
wangxianjiao