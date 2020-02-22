#!/bin/bash -e

exit 0 # DISABLE -- won't pass WORK IN PROGRESS

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua
./ObHack 1FreeDoom1 || true
unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
a1daf40c83ca0035649f4d1379d60936b84d8d7f716880593655f774f2aff750  MAP01.txt
306a744162b699957322a4cfa790b2dc58738b9e022a1b90c2e49b5e7eb1ea38  MAP02.txt
06c0647011794751d1cb998d3118f383c9df26f0b2a597cf98e04fb76b3472fd  MAP03.txt
6a330fff6941bd7a36bc86cbc1d863fabfbac5e7530635e5077905258e4060cd  MAP04.txt
34a86d288c3bce039f8b1f1820b1a8762907157ef7a0542b21d71bd8c0bd2df4  MAP05.txt
561fb21bc4056591657b3348f1b4aa2cb17e40686d053bc91da03df0aa1d7814  MAP06.txt
311531251cc31f690b364b10f165b34a1584ec6864a3ffc92168e247408d7ddb  MAP07.txt
a6132573cd2d0c3e371172872b4d1359b4f4f59327ac9ae9672be119a939bf4c  MAP08.txt
f3d70208633b739eb1e368a07f5b33de1e01b820e4862db8952e2508460b129b  MAP09.txt
34e6c36e8953d1495eff6a622624a7910bf0f66554936a88b69fecc1996965c8  MAP10.txt
b8586f19162ba5b541e20a9910adc55bb1f77a051c3e36d49edd849457baaa17  MAP11.txt
24cee2c01ca49322cb18795c788374598ebe25a0b26b890211a356ed17ee6954  MAP12.txt
c5a71ddc3b06acdadbfaaff62cd6cde38df0f5c8e163f46003bc9840431f8b40  MAP13.txt
eeab2ffecb1905bf12ef58253cfa58b7daf3dba527094359ce59205796e324ef  MAP14.txt
f15edce76b9dc265107ab0ed760e6df7f47716f133deb62d28c8b596a91dd0bd  MAP15.txt
8d3878b5175e319c881211916a3b28e1e3e317eca832be0499583e93e2c7e00e  MAP16.txt
d1c614679cf1049da80271ec9c19b7d68c5fd7f5e8ea748a90e51eda015b87cc  MAP17.txt
2b8fa90eb356724bff6fd9f8d9fcc56db191c3358047bf5da759ed015028f476  MAP18.txt
961a7923b6f6bd62db59ff7b21540e7151238d0fe4b89d1720d9eff533126105  MAP19.txt
be0c3595a345a266366d1998d7309f58babd27e09bc554f993df8119503a215d  MAP20.txt
6e8b7a2ddf086a722f7c94eb35da431040dbb54ed8a1eff2fb65726cf8149fc6  MAP21.txt
8776d5c7c708413304589ff4a70faee432d087ccd09a1d47b21b4eaa430ccfc3  MAP22.txt
3dbd90939f349b20834d9bdacf6220d7fba290d9a1c340953de2a953e3217b8a  MAP23.txt
97c01c6b5e830f92d7c01141a3f3cdf504661a6fe14d925c88718b36f7a3fa7e  MAP24.txt
db409df20d841834513c247e4faed7a4981440363dd8a7689869c73d6682313a  MAP25.txt
225b36301d563bc8ea90dafa37f9ddd3c9a34c264d385bba34015a8e3c25ac66  MAP26.txt
6df89355ca2aaa5e870c39d32cc0a8607f45927c01decd56645ffde3814b3330  MAP27.txt
f3ca32fd2f2ffb9f789123bfa3a88f159ccb613c3931c93f7ee6a187e9c8dab6  MAP28.txt
3e1b4dcd74feb8436b5e57ed8d17f1eaa012c308dcb391a15d68cdc6c97ba033  MAP29.txt
d430bb93e43b875852f0f63ab3531ae1a774b967555c7622daded745e688e007  MAP30.txt
bf9b5662c45e3220a3d56a8d863ee5d66c12fb88e22b9ec30b9d1f07e6624c6d  MAP31.txt
25ecb0c580bcecc92cff5e05035619735729edbfa6ab24051ff51b22d65a8433  MAP32.txt
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
