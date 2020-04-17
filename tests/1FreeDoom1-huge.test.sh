#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt
cat > CONFIG.cfg << EOF
mode = sp
game = freedoom
mons = normal
seed = 1FreeDoom1
port = nolimit
length = full
size = huge
steep = some
puzzles = more
traps = normal
health = normal
ammo = normal
outdoors = more
iweapon = none
switches = keys
EOF

cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua
./ObHack 1FreeDoom1 || true
unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
f5213c3202aa8da7f6061c7680c99657d8f2b27749248704f32f754765fc4b4c  MAP01.txt
e3a8db8c5cd811f83eb5c50b81454b210c8386732ff3d01fd20f2e6939a5ca3f  MAP02.txt
7fcc0aaad3eedaf1c928ad4f59f7b8cad3847ccdd6cb30286f9d60fa7fd41de0  MAP03.txt
8ecbbc3ec6d7524efccaca5c6d05b910ccaab35cfe86089ea68b16669baeb18a  MAP04.txt
20fee12ea961303ce2579a40e650cbe7edefdcee98144f0d71a5321b17ec1c00  MAP05.txt
863ce8f92ac97439d2ba6d20385a0d59bacad820d9df7d82d4cd12fdba42caf6  MAP06.txt
fe55e0bb7d46da09bf82fb8b0dbc7661a43bf9c0e222f45f516dc1186380a649  MAP07.txt
20e1081c68f71fcd8779a8252b3141a9921043f3bceb4341b2963283fd27206a  MAP08.txt
475b7f2f19b977fa6b0a5d4d67027424932b67be64566f61f2a0d6de80584bb3  MAP09.txt
5b30914019ba6711fac1243ec74adcc860b34d3d1c4a41b096d52b62a232c402  MAP10.txt
c9d1028d6966def68ce2a44e2269f4ea3e5d9a74a4dc01b71ebc0a423be80538  MAP11.txt
45ecb3c3f244e414235786ea4eff66d70109c8d6b7f00a221ccf1f453301fd31  MAP12.txt
ea8d305e5f5f596779ad592ac4a00e4b945267bc22648e9e78f183880815818f  MAP13.txt
aeac92eb023a477b32564794fbe8187417d11c6e2cf4ce0dd063378315fb1f52  MAP14.txt
f81617f1c221c9448e27f5ebd960bc0d0666ef3aa8872200d49124b4e6abafbb  MAP15.txt
0ee99bbe2dc981b8e05338899f80d3380d2245827153541ba36e548d53cbd740  MAP16.txt
1350b6adc01b9f3228f8ae274d2845856be0156519297d09473a6c1d39739b2e  MAP17.txt
eba08f86f2b8997c59339df70086a69f20d00264d4ebdf304d84b860c9fe3563  MAP18.txt
db10bbf18f747b807b67f38c1d5e0e29e2e82a917a710d064740f2a5b5b8f805  MAP19.txt
d51e3a6ff00bf3a00e2bf46405c0e19663fe971bcdbfb78abb8c6e5f4305689c  MAP20.txt
cf1fe0f424acffcc85f94a1cdc8bf0b980b660083fabf810abbdfaa60e2827f3  MAP21.txt
016bd7760bb36200ca16c18a3b8aa35d88f0156cc2fb9979de7b6ff6d384932e  MAP22.txt
0bd5375d397968f23fe44c0d33da43662576ff479764475adb3f17ae1643450c  MAP23.txt
26c6668c2c1ce1ee0434dad72c4f870c134e8fa97990d640b51ecb839d9b3bee  MAP24.txt
9e933eeea2fc512baa2dbf68b78eea7cb23c6fcbe6b63674094e3567f23fe7e1  MAP25.txt
9fa4e682d34e6c47d20d441cd34e04b5c500bc0d8d6b6bb7bff4029dde23506f  MAP26.txt
b72bbf066b64199871fc3300e93e0b76ca0820a756b3d9a042ca6c70324e7125  MAP27.txt
410018057cdeadf7bf20b69f40c7713026fba599322d082567ee72c8b628402b  MAP28.txt
67ab70147dc89ecc96b2080011b8e4aa08063ba94bb52d1eda083250b9fae793  MAP29.txt
b00d851d74040bcfadc545a396577970871fa61f5fa2b32207a8cfd7e49058f9  MAP30.txt
2f7151af445ecbdea1c1240002aad94231226584cfc92391a91192daecaa05df  MAP31.txt
15bf31be693a6df1db88f1d2d393a44b903d18d65755381c90442a30a6085849  MAP32.txt
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
rm CONFIG.cfg
