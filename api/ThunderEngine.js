import {
    Platform
} from 'react-native';
import ThunderModule from 'react-native-jocloud-rtc';

const react_native_1 = require("react-native");
const ThunderEventEmitter = new react_native_1.NativeEventEmitter(ThunderModule);
const THUNDER_PREFIX = 'thunder_rtc';
const _eventTypes = new Set();
let createEngine = false;
export default class ThunderEngine {

    static hasCreatedEngine() {
        return createEngine;
    }

    static createEngine(appId, sceneId, resultCallback = null) {
        if (createEngine) {
            if (resultCallback != null) {
                resultCallback('已经初始化');
            }
            return
        }
        ThunderModule.createEngine({'appId': appId, 'sceneId': sceneId}).then((value) => {
            createEngine = true;
            if (resultCallback != null) {
                resultCallback('初始化成功')
            }
        }).catch((code, err) => {

        });
    }

    static destroyEngine(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化')
            }
            return
        }
        ThunderModule.destroyEngine({}).then((value) => {
            createEngine = false;
            if (resultCallback != null) {
                resultCallback('卸载成功')
            }
        }).catch((code, err) => {

        });
    }

    static getVersion(resultCallback = null) {
        ThunderModule.getVersion({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setArea(are, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setArea(are).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setMediaMode(mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setMediaMode(mode).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setRoomMode(mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setRoomMode(mode).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static joinRoom(uid, roomName, token, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.joinRoom({'uid': uid, 'roomName': roomName, 'token': token}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static leaveRoom(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.leaveRoom({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static updateToken(token, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.updateToken(token).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setAudioConfig(profile, commutMode, scenarioMode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setAudioConfig({
            'profile': profile,
            'commutMode': commutMode,
            'scenarioMode': scenarioMode
        }).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setAudioSourceType(mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setAudioSourceType(mode).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setMicVolume(volume, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setMicVolume(volume).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopLocalAudioStream(stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopLocalAudioStream(stop).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopAllRemoteAudioStreams(stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopAllRemoteAudioStreams(stop).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setVideoEncoderConfig(playType, publishMode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setVideoEncoderConfig({'playType': playType, 'publishMode': publishMode}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static enableLocalVideoCapture(enable, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.enableLocalVideoCapture(enable).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopRemoteAudioStream(uid, stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopRemoteAudioStream({'uid': uid, 'stop': stop}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static startVideoPreview(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.startVideoPreview({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopVideoPreview(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopVideoPreview({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLocalCanvasScaleMode(mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setLocalCanvasScaleMode(mode).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setRemoteCanvasScaleMode(uid, mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setRemoteCanvasScaleMode({'uid': uid, 'mode': mode}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLocalVideoMirrorMode(mode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setLocalVideoMirrorMode(mode).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopLocalVideoStream(stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopLocalVideoStream(stop).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static getVideoEncoderParam(playType, publishMode, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.getVideoEncoderParam({'playType': playType, 'publishMode': publishMode}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }

        }).catch((code, err) => {

        });
    }

    static stopAllRemoteVideoStreams(stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopAllRemoteVideoStreams(stop).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopRemoteVideoStream(uid, stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopRemoteVideoStream({'uid': uid, 'stop': stop}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static stopAllRemoteVideoStreams(stop, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.stopAllRemoteVideoStreams(stop).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setMultiVideoViewLayout(videoPositions, bgPosition, bgImageName, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        var videoPositionsMap = []
        videoPositions.map((item, i) => {
            videoPositionsMap.push(item.toMap())
        })
        ThunderModule.setMultiVideoViewLayout({
            'videoPositions': videoPositionsMap, 'bgPosition': bgPosition.toMap(), 'bgImageName': bgImageName
        }).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setRemotePlayType(remotePlayType, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setRemotePlayType(remotePlayType).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static getConnectionStatus(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.getConnectionStatus({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }


    static setLiveTranscodingTask(taskId, liveTranscoding, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setLiveTranscodingTask({
            'taskId': taskId,
            'transCodingMode': liveTranscoding.transCodingMode,
            'audioUrl': liveTranscoding.audioUrl,
            'lyricUrl': liveTranscoding.lyricUrl,
            'mediaUrl': liveTranscoding.mediaUrl,
            'mediaStreamLayout': liveTranscoding.getMediaStreamLayoutMap(),
            'users': liveTranscoding.getUserListMap()
        }).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static removeLiveTranscodingTask(taskId, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.removeLiveTranscodingTask(taskId).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static addPublishTranscodingStreamUrl(taskId, url, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.addPublishTranscodingStreamUrl({'taskId': taskId, 'url': url}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static removePublishTranscodingStreamUrl(taskId, url, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.removePublishTranscodingStreamUrl({'taskId': taskId, 'url': url}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static addPublishOriginStreamUrl(url, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.addPublishOriginStreamUrl(url).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static removePublishOriginStreamUrl(url, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.removePublishOriginStreamUrl(url).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static addSubscribe(roomId, uid, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.addSubscribe({'roomId': roomId, 'uid': uid}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static removeSubscribe(roomId, uid, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.removeSubscribe({'roomId': roomId, 'uid': uid}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static switchFrontCamera(bFront, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.switchFrontCamera(bFront).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setVideoCaptureOrientation(orientation, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setVideoCaptureOrientation(orientation).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static enableCaptureVolumeIndication(interval, moreThanThd, lessThanThd, smooth, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.enableCaptureVolumeIndication({
            'interval': interval,
            'moreThanThd': moreThanThd,
            'lessThanThd': lessThanThd,
            'smooth': smooth
        }).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setAudioVolumeIndication(interval, moreThanThd, lessThanThd, smooth, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setAudioVolumeIndication({
            'interval': interval,
            'moreThanThd': moreThanThd,
            'lessThanThd': lessThanThd,
            'smooth': smooth
        }).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static switchFrontCamera(bFront, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.switchFrontCamera(bFront).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static isLoudspeakerEnabled(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.isLoudspeakerEnabled({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static enableLoudspeaker(enable, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.enableLoudspeaker(enable).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLoudSpeakerVolume(volume, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setLoudSpeakerVolume(volume).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }


    static enableMixVideoExtraInfo(enable, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.enableMixVideoExtraInfo(enable).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });

    }

    static sendMediaExtraInfo(msg, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.sendMediaExtraInfo(msg).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setMediaExtraInfoCallback(enable, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setMediaExtraInfoCallback(enable).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLogFilePath(path, resultCallback = null) {
        ThunderModule.setLogFilePath(path).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLogLevel(filter, resultCallback = null) {
        ThunderModule.setLogLevel(filter).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static setLogCallback(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.setLogCallback({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static registerVideoCaptureTextureObserver(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        if (Platform.OS === 'android') {
            ThunderModule.registerVideoCaptureTextureObserver({}).then((value) => {
                if (resultCallback != null) {
                    resultCallback(value)
                }
            }).catch((code, err) => {

            });
        } else {
            if (resultCallback != null) {
                resultCallback('only android platform support this api')
            }
        }
    }

    static registerVideoDecodeFrameObserver(uid, resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.registerVideoDecodeFrameObserver(uid).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static registerVideoCaptureFrameObserver(resultCallback = null) {
        if (!createEngine) {
            if (resultCallback != null) {
                resultCallback('未初始化');
            }
            return;
        }
        ThunderModule.registerVideoCaptureFrameObserver({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }


    static on(eventType, listener) {
        _eventTypes.add(`${THUNDER_PREFIX}${eventType}`);
        var add = false;
        var listAdd = [
            'onJoinRoomSuccess',
            'onLeaveRoom',
            'onSdkAuthResult',
            'onUserBanned',
            'onUserJoined',
            'onUserOffline',
            'onRoomStats',
            'onBizAuthResult',
            'onTokenWillExpire',
            'onTokenRequested',
            'onFirstLocalAudioFrameSent',
            'onLocalAudioStats',
            'onLocalAudioStatusChanged',
            'onRemoteAudioStopped',
            'onRemoteAudioStatsOfUid',
            'onRemoteAudioStateChangedOfUid',
            'onFirstLocalVideoFrameSent',
            'onLocalVideoStats',
            'onLocalVideoStatusChanged',
            'onRemoteVideoStopped',
            'onRemoteVideoStatsOfUid',
            'onRemoteVideoPlay',
            'onVideoSizeChanged',
            'onRemoteVideoStateChangedOfUid',
            'onNetworkQuality',
            'onConnectionStatus',
            'onConnectionLost',
            'onPublishStreamToCDNStatus',
            'onCaptureVolumeIndication',
            'onPlayVolumeIndication',
            'onDeviceStats',
            'onLogCallback',
            'onSendMediaExtraInfoFailedStatus',
            'onRecvMediaExtraInfo',
            'onRecvMixAudioInfo',
            'onRecvMixVideoInfo',
            'onRemoteAudioPlay'];
        if (listAdd.indexOf(eventType) != -1) {
            add = true;
        }

        if (add) {
            ThunderEventEmitter.addListener(`${THUNDER_PREFIX}${eventType}`, (args) => {
                listener(args);
            });
        }
    }
};
