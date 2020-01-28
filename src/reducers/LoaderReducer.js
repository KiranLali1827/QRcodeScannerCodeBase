import Immutable from 'immutable';
import { SHOW_FULL_PAGE_LOADER, HIDE_FULL_PAGE_LOADER } from '../constants/ActionsTypes';

const INTIAL_STATE = Immutable.fromJS({
  show: false
});


export default function loader(state = INTIAL_STATE, action) {
  switch (action.type) {
    case SHOW_FULL_PAGE_LOADER:
      return { ...state, show: true }
    case HIDE_FULL_PAGE_LOADER:
      return { ...state, show: false }
    default:
      return state
  }
}
