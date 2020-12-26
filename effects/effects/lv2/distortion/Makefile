INSTALL_DIR = .out
BUNDLE = $(INSTALL_DIR)/distortion.lv2


$(BUNDLE): manifest.ttl distortion.ttl $(INSTALL_DIR)/distortion.so
	rm -rf $(BUNDLE)
	mkdir -p $(BUNDLE)
	cp $? $(BUNDLE)

$(INSTALL_DIR)/distortion.so: distortion.cpp
	mkdir -p $(INSTALL_DIR)
	g++ -shared -fPIC -DPIC $< `pkg-config --cflags --libs lv2-plugin` `pkg-config --cflags --libs lvtk-1` -o $@

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(INSTALL_DIR)
