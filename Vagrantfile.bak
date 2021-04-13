
Vagrant.configure("2") do |config|

  config.vm.box = "centos/7"
  config.vm.box_version = "2004.01"

  #config.vm.provision :file, source: './', destination: "/home/vagrant"
  config.vm.synced_folder "./", "/home/vagrant/linux-hevd-tutorial"
  
  #config.vm.provision "shell" do |s|
   # s.inline="/bin/sh /home/vagrant/scripts/install_package.sh"
  #end

  

  config.vm.provider "virtualbox" do |vb|
     vb.memory = "4096"
     vb.cpus = 4
  end
end
