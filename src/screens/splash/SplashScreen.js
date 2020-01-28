
import React, { Component } from 'react';
import { View, Text, StyleSheet, Image } from 'react-native';
import { widthPercentageToDP, heightPercentageToDP } from '../../helper/dimensionsHelper';
import logo from '../../assets/images/backimage.png';
import { Actions, ActionConst } from 'react-native-router-flux';
import { routes } from '../../../routes';
import { GREEN900, WHITE } from '../../constants/ColorConstant';
import AsyncStorage from '@react-native-community/async-storage';
import USER_DATA from '../../constants/AppConstant'
import { NativeModules } from 'react-native'
var SplashScreen1 = NativeModules.SplashScreen
class SplashScreen extends Component {

   
  componentDidMount() {
    // setTimeout(() => {
    //   Actions.reset(routes.login)
    // }, 500);
       SplashScreen1.hide();
     this.checkUserData()

  }

  login() { 
      this.props.getToken({
        onSuccess: () => this.onSuccess()
      })
   }

  onSuccess = () => {
    Actions.reset(routes.login)
  }

  checkUserData = async () => {
    try {
      const value = await AsyncStorage.getItem('USER_DATA');
      const userData = JSON.parse(value);
      if ( userData && userData.auth_key ) {
         Actions.reset(routes.qrcodescannerscreen);
      }else{
        this.login()
      }
      console.warn('user data from async :', userData);
    } catch (error) {
      Actions.reset(routes.login);
      console.log('error in user data', error )
    }
  }

  appStateHandling = (appState) => {
    if (appState === 'active') {
      console.log('appStateHandling', appState);
    } else {
      console.log('appStateHandling', appState);
    }
  }

  networkStateHandling = (isConnected) => {
    if (isConnected) {
      console.log('mobile connected to network', isConnected);
    } else {
      console.log('mobile not connected to network', isConnected);
    }
  }

  shouldComponentUpdate(nextProps) {
    console.log('splash shouldComponentUpdate ', nextProps);
    if (this.props.isConnected !== nextProps.isConnected) {
      this.networkStateHandling(nextProps.isConnected);
      return true;
    }
    if (this.props.appState !== nextProps.appState) {
      this.appStateHandling(nextProps.appState);
      return true;
    }
    return false;
  }

  componentWillUnmount() { 
  }

  retry = () => {
    console.warn('retry block');
  }

  render() {
    return (
      <View style={styles.root}>
        <Image source={logo} />
        <Text style={styles.dealshareText}>
          TNT
        </Text>
      </View>
    )
  }

}

export default SplashScreen;

const styles = StyleSheet.create({
  root: {
    backgroundColor: GREEN900,
    width: widthPercentageToDP(100),
    height: heightPercentageToDP(100),
    justifyContent: 'center',
    alignItems: 'center'
  },
  dealshareText: {
    textAlign: 'center',
    fontSize: 24,
    color: WHITE
  }
})
