# addin-droid

Sample 1C:Enteprise AddIn with Java interop on Android.  
AddIn itself implements simple universal broadcast receiver.  
Made with [modern template](https://github.com/Infactum/addin-template).

## Development tips

- Use native android tests for Java interop.
- Reduce coupling between Android specific code and cross-platform addIn part by using interfaces.
- Release apk should not contain and *.so files.
- Develop Android part with Android Studio (`android` folder), but you are free to use any other IDE for cross-platform C++ code part.
- Java classes loaded from apk could be accessed by `Component::FindClass`. Other class accessed with standard JNI interface.

## License exclusions
In case of embedding add-in based on this template inside 1C:Enterprise configuations, external processors, configuration extensions etc, it's allowed not to apply AGPL terms to whole application part, but only add-in itself.
