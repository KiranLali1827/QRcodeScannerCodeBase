
import {
  
  GET_OTP,
  GET_OTP_SUCCESS,
  GET_OTP_ERROR,

  GET_TOKEN,
  GET_TOKEN_SUCCESS,
  GET_TOKEN_ERROR
  
} from '../constants/ActionsTypes';


// Get OTP
export const getOtp = (data) => {
  return {
    type: GET_OTP,
    data
  }
}

export const getOtpSuccess = (data) => {
  return {
    type: GET_OTP_SUCCESS,
    data
  }
}

export const getOtpError = (data) => {
  return {
    type: GET_OTP_ERROR,
    data
  }
}

// Get TOKEN
export const getToken = (data) => {
  return {
    type: GET_TOKEN,
    data
  }
}

export const getTokenSuccess = (data) => {
  return {
    type: GET_TOKEN_SUCCESS,
    data
  }
}

export const getTokenError = (data) => {
  return {
    type: GET_TOKEN_ERROR,
    data
  }
}
 