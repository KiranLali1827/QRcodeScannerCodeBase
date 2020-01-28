 
import axios from 'axios';
import Config from 'react-native-config';

function baseAxios(options) {
  const defaultHeaders = {
    "Content-Type": "application/x-www-form-urlencoded",
  }
  // let baseUrl = `${Config.API_URL}`;
  // if (__DEV__) {
  //   baseUrl = `${Config.STAGING_URL}`;
  // }

  return axios.create({
    // baseURL: baseUrl,
    timeout: options.timeout || 30000,
    headers: defaultHeaders,
  })
}

function executeRequest(method, pathname, data, options = {}) {
  const body = method === 'get' || !data ? {} : {
    data
  }
  const reqObj = {
    method,
    url: pathname,
    params: options.query,
    ...body
  }
  const baseAxiosRequest = baseAxios(options)
  return new Promise((resolve, reject) => {
    return baseAxiosRequest
      .request(reqObj)
      .then(res => {
        console.log('Axios', res);
        resolve(res.data)
      })
      .catch(error => {
        console.log('Axios', error);
        reject(error)
      })
  })
}

export default {
  get(pathname, options, params) {
    if(params){
      for (let property in params) {
        pathname += `&${property}=${params[property]}`
      }
    }
    console.log('Inside get', pathname);
    return executeRequest('get', pathname, null, options)
  },

  post(pathname, data, options) {
    return executeRequest('post', pathname, data, options)
  },

  put(pathname, data, options) {
    return executeRequest('put', pathname, JSON.stringify(data), options)
  },

  delete(pathname, data, options) {
    return executeRequest('delete', pathname, JSON.stringify(data), options)
  },

  all(promises) {
    return axios.all(promises)
  },
}

