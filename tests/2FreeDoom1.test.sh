#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

./ObHack 2FreeDoom1 || true

unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
6e0e2df31825da7e1d6854fa4b3a5eb6a8b8afd730435def2cf91d135a6b7fcc  MAP01.txt
b3cbbb07d5355ea83d385555c668c284e09ac05ef12d969bcf5bb5a5a9f06da3  MAP02.txt
1ab39ca56fcddc784d09d2a72c2e5f93a1c19f8df22a1667cd788d9cbe629733  MAP03.txt
3d2f0399cdf3b9488eb6263d6a124bab9079c6290c2a1eb20fd9d2f5204cd999  MAP04.txt
b8cbac2d294a0f790b9deccc1ec85bc1cf1082b83c8d664e3717540a63d68ba8  MAP05.txt
3b75048aeedd62cb09b31c51a6ff9f61a4e3444e41b73b8c631916c20869b9c6  MAP06.txt
4aab864a91e56cad9f6cb99b1f7bb810be57359bcd2a14237d9e17c6035c05f8  MAP07.txt
c2448370cccb9911746f27b6cdcb08eb5aa5fb9471cd4d933553acb036de2146  MAP08.txt
67a229fdf899d66388619e0ab69f34a8ed93f58025dae48c00090bc9e2d0adda  MAP09.txt
6cbf35963206aed1b632415b5113f4cbe80297bba996b307f306c2517925e92e  MAP10.txt
3d8c85b071f45e67e72672c41787e87303da79d23d4705539422fb56f545f7f8  MAP11.txt
baaba810ca8ae2cbc03765cb266cf82aa41bff1e242f3570fbb389053c6c43d1  MAP12.txt
db80b4c114063dd29b81e052a04e887ab5422cb3941b1ce430aa1613cc3699ed  MAP13.txt
1b4a2d3f1ff0965aa95f71a3082be4e5d6b804a941c10780962f6fbc71a91f89  MAP14.txt
ea0de54817682ba0167132ae15ffcaebadfb0110239933c463e9cc45b0d4731c  MAP15.txt
c318d5316c0adefcddb38ae1a712daf37af7a0e8aece2b1f38fc67ae0ef4bcd8  MAP16.txt
6e3b11fe0ad0aa6551c1c321f07d07e213ced9a6c62764205970b55d61bebd77  MAP17.txt
12f8cefb3d586ae2a7372f463b61d0275de79dccb4442d745286a0e75e91ab3d  MAP18.txt
270ddcdbc68c3f9f942c59969c4ef5eba8e44d6fc70f4b40f97d4b2304ba6d67  MAP19.txt
5efb5cd535b35464211fbf73c0a032255e5e31503d6a2512a566d5dd5fc1b402  MAP20.txt
c268655f407fb234e5cca47bbf63593e7d21c7cd8bb3f9ca2fb9636aa3e7110a  MAP21.txt
cfdd35c9d61cbdc50e5d44da8cca70db22fdbf39ba6b4a4a4876932feac711f5  MAP22.txt
9600270069d6574a473d1b1b6319b99b2148c419e81d8c0465d9cc7357cde09e  MAP23.txt
24f8a32b4f48e2a554ffd578082d631bf0d07e16b6f14345b42d79179b7ef692  MAP24.txt
7043a055e3fb47ba849a6a9ead737011eef5286ec7718d12b4aa120b11960a50  MAP25.txt
f7c6da2455d5c789f0e67f66f52f06ec80b1ee7010778fa7ffb48b8de05eda4d  MAP26.txt
b5ce26fc3b937687632c49dcae1f7e40f62c66cf3a0b0737dd1dfeefa5bdf45f  MAP27.txt
37cb36d8546d329820fd0f108ef48868e7e9740c2273bed500c8d7489a009c44  MAP28.txt
21bde423dff1797be63c39d7cafc0d0bf88a8a269b567aad3f56a2237294a6bf  MAP29.txt
061693c411f1d3a7e525ef518da19d05e60585ffbf3cebb82ee7169e8aa5ea80  MAP30.txt
0c5d91a60bb38c8de0e930b846b62b3b7536d7b1924194acfad8aebd4ccb28a0  MAP31.txt
86238f48c15357a7b048bd6ce889e29e207cfd7773a015fa87af9e21797243e1  MAP32.txt
EOF

echo Please ignore the glBSP errors above, we are running ObHack in a 
echo special test mode.

if ! cmp output.success output.test > /dev/null 2>&1 ; then
	echo Test failed
	mv writer.lua.save scripts/writer.lua
	exit 1
fi

echo Test success

# Clean up
mv writer.lua.save scripts/writer.lua
rm MAP*txt
rm output.test
rm output.success
rm LOGS.txt
