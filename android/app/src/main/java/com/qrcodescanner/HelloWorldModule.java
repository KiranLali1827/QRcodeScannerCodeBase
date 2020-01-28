package com.qrcodescanner;

import android.content.Intent;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.uimanager.IllegalViewOperationException;
 
public class HelloWorldModule extends ReactContextBaseJavaModule {
 
    public HelloWorldModule(ReactApplicationContext reactContext) {
        super(reactContext); //required by React Native
    }
 
    @Override
    //getName is required to define the name of the module represented in JavaScript
    public String getName() { 
        return "HelloWorld";
    }
 
    @ReactMethod
    public void sayHi(Callback errorCallback, Callback successCallback) {
        try {



            System.out.println("Greetings from shree");
            successCallback.invoke("Callback : Greetings from shree");

            Intent intent = new Intent(MainActivity.getActivity(),TestActivity.class);
            MainActivity.getActivity().startActivity(intent);


        } catch (IllegalViewOperationException e) {
            errorCallback.invoke(e.getMessage());
        }
    }
}