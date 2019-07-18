mkdir -p ~/.DeepOnion
cd ~/.DeepOnion
mv -f DeepOnion.conf .DeepOnion.conf.bak
echo "testnet=0
listen=1
addnode=45.76.237.66:17571
addnode=140.82.26.31:17571
addnode=140.82.1.98:17571
addnode=139.180.197.94:17571
addnode=45.76.212.59:17571
addnode=103.102.44.103:17571
addnode=45.32.234.176:17571
addnode=45.77.201.153:17571
addnode=139.180.197.94:17571
staking=1
checkblockchain=0" >> ~/.DeepOnion/DeepOnion.conf
echo China nodes updated! Restart the DeepOnion wallet.
