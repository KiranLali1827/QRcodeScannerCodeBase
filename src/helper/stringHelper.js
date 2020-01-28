export const isPhoneNumberValid = (phone) => {
  if (phone.length !== 10) {
    return false;
  }
  return true;
}

export const isValidString = str => {
  if (str && str.length > 0) { return true }
  return false;
}

export const formatPhoneNumber = value => {
  const phone = value.replace(/\D+/g, '');
  return phone.slice(-10);

}

export const NameRegex = /[^A-Za-z0-9 ]+/g;