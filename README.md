
# react-native-zendrive

## Getting started

`$ npm install react-native-zendrive --save`

### Mostly automatic installation

1. `$ react-native link react-native-zendrive`
##### IOS

- In your project under Embedded Binaries, add the following 
Frameworks from the react-native-zendrive/ios folder in node_modules:
   - AWSSQS.framework
   - ZipArchive.framework
   - FMDB.framework
   - AWSCore.framework

Be sure that 'Copy items if needed' is checked

- Adjust Project Settings
 Allow background location updates for your app.
 On the project screen, click Capabilities.
 Turn Background Modes on.
 Select Location updates.
 
- Disable Bitcode for your app. The Zendrive SDK does not support Bitcode.
 On the Project Settings screen, select the relevant Target for your app.
 Click Build Settings.
 Search the options for Enable Bitcode.
 Ensure it is set to No.
 
- Add the key NSLocationAlwaysUsageDescription to your Info.plist. Set its value to your custom text that tells the user why you want them to allow location services for the application. See sample text below.
 This is required for iOS 8 and above. See Apple's documentation.
 
 Add the key NSMotionUsageDescription to your Info.plist. Set its value to your custom text that tells the user why you want them to allow motion services for the application. See sample text below.
 "We use activity to detect your driving trips faster and more accurately.
 This also reduces the amount of battery we use."
 This is used for better trip detection results. While we need you to add this key to your plist, this program requires an opt-in. If you want to take advantage of this program, please contact us to opt-in. If you choose not to, this permission will not be used.

- Add your Zendrive SDK to your Info.plist 
```
    <key>ZendriveKey</key>
    <string>YourKey</string>
 ```

##### Android
- Add your Zendrive SDK in the following spot
```
protected List<ReactPackage> getPackages() {
            return Arrays.<ReactPackage>asList(
                    new MainReactPackage(),
            new RNZendrivePackage("YourKey")   <- here
            );
        }
```

- add permissions ACCESS_COARSE_LOCATION and ACCESS_FINE_LOCATION, 
and if on Android Q, ACCESS_BACKGROUND_LOCATION, ACTIVITY_RECOGNITION

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-zendrive` and add `RNZendrive.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNZendrive.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Follow above steps for IOS
5. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.RNZendrivePackage;` to the imports at the top of the file
  - Add `new RNZendrivePackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-zendrive'
  	project(':react-native-zendrive').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-zendrive/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-zendrive')
  	```
4. Follow above steps for Android  	

## Usage
```javascript
import RNZendrive from 'react-native-zendrive';

// TODO: What to do with the module?
RNZendrive;

RNZendrive.startPeriod1().then(res => res).catch(e => e);

RNZendrive.startPeriod2("driverID").then(res => res).catch(e => e);

RNZendrive.startPeriod3("driverID").then(res => res).catch(e => e);

RNZendrive.stopPeriod().then(res => res).catch(e => e)

RNZendrive.enableZendrive("driverID").then(res => res).catch(e => e)

// Calling disableZendrive in an ongoing period can result in malformed data
RNZendrive.disableZendrive().then(res => res).catch(e => e)
```
