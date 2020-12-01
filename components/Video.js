import requestCameraAndAudioPermission from './permission';
import React, {
    Component,
} from 'react';
import {
    TouchableOpacity,
    AsyncStorage,
    View,
    Text,
    Platform,
    StyleSheet
} from 'react-native';
import TestPage from './View/TestPage'
import SettingPage from './View/SettingPage';
import SystemPage from './View/SystemPage';
import Config from './Config';
import ThunderEngine from "../api/ThunderEngine";
import FeedbackUtils from '../api/FeedbackUtils.js';


class Video extends Component {
    static testPage;
    static systemPage;
    static settingPage;

    constructor(props) {
        super(props);

        this._get(Config.STORAGE_APP_ID_KEY, false).then(r => {
            Config.APPID = r
        });
        this._get(Config.STORAGE_UID_KEY, true).then(r => Config.uid = r);
        this._get(Config.STORAGE_CHANNEL_ID_KEY, true).then(r => Config.channelId = r);

        this.state = {
            selectPage: 1,
        };

        if (Platform.OS === 'android') {
            requestCameraAndAudioPermission().then(_ => {
            });
        }
    }

    // 获取
    async _get(key, useRandom) {
        let ret = '';
        try {// try catch 捕获异步执行的异常
            var value = await AsyncStorage.getItem(key);
            if (value !== null) {
                ret = value;
            } else {
                if (useRandom) {
                    ret = (Math.floor(Math.random() * 10000) + 1).toString();
                }
            }
        } catch (error) {
        }
        return ret;
    }

    componentDidMount() {
    }


    mainPage() {

        this.showPage();
        return <View>
            <TestPage onRef={this.testPageOnRef}/>
            <SettingPage onRef={this.settingPageOnRef}/>
            <SystemPage onRef={this.systemPageOnRef}/>
        </View>
    }

    showPage() {

        if (Video.testPage == null) {
            return;
        }

        if (this.state.selectPage == 1) {
            Video.testPage.show();
            Video.settingPage.hide();
            Video.systemPage.hide();
        } else if (this.state.selectPage == 2) {
            Video.testPage.hide();
            Video.settingPage.show();
            Video.systemPage.hide();
        } else {
            Video.testPage.hide();
            Video.settingPage.hide();
            Video.systemPage.show();
        }
    }

    testPageOnRef(ref) {
        Video.testPage = ref;
    }

    settingPageOnRef(ref) {
        Video.settingPage = ref;
    }

    systemPageOnRef(ref) {
        Video.systemPage = ref;
    }

    clickChangePage(index) {
        this.setState({
            selectPage: index
        })
    }

    videoView() {
        return (
            <View style={styles.f1}>
                {this.mainPage()}
                <View style={styles.bottom_bar}>
                    <TouchableOpacity style={styles.f1} onPress={() => {
                        this.clickChangePage(1)
                    }}>
                        <Text
                            style={this.state.selectPage === 1 ? styles.bottom_text_choose : styles.bottom_text}>测试</Text>
                    </TouchableOpacity>
                    <TouchableOpacity style={styles.f1} onPress={() => {
                        this.clickChangePage(2)
                    }}>
                        <Text
                            style={this.state.selectPage === 2 ? styles.bottom_text_choose : styles.bottom_text}>设置</Text>
                    </TouchableOpacity>
                    <TouchableOpacity style={styles.f1} onPress={() => {
                        this.clickChangePage(3)
                    }}>
                        <Text
                            style={this.state.selectPage === 3 ? styles.bottom_text_choose : styles.bottom_text}>系统</Text>
                    </TouchableOpacity>
                </View>
            </View>
        );
    }

    render() {
        return (
            this.videoView()
        )
    }
}

const styles = StyleSheet.create({
    f1: {
        flex: 1
    },
    bottom_bar: {
        flex: 1,
        flexDirection: 'row',
        position: 'absolute',
        left: 0,
        right: 0,
        bottom: 0,
        height: 44,
    },
    bottom_text: {
        paddingTop: 14,
        paddingBottom: 14,
        backgroundColor: 'rgba(0, 0, 0, 0.1)',
        textAlign: "center"
    },
    bottom_text_choose: {
        paddingTop: 14,
        paddingBottom: 14,
        backgroundColor: '#ffffff',
        textAlign: "center"
    }
});


export default Video;
