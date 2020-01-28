import { SHOW_ERROR_MODAL, HIDE_ERROR_MODAL } from "../constants/ActionsTypes";


export const showErrorModal = (data) => {
  return {
    type: SHOW_ERROR_MODAL,
    data
  }
}

export const hideErrorModal = () => {
  return {
    type: HIDE_ERROR_MODAL
  }
}

