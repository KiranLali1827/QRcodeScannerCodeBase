import Immutable from 'immutable';
import { SHOW_ERROR_MODAL, HIDE_ERROR_MODAL } from '../constants/ActionsTypes';

const INTIAL_STATE = Immutable.fromJS({
  visible: false,
  message: null
});

export default function error(state = INTIAL_STATE, action) {
  switch (action.type) {
    case SHOW_ERROR_MODAL:
      return { ...state, visible: true, message: action.data }
    case HIDE_ERROR_MODAL:
      return { ...state, visible: false, message: null }
    default:
      return state
  }
}
