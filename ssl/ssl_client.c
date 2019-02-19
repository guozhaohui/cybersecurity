//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#if defined(_WIN32) || defined(__CYGWIN__)
// Name clashes between windows.h and openssl
#undef X509_NAME
#undef X509_CERT_PAIR
#undef X509_EXTENSIONS
#undef OCSP_REQUEST
#undef OCSP_RESPONSE
#endif

#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/rand.h" 
#include "openssl/bio.h"
 
/*所有需要的参数信息都在此处以#define的形式提供*/
 
#define CERTF "C:\\...\\...\\client\\client-cert.pem" /*客户端的证书(需经CA签名)*/
#define KEYF "C:\\...\\...\\client\\client-key.pem" /*客户端的私钥(建议加密存储)*/
#define CACERT "C:\\...\\...\\ca\\ca-cert.pem" /*CA 的证书*/
#define PORT 4433 /*服务端的端口*/
#define SERVER_ADDR "X.X.X.X"/*服务段的IP地址*/
 
#define CHK_NULL(x) if ((x)==NULL) exit (-1)
 
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(-2); }
 
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(-3); }
 
int main()
{
	int err;
	int sd;
	struct sockaddr_in sa;
	SSL_CTX* ctx;
	SSL* ssl;
	X509* server_cert;
 
	char* str;
	char buf[4096];
	const SSL_METHOD *meth;
	int seed_int[100]; /*存放随机序列*/
 
	OpenSSL_add_ssl_algorithms();/*初始化*/
	SSL_load_error_strings();/*为打印调试信息作准备*/
	meth = TLSv1_client_method();/*采用什么协议(SSLv2/SSLv3/TLSv1)在此指定*/
	ctx = SSL_CTX_new(meth);
	CHK_NULL(ctx);
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL); /*验证与否*/
	SSL_CTX_load_verify_locations(ctx, CACERT, NULL); /*若验证,则放置CA证书*/
 
	if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		exit(-2);
	}
 
	if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		exit(-3);
	}
 
	if (!SSL_CTX_check_private_key(ctx))
	{
		printf("Private key does not match the certificate public key\n");
		exit(-4);
	}
 
	/*构建随机数生成机制,WIN32平台必需*/
 
	srand((unsigned)time(NULL));
 
	for (int i = 0; i < 100; i++)
		seed_int[i] = rand();
 
	RAND_seed(seed_int, sizeof(seed_int));
 
 
	/*以下是正常的TCP socket建立过程*/
	printf("Begin tcp socket...\n");
	sd = socket(AF_INET, SOCK_STREAM, 0);
	CHK_ERR(sd, "socket");
	memset(&sa, '\0', sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(SERVER_ADDR);/* Server IP */
	sa.sin_port = htons(PORT);/* Server Port number */
	err = connect(sd, (struct sockaddr*)&sa, sizeof(sa));
	CHK_ERR(err, "connect");
 
	/* TCP 链接已建立.开始 SSL 握手过程*/
	printf("Begin SSL negotiation \n");
 
	ssl = SSL_new(ctx);
	CHK_NULL(ssl);
 
	SSL_set_fd(ssl, sd);
	err = SSL_connect(ssl);
	CHK_SSL(err);
 
	/*打印所有加密算法的信息(可选)*/
	printf("SSL connection using %s\n", SSL_get_cipher(ssl));
 
	/*得到服务端的证书并打印些信息(可选) */
	server_cert = SSL_get_peer_certificate(ssl);
	CHK_NULL(server_cert);
	printf("Server certificate:\n");
 
	str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
	CHK_NULL(str);
	printf("\t subject: %s\n", str);
	//free (str);
 
	str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
	CHK_NULL(str);
	printf("\t issuer: %s\n", str);
	//free (str);
 
	X509_free(server_cert);/*如不再需要,需将证书释放 */
 
	/*数据交换开始,用SSL_write,SSL_read代替write,read */
	printf("Begin SSL data exchange\n");
	do {
		printf("client:");
		gets(buf);
		err = SSL_write(ssl, buf, strlen(buf));
 
		CHK_SSL(err);
		{
			char* presult = NULL;
			unsigned long nresult = 0;
			err = SSL_read(ssl, buf, 4095);
 
			buf[err] = '\0';
			printf("server:'%s'\n", buf);
			nresult = atoi(buf);
 
			if ((err == 4095) && (nresult > 0))
			{
				presult = (char*)malloc(nresult + 1);
				err = SSL_read(ssl, presult, nresult);
				if (err == nresult)
				{
					presult[nresult] = '\0';
				}
				//CHK_SSL(err);
				printf("server:'%s'\n", presult);
				free(presult);
			}
			// SSL_write(ssl, "1", 1);
		}
	} while (strcmp(buf, "bye"));
 
	SSL_shutdown(ssl);
	/* send SSL/TLS close_notify */
 
	/*收尾工作 */
	shutdown(sd, 2);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	system("pause");
	return 0;
}
