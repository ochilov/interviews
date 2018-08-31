# Собрание интересных задачек

## Nokia
- [Prime Numbers](nokia/1.cpp)

	 Написать функцию, вычисляющую первые N простых чисел и помещающую эти числа в переданный ей массив.

- [Words](nokia/2.cpp)
	Написать функцию, подсчитывающую количество слов в тексте для каждой длины слова (столько-то слов из 1й буквы, столько-то слов из 2х букв, etc.)

- [List](nokia/3.cpp)
	Есть односвязный список:
	```cpp
	typedef struct List {
		DataType data;
		struct List* next;
	}
	```
	Написать функцию, которая удалит из этого списка каждый пятый элемент.
	
- [Bits](nokia/4.cpp)
	На вход функции поступает беззнаковое целое 32битное число. Требуется вывести на экран максимальное и минимальное целое беззнаковое 32битное число, которое может быть получено с использованием такого же числа единиц в двоичном представлении, как и у оригинального числа.

- [BinaryTree](nokia/5.cpp)
	Пускай бинарное дерево задано структурой вида:
	```cpp
	struct TreeNode {
		TreeNode *leftChild, *rightChild;
	}
	```
	Требуется написать функцию, вычисляющую ***глубину дерева*** (максимальное количество узлов на пути от корня до листа).