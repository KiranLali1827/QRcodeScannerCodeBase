/*
 * @Author: Shreeshaila v
 * @Date: 2019-10-31 1:10 pm
 * @Last Modified by:
 * @Last Modified time:
 */
import {
    createStore,
    applyMiddleware,
    compose
  } from 'redux'
  import createSagaMiddleware from 'redux-saga';
  import {
    createLogger
  } from 'redux-logger';
  import rootReducer from './src/reducers';
  import rootSaga from './src/sagas';
  
  export default configureStore = () => {
    const middleware = []
    const enhancers = []
  
    const sagaMiddleware = createSagaMiddleware()
    middleware.push(sagaMiddleware)
  
    // if (DebugSetting.reduxLogging) {
      middleware.push(createLogger())
    // }
  
    enhancers.push(applyMiddleware(...middleware))
    const store = createStore(rootReducer, compose(...enhancers))
  
    sagaMiddleware.run(rootSaga)
  
    return store
  }
  