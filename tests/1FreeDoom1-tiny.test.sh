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
size = tiny
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
1872742c53d33b2ab4d1b0eb8bf7db7234dc50c3d6aec09765d9e45ac1d5aa88  MAP01.txt
db29e6dac89c4c5c5d7f23d50e5c14fb720563ec9ad61d7e9804f669daeab590  MAP02.txt
c57e22f00e4935bd415f1bbb166d1d379a3c5c1bd7350ac9c78365a48f3fc9f0  MAP03.txt
5838e01d95e9edcd16094d734ad3cb41c76663660d211f5e2dc22e2e4c62891d  MAP04.txt
75ebd11708cc970b1915bcd7db8b6d25b095f63c578b164d23d5aab920993ae0  MAP05.txt
d9238a16b669c082a2b8021c378a0983a2c6efb036b18573be993d2879050606  MAP06.txt
1bdf30068bdfa20a4d5ce19ddde0c6cbb76f0d04ee1fef3b179a9967eab6631b  MAP07.txt
e9cd2e07799ec430563987b1856be6aaa0510c862a001559b48617205aa23b66  MAP08.txt
46be429244ea221ff707ebf9b1526a7fdbe072cf11f209df786f0497ac40040b  MAP09.txt
f3b6602421ed7f51f6199ad5e63c4879e4582a3a8a543154015aa61458eb0c30  MAP10.txt
ebc12164808495eaae508be2cb18f32aa3e614a8e892f61b0787c8d1fe22c0be  MAP11.txt
8ae06041f0361c8ff1fcab9b71ba06bfb86995f339289856d0c561a2b37b08f7  MAP12.txt
f3d1906e1048e4bf95be860fbc82b065c52d302712d33454abaae794e2b75a7f  MAP13.txt
1cb3fbc7d8b7fa3f8764002fe1682e789f75bdc79bd73cd3cfdc0215c8e306c1  MAP14.txt
3f3e0de47578da4755e99c0cac943638fa5e4681c31ab79d78120fdd2d9081f0  MAP15.txt
fc0de6f2da8e8214f05a5341365818dad3f798614efa09b209c9e432b3d49cee  MAP16.txt
5cd46bba4b5a5d25f8026e6445c592fdf5e3d7460ffb65291ec0135d576b56d4  MAP17.txt
1a71365c47dbccc46548dc1d72e03311c5666dbeb28267e88ae19e805ae94f65  MAP18.txt
804b44854a15219a95571d849defdb060ba5136f9e1560d18f2a21e8f173523c  MAP19.txt
76dd6a7be77452cb5b3d4e970f65cd48345a65816667f9af2df75d3827c72a2b  MAP20.txt
010434d559c59024ad6e84e87095fe5da68a9d9015534664cd26fae5b2799ad7  MAP21.txt
d924c35e64f2b5fe6687d41fc7af2c1f9dc7cdf5f59bba98b3896c8a1b0d28db  MAP22.txt
8044e85580b0aa4cbc25e6524ce1521b1edf425f69e7c7ffde04d97204ea394a  MAP23.txt
33208d678df3359d6016b4c1dc0b9697d5162ae4e74fea7a6c412d832a2fb6d5  MAP24.txt
eb275f2e2ff728127f924d70b34b57cee64cbaefc86164ac09f4aba5eda13a6c  MAP25.txt
cf2e0a5d56370bc1f1886e7267f0df577e641c46ec75cbfc7dadc7664606ebbf  MAP26.txt
e481cd404ea25e74216c0487d37eac65326e696d6cbd39536e0716f4fbab1d59  MAP27.txt
18d747f89e0e0ff23454cdb9f485ab261ebcb723308c9b937b75baa88fb8c563  MAP28.txt
c3c9bcf60c91323a94489b03729f713d53a0591c477ee9f4eb3d708cc68cbf9a  MAP29.txt
4930f78d7066957f81128ecc7792c3858643ceb2d59335ac9544f6bf96664964  MAP30.txt
1edcc3d1212b07505b0aa50ef55b9292b03c039774695755180635986ab777b9  MAP31.txt
2ced2b77e489032ce6f90d80b6811c003b95dc5ef487ed7ae7b0e61c5a6e5dc9  MAP32.txt
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
