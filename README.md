# 说明
React Native Jocloud RTC Demo

# 使用
详细安装请参考[文档](https://www.npmjs.com/package/react-native-jocloud-rtc)
## 安装
```
yarn add react-native-jocloud-rtc
```
或者
```
npm i --save react-native-jocloud-rtc
```

## 使用

```js
//主要功能模块
import ThunderModule from "react-native-jocloud-rtc";
 
//视频显示View
import { ThunderRemoteVideoView, ThunderLocalVideoView } from 'react-native-jocloud-rtc';
 
//数据对象
import { LiveTranscoding, MediaStreamLayout, TranscodingUser, VideoPosition } from 'react-native-jocloud-rtc'
```

```
ios 生成main.jsbundle 
react-native bundle --entry-file index.js --platform ios --dev false --bundle-output release_ios/main.jsbundle --assets-dest release_ios/
```