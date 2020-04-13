#!/bin/bash -e

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua
./ObHack 1FreeDoom1 || true
unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
30988015caff79e54237f810a1a5c51dcb282a8e01683b2d5b4f8c9fd16e64d6  MAP01.txt
0ea3e858503d101302c9df71d7668c1e38b5d62f53d51a04936bf4efb757f3bd  MAP02.txt
6f1df9061441643160465eeab15c0c1a2091dde8af5a48a04f0f0f825d8787ca  MAP03.txt
480b04ed5b802f49aadbc5e1b279cb4fe5ef8c0b7b13c4355e13271db1140d46  MAP04.txt
7ecfc7522510c9ad67acf50bea40a878c22aa5a6c6d69e95f563f0b132f3e6c4  MAP05.txt
f8a4d42f4efe1b55cd234c171fd08da1e547c2885c7154bbbbc6ad65e30feb32  MAP06.txt
79c92eec610a9659e4541e981ebacc6b97ef8da66c6bbc1e207b2e502662ee29  MAP07.txt
8f1586266489f9777667e07ed6553cbbc832207bbbcbb7f99cd67e86bd023916  MAP08.txt
7a70a59f8cfa4f1aefea3a1e266167b1297e4257a726d6a0b964db92d1b86486  MAP09.txt
9fed76aceb5671feb675c87ced10b3e4d6c4a836ef668de13c0d00c2fbd00e8e  MAP10.txt
da145668376abfc20cc62d011959410890345d504e83c17b2799b71e1d67b046  MAP11.txt
b8947d6414602f292aac1fb01144cb1e6845409c9037182afc0ba31678a2ae7c  MAP12.txt
4b83203ffe28b3a09ee2e90417d5246387e33ef06451984d7da146b8bdb079e3  MAP13.txt
5278ffd714838e944057f5069a370ab4c922fd74622b55c7f287a47d7b5db1e6  MAP14.txt
b1242889409fb47372cd5e99892025eedaf3e5bc6679fda7acc7d0c4fda39b33  MAP15.txt
74af423b900b937c3203ba5ceeba5089d2b95f7cb1d488299b8446fbcbd440d6  MAP16.txt
f3e001515c57e39cf92a72aad84b47df863a19c580adf5611ddfcc85cf725e2f  MAP17.txt
a0100d450bd00a9319e22bb48eaf0acce08038a484607cf33629a6ae3ffa1f5d  MAP18.txt
7637ad3d1bd1b757c0308e389fee7a245a79c88cc0b955e1ac596cd64ab56fa3  MAP19.txt
78ac1eaa9cdd920c47317e714517c85363944d27e59bde19403d1903d4d12d0b  MAP20.txt
1283aa3b624655b0561335bf3cc8f5bec8107728b55080fd7f300aad68f7452d  MAP21.txt
e4346fcd104eca91649f78592741c08348e06b21605f265dcc755dfa07176dcc  MAP22.txt
fa2641029fdf5e80b01a2d00c080b2bf56846923ca97a293b05484212176ae7c  MAP23.txt
955c01d98d56521fd2a901954a8e0758b78ac1d56180f68f1047063d50d9ddac  MAP24.txt
9663eb6b5dd72a83ce1399f4e20821baabea53c84dcb0053ec562674d572523a  MAP25.txt
27f06d361645e60dd51e7fe432397a857bc85bbf047109bc2a0f13719a69c2c2  MAP26.txt
2b770fd6720c322db9e0ecf05aa6ddb7ea155a2509fd66ac18756e1e2b130426  MAP27.txt
80f300e901be2d32281027cef0f6065e9b3dbaa6e1845dab0e96b2ea13900785  MAP28.txt
6a67ed99a811cb29f003b2519cdfda060f4f319a17e64e6fd4df683391c838fa  MAP29.txt
9df47e1e9b5702db50612b0e1e384ff1f8543683fc1ad3863f7ea0c650518d92  MAP30.txt
7f638d45fc1a38bc0b25f221c046412a49574f9b52c69e3b8a4e3356143c0cf4  MAP31.txt
ea35fd3666002aa4a520c7d64710a4e9034f62cb1de72e5441d00f9b10a148b0  MAP32.txt
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
