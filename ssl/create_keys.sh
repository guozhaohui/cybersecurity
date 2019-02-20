#!/bin/sh

mkdir ca server client

openssl genrsa -out ./ca/ca-key.pem 1024
openssl req -new -out ./ca/ca-req.csr -key ./ca/ca-key.pem
openssl x509 -req -in ./ca/ca-req.csr -out ./ca/ca-cert.pem -signkey ./ca/ca-key.pem -days 365
openssl genrsa -out ./server/server-key.pem 1024
openssl req -new -out ./server/server-req.csr -key ./server/server-key.pem
openssl x509 -req -in ./server/server-req.csr -out ./server/server-cert.pem -signkey ./server/server-key.pem -CA ./ca/ca-cert.pem -CAkey ./ca/ca-key.pem -CAcreateserial -days 365
openssl pkcs12 -export -clcerts -in ./server/server-cert.pem -inkey ./server/server-key.pem-out ./server/server.p12
openssl genrsa -out ./client/client-key.pem 1024
openssl req -new -out ./client/client-req.csr -key ./client/client-key.pem
openssl x509 -req -in ./client/client-req.csr -out ./client/client-cert.pem -signkey ./client/client-key.pem -CA ./ca/ca-cert.pem -CAkey ./ca/ca-key.pem -CAcreateserial -days 365
openssl pkcs12 -export -clcerts -in ./client/client-cert.pem -inkey ./client/client-key.pem -out ./client/client.p12
