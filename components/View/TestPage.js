import React, {Component} from 'react'
import {
    Picker,
    StyleSheet,
    TouchableOpacity,
    Text,
    View,
    Dimensions,
    ScrollView,
    TextInput,
    Platform,
    SafeAreaView
} from 'react-native'
import CheckBox from '../CheckBox'
import ThunderEngine from '../../api/ThunderEngine'
import Config from '../Config'
import {ThunderRemoteVideoView, ThunderLocalVideoView} from 'react-native-jocloud-rtc'
import FeedbackUtils from "../../api/FeedbackUtils"
import RadioButton from "../RadioButton"
import {isIphoneX} from "../../api/IphoneUtil"

const {width, height, scale} = Dimensions.get('window')
const videoHeight = 150
const apiTopViewHeight = 38
const apiContentViewHeight = 280
const bottomHeight = 44
const iphoneXHead = 44
const iphoneHead = 20
const redTextHeight = 20
let logPrev1 = 1
let logPrev2 = 1
let logPrev3 = 1
let logPrev4 = 1
let logPrev5 = 1
let localVideoCanvasModeUse = 1
let remoteVideoList = []
export default class TestPage extends Component {
    constructor(props) {
        super(props)

        this.state = {
            showPage: true,
            apiSelectedTab: 1,
            callbackSelectedTab: 1,
            addTransUser: false,
            zoomInVideo: '',
            zoomInCallback: false,
            callbackInfo1: '',
            callbackInfo2: '',
            callbackInfo3: '',
            callbackInfo4: '',
            callbackInfo5: '',
            localUser: null,
            remoteUser: [],
            createEngineTotal: 0,
            createEngineF: 0,
            createEngineRet: 0,
            destroyEngineTotal: 0,
            destroyEngineF: 0,
            destroyEngineRet: 0,
            setAreaTotal: 0,
            setAreaF: 0,
            setAreaRet: 0,
            setRemotePlayTypeTotal: 0,
            setRemotePlayTypeF: 0,
            setRemotePlayTypeRet: 0,
            joinRoomTotal: 0,
            joinRoomF: 0,
            joinRoomRet: 0,
            leaveRoomTotal: 0,
            leaveRoomF: 0,
            leaveRoomRet: 0,
            setMediaModeTotal: 0,
            setMediaModeF: 0,
            setMediaModeRet: 0,
            setRoomModeTotal: 0,
            setRoomModeF: 0,
            setRoomModeRet: 0,
            setAudioConfigTotal: 0,
            setAudioConfigF: 0,
            setAudioConfigRet: 0,
            getConnectionStatusTotal: 0,
            getConnectionStatusRet: 0,
            getConnectionStatusRetText: "",
            enableLoudspeakerTotal: 0,
            enableLoudspeakerF: 0,
            enableLoudspeakerRet: 0,
            isLoudspeakerEnabledTotal: 0,
            isLoudspeakerEnabledRet: 0,
            setAudioVolumeIndicationTotal: 0,
            setAudioVolumeIndicationF: 0,
            setAudioVolumeIndicationRet: 0,
            enableCaptureVolumeIndicationTotal: 0,
            enableCaptureVolumeIndicationF: 0,
            enableCaptureVolumeIndicationRet: 0,
            stopLocalAudioStreamTotal: 0,
            stopLocalAudioStreamF: 0,
            stopLocalAudioStreamRet: 0,
            stopAllRemoteAudioStreamsTotal: 0,
            stopAllRemoteAudioStreamsF: 0,
            stopAllRemoteAudioStreamsRet: 0,
            stopRemoteAudioStreamTotal: 0,
            stopRemoteAudioStreamF: 0,
            stopRemoteAudioStreamRet: 0,
            setMicVolumeTotal: 0,
            setMicVolumeF: 0,
            setMicVolumeRet: 0,
            setLoudSpeakerVolumeTotal: 0,
            setLoudSpeakerVolumeF: 0,
            setLoudSpeakerVolumeRet: 0,
            sendMediaExtraInfoTotal: 0,
            sendMediaExtraInfoF: 0,
            sendMediaExtraInfoRet: 0,
            setMediaExtraInfoCallbackTotal: 0,
            setMediaExtraInfoCallbackF: 0,
            setMediaExtraInfoCallbackRet: 0,
            setVideoEncoderConfigTotal: 0,
            setVideoEncoderConfigF: 0,
            setVideoEncoderConfigRet: 0,
            getVideoEncoderParamTotal: 0,
            getVideoEncoderParamF: 0,
            getVideoEncoderParamRet: 0,
            setLocalVideoCanvasTotal: 0,
            setLocalVideoCanvasF: 0,
            setLocalVideoCanvasRet: 0,
            setRemoteVideoCanvasTotal: 0,
            setRemoteVideoCanvasF: 0,
            setRemoteVideoCanvasRet: 0,
            setLocalCanvasScaleModeTotal: 0,
            setLocalCanvasScaleModeF: 0,
            setLocalCanvasScaleModeRet: 0,
            setRemoteCanvasScaleModeTotal: 0,
            setRemoteCanvasScaleModeF: 0,
            setRemoteCanvasScaleModeRet: 0,
            enableLocalVideoCaptureTotal: 0,
            enableLocalVideoCaptureF: 0,
            enableLocalVideoCaptureRet: 0,
            startVideoPreviewTotal: 0,
            startVideoPreviewF: 0,
            startVideoPreviewRet: 0,
            stopVideoPreviewTotal: 0,
            stopVideoPreviewF: 0,
            stopVideoPreviewRet: 0,
            stopLocalVideoStreamTotal: 0,
            stopLocalVideoStreamF: 0,
            stopLocalVideoStreamRet: 0,
            stopRemoteVideoStreamTotal: 0,
            stopRemoteVideoStreamF: 0,
            stopRemoteVideoStreamRet: 0,
            stopAllRemoteVideoStreamTotal: 0,
            stopAllRemoteVideoStreamF: 0,
            stopAllRemoteVideoStreamRet: 0,
            setLocalVideoMirrorModeTotal: 0,
            setLocalVideoMirrorModeF: 0,
            setLocalVideoMirrorModeRet: 0,
            setVideoCaptureOrientationTotal: 0,
            setVideoCaptureOrientationF: 0,
            setVideoCaptureOrientationRet: 0,
            switchFrontCameraTotal: 0,
            switchFrontCameraF: 0,
            switchFrontCameraRet: 0,
            addSubscribeTotal: 0,
            addSubscribeF: 0,
            addSubscribeRet: 0,
            removeSubscribeTotal: 0,
            removeSubscribeF: 0,
            removeSubscribeRet: 0,
            areaType: 0,
            remotePlayType: 0,
            mediaMode: 0,
            roomMode: 0,
            profile: 0,
            commutMode: 0,
            scenarioMode: 0,
            enableLoudspeaker: true,
            stopLocalAudioStream: false,
            stopAllRemoteAudioStreams: false,
            stopRemoteAudioStream: false,
            stopRemoteAudioStreamUid: '',
            micVolume: 0,
            loudSpeakerVolume: 0,
            audioSourceType: 0,
            mediaExtraInfo: 'adc1234',
            publishPlayType: 0,
            publishVideoMode: 2,
            getPublishPlayType: 0,
            getPublishVideoMode: 2,
            multiVideoViewLayout: 9,
            localVideoCanvasMode: 1,
            localCanvasScaleMode: 1,
            localVideoCanvasUid: '',
            remoteVideoCanvasMode: 1,
            remoteCanvasScaleMode: 1,
            remoteVideoCanvasUid: '',
            enableLocalVideoCapture: true,
            stopLocalVideoStream: false,
            stopRemoteVideoStreamUid: '',
            stopRemoteVideoStream: false,
            stopAllRemoteVideoStream: false,
            mirrorMode: 0,
            videoCaptureOrientation: 1,
            frontCamera: true,
            addSubscribeRoomId: '',
            addSubscribeUid: '',
            removeSubscribeRoomId: '',
            removeSubscribeUid: '',
            audioChorus: false,
            videoChorus: false,
            mediaStreamLayout: '400,400,200,200,0',
            setMediaExtraInfoCallbackEnable: false,
        }
    }

    show() {
        this.setState({
            showPage: true
        })
    }

    hide() {
        this.setState({
            showPage: false
        })
    }


    componentDidMount() {
        this.props.onRef(this)
        ThunderEngine.on('onJoinRoomSuccess', (ret) => {
            this.addCallBackInfo(1, 'onJoinRoomSuccess ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onLeaveRoom', (ret) => {
            this.addCallBackInfo(1, 'onLeaveRoom ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onSdkAuthResult', (ret) => {
            if (Config.STOP_ON_SDK_AUTH_RESULT_LOG != '1') {
                this.addCallBackInfo(1, 'onSdkAuthResult ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onUserBanned', (ret) => {
            this.addCallBackInfo(1, 'onUserBanned ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onUserJoined', (ret) => {
            this.addCallBackInfo(1, 'onUserJoined ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onUserOffline', (ret) => {
            this.addCallBackInfo(1, 'onUserOffline ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRoomStats', (ret) => {
            if (Config.STOP_ON_ROOM_STATS_LOG != '1') {
                this.addCallBackInfo(1, 'onRoomStats ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onBizAuthResult', (ret) => {
            if (Config.STOP_ON_SDK_AUTH_RESULT_LOG != '1') {
                this.addCallBackInfo(1, 'onBizAuthResult ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onTokenWillExpire', (ret) => {
            this.addCallBackInfo(1, 'onTokenWillExpire ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onTokenRequested', (ret) => {
            this.addCallBackInfo(1, 'onTokenRequested ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onFirstLocalAudioFrameSent', (ret) => {
            this.addCallBackInfo(1, 'onFirstLocalAudioFrameSent ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onLocalAudioStats', (ret) => {
            if (Config.STOP_ON_LOCAL_AUDIO_STATUS_LOG != '1') {
                this.addCallBackInfo(1, 'onLocalAudioStats ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onRemoteAudioPlay', (ret) => {
            this.addCallBackInfo(1, 'onRemoteAudioPlay ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onLocalAudioStatusChanged', (ret) => {
            this.addCallBackInfo(1, 'onLocalAudioStatusChanged ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRemoteAudioStopped', (ret) => {
            this.addCallBackInfo(1, 'onRemoteAudioStopped ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRemoteAudioStatsOfUid', (ret) => {
            if (Config.STOP_ON_REMOTE_AUDIO_STATS_OF_UID_LOG != '1') {
                this.addCallBackInfo(1, 'onRemoteAudioStatsOfUid ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onRemoteAudioStateChangedOfUid', (ret) => {
            this.addCallBackInfo(1, 'onRemoteAudioStateChangedOfUid ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onFirstLocalVideoFrameSent', (ret) => {
            this.addCallBackInfo(1, 'onFirstLocalVideoFrameSent ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onLocalVideoStats', (ret) => {
            if (Config.STOP_ON_LOCAL_VIDEO_STATUS_LOG != '1') {
                this.addCallBackInfo(1, 'onLocalVideoStats ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onLocalVideoStatusChanged', (ret) => {
            this.addCallBackInfo(1, 'onLocalVideoStatusChanged ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRemoteVideoStopped', (ret) => {
            if (!ret.stop) {
                let it = null
                let index = 0
                let remoteUser = this.state.remoteUser
                remoteUser.map((item, i) => {
                    if (item.uid == ret.uid) {
                        index = i
                        it = item
                    }
                })
                if (it != null) {
                    remoteUser.splice(index, 1)
                    this.setState({remoteUser: remoteUser})

                    remoteUser.splice(index, 0, it)
                    this.setState({remoteUser: remoteUser})
                }
            }
            this.addCallBackInfo(1, 'onRemoteVideoStopped ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRemoteVideoStatsOfUid', (ret) => {
            if (Config.STOP_ON_REMOTE_VIDEO_STATS_OF_UID_LOG != '1') {
                this.addCallBackInfo(1, 'onRemoteVideoStatsOfUid ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onRemoteVideoPlay', (ret) => {
            this.addCallBackInfo(1, 'onRemoteVideoPlay ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onVideoSizeChanged', (ret) => {
            this.addCallBackInfo(1, 'onVideoSizeChanged ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRemoteVideoStateChangedOfUid', (ret) => {
            this.addCallBackInfo(1, 'onRemoteVideoStateChangedOfUid ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onNetworkQuality', (ret) => {
            if (Config.ON_NETWORK_QUALITY_LOG != '1') {
                this.addCallBackInfo(1, 'onNetworkQuality ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onConnectionStatus', (ret) => {
            this.addCallBackInfo(1, 'onConnectionStatus ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onConnectionLost', (ret) => {
            this.addCallBackInfo(1, 'onConnectionLost ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onPublishStreamToCDNStatus', (ret) => {
            this.addCallBackInfo(1, 'onPublishStreamToCDNStatus ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onCaptureVolumeIndication', (ret) => {
            this.addCallBackInfo(5, 'onCaptureVolumeIndication ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onPlayVolumeIndication', (ret) => {
            this.addCallBackInfo(5, 'onPlayVolumeIndication ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onDeviceStats', (ret) => {
            if (Config.STOP_ON_DEVICE_STATS_LOG != '1') {
                this.addCallBackInfo(1, 'onDeviceStats ' + JSON.stringify(ret))
            }
        })
        ThunderEngine.on('onSendMediaExtraInfoFailedStatus', (ret) => {
            this.addCallBackInfo(1, 'onSendMediaExtraInfoFailedStatus ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRecvMixAudioInfo', (ret) => {
            this.addCallBackInfo(1, 'onRecvMixAudioInfo ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRecvMixVideoInfo', (ret) => {
            this.addCallBackInfo(1, 'onRecvMixVideoInfo ' + JSON.stringify(ret))
        })
        ThunderEngine.on('onRecvMediaExtraInfo', (ret) => {
            this.addCallBackInfo(1, 'onRecvMediaExtraInfo ' + JSON.stringify(ret))
        })

    }

    clickApiItem(apiSelectedTab) {
        if (this.state.apiSelectedTab === apiSelectedTab) {
            return
        }
        this.setState({
            apiSelectedTab: apiSelectedTab
        })
    }

    clickCallbackItem(callbackSelectedTab) {
        if (this.state.callbackSelectedTab === callbackSelectedTab) {
            return
        }
        this.setState({
            callbackSelectedTab: callbackSelectedTab
        })
    }

    onLongPressCallback() {
        this.setState({
            zoomInCallback: !this.state.zoomInCallback
        })
    }


    onPressZoomInVideo(uid) {
        this.setState({
            zoomInVideo: uid
        })
    }

    videoView(show) {
        if (!show) {
            return <View style={{height: videoHeight}}/>
        }

        let remoteViews = this.state.remoteUser.map((item, i) => {
            return <View style={styles.video}>
                <TouchableOpacity onPress={() => {
                    this.onPressZoomInVideo(item.uid)
                }}><Text style={styles.text_red}>全屏</Text></TouchableOpacity>
                <ThunderRemoteVideoView setRemoteVideoCanvas={{'renderMode': item.mode, 'uid': item.uid}}
                                        style={{height: videoHeight - redTextHeight, backgroundColor: "#000000"}}/>
            </View>
        })
        while (remoteViews.length < 4) {
            remoteViews.push(null)
        }
        return <View style={styles.videos}>
            <View style={styles.video}>
                {this.state.localUser == null ? <View></View> :
                    <View style={styles.video}>
                        <TouchableOpacity onPress={() => {
                            this.onPressZoomInVideo(this.state.localUser.uid)
                        }}><Text style={styles.text_red}>全屏</Text></TouchableOpacity>
                        <ThunderLocalVideoView setLocalVideoCanvas={{
                            'renderMode': this.state.localUser.mode,
                            'uid': this.state.localUser.uid
                        }} style={{height: videoHeight - redTextHeight, backgroundColor: "#000000"}}/>
                    </View>
                }
            </View>
            {remoteViews.map((item, i) => {
                return item == null ? <View style={i % 2 == 0 ? styles.video2 : styles.video}></View> : item
            })}
        </View>

    }

    apiTopView() {
        return <View style={styles.api_top}>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(1)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 1 ? styles.ta_choose : styles.ta}>频道</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(2)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 2 ? styles.ta_choose : styles.ta}>声音</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(3)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 3 ? styles.ta_choose : styles.ta}>伴奏</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(4)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 4 ? styles.ta_choose : styles.ta}>音调</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(5)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 5 ? styles.ta_choose : styles.ta}>K歌</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(6)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 6 ? styles.ta_choose : styles.ta}>视频</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickApiItem(7)
            }} style={styles.f1}>
                <Text style={this.state.apiSelectedTab === 7 ? styles.ta_choose : styles.ta}>连麦</Text>
            </TouchableOpacity>
        </View>
    }

    createNormalApiContent(desc, api, pressCallBtn, total, failure, ret, addViews) {
        return <View>
            <View style={styles.fr}>
                <TouchableOpacity onPress={pressCallBtn} style={styles.call_btn}>
                    <Text>CALL</Text>
                </TouchableOpacity>
                <View style={styles.fl}>
                    <View style={{flexDirection: "row", width: width - 30}}>
                        <Text style={styles.blue_text}>{desc}:</Text>
                        <Text style={styles.gray_text}>{api}</Text>
                    </View>
                    <View style={styles.fr}>
                        <View style={styles.f1}>
                            <Text style={styles.gray_text}>Total:{total}</Text>
                        </View>
                        <View style={styles.f1}>
                            <Text style={styles.gray_text}>Failure:{failure}</Text>
                        </View>
                        <View style={styles.f1}>
                            <Text style={styles.gray_text}>Ret:{ret}</Text>
                        </View>
                    </View>
                </View>
            </View>
            {addViews != null ? addViews.map((item, i) => item) : <View></View>}
            <View style={styles.line}></View>
        </View>
    }

    createCheckBox(desc, isSelected, onValueChange) {
        return <View style={styles.fr}>
            <Text>{desc}</Text>
            <CheckBox
                isChecked={isSelected}
                onClick={onValueChange}
            />
        </View>
    }

    createInput(desc, defaultText, onChangeText, isNumeric = false) {
        return <View style={styles.fr}>
            <Text>{desc}</Text>
            <TextInput
                defaultValue={defaultText}
                keyboardType={isNumeric ? "numeric" : "default"}
                style={{height: 40, width: 100, borderColor: 'gray', borderWidth: 1}}
                onChangeText={text => onChangeText(text)}
                returnKeyType="done"
            />
        </View>
    }

    createBtn(text, onPress) {
        return <TouchableOpacity onPress={onPress} style={styles.call_btn}>
            <Text>{text}</Text>
        </TouchableOpacity>
    }

    createPicker(listText, listValue, selectedValue, onValueChange) {
        if (Platform.OS === 'android') {
            return <Picker
                style={{width: 150}}
                selectedValue={selectedValue}
                mode="dropdown"
                onValueChange={(item, i) => {
                    onValueChange(item)
                }}>
                {
                    listText.map((item, i) => <Picker.Item label={item} value={listValue[i]}/>)
                }
            </Picker>
        }

        let listData = []
        listText.map((item, i) => {
            listData.push({label: item, value: listValue[i]})
        })

        return <View style={{marginBottom: 5}}>
            <RadioButton
                outerWidth={30}
                innerWidth={20}
                borderWidth={1}
                selectValue={selectedValue}
                data={listData}
                color={"steelblue"}
                onPress={(i) => {
                    onValueChange(i)
                }}
                wrapperStyle={{padding: 3}}
            />
            <View style={{width: 40, height: 1, backgroundColor: "steelblue"}}/>
        </View>

    }

    createText(textDesc, text) {
        return <Text>{textDesc}:{text}</Text>
    }

    addCallBackInfo(index, info) {
        if (index == 1) {
            console.log(this.state.callbackInfo1.length)
            if (this.state.callbackInfo1.length >= 7000) {
                this.setState({callbackInfo1: ""})
            }
            this.setState({callbackInfo1: logPrev1 + '- ' + info + '\n\n' + this.state.callbackInfo1})
            logPrev1++
        } else if (index == 2) {
            this.setState({callbackInfo2: logPrev2 + '- ' + info + '\n\n' + this.state.callbackInfo2})
            logPrev2++
        } else if (index == 3) {
            this.setState({callbackInfo3: logPrev3 + '- ' + info + '\n\n' + this.state.callbackInfo3})
            logPrev3++
        } else if (index == 4) {
            this.setState({callbackInfo4: logPrev4 + '- ' + info + '\n\n' + this.state.callbackInfo4})
            logPrev4++
        } else {
            if (this.state.callbackInfo5.length >= 7000) {
                this.setState({callbackInfo5: ""})
            }
            this.setState({callbackInfo5: logPrev5 + '- ' + info + '\n' + this.state.callbackInfo5})
            logPrev5++
        }
    }

    isSuccess(ret) {
        if (ret === '未初始化') {
            return false
        }
        return ret === 0 || ret === '0'
    }

    apiContentView() {
        if (this.state.apiSelectedTab === 1) {
            return <ScrollView style={{height: apiContentViewHeight}}>
                {this.createNormalApiContent('初始化SDK', 'createEngine',
                    () => {
                        this.setState({createEngineTotal: this.state.createEngineTotal + 1})
                        ThunderEngine.createEngine(Config.APPID, 0, (ret) => {
                            this.addCallBackInfo(2, 'createEngine->' + ret)
                            if (ret === '已经初始化') {
                                this.setState({
                                    createEngineF: this.state.createEngineF + 1,
                                    createEngineRet: ret
                                })
                            } else {
                                this.setState({createEngineRet: ret})
                                FeedbackUtils.getLogPath((path) => {
                                    ThunderEngine.setLogFilePath(path)
                                })
                            }
                        })
                    }, this.state.createEngineTotal, this.state.createEngineF, this.state.createEngineRet)}
                {this.createNormalApiContent('卸载SDK', 'destroyEngine',
                    () => {
                        this.setState({
                            localUser: null,
                            remoteUser: []
                        })
                        remoteVideoList = []
                        setTimeout(() => {
                            ThunderEngine.destroyEngine((ret) => {
                                this.addCallBackInfo(2, 'destroyEngine->' + ret)
                                if (ret === '未初始化') {
                                    this.setState({
                                        destroyEngineTotal: this.state.destroyEngineTotal + 1,
                                        destroyEngineF: this.state.destroyEngineF + 1,
                                        destroyEngineRet: ret,
                                    })
                                } else {
                                    this.setState({
                                        destroyEngineTotal: this.state.destroyEngineTotal + 1,
                                        destroyEngineRet: ret,
                                    })
                                }
                            })
                        }, 1)
                    }, this.state.destroyEngineTotal, this.state.destroyEngineF, this.state.destroyEngineRet)}
                {this.createNormalApiContent('设置区域', 'setArea',
                    () => {
                        this.setState({setAreaTotal: this.state.setAreaTotal + 1})
                        ThunderEngine.setArea(this.state.areaType, (ret) => {
                            this.addCallBackInfo(2, 'setArea areaType(' + this.state.areaType + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setAreaF: this.state.setAreaF + 1,
                                    setAreaRet: ret
                                })
                            } else {
                                this.setState({setAreaRet: ret})
                            }
                        })
                    }, this.state.setAreaTotal, this.state.setAreaF, this.state.setAreaRet,
                    [this.createPicker(['国内0', '国外1'], [0, 1], this.state.areaType, (item) => {
                        this.setState({areaType: item})
                    })])}
                {this.createNormalApiContent('设置远端视图显示模式', 'setRemotePlayType',
                    () => {
                        this.setState({setRemotePlayTypeTotal: this.state.setRemotePlayTypeTotal + 1})
                        ThunderEngine.setRemotePlayType(this.state.remotePlayType, (ret) => {
                            this.addCallBackInfo(2, 'setRemotePlayType remotePlayType(' + this.state.remotePlayType + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setRemotePlayTypeF: this.state.setRemotePlayTypeF + 1,
                                    remotePlayTypeRet: ret
                                })
                            } else {
                                this.setState({remotePlayTypeRet: ret})
                            }
                        })
                    }, this.state.setRemotePlayTypeTotal, this.state.setRemotePlayTypeF, this.state.remotePlayTypeRet,
                    [this.createPicker(['0', '1'], [0, 1], this.state.remotePlayType, (item) => {
                        this.setState({remotePlayType: item})
                    })])}
                {this.createNormalApiContent('进频道', 'joinRoom',
                    () => {
                        this.setState({joinRoomTotal: this.state.joinRoomTotal + 1})
                        ThunderEngine.joinRoom(Config.uid, Config.channelId, "", (ret) => {
                            this.addCallBackInfo(2, 'joinRoom uid(' + Config.uid + ') roomName(' + Config.channelId + ') token(' + "" + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    joinRoomF: this.state.joinRoomF + 1,
                                    joinRoomRet: ret
                                })
                            } else {
                                this.setState({joinRoomRet: ret})
                            }
                        })
                    }, this.state.joinRoomTotal, this.state.joinRoomF, this.state.joinRoomRet)}
                {this.createNormalApiContent('退频道', 'leaveRoom',
                    () => {
                        this.setState({leaveRoomTotal: this.state.leaveRoomTotal + 1})
                        ThunderEngine.leaveRoom((ret) => {
                            this.addCallBackInfo(2, 'leaveRoom->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    leaveRoomF: this.state.leaveRoomF + 1,
                                    leaveRoomRet: ret
                                })
                            } else {
                                this.setState({leaveRoomRet: ret, remoteUser: []})
                                remoteVideoList = []
                            }
                        })
                    }, this.state.leaveRoomTotal, this.state.leaveRoomF, this.state.leaveRoomRet)}
                {this.createNormalApiContent('设置sdk媒体模式', 'setMediaMode',
                    () => {
                        this.setState({setMediaModeTotal: this.state.setMediaModeTotal + 1})
                        ThunderEngine.setMediaMode(this.state.mediaMode, (ret) => {
                            this.addCallBackInfo(2, 'setMediaMode mode(' + this.state.mediaMode + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setMediaModeF: this.state.setMediaModeF + 1,
                                    setMediaModeRet: ret
                                })
                            } else {
                                this.setState({setMediaModeRet: ret})
                            }
                        })
                    }, this.state.setMediaModeTotal, this.state.setMediaModeF, this.state.setMediaModeRet,
                    [this.createPicker(['默认', '音视频模式', '纯音频模式'], [0, 1, 2], this.state.mediaMode, (item) => {
                        this.setState({mediaMode: item})
                    })])}
                {this.createNormalApiContent('设置房间场景模式', 'setRoomMode',
                    () => {
                        this.setState({setRoomModeTotal: this.state.setRoomModeTotal + 1})
                        ThunderEngine.setRoomMode(this.state.roomMode, (ret) => {
                            this.addCallBackInfo(2, 'setRoomMode mode(' + this.state.roomMode + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setRoomModeF: this.state.setRoomModeF + 1,
                                    setRoomModeRet: ret
                                })
                            } else {
                                this.setState({setRoomModeRet: ret})
                            }
                        })
                    }, this.state.setRoomModeTotal, this.state.setRoomModeF, this.state.setRoomModeRet,
                    [this.createPicker(['直播模式', '通信模式', '游戏模式', '语音房模式', '会议模式'], [0, 1, 3, 4, 5], this.state.roomMode, (item) => {
                        this.setState({roomMode: item})
                    })])}
                {this.createNormalApiContent('设置音频属性', 'setAudioConfig',
                    () => {
                        this.setState({setAudioConfigTotal: this.state.setAudioConfigTotal + 1})
                        ThunderEngine.setAudioConfig(this.state.profile, this.state.commutMode, this.state.scenarioMode, (ret) => {
                            this.addCallBackInfo(2, 'setAudioConfig profile(' + this.state.profile + ') commutMode(' + this.state.commutMode + ') scenarioMode(' + this.state.scenarioMode + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setAudioConfigF: this.state.setAudioConfigF + 1,
                                    setAudioConfigRet: ret
                                })
                            } else {
                                this.setState({setAudioConfigRet: ret})
                            }
                        })
                    }, this.state.setAudioConfigTotal, this.state.setAudioConfigF, this.state.setAudioConfigRet,
                    [this.createPicker(['默认:0', 'SPEECH:1', 'MUSIC延时高:2', 'MUSIC延时低:3', '高音质:4', '超高音质:5'], [0, 1, 2, 3, 4, 5], this.state.profile, (item) => {
                        this.setState({profile: item})
                    }),
                        this.createPicker(['默认交互模式', '强交互模式', '弱交互模式'], [0, 1, 2], this.state.commutMode, (item) => {
                            this.setState({commutMode: item})
                        }),
                        this.createPicker(['默认情景模式', '流畅情景模式', '音质情景模式'], [0, 1, 2], this.state.scenarioMode, (item) => {
                            this.setState({scenarioMode: item})
                        })])}
                {this.createNormalApiContent('获取网络连接状态', 'getConnectionStatus',
                    () => {
                        this.setState({getConnectionStatusTotal: this.state.getConnectionStatusTotal + 1})
                        ThunderEngine.getConnectionStatus((ret) => {
                            this.addCallBackInfo(2, 'getConnectionStatus->' + ret)
                            let getConnectionStatusRetText = ""
                            if (ret == 0) {
                                getConnectionStatusRetText = "连接中"
                            } else if (ret == 1) {
                                getConnectionStatusRetText = "连接成功"
                            } else {
                                getConnectionStatusRetText = "连接断开"
                            }
                            this.setState({
                                getConnectionStatusRet: ret,
                                getConnectionStatusRetText: getConnectionStatusRetText
                            })
                        })
                    }, this.state.getConnectionStatusTotal, 0, this.state.getConnectionStatusRet, [this.createText("连接状态", this.state.getConnectionStatusRetText)])}
            </ScrollView>
        } else if (this.state.apiSelectedTab === 2) {
            return <ScrollView style={{height: apiContentViewHeight}}>
                {this.createNormalApiContent('打开扬声器', 'enableLoudspeaker',
                    () => {
                        this.setState({enableLoudspeakerTotal: this.state.enableLoudspeakerTotal + 1})
                        ThunderEngine.enableLoudspeaker(this.state.enableLoudspeaker, (ret) => {
                            this.addCallBackInfo(2, 'enableLoudspeaker enable(' + this.state.enableLoudspeaker + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    enableLoudspeakerF: this.state.enableLoudspeakerF + 1,
                                    enableLoudspeakerRet: ret
                                })
                            } else {
                                this.setState({enableLoudspeakerRet: ret})
                            }
                        })
                    }, this.state.enableLoudspeakerTotal, this.state.enableLoudspeakerF, this.state.enableLoudspeakerRet,
                    [this.createCheckBox('扬声器播放', this.state.enableLoudspeaker, () => {
                        this.setState({enableLoudspeaker: !this.state.enableLoudspeaker})
                    })])}
                {this.createNormalApiContent('是否打开扬声器', 'isLoudspeakerEnabled',
                    () => {
                        this.setState({isLoudspeakerEnabledTotal: this.state.isLoudspeakerEnabledTotal + 1})
                        ThunderEngine.isLoudspeakerEnabled((ret) => {
                            this.addCallBackInfo(2, 'isLoudspeakerEnabled->' + ret)
                            if (ret) {
                                this.setState({isLoudspeakerEnabledRet: 1})
                            } else {
                                this.setState({isLoudspeakerEnabledRet: 0})
                            }

                        })
                    }, this.state.isLoudspeakerEnabledTotal, 0, this.state.isLoudspeakerEnabledRet)}
                {this.createNormalApiContent('打开播放回调', 'setAudioVolumeIndication',
                    () => {
                        this.setState({setAudioVolumeIndicationTotal: this.state.setAudioVolumeIndicationTotal + 1})
                        ThunderEngine.setAudioVolumeIndication(500, 50, 50, 0, (ret) => {
                            this.addCallBackInfo(2, 'setAudioVolumeIndication interval(' + 500 + ') moreThanThd(' + 50 + ') lessThanThd(' + 50 + ') smooth(' + 0 + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setAudioVolumeIndicationF: this.state.setAudioVolumeIndicationF + 1,
                                    setAudioVolumeIndicationRet: ret
                                })
                            } else {
                                this.setState({setAudioVolumeIndicationRet: ret})
                            }
                        })
                    }, this.state.setAudioVolumeIndicationTotal, this.state.setAudioVolumeIndicationF, this.state.setAudioVolumeIndicationRet)}
                {this.createNormalApiContent('打开采集回调', 'enableCaptureVolumeIndication',
                    () => {
                        this.setState({enableCaptureVolumeIndicationTotal: this.state.enableCaptureVolumeIndicationTotal + 1})
                        ThunderEngine.enableCaptureVolumeIndication(500, 50, 50, 0, (ret) => {
                            this.addCallBackInfo('2', 'enableCaptureVolumeIndication interval(' + 500 + ') moreThanThd(' + 50 + ') lessThanThd(' + 50 + ') smooth(' + 0 + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    enableCaptureVolumeIndicationF: this.state.enableCaptureVolumeIndicationF + 1,
                                    enableCaptureVolumeIndicationRet: ret
                                })
                            } else {
                                this.setState({enableCaptureVolumeIndicationRet: ret})
                            }
                        })
                    }, this.state.enableCaptureVolumeIndicationTotal, this.state.enableCaptureVolumeIndicationF, this.state.enableCaptureVolumeIndicationRet)}
                {this.createNormalApiContent('是否静音自己', 'stopLocalAudioStream',
                    () => {
                        this.setState({stopLocalAudioStreamTotal: this.state.stopLocalAudioStreamTotal + 1})
                        ThunderEngine.stopLocalAudioStream(this.state.stopLocalAudioStream, (ret) => {
                            this.addCallBackInfo('2', 'stopLocalAudioStream stop(' + this.state.stopLocalAudioStream + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopLocalAudioStreamF: this.state.stopLocalAudioStreamF + 1,
                                    stopLocalAudioStreamRet: ret
                                })
                            } else {
                                this.setState({stopLocalAudioStreamRet: ret})
                            }
                        })
                    }, this.state.stopLocalAudioStreamTotal, this.state.stopLocalAudioStreamF, this.state.stopLocalAudioStreamRet,
                    [this.createCheckBox('静音', this.state.stopLocalAudioStream, () => {
                        this.setState({stopLocalAudioStream: !this.state.stopLocalAudioStream})
                    })])}
                {this.createNormalApiContent('静音所有播放', 'stopAllRemoteAudioStreams',
                    () => {
                        this.setState({stopAllRemoteAudioStreamsTotal: this.state.stopAllRemoteAudioStreamsTotal + 1})
                        ThunderEngine.stopAllRemoteAudioStreams(this.state.stopAllRemoteAudioStreams, (ret) => {
                            this.addCallBackInfo('2', 'stopAllRemoteAudioStreams stop(' + this.state.stopAllRemoteAudioStreams + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopAllRemoteAudioStreamsF: this.state.stopAllRemoteAudioStreamsF + 1,
                                    stopAllRemoteAudioStreamsRet: ret
                                })
                            } else {
                                this.setState({stopAllRemoteAudioStreamsRet: ret})
                            }
                        })
                    }, this.state.stopAllRemoteAudioStreamsTotal, this.state.stopAllRemoteAudioStreamsF, this.state.stopAllRemoteAudioStreamsRet,
                    [this.createCheckBox('静音', this.state.stopAllRemoteAudioStreams, () => {
                        this.setState({stopAllRemoteAudioStreams: !this.state.stopAllRemoteAudioStreams})
                    })])}
                {this.createNormalApiContent('静音某个用户', 'stopRemoteAudioStream',
                    () => {
                        this.setState({stopRemoteAudioStreamTotal: this.state.stopRemoteAudioStreamTotal + 1})
                        ThunderEngine.stopRemoteAudioStream(this.state.stopRemoteAudioStreamUid, this.state.stopRemoteAudioStream, (ret) => {
                            this.addCallBackInfo('2', 'stopRemoteAudioStream uid(' + this.state.stopRemoteAudioStreamUid + ') stop(' + this.state.stopRemoteAudioStream + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopRemoteAudioStreamF: this.state.stopRemoteAudioStreamF + 1,
                                    stopRemoteAudioStreamRet: ret
                                })
                            } else {
                                this.setState({stopRemoteAudioStreamRet: ret})
                            }
                        })
                    }, this.state.stopRemoteAudioStreamTotal, this.state.stopRemoteAudioStreamF, this.state.stopRemoteAudioStreamRet,
                    [this.createInput('uid', this.state.stopRemoteAudioStreamUid, (text) => {
                        this.setState({stopRemoteAudioStreamUid: text})
                    }, false),
                        this.createCheckBox('静音', this.state.stopRemoteAudioStream, () => {
                            this.setState({stopRemoteAudioStream: !this.state.stopRemoteAudioStream})
                        })])}
                {this.createNormalApiContent('麦克风音量', 'setMicVolume',
                    () => {
                        this.setState({setMicVolumeTotal: this.state.setMicVolumeTotal + 1})
                        ThunderEngine.setMicVolume(Number(this.state.micVolume), (ret) => {
                            this.addCallBackInfo('2', 'setMicVolume volume(' + this.state.micVolume + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setMicVolumeF: this.state.setMicVolumeF + 1,
                                    setMicVolumeRet: ret
                                })
                            } else {
                                this.setState({setMicVolumeRet: ret})
                            }
                        })
                    }, this.state.setMicVolumeTotal, this.state.setMicVolumeF, this.state.setMicVolumeRet,
                    [this.createInput('音量', this.state.micVolume, (text) => {
                        this.setState({micVolume: text})
                    }, true)])}
                {this.createNormalApiContent('扬声器音量', 'setLoudSpeakerVolume',
                    () => {
                        this.setState({setLoudSpeakerVolumeTotal: this.state.setLoudSpeakerVolumeTotal + 1})
                        ThunderEngine.setLoudSpeakerVolume(Number(this.state.loudSpeakerVolume), (ret) => {
                            this.addCallBackInfo('2', 'setLoudSpeakerVolume volume(' + this.state.loudSpeakerVolume + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setLoudSpeakerVolumeF: this.state.setLoudSpeakerVolumeF + 1,
                                    setLoudSpeakerVolumeTotalRet: ret
                                })
                            } else {
                                this.setState({setLoudSpeakerVolumeTotalRet: ret})
                            }
                        })
                    }, this.state.setLoudSpeakerVolumeTotal, this.state.setLoudSpeakerVolumeF, this.state.setLoudSpeakerVolumeTotalRet,
                    [this.createInput('音量', this.state.loudSpeakerVolume, (text) => {
                        this.setState({loudSpeakerVolume: text})
                    }, true)])}
            </ScrollView>
        } else if (this.state.apiSelectedTab === 3) {
            return <ScrollView style={{height: apiContentViewHeight}}/>
        } else if (this.state.apiSelectedTab === 4) {
            return <ScrollView style={{height: apiContentViewHeight}}/>
        } else if (this.state.apiSelectedTab === 5) {
            return <ScrollView style={{height: apiContentViewHeight}}>
                {this.createNormalApiContent('发送媒体次要信息', 'sendMediaExtraInfo',
                    () => {
                        this.setState({sendMediaExtraInfoTotal: this.state.sendMediaExtraInfoTotal + 1})
                        ThunderEngine.sendMediaExtraInfo(this.state.mediaExtraInfo, (ret) => {
                            this.addCallBackInfo('2', 'sendMediaExtraInfo info(' + this.state.mediaExtraInfo + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    sendMediaExtraInfoF: this.state.sendMediaExtraInfoF + 1,
                                    sendMediaExtraInfoRet: ret
                                })
                            } else {
                                this.setState({sendMediaExtraInfoRet: ret})
                            }
                        })
                    }, this.state.sendMediaExtraInfoTotal, this.state.sendMediaExtraInfoF, this.state.sendMediaExtraInfoRet,
                    [this.createInput('次要信息', this.state.mediaExtraInfo, (text) => {
                        this.setState({mediaExtraInfo: text})
                    }, false)])}
                {this.createNormalApiContent('次要信息回调', 'setMediaExtraInfoCallback',
                    () => {
                        this.setState({setMediaExtraInfoCallbackTotal: this.state.setMediaExtraInfoCallbackTotal + 1})
                        ThunderEngine.setMediaExtraInfoCallback(this.state.setMediaExtraInfoCallbackEnable, (ret) => {
                            this.addCallBackInfo('2', 'sendMediaExtraInfo info(' + this.state.mediaExtraInfo + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setMediaExtraInfoCallbackF: this.state.setMediaExtraInfoCallbackF + 1,
                                    setMediaExtraInfoCallbackRet: ret
                                })
                            } else {
                                this.setState({setMediaExtraInfoCallbackRet: ret})
                            }
                        })
                    }, this.state.setMediaExtraInfoCallbackTotal, this.state.setMediaExtraInfoCallbackF, this.state.setMediaExtraInfoCallbackRet,
                    [this.createCheckBox('开启', this.state.setMediaExtraInfoCallbackEnable, () => {
                        this.setState({setMediaExtraInfoCallbackEnable: !this.state.setMediaExtraInfoCallbackEnable})
                    })])}
            </ScrollView>
        } else if (this.state.apiSelectedTab === 6) {
            return <ScrollView style={{height: apiContentViewHeight}}>
                {this.createNormalApiContent('设置视频编码配置', 'setVideoEncoderConfig',
                    () => {
                        this.setState({setVideoEncoderConfigTotal: this.state.setVideoEncoderConfigTotal + 1})
                        ThunderEngine.setVideoEncoderConfig(this.state.publishPlayType, this.state.publishVideoMode, (ret) => {
                            this.addCallBackInfo('2', 'setVideoEncoderConfig playType(' + this.state.publishPlayType + ') mode(' + this.state.publishVideoMode + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setVideoEncoderConfigF: this.state.setVideoEncoderConfigF + 1,
                                    setVideoEncoderConfigRet: ret
                                })
                            } else {
                                this.setState({setVideoEncoderConfigRet: ret})
                            }
                        })
                    }, this.state.setVideoEncoderConfigTotal, this.state.setVideoEncoderConfigF, this.state.setVideoEncoderConfigRet,
                    [this.createPicker(['单人开播', '视频连麦开播', '录屏开播', '视频多人连麦开播'], [0, 1, 2, 3], this.state.publishPlayType, (item) => {
                        this.setState({publishPlayType: item})
                    }),
                        this.createPicker(['自动', '标清', '高清', '超清', '蓝光', '蓝光2'], [-1, 1, 2, 3, 4, 5], this.state.publishVideoMode, (item, i) => {
                            this.setState({publishVideoMode: item})
                        })])}
                {this.createNormalApiContent('获取视频编码参数', 'getVideoEncoderParam',
                    () => {
                        this.setState({getVideoEncoderParamTotal: this.state.getVideoEncoderParamTotal + 1})
                        ThunderEngine.getVideoEncoderParam(this.state.getPublishPlayType, this.state.getPublishVideoMode, (ret) => {
                            if (ret === '未初始化') {
                                this.setState({
                                    getVideoEncoderParamF: this.state.getVideoEncoderParamF + 1,
                                    getVideoEncoderParamRet: '未初始化'
                                })
                            } else {
                                this.setState({getVideoEncoderParamRet: '0'})
                            }
                            this.addCallBackInfo('2', 'getVideoEncoderParam playType(' + this.state.getPublishPlayType + ') mode(' + this.state.getPublishVideoMode + ')->' + JSON.stringify(ret))
                        })
                    }, this.state.getVideoEncoderParamTotal, this.state.getVideoEncoderParamF, this.state.getVideoEncoderParamRet,
                    [this.createPicker(['单人开播', '视频连麦开播', '录屏开播', '视频多人连麦开播'], [0, 1, 2, 3], this.state.getPublishPlayType, (item) => {
                        this.setState({getPublishPlayType: item})
                    }),
                        this.createPicker(['自动', '标清', '高清', '超清', '蓝光', '蓝光2'], [-1, 1, 2, 3, 4, 5], this.state.getPublishVideoMode, (item, i) => {
                            this.setState({getPublishVideoMode: item})
                        })])}
                {this.createNormalApiContent('本地渲染视图', 'setLocalVideoCanvas',
                    () => {
                        if (ThunderEngine.hasCreatedEngine()) {
                            this.addCallBackInfo('2', 'setLocalVideoCanvas uid(' + Config.uid + ') mode(' + this.state.localVideoCanvasMode + ')->0')
                            localVideoCanvasModeUse = this.state.localVideoCanvasMode
                            this.setState({
                                setLocalVideoCanvasRet: '0',
                                setLocalVideoCanvasTotal: this.state.setLocalVideoCanvasTotal + 1,
                                localUser: {
                                    'mode': localVideoCanvasModeUse,
                                    'uid': Config.uid,
                                }
                            })
                        } else {
                            this.addCallBackInfo('2', 'setLocalVideoCanvas->未初始化')
                            this.setState({
                                setLocalVideoCanvasTotal: this.state.setLocalVideoCanvasTotal + 1,
                                setLocalVideoCanvasF: this.state.setLocalVideoCanvasF + 1,
                                setLocalVideoCanvasRet: '未初始化'
                            })
                        }
                    }, this.state.setLocalVideoCanvasTotal, this.state.setLocalVideoCanvasF, this.state.setLocalVideoCanvasRet,
                    [this.createPicker(['拉伸', '自适应', '裁剪'], [0, 1, 2], this.state.localVideoCanvasMode, (item) => {
                        this.setState({localVideoCanvasMode: item})
                    })])}
                {this.createNormalApiContent('远端渲染视图', 'setRemoteVideoCanvas',
                    () => {
                        if (ThunderEngine.hasCreatedEngine()) {
                            let remoteUser = this.state.remoteUser
                            let add = true
                            let update = false
                            let index = 0

                            remoteUser.map((item, i) => {
                                if (item.uid == this.state.remoteVideoCanvasUid) {
                                    add = false
                                    if (item.mode != this.state.remoteVideoCanvasMode) {
                                        update = true
                                        index = i
                                    }
                                }
                            })

                            if (add && remoteUser.length >= 4) {
                                this.setState(
                                    {
                                        setRemoteVideoCanvasRet: '人数超过限制',
                                        setRemoteVideoCanvasTotal: this.state.setRemoteVideoCanvasTotal + 1,
                                    })
                                return
                            }
                            this.addCallBackInfo('2',
                                'setRemoteVideoCanvas uid(' + this.state.remoteVideoCanvasUid + ') mode(' + this.state.remoteVideoCanvasMode + ')->0')

                            if (add) {
                                remoteUser.push({
                                    'uid': this.state.remoteVideoCanvasUid,
                                    'mode': this.state.remoteVideoCanvasMode,
                                })
                                remoteVideoList.push({
                                    'uid': this.state.remoteVideoCanvasUid,
                                    'show': true
                                })
                            } else if (update) {
                                let newItem = {
                                    'uid': this.state.remoteVideoCanvasUid,
                                    'mode': this.state.remoteVideoCanvasMode,
                                }
                                remoteUser.splice(index, 1, newItem)
                            }
                            this.setState(
                                {
                                    setRemoteVideoCanvasRet: '0',
                                    setRemoteVideoCanvasTotal: this.state.setRemoteVideoCanvasTotal + 1,
                                    remoteUser: remoteUser
                                })
                        } else {
                            this.addCallBackInfo('2', 'setRemoteVideoCanvas->未初始化')
                            this.setState({
                                setRemoteVideoCanvasRet: '未初始化',
                                setRemoteVideoCanvasTotal: this.state.setRemoteVideoCanvasTotal + 1,
                                setRemoteVideoCanvasF: this.state.setRemoteVideoCanvasF + 1,
                            })
                        }
                    }, this.state.setRemoteVideoCanvasTotal, this.state.setRemoteVideoCanvasF, this.state.setRemoteVideoCanvasRet,
                    [this.createInput('uid', this.state.remoteVideoCanvasUid, (text) => {
                        this.setState({remoteVideoCanvasUid: text})
                    }, false),
                        this.createPicker(['拉伸', '自适应', '裁剪', '原画'], [0, 1, 2, 3], this.state.remoteVideoCanvasMode, (item) => {
                            this.setState({remoteVideoCanvasMode: item})
                        })])}
                {this.createNormalApiContent('本地视图拉伸模式', 'setLocalCanvasScaleMode',
                    () => {
                        this.setState({setLocalCanvasScaleModeTotal: this.state.setLocalCanvasScaleModeTotal + 1})
                        ThunderEngine.setLocalCanvasScaleMode(this.state.localCanvasScaleMode, (ret) => {
                            this.addCallBackInfo('2', 'setLocalCanvasScaleMode mode(' + this.state.localCanvasScaleMode + ')->' + ret)
                            localVideoCanvasModeUse = this.state.localCanvasScaleMode
                            if (ret === '未初始化') {
                                this.setState({
                                    setLocalCanvasScaleModeF: this.state.setLocalCanvasScaleModeF + 1,
                                    setLocalCanvasScaleModeRet: ret
                                })
                                return
                            }
                            if (this.state.localUser != null) {
                                this.setState({
                                    localUser: {
                                        'mode': localVideoCanvasModeUse,
                                        'uid': Config.uid,
                                    },
                                    setLocalCanvasScaleModeRet: ret
                                })
                            } else {
                                this.setState({setLocalCanvasScaleModeRet: ret})
                            }
                        })
                    }, this.state.setLocalCanvasScaleModeTotal, this.state.setLocalCanvasScaleModeF, this.state.setLocalCanvasScaleModeRet,
                    [this.createPicker(['拉伸', '自适应', '裁剪'], [0, 1, 2], this.state.localCanvasScaleMode, (item) => {
                        this.setState({localCanvasScaleMode: item})
                    })])}
                {this.createNormalApiContent('远端视图拉伸模式', 'setRemoteCanvasScaleMode',
                    () => {
                        this.setState({setRemoteCanvasScaleModeTotal: this.state.setRemoteCanvasScaleModeTotal + 1})
                        ThunderEngine.setRemoteCanvasScaleMode(this.state.remoteVideoCanvasUid, this.state.remoteCanvasScaleMode, (ret) => {
                            this.addCallBackInfo('2', 'setRemoteCanvasScaleMode uid(' + this.state.remoteVideoCanvasUid + ') mode(' + this.state.remoteCanvasScaleMode + ')->' + ret)
                            if (ret === '未初始化') {
                                this.setState({
                                    setRemoteCanvasScaleModeF: this.state.setRemoteCanvasScaleModeF + 1,
                                    setRemoteCanvasScaleModeRet: ret
                                })
                                return
                            }
                            let it = null
                            let index = 0
                            let remoteUser = this.state.remoteUser
                            remoteUser.map((item, i) => {
                                if (item.uid === this.state.remoteVideoCanvasUid) {
                                    index = i
                                    it = item
                                }
                            })

                            if (it != null) {
                                let newItem = {
                                    'uid': this.state.remoteVideoCanvasUid,
                                    'mode': this.state.remoteCanvasScaleMode
                                }
                                remoteUser.splice(index, 1, newItem)
                                this.setState({remoteUser: remoteUser, setRemoteCanvasScaleModeRet: ret})
                            } else {
                                this.setState({setRemoteCanvasScaleModeRet: ret})
                            }
                        })
                    }, this.state.setRemoteCanvasScaleModeTotal, this.state.setRemoteCanvasScaleModeF, this.state.setRemoteCanvasScaleModeRet,
                    [this.createInput('uid', this.state.remoteVideoCanvasUid, (text) => {
                        this.setState({remoteVideoCanvasUid: text})
                    }, false),
                        this.createPicker(['拉伸', '自适应', '裁剪', '原画'], [0, 1, 2, 3], this.state.remoteCanvasScaleMode, (item) => {
                            this.setState({remoteCanvasScaleMode: item})
                        })])}
                {this.createNormalApiContent('开/关本地视频采集', 'enableLocalVideoCapture',
                    () => {
                        this.setState({enableLocalVideoCaptureTotal: this.state.enableLocalVideoCaptureTotal + 1})
                        ThunderEngine.enableLocalVideoCapture(this.state.enableLocalVideoCapture, (ret) => {
                            this.addCallBackInfo('2', 'enableLocalVideoCapture enable(' + this.state.enableLocalVideoCapture + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    enableLocalVideoCaptureF: this.state.enableLocalVideoCaptureF + 1,
                                    enableLocalVideoCaptureRet: ret
                                })
                            } else {
                                this.setState({enableLocalVideoCaptureRet: ret})
                            }
                        })
                    }, this.state.enableLocalVideoCaptureTotal, this.state.enableLocalVideoCaptureF, this.state.enableLocalVideoCaptureRet,
                    [this.createCheckBox('关闭', !this.state.enableLocalVideoCapture, () => {
                        this.setState({enableLocalVideoCapture: !this.state.enableLocalVideoCapture})
                    })])}
                {this.createNormalApiContent('开启预览', 'startVideoPreview',
                    () => {
                        this.setState({startVideoPreviewTotal: this.state.startVideoPreviewTotal + 1})
                        ThunderEngine.startVideoPreview((ret) => {
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    startVideoPreviewF: this.state.startVideoPreviewF + 1,
                                    startVideoPreviewRet: ret
                                })
                                return
                            }
                            this.addCallBackInfo('2', 'startVideoPreview->' + ret)
                            if (this.state.localUser != null) {
                                this.setState({
                                    localUser: null,
                                    startVideoPreviewRet: ret
                                })
                                this.setState({
                                    localUser: {
                                        'mode': localVideoCanvasModeUse,
                                        'uid': Config.uid,
                                    },
                                })
                            } else {
                                this.setState({startVideoPreviewRet: ret})
                            }
                        })
                    }, this.state.startVideoPreviewTotal, this.state.startVideoPreviewF, this.state.startVideoPreviewRet)}
                {this.createNormalApiContent('停止预览', 'stopVideoPreview',
                    () => {
                        this.setState({stopVideoPreviewTotal: this.state.stopVideoPreviewTotal + 1})
                        ThunderEngine.stopVideoPreview((ret) => {
                            this.addCallBackInfo('2', 'stopVideoPreview->' + ret)
                            this.setState({stopVideoPreviewRet: ret})
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopVideoPreviewF: this.state.stopVideoPreviewF + 1,
                                    stopVideoPreviewRet: ret
                                })
                            } else {
                                this.setState({stopVideoPreviewRet: ret})
                            }
                        })
                    }, this.state.stopVideoPreviewTotal, this.state.stopVideoPreviewF, this.state.stopVideoPreviewRet)}
                {this.createNormalApiContent('开启本地视频发送', 'stopLocalVideoStream',
                    () => {
                        this.setState({stopLocalVideoStreamTotal: this.state.stopLocalVideoStreamTotal + 1})
                        ThunderEngine.stopLocalVideoStream(this.state.stopLocalVideoStream, (ret) => {
                            this.addCallBackInfo('2', 'stopLocalVideoStream stop(' + this.state.stopLocalVideoStream + ')->' + ret)
                            this.setState({stopLocalVideoStreamRet: ret})
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopLocalVideoStreamF: this.state.stopLocalVideoStreamF + 1,
                                    stopLocalVideoStreamRet: ret
                                })
                            } else {
                                this.setState({stopLocalVideoStreamRet: ret})
                            }


                        })
                    }, this.state.stopLocalVideoStreamTotal, this.state.stopLocalVideoStreamF, this.state.stopLocalVideoStreamRet,
                    [this.createCheckBox('关闭', this.state.stopLocalVideoStream, () => {
                        this.setState({stopLocalVideoStream: !this.state.stopLocalVideoStream})
                    })])}
                {this.createNormalApiContent('接收指定用户视频数据', 'stopRemoteVideoStream',
                    () => {
                        this.setState({stopRemoteVideoStreamTotal: this.state.stopRemoteVideoStreamTotal + 1})
                        ThunderEngine.stopRemoteVideoStream(this.state.stopRemoteVideoStreamUid, this.state.stopRemoteVideoStream, (ret) => {
                            this.addCallBackInfo('2', 'stopRemoteVideoStream uid(' + this.state.stopRemoteVideoStreamUid + ') stop(' + this.state.stopRemoteVideoStream + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopRemoteVideoStreamF: this.state.stopRemoteVideoStreamF + 1,
                                    stopRemoteVideoStreamRet: ret
                                })
                                return
                            }
                            this.setState({stopRemoteVideoStreamRet: ret})
                            if (!this.state.stopRemoteVideoStream) {
                                let it = null
                                let index = 0
                                let remoteUser = this.state.remoteUser
                                remoteUser.map((item, i) => {
                                    if (item.uid === this.state.stopRemoteVideoStreamUid && !remoteVideoList[i].show) {
                                        index = i
                                        it = item
                                        remoteVideoList[i].show = true
                                    }
                                })

                                if (it != null) {
                                    remoteUser.splice(index, 1)
                                    this.setState({remoteUser: remoteUser})

                                    remoteUser.splice(index, 0, it)
                                    this.setState({remoteUser: remoteUser})
                                }
                            } else {
                                remoteVideoList.map((item, i) => {
                                    if (item.uid === this.state.stopRemoteVideoStreamUid) {
                                        remoteVideoList[i].show = false
                                    }
                                })
                            }
                        })
                    }, this.state.stopRemoteVideoStreamTotal, this.state.stopRemoteVideoStreamF, this.state.stopRemoteVideoStreamRet,
                    [this.createInput('uid', this.state.stopRemoteVideoStreamUid, (text) => {
                        this.setState({stopRemoteVideoStreamUid: text})
                    }, false),
                        this.createCheckBox('关闭', this.state.stopRemoteVideoStream, () => {
                            this.setState({stopRemoteVideoStream: !this.state.stopRemoteVideoStream})
                        })])}
                {this.createNormalApiContent('打开所有远端流播放', 'stopAllRemoteVideoStream',
                    () => {
                        this.setState({stopAllRemoteVideoStreamTotal: this.state.stopAllRemoteVideoStreamTotal + 1})
                        ThunderEngine.stopAllRemoteVideoStreams(this.state.stopAllRemoteVideoStream, (ret) => {
                            this.addCallBackInfo('2', 'stopAllRemoteVideoStream stop(' + this.state.stopAllRemoteVideoStream + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    stopAllRemoteVideoStreamF: this.state.stopAllRemoteVideoStreamF + 1,
                                    stopAllRemoteVideoStreamRet: ret
                                })
                            } else {
                                this.setState({stopAllRemoteVideoStreamRet: ret})

                                let allShow = true
                                remoteVideoList.map((item, i) => {
                                    if (!item.show) {
                                        allShow = false
                                    }
                                })

                                if (!this.state.stopAllRemoteVideoStream) {
                                    if (!allShow) {
                                        let remoteUser = this.state.remoteUser
                                        this.setState({remoteUser: []})
                                        this.setState({remoteUser: remoteUser})

                                        remoteVideoList.map((item, i) => {
                                            remoteVideoList[i].show = true
                                        })
                                    }
                                } else {
                                    remoteVideoList.map((item, i) => {
                                        remoteVideoList[i].show = false
                                    })
                                }
                            }
                        })

                    }, this.state.stopAllRemoteVideoStreamTotal, this.state.stopAllRemoteVideoStreamF, this.state.stopAllRemoteVideoStreamRet,
                    [this.createCheckBox('关闭', this.state.stopAllRemoteVideoStream, () => {
                        this.setState({stopAllRemoteVideoStream: !this.state.stopAllRemoteVideoStream})
                    })])}
                {this.createNormalApiContent('设置本地视频镜像模式', 'setLocalVideoMirrorMode',
                    () => {
                        this.setState({setLocalVideoMirrorModeTotal: this.state.setLocalVideoMirrorModeTotal + 1})
                        ThunderEngine.setLocalVideoMirrorMode(this.state.mirrorMode, (ret) => {
                            this.addCallBackInfo('2', 'setLocalVideoMirrorMode mode(' + this.state.mirrorMode + ')->' + ret)
                            this.setState({setLocalVideoMirrorModeRet: ret})


                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setLocalVideoMirrorModeF: this.state.setLocalVideoMirrorModeF + 1,
                                    setLocalVideoMirrorModeRet: ret
                                })
                            } else {
                                this.setState({setLocalVideoMirrorModeRet: ret})
                            }
                        })
                    }, this.state.setLocalVideoMirrorModeTotal, this.state.setLocalVideoMirrorModeF, this.state.setLocalVideoMirrorModeRet,
                    [this.createPicker(['预览镜像，开播不镜像', '预览开播都镜像', '预览开播都不镜像', '预览不镜像，开播镜像'], [0, 1, 2, 3], this.state.mirrorMode, (item) => {
                        this.setState({mirrorMode: item})
                    })])}
                {this.createNormalApiContent('设置摄像头（横屏/竖屏）', 'setVideoCaptureOrientation',
                    () => {
                        this.setState({setVideoCaptureOrientationTotal: this.state.setVideoCaptureOrientationTotal + 1})
                        ThunderEngine.setVideoCaptureOrientation(this.state.videoCaptureOrientation, (ret) => {
                            this.addCallBackInfo('2', 'setVideoCaptureOrientation orientation(' + this.state.videoCaptureOrientation + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    setVideoCaptureOrientationF: this.state.setVideoCaptureOrientationF + 1,
                                    setVideoCaptureOrientationRet: ret
                                })
                            } else {
                                this.setState({setVideoCaptureOrientationRet: ret})
                            }
                        })
                    }, this.state.setVideoCaptureOrientationTotal, this.state.setVideoCaptureOrientationF, this.state.setVideoCaptureOrientationRet,
                    [this.createCheckBox('横', this.state.videoCaptureOrientation == 1, () => {
                        this.setState({videoCaptureOrientation: this.state.videoCaptureOrientation == 0 ? 1 : 0})
                    })])}
                {this.createNormalApiContent('切换前/后置摄像头', 'switchFrontCamera',
                    () => {
                        this.setState({switchFrontCameraTotal: this.state.switchFrontCameraTotal + 1})
                        ThunderEngine.switchFrontCamera(this.state.frontCamera, (ret) => {
                            this.addCallBackInfo('2', 'switchFrontCamera bFront(' + this.state.frontCamera + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    switchFrontCameraF: this.state.switchFrontCameraF + 1,
                                    switchFrontCameraRet: ret
                                })
                            } else {
                                this.setState({switchFrontCameraRet: ret})
                            }
                        })
                    }, this.state.switchFrontCameraTotal, this.state.switchFrontCameraF, this.state.switchFrontCameraRet,
                    [this.createCheckBox('后置摄像头', !this.state.frontCamera, () => {
                        this.setState({frontCamera: !this.state.frontCamera})
                    })])}
            </ScrollView>
        } else {
            return <ScrollView style={{height: apiContentViewHeight}}>
                {this.createNormalApiContent('跨房间订阅指定用户的流', 'addSubscribe',
                    () => {
                        this.setState({addSubscribeTotal: this.state.addSubscribeTotal + 1})
                        ThunderEngine.addSubscribe(this.state.addSubscribeRoomId, this.state.addSubscribeUid, (ret) => {
                            this.addCallBackInfo('2', 'addSubscribeRoomId roomId(' + this.state.addSubscribeRoomId + ') uid(' + this.state.addSubscribeUid + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    addSubscribeF: this.state.addSubscribeF + 1,
                                    addSubscribeRet: ret
                                })
                            } else {
                                this.setState({addSubscribeRet: ret})
                            }
                        })
                    }, this.state.addSubscribeTotal, this.state.addSubscribeF, this.state.addSubscribeRet,
                    [this.createInput('addSubscribeRoomId', this.state.addSubscribeRoomId, (text) => {
                        this.setState({addSubscribeRoomId: text})
                    }, false),
                        this.createInput('addSubscribeUid', this.state.addSubscribeUid, (text) => {
                            this.setState({addSubscribeUid: text})
                        }, false)])}
                {this.createNormalApiContent('取消跨房间订阅指定用户的流', 'removeSubscribe',
                    () => {
                        this.setState({removeSubscribeTotal: this.state.removeSubscribeTotal + 1})
                        ThunderEngine.removeSubscribe(this.state.removeSubscribeRoomId, this.state.removeSubscribeUid, (ret) => {
                            this.addCallBackInfo('2', 'removeSubscribeRoomId roomId(' + this.state.removeSubscribeRoomId + ') uid(' + this.state.removeSubscribeUid + ')->' + ret)
                            if (!this.isSuccess(ret)) {
                                this.setState({
                                    removeSubscribeF: this.state.removeSubscribeF + 1,
                                    removeSubscribeRet: ret
                                })
                            } else {
                                this.setState({removeSubscribeRet: ret})
                            }
                        })
                    }, this.state.removeSubscribeTotal, this.state.removeSubscribeF, this.state.removeSubscribeRet,
                    [this.createInput('removeSubscribeRoomId', this.state.removeSubscribeRoomId, (text) => {
                        this.setState({removeSubscribeRoomId: text})
                    }, false),
                        this.createInput('removeSubscribeUid', this.state.removeSubscribeUid, (text) => {
                            this.setState({removeSubscribeUid: text})
                        }, false)])}
            </ScrollView>
        }
    }

    callbackTopView() {
        return <View style={styles.api_top}>
            <TouchableOpacity onPress={() => {
                this.clickCallbackItem(1)
            }} onLongPress={() => {
                this.onLongPressCallback()
            }} style={styles.f1}>
                <Text style={this.state.callbackSelectedTab === 1 ? styles.ta_choose : styles.ta}>回调</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickCallbackItem(2)
            }} style={styles.f1}>
                <Text style={this.state.callbackSelectedTab === 2 ? styles.ta_choose : styles.ta}>回显</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickCallbackItem(3)
            }} style={styles.f1}>
                <Text style={this.state.callbackSelectedTab === 3 ? styles.ta_choose : styles.ta}>开播</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickCallbackItem(4)
            }} style={styles.f1}>
                <Text style={this.state.callbackSelectedTab === 4 ? styles.ta_choose : styles.ta}>观看</Text>
            </TouchableOpacity>
            <TouchableOpacity onPress={() => {
                this.clickCallbackItem(5)
            }} style={styles.f1}>
                <Text style={this.state.callbackSelectedTab === 5 ? styles.ta_choose : styles.ta}>音量</Text>
            </TouchableOpacity>
        </View>
    }


    getCallbackShowString() {
        if (this.state.callbackSelectedTab === 5) {
            return this.state.callbackInfo5
        } else if (this.state.callbackSelectedTab === 2) {
            return this.state.callbackInfo2
        } else if (this.state.callbackSelectedTab === 3) {
            return this.state.callbackInfo3
        } else if (this.state.callbackSelectedTab === 4) {
            return this.state.callbackInfo4
        } else {
            return this.state.callbackInfo1
        }
    }

    callBackView(headHeight, fullScreen) {
        return <ScrollView
            style={{
                height: fullScreen ? height - bottomHeight - apiTopViewHeight - headHeight
                    : height - videoHeight - apiContentViewHeight - apiTopViewHeight * 2 - bottomHeight - headHeight,
                backgroundColor: "#cccccc"
            }}>
            <Text>{this.getCallbackShowString()}</Text>
        </ScrollView>
    }


    getZoomInVideo(headHeight) {
        if (this.state.zoomInVideo != '') {
            if (this.state.localUser != null && this.state.zoomInVideo == this.state.localUser.uid) {
                return <View style={{backgroundColor: "#000000", height: height - bottomHeight - headHeight}}>
                    <TouchableOpacity onPress={() => {
                        this.onPressZoomInVideo('')
                    }}>
                        <Text style={styles.text_red}>退出全屏</Text>
                    </TouchableOpacity>
                    <ThunderLocalVideoView setLocalVideoCanvas={{
                        'renderMode': this.state.localUser.mode,
                        'uid': this.state.localUser.uid
                    }} style={{height: height - bottomHeight - redTextHeight - headHeight}}/>
                </View>
            } else {
                let match = false
                let ret = this.state.remoteUser.map((item, i) => {
                    if (item != null && item.uid == this.state.zoomInVideo) {
                        match = true
                        return <View style={{backgroundColor: "#000000", height: height - bottomHeight - headHeight}}>
                            <TouchableOpacity onPress={() => {
                                this.onPressZoomInVideo('')
                            }}>
                                <Text style={styles.text_red}>退出全屏</Text>
                            </TouchableOpacity>
                            <ThunderRemoteVideoView
                                setRemoteVideoCanvas={{'renderMode': item.mode, 'uid': item.uid}}
                                style={{height: height - bottomHeight - redTextHeight - headHeight}}/>
                        </View>
                    }
                    return null
                })
                if (match) {
                    return ret
                }
            }
        }
        return null
    }

    getHeadHeight() {
        if (Platform.OS === 'ios') {
            if (isIphoneX()) {
                return iphoneXHead
            } else {
                return iphoneHead
            }
        }
        return 0
    }

    getZoomInCallback() {
        if (this.state.zoomInCallback) {
            let headHeight = this.getHeadHeight()
            if (headHeight !== 0) {
                return <View style={{marginTop: headHeight}}>
                    {this.callbackTopView()}
                    {this.callBackView(headHeight, true)}
                </View>
            } else {
                return <SafeAreaView>
                    {this.callbackTopView()}
                    {this.callBackView(0, true)}
                </SafeAreaView>
            }
        }
        return null
    }

    // addTranscodingUsers = []
    // addTranscodingUser
    // addTransUserView() {
    //     this.addTranscodingUser = new TranscodingUser()
    //     return <ScrollView >
    //         <View>
    //             {this.createInput('uid', (text) => { this.addTranscodingUser.uid = text }, true)}
    //             {this.createInput('roomId', (text) => { this.addTranscodingUser.roomId = text }, true)}
    //             {this.createInput('layoutX', (text) => { this.addTranscodingUser.layoutX = text }, true)}
    //             {this.createInput('layoutY', (text) => { this.addTranscodingUser.layoutY = text }, true)}
    //             {this.createInput('layoutW', (text) => { this.addTranscodingUser.layoutW = text }, true)}
    //             {this.createInput('layoutH', (text) => { this.addTranscodingUser.layoutH = text }, true)}
    //             {this.createInput('zOrder', (text) => { this.addTranscodingUser.zOrder = text }, true)}
    //             {this.createInput('bCrop', (text) => { this.addTranscodingUser.bCrop = text }, true)}
    //             {this.createInput('cropX', (text) => { this.addTranscodingUser.cropX = text }, true)}
    //             {this.createInput('cropY', (text) => { this.addTranscodingUser.cropY = text }, true)}
    //             {this.createInput('cropW', (text) => { this.addTranscodingUser.cropW = text }, true)}
    //             {this.createInput('cropH', (text) => { this.addTranscodingUser.cropH = text }, true)}
    //             {this.createInput('alpha', (text) => { this.addTranscodingUser.alpha = text }, true)}
    //             <TouchableOpacity onPress={() => { this.setState({ addTransUser: false }) this.addTranscodingUsers.push(addTranscodingUser) }} style={styles.call_btn}>
    //                 <Text>添加</Text>
    //             </TouchableOpacity>
    //             <TouchableOpacity onPress={() => { this.setState({ addTransUser: false }) this.addTranscodingUser = null }} style={styles.call_btn}>
    //                 <Text>取消</Text>
    //             </TouchableOpacity>
    //         </View>
    //     </ScrollView>
    // }

    render() {
        // if (this.state.addTransUser) {
        //     return this.addTransUserView()
        // }

        if (this.state.showPage != true) {
            return <View></View>
        }
        let zoomInCallback = this.getZoomInCallback()
        if (zoomInCallback != null) {
            return zoomInCallback
        }

        let headHeight = this.getHeadHeight()

        let zoomInVideo = this.getZoomInVideo(headHeight)

        if (headHeight !== 0) {
            return <View style={{marginTop: headHeight}}>
                {zoomInVideo != null ? zoomInVideo : <View/>}
                {this.videoView(zoomInVideo == null)}
                {this.apiTopView()}
                {this.apiContentView()}
                {this.callbackTopView()}
                {this.callBackView(headHeight, false)}
            </View>
        } else {
            return <SafeAreaView>
                {zoomInVideo != null ? zoomInVideo : <View/>}
                {this.videoView(zoomInVideo == null)}
                {this.apiTopView()}
                {this.apiContentView()}
                {this.callbackTopView()}
                {this.callBackView(0, false)}
            </SafeAreaView>
        }
    }
}

const styles = StyleSheet.create({
    f1: {
        flex: 1
    },
    videos: {
        flexDirection: "row",
    },
    fr: {
        flexDirection: "row",
    },
    fl: {
        flexDirection: "column",
    },
    video: {
        flex: 1,
        height: videoHeight,
        backgroundColor: "#000000",
    },
    text_red: {
        height: redTextHeight,
        fontSize: 16,
        color: "#ff0000",
    },
    video2: {
        flex: 1,
        backgroundColor: "#DC143C",
        height: videoHeight
    },
    api_top: {
        height: apiTopViewHeight,
        flexDirection: "row",
    },
    ta: {
        paddingTop: 10,
        height: apiTopViewHeight,
        backgroundColor: 'rgba(0, 0, 0, 0.1)',
        textAlign: "center",
    },
    ta_choose: {
        paddingTop: 10,
        height: apiTopViewHeight,
        textAlign: "center",
        backgroundColor: "#ffffff"
    },
    call_btn: {
        margin: 7,
        padding: 10,
        backgroundColor: 'rgba(0, 0, 0, 0.2)',
    },
    line: {
        height: 1,
        backgroundColor: 'rgba(0, 0, 0, 0.2)'
    },
    blue_text: {
        color: "#0000ff"
    },
    gray_text: {
        color: 'rgba(0, 0, 0, 0.5)'
    },
    gray_text_f1: {
        flex: 1,
        color: 'rgba(0, 0, 0, 0.5)'
    },
})