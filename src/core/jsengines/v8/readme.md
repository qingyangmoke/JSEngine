> v8 引擎


## 编译
 * [v8 build](https://v8.dev/docs/build)
 * 


 ### 安装depot_tools
 ```shell
  # clone代码
  git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
  # 配置全局环境变量/path/to/depot_tools改成depot_tools的目录
  echo 'export PATH=$PATH:"/path/to/depot_tools"' >> ~/.bashrc
```

 ### 安装ninja
 ```shell
  # clone代码
  git clone https://github.com/ninja-build/ninja.git
  cd ninja && ./configure.py --bootstrap && cd ..
  # 配置全局环境变量 /path/to/ninja改成ninja的目录
  echo 'export PATH=$PATH:"/path/to/ninja"' >> ~/.bashrc
```

## 下载v8源码
```shell
# 下载v8的repo，这个也是需要git代理才能成功下载的
fetch v8
cd v8
# 改成你自己的需要的分支 这里使用的
git checkout 7.7.299.13
# 同步 build dependencies
gclient sync
```
## 编译
```shell
  # 进入v8目录
  cd v8
  # 
  tools/dev/gm.py x64.release
  # 
  ninja -C out/x64.release
```


## 其他


### 编译sdk找不到
```python
# build/mac/find_sdk.py
re.findall('^MacOSX(11\.\d+)\.sdk$
```