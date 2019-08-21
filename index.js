import {NativeModules} from 'react-native';

const {RNZendrive} = NativeModules;

const verifyID = (id) => {
    if (typeof id !== 'string') {
        throw new Error('Tracking ID must be a string');
    }
};

// all methods return a promise
export default class NativeModule {
    static startPeriod1() {
        return RNZendrive.startPeriod1();
    };

    static startPeriod2(driverID) {
        verifyID(driverID);
        return RNZendrive.startPeriod2(driverID);
    }

    static startPeriod3(driverID) {
        verifyID(driverID);
        return RNZendrive.startPeriod3(driverID);
    }

    static stopPeriod() {
        return RNZendrive.stopPeriod();
    }

    static enableZendrive(driverID) {
        verifyID(driverID);
        return RNZendrive.enableZendrive(driverID);
    }

    static disableZendrive() {
        return RNZendrive.disableZendrive();
    }

}
