

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O3 -Wall -Wextra -Werror

TARGET   = filesorter
PREFIX   ?= /usr/local
SYSCONFDIR ?= $(PREFIX)/etc

CONFIG_DEST = $(SYSCONFDIR)/filesorter

SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "[LINK] Creating binary: $(TARGET)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	@echo "[CXX] Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "[CLEAN] Removing object files and binary"
	rm -f $(OBJS) $(TARGET)

install: all
	@echo "[INSTALL] Installing binary to $(PREFIX)/bin"
	install -Dm755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	
	@echo "[INSTALL] Copying entire config directory to $(CONFIG_DEST)"
	mkdir -p $(DESTDIR)$(CONFIG_DEST)
	cp -r config/* $(DESTDIR)$(CONFIG_DEST)/
	chmod 755 $(DESTDIR)$(CONFIG_DEST)
	chmod -R 644 $(DESTDIR)$(CONFIG_DEST)/*

uninstall:
	@echo "[UNINSTALL] Removing binary from $(PREFIX)/bin"
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	
	@echo "[UNINSTALL] Removing configuration directory $(CONFIG_DEST)"
	rm -rf $(DESTDIR)$(CONFIG_DEST)

