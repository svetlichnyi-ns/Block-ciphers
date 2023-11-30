CC=gcc
CFLAGS=-lm
SOURCES=AES/aes.c AES/aes_modes.c DES/des.c DES/des_modes.c Blowfish/blowfish.c Blowfish/blowfish_modes.c Base64/base64.c Base64/base64_test_time.c API_for_AES_time_performance.c
EXECUTABLE=API_for_AES_time_performance.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)