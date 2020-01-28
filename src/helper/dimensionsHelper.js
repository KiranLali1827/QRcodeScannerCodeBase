import { Dimensions, PixelRatio } from 'react-native';

const widthPercentageToDP = widthPercent => {
  const screenWidth = Dimensions.get('window').width;
  // Convert string input to decimal number
  const elemWidth = parseFloat(widthPercent);
  return PixelRatio.roundToNearestPixel(screenWidth * elemWidth / 100);
};
const heightPercentageToDP = heightPercent => {
  const screenHeight = Dimensions.get('window').height;
  // Convert string input to decimal number
  const elemHeight = parseFloat(heightPercent);
  return PixelRatio.roundToNearestPixel(screenHeight * elemHeight / 100);
};
const proportionedPixel = designPixels => {
  const screenPropotion = Dimensions.get('window').width / 180;
  return PixelRatio.roundToNearestPixel(designPixels * screenPropotion);
}

export { widthPercentageToDP, heightPercentageToDP, proportionedPixel };
