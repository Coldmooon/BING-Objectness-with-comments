# Introduction

This repo is related to the paper: 
BING: Binarized Normed Gradients for Objectness Estimation at 300fps. <br/>
Ming-Ming Cheng, Ziming Zhang, Wen-Yan Lin, Philip Torr.<br/>
IEEE CVPR, 2014. [pdf](http://mmcheng.net/mftp/Papers/ObjectnessBING.pdf)

Currently, there are a lot of implements of BING. First, The authors published the windows version. Then `bittnt` converted it into the [Linux version](https://github.com/torrvision/Objectness). After that, [varun-nagaraja](https://github.com/varun-nagaraja/BING-Objectness) further added some new auxiliary functions to `bittnt` version. Even `bittnt` version keeps updating, its core parts maintain the same. So, this repo uses `varun-nagaraja` verison.

The following files are heavily commented.
1. DataSetVOC.cpp
2. FilterTIG.cpp
3. FilterTIG.h
4. Objectness.cpp
5. Main.cpp

# For Opencv 3.3 or later
If you are using opencv 3.3 or later, you might encounter with this error during compling:
```
error: no type named ‘channel_type’ in ‘class cv::DataType<long int>
```
This is not a bug but mentions you to change the data type. Check issues [9985](https://github.com/opencv/opencv/issues/9985), [10115](https://github.com/opencv/opencv/issues/10115), [7599](https://github.com/opencv/opencv/issues/7599).
To fix this, simply add `#define OPENCV_TRAITS_ENABLE_DEPRECATED` in `stdafx.h`.

-------------------------------------------

## Detect bounding boxes of objects in images irrespective of class/category.

This is a fork of the BING Objectness code from www.mmcheng.net/bing for Linux and OSX. <br/>
It should also compile on Windows as intended by the original author (not tested).

Note: OpenMP is not yet supported by the default LLVM compiler in OSX, hence it is disabled for OSX. <br/>
Nevertheless, the code can still be compiled and executed successfully in OSX. 

It implements the techniques described in the following paper:<br/>
BING: Binarized Normed Gradients for Objectness Estimation at 300fps. <br/>
Ming-Ming Cheng, Ziming Zhang, Wen-Yan Lin, Philip Torr.<br/>
IEEE CVPR, 2014. [pdf](http://mmcheng.net/mftp/Papers/ObjectnessBING.pdf)

These are the results that I obtained using the fast detection variant <br/>
1:0.25,0.304  10:0.481,0.449  100:0.794,0.607 1000:0.958,0.669  <br/>
2000:0.969,0.673  3000:0.969,0.673  4000:0.969,0.673  5000:0.969,0.673

### Setup 
Download the [VOC 2007 train data](http://pascallin.ecs.soton.ac.uk/challenges/VOC/voc2007/VOCtrainval_06-Nov-2007.tar
) and put them in the VOC2007 directory. <br/>
Do not copy the ImageSets directory from the VOC dataset, retain the version supplied with this code. 

Download the [VOC2007 test data] (http://pascallin.ecs.soton.ac.uk/challenges/VOC/voc2007/VOCtest_06-Nov-2007.tar) <br/>
Move all images from <test>/JPEGImages folder to the earlier extracted VOC2007/JPEGImages folder.

Unzip the Annotations.zip file in the VOC2007 folder. <br/>
-Or- <br/>
Download an OpenCV readable version of [VOC 2007 annotations](http://mmcheng.net/mftp/Data/VOC2007_AnnotationsOpenCV_Readable.7z). 


### Building from source
Set OPENCV_DIR set as an environment variable in the shell if it is not present in the standard directories.
```
mkdir build
cd build
cmake ..
make
```
