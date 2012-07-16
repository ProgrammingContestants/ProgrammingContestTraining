
JSRCDIR = src
CLASSES = classes
MANIFEST = manifest.mf
MAINCLASS = vmap.Main
JAR_TARGET = visualizer.jar

RUN_SH = run
RUN_BAT = run.bat

ARCHIVE = visualizer.tar.gz
TAR_INCLUDE = $(JAR_TARGET) $(CLASSES) $(JSRCDIR) $(RUN_SH) $(RUN_BAT) *.png *.txt Makefile

default: java tar

tar: $(ARCHIVE)

$(ARCHIVE): $(TAR_INCLUDE)
	tar -czf $(ARCHIVE) $(TAR_INCLUDE)

java: jar $(RUN_SH) $(RUN_BAT)

java_compile: $(CLASSES)

$(CLASSES):
	mkdir -p $(CLASSES)
	javac -d $(CLASSES) `find $(JSRCDIR) -name '*.java'`

jar: $(JAR_TARGET)

$(JAR_TARGET): $(CLASSES) $(MANIFEST)
	jar cfm $(JAR_TARGET) $(MANIFEST) -C $(CLASSES) .

$(MANIFEST):
	@echo 'Manifest-Version: 1.0' > $(MANIFEST)
	@echo 'Main-Class: $(MAINCLASS)' >> $(MANIFEST)

#
# Boot script for Linux shell
#
$(RUN_SH):
	echo '#!/bin/sh' > $(RUN_SH)
	echo 'java -jar $(JAR_TARGET)' >> $(RUN_SH)
	chmod +x $(RUN_SH)

#
# Boot script for Windows
#
$(RUN_BAT):
	echo 'java -jar $(JAR_TARGET)' > $(RUN_BAT)
	chmod +x $(RUN_BAT)

.PHONY: clean
clean:
	-rm -rf $(CLASSES) $(JAR_TARGET) $(MANIFEST)
	-rm -f $(RUN_SH) $(RUN_BAT)
	-rm -f $(ARCHIVE)
	-rm -f *.exe *.out
