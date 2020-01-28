/*
 * @Author: Shreeshaila v
 * @Date: 2019-10-31 1:10 pm
 * @Last Modified by:
 * @Last Modified time:
 */

import React from 'react';
import { Scene, Router, Stack, Tabs } from 'react-native-router-flux';
import SplashContainer from './src/screens/splash';
import LoginContainer from './src/screens/login'; 
import QRcodescannerContainer from './src/screens/qrcodescannerscreen'; 
  
 

import { StyleSheet } from 'react-native';

export const routes = {
  splash: 'splash',
  login: 'login',
  qrcodescannerscreen: 'qrcodescannerscreen',

 }

const RouterComponent = (props) => {

  return (
    <Router>
      <Stack key="root">
        <Scene key={routes.splash} component={SplashContainer} hideNavBar={true} />
        <Scene key={routes.login} component={LoginContainer}  hideNavBar={true} />
        <Scene key={routes.qrcodescannerscreen} component={QRcodescannerContainer} hideNavBar={true}  />
      </Stack>
    </Router>
  );
};

export default RouterComponent;

const styles = StyleSheet.create({
  tabBarStyles: {
    height: 55
  }
})
