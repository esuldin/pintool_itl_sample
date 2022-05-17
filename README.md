ILT pass-through sample
===
This is an example of Pin tool to pass through Incremental Linking Table (ILT). ILT is added to an executable file if /INCREMENTAL option is used for Microsoft Incremental Linker. In this case Intel Pin cannot replace the function in the application by another function out of the box. This sample shows how it can be implemented using Pin API. The sample was developed as an illustration for the article "[Analysis of machine code using Intel Pin](https://habr.com/ru/post/666274/)".

Building on Windows
---
 1. Download [Intel Pin kit](https://www.intel.com/content/www/us/en/developer/articles/tool/pin-a-dynamic-binary-instrumentation-tool.html) and extract it
 2. Set the path to the Intel Pin kit, for example

        set PinRoot=<path-to-pin-kit>\pin-3.22-98547-g7a303a835-msvc-windows

 3. Clone the repository

        git clone https://github.com/esuldin/pintool_itl_sample.git

 4. Open the solution

        cd pintool_itl_sample
        start pin_ilt_sample.sln

 5. Build the solution (press Ctrl+Shift+B)

