Vagrant.configure("2") do |config|
  config.vm.box = "centos7-nir"


  config.vm.synced_folder "./", "/home/vagrant/data"

  config.vm.provider "virtualbox" do |vb|
     vb.memory = "4096"
     vb.cpus = 4
  end
end