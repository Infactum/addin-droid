if exist dist rd /q /s dist
mkdir dist
copy MANIFEST.XML dist\MANIFEST.XML

pushd android
call gradlew clean app:stripReleaseDebugSymbols
copy app\build\intermediates\stripped_native_libs\release\out\lib\x86\libDroid.so ..\dist\libDroid_i386.so
copy app\build\intermediates\stripped_native_libs\release\out\lib\x86_64\libDroid.so ..\dist\libDroid_x64.so
copy app\build\intermediates\stripped_native_libs\release\out\lib\armeabi-v7a\libDroid.so ..\dist\libDroid_ARM.so
copy app\build\intermediates\stripped_native_libs\release\out\lib\arm64-v8a\libDroid.so ..\dist\libDroid_ARM64.so

call gradlew assembleRelease -Pexclude-libs
copy C:\AndroidStudioProjects\addin-android\android\app\build\outputs\apk\release\app-release-unsigned.apk ..\dist\Droid.apk
popd