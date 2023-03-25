#include <napi.h>
#include <cadex/Base_ProgressScope.hxx>
#include <cadex/ModelData_Model.hxx>
#include <cadex/ModelData_Part.hxx>
#include <cadex/ModelData_ModelReader.hxx>
#include <cadex/ModelData_ModelWriter.hxx>
#include <cadex/STEP_Reader.hxx>
#include <cadex/IGES_Reader.hxx>
#include <cadex/GLTF_Writer.hxx>

#include <iostream>
#include <string>

bool convertCADtoGLTF(const std::string& inputFilePath, const std::string& outputFilePath) {
    // Load CAD file
    cadex::ModelData_Model aModel;
    cadex::ModelData_ModelReader *aReader = nullptr;

    // Use the file extension to choose the correct reader
    if (inputFilePath.substr(inputFilePath.find_last_of(".") + 1) == "step") {
        aReader = new cadex::STEP_Reader();
    } else if (inputFilePath.substr(inputFilePath.find_last_of(".") + 1) == "iges") {
        aReader = new cadex::IGES_Reader();
    } else {
        std::cerr << "Unsupported CAD file format." << std::endl;
        return false;
    }

    cadex::Base_ProgressScope aPS;
    if (!aReader->ReadFile(inputFilePath.c_str()) || !aReader->Transfer(aModel, aPS)) {
        std::cerr << "Error reading CAD file." << std::endl;
        return false;
    }

    delete aReader;

    // Export to GLTF
    cadex::GLTF_Writer aGLTFWriter;
    if (!aGLTFWriter.Transfer(aModel) || !aGLTFWriter.WriteFile(outputFilePath.c_str())) {
        std::cerr << "Error exporting to GLTF." << std::endl;
        return false;
    }

    return true;
}

Napi::Boolean ConvertCADtoGLTFWrapper(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }

  std::string inputFilePath = info[0].As<Napi::String>();
  std::string outputFilePath = info[1].As<Napi::String>();

  bool result = convertCADtoGLTF(inputFilePath, outputFilePath);
  return Napi::Boolean::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("convertCADtoGLTF", Napi::Function::New(env, ConvertCADtoGLTFWrapper));
  return exports;
}

NODE_API_MODULE(cadexchanger, Init)

