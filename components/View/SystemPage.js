import React, { Component } from 'react';
import {
    StyleSheet,
    Text,
    View,
    TextInput,
    Button, Alert, SafeAreaView
} from 'react-native';
import FeedbackUtils from '../../api/FeedbackUtils.js';
import ThunderEngine from '../../api/ThunderEngine.js';
export default class SystemPage extends Component {
    constructor(props) {
        super(props);
        this.state = {
            appVersionName: "",
            sdkVersionName: "",
            cpuABI: "",
            message: "",
            showPage: false,
        };

        FeedbackUtils.getAppVersionName(version => {
            this.setState({
                appVersionName: version
            });
        });

        ThunderEngine.getVersion(version => {
            this.setState({
                sdkVersionName: version
            });
        });

        FeedbackUtils.getABI(value => {
            this.setState({
                cpuABI: value
            });
        });
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

    setMessage(message) {
        this.setState({
            message: message
        });
    }

    onFeedbackFail(msg) {
        Alert.alert("意见反馈", msg, [{ text: "确定", onPress: () => { } }])
    }

    onFeedbackCompleted() {
        Alert.alert("意见反馈", "反馈成功", [{ text: "确定", onPress: () => { } }])
    }

    onFeedbackProgressChange(i) {
        console.log("意见反馈进度：" + i)
    }

    doFeedback(ev) {
        FeedbackUtils.doFeedback(this.state.message,
            (ret) => {
                if (ret == 0) {
                    Alert.alert("意见反馈", "反馈成功", [{
                        text: "确定", onPress: () => {
                        }
                    }])
                } else {
                    Alert.alert("意见反馈", "反馈失败", [{
                        text: "确定", onPress: () => {
                        }
                    }])
                }
            })
    }

    crashTest(){
        FeedbackUtils.crashTest()
    }

    render() {
        if (this.state.showPage != true) {
            return <View></View>
        }

        return (
            <SafeAreaView>
                <View style={styles.container}>
                    <Text style={styles.itemcontainer}>
                        Demo版本号：{this.state.appVersionName}
                    </Text>
                    <Text style={styles.itemcontainer}>
                        SDK版本号：{this.state.sdkVersionName}
                    </Text>
                    <Text style={styles.itemcontainer}>
                        ABI：{this.state.cpuABI}
                    </Text>
                    <TextInput style={styles.inputcontainer} placeholder="日志反馈：" returnKeyType="done"
                               onChangeText={text => this.setMessage(text)}/>
                    <Button style={styles.bottoncontainer} title="反馈" onPress={ev => this.doFeedback(ev)}/>
                    <View style={styles.itemcontainer}></View>
                    <Button style={styles.bottoncontainer} title="崩溃测试" onPress={ev => this.crashTest()}/>
                </View>
            </SafeAreaView>
        );
    }

    componentDidMount() {
        this.props.onRef(this);
    };
}


const styles = StyleSheet.create({
    container: {
        margin: 10,
    },
    itemcontainer: {
        marginTop: 4,
        marginBottom: 4,
    },
    inputcontainer: {
        marginTop: 4,
        marginBottom: 4,
        borderWidth: 1,
        height: 100
    },
    bottoncontainer: {
    },
});