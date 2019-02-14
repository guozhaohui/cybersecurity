一、环境

OS：win10 

IDE：Visual Studio 2010

类库支持：Win32OpenSSL_Light-1_0_1f，vcredist_x86，ActivePerl-5.16.3.1603-MSWin32-x86-296746.exe


二、OpenSSL工具库的安装和编译

直接安装：

（1）安装VC++2008环境支持（vcredist_x86），使系统能够运行VC++2008编译形成的Win32OpenSSL_Light-1_0_1f；

（2）安装Win32OpenSSL_Light-1_0_1f；

（3）配置系统环境变量，把Win32OpenSSL和Visual Studio 2010的安装目录下的bin目录添加到系统路径里面，重启系统；

（4）安装ActivePerl-5.16.3.1603-MSWin32-x86-296746.exe。

openssl源代码编译安装：

（1）解压缩openssl到C盘；

（2）配置WIN32环境，打开CMD命令行，进入C:\openssl目录，执行命令perl Configure VC-WIN32；

（3）进入VC\BIN目录，配置VC环境变量，进入VS安装路径的VC/bin目录下，运行：VCVARS32.BAT，设置环境变量；

（4）返回OpenSSL目录，创建makefile文件，执行ms\do_ms；

（5）在Openssl目录下：

编译动态库：nmake -f ms\ntdll.mak

编译静态库：nmake -f ms\nt.mak

测试动态库：nmake -f ms\ntdll.mak test

测试静态库：nmake -f ms\nt.mak test

安装动态库：nmake -f ms\ntdll.mak install

安装静态库：nmake -f ms\nt.mak install

清除上次动态库的编译，以便重新编译：nmake -f ms\ntdll.mak clean

清除上次静态库的编译，以便重新编译：nmake -f ms\nt.mak clean

（6）最终编译动态库完成后，输出都在out32dll目录下：包括可执行文件、两个dll 和两个lib文件: libeay32.dll, libeay32.lib, ssleay32.dll, ssleay32.lib，如果需要使用openssl命令，还需要在系统环境变量path中增加c:\openssl\out32dll路径，因为openssl.exe就在该目录下，声明后可以直接在命令行中使用openssl命令。


三、利用OpenSSL工具生成数字证书和密钥

（1）当前目录下创建ca, server, client目录；

（2）创建ca的私钥和证书 (ca的创建也可以用命令CA.pl –newca, 在当前目录下demoCA/private/cakey.pem是CA根证书的私钥；demoCA/cacert.pem是CA的根证书文件，需要导入到服务器和浏览器里面)；

--生成ca的私有密钥文件，比如叫ca-key.pem：

    openssl genrsa -out ca/ca-key.pem 1024

--创建ca的证书请求文件，比如叫ca-req.csr：

    openssl req -new -out ca/ca-req.csr -key ca/ca-key.pem

--创建自签名证书，比如叫ca-cert.pem：

    opensslx509 -req -in ca/ca-req.csr -out ca/ca-cert.pem -signkey ca/ca-key.pem -days365

（3）创建server的私钥和证书；

--生成server的私有密钥文件，比如叫server-key .pem：

    openssl genrsa -out server/server-key.pem 1024

--创建server的证书请求文件，比如叫server-req.csr：

    opensslreq -new -out server/server-req.csr -key server/server-key.pem

--创建ca签名的server证书，比如叫server-cert.pem：

   openssl x509 -req -in server/server-req.csr -outserver/server-cert.pem -signkey server/server-key.pem -CA ca/ca-cert.pem -CAkeyca/ca-key.pem -CAcreateserial -days 365

--将证书导出成浏览器支持的.p12格式：

    opensslpkcs12 -export -clcerts -in server/server-cert.pem -inkey server/server-key.pem-out server/server.p12

（4）创建client的私钥和证书；

--生成client的私有密钥文件，比如叫client-key .pem：

    openssl genrsa -out client/client-key.pem 1024

--创建client的证书请求文件，比如叫client-req.csr：

    openssl req -new -out client/client-req.csr -key client/client-key.pem

--创建ca签名的client证书，比如叫client-cert.pem：

  opensslx509 -req -in client/client-req.csr -out client/client-cert.pem -signkey client/client-key.pem-CA ca/ca-cert.pem -CAkey ca/ca-key.pem -CAcreateserial -days 365

--将证书导出成浏览器支持的.p12格式：

    opensslpkcs12 -export -clcerts -in client/client-cert.pem -inkey client/client-key.pem-out client/client.p12
--------------------- 
作者：Dylan-97 
来源：CSDN 
原文：https://blog.csdn.net/qq_40394039/article/details/80570207 
版权声明：本文为博主原创文章，转载请附上博文链接！