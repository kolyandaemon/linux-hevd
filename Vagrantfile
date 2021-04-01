ENV["LC_ALL"] = "en_US.UTF-8"

Vagrant.configure("2") do |config|

  config.vm.box = "centos/7"
  config.vm.box_version = "2004.01"

  config.vm.provision :file, source: './', destination: "/home/vagrant"

  
  config.vm.provision "shell" do |s|
    s.inline="sh /home/vagrant/scripts/install_package.sh"

    #s.inline="sudo yum update"
    #s.inline="sudo yum makecache"

  end

  

  config.vm.provider "virtualbox" do |vb|
     vb.memory = "4096"
     vb.cpus = 4
  end
end
