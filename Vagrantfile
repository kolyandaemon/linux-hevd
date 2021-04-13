$script = <<-SCRIPT
#!/bin/bash

sudo yum -y  update
sudo yum -y install git

git clone https://github.com/kolyandaemon/linux-hevd.git

sudo chown -R vagrant:vagrant /home/vagrant/linux-hevd

sh /home/vagrant/linux-hevd/scripts/install_package.sh
SCRIPT

Vagrant.configure("2") do |config|

  config.vm.box = "centos/7"
  config.vm.box_version = "2004.01"

  
  config.vm.provision "shell" do |s|
    s.inline= $script
  end

  

  config.vm.provider "virtualbox" do |vb|
     vb.memory = "4096"
     vb.cpus = 4
  end
end
