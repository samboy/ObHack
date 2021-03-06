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
56da5acbe5f1b919a4705de583c01493d17223dd96e5a2c72a463d71ddb96ff7  MAP01.txt
dab4b82a9d3967ac9c863d29661fbb1ba1f9f726385edf727707aed08e19576f  MAP02.txt
de19b60132a47be8023dd9323043f5e7d69b46fa7f88b579387f05ba99aec8fe  MAP03.txt
b1ff5d85797a4ac10e65cbd2c40a142ad257d4c3b4b1094b037b3b1cd0329ad7  MAP04.txt
b3ca88e86ed3c0a5dea825ca10fd7f9da9a8b14e157751d3ed18261dcc3a82bc  MAP05.txt
2274eb9f9527291611f25f2cbb094eb246d558481062fbdc9e19d927aa5bc12c  MAP06.txt
f6c0d46d8650f62ea77ffe5b3d01cf24aa7df778c09ac26b7cb0915c1afe121d  MAP07.txt
090776b734ce7650d5a101e2bb0c16e66ce019a9df78fec073e8841d9ceea343  MAP08.txt
f87c166d12d90dc336fd6f667ea854881820b7e53ee56f2b88210d83fdd5f035  MAP09.txt
3d434ce4a35c5aac1d5b9281cd39c03005a4033259fdab1fd8a64f3eb3285871  MAP10.txt
4817b7243e231672fee28ff87e9da225fdf3f22bc48d196204f887bb26c74f3b  MAP11.txt
a12cf5eb8ada1473a91b8c1f0c995ee6def2727772d09791cb4d2fc15e74575b  MAP12.txt
c34e4518ac376189f8bdf8f9f74a0bd19936f75e0e27f0e4369a8b9c6a08ab10  MAP13.txt
d8fee922a4bba6fcd331ac66dffa1eeea82708bdbdb2f632c015c399e3cd9440  MAP14.txt
ec938775a16acc389f40df18b5b3264a36e8b2b4e81d9918242e081769cf6ca1  MAP15.txt
e2efaffff9ce489d259c53ad7038ea9416f8247c230f1884e4563370e6b7b687  MAP16.txt
05e44b7a8e81c1203e1ebe408909888acc39460cf2fb1e3e83088c7667e3896a  MAP17.txt
320110a4d2c00858a37314e9d132c699d88dc5f474186cf93a476fa9c2aba43b  MAP18.txt
0f8754c3fd065d9b63488d9f5e06cc79180d8ca689a66dae2ff55ea821ed0e51  MAP19.txt
7ec9034827a25b794e01f9165eae010bad42db44c90bca302a10f96863bc587d  MAP20.txt
8bfc9e21b0ecb631974cf67dc52a03762b929bccde1da7510fbca36adf749bd5  MAP21.txt
406f3b44dcd65375ac263bda6c0b44179897ea2ce9d36b4a1eea9c9b66a4e74a  MAP22.txt
9fcdf647b98e315a17d7d47805688eedb96a8fa1f1eb215e59052b828954b43e  MAP23.txt
c98a9bca809a33ad686efd51b8b72f049ea171bf33227593e9f9b3c25ce373f2  MAP24.txt
fe8580fda9716bd0b19b5858648fa637327b3559957df707ec0b90c1a7862c97  MAP25.txt
73eaa2b1387abdfa3758cbbb2dea69abefc5b851acc919f23151fb33716142c2  MAP26.txt
c0fc5082b2d4a038d7493f09f754d0708cb13b77470ff64969ed9a0c5c72862e  MAP27.txt
5ec24293a5bd29c0a8416da9feeab48d6378cf881653c9f0d32d3a5712db03dd  MAP28.txt
321b465dae5fa67d695f314639c82be2d141759e8e0b43a722a8c302ee798237  MAP29.txt
1b969cdefee1e8ab8ebd088787d0dee217d7fc75807101ad97ba8cc916c57ffb  MAP30.txt
fab0e909637b48a31257bfddb668317c21b646f86551d7a56a1310a8d7a89d9d  MAP31.txt
b77754bde1a85056d841982572f8435a9a90aa181c725642f5ddd52e7fc3a50b  MAP32.txt
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
