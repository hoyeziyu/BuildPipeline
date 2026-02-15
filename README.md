# BuildPipeline
cmake构建流程，实现完整的配置树、构建树、安装树的构建流程，支持vcpkg依赖库的集成。


1.进入vendor/vcpkg目录，执行以下命令安装依赖库：
```
运行 vcpkg 附带的 bootstrap-vcpkg.bat 文件以完成设置
bootstrap-vcpkg.bat
```

2.设置 CMAKE_TOOLCHAIN_FILE 变量指向 vcpkg 在安装目录中
提供的变量 vendor/vcpkg/scripts/buildsystems/vcpkg.cmake

也可以使用系统环境变量PATH来指定 vcpkg 的安装目录。

3.修改CMakePresets.json中的testPresets中sanitize的PATH变量，指向
加载 MSVC 的 ASan 运行时动态库的具体位置
```
通常是clang_rt.asan_dynamic-x86_64.dll的位置：
where /r "D:\Apps\vs2022\path" clang_rt.asan_dynamic-x86_64.dll
```