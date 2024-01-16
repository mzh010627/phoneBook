src=*.c
test:${src}
	gcc ${src} -o test

g:${src}
	gcc -g ${src} -o gtest

clean:
	@rm -rf test gtest phoneBook.txt