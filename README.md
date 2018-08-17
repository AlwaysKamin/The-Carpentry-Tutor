# The-Carpenter-Tutor

## Mac Setup
---

Install Homebrew:
- www.brew.sh

Setup path:
```console
nano ~/.bash_profile

#brew
exportPATH=/usr/local/bin:$PATH
```

Grab dependencies:
```console
brew install cmake
brew install glew
brew install glfw3

brew tap homebrew/science
brew install opencv3 --with-contrib
brew install librealsense

```
  
Clone this repository to wherever you'd like:

```console 
git clone https://github.com/AlwaysKamin/The-Carpentry-Tutor.git 
```

To build:

```console
cd [path]/The-Carpentry-Tutor
mkdir build
cd build
cmake ..
make
```

To Run:

```console
cd [path]/The-Carpentry-Tutor
./bin/CarpentryTutor
```
