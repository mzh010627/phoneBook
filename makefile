
#自定义变量
OBJ = main.o AVLTree.o doubleLinkList.o doubleLinkListQueue.o phoneBook.o
TARGET = main

#使用变量:$(变量名)
$(TARGET): $(OBJ)
	gcc $^ -o $@


add.o: AVLTree.c
	gcc -c $^ -o $@
sub.o:doubleLinkList.c
	gcc -c $^ -o $@
div.o:doubleLinkListQueue.c
	gcc -c $^ -o $@
mul.o:phoneBook.c
	gcc -c $^ -o $@

clean:
	@rm -rf  *.o main

