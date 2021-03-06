#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

# This is a test which tests the level design and placement of single
# player things for all 32 1FreeDoom1 FreeDoom maps

rm -f MAP*txt

cat > CONFIG.cfg << EOF
mode = sp
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
	# Please be aware that this GAWK script is *not* POSIX compatible
	# It uses GAWK 4.0 and higher sorting.
	# The reason being we sort the things because adding things screws
        # up their order in the file
	cat $a | gawk 'BEGIN {PROCINFO["sorted_in"]="@ind_str_asc"}
			{
                        if($0 ~ /^THINGS/){a++;
			  if($0 ~ /START/){print}
			  if($0 ~ /END/){for(b in t){print b}}}
			if(a == 1 && $NF < 16){t[$0]=1}
			if(a != 1){print}
			}' > foo
	mv foo $a
done

sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
9d562ecdd9320258db435dc0750fe0d2e94dcaaaad4adfec02cd73c011d4c4a0  MAP01.txt
773127a11194ecef1bb352404ca4506f0830f7f3e019fd97c31349518a91cc5a  MAP02.txt
8a5ed8b9e9aa7da78a130a216d101621ccd427e1bc2a88c3be0a1c7ee1e28c3e  MAP03.txt
a109526ba7a3622f57c7f07a17392094b6ed57f8e9405f533e8b24002b93cff3  MAP04.txt
fe3ea94a1eae5f712f96d2468f280084305422f12c6d4584c2396508e911085c  MAP05.txt
dc95219ff0d50e02d31d50acbc474a2a472eb557ecb87a0a39e7a846bee0b831  MAP06.txt
a15aace245c3e4a739f4e596dff329c19a47fad36120814a1c287a74175d94bb  MAP07.txt
c9ce18e89aaee038384c1d78fe193a598ed83a171912b60ad6ba2eff91ffee2b  MAP08.txt
537a7396106caf5375d001ad5691a1236715a90a2bdf4cddcf41dc44ebc9ed83  MAP09.txt
707c2bf336182f0e843cf85ab4b96c0ebf8cda7b9bdca087ea08be33f97dad45  MAP10.txt
82fab1313c02bea05fe393e47b3eb01580c9d0fdac169d93248c10a96d1a96c2  MAP11.txt
58285dc13372fa54e43b1d4e9397032aaed55c7c0a475aef94e43d3883149c6a  MAP12.txt
103c0e8743dfa2e426fab41a228a3568196647ccea533a1c16149c4300c2ad52  MAP13.txt
9cca10e6a20f9b0c41d2c1536929b02f10f83f9ed4c22136904ee5f46302ed4a  MAP14.txt
3082d4155ab722067e26c39fd12f1898c31971779fd97ed1547840e1d5daee14  MAP15.txt
ca2a809c8facb33d7e36219f4a328341fd1308d45d6c90896b3174623d722474  MAP16.txt
9ff549d91baf2b1b051ba276e7dc4a676868023bcd2d337fe098e3e1e0c5cfce  MAP17.txt
67ea6ec388bc73acd40a7e2ec6990cb3c253465bc53a86af16a0faf9bdf5b8f7  MAP18.txt
b9c5cded981aea54b9783b5bf3e485808257ede4dd5894daae675f19937ee419  MAP19.txt
36007ce26e41a3aac6e269047830e2c3b4276198ac67328c27b82e19c3d093c8  MAP20.txt
3856062f52c0e0ac864ffac8b18fdf59096fc097c4bcdab5be2d29bb7b3027ba  MAP21.txt
a5892c5c687ec6e81f100c731dcc836018209260ebc15bd4e0a7eace7bfde6aa  MAP22.txt
a2886468c36d7a6c07ed6bcb92c5b2f7a0ff096053285b35953f0d4b92a2ae58  MAP23.txt
a4ed5d517e9d6cb7fbfde400399b93b3abb498ef0b17b3a24d9c36f7abf74b2c  MAP24.txt
1789e5f838f8bfc2c718924d86b0852c6b1dcb76103e364bc8c494a77a97aad1  MAP25.txt
373013dcd7a1f66a0c0df996fa98d9cd206034c54a0f2e962fec4d5592050aa3  MAP26.txt
e823aaccbbcacbbc459953da4dce71adf1c131c9038894ea90786a0f26bb8f27  MAP27.txt
f07107372e4d51ffa199d29c2ff85606e1370f370890af6bc7e4805bdbca52e7  MAP28.txt
06031ff7172404e9975921e84020a0506400a86beb4afee84a3cb4a148353522  MAP29.txt
1a11fb70bbafdb6128cd92c9f7b1291d98f23f3658cac0178987e278cfdad338  MAP30.txt
9bd35567b5ab4a049438922e743d99130f3790b2c4df38d38ca54157169d9768  MAP31.txt
17337838f47ce267c30fad2f518ad0bbc678210709bda94455ee570c945bff62  MAP32.txt
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
rm CONFIG.cfg
rm output.test
rm output.success
rm LOGS.txt
