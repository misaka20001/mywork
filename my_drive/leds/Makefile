CROSS=arm-linux-

all: led_test

led_test: led_test.c
	$(CROSS)gcc -o $@ led_test.c -static

clean:
	@rm -rf led_test *.o
