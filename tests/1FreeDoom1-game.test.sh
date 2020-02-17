#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

# Make sure that, for all possible "monsters" values, the architecture of
# all 32 "1FreeDoom1" maps does not change, and the only thing that changes
# is the placement of Doom "Things" (Monsters, health, ammo, weapons, etc.)

for GAME in freedoom doom2 ; do

rm -f MAP*txt

cat > CONFIG.cfg << EOF
game = $GAME
mons = normal
seed = 1FreeDoom1
port = nolimit
mode = sp
length = full
size = small
steep = some
puzzles = more
traps = normal
health = normal
ammo = normal
outdoors = more
iweapon = none
switches = keys
EOF

./ObHack 1FreeDoom1 || true
unix2dos MAP*txt

# Remove things; we are testing if changing monsters affects the map itself
for a in MAP*txt ; do
	cat $a | awk '{if($0 ~ /^THINGS/){a++}if(a % 2 == 0){print}}' > foo
	mv foo $a
done

sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
7d8a397d3c48881d251fb385e92249105cbdc466b773411897c371fb5f9c62fe  MAP01.txt
3e8beb5a396405e7e3f5af9c8b073ffaf075531b90cf5b1c3ea1436616462867  MAP02.txt
b34643716a3dad99b7df232283b75bef2e3d48154ae44cf1555a0e0acdfa736f  MAP03.txt
9700ecfee1d42ab95ab52b5ee96eaf862b0aca2f73594e75b99b7fed35cd2968  MAP04.txt
a2c1784e17ef9829d69f97eee700321288b5db74eade6f362290e441454a95f1  MAP05.txt
8bfd5e0d3f9943974963468360f19e2b6a192846ffb27835cd0e62db6f89c638  MAP06.txt
3f3dec1b1030cc7a47eb545e12d3edf85b61616d97e7e069b8c45f2d30863327  MAP07.txt
f0ac493bddf0a4e32de022b014f833a3a1ec5196fb1f60c3914086843e97161a  MAP08.txt
5aa9eb13ac60c77a1673d1c61b169ba417976de5bec57332eb7315c7599bd832  MAP09.txt
dc7adfc28425ae613c084ca5e04da8079fe9f4a7bd8bc4c2b238203309cda36a  MAP10.txt
b44e0656631bfbbb05ab5e19864367673b8181294948114fc8ef1de88aac808b  MAP11.txt
2f998b5dd6330d628868ac65e4d6cccb1f064d2f3838b52ae94c53116c693ecd  MAP12.txt
a6e4e869c13634ad7e730578aade894135fa26d69af80157d0c8a143c68fb93f  MAP13.txt
86092c0a5de5f28e5a01f8e5c1f8e58a1d719a9d93058ec9dc4b05c87a123286  MAP14.txt
8427198e885f321a8ee57ae649b8def7d25cb979e3c8c84291bb4ca4cd94bd04  MAP15.txt
945039f37608239604973f6201b04159c2bfd7d11e0a8e03c3cd6e9d21ef40ce  MAP16.txt
2ad48f12bb294826ae643285b0949fbc25f769ee270b17c60edf0baf9b3629ca  MAP17.txt
dd254938bcbd97c5cbd9f87c03522e84832f9e84dd2a8b260a0b39bf5f879351  MAP18.txt
26b0243cf1b80044b074b6500e3d331cca2453f4338efc211f85bd9355b2b55e  MAP19.txt
5205b1a2209a282efc4505dc6311bec299bb6082767bb29d108a84e5cb77e0d1  MAP20.txt
5d67b6c5e51b01e5e23239cdc7e8bf5e06d362612da8a5c939d5a95d5a12a085  MAP21.txt
f6079dd0262a6a29d8e7b61a1fcd025b10e6c95213f025a1cd2336d4404d8622  MAP22.txt
eb4d4876d161f1920a5dec8bd9f04ca99906856985d2b6ca24a29fb752709d46  MAP23.txt
e3a7ec4c6c49b1573019a333656e47e2e2c8b7f5122ea59f15061d6109437fb6  MAP24.txt
c8f99b7437e7f408456ed655e74089b3b9819e66c9d6f0e1345fa27bc373b7f2  MAP25.txt
7df4a6232e9640525ae7b92538a54baa57e08961c24f0066c9b24ebdd34a7eea  MAP26.txt
5fda33046f6ddb9bae3e7770b2b911242e5960a8b293baf6f57cb0d79d3d7347  MAP27.txt
c5e407418772ae2424b19b99f2e8fb06d2c724b8024c1186305b5382675d54cf  MAP28.txt
e299cdf82834e83b68516f2ceee5d91ffc3e9de75610a774426302139ba87a4c  MAP29.txt
42772352347327360a7da02b9bf3c8f7ea1cb31f54b286800c3f1cc0061e56fd  MAP30.txt
9493745fa8b45062a20caef8b6f06da78faca31847d411b391ba9c9ccf1dc57f  MAP31.txt
0c792f4ffed21071f0beb854b354acba821fdb40e04727cf7403e3b7f53c5576  MAP32.txt
EOF

echo Please ignore the glBSP errors above, we are running ObHack in a 
echo special test mode.

if ! cmp output.success output.test > /dev/null 2>&1 ; then
	echo Test failed
	mv writer.lua.save scripts/writer.lua
	exit 1
fi

echo Test for $GAME game success
OUT="$OUT $GAME"

done # for GAME

echo Tests for all of $OUT monsters success

# Clean up
mv writer.lua.save scripts/writer.lua
rm MAP*txt
rm CONFIG.cfg
rm output.test
rm output.success
rm LOGS.txt
