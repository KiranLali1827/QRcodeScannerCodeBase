import React, { PureComponent } from 'react';
import {
  View, ScrollView, KeyboardAvoidingView,
  StyleSheet, Platform, TouchableOpacity, Image, ImageBackground, TextInput
} from 'react-native';

import Icon from 'react-native-vector-icons/MaterialIcons'

 


import { Text } from 'native-base';
import { proportionedPixel } from '../../helper/dimensionsHelper';
import RNOtpVerify from 'react-native-otp-verify';
import { WHITE } from '../../values/Colors';
import { isPhoneNumberValid, NameRegex, formatPhoneNumber } from '../../helper/stringHelper';
import { Actions } from 'react-native-router-flux';
import LinearGradient from 'react-native-linear-gradient';

import { routes } from '../../../routes';
import { Card } from "native-base";

import logo from '../../assets/images/backimage.png';


class LoginScreen extends PureComponent {
  constructor(props) {
    super(props);
    this.state = {
      name: '',
      phone: '',
      hash_code: null,
      lat: '',
      long: '',
      signature: null,
      payload: null,
      checked: false,
    }
    this.nameFieldRef = React.createRef();    // reference used to focus on name field once mobile no. is entered
  }

  componentDidMount() {
    if (Platform.OS === 'android') {
      this.getHashCode();
    }

  }
  handleCheckBox = () => this.setState({ checked: !this.state.checked })

  getHashCode() {

    RNOtpVerify.getHash()
      .then(message => {
        this.setState({ hash_code: message[0] });

      })
      .catch(console.log);    // TODO: Replace console with global error modal

  }

  changeFocusToNameField() {
    this.nameFieldRef._root.focus();
  }

  onChangePhone(value) {
    const phone = formatPhoneNumber(value);
    if (phone.length <= 10) {
      this.setState({ phone });
      if (phone.length > 9) {
        this.changeFocusToNameField();
      }
    }
  }

  onChangeName(value) {
    NameRegex.test(value) ?
      this.props.showError('Special Chars not allowed in Name') :
      this.setState({ name: value })
  }



  login() {
    Actions.reset(routes.qrcodescannerscreen)
  }

  retry = () => {
    console.warn('retry block');
  }

  render() {
    const { checked } = this.state;

    const { name, phone } = this.state;
    const { loading, error } = this.props;    // TODO: on loading/error open global loading/error modal
    const disableSubmit = !(name && name.length > 0 && isPhoneNumberValid(phone))
    return (
      <KeyboardAvoidingView
        style={styles.root}
      >
        <ImageBackground source={logo} style={styles.root}>
          <ScrollView contentContainerStyle={{ flexGrow: 1 }} keyboardShouldPersistTaps='always'>
            <View style={styles.child1}>
              <Card style={styles.cardview}>
                <Image
                  style={styles.profileimage}
                  source={logo}
                />
                <TextInput style={[styles.textinputview,{marginTop: proportionedPixel(14) / 2}]}/>
                <TextInput style={[styles.textinputview,{marginTop: proportionedPixel(14) / 2}]}/>


                
                <TouchableOpacity onPress={() => this.login()}>

                  <LinearGradient
                    start={{ x: 0, y: 0 }} end={{ x: 1, y: 0 }}
                    locations={[0, 0.5, 0.6]}
                    colors={['#00C9F2', '#004250']}
                    style={styles.linearGradient}>
                    <Text style={styles.buttonText}>
                      {'LOGIN'}
                    </Text>
                  </LinearGradient>
                </TouchableOpacity>

                <View style={{ flexDirection: 'row', alignItems: 'center', justifyContent: 'center', paddingLeft: proportionedPixel(33) / 2,marginTop:proportionedPixel(15)/2 }}>

                  <TouchableOpacity style={[styles.checkBox]} onPress={this.handleCheckBox} >
                    <Icon
                      size={25}
                      color={'#000'}
                      name={this.state.checked ? 'check-box' : 'check-box-outline-blank'}
                    />

                  </TouchableOpacity>
                  <Text style={{ fontSize: proportionedPixel(4.5), flex: 1 }}>{'Keep Me Logged In'}</Text>

                  <Text style={{ fontSize: proportionedPixel(4.5), flex: 1 }}>{'Forgot Password'}</Text>
                </View>



              </Card>
            </View>
          </ScrollView>
        </ImageBackground>
      </KeyboardAvoidingView>
    )
  }
}

const styles = StyleSheet.create({
  root: {
    flex: 1,
    backgroundColor: WHITE
  },
  child1: {
    alignItems: 'center',
    justifyContent: 'center',
    width: '100%', height: '100%',
  },
  cardview: {
    borderRadius: 8,
    width: proportionedPixel(280) / 2,
    height: proportionedPixel(335) / 2,
    justifyContent: 'center',
    alignItems: 'center'
  },
  profileimage: {
    width: proportionedPixel(50),
    height: proportionedPixel(50),
    borderRadius: proportionedPixel(50) / 2,
    marginTop: proportionedPixel(31) / 2
  }, 

  linearGradient: {
    alignItems: 'center',
    flexDirection: 'row',
    justifyContent: 'center',
    alignItems: 'center',
    width: proportionedPixel(235) / 2,
    height: proportionedPixel(15),
    borderRadius: proportionedPixel(15) / 2,
    marginTop: proportionedPixel(21) / 2

  },
  buttonText: {
    fontSize: proportionedPixel(6),
    fontFamily: 'Gill Sans',
    textAlign: 'center',
    color: '#ffffff',
    backgroundColor: 'transparent',
  },
  textinputview: {
    backgroundColor: '#CDCDCD',
    width: proportionedPixel(235) / 2,
    height: proportionedPixel(15),
    borderRadius: proportionedPixel(15) / 2,
    paddingRight: proportionedPixel(5),
    paddingLeft: proportionedPixel(5),
    alignItems:'center',
    justifyContent:'center',
    fontSize: proportionedPixel(8),
    textAlign:'center'
 
  }, textinput: {

    
  },
  checkBox: {
    flexDirection: 'row',
    alignItems: 'center'
  },

   
  scrollView: {
    paddingBottom: 10,
    flexGrow: 1

  }
  
  
})

export default LoginScreen;
