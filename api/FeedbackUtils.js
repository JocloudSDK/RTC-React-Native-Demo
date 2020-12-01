import Config from '../components/Config.js';
import FeedbackModule from './FeedbackModule';

export default class FeedbackUtils {
    static getAppVersionName(fun) {
        FeedbackModule.getAppVersionName({}).then((value) => {
            fun(value);
        });
    }

    static getABI(fun) {
        FeedbackModule.getABI({}).then((value) => {
            fun(value);
        });
    }

    static doFeedback(feedbackMsg, resultCallback) {
        FeedbackModule.doFeedback({'uid':Config.uid,'feedbackMsg':feedbackMsg}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }

    static crashTest() {
        FeedbackModule.crashTest({}).then((value) => {

        }).catch((code, err) => {

        });
    }

    static getLogPath(resultCallback) {
        FeedbackModule.getLogPath({}).then((value) => {
            if (resultCallback != null) {
                resultCallback(value)
            }
        }).catch((code, err) => {

        });
    }
}