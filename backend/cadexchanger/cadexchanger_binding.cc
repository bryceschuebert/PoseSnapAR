#include <napi.h>
#include "cadexsdk/inc/cadex/LicenseManager_Activate.h"
#include "cadexsdk/inc/cadex/ModelData_Model.hxx"
#include "cadexsdk/inc/cadex/ModelData_RepresentationMask.hxx"
#include "cadexsdk/inc/cadex/ModelData_ModelReader.hxx"
#include "cadexsdk/inc/cadex/ModelData_ModelWriter.hxx" 
#include <iostream>
#include <cadex/LicenseManager_LicenseError.hxx>

#include "cadexsdk/examples/cxx/cadex_license.cxx"

bool cadexFunction();

Napi::Value WrapperFunction(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = cadexFunction();
  return Napi::Boolean::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("wrapperFunction", Napi::Function::New(env, WrapperFunction));
  return exports;
}

NODE_API_MODULE(cadexchanger, Init)
