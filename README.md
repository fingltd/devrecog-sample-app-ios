![Fing](FingKitTestApp/Assets.xcassets/AppIcon.appiconset/Icon-60@2x.png)

Table of contents
-----------------

- [Description](#Description)
- [Dependencies](#Dependencies)
- [Build](#Build)
- [Resources](#Resources)
- [Authors](#Authors)
- [License](#License)

Description
------------
This folder contains the sample project of an iOS App containing the functionalities
provided by the Fing SDK for network scanning and device recognition.

The Fing SDK provides the core feature of the [Fing (Network Tools)](https://play.google.com/store/apps/details?id=com.overlook.android.fing) app for iOS. 

It is available as an Objective-C Framework library, suitable to be used with the
standard development tools (Xcode) and to be published on the official Apple Store. As a
framework, it may also be used by applications written in Swift language. It is compatible
with Apple iOS 9.x and greater.

The latest version of the Fing Kit for iOS can be downloaded from [here](https://get.fing.com/fing-business/devrecog/releases/sdk/ios/SDK_Mobile_iOS.zip).

__Fing SDK requires a license key to work. [Create a trial license](https://app.fing.com/internet/business/devrecog/trial) 
or [contact us](mailto:sales@fing.com) to get a valid key.__

Dependencies
-----

Fing SDK requires the following items to be added in “Linked Frameworks and Libraries”
in your Xcode project.

|             Item              |
| ----------------------------- | 
| libresolv.9.tdb               |         
| libsqllite3.tbd               |
| SystemConfiguration.framework |
| Security.framework            |
| Foundation.framework          |
| CFNetwork.framework           |
| CoreTelephony.framework       |

Starting from iOS 13, the Apps that want to access Wi-Fi details must include also the  
entitlement named “com.apple.developer.networking.wifi-info” that must
therefore be added in the property list (see Apple Developer website for details).   

Build
-----

The FingKit framework itself shall be added as “Embedded Binaries” as well; Xcode
automatically includes the framework in the final package. To import and use the
functionalities of the FingKit modules, you shall simply import the module main header.

```objc
#import <FingKit/FingKit.h>
```
Functionalities are accessed via the main singleton class FingScanner.

Resources
---------------

### Current Version

|           | Version |
| --------- | ------- |
| Fing SDK  | 1.9.0   |

### Latest Doc

[Fing Mobile SDK](https://get.fing.com/fing-business/devrecog/documentation/Fing_Mobile_SDK.pdf)

Authors
--------

**Project Owner**

- Marco De Angelis (marco at fing.com)

**Contributors**

- Daniele Pantaleone (daniele at fing.com)
- Tommaso Latini (tommaso at fing.com)

License
-------

Code released under the [MIT License](https://github.com/fingltd/devrecog-sample-app-android/blob/master/LICENSE).
