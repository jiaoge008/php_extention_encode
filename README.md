# php_extention_encode
一个简单的php 扩展实现的字符加密、解密<br>
下载源码，安装此扩展<br>
进入目录muyi<br>
/usr/local/php-5.5.38/bin/phpize <br>
./configure --with-php-config=/usr/local/php-5.5.38/bin/php-config <br>
make <br>
make install<br>
<br>
测试文件test.php<br>
<?php<br>
$str = encodeStr("wangxianjiao");<br>
echo $str;<br>
echo "\n************\n";<br>
$str1 = decodeStr($str);<br>
echo $str1;<br>
echo "\n";<br>
<br>
<br>
/usr/local/php-5.5.38/bin/php test.php <br>
<br>
输出：<br>
dmpsZmVxZ2pnZWNsbm1ebA<br>
************<br>
woshizhongguoren<br>