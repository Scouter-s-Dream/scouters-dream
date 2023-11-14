
# Installation


```bash
sudo apt install -y g++ cmake make git libgtk2.0-dev pkg-config
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update && sudo apt install gcc-11 g++-11
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 50
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 50  
sudo apt install pkg-config ffmpeg libavformat-dev libavcodec-dev libswscale-dev
cd ~    
git clone https://github.com/opencv/opencv.git
cd opencv
cmake -B build 
cd build 
make -j5 
sudo make install
``` 