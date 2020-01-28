
import Immutable from 'immutable';
import {
  GET_OTP,
  GET_OTP_SUCCESS,
  GET_OTP_ERROR,
  GET_TOKEN,
  GET_TOKEN_SUCCESS,
  GET_TOKEN_ERROR
} from '../constants/ActionsTypes';

const INTIAL_STATE = Immutable.fromJS({
  error: null,
  loading: false,
  details: null
});


export default function user(state = INTIAL_STATE, action) {
  console.log('Reducers User', action.type);
  switch (action.type) {
    case GET_OTP:
      const { data } = action.data;
      return { ...state, loading: true, error: null, details: data }
    case GET_OTP_SUCCESS:
      return { ...state, loading: false, error: null }
    case GET_OTP_ERROR:
      return { ...state, loading: false, error: action.data }

    case GET_TOKEN:
      const { data1 } = action.data;
      return { ...state, loading: true, error: null, details: data1 }
    case GET_TOKEN_SUCCESS:
      return { ...state, loading: false, error: null }
    case GET_TOKEN_ERROR:
      return { ...state, loading: false, error: action.data }

    default:
      return state
  }
}
