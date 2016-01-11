/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_reacttests_API */
#include <dlfcn.h>
#include <iostream>
#include <sstream>

#include "com_reacttests_RealmReactAndroid.h"
#include "JSCExecutor.h"
#include "js_init.h"
#include "platform.hpp"
#include <unordered_map>

/*
 * Class:     com_reacttests_RealmReactAndroid
 * Method:    injectRealmJsContext
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_reacttests_RealmReactAndroid_injectRealmJsContext
  (JNIEnv *env, jclass, jstring fileDir) 
  {
  	
  	void* handle = dlopen ("libreactnativejni.so", RTLD_LAZY);
  	if (!handle) {
        return env->NewStringUTF("Cannot open library");
    }
    
    // Getting the internal storage path for the application
    const char* strFileDir = env->GetStringUTFChars(fileDir , NULL);
    std::string absoluteAppPath(strFileDir); 
    env->ReleaseStringUTFChars(fileDir , strFileDir);
      realm::set_default_realm_file_directory(absoluteAppPath);

    // load the symbol
	typedef std::unordered_map<JSContextRef, facebook::react::JSCExecutor*> (*get_jsc_context_t)();

	get_jsc_context_t get_jsc_context = (get_jsc_context_t) dlsym(handle, "get_jsc_context");

	  if (get_jsc_context != NULL) {
	  	std::unordered_map<JSContextRef, facebook::react::JSCExecutor*> s_globalContextRefToJSCExecutor = get_jsc_context();	
	  	std::stringstream msg;
	  	msg << "Got the globalContext map, size=" << s_globalContextRefToJSCExecutor.size();

          for (auto pair : s_globalContextRefToJSCExecutor) {
			  RJSInitializeInContext(pair.first);
		  }

	  	return env->NewStringUTF(msg.str().c_str());
	  } else {
	  	 return env->NewStringUTF("Cannot find symbol get_jsc_context");
	  }
  }

