Generation of binary files (folders: first & third): test.sh
Dependencies: boost, openssl 
Build:  cmake . -DOPENSSL_INCLUDE_DIRS=<path to openssl include> -DOPENSSL_CRYPTO_LIBRARY=<path to lib crypto.a>; make
Run: file-duplicates <src dir> <compare to dir> [cmp | md5]
