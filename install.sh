# Here's what you do to install the neoPixel driver
# git clone https://github.com/Yona-Appletree/LEDscape.git
# cd LEDscape
# less README.md	# Follow these insturctions.
cp /boot/uboot/dtbs/am335x-boneblack.dtb{,.preledscape_bk}
cp am335x-boneblack.dtb /boot/uboot/dtbs
#reboot
#cd LEDscape
modprobe uio_pruss
#node pinmap.js	# This shows that P9_22 is string 0 and
		# Wiring as shown uses string 0
#./rgb-test	# Things should light up

# Do the following to run from Python
# gedit run-ledscape	# Set the -c option to the number of LEDs
# ./run-ledscape
# cd ..
# git clone https://github.com/zestyping/openpixelcontrol.git
# cd openpixelcontrol/python_clients
# ./example.py
