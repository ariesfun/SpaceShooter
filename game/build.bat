rm build -r
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cd ..
.\build\Release\SpaceShooter.exe