
import { connect } from 'react-redux';
import { getToken } from '../../actions/UserActions';
import SplashScreen from './SplashScreen';

const mapStateToProps = (user) => {
  const {
    loading,
    error,
  } = user
  return {
    loading,
    error,
  }
}

const mapDispatchToProps = (dispatch) => {
  return {
    getToken: (data) => dispatch(getTokenSuccess(data))
  }
}


export default connect(mapStateToProps, mapDispatchToProps)(SplashScreen);
