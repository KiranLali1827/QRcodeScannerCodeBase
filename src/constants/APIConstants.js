const ENTRY_POINT= 'https://skyoms.com/';   
// const ENTRY_POINT = 'https://s';   

export const GET_OTP_API = ENTRY_POINT + ''; 
export const GET_ACCESS_TOKEN_API = ENTRY_POINT + 'api/token'; 

export const GET_CONFIG_DETAILS_API = (phone, pincode) => `${ENTRY_POINT}config/app/${phone}/${pincode}`