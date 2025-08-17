rm SpaceShooter-Windows.exe
%不删除 build 目录，直接进入并编译%
if not exist build mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd ..
.\SpaceShooter-Windows.exe