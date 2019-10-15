# The-Carpenter-Tutor

## UPDATE:

- This project is currently be reworked at the moment. I am shifinting away from the PHP middleware for database management to a GO API instead under this project:
  - https://github.com/KaminFay/CarpentryTutorApi
- I have archived the mobile app that was used for testing while working on this for school:
  - https://github.com/KaminFay/TheCarpentryTutorApp
- And I will be starting a ground up overhaul of this project, I feel there is a lot of promise for what can be done here but it needs a refresh (not a time crunched school project).

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
