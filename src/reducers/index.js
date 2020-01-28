 

import { combineReducers } from 'redux';
import user from './UserReducer';
import error from './ErrorReducer';
import loader from './LoaderReducer';
import config from './ConfigReducer';

const rootReducer = combineReducers({
  user,
  error,
  loader,
  config
});

export default rootReducer;
