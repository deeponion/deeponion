mkdir -p ~/.DeepOnion
cd ~/.DeepOnion
mv -f DeepOnion.conf .DeepOnion.conf.bak
sudo apt-get install curl -y
echo "$(curl https://deeponion.org/conf_file/DeepOnion.conf)" >> ~/.DeepOnion/DeepOnion.conf
echo "staking=1" >> ~/.DeepOnion/DeepOnion.conf
echo "checkblockchain=0" >> ~/.DeepOnion/DeepOnion.conf
echo Task finished! Restart the DeepOnion wallet.
