mkdir -p ~/.DeepOnion
cd ~/.DeepOnion
mv -f DeepOnion.conf .DeepOnion.conf.bak
wget https://deeponion.org/conf_file/DeepOnion.conf --ca-certificate=https://raw.githubusercontent.com/deeponion/deeponion/tree/master/contrib/scripts/deeponion-cert.txt
echo "staking=1
checkblockchain=0" >> ~/.DeepOnion/DeepOnion.conf
echo Nodes updated! Restart the DeepOnion wallet.
