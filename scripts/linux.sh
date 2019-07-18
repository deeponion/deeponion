mkdir -p ~/.DeepOnion
cd ~/.DeepOnion
mv -f DeepOnion.conf .DeepOnion.conf.bak
sudo apt-get install curl -y
echo "$(curl https://deeponion.org/conf_file/DeepOnion.conf)" >> ~/.DeepOnion/DeepOnion.conf
echo "staking=1
checkblockchain=0" >> ~/.DeepOnion/DeepOnion.conf
echo Nodes updated! Restart the DeepOnion wallet.
