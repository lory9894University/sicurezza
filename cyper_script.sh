## cifratura simmetrica

openssl aes-512-cbc -a -in prova.txt -out provaenc
openssl aes-512-cbc -d -a -in provaenc -out prova2
more prova2

## cifratura assimmetrica
openssl genpkey -out fb1.key -algorithm RSA -pkeyopt rsa_keygen_bits:2048

openssl rsa -pubout -in fb1.key -out fb1.pub

openssl rsautl -in pass.txt -out pass.enc -pubin -inkey fb1.pub -encrypt #encrypt file pass.txt with pub key
openssl rsautl -in pass.enc -out pass.dec -inkey fb1.key -decrypt #decrypt with private key

##firma 
#sign
#openssl dgst -sha512 -sign <private-key> -out /tmp/sign.sha512 <file>

#verify
#openssl base64 -d -in <signature> -out <signature> #solo per vedere firma human readable
#openssl dgst -sha512 -verify <pub-key> -signature /tmp/sign.sha512 <file>

#example
openssl dgst -sha512 -sign fb1.key -out sig1 prova.txt
openssl base64 -in sig1 -out sig1a # solo per vedere la firma humand readable
openssl dgst -sha512 -verify fb1.pub -signature sig1 prova.txt

##creazione certificati
# genero coppia di chiavi
openssl genpkey -out CA.key -algorithm RSA -pkeyopt rsa_keygen_bits:2048 
openssl rsa -pubout -in CA.key -out CA.pub

#a questo punto la CA potrebbe già darti la chiave, ma per una questione di uniformità del software anche la CA diffonde la sua chiave all'interno di certificati.
#ma certifica questo certificato con la sua stessa chiave (dato che è lei stessa la CA) quindi il certificato è self-signed.
openssl req -key CA.key -new -x509 -days 365 -out ca-bundle.crt
#rispondi ad alcune domande per costruire un certificato "che rispetti regole"
#il certificato può essere 

#ed invece per certificare qualcun'altro?
openssl req -key fb1.key -new -out fb1.req #richiesta di firma di un certificato generato (da mandare alla CA)
openssl x509 -days 365 -CA ca-bundle.crt -CAkey CA.key -CAcreateserial -CAserial ca.srl -req -in fb1.req -out subject.crt #certificazione della richiesta (da parte della CA)
#si certifica con il certificato della CA. quindi -CA ca-bundle, ma non è detto che sia self-signed di solito è signed da una Certification Autority superiore. Serve anche la private key della CA che sta certificando. Invece CAcreateserial e CAserial li vedremo poi.
