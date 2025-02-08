@echo off
cd build
echo ~~~~~~~~~~~~~~~~~~~~
echo Creating Ninja Files
echo ~~~~~~~~~~~~~~~~~~~~
cmake -G Ninja ..

echo.
echo ~~~~~~~~
echo Building
echo ~~~~~~~~
cmake --build .

echo.
echo ~~~~~~~
echo Running
echo ~~~~~~~
out

cd ..