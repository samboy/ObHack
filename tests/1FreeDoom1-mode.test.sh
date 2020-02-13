#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

# Make sure that, for all possible "monsters" values, the architecture of
# all 32 "1FreeDoom1" maps does not change, and the only thing that changes
# is the placement of Doom "Things" (Monsters, health, ammo, weapons, etc.)

for MODE in sp spdm2 ; do

rm -f MAP*txt

cat > CONFIG.cfg << EOF
mode = $MODE
game = freedoom
mons = normal
seed = 1FreeDoom1
port = nolimit
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
	cat $a | awk '{if($0 ~ /^THINGS/){a++;
			  if($0 ~ /START/){print}}
			if(a % 2 == 0 || $NF < 16){print}}' > foo
	mv foo $a
done

sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
426e6beb16bdd762e85b9ab4afb751977ced1fc3a5fde3e4170df6c85c3388ff  MAP01.txt
3d5b6d1238005f38a78ed8014ff19afc9790e991987ebdada5b0db72ec9a4c83  MAP02.txt
271b6bd78830b272d85998a56ab3944f5b6356496729c1759e5e6ab617fbdeb7  MAP03.txt
d90554647c38410464e4a7c85b03f638965a73a98a1dadc1a94dbaf9b04372ed  MAP04.txt
ba0dc8d6586c4e2d830053e58dd38a3a36607759d163ec55cb066536fc65980b  MAP05.txt
b5038822194623c5d977964c261d1504100c6fcfca85cf9ae6b797d3488ce35e  MAP06.txt
2f59b08b714260831404dbac912ecf1cf3a3a6a862ac11bd3835bb31a237571a  MAP07.txt
2c7379777c30857809ec52dc00654b27d2079fc26cc19346a38560f66f61d9cf  MAP08.txt
c280ad6988f41bfb2476ccc9749c12903bb524bcafd119f5b52ad0b350fc4ed6  MAP09.txt
4c9498bfb5f353394a52926c5fa80b2ade13f0cd0dc668e0bf3c920befced29e  MAP10.txt
98c9fe685574e037d1bbb8f1d2eea802e4222aa5aa8fb020008f0bec4c90aaa8  MAP11.txt
d709a8525f2c968def4955bf75164a2ececd84397dcb546cc30005ba76e515ac  MAP12.txt
ae436ce1f8f7ed8137ffcb1a3a24dd032752af47ed6cc3db7b387e4651272af6  MAP13.txt
9beb84ced413e4f538bd081faeafd02daecf3197c7ee37d511bc144d4a82d6fe  MAP14.txt
f05bd1fe38e79250fa5c18db935804665c3359c3ed9d7b52731494040cf4fc05  MAP15.txt
86f4165b29e6530ac55bd75a36f2720ae1c79d4f61547bd78c3550bd3ea757d6  MAP16.txt
e172246cb974b5fe9fb4355d54450289c14f670bfe2e24ce91a90ace185e5c1f  MAP17.txt
f68dc962c72f500f79c70f710435b8d157ea1d78b082bd84b329e05a3e74019e  MAP18.txt
d9518d79f07a2e3b9b885e4a321f18d0beddf8f28bfff565298e5277edb825e5  MAP19.txt
4edef90eaecc3aba9abbff48598210933b70445939c34d0346d8b89fa4ea1510  MAP20.txt
85bb93a61b4b91d2388ac4cd167db7a206a8fa6ad5cadc3df55a178fa7aba023  MAP21.txt
ee44c09351abb6881e4e064d0657b8fc3ef79b74e33aae84b12bcf4c439ad35b  MAP22.txt
bcaa4ccac63816166a969eb419e4ff7a0eaf7a865261de06ae5b0b694f7e8c35  MAP23.txt
b3fd4c68ad402bc7192f9f002065178e686356dd5897e073f6771ca1701709ce  MAP24.txt
8f3a1865739042986277641735670b9def6bdf039bcd79173bc64f36eb0e4f75  MAP25.txt
6f292cb794ee84f6832a24533a659d0be4d18f81ac127897d2bff4b63f90d414  MAP26.txt
a93a7b01c79170dc9f9c471f4179ce99b4241301e9c9f9bc377005d59add68fb  MAP27.txt
b1b57f5af4affb619fdb0d31ebe31447e1f33d0da0e1db5258fd38fddbec262d  MAP28.txt
5d2864ff153d9267e1beb55587eb7a43741bbd4575a6995d7e010190cd296ab0  MAP29.txt
aa92847d525e7e52f77a8af0a1dbc30a2bd84c1c07f2689cbb832a26e7b6892a  MAP30.txt
34ffd81843412c2b7582195cd166f903451fc30f63d847dd59148e0888096909  MAP31.txt
58c52624043390cf8d492393096f7930484e938518a9c9695dcc2333410d39b8  MAP32.txt
EOF

echo Please ignore the glBSP errors above, we are running ObHack in a 
echo special test mode.

if ! cmp output.success output.test > /dev/null 2>&1 ; then
	echo Test failed
	mv writer.lua.save scripts/writer.lua
	exit 1
fi

echo Test for $MODE mode success
OUT="$OUT $MODE"

done # for MODE

echo Tests for all of $OUT monsters success

# Clean up
mv writer.lua.save scripts/writer.lua
rm MAP*txt
rm CONFIG.cfg
rm output.test
rm output.success
rm LOGS.txt
