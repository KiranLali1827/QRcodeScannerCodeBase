
import { all, fork } from 'redux-saga/effects';
import UserSaga from './UserSaga';
export default function* root() {
  console.log('root Saga');
  yield all([
    fork(UserSaga),
   ]);
}


