#!/bin/sh

# create folders to save keys.
mkdir ca server client

# ----- create keys for CA -------
# create private key file for CA
openssl genrsa -out ./ca/ca-key.pem 1024
# create X.509 Certificte Signing Request (CSR) file for CA
openssl req -new -out ./ca/ca-req.csr -key ./ca/ca-key.pem
# create X.509 Certificate Data for CA
openssl x509 -req -in ./ca/ca-req.csr -out ./ca/ca-cert.pem -signkey ./ca/ca-key.pem -days 365

# ----- create keys for server -------
# create private key file for server
openssl genrsa -out ./server/server-key.pem 1024
# create X.509 Certificte Signing Request (CSR) file for server
openssl req -new -out ./server/server-req.csr -key ./server/server-key.pem
# create X.509 Certificate Data for server
openssl x509 -req -in ./server/server-req.csr -out ./server/server-cert.pem -signkey ./server/server-key.pem -CA ./ca/ca-cert.pem -CAkey ./ca/ca-key.pem -CAcreateserial -days 365
# convert to .p12 (PKCS#12 Data) for using on browser
openssl pkcs12 -export -clcerts -in ./server/server-cert.pem -inkey ./server/server-key.pem-out ./server/server.p12

# ----- create keys for client -------
# create private key file for client
openssl genrsa -out ./client/client-key.pem 1024
# create X.509 Certificte Signing Request (CSR) file for client
openssl req -new -out ./client/client-req.csr -key ./client/client-key.pem
# create X.509 Certificate Data for client
openssl x509 -req -in ./client/client-req.csr -out ./client/client-cert.pem -signkey ./client/client-key.pem -CA ./ca/ca-cert.pem -CAkey ./ca/ca-key.pem -CAcreateserial -days 365
# convert to .p12 (PKCS#12 Data) for using on browser
openssl pkcs12 -export -clcerts -in ./client/client-cert.pem -inkey ./client/client-key.pem -out ./client/client.p12
