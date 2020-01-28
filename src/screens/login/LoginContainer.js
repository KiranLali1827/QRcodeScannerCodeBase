import { connect } from 'react-redux';
import LoginScreen from './LoginScreen';
import { getOtp } from '../../actions/UserActions';
import { showErrorModal } from '../../actions/ErrorActions';

const mapStateToProps = (state) => {
  const { loading, error } = state.user;
  return {
    loading,
    error,
  }
}

const mapDispatchToProps = (dispatch) => {
  return {
    getOtp: (data) => dispatch(getOtp(data)),
    showError: (msg) => dispatch(showErrorModal(msg))
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(LoginScreen);