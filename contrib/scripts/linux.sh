mkdir -p ~/.DeepOnion
cd ~/.DeepOnion
mv -f DeepOnion.conf .DeepOnion.conf.bak
echo | openssl s_client -servername deeponion.org -connect deeponion.org:443 |\
  sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > ~/.DeepOnion/deeponion.crt
wget https://deeponion.org/conf_file/DeepOnion.conf --ca-certificate=~/.DeepOnion/deeponion.crt
echo "staking=1
checkblockchain=0" >> ~/.DeepOnion/DeepOnion.conf
echo Nodes updated! Restart the DeepOnion wallet.
