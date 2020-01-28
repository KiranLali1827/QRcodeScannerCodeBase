import React from 'react';
import { Text, View, StyleSheet, Image } from 'react-native';
import { Header, Left, Icon, Body, Right, Button } from 'native-base';
import white_logo from '../../assets/images/small_green_logo.png';
import { GREEN600, WHITE, GREEN900, GREY700, BLACK } from '../../constants/ColorConstant';
import { proportionedPixel } from '../../helper/dimensionsHelper';

export const HeaderHeight = 56;
export const NavigationHeaderHeight = 40

export default function Headers(props) {
  const {
    navigation        // Display navigation header instead default header with logo
  } = props;
  return navigation ? renderNavigationHeader(props) : renderHeader(props);
}

function renderNavigationHeader(props) {
  const {
    onBack,             // Callback for back press
    backBtnTestId,      // Test Id for back button
    title,              // Title to display
    showCart,           // Display cart icon
    onPressCart,        // Callback for cart icon press
    secondary,          // white Background Header
    style = {}          // additional styles {root, title}
  } = props;
  return (
    <Header
      style={[
        secondary ? styles.rootNavigationSecondary : styles.rootNavigation,
        style.root          // Style from props
      ]}
    >
      <Left style={styles.left}>
        {onBack && <Button transparent onPress={onBack} testId={backBtnTestId}>
          <Icon name="ios-arrow-back"
          type='Ionicons'
            style={
              secondary ? styles.backIconSecondary : styles.backIcon
            }
          />
        </Button>}
      </Left>
      <Body style={styles.body}>
        <Text
          style={[
            secondary ? styles.titleCenterSecondary : styles.titleCenter,
            style.title     // Style from props
          ]}
        >{title}</Text>
      </Body>
      {/* <Right style={styles.right}>
        {showCart && <Button transparent onPress={onPressCart}>
          <Icon
            name="cart"                        // TODO Update cart icon based on Final design
          />
        </Button>}
      </Right> */}
    </Header>
  );
}

function renderHeader(props) {
  const {
    rightIcons,          // Array for right side icons with icon name, onPress callback and text to display under icon
    //                      example rightIcons={[
    //                          { name: 'home', onPress: () => { doSomething() }, text: 'Home', testId: 'btn_001' },
    //                          { name: 'cart', onPress: () => { doSomething() }, text: 'Cart', testId: 'btn_002' }
    //                      ]}

    style = {}           // additional styles {root, title}
  } = props;
  return (
    <Header
      style={[
        styles.root,
        style.root     // Style from props
      ]}
    >
      <Left style={styles.left}>
        <Image source={white_logo} style={styles.titleLogo} />
        <Text style={[
          styles.titleLeft,
          style.title
        ]}>
          Dealshare
        </Text>
      </Left>
      <Right style={styles.right}>
        {
          rightIcons && rightIcons.map(icon => (
            <Button flexDirection='row' iconRight transparent style={styles.rightIconButton} onPress={icon.onPress} testId={icon.testId}>
              <Icon
                name={icon.name}
                style={styles.rightIcon}
                type={icon.type}
              />
              <View style={{flexDirection: 'column'}}>
                <Text
                  style={[
                    style.title,
                    styles.rightIconText,
                    { paddingLeft: 1 }
                  ]}
                >
                  {icon.text}
                </Text>

                <Text
                  style={[
                    style.title,
                    styles.rightIconSubText,
                    { paddingLeft: 1 }
                  ]}
                >
                  {icon.subtext}
                </Text>

              </View>

            </Button>
          ))
        }
      </Right>
    </Header>
  );
}


const styles = StyleSheet.create({
  root: {
    backgroundColor: WHITE
  },
  rootNavigation: {
    backgroundColor: GREEN600,
    height: NavigationHeaderHeight
  },
  rootNavigationSecondary: {
    backgroundColor: WHITE,
    height: NavigationHeaderHeight
  },
  backIcon: {
    color: WHITE
  },
  backIconSecondary: {
    color: GREEN900
  },
  left: {
    flex: 1,
    flexDirection: 'row',
    alignItems: 'center',
   },
  body: {
    position:'absolute',
    textAlign: 'center',
    flex: 1,
    flexDirection: 'row',
    alignContent: 'center',
    justifyContent: 'center'
  },
  titleLeft: {
    color: GREEN900,
    fontSize: proportionedPixel(11),
    lineHeight: proportionedPixel(11) * 1.3,
    fontWeight: 'bold',
    marginLeft: proportionedPixel(2),
    textAlignVertical: 'center',
  },
  titleLogo: {
    width: 33,
    height: 33
  },
  titleCenter: {
    color: WHITE,
    fontSize: 20,
    fontWeight: 'bold'
  },
  titleCenterSecondary: {
    color: GREEN900,
    fontSize: 20,
    fontWeight: 'bold'
  },
  right: {
    flex: 1
  },
  rightIcon: {
    color: GREEN900,
    fontSize: proportionedPixel(12)
  },
  rightIconButton: {
    flexDirection: 'column',
  },
  rightIconText: {
    fontSize: proportionedPixel(5),
    color: BLACK
  },
  rightIconSubText: {
    fontSize: proportionedPixel(5),
    color: GREY700
  }
})
