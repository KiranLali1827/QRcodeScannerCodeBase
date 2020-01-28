import { SHOW_FULL_PAGE_LOADER, HIDE_FULL_PAGE_LOADER } from "../constants/ActionsTypes"

export const showFullPageLoader = () => {
  return {
    type: SHOW_FULL_PAGE_LOADER
  }
}

export const hideFullPageLoader = () => {
  return {
    type: HIDE_FULL_PAGE_LOADER
  }
}