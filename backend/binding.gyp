{
  "targets": [
    {
      "target_name": "cadexchanger",
      "sources": ["cadexchanger.cc"],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/Users/bryceschuebert/Code/GitHub/PoseSnapAR/backend/cadexsdk_3.17.0_build16601_mac_full/include"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "libraries": [
        "-L/Users/bryceschuebert/Code/GitHub/PoseSnapAR/backend/cadexsdk_3.17.0_build16601_mac_full/lib",
        "-lcadex_license",
        "-lcadex_model",
        "-lcadex_base",
        "-lcadex"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": ["NAPI_CPP_EXCEPTIONS"]
    }
  ]
}

