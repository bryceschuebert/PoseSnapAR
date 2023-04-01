{
  "targets": [
    {
      "target_name": "cadexchanger",
      "sources": ["cadexchanger_binding.cc"],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++"
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      },
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "cadexsdk/inc",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "<full_path_to_cadexchanger_library>/libcadex.dylib"
      ],
      "ldflags": [
        "-Wl,-rpath,<full_path_to_cadexchanger_library>"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
    }
  ]
}





