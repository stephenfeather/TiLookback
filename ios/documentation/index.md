# Lookback Module

## Description

This is an Appcelerator Titanium module for iOS that wraps the Lookback iOS SDK.

## Accessing the Lookback Module

To access this module from JavaScript, you need to first set your app token in a string property and then load the module

```javascript
Ti.App.Properties.setString('LookbackAppToken', 'your_app_token');
var Lookback = require("com.featherdirect.lookback");
```

The Lookback variable is a reference to the Module object.	

## Properties

### enabled

Returns a boolean letting you know if Loopback is enabled (read only)

```javascript
Lookback.enabled 
```

### shakeToRecord

Returns a boolean letting you know if Loopback is listening to the shake event to start recording (read only)

```javascript
Loopback.shakeToRecord
```

## Methods

### enableShakeToRecord

Enables shakeToRecord and returns a boolean telling you the value of the shakeToRecord property

```javascript
Lookback.enableShakeToRecord();
```

### disableShakeToRecord

Disables shakeToRecord and returns a boolean telling you the value of the shakeToRecord property

```javascript
Lookback.disableShakeToRecord();
```

### setUserIdentifier

Method takes a string used to set the userIdentifier so a session can be matched to a specific user

```javascript
Lookback.setUserIdentifier('Joe');
``` 

## Support

There is none. Freely given, freely received, user beware.

## Warranty

There is none.  If you lose your job, your health, end up living in a van down by the river, I am not responsible. User beware.

## Author

Stephen Feather
@stephenfeather

## License

Copyright 2014 Feather Direct, LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
