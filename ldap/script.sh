#!/bin/bash -e
docker compose up -d ;
sleep 5 ;
ldapadd -H ldap://localhost -D "cn=admin,dc=lorenzodentis,dc=org" -w admin -f entry_ldif