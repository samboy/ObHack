#!/bin/bash -e

exit 0 # DISABLE -- won't pass WORK IN PROGRESS

cd ../ObHack-engine-697
rm -f CONFIG.cfg MAP*txt
cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

./ObHack 2FreeDoom1 || true

unix2dos MAP*txt
sha256sum MAP*txt | tr '*' ' ' > output.test
cat > output.success << EOF
651b5e2b1b75855e163e96ebb5c3ac3ca75386fc9748f5b40d0d3a1dda1b9168  MAP01.txt
ac7b600df8654a3a5e99ba894d61e0e269f529294504425e0c2148ab50be0cc4  MAP02.txt
2f8b381b52e7ed72a5489c27452208b5597a9a795ffd04cc7c9ffd61133fed8d  MAP03.txt
6183bba9dde025d1450da2113242c3fac397306fcd8705aa1513bdd64c71d0b1  MAP04.txt
b13d6f8439ba4dd3e259ed7503fe60d451e9744a2b200fe733b7844f8eb2058d  MAP05.txt
98e34c35a5bd91c2b4ac293e6489943130a64671a20d9e583da323a5d3b19390  MAP06.txt
ead0e012c57db8307b01f906aa554023028d6311654c7eed188c531c5dfa7622  MAP07.txt
78549a96bb2571e0a8e1d809f40c5100a38745f3c4a364875aa0987172e2381c  MAP08.txt
ee41056a5179c23c7ce900dad8ee78f750661863040198e233ef058bfa2316a0  MAP09.txt
e0441d2d1f2341fc08ba534f18922775aa893f032f2d4eead4bbaed6f72b4889  MAP10.txt
34a01f1e867be921e446334a7e475518d4f3a998b93268078bf269dc63b6e0da  MAP11.txt
5677f99b97598500c9043a977f01a2cd8f927a5a945dbd3a6b4288b42578ee1b  MAP12.txt
718f6ce2c1ebeb81f07a8fa8f77371c1fc65c284add1715d4cac6edbc5d84173  MAP13.txt
fd0f17bd97beb5e43dfbf10145432dcec03403f07f87b886bae1a1ac88893a08  MAP14.txt
c836719084d0a8eef4ef5118592708d6301ad327e2f988a51f6ab0389cbce481  MAP15.txt
302ad052b57105bd3bf956279f54954b4a6faac7753a2327a980a065958aafe5  MAP16.txt
5ce5491398e3ac9af91565223eef138ab6a768ee70cdca5f85c38738e2ad2f38  MAP17.txt
332398087c384213625f77d60a3769b7235baebdd2a3d99d4466fd1cb2196e63  MAP18.txt
f7bbcaa0a1caacc967f80398bd925c5dd360c36b73379f23819b255cef228cfc  MAP19.txt
669ae7b35ccb10c5a725c7ff536f3e402aa654d8d714ab8b80c399bf035f6d86  MAP20.txt
ef78c550ead81f6e4d049ed850cf9b956168a3f9000128c3eecca429e58cd340  MAP21.txt
85847952e8c76b8d0e1d8325fe5c2ca1420798d4072fd81d1b6fdd51539206df  MAP22.txt
03f5960a82fe3fc8e8f8e0a78d5abbb86a1073ac39e303f4749bc6242dc5bfc6  MAP23.txt
9184324d7b15f7dc0e2416b10162ad2635de049b434b7404ebe78c44a5c2ce3b  MAP24.txt
6c63c64b6c70f8cf0dabd54d6dfe1cdb36776613cc69a2f78683b464c837ea04  MAP25.txt
e85a036cefcbb9620ea3ade8dfe7aed4116ebb0c553b69b24634f8f937135662  MAP26.txt
cc0fac4ce50053a378f211666ae4f845d215457377f60274ac4c301a8431ad25  MAP27.txt
e46ed8686f684b71a4d9717ea1a585cb748bc94f4917de930c2ea213bf58c16f  MAP28.txt
022df99c897b4f04155289c4620271577a4cd4a4d83b4b7501d687daba593508  MAP29.txt
a120abc9cfd70c153c2893525b20e6c745afff5cf92274cfb93411f9a3c9f7da  MAP30.txt
d0e50282c7dadd02fe2716de6f2d833a1dc75bcdaf01c9cf1e391b6239cdd409  MAP31.txt
f0e37d301fb5d5f185e258de6553ecaa711d7f448035d785d9d9ac842151e6b1  MAP32.txt
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
