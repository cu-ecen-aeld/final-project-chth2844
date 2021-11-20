#!/bin/bash
# Script to build image for qemu.
# Author: Siddhant Jajoo.

git submodule init
git submodule sync
git submodule update

# local.conf won't exist until this step on first execution
source poky/oe-init-build-env

IMAGE="IMAGE_FSTYPES = \"wic.bz2\""
cat conf/local.conf | grep "${IMAGE}" > /dev/null
local_image_info=$?

#Set GPU memory as minimum
MEMORY="GPU_MEM = \"16\""
cat conf/local.conf | grep "${MEMORY}" > /dev/null
local_memory_info=$?

CONFLINE="MACHINE = \"raspberrypi3\""
cat conf/local.conf | grep "${CONFLINE}" > /dev/null
local_conf_info=$?

#Add any packages needed 
#ADD_PACK="CORE_IMAGE_EXTRA_INSTALL += \"uart\""
#cat conf/local.conf | grep "${ADD_PACK}" > /dev/null
#local_pack_info=$?

#Add any packages needed 
ADD_PACK="CORE_IMAGE_EXTRA_INSTALL += \"fps temperature server\""
cat conf/local.conf | grep "${ADD_PACK}" > /dev/null
local_pack_info=$?

# Add Wifi support
DISTRO_F="DISTRO_FEATURES:append = \"wifi\""
cat conf/local.conf | grep "${DISTRO_F}" > /dev/null
local_distro_info=$?

# Add firmware aupport
IMAGE_ADD="IMAGE_INSTALL:append = \"linux-firmware-rpidistro-bcm43430 v4l-utils python3 ntp wpa-supplicant libgpiod libgpiod-tools libgpiod-dev\""
cat conf/local.conf | grep "${IMAGE_ADD}" > /dev/null
local_imgadd_info=$?

# Add ssh support
IMAGE_F="IMAGE_FEATURES += \"ssh-server-openssh\""
cat conf/local.conf | grep "${IMAGE_F}" > /dev/null
local_imgf_info=$?

# Add I2C 
MODULE_I2C="ENABLE_I2C = \"1\""
cat conf/local.conf | grep "${MODULE_I2C}" > /dev/null
local_i2c_info=$?

# Autoload I2C_MODULE
AUTOLOAD_I2C="KERNEL_MODULE_AUTOLOAD:rpi += \"i2c-dev i2c-bcm2708\""
cat conf/local.conf | grep "${AUTOLOAD_I2C}" > /dev/null
local_i2c_autoload_info=$?

if [ $local_conf_info -ne 0 ];then
	echo "Append ${CONFLINE} in the local.conf file"
	echo ${CONFLINE} >> conf/local.conf
	
else
	echo "${CONFLINE} already exists in the local.conf file"
fi

if [ $local_pack_info -ne 0 ];then
    echo "Append ${ADD_PACK} in the local.conf file"
	echo ${ADD_PACK} >> conf/local.conf
else
	echo "${ADD_PACK} already exists in the local.conf file"
fi


if [ $local_distro_info -ne 0 ];then
        echo "Append ${DISTRO_F} in the local.conf file"
        echo ${DISTRO_F} >> conf/local.conf
        
else
        echo "${DISTRO_F} already exists in the local.conf file"
fi

if [ $local_imgadd_info -ne 0 ];then
        echo "Append ${IMAGE_ADD} in the local.conf file"
        echo ${IMAGE_ADD} >> conf/local.conf
        
else
        echo "${IMAGE_ADD} already exists in the local.conf file"
fi

if [ $local_imgf_info -ne 0 ];then
        echo "Append ${IMAGE_F} in the local.conf file"
        echo ${IMAGE_F} >> conf/local.conf
        
else
        echo "${IMAGE_F} already exists in the local.conf file"
fi


if [ $local_image_info -ne 0 ];then 
    echo "Append ${IMAGE} in the local.conf file"
	echo ${IMAGE} >> conf/local.conf
else
	echo "${IMAGE} already exists in the local.conf file"
fi

if [ $local_memory_info -ne 0 ];then
    echo "Append ${MEMORY} in the local.conf file"
	echo ${MEMORY} >> conf/local.conf
else
	echo "${MEMORY} already exists in the local.conf file"
fi

if [ $local_i2c_info -ne 0 ];then
        echo "Append ${MODULE_I2C} in the local.conf file"
        echo ${MODULE_I2C} >> conf/local.conf
else
        echo "${MODULE_I2C} already exists in the local.conf file"
fi

if [ $local_i2c_autoload_info -ne 0 ];then
        echo "Append ${AUTOLOAD_I2C} in the local.conf file"
        echo ${AUTOLOAD_I2C} >> conf/local.conf
else
        echo "${AUTOLOAD_I2C} already exists in the local.conf file"
fi


bitbake-layers show-layers | grep "meta-oe" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
	echo "Adding meta-oe layer"
	bitbake-layers add-layer ../meta-openembedded/meta-oe
else
	echo "meta-oe layer already exists"
fi

bitbake-layers show-layers | grep "meta-python" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-python layer"
        bitbake-layers add-layer ../meta-openembedded/meta-python
else
        echo "meta-python layer already exists"
fi

bitbake-layers show-layers | grep "meta-networking" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-networking layer"
        bitbake-layers add-layer ../meta-openembedded/meta-networking
else
        echo "meta-networking layer already exists"
fi

bitbake-layers show-layers | grep "meta-raspberrypi" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-raspberrypi layer"
        bitbake-layers add-layer ../meta-raspberrypi
else
        echo "meta-raspberrypi layer already exists"
fi

bitbake-layers show-layers | grep "meta-aesd" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-aesd layer"
        bitbake-layers add-layer ../meta-aesd
else
        echo "meta-aesd layer already exists"
fi

#bitbake-layers show-layers | grep "meta-uart" > /dev/null
#layer_info=$?

#if [ $layer_info -ne 0 ];then
	#echo "Adding meta-uartlayer"
	#bitbake-layers add-layer ../meta-uart
#else
	#echo "meta-uartlayer already exists"
#fi

bitbake-layers show-layers | grep "meta-fps" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
	echo "Adding meta-fpslayer"
	bitbake-layers add-layer ../meta-fps
else
	echo "meta-fpslayer already exists"
fi

bitbake-layers show-layers | grep "meta-temperature" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
        echo "Adding meta-temperature layer"
        bitbake-layers add-layer ../meta-temperature
else
        echo "meta-temperature layer already exists"
fi

bitbake-layers show-layers | grep "meta-server" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
	echo "Adding meta-serverlayer"
	bitbake-layers add-layer ../meta-server
else
	echo "meta-server already exists"
fi

set -e
bitbake core-image-base
