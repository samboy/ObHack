#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt

cat > CONFIG.cfg << EOF
game = freedoom
mons = normal
seed = 1FreeDoom1
port = nolimit
mode = coop
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

cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua
./ObHack 1FreeDoom1 || true
unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
cfcb0099460354774517eb3133f890b5e2aa5453b021594b5dd1ad807f5e11c3  MAP01.txt
8f4554d6f1572527d992e28ea543ec88b2f289acdfd35bd46fe118af3c0d5bec  MAP02.txt
d02362f6a83c1e80dab8bc59b13f824203f516205be108455e43c720820f55c8  MAP03.txt
6bcbf6de4c879d63d7d88838dc420c3b377f2098efb1df5b08de2fe88e36522d  MAP04.txt
b93161371a9b00c29a5fadb72028a8f4acf9292cf31a7497f8fe802c614eecd6  MAP05.txt
c1e48ff39c7f4112efc14ad0a4d27d23da6bb1596a167ee17bc8c0d10d72d66e  MAP06.txt
800c5757776f68adb9faf996e918ed0b0b5d26c084471b42cab10e11c702b703  MAP07.txt
de1b182c888d1307b8b05c8d36d4a20eb18802309f4f2759ea46299118c33240  MAP08.txt
e5c618a3fea217ab1b7a72783e429d6bb84a12a7dcd23dfd9243e563302f17f9  MAP09.txt
549beeaf425d73a19a34cbbf11bb56d58de5de731c570a018c8e8f32595eba97  MAP10.txt
4eb7a443659432df100e3d274ae4282af8ac84b0b802b035c322989e7560855b  MAP11.txt
f2feacd77b44121c2c244d699c01a2104665a31bbcdb11e32ad32782e53d9ecf  MAP12.txt
a85dc0fdb5b5df1b3505307787f492411c6be0c6032f59e9464377bce62c8115  MAP13.txt
a3ece868b936a9b2eebcb5ac799708ab113defca0b9bbab26d51613b14cfce32  MAP14.txt
33fb88ca57f9051b80fa79d796be39969c2bdfa1de6c473031fc47b8ad17d4f4  MAP15.txt
bcdd8a779a9078049c4b79c2cb5453be25c92101c21797b10dd0eb7cc83867f1  MAP16.txt
c6775ef766421ecc8ce45a6271cd841d317ea8684d6fc03dff9b4e3f568e4fdb  MAP17.txt
736e86c26502d58b53348ced3a9387e1bfaef481f71954e188ae106bb35df92e  MAP18.txt
72a04d9d5f47c2076502acf91be5e8d913047ff8e821874a9493ab23fc98167c  MAP19.txt
95edd5c765932d1602c4beb1b006e9d84e40155d1505472bde301bd214a2a2f7  MAP20.txt
edbf448125046714749f42919cc1f8d8f358bf4fc2b37138c6c245542e2d1a61  MAP21.txt
f0a9aa6920c46c89757fa2a8de74e044bef1fd67203decd74485bc619403215f  MAP22.txt
e1c560fcaaaa86f5855ba77d4b15aec85629b6bb68994bc88cbc5e157058f05b  MAP23.txt
4e9783ef2c44345c6a7f028bbd32093b0f09661ef4e9af140976e651d3740b2c  MAP24.txt
4ba2c5f19f0f608147067f1606f928b890ea4fb8f17d154e4d7f3452329efcbc  MAP25.txt
9468122a62b086eed9c51edd2cbd090340a9f0f6f6e603a5d388f67a6e569a69  MAP26.txt
b67ae0b0623273f4b4acf4dc0060ea5ec578e562e909fe520f484066e2e2c525  MAP27.txt
d052456907eae09189ba17605c57fbce4026ffe4f896e6097bed28e5a38a33a0  MAP28.txt
d5ea7afa97be92f4fe9135041de0cfd7f7e84ecd7e6b266ae78e6113d41787f2  MAP29.txt
5d98ec6e2b961cefea6021d742a99b081b54f0b64d2fcc1a91b412bed2728ce2  MAP30.txt
2eb92b973b41def2a4af820584191f9a64d3096ddb57f6319d29e650557e962e  MAP31.txt
d14a2fd79b4ae85c946efebfd4f9e1173992703f38a6a70ef7971b5f3bd4eccd  MAP32.txt
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
rm CONFIG.cfg
rm MAP*txt
rm output.test
rm output.success
rm LOGS.txt
