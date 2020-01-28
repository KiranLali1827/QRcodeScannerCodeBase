import Immutable from 'immutable';
import { GET_CONFIG_DETAILS, GET_CONFIG_DETAILS_SUCCESS, GET_CONFIG_DETAILS_ERROR } from '../constants/ActionsTypes';

const INTIAL_STATE = Immutable.fromJS({
  config: {},
  error: null,
  loading: false
});

export default function config(state = INTIAL_STATE, action) {
  switch (action.type) {
    case GET_CONFIG_DETAILS:
      return { ...state, loading: true, error: null }
    case GET_CONFIG_DETAILS_SUCCESS:
      return { ...state, loading: false, error: null, details: action.data }
    case GET_CONFIG_DETAILS_ERROR:
      return { ...state, loading: false, error: action.data.message }
    default:
      return state
  }
}
