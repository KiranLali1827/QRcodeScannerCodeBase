

import {
  GET_OTP,
  GET_TOKEN,
} from '../constants/ActionsTypes';
import { put, takeLatest, call } from 'redux-saga/effects';
import API from '../apis/BaseApi';
import {
  getOtpError, getOtpSuccess,
  verifyOtpError, verifyOtpSuccess,getTokenSuccess
} from '../actions/UserActions';
import {
  GET_OTP_API,
  GET_ACCESS_TOKEN_API,
} from '../constants/APIConstants';
import { showFullPageLoader, hideFullPageLoader } from '../actions/LoaderActions';
console.log('API', API);


function* getOtp(action) {
  const { data, onSuccess, onError } = action.data;
  yield put(showFullPageLoader());
  try {
    const response = yield call(API.post, GET_OTP_API, data);
    if (onSuccess) {
      onSuccess(response)
    }
    yield put(getOtpSuccess(response));
  } catch (error) {
    if (onError) {
      onError();
    }
    yield put(getOtpError(error.message));
  } finally {
    yield put(hideFullPageLoader());
  }
}

function* verifyOtp(action) {
  const { data, onSuccess, onError } = action.data;
  yield put(showFullPageLoader());
  try {
    const response = yield call(API.post, VERIFY_OTP_API, data);
    if (!response.status) {
      throw new Error(response.msg)
    }
    if (onSuccess) {
      onSuccess()
    }
    yield put(verifyOtpSuccess(response));
  } catch (error) {
    if (onError) {
      onError();
    }
    yield put(verifyOtpError(error))
  } finally {
    yield put(hideFullPageLoader());
  }
}

function* getToken(action) {
  const { onSuccess, onError } = action.data;
  let details = {
    'username': 'admin',
    'password': 'adminpass',
    'grant_type': 'password'
  };
  let formBody = [];
  for (let property in details) {
    let encodedKey = encodeURIComponent(property);
    let encodedValue = encodeURIComponent(details[property]);
    formBody.push(encodedKey + "=" + encodedValue);
  }
  formBody = formBody.join("&");
  try {
    const response = yield call(API.post, GET_ACCESS_TOKEN_API, formBody);
    if (!response.access_token) {
      throw new Error(response.msg)
    }
    if (onSuccess) {
      onSuccess()
    }
    yield put(getTokenSuccess(response));
  } catch (error) {
    console.log('error : ', error.message)
    if (onError) {
      onError();
    }
    yield put(verifyOtpError(error))
  } finally {
    yield put(hideFullPageLoader());
  }
}

export default function* root() {
  console.log('Inside Saga root');
  yield [
    yield takeLatest(GET_OTP, getOtp),
    yield takeLatest(GET_TOKEN, getToken),
    // yield takeLatest(VERIFY_OTP, verifyOtp), 
  ]
}
